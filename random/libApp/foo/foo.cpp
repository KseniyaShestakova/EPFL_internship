#include <iostream>
#include "foo.h"

extern "C" {
    void foo() {
        std::cout << "Hello from foo!" << std::endl;
    }
}
