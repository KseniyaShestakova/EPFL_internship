#include "/home/xxeniash/EPFL_internship/minio_dev/minio-cpp/examples/backend.h"
#include <cassert>
#include <vector>
#include <gtest/gtest.h>

static const std::string default_path = "play.min.io";
static const int small_num_iter = 10;
static const int large_num_iter = 25;

/* Case 1:
 * creating a new file,
 * repeating create query,
 * opening it once more,
 * trying to delete (impossible because of many references),
 * closing,
 * deleting
 */
void easy_test_1() {
    bool flag = false;

    BackendData* bd = nullptr;
    flag = init(default_path, &bd);
    assert("Failed to initialize backend" && flag);

    std::string ns = "test-ns-1";
    flag = create_namespace(bd, ns);
    assert("Failed to create namespace" && flag); 

    BackendObject* bo_1 = nullptr;
    flag = open(bd, ns, "obj1.txt", &bo_1);
    assert("Failed to create object" && flag);

    BackendObject* bo_2 = nullptr;
    flag = create(bd, ns, "obj1.txt", &bo_2);
    assert("Repeated create succeeded" && !flag);
    assert("Repeated create spoiled BackendObject ptr" && bo_2 == nullptr);
    assert("Repeated create spoiled refCount" && bo_1->refCount == 1);

    flag = open(bd, ns, "obj1.txt", &bo_2);
    assert("Failed to open obj1.txt" && flag);
    assert("Open spoiled refCount" && (bo_1->refCount == 2) && (bo_2->refCount == 2));

    flag = delete_object(bd, bo_1);
    assert("Managed to delete an object with extra reference" && !flag);
    assert("Failing delete spoiled refCount" &&
            (bo_1->refCount == 2) && (bo_2->refCount == 2));

    flag = close(bd, bo_1);
    assert("Failed to close object" && flag);
    assert("Close spoiled refCount" && bo_2->refCount == 1);

    flag = delete_object(bd, bo_2);
    assert("Failed to delete object" && flag);


    flag = clean_namespace(bd, ns);
    assert("Failed to clean namespace" && flag);
    fini(bd);
    std::cout << "Easy test 1 passed!" << std::endl << std::endl;
}

/* Case 2:
 * opening a new object (without create),
 * trying to reuse bo pointer,
 * opening second bo for same file,
 * closing both bo-s,
 * reusing pointer to bo
 */
void easy_test_2() {
    bool flag = false;
 
    BackendData* bd = nullptr;
    flag = init(default_path, &bd);
    assert("Failed to initialize backend" && flag);
 
    std::string ns = "test-ns-2";
    flag = create_namespace(bd, ns);
    assert("Failed to create namespace" && flag); 

    BackendObject* bo = nullptr;
    flag = open(bd, ns, "obj1.txt", &bo);
    assert("Failed to open obj1.txt" && flag);

    flag = open(bd, ns, "obj2.txt", &bo);
    assert("Managed to reuse existing BackendObject" && !flag);
    assert("Failing open spoiled refCount" && bo->refCount == 1);

    BackendObject* bo_1 = nullptr;
    flag = open(bd, ns, "obj1.txt", &bo_1);
    assert("Failed to open object" && flag);
    assert("Repeated open spoiled refCount" && bo->refCount == 2 && bo_1->refCount == 2);

    flag = close(bd, bo);
    assert("Failed to close" && flag);
    assert("Close spoiled refCount" && bo_1->refCount == 1);

    flag = close(bd, bo_1);
    assert("Failed to close" && flag);
    // this test also aims to outline memory leaks in such cases

    bo = nullptr;
    flag = open(bd, ns, "obj2.txt", &bo);
    assert("Failed to open second object" && flag);

    flag = delete_object(bd, bo);
    assert("Failed to delete" && flag);


    flag = clean_namespace(bd, ns);
    assert("Failed to clean namespace" && flag);
    fini(bd);

    std::cout << "Easy test 2 passed!" << std::endl << std::endl;
}

/* Case 3:
 * working with single object and pointer to it:
 * uploading data,
 * retrieveing object status,
 * retrieving object contents
 */
void easy_test_3() {
    bool flag = false;

    BackendData* bd = nullptr;
    flag = init(default_path, &bd);
    assert("Failed to initialize backend" && flag);

    std::string ns = "test-ns-3";
    flag = create_namespace(bd, ns);
    //assert("Failed to create namespace" && flag);

    BackendObject* bo = nullptr;
    flag = open(bd, ns, "obj1.txt", &bo);
    assert("Failed to create object" && flag);

    char buffer[] = "Test write";
    uint64_t length = strlen(buffer);
    uint64_t offset = 0;
    uint64_t bytes_written = -1;
    uint64_t total = 0;
    //while (total < length) {
        flag = write(bd, bo, buffer + total, length - total, offset, &bytes_written);
        assert("Failed to write" && flag);
      //  assert("Written zero bytes" && (bytes_written > 0));
      //  total += bytes_written;
    //}
    std::cout << "written" << bytes_written << "out of" << length << std::endl;

    int64_t modification_time = 0;
    uint64_t size = 0;

    flag = status(bd, bo, &modification_time, &size);
    std::cout << "Got modification time:" << modification_time <<
         " and size: " << size << std::endl;

    assert("Failed to get status" && flag);
    //assert("Modification time is zero :(" && (modification_time != 0));
    assert("Got wrong size" && size == length);

    char read_buffer[256];
    // needed to subpress warning about uninitialized bytes
    memset(read_buffer, 0, 256);
    total = 0;
    uint64_t bytes_read = -1;
    while (total < length) {
        flag = read(bd, bo, read_buffer + total,
                            length, total, &bytes_read);
        assert("Failed to read" && flag);
        assert("Readzero bytes" && (bytes_read > 0));
        total += bytes_read;
        std::cout << "Bytes read " << bytes_read << std::endl; 
    }
    std::cout << "Read: " << read_buffer << std::endl;
    read_buffer[total] = 0;
    assert("Read wrong content" && !strcmp(buffer, read_buffer));

    flag = close(bd, bo);
    assert("Failed to close" && flag);

    flag = clean_namespace(bd, ns);
    assert("Failed to clean namespace" && flag);
    fini(bd);

    std::cout << "Easy test 3 passed!" << std::endl << std::endl;
}

void easy_test_4() {
    bool flag = false;

    BackendData* bd = nullptr;
    flag = init(default_path, &bd);
    assert("Failed to initialize backend" && flag);

    std::string ns = "test-ns-4-new";
    flag = create_namespace(bd, ns);
    //assert("Failed to create namespace" && flag);

    size_t num_obj = 5;
    std::vector<BackendObject*> bo_obj(num_obj, nullptr);
    for (uint64_t i = 0; i < num_obj; ++i) {
        flag = open(bd, ns, "obj" + std::to_string(i), &bo_obj[i]);
        assert("Failed to create object" && flag);
    }

    size_t num_foo = 6;
    std::vector<BackendObject*> bo_foo(num_foo, nullptr);
    for (uint64_t i = 0; i < num_foo; ++i) {
        flag = open(bd, ns, "foo-obj" + std::to_string(i), &bo_foo[i]);
        assert("Failed to create object" && flag);
    }

    BackendIterator* bi_all;
    get_all(bd, ns, &bi_all);

    std::string name;
    
    std::cout << "List of all elements in " << ns << std::endl;
    uint64_t cnt = 0;
    while(iterate(bd, bi_all, name)) {
        std::cout << name << std::endl;
        ++cnt;
    }
    assert("Got wrong number of elements" && cnt == num_obj + num_foo);
    iterator_free(bi_all);

    BackendIterator* bi_prefix;
    std::string prefix = "foo-";
    get_by_prefix(bd, ns, &bi_prefix, prefix);

    std::cout << "List of all elements in " << ns << prefix << std::endl;
    cnt = 0;
    while(iterate(bd, bi_prefix, name)) {
        std::cout << name << std::endl;
        ++cnt;
    }
    assert("Got wrong size of elements" && cnt == num_foo);
    iterator_free(bi_prefix);

    for (auto bo: bo_foo) {
        flag = close(bd, bo);
        assert("Failed to close" && flag);
    }

    for (auto bo: bo_obj) {
        flag = close(bd, bo);
        assert("Failed to close" && flag);
    }

    flag = clean_namespace(bd, ns);
    assert("Failed to clean namespace" && flag);
    fini(bd);
    std::cout << "Easy test 4 passed!" << std::endl << std::endl;
}


void multiple_creates(int num_iter) {
    BackendData* bd = nullptr;
    EXPECT_TRUE(init(default_path, &bd));

    bool flag = false;

    std::string ns = "ns-create-" + std::to_string(num_iter);

    std::vector<BackendObject*> bo(num_iter, nullptr);

    // memory leak!
    for (int i = 0; i < num_iter; ++i) {
        flag = create(bd, ns, "obj" + std::to_string(i), &bo[i]);
        EXPECT_TRUE(flag) << "Failed to create object\n";
    }

    fini(bd);
}

void multiple_opens(int num_iter) {
    BackendData* bd = nullptr;
    EXPECT_TRUE(init(default_path, &bd));
 
    bool flag = false;
 
    std::string ns = "ns-open-" + std::to_string(num_iter);

    std::vector<BackendObject*> bo(num_iter, nullptr);

    // memory leak!
    for (int i = 0; i < num_iter; ++i) {
        flag = open(bd, ns, "obj" + std::to_string(i), &bo[i]);
        EXPECT_TRUE(flag) << "Failed to open object\n";
    }

    fini(bd);
}

void multiple_closes(int num_iter) {
    BackendData* bd = nullptr;
    EXPECT_TRUE(init(default_path, &bd));
 
    bool flag = false;

    std::string ns = "ns-close-" + std::to_string(num_iter);

    std::vector<BackendObject*> bo(num_iter, nullptr);

    for (int i = 0; i < num_iter; ++i) {
         flag = open(bd, ns, "obj" + std::to_string(i), &bo[i]);
         EXPECT_TRUE(flag) << "Failed to open object\n";
     }

    for (int i = 0; i < num_iter; ++i) {
        flag = close(bd, bo[i]);
        EXPECT_TRUE(flag) << "Failed to close object\n";
    }

    fini(bd);
}

void multiple_deletes(int num_iter) {
    BackendData* bd = nullptr;
    EXPECT_TRUE(init(default_path, &bd));
 
    bool flag = false;
 
    std::string ns = "ns-delete-" + std::to_string(num_iter);
 
    std::vector<BackendObject*> bo(num_iter, nullptr);
 
    for (int i = 0; i < num_iter; ++i) {
         flag = open(bd, ns, "obj" + std::to_string(i), &bo[i]);
         EXPECT_TRUE(flag) << "Failed to open object\n";
    }
 
    for (int i = 0; i < num_iter; ++i) {
        flag = delete_object(bd, bo[i]);
        EXPECT_TRUE(flag) << "Failed to close object\n";
    }
 
    fini(bd);
}


void multiple_writes(int size, int num_iter) {
    bool flag = false;

    BackendData* bd = nullptr;
    flag = init(default_path, &bd);
    assert("Failed to initialize backend" && flag);

    std::string ns = "ns-write-" + std::to_string(size) + "-" + std::to_string(num_iter);

    std::vector<BackendObject*> bo(num_iter, nullptr);

    // memory leak!
    for (int i = 0; i < num_iter; ++i) {
        flag = open(bd, ns, "obj" + std::to_string(i), &bo[i]);
        EXPECT_TRUE(flag) << "Failed to open\n";
    }

    std::string str(size, 'a');
    uint64_t length = size;
    uint64_t offset = 0;
    uint64_t bytes_written = -1;

    for (int i = 0; i < num_iter; ++i) {
        flag = write(bd, bo[i], str.c_str(), length, offset, &bytes_written);
        EXPECT_TRUE(flag) << "Failed to write\n";
    }

    fini(bd);
}

void multiple_reads(uint64_t size, int num_iter) {
    bool flag = false;
    BackendData* bd = nullptr;
    flag = init(default_path, &bd);
    assert("Failed to initialize" && flag);

    std::string ns = "ns-read-" + std::to_string(size) + "-" + std::to_string(num_iter);

    std::vector<BackendObject*> bo(num_iter, nullptr);

    // memory leak!
    for (int i = 0; i < num_iter; ++i) {
        flag = open(bd, ns, "obj" + std::to_string(i), &bo[i]);
        EXPECT_TRUE(flag) << "Failed to open\n";
    }

    char* buffer = new char[size];
    std::string str(size, 'a');
    uint64_t length = size;
    uint64_t offset = 0;
    uint64_t bytes_read = -1;

    for (int i = 0; i < num_iter; ++i) {
        flag = read(bd, bo[i], buffer, length, offset, &bytes_read);
        EXPECT_TRUE(flag) << "Failed to read\n";
        EXPECT_TRUE(0 < bytes_read && bytes_read <= size) << "Strange bytes_read\n";
        EXPECT_EQ(0, memcmp(str.c_str(), buffer, bytes_read)) << "Wrong read content\n";
    }

    fini(bd);
}



void multiple_lists(int no_prefix, int with_prefix, int num_iter,
                    bool include_prefix, bool iterating) {
    bool flag = false;
    BackendData* bd = nullptr;
    flag = init(default_path, &bd);
    assert("Failed to initialize" && flag);

    std::string ns = "ns-listing-" + std::to_string(no_prefix) +
            "-" + std::to_string(with_prefix);

    std::vector<BackendObject*> bo_no_prefix(no_prefix, nullptr);
    std::vector<BackendObject*> bo_with_prefix(with_prefix, nullptr);

    for (int i = 0; i < no_prefix; ++i) {
        flag = open(bd, ns, "obj" + std::to_string(i), &bo_no_prefix[i]);
        EXPECT_TRUE(flag) << "Failed to open\n";
    }

    for (int i = 0; i < with_prefix; ++i) {
        flag = open(bd, ns, "prefix-obj" + std::to_string(i), &bo_with_prefix[i]);
        EXPECT_TRUE(flag) << "Failed to open\n";
    }

    uint64_t total = include_prefix ? with_prefix : with_prefix + no_prefix;

    for (int it = 0; it < num_iter; ++it) {
        BackendIterator* bi = nullptr;

        if (!include_prefix) {
            get_all(bd, ns, &bi);
        } else {
            get_by_prefix(bd, ns, &bi, "prefix-");
        }

        if (!iterating) {
            continue;
        }

        // iterate
        std::string name;
        uint64_t cnt = 0;
        while (iterate(bd, bi, name)) {
            ++cnt;
        }
        EXPECT_EQ(cnt, total) << "Wrong number of elements\n";
    }
}
/*
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */

TEST(Basic, JustBoot) {
    BackendData* bd = nullptr;
    assert(init(default_path, &bd));

    fini(bd);
}

TEST(Basic, BootAndCreateNamespace) {
    BackendData* bd = nullptr;
    assert(init(default_path, &bd));

    std::string ns = "test-ns-0";
    assert(create_namespace(bd, ns));
 
    assert(clean_namespace(bd, ns));
    fini(bd);
}



TEST(CAssert, easy_test_1) {
    easy_test_1();
}

TEST(CAssert, easy_test_2) {
    easy_test_2();
}

TEST(CAssert, easy_test_3) {
    easy_test_3();
}

TEST(CAssert, easy_test_4) {
    easy_test_4();
}



TEST(HighLoad, Createsmall_num_iter) {
    multiple_creates(small_num_iter);
}

TEST(HighLoad, Createlarge_num_iter) {
    multiple_creates(large_num_iter);
}

TEST(HighLoad, Opensmall_num_iter) {
    multiple_opens(small_num_iter);
}

TEST(HighLoad, Openlarge_num_iter) {
    multiple_opens(large_num_iter);
}

TEST(HigLoad, Closesmall_num_iter) {
    multiple_closes(small_num_iter);
}

TEST(HigLoad, Closelarge_num_iter) {
    multiple_closes(large_num_iter);
}

TEST(HighLoad, Deletesmall_num_iter) {
    multiple_deletes(small_num_iter);
}

TEST(HighLoad, Deletelarge_num_iter) {
     multiple_deletes(large_num_iter);
 }



TEST(HighLoad, Write512_small_num_iter) {
    multiple_writes(512, small_num_iter);
}

TEST(HighLoad, Write512_large_num_iter) {
     multiple_writes(512, large_num_iter);
}

TEST(HighLoad, Write2048_small_num_iter) {
    multiple_writes(2048, small_num_iter);
}

TEST(HighLoad, Write2048_large_num_iter) {
    multiple_writes(2048, large_num_iter);
}


TEST(HighLoad, Read512_small_num_iter) {
    multiple_reads(512, small_num_iter);
}

TEST(HighLoad, Read512_large_num_iter) {
    multiple_reads(512, large_num_iter);
}

TEST(HighLoad, Read2048_small_num_iter) {
    multiple_reads(2048, small_num_iter);
}

TEST(HighLoad, Read2048_large_num_iter) {
    multiple_reads(2048, large_num_iter);
}

TEST(HighLoad, ListNoPrefix) {
    multiple_lists(large_num_iter, large_num_iter, small_num_iter, false, false);
}

TEST(HighLoad, ListWithPrefix) {
    multiple_lists(large_num_iter, large_num_iter, small_num_iter, true, false);
}

TEST(HighLoad, IterateNoPrefix) {
    multiple_lists(large_num_iter, large_num_iter, small_num_iter, false, true);
}

TEST(HighLoad, IterateWithPrefix) {
    multiple_lists(large_num_iter, large_num_iter, small_num_iter, true, true);
}

