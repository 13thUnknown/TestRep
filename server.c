#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
int main(int argc, char * argv[])
{
    struct sockaddr_in local, from;
	int sock, other;
	int side[3];
	int counter;
	int fromlen;
	int recv;
	char charCounter[4]={'\0'};
	char responce[128]={'\0'};
	char sideString[128]={'\0'};
	long int port = atoi(argv[1]);
	printf("Initializing socket...");
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }
	printf("Success\n");
    local.sin_family = AF_INET;
    local.sin_port = htons(port);
    local.sin_addr.s_addr = htonl(INADDR_ANY);
	printf("Binding port %d...", port);
    if(bind(sock, (struct sockaddr *)&local, sizeof(local)) < 0)
    {
        perror("bind");
        exit(2);
    }
	printf("Success\n");
	other=sock;
	fromlen=sizeof(from);
	printf("Ready to receive the data!\n");
	recv = recvfrom(other, charCounter, sizeof(charCounter), 0, (struct sockaddr *)&from, &fromlen);
	printf("Times to reply: %s \n",charCounter);
	counter=atoi(charCounter);
	srand(time(0));
	printf("Calculating and replying\n");
	 while(counter>0){
		//recv = recvfrom(sock, charCounter, sizeof(charCounter), 0, (struct sockaddr *)&from, &fromlen);
		side[0]=rand()%20;
		side[1]=rand()%20;
		side[2]=rand()%20;
		if((side[0]+side[1])>side[2]&&(side[0]+side[2])>side[1]&&(side[1]+side[2])>side[0]){
			sprintf(sideString,"{%d:",side[0]);
			strcat(responce,sideString);
			sprintf(sideString,"%d",side[1]);
			strcat(responce,sideString);
			sprintf(sideString,":%d}\n",side[2]);
			strcat(responce,sideString);
			printf("%s Remaining: %d\n",responce, counter);
			counter--;
			sendto(other, responce, 128, 0, (struct sockaddr *)&from, fromlen);
			for (int i=0;i<128;i++){
				responce[i]='\0';
			}
			sleep(1);
		}
    }
	printf("Done\n");
}




