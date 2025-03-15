#include <stdio.h>
#include <time.h> // Для clock()
#include "include/cfrequests.h"

int main(int argc, char* argv[]) {
    unsigned char buffer[8192] = { 0 };
    clock_t start = clock();

    frequest(GET, "0.0.0.0", 5000, "/api/moderators", NO_BODY, buffer, 8192);

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("[%s]\n", buffer);
    printf("Time spent: %.6f seconds\n", time_spent);

    return 0;
}