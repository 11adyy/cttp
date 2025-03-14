#ifndef _H_SOCKETMAN
#define _H_SOCKETMAN

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <netdb.h>
#endif

#include <openssl/ssl.h>
#include <openssl/err.h>
#include "fmemory.h"


int create_socket(const char *host, int port);
int create_ssl_socket(const char* host, int port);
int send_ssl_request(int sock, const char* request);
int receive_ssl_response(int sock, char* buffer, size_t size);

void cleanup_sockets();
void cleanup_ssl();

#endif