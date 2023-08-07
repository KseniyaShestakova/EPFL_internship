#include "lib/backend.h"
#include <stdio.h>

int main() {
    char path[] = "127.0.0.1:9000";
    gpointer bd = NULL;
    backend_init(path, &bd);

    backend_fini(bd);
    return 0;
}
