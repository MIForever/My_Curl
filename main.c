#include "./include/socket_funcs.h"
#include "./include/string_funcs.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        m_perror("Usage: ./program_name <URL>\n");
        return EXIT_FAILURE;
    }

    int fd_sock;
    if ((fd_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        m_perror("Socket creation failed\n");
        return EXIT_FAILURE;
    }

    if (connecting(fd_sock, argv[1])) {
        m_perror("Connection failed\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}