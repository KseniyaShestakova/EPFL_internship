#include "backend.h"
#include <cassert>
#include <vector>
#include <string>

void clean_up(BackendData* bd, const std::string& operation, int num_iters) {
    bool flag = clean_namespace(bd, "ns-" + operation + "-" + std::to_string(num_iters));
    assert(flag && "Failed to clean namespace");
}

int main() {
    bool flag = false;

    std::string path = "127.0.0.1:9000";
    BackendData* bd = nullptr;
    flag = init(path, &bd);
    assert("Failed to initialize backend" && flag);

    std::vector<int> num_iters = {200, 500};

    std::vector<std::string> operations = { "open", "create", "close",
        "delete", "write-512", "write-2048", "read-512", "read-2048"};

    for (auto num_iter: num_iters) {
        for (auto operation: operations) {
            clean_up(bd, operation, num_iter);
        }
    }

    clean_up(bd, "list-500", 500);

    fini(bd);
}
