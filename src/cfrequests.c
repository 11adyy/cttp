#include "../include/cfrequests.h"


unsigned char* frequest(
    const char* method, 
    const char* host, 
    int port, 
    const char* path, 
    const char* body, 
    unsigned char* buffer, 
    size_t buff_size
) {
    if (
        port == HTTPS_PORT ||
        port == SFTP_PORT ||
        port == IMAPS_PORT ||
        port == POP3S_PORT ||
        port == SMTPS_PORT
    ) printf("[WARN] You are trying to use SSL port with non ssl method. Use frequest_ssl instead.");

    int sock = create_socket(host, port);
    if (sock < 0) return NULL;

    char request[BUFFER_SIZE] = { 0 };
    snprintf(
        request, BUFFER_SIZE, 
        "%s %s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\nContent-Length: %zu\r\n\r\n%s",
        method, path, host, body ? strlen(body) : 0, body ? body : ""
    );

    send(sock, request, strlen(request), 0);

    int total = 0, bytes;
    while ((bytes = recv(sock, request, BUFFER_SIZE - 1, 0)) > 0) {
        if (total >= buff_size) break;
        __f_memcpy(buffer + total, request, bytes);
        total += bytes;
    }

#ifdef _WIN32
    closesocket(sock);
#else
    close(sock);
#endif

    cleanup_sockets();
    return buffer;
}

unsigned char* frequest_ssl(
    const char* method, 
    const char* host, 
    int port, 
    const char* path, 
    const char* body, 
    unsigned char* buffer, 
    size_t buff_size
) {
    int sock = create_ssl_socket(host, port);
    if (sock < 0) return NULL;

    char request[BUFFER_SIZE] = { 0 };
    snprintf(
        request, BUFFER_SIZE, 
        "%s %s HTTPS/1.1\r\nHost: %s\r\nConnection: close\r\nContent-Length: %zu\r\n\r\n%s",
        method, path, host, body ? strlen(body) : 0, body ? body : ""
    );

    send_ssl_request(sock, request);
    int total = 0, bytes;
    while ((bytes = receive_ssl_response(sock, request, BUFFER_SIZE - 1)) > 0) {
        if (total >= buff_size) break;
        __f_memcpy(buffer + total, request, bytes);
        total += bytes;
    }

#ifdef _WIN32
    closesocket(sock);
#else
    close(sock);
#endif

    cleanup_sockets();
    cleanup_ssl();
    return buffer;
}
