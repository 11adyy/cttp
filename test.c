// gcc test.c src/*  -o test -mavx -lssl -lcrypto
#include <stdio.h>
#include "include/cfrequests.h"


int main(int argc, char* argv[]) {
    unsigned char buffer[512] = { 0 };
    frequest(GET, "osu.ru", HTTP_PORT, "/", NO_BODY, buffer, 512);
    printf("[%s]\n", buffer);
}