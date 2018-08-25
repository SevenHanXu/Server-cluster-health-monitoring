/*************************************************************************
	> File Name: common.c
	> Author: skange
	> Mail:
	> Created Time: 2018年06月10日 星期日 15时42分58秒
 ************************************************************************/

#include "common.h"

int socket_create(int port) {
    int socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in sock_addr = {0};
    if (socket_fd < 0) {
        perror("socket_create ");
        return -1;
    }
    
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(port);
    sock_addr.sin_addr.s_addr = INADDR_ANY;
    
    if (bind(socket_fd, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) < 0) {
        perror("bind");
        return -1;
    }

    if (listen(socket_fd, 10) < 0) {
        perror("listen");
        return -1;
    }
    return socket_fd;
}
