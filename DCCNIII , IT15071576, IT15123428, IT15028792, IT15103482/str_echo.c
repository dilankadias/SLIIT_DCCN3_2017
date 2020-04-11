#include	"header.h"

void
str_echo(int sockfd)
{
	char	line[MAXLINE];
	char	sendline[MAXLINE];
	int 	b;
	char 	ch;
	char 	ans;
	char 	ans2;
	ssize_t	n;

	char	qnumber[2];
	char	question[200];
	char	answers[100];
	char	correct[2];
	FILE	*fp;
	char	words[200];
	int 	i = 0 , random = 0;

		

		for( ; ; )
		{
			
			if((fp = fopen("QFile.txt" , "r+"))==NULL)
			{
				printf("Error! opening file");
				return;
			}
			srand(time(NULL));
				for(; fgets(words , sizeof(words) , fp) ; i++)
			          ;
			random = rand() % i;
			rewind(fp);
			for(i = 0 ; i < random ; i++)
			    fgets(words , sizeof(words) , fp);

			
 
			sscanf(words, "%s\t%[^\t]\t%s\t%[^\n]\t", qnumber, question, correct, answers);
		       




			memset(&line,0, sizeof(line));
			Read(sockfd, line, MAXLINE);
			ch = line[0];
								
			if(ch == 'q' || ch=='Q'){
				snprintf(sendline,sizeof(sendline),"%s\n%s\n",question,answers);
				Writen(sockfd, sendline, strlen(sendline));
				memset(&line,0, sizeof(line));
				Read(sockfd, line, MAXLINE);
				ans = line[0];
				
					if(ans == correct[0]){
						snprintf(sendline,sizeof(sendline),"answer is correct\n");
						Writen(sockfd, sendline, strlen(sendline));
						
						}
					
						
					else{
						snprintf(sendline,sizeof(sendline),"wrong answer\n");
						Writen(sockfd, sendline, strlen(sendline));
						/*snprintf(sendline,sizeof(sendline),"%s\n%s\n",question,answers);
						Writen(sockfd, sendline, strlen(sendline));*/
						}
				
				}
			else{
				memset(&sendline,0, sizeof(sendline));
				snprintf(sendline,sizeof(sendline),"invalied\n");
				Writen(sockfd, sendline, strlen(sendline));
				}
		}
		return;


	
}
