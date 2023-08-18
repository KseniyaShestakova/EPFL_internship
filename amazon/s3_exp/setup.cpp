#include "backend.h"
#include <cassert>
#include <vector>
#include <string.h>

static const int default_num_objects = 300;

void prepare_create(BackendData* bd, int num_iter) {
    bool flag = create_namespace(bd, "ns-create-" + std::to_string(num_iter));
    assert(flag && "Failed to create namespace");
}

// num is describing some characteristic specific for this test
void prepare_general(BackendData* bd, const std::string& operation, int num,
                                        bool use_default = false) {
    int num_objects = use_default ? default_num_objects : num;

    bool flag = false;

    std::string ns = "ns-" + operation + "-" + std::to_string(num);

    flag = create_namespace(bd, ns);
    assert(flag && "Failed to create namespace");
    
    std::vector<BackendObject*> bo(num_objects, nullptr);

    for (int i = 0; i < num_objects; ++i) {
        flag = create(bd, ns, "obj" + std::to_string(i), &bo[i]);
        assert(flag && "Failed to create object");
    }

    for (int i = 0; i < num_objects; ++i) {
        flag = close(bd, bo[i]);
        assert(flag && "Failed to close object");
    }

}

void prepare_read(BackendData* bd, int size, int num_iter) {
    bool flag = false;
 
    std::string ns = "ns-read-" + std::to_string(size) + "-" + std::to_string(num_iter);

    std::cout << "Trying to create " << ns << std::endl;
    flag = create_namespace(bd, ns);
    assert(flag && "Failed to create namespace");
 
    std::vector<BackendObject*> bo(num_iter, nullptr);
 
    for (int i = 0; i < num_iter; ++i) {
        flag = create(bd, ns, "obj" + std::to_string(i), &bo[i]);
        assert(flag && "Failed to create\n");
    }
 
     std::string str(size, 'a');
     uint64_t length = size;
     uint64_t offset = 0;
     uint64_t bytes_written = -1;
 
     for (int i = 0; i < num_iter; ++i) {
         flag = write(bd, bo[i], str.c_str(), length, offset, &bytes_written);
         assert(flag && "Failed to write\n");
     }

     for (int i = 0; i < num_iter; ++i) {
        flag = close(bd, bo[i]);
        assert(flag && "Failed to close\n");
     }
}

void prepare_list(BackendData* bd, int no_prefix, int with_prefix) {
    bool flag = false;

    std::string ns = "ns-list-" + std::to_string(no_prefix) + 
        "-" + std::to_string(with_prefix);

    flag = create_namespace(bd, ns);
    assert(flag && "Failed to create namespace");

    std::vector<BackendObject*> bo_no_prefix(no_prefix, nullptr);
    std::vector<BackendObject*> bo_with_prefix(with_prefix, nullptr);

    for (int i = 0; i < no_prefix; ++i) {
        flag = create(bd, ns, "obj" + std::to_string(i), &bo_no_prefix[i]);
        assert(flag && "Failed to create object");
    }

    for (int i = 0; i < with_prefix; ++i) {
        flag = create(bd, ns, "prefix/obj" + std::to_string(i), &bo_with_prefix[i]);
        assert(flag && "Failed to create object");
    }
}

void setup_general(BackendData* bd) {
    prepare_create(bd, 200);
    prepare_create(bd, 500);
 
    std::vector<std::string> operations = { "open", "close", "delete",
                                     "write-512", "write-2048"};
 
    std::vector<int> num_iters = {200, 500};
    std::vector<int> sizes = {512, 2048};
 
    for (auto operation: operations) {
        for (auto num_iter: num_iters) {
            prepare_general(bd, operation, num_iter);
        }
    }
 
    for (auto  num_iter: num_iters) {
        for (auto size: sizes) {
            prepare_read(bd, size, num_iter);
        }
    }
 
    prepare_list(bd, 500, 500);
}

void setup_read_write(BackendData* bd) {
    int num_iter = 300;

    std::vector<int> sizes = {512, 1024, 2048, 4096, 8192, 12288, 16384, 32768};

    for (auto size: sizes) {
        prepare_read(bd, size, num_iter);
        prepare_general(bd, "write", size, true);
    }
}

void setup_num_obj_dep(BackendData* bd) {
    int block_size = 2048;

    std::vector<int> num_iters = { 200, 400, 600, 800, 1000 };

    for (auto num_iter: num_iters) {
        prepare_read(bd, block_size, num_iter);
        prepare_general(bd, "write-" + std::to_string(block_size), num_iter);
    }
}

int main() {
    bool flag = false;

    std::string path = "127.0.0.1:9000";
    BackendData* bd = nullptr;
    flag = init(path, &bd);
    assert("Failed to initialize backend" && flag);

    setup_num_obj_dep(bd);

    fini(bd);
}



