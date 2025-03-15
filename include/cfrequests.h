#ifndef _H_CFREQUESTS
#define _H_CFREQUESTS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <immintrin.h>

#include "socketman.h"
#include "fmemory.h"
#include "fmath.h"


#define BUFFER_SIZE 8192

#define NO_BODY NULL

#define HTTP_PORT   80
#define HTTPS_PORT  443
#define FTP_PORT    21
#define SFTP_PORT   22
#define IMAP_PORT   143
#define IMAPS_PORT  993
#define POP3_PORT   110
#define POP3S_PORT  995
#define SMTP_PORT   25
#define SMTPS_PORT  465

#define POST    "POST"
#define GET     "GET"
#define PUT     "PUT"
#define DELETE  "DELETE"


/*
Non SSL requests method.

Params:
- method - Method type POST/GET/PUT/DELETE.
- host - Base host ip or domain name.
- port - Host port.
- path - Second part of request url.
- body - Data body.
- buffer - Pointer to memory, where will store answer.
- buff_size - Buffer size.

Return pointer to buffer.
*/
unsigned char* frequest(
    const char* method, 
    const char* host, 
    int port, 
    const char* path, 
    const char* body, 
    unsigned char* buffer, 
    size_t buff_size
);

/*
Requests method.

Params:
- method - Method type POST/GET/PUT/DELETE.
- host - Base host ip or domain name.
- port - Host port.
- path - Second part of request url.
- body - Data body.
- buffer - Pointer to memory, where will store answer.
- buff_size - Buffer size.

Return pointer to buffer.
*/
unsigned char* frequest_ssl(
    const char* method, 
    const char* host, 
    int port, 
    const char* path, 
    const char* body, 
    unsigned char* buffer, 
    size_t buff_size
);

#endif