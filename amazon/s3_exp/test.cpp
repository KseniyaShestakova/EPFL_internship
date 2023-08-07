#include "backend.h"
#include <cassert>
#include <cassert>

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

    std::string path = "127.0.0.1:9000";
    BackendData* bd = nullptr;
    flag = init(path, &bd);
    assert("Failed to initialize backend" && flag);

    std::string ns = "test-ns-1";
    flag = create_namespace(bd, ns);
    assert("Failed to create namespace" && flag); 

    BackendObject* bo_1 = nullptr;
    flag = create(bd, ns, "obj1.txt", &bo_1);
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
 
    std::string path = "127.0.0.1:9000";
    BackendData* bd = nullptr;
    flag = init(path, &bd);
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



int main() {
    easy_test_1();
    easy_test_2();
    return 0;
}
