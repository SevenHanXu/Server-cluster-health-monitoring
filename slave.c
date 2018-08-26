/*************************************************************************
	> File Name: slave.c
	> Author: ShangKe
	> Mail: 
	> Created Time: 2018年06月23日 星期六 16时45分12秒
 ************************************************************************/

#include"common.c"

int send_log(int data_sock, int retcode, char *client) {
    char data_dir[50] = "./log";
    char logdir[100] = {0};
    char data[MAX_SIZE] = {0};
    generate_name(retcode, logdir, data_dir);
    FILE *fp = fopen(logdir, "a+");
    int cnt = 0;
    printf("%s data : \n", logdir);
    while (fgets(data, MAX_SIZE - 1, fp)) {
        printf("%s\n", data);
        send(data_sock, data, strlen(data), 0);
    }
    fclose(fp);
    return 0;
}

int main(int argc, char **argv) {
    int server_listen, socket_fd, port, pid, data_listen;
    if (argc == 1) {
        port = 8888;
    } else {
        port = atoi(argv[1]);
    }

    server_listen = socket_create(port);
    data_listen = socket_create(port + 1);
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    if ((socket_fd = accept(server_listen, (struct sockaddr*)&client_addr, &len)) < 0) {
        printf("accept error\n");
    }

    char buff_peer[64] = {0};
    inet_ntop(AF_INET, (void *)&client_addr.sin_addr, buff_peer, 63);

    for (int i = 0; i < 6; i++){
        int retcode = 100 + i, socket_data;
        send_response(socket_fd, retcode);
        pid = fork();
        if (pid == 0) {
            if ((socket_data = accept(data_listen, (struct sockaddr*)&client_addr, &len)) < 0)
                break;
            recv_response(socket_fd);
            send_log(socket_data, retcode, buff_peer);
            close(socket_data);
            exit(0);
        } else {
            wait(NULL);
            recv_response(socket_fd);
        }
    }
    close(socket_fd);
    close(server_listen);
    close(data_listen);
    return 0;
}
