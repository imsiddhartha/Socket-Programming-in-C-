#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include <sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include <arpa/inet.h>
#include<unistd.h>
#include<cstdlib>
using namespace std;

int main(int argc,char *argv[])
{
/*
Client
	1 socket
	2 connect 
	3 send/recv
	argv[1]=server_IP
	argv[2]=server Port_No
*/


	int sock,bin,sent_bytes,recv_bytes,sum,csocket,con;
	char msgr[1024];
	char msgs[1024];
	struct sockaddr_in server,client;
	
	sock=socket(AF_INET,SOCK_STREAM,0);						//AF_INET means IPv4 protocols

	if(sock<0)
	{
		printf("ERROR");
		exit(-1);
	}
	server.sin_family=AF_INET;
	server.sin_port= htons(atoi(argv[2]));					//host always big endian that whhhy host to network short
	//cout<<"port of server : "<<htons(atoi(argv[2]))<<endl;
	server.sin_addr.s_addr =inet_addr(argv[1]);		
	//cout<<"IP of Server: "<<inet_addr(argv[1])<<endl;
	/*
	The  inet_addr()  function converts the Internet host address cp from IPv4 numbers-and-dots notation into binary data in network byte
       order
	*/
	bzero(&server.sin_zero, 8);			
	
	unsigned int len=sizeof(struct sockaddr_in);

	// int connect(int sockfd, const struct sockaddr *addr,socklen_t addrlen);

	con=connect(sock, (struct sockaddr *)&server,len);
	
	if(con <0)
	{
		printf("Connection Error");
		exit(-1);
	}
	
	while(1)
	{
		cout<<"Type string to send : ";			//1
		//cin>>msgs;
		cin.getline (msgs,1024);
		sent_bytes=send(sock,msgs,strlen(msgs),0);
		//cout<<"No. of bytes sent : "<<sent_bytes<<endl;
		
		recv_bytes=recv(sock,msgr,1024,0);
		//cout<<"No. of bytes recvd : "<<recv_bytes<<endl;
		msgr[recv_bytes]='\0';
		cout<<"Sum recieved : "<<msgr<<endl;		//2
	}
	close(sock);
return 0;
}
