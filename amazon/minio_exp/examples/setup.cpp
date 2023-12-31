#include "/home/xxeniash/EPFL_internship/minio_dev/minio-cpp/examples/backend.h"
#include <cassert>
#include <vector>
#include <string.h>

void prepare_create(BackendData* bd, int num_iter) {
    bool flag = create_namespace(bd, "ns-create-" + std::to_string(num_iter));
    assert(flag && "Failed to create namespace");
}

void prepare_general(BackendData* bd, const std::string& operation, int num_iter) {
    bool flag = false;
    std::string ns = "ns-" + operation + "-" + std::to_string(num_iter);

    flag = create_namespace(bd, ns);
    assert(flag && "Failed to create namespace");
    
    std::vector<BackendObject*> bo(num_iter, nullptr);

    for (int i = 0; i < num_iter; ++i) {
        flag = create(bd, ns, "obj" + std::to_string(i), &bo[i]);
        assert(flag && "Failed to create object");
    }

    for (int i = 0; i < num_iter; ++i) {
        flag = close(bd, bo[i]);
        assert(flag && "Failed to close object");
    }

}

void prepare_read(BackendData* bd, int size, int num_iter) {
    bool flag = false;
 
    std::string ns = "ns-read-" + std::to_string(size) + "-" + std::to_string(num_iter);
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

    std::string ns = "ns-listing-" + std::to_string(no_prefix) + 
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
        flag = create(bd, ns, "prefix-obj" + std::to_string(i), &bo_with_prefix[i]);
        assert(flag && "Failed to create object");
    }
}

int main() {
    bool flag = false;

    std::string path = "play.min.io";
    BackendData* bd = nullptr;
    flag = init(path, &bd);
    assert("Failed to initialize backend" && flag);

    prepare_create(bd, 10);
    prepare_create(bd, 25);

    std::vector<std::string> operations = { "open", "close", "delete",
                                    "write-512", "write-2048"};

    std::vector<int> num_iters = {10, 25};
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

    prepare_list(bd, 25, 25);
    

    fini(bd);
}



