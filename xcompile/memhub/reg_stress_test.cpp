#include "memhub.h"
#include <stdio.h>
#include <iostream>
#include <sstream>

static memsvc_handle_t handle;

int main(int argc, char *argv[]) {

    if (memhub_open(&handle) != 0) {
        printf("Error while opening a memhub handle..");
        exit(1);
    }

    printf("Starting the test...\n");

    uint32_t i;
    uint32_t test_data;
    for (i=0; i < 1000000; i++) {
        test_data = i;
        memhub_write(handle, 0x66400008, 1, &test_data);
        test_data = 0;
        memhub_read(handle, 0x66400008, 1, &test_data);
        test_data = test_data & 0xffff;
        if (test_data != (i & 0xffff)) {
            printf("Error, expected %d, but got %d!\n", i, test_data);
        }
    }

    memhub_close(&handle);

}
