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

void int_to_str(int ,char []);

int main()
{
/*
SERVER
	1 socket
	2 bind 
	3 listen
	4 accept
	My ip-10.1.131.69
	Athresh ip-10.1.131.43
*/

	int sock,bin,sent_bytes,recv_bytes,csocket,sum,i;
	char msgr[1024];									//for recieving msg
	char msgs[1024];									////for sending msg
	struct sockaddr_in server,client;
	
	sock=socket(AF_INET,SOCK_STREAM,0);						//AF_INET means IPv4 protocols

	if(sock<0)
	{
		printf("ERROR");
		exit(-1);
	}
	
	server.sin_family=AF_INET;
	server.sin_port= htons(10000);						//host always big endian that whhhy host to network short
	server.sin_addr.s_addr =INADDR_ANY;						//server will listen to all possible interfaces INADDR_ANY means any IP	
	//server.sin_addr.s_addr =INADDR_ANY;
	bzero(&server.sin_zero, 8);							//starting 8 bytes of server to zero	
	
	unsigned int len=sizeof(struct sockaddr_in);
	
	bin=bind(sock, (struct sockaddr *)&server ,len); 			//sockaddr is father of sockaddr_in,having only two elements in struct
	if(bin<0)
	{
		printf("ERROR");
		exit(-1);
	}
	
	if(listen(sock,5) == -1 )							//5 clients handle kr skta h mera server
	{
		printf("Many Requests");
		exit(-1);
	}
	/* if multiple clints then put this in while lolop and csocket ka ek array bna do*/
	
	csocket=accept(sock, (struct sockaddr *) &client, &len);		//descriptor for the accepted socket block sys call jb tk client nh aata wait kro
	
		if(csocket==-1)
		{
			printf("ERROR");
			exit(-1);
		}
		//cout<<"IP of CLIENT: "<<inet_ntoa(client.sin_addr)<<"Connected To port No: "<<ntohs(client.sin_port)<<endl;
	
		while(1)
		{
			sum=0;
			recv_bytes=recv(csocket,msgr,1024,0);
			//cout<<"No. of bytes recvd : "<<recv_bytes<<endl;
		
			
			msgr[recv_bytes]='\0';
			cout<<"String recieved : "<<msgr<<endl;		//  1
		
			for(i=0;i<recv_bytes;i++)
				sum=sum+msgr[i];								//cal ascii val and print it!
			
			int_to_str(sum,msgs);
			
			//cin.getline (msgs,1024);

			sent_bytes =send(csocket,msgs,strlen(msgs),0);
			cout<<"Sum Sent : "<<msgs<<endl;
		}	
		int clo=close(csocket);		
	
return 0;
}

void int_to_str(int sum,char msgs[])
{
	int i,res;char temp;
	i=0;
	
	while ( sum != 0 )
	{
		res=sum%10;
		//cout<<res;
		msgs[i]=res+'0';
		sum=sum/10;
		i++;
	}
	msgs[i]='\0';
	//cout<<"\n";
	//cout<<"INT_RO STR : "<<msgs<<endl;
	i = 0;
	res= strlen(msgs)-1;
   	while (i < res) 
   	{
		temp = msgs[i];
		msgs[i] = msgs[res];
		msgs[res] = temp;
		i++;
		res--;
   }

}
