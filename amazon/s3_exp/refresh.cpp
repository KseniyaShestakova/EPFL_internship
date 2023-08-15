#include "backend.h"
#include <cassert>
#include <vector>
#include <string.h>

void refresh_create(BackendData* bd, int num_iter) {
    bool flag = clean_namespace(bd, "ns-create-" + std::to_string(num_iter));
    assert(flag && "Failed to clean namespace");
    flag = create_namespace(bd, "ns-create-" + std::to_string(num_iter));
    assert(flag && "Failed to create namespace");
}

void refresh_delete(BackendData* bd, int num_iter) {
    bool flag = false;
    std::vector<BackendObject*> bo(num_iter, nullptr);
    std::string ns = "ns-delete-" + std::to_string(num_iter);

    for (int i = 0; i < num_iter; ++i) {
        flag = create(bd, ns, "obj" + std::to_string(i), &bo[i]);
        assert(flag && "Failed to create object");
    }

    for (int i = 0; i < num_iter; ++i) {
        flag = close(bd, bo[i]);
        assert(flag && "Failed to close object");
    }
}

int main() {
    bool flag = false;
    std::string path = "127.0.0.1:9000";
    BackendData* bd = nullptr;

    flag = init(path, &bd);
    assert("Failed to initialize backend" && flag);

    std::vector<int> num_iters = {200, 500};

    for (auto num_iter: num_iters) {
        refresh_create(bd, num_iter);
        refresh_delete(bd, num_iter);
    }

    fini(bd);
    return 0;
}
