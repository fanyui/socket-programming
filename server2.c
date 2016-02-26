//SERVER PROGRAM USING AF_INET AND SOCK_STREAM TO COMMUNICATE WITH DEFAULT IP 127.0.0.1

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
int main()
{
int server_sockfd, client_sockfd;
int server_len, client_len;
struct sockaddr_in server_address;
struct sockaddr_in client_address;

server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
server_address.sin_family = AF_INET;
server_address.sin_addr.s_addr = htonl(INADDR_ANY);
server_address.sin_port = htons(8080);
server_len = sizeof(server_address);
bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

listen(server_sockfd, 5);
while(1) {
int num1;
	int num2;
int operator;
int result;
printf("server waiting\n");
client_len = sizeof(client_address);
client_sockfd = accept(server_sockfd,
(struct sockaddr *)&client_address, &client_len);
read(client_sockfd, &num1, 4);
read(client_sockfd, &num2, 4);
read(client_sockfd, &operator, 4);
//result=num1+num2;
if(operator=='/' && num2==0)
result=100000;
else{
if (operator=='+')
result=num1+num2;
else if (operator=='-')
result=num1-num2;
else if(operator=='*')
result=num1*num2;
else if(operator=='/')
result=num1/num2;
else if(operator=='%')
result=num1%num2;
else result=100000;
}
write(client_sockfd, &result, sizeof(result));
close(client_sockfd);

}

}
