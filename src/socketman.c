#include "../include/socketman.h"


static SSL_CTX* ctx = NULL;
static SSL* ssl = NULL;
static int _socket_init = 0;
static int _ssl_init = 0;


static void _init_ssl() {
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();

    ctx = SSL_CTX_new(SSLv23_client_method());
    if (ctx == NULL) {
        fprintf(stderr, "Error: Unable to create SSL context\n");
        exit(1);
    }
}

static void _init_sockets() {
#ifdef _WIN32
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
#endif
}

void cleanup_sockets() {
#ifdef _WIN32
    _socket_init = 0;
    WSACleanup();
#endif
}

void cleanup_ssl() {
    _ssl_init = 0;
    if (ssl != NULL) {
        SSL_free(ssl);
        ssl = NULL;
    }

    if (ctx != NULL) {
        SSL_CTX_free(ctx);
        ctx = NULL;
    }
}

int create_socket(const char *host, int port) {
    if (!_socket_init) {
        _init_sockets();
        _socket_init = 1;
    }

    struct sockaddr_in server_addr;
    struct addrinfo hints, *result;
    int sock = 0;
    char port_str[6] = { 0 };
    snprintf(port_str, sizeof(port_str), "%d", port);

    __f_memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(host, port_str, &hints, &result) != 0) {
        fprintf(stderr, "Error: getaddrinfo failed\n");
        return -1;
    }

    sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (sock < 0) {
        perror("Socket creation failed");
        freeaddrinfo(result);
        return -1;
    }

    if (connect(sock, result->ai_addr, result->ai_addrlen) < 0) {
        perror("Connection failed");
        freeaddrinfo(result);
        return -1;
    }

    freeaddrinfo(result);
    return sock;
}

int create_ssl_socket(const char* host, int port) {
    if (!_socket_init) {
        _init_sockets();
        _socket_init = 1;
    }

    if (!_ssl_init) {
        _init_ssl();
        _ssl_init = 1;
    }

    struct sockaddr_in server_addr;
    struct addrinfo hints, *result;
    int sock = -1;
    char port_str[6];
    snprintf(port_str, sizeof(port_str), "%d", port);

    __f_memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(host, port_str, &hints, &result) != 0) {
        fprintf(stderr, "Error: getaddrinfo failed\n");
        return -1;
    }

    sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (sock < 0) {
        perror("Socket creation failed");
        freeaddrinfo(result);
        return -1;
    }

    if (connect(sock, result->ai_addr, result->ai_addrlen) < 0) {
        perror("Connection failed");
        freeaddrinfo(result);
        return -1;
    }

    freeaddrinfo(result);
    SSL *ssl = SSL_new(ctx);
    if (ssl == NULL) {
        fprintf(stderr, "Error: Unable to create SSL object\n");
        return -1;
    }

    SSL_set_fd(ssl, sock);
    if (SSL_connect(ssl) == -1) {
        fprintf(stderr, "Error: SSL connection failed\n");
        SSL_free(ssl);
        return -1;
    }

    return sock;
}

int send_ssl_request(int sock, const char* request, size_t len) {
    return SSL_write(ssl, request, len);
}

int receive_ssl_response(int sock, char* buffer, size_t size) {
    return SSL_read(ssl, buffer, size);
}
