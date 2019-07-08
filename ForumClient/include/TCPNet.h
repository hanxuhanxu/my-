#include"res.h"

#ifndef _TCPNET_H_
#define _TCPNET_H_

#define FALSE 0
#define TRUE 1
#define BUFFSIZE 1024
#define SERVERIP "10.51.166.165"


int TCPSocket;
int UDPSocket;
char recvbuf[BUFFSIZE];
char sendbuf[BUFFSIZE];
MYSQL mysql;

struct sockaddr_in server_udp,client_udp;
struct sockaddr_in server_tcp,client_tcp;

void CreateUDPSocket();
void CreateTCPSocket();
void ConnectMysql();

void * udp_recv_thread(void *);
void * tcp_accept_thread(void *);
void * tcp_recv_thread(void *);
void * epoll_thread(void *);

int sqlAdd(char *name, char *password);
bool sqlfind(int id,char *password,STRU_ONLINERS * onliners);


#endif
