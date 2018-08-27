/*************************************************************************
	> File Name: master.c
	> Author: ShangKe
	> Mail: 
	> Created Time: 2018年06月23日 星期六 16时44分45秒
 ************************************************************************/

#include"common.c"

int master_get(int data_sock, int reqcode, char *client) {
    int size;
    char data_dir[50] = "/tmp";
    char data[MAX_SIZE] = {0};
    char arg[MAX_SIZE] = {0};
    char logdir[100] = {0};
    strcpy(logdir, data_dir);
    //if (logdir[sizeof(logdir - 1) != '/'])
    strcat(logdir, "/");
    strcat(logdir, client);
    mkdir(logdir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    generate_name(reqcode, arg, logdir);
    printf("arg: %s\n", arg);
    
    FILE *fd = fopen(arg, "a+");
    int times = 0;
    while ((size = recv(data_sock, data, MAX_SIZE, 0)) > 0) {
        printf("%d data: %s\n", ++times, data);
        fwrite(data, 1, size, fd);
        memset(data, 0, sizeof(data));
    }
    fclose(fd);
    return 0;
}


int main(int argc, char **argv) {
    int socket_fd, port;
    char *ip_addr;
    if (argc == 1) {
        ip_addr = "192.168.1.102";
        port = 8888;
    } else if (argc == 3){
        ip_addr = argv[1];
        port = atoi(argv[2]);
    } else {
        printf("Use : ./master ip_addr port\n");
    }
    int addr_index = 0;
    while (1) {
        ip_addr = ip_addrs[addr_index]; 
        addr_index = (addr_index + 1) % IP_NUM;
        socket_fd = socket_connect(port, ip_addr);
        if (socket_fd < 0) {
            printf("pi%d socket_fd error\n", addr_index);
            sleep(5);
            continue;
        }
        for (int i = 0; i < FILE_NUM; i++) {
            int retcode, pid;
            if ((retcode = recv_response(socket_fd)) <= 0) {
                break;
            }
            printf("retcode: %d\n", retcode);
            pid = fork();
            if (pid == 0) {
                int socket_data = socket_connect(port + 1, ip_addr);
                if (socket_data < 0) {
                    printf("socket_data error\n");
                    exit(1);
                }
                send_response(socket_fd, 200);
                printf("send_response\n");
                master_get(socket_data, retcode, ip_addr);
                close(socket_data);
                exit(0);
            } else {
                wait(NULL);
                send_response(socket_fd, 201);
                printf("pi%d connect end\n", addr_index); 
            }
        }
    }
    return 0;
}
