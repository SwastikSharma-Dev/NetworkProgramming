#include <sys/socket.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char **argv)
{
int socketfd = socket(PF_INET,SOCK_DGRAM,0);
if(socketfd==-1)
{
printf("Socket Creation Failed! \n");
return -1;
}
else
{
printf("Socket Creation Successful : %d \n", socketfd);
}
// -------------------------------------
struct sockaddr_in Socket_Address_Server;
Socket_Address_Server.sin_family = AF_INET;
Socket_Address_Server.sin_port = htons(22000);
Socket_Address_Server.sin_addr.s_addr = inet_addr("127.0.0.1");
// -------------------------------------
int message_size=100;
char sendline[message_size];
char recvline[message_size];
socklen_t addr_length = sizeof(Socket_Address_Server);

while(1)
{
bzero(sendline, message_size);
bzero(recvline, message_size);
printf("Enter the Message to Send -> ");
fgets(sendline,message_size,stdin);
// -------------------------------------
int sent_bytes = sendto(socketfd,sendline,strlen(sendline),0,(struct sockaddr*)&Socket_Address_Server,addr_length);
if(sent_bytes == -1)
{
printf("Sending Failed! \n");
return -1;
}
else
{
printf("Message Sent by Client -> %s \n",sendline);
printf("Bytes Sent by Client -> %d \n",sent_bytes);
}
// -------------------------------------
int recv_bytes = recvfrom(socketfd,recvline,message_size,0,(struct sockaddr*)&Socket_Address_Server,&addr_length);
if(recv_bytes == -1)
{
printf("Error in Receiving! \n");
}
else
{
printf("Bytes Received Successfully : %d \n",recv_bytes);
printf("Message Received at Client -> %s \n",recvline);
}
// -------------------------------------
int close_result = close(socketfd);
if(close_result == 0)
{
break;
}
else if(close_result == -1)
{
printf("Failed to Close the Socket!");
}
}

}
