#include<iostream>
#include<WinSock2.h>
#include<cstring>
#define SERVER_ADDRESS "127.0.0.1" //��������IP��ַ      
#define PORT           8888         //�������Ķ˿ں�      
#define MSGSIZE        1024         //�շ��������Ĵ�С    
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#pragma comment(lib,"ws2_32.lib")
using namespace std;
class server {
private:
	int port; //�˿ں�
	SOCKET sfd;  //�����׽���
	SOCKET cfd;  //�ͻ����׽���
	struct sockaddr_in server_addr; //�����ip
	struct sockaddr_in client_addr; //�ͻ���ip
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
			cout << "�����׽���ʧ��";
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
		cout << "������������������...." << endl;
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
			cout << "�����׽���ʧ��";
		}
		memset(&server_addr, 0, sizeof(SOCKADDR_IN)); //�Ƚ������ַ��server��Ϊȫ0      
		server_addr.sin_family = PF_INET; //������ַ��ʽ��TCP/IP��ַ��ʽ      
		server_addr.sin_port = htons(PORT); //ָ�����ӷ������Ķ˿ںţ�htons()���� converts values between the host and network byte order      
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