#include<iostream>
#include<WinSock2.h>
#include<cstring>
#define SERVER_ADDRESS "127.0.0.1" //服务器端IP地址      
#define PORT           8888         //服务器的端口号      
#define MSGSIZE        1024         //收发缓冲区的大小    
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#pragma comment(lib,"ws2_32.lib")
using namespace std;
class server {
private:
	int port; //端口号
	SOCKET sfd;  //监听套接字
	SOCKET cfd;  //客户端套接字
	struct sockaddr_in server_addr; //服务端ip
	struct sockaddr_in client_addr; //客户端ip
	char buf[MSGSIZE];
	char recvbuf[MSGSIZE];
	int len;
public:
	server(){
		port =PORT;
		sfd = -1;
		cfd = -1;
		WORD sockVersion = MAKEWORD(2, 2);
		WSADATA wsaData;
		if (WSAStartup(sockVersion, &wsaData) != 0)
		{
			return;
		}
		sfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sfd == -1) {
			cout << "创建套接字失败";
		}
		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.S_un.S_addr = INADDR_ANY;
		server_addr.sin_port = htons(8888);
		if (bind(sfd, (LPSOCKADDR)&server_addr, sizeof(server_addr))) {
			cout << "bind error!";
		}
	}
	~server() { close(); };
	void close() {
		closesocket(sfd);
		closesocket(cfd);
	}
	bool server_listen() {
		listen(sfd, 1);
		cout << "服务器启动，监听中...." << endl;
		len = sizeof(SOCKADDR);
		cfd = accept(sfd, (SOCKADDR*)&client_addr, &len);
		if (cfd >= 0) {
			cout << "accepted client:" << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << endl;
			return true;
		}
		else return false;
	}
	char* server_receive() {
		memset(recvbuf,'\0',1024);
		if (SOCKET_ERROR != recv(cfd, recvbuf, sizeof(recvbuf), 0)) {
			cout << "receive:" << recvbuf << endl;
			return recvbuf;
		}
		else {
			memset(recvbuf, '\0', 1024);
			return recvbuf;
		}
	}
	bool server_send(char* buff) {
		if (send(cfd, buff, strlen(buff) + 1, 0) != SOCKET_ERROR) {
			return true;
		}
		else{return false; }
	}
};
class client {
private:
	int port;
	SOCKET sfd;
	struct sockaddr_in server_addr;
	char recvbuf[MSGSIZE];
public:
	client() {
		WORD sockVersion = MAKEWORD(2, 2);
		WSADATA wsaData;
		if (WSAStartup(sockVersion, &wsaData) != 0)
		{
			return;
		}
		sfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sfd == -1) {
			cout << "创建套接字失败";
		}
		memset(&server_addr, 0, sizeof(SOCKADDR_IN)); //先将保存地址的server置为全0      
		server_addr.sin_family = PF_INET; //声明地址格式是TCP/IP地址格式      
		server_addr.sin_port = htons(PORT); //指明连接服务器的端口号，htons()用于 converts values between the host and network byte order      
		server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);   
	}
	~client() {
		close();
		WSACleanup();
	}
	void client_connect() {
		int cret = connect(sfd, (SOCKADDR*)&server_addr, sizeof(SOCKADDR));
		if (cret!=0){
			cout << "connect failed!" << endl;
		}
	}
	void client_send(char *buf) {
		send(sfd, buf, strlen(buf) + 1, 0);
	}
	char* cient_recv() {
		if (SOCKET_ERROR != recv(sfd, recvbuf, sizeof(recvbuf), 0)) {
			//cout << "receive:" << recvbuf << endl;
			return recvbuf;
		}
		else {
			memset(recvbuf, '\0', 1024);
			return recvbuf;
		}
	}
	void close() {
		closesocket(sfd);
	}
	SOCKET getsfd() { return sfd; }
};