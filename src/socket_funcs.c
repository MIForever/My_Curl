#include "../include/socket_funcs.h"
#include "../include/string_funcs.h"
#include <netdb.h>
#include <arpa/inet.h>

in_addr_t get_ipv4_addr(char* hostname, struct SocketInfo* sock_info) {
    const char* service = "http";
    struct addrinfo hints;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(hostname, service, &hints, &(sock_info->result));
    if (status != 0) {
        m_perror("nodename nor servname provided, or not known");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in* ipv4_addr;
    for (struct addrinfo* p = sock_info->result; p != NULL; p = p->ai_next) {
        ipv4_addr = (struct sockaddr_in*)p->ai_addr;
        void* addr = &(ipv4_addr->sin_addr);
        char ip_address[INET_ADDRSTRLEN];

        inet_ntop(AF_INET, addr, ip_address, INET_ADDRSTRLEN);
        return ipv4_addr->sin_addr.s_addr;
    }

    return 0;
}


int fill_info(char* url, int fd_sock, struct SocketInfo* sock_info) {
    sock_info->info.sin_addr.s_addr = get_ipv4_addr(url, sock_info);
    sock_info->info.sin_port = htons(80);
    sock_info->info.sin_family = AF_INET;

    if (connect(fd_sock, (struct sockaddr*)&(sock_info->info), sizeof(sock_info->info)) < 0) {
        m_perror("connect");
        return 1;
    }

    freeaddrinfo(sock_info->result);
    return 0;
}


void parse_ip(char* ip, char** url, char** path) {
    int i = 0;
    int flag = 0;

    while (ip[i]) {
        if (ip[i] == '/' && ip[i - 1] == '/' && flag == 0) {
            *url = get_url(&ip[i + 1]);
            flag = get_len(&ip[i + 1]);
            break;
        }
        i++;
    }

    if (!ip[flag + i + 1]) {
        *path = (char*)malloc(2);
        if (*path == NULL) {
            m_perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }
        (*path)[0] = '/';
        (*path)[1] = '\0';
        return;
    }

    *path = &ip[flag + i + 1];
}


void read_and_write(int fd_sock) {
    char buff[1025] = {0};
    int n;
    char* content = NULL;
    int flag = 0;

    while (1) {
        fill_null(buff, 1024);
        n = read(fd_sock, buff, 1024);

        if (!flag) {
            if ((content = strstr(buff, "\r\n\r\n"))) {
                content += 4;
                write(1, content, my_strlen(content));
                flag = 1;
            }
        } else {
            write(1, buff, n);
        }

        if (n != 1024)
            break;
    }
}


int connecting(int fd_sock, char* ip) {
    char* url = NULL;
    char* path = "/";
    parse_ip(ip, &url, &path);

    struct SocketInfo sock_info;
    if (fill_info(url, fd_sock, &sock_info)) {
        return 1;
    }

    char* req = get_request(path, url);
    write(fd_sock, req, my_strlen(req));

    read_and_write(fd_sock);

    free(url);
    free(req);
    return 0;
}