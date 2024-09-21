#include <sys/socket.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h> // close

int main()
{
// -------------------------------------
int socketfd = socket(PF_INET,SOCK_STREAM,0);
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
struct sockaddr_in Socket_Address;
Socket_Address.sin_family = AF_INET;
Socket_Address.sin_port = htons(22000);
Socket_Address.sin_addr.s_addr = htonl(INADDR_ANY);
// -------------------------------------
int bind_result = bind(socketfd,(struct sockaddr*)&Socket_Address,sizeof(Socket_Address));
if(bind_result==-1)
{
printf("Binding Failed! \n");
return -1;
}
else
{
printf("Binding Successful : %d \n",bind_result);
}
// --------------------------------------
int listen_result = listen(socketfd,10);
if(listen_result == -1)
{
printf("Not Listening! \n");
return -1;
}
else
{
printf("Listening Successfully : %d \n",listen_result);
}
// --------------------------------------
int comm_client_socket;
while(1)
{
comm_client_socket = accept(socketfd,(struct sockaddr*)NULL,NULL);
// --------------------------------------
int message_buffer_size=100;
char receiving_message[message_buffer_size];
bzero(receiving_message,message_buffer_size);
// --------------------------------------
int recv_bytes = recv(comm_client_socket,receiving_message,message_buffer_size,0);

if(recv_bytes == -1)
{
printf("Error in Receiving! \n");
}
else
{
printf("Bytes Received Successfully : %d \n",recv_bytes);
printf("Message Received at Server -> %s \n",receiving_message);
}
// ---------------------------------------
// strncat(receiving_message,", Hello!",sizeof(receiving_message)-strlen(receiving_message)-1);
int sent_bytes = send(comm_client_socket,receiving_message,strlen(receiving_message),0);
if(sent_bytes == -1)
{
printf("Sending Failed! \n");
return -1;
}
else
{
printf("Message Sent by Server -> %s \n",receiving_message);
printf("Bytes Sent by Server -> %d \n",sent_bytes);
}
int close_result = close(comm_client_socket);
if(close_result == 0)
{
break;
}
else if(close_result == -1)
{
printf("Failed to Close the Socket!");
}
}

return 0;
}
