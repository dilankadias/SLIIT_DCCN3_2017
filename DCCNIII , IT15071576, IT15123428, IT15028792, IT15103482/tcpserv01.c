#include	"header.h"
#include 	"signal.h"

int
main(int argc, char **argv)
{
	int					listenfd, connfd,port;
	pid_t				childpid;
	socklen_t			clientlength;
	struct sockaddr_in	clientaddr, serveraddr;
	void 				sig_chld(int);
	char				buff[MAXLINE];
	const char			*ptr;
	
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family      = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port        = htons(SERV_TCP_PORT);

	Bind(listenfd, (SA *) &serveraddr, sizeof(serveraddr));

	Listen(listenfd, LISTENQ);
	signal(SIGCHLD, sig_chld);

	for ( ; ; ) {
		clientlength = sizeof(clientaddr);
		if((connfd = Accept(listenfd, (SA *) &clientaddr, &clientlength)) < 0) {
			if(errno==EINTR)
				continue;
		else
			err_sys("accept error");
		}

		
		ptr = inet_ntop(AF_INET, &clientaddr.sin_addr, buff, sizeof(buff));
		port = (int) ntohs(clientaddr.sin_port);
		printf("connection from %s , port %d \n ", ptr, port);

		if ( (childpid = Fork()) == 0) {	/* child process */
			Close(listenfd);	/* close listening socket */
			str_echo(connfd);	/* process the request */
			exit(0);
		}
		Close(connfd);			/* parent closes connected socket */
	}
}
