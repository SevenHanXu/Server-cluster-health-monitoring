/*************************************************************************
	> File Name: common.c
	> Author: 
	> Mail: 
	> Created Time: 六  8/25 19:48:09 2018
 ************************************************************************/
#include "common.h"

int socket_create(int port) {
    int socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    /*socket(int domain, int type, int protocol) 
      domain 参数指定哪个协议用在当前套接字上；
             AF_INET   IPv4网络协议，TCP和UDP都可以用的协议
             AF_INET6  IPv6网络协议，TCP和UDP都可以用的协议
             AF_UNIX   本地通讯协议。具有高性能和低成本的IPC（进程间通讯）
      type    用于选择套接字使用的类型
             SOCK_STREAM  提供一个顺序化的、可靠的、全双工的、基于连接的字节流。支持数据传送流量控制。
                          TCP协议基于这种流式套接字
             SOCK_DGRAM    提供数据报文的支持。（无连接，不可靠、固定最大长度）UDP协议基于这种数据报文套接字
             SOCK_SEQPACKET提供一个顺序化的、可靠的、全双工的、面向连接的、固定最大长度的数据通信；
                          数据端通过接收每一个数据段来读取整个数据包
             SOCK_RAW      提供读取原始的网络协议。这种特殊的套接字可用于手工构建任意类型的协议 。一般使用这
                          个套接字来实现 ICMP 请求（例如 ping)
             SOCK_RDM      供一个可靠的数据层，但不保证到达顺序。一般的操作系统都未实现此功能。
    成功时返回 TRUE， 或者在失败时返回 FALSE。
    */
    struct sockaddr_in sock_addr = {0};//处理网络通信的地址；
    /*sockaddr 在头文件#include <sys/socketh>中定义，sockaddr的缺陷是：sa_data把目标地址和端口信息混在一起了;
     struct sockaddr {
     sa_family_t sin_family;//地址族
　　  char sa_data[14]; //14字节，包含套接字中的目标地址和端口信息               
　　 }; 
    【在本段程序中，sockaddr并不是结构体类型名，它是结构体sockaddr_in变量的名字】*/
    /*sockaddr_in在头文件#include<netinet/in.h>或#include <arpa/inet.h>中定义，该结构体解决了sockaddr的缺陷，
     把port和addr 分开储存在两个变量中;
     */
    if (socket_fd < 0) {//socket_fd < 0表示创建套接字失败；
        perror("socket_create ");
        return -1;
    }
    
    sock_addr.sin_family = AF_INET;//sin_family是地址家族
    sock_addr.sin_port = htons(port);//端口号转换成网络通用字节序；
    sock_addr.sin_addr.s_addr = INADDR_ANY;//网络地址,存储IP地址；
    
    if (bind(socket_fd, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) < 0) {
        perror("bind");
        return -1;
    }
    /*服务器端要用 bind() 函数将套接字与特定的IP地址和端口绑定起来，只有这样，流经该IP地址和端口的数据才能交
      给套接字处理；而客户端要用 connect() 函数建立连接。*/

    if (listen(socket_fd, 10) < 0) {
        perror("listen");
        return -1;
    }
    /*int listen(int sockfd, int backlog);
     (1) listen() 函数的主要作用就是将套接字( sockfd )变成被动的连接监听套接字（被动等待客户端的连接），至
      于参数 backlog 的作用是设置内核中连接队列的长度
     (2) 这里需要注意的是，listen()函数不会阻塞，它主要做的事情为，将该套接字和套接字对应的连接队列长度告诉 
     Linux 内核，然后，listen()函数就结束。
    */
    return socket_fd;
}

 
