#include <nds.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <dswifi9.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>


char ip_decimal[0x10];

char * print_ip(u32 ip)
{
    unsigned char bytes[4];
    bytes[0] = ip & 0xFF;
    bytes[1] = (ip >> 8) & 0xFF;
    bytes[2] = (ip >> 16) & 0xFF;
    bytes[3] = (ip >> 24) & 0xFF;	
    sprintf(ip_decimal,"%d.%d.%d.%d\n", bytes[0], bytes[1], bytes[2], bytes[3]);        

return ip_decimal;
}

char * print_ip(u32 ip);


//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------

	consoleDemoInit();  //setup the sub screen for printing
	iprintf("Connecting via WFC data ...\n");

	if(!Wifi_InitDefault(WFC_CONNECT)) {
		iprintf("Failed to connect!");
	} else {

		iprintf("Connected %s\n\n",(char*)print_ip((u32)Wifi_GetIP()));
    }
	
	
    int sock;
	printf("UDP test program\nListens on port 8888, transmits data as a response to received data.\n");

	sock=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in sain;
	sain.sin_family=AF_INET;
	sain.sin_addr.s_addr=0;
	sain.sin_port=htons(8888);
	if(bind(sock,(struct sockaddr *)&sain,sizeof(sain))) {
		printf("bind() error!\n");
		close(sock);
		return 0;
	}

	char incomingbuf[1024];
	char outgoingbuf[1024];
	int datalen;
	int sain_len;
	struct sockaddr_in sender;
	while(1) {
		sain_len=sizeof(sender);
		datalen=recvfrom(sock,incomingbuf,1023,0,(struct sockaddr *)&sender,&sain_len);
		if(datalen>0) {
			incomingbuf[datalen]=0;
			printf("UDP Datagram from %i.%i.%i.%i:%i\n",(sender.sin_addr.s_addr)&255,(sender.sin_addr.s_addr>>8)&255,(sender.sin_addr.s_addr>>16)&255,(sender.sin_addr.s_addr>>24)&255,ntohs(sender.sin_port));
			printf("Received '%s' [%i]\n",incomingbuf,datalen);
			sprintf(outgoingbuf,"%s|rnd=%i",incomingbuf,rand()&0xFF);
			printf("Sent back: '%s' [%i]\n",outgoingbuf,strlen(outgoingbuf));
			sendto(sock,outgoingbuf,strlen(outgoingbuf)+1,0,(struct sockaddr *)&sender,sizeof(sender));
		}
		
		swiWaitForVBlank();
	}
	
	close(sock);
	return 0;
}