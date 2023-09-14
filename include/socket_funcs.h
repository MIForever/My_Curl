#ifndef SOCKET_FUNCS_H
#define SOCKET_FUNCS_H

#include <netinet/in.h>
#include "string_funcs.h"

struct SocketInfo {
    struct sockaddr_in info;
    struct addrinfo* result;
};

in_addr_t get_ipv4_addr(char* hostname, struct SocketInfo* sock_info);

int fill_info(char* url, int fd_sock, struct SocketInfo* sock_info);

void parse_ip(char* ip, char** url, char** path);

void read_and_write(int fd_sock);

int connecting(int fd_sock, char* ip);

#endif
