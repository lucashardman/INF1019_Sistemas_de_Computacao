/* 
 * udpserver.c - A simple UDP echo server 
 * usage: udpserver <port>
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>

#define BUFSIZE 1024

/*
 * error - wrapper for perror
 */
void error(char *msg) {
  perror(msg);
  exit(1);
}

//função parser que interpreta o comando recebido em buf e o interpreta de acordo
int parse_buff (char *buf, int n, int *cmd, char *name) {
    char *cmdstr, *cmdstr2;
    struct stat st;
    
    cmdstr = (char*) malloc(BUFSIZE * sizeof(char));
    cmdstr2 = (char*) malloc(BUFSIZE * sizeof(char));
    
    cmdstr = strtok(buf,", ");
    
    
	//RD-­‐REQ,path(string),strlen(int),payload(stringvazio),nrbytes(int),offset(int)
	//lê nrbytes do arquivo path a partir da posição offset
	if (strcmp(cmdstr, "RD-REQ") == 0)
	{
		
		
	}
	
	
	//WR-­-REQ,path(string),strlen(int),payload(string),nrbytes(int),offset(int)
	//escreve nrbytes do conteúdo de payload no arquivo path a partir da posição offset
	else if (strcmp(cmdstr, "WR-REQ") == 0)
	{
		
	}

	
	
	else if (strcmp(cmdstr, "FI-REQ") == 0)
	{
		
	}
	
	//DC-­‐REQ,path(string),strlen(int), dirname(string),strlen(int)
	//cria um novo subdiretório dirname em path
	else if (strcmp(cmdstr, "DC-REQ") == 0)
	{
		//path
		cmdstr = strtok(NULL,", ");
		//strlen
		cmdstr2 = strtok(NULL,", ");
		//dirname
		cmdstr2 = strtok(NULL,", ");
		
		//cmdstr = full path
		strcat(cmdstr, cmdstr2);
		
		printf("cmdstr: %s\n, cmdstr2: %s\n", cmdstr, cmdstr2);
		
		
		
		//cria novo diretório em path se diretório já não existe
		if (stat(cmdstr, &st) == -1)
		{
			printf("cria\n");
			mkdir(cmdstr, 0700);
			
			//buf  = DC-­‐REP,path(string),strlen(int)       
			strcpy(buf, "DC-REP, ");
			strcat(buf, cmdstr);
			strcat(buf, ", ");
			//strcat(buf, itoa(strlen(cmdstr), cmdstr2, 10));
			sprintf(buf, "%s, %d", buf, strlen(cmdstr));
		}
		else
		{
			printf("não cria")
			//buf  = DC-­‐REP,path(string),strlen(int)       
			strcpy(buf, "DC-REP, ");
			strcat(buf, ", ");
			sprintf(buf, "%s, %d", buf, 0);
		}
		
		
		
	}
	
	else if (strcmp(cmdstr, "DR-REQ") == 0)
	{
		
	}
	
	else if (strcmp(cmdstr, "DL-REQ") == 0)
	{
		
	}

	else 
	{
		printf("ERRO. Comando não reconhecido.\n");
		
	}
    printf("%s\n", cmdstr);
    
    name = strtok(NULL,"\0");
    *cmd = atoi(cmdstr);
    return 0;
}

int main(int argc, char **argv) {
  int sockfd; /* socket */
  int portno; /* port to listen on */
  int clientlen; /* byte size of client's address */
  struct sockaddr_in serveraddr; /* server's addr */
  struct sockaddr_in clientaddr; /* client addr */
  struct hostent *hostp; /* client host info */
  char buf[BUFSIZE]; /* message buf */
  char *hostaddrp; /* dotted decimal host addr string */
  int optval; /* flag value for setsockopt */
  int n; /* message byte size */
    
  char name[BUFSIZE];   // name of the file received from client
  int cmd;              // cmd received from client
    
  /* 
   * check command line arguments 
   */
  if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(1);
  }
  portno = atoi(argv[1]);

  /* 
   * socket: create the parent socket 
   */
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) 
    error("ERROR opening socket");

  /* setsockopt: Handy debugging trick that lets 
   * us rerun the server immediately after we kill it; 
   * otherwise we have to wait about 20 secs. 
   * Eliminates "ERROR on binding: Address already in use" error. 
   */
  optval = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, 
	     (const void *)&optval , sizeof(int));

  /*
   * build the server's Internet address
   */
  bzero((char *) &serveraddr, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons((unsigned short)portno);

  /* 
   * bind: associate the parent socket with a port 
   */
  if (bind(sockfd, (struct sockaddr *) &serveraddr, 
	   sizeof(serveraddr)) < 0) 
    error("ERROR on binding");

  /* 
   * main loop: wait for a datagram, then echo it
   */
  clientlen = sizeof(clientaddr);
  while (1) {

    /*
     * recvfrom: receive a UDP datagram from a client
     */
    bzero(buf, BUFSIZE);
    n = recvfrom(sockfd, buf, BUFSIZE, 0,
		 (struct sockaddr *) &clientaddr, &clientlen);
    if (n < 0)
      error("ERROR in recvfrom");
      
    parse_buff(buf,n, &cmd, name);
    /* 
     * gethostbyaddr: determine who sent the datagram
     */
    hostp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr, 
			  sizeof(clientaddr.sin_addr.s_addr), AF_INET);
    if (hostp == NULL)
      error("ERROR on gethostbyaddr");
    hostaddrp = inet_ntoa(clientaddr.sin_addr);
    if (hostaddrp == NULL)
      error("ERROR on inet_ntoa\n");
    printf("server received datagram from %s (%s)\n", 
	   hostp->h_name, hostaddrp);
    printf("server received %ld/%d bytes: %s\n", strlen(buf), n, buf);
    
    /* 
     * sendto: echo the input back to the client 
     */
    n = sendto(sockfd, buf, strlen(buf), 0, 
	       (struct sockaddr *) &clientaddr, clientlen);
    if (n < 0) 
      error("ERROR in sendto");
  }
}
