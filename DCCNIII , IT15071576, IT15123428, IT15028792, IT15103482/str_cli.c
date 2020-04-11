#include	"header.h"

void
str_cli(FILE *fp, int sockfd)
{
	char	sendline[MAXLINE], recvline[MAXLINE];
	int a;
	int maxfdp1;
	fd_set rset;
	
	

	printf("%s","Welcome to exam server.\n enter q for question\n");
	FD_ZERO(&rset);
	for( ; ; ){
		FD_SET(fileno(fp), &rset);
		FD_SET(sockfd, &rset);
		maxfdp1 = max(fileno(fp), sockfd) + 1;
		Select(maxfdp1, &rset, NULL, NULL, NULL);
		
		if(FD_ISSET(sockfd, &rset)){
			if(Read(sockfd, recvline, MAXLINE) == 0){
				err_quit("str_cli: server terminated prematurely");			
			}
			Fputs(recvline, stdout);
			memset(&recvline,0,sizeof(sendline));		
		}
		if(FD_ISSET(fileno(fp), &rset)){
			if(Fgets(sendline, MAXLINE, fp) == NULL){
				return;
			}
			Writen(sockfd, sendline, strlen(sendline));
			

		}	
	}
	/*for( ; ; ){
	Fgets(sendline, MAXLINE, fp);
	Writen(sockfd, sendline, strlen(sendline));
	Read(sockfd, recvline, MAXLINE);
	Fputs(recvline, stdout);
	memset(&recvline,0, sizeof(sendline));
	//Fgets(sendline, MAXLINE, fp);
	//Writen(sockfd, sendline, strlen(sendline));
	}*/

}
