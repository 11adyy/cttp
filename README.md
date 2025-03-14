# cttp

A compact C networking library for issuing HTTP-style requests over TCP sockets, with both plain and TLS-backed request paths. The public functions accept a method, host, port, URL path, optional body, and caller-owned response buffer. The repository also includes socket setup and lightweight memory and math helpers.

## Public API

Include `include/cfrequests.h` to use the request interface:

```c
#include "include/cfrequests.h"

unsigned char response[8192] = {0};
frequest(GET, "example.com", 80, "/", NO_BODY,
         response, sizeof response);
```

`frequest` opens a TCP connection and sends a request. `frequest_ssl` uses the TLS socket helpers for encrypted connections. The header defines the common method strings (`GET`, `POST`, `PUT`, and `DELETE`), a default buffer size, and port constants for several services.

The response is copied into a buffer owned by the caller. Choose a buffer large enough for the expected response and check the return value before using the data. The current API is intentionally small: it does not expose a structured response object or a full HTTP parser.

## Source layout

- `include/cfrequests.h` declares the request functions and method constants.
- `include/socketman.h` declares platform socket and OpenSSL helpers.
- `src/cfrequests.c` builds and sends request bytes.
- `src/socketman.c` creates TCP/TLS connections and performs socket cleanup.
- `src/fmemory.c` and `src/fmath.c` provide project helper routines.
- `test.c` contains a small request example.

## Build requirements

Build with a C compiler and OpenSSL development headers and libraries. On Unix-like systems, link the OpenSSL SSL and crypto libraries and include the source files in `src/`. Windows builds use Winsock and require the matching OpenSSL development package.

```bash
cc -I. test.c src/cfrequests.c src/socketman.c src/fmemory.c \
  -lssl -lcrypto -o cttp-example
```

Adjust the compiler command for the platform and the exact OpenSSL installation. The implementation has platform-specific socket setup, but network calls still depend on DNS, remote availability, and firewall rules.

## Current boundaries

This is a low-level request helper intended for small C programs and experiments. It currently uses a fixed-size request construction buffer and a caller-provided response buffer, so applications should account for those limits. It does not provide high-level URL parsing, automatic redirects, cookie storage, retries, or complete HTTP response decoding.
