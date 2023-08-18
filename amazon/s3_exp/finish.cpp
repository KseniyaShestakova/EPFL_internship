#include "backend.h"
#include <cassert>
#include <vector>
#include <string>

void clean_up(BackendData* bd, const std::string& operation, int num_iters) {
    std::string ns = "ns-" + operation + "-" + std::to_string(num_iters);
    std::cout << "trying to clean " << ns << std::endl; 
    bool flag = clean_namespace(bd, ns);
    assert(flag && "Failed to clean namespace");
}

void finish_general(BackendData* bd) {
    std::vector<int> num_iters = {200, 500};
 
    std::vector<std::string> operations = { "open", "create", "close",
        "delete", "write-512", "write-2048", "read-512", "read-2048"};
 
    for (auto num_iter: num_iters) {
        for (auto operation: operations) {
            clean_up(bd, operation, num_iter);
        }
    }
 
    clean_up(bd, "list-500", 500);
}

void finish_read_write(BackendData* bd) {
    int num_iter = 300;

    std::vector<int> sizes = {512, 1024, 2048, 4096, 8192, 12288, 16384, 32768};

    for (auto size: sizes) {
        clean_up(bd, "read-" + std::to_string(size), num_iter);
        clean_up(bd, "write", size);
    }
}

void finish_num_obj_dep(BackendData* bd) {
    int block_size = 2048;

    std::vector<int> num_iters = { 200, 400, 600, 800, 1000 };

    for (auto num_iter: num_iters) {
        clean_up(bd, "read-" + std::to_string(block_size), num_iter);
        clean_up(bd, "write-" + std::to_string(block_size), num_iter);
    }

}

int main() {
    bool flag = false;

    std::string path = "127.0.0.1:9000";
    BackendData* bd = nullptr;
    flag = init(path, &bd);
    assert("Failed to initialize backend" && flag);

    finish_num_obj_dep(bd);

    fini(bd);
}
