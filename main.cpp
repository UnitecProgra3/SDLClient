#include <stdio.h>
#include <stdlib.h>
#ifndef _MSC_VER
#include <unistd.h>
#endif
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_net.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	IPaddress ip;
	TCPsocket sock;
	//char message[1024];
	int len;
	Uint16 port;

	/* initialize SDL */
	if(SDL_Init(0)==-1)
	{
		printf("SDL_Init: %s\n",SDL_GetError());
		exit(1);
	}

	/* initialize SDL_net */
	if(SDLNet_Init()==-1)
	{
		printf("SDLNet_Init: %s\n",SDLNet_GetError());
		exit(2);
	}

	/* get the port from the commandline */
	port=(Uint16) strtol("3000",NULL,0);

	/* Resolve the argument into an IPaddress type */
	if(SDLNet_ResolveHost(&ip,"127.0.0.1",port)==-1)
	{
		printf("SDLNet_ResolveHost: %s\n",SDLNet_GetError());
		exit(6);
	}

	/* open the server socket */
	sock=SDLNet_TCP_Open(&ip);
	if(!sock)
	{
		printf("SDLNet_TCP_Open: %s\n",SDLNet_GetError());
		exit(4);
	}

	/* read the buffer from stdin */
	printf("Escriba 'c', 'r' o 't':\n");
//	fgets(message,1024,stdin);

    string message;
    cin>>message;

    int result;

    /* print out the message */
    printf("Sending: %.*s\n",len,message.c_str());

    result=SDLNet_TCP_Send(sock,message.c_str(),len); /* add 1 for the NULL */
    if(result<len)
        printf("SDLNet_TCP_Send: %s\n",SDLNet_GetError());

	SDLNet_TCP_Close(sock);

	/* shutdown SDL_net */
	SDLNet_Quit();

	/* shutdown SDL */
	SDL_Quit();

	return(0);
}
