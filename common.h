/*************************************************************************
	> File Name: command.h
	> Author: ShangKe
	> Mail: 
	> Created Time: 2018年06月10日 星期日 15时21分50秒
 ************************************************************************/

#ifndef _COMMAND_H
#define COMMAND_H

#define OPEN_DBG 1
#ifdef OPEN_DBG 
#define DBG(format,...) printf(""__FILE__" : %s : %05d==>"format"\n", __func__, __LINE__,##__VA_ARGS__)
#else
#define DBG(s) 1
#endif

#include<arpa/inet.h>
#include<ctype.h>
#include<dirent.h>
#include<errno.h>
#include<fcntl.h>
#include<netdb.h>
#include<netinet/in.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<signal.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<time.h>
#include<stdarg.h>

#define MAX_SIZE 1034
#define MASTER_PORT 6666

#define FILE_NUM 6

int socket_create(int port);
int socket_connect(int port, char *host);
int recv_data(int sockfd, char *buf, int bufsize);
int send_response(int sockfd, int req);
int recv_response(int sockfd);
int generate_logname(int code, char *logname, char *logdir);

#endif
