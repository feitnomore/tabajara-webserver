/*
 * Tabajara HTTP Server 1.2
 * httpd.c -- This file contains the initialization
 *            routines for the http server.
 * 
 * Marcelo Feitoza Parisi 
 */

/* System libs */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <ctype.h>

/* Local libs */
#include "include/defines.h" /* Server/Socket definitions        */
#include "include/mime.h"	 /* To handle mime-types             */
#include "include/header.h"	 /* HTTP response header handler     */
#include "include/config.h"	 /* Most of the server configuration */
#include "include/error.h"	 /* Error pages template             */
#include "include/logger.h"  /* Logging stuff                    */

/* Local handlers */
#include "handler/handle_post.h" /* Handle HTTP POST verb */
#include "handler/handle_head.h" /* Handle HTTP HEAD verb */
#include "handler/handle_put.h"  /* Handle HTTP PUT verb  */
#include "handler/handle_get.h"  /* Handle HTTP GET berb  */
#include "handler/handler.h"     /* Client thread handler */


int main(int argc, char *argv[])
{
	printf("Tabajara HTTP Server 1.2\n");
	fflush(stdout);
	pthread_t tid;
	int ret;

	int sockfd, new_connection;    /* listen on sock_fd, new client on new_connection */
	struct sockaddr_in my_addr;	   /* my address information                          */
	struct sockaddr_in their_addr; /* client's address information                    */
	socklen_t sin_size;
	int yes = 1;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		log_str(ERROR_LOG, "ERROR: Not able to create the socket");
		exit(1);
	}

	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &yes, sizeof(int)) == -1) {
		log_str(ERROR_LOG, "ERROR: Not able to set our socket options");
		exit(1);
	}
	
	my_addr.sin_family = AF_INET;		    /* Use host byte order            */
	my_addr.sin_port = htons(atoi(MYPORT));	/* Setting the socket port        */
	my_addr.sin_addr.s_addr = INADDR_ANY;   /* We'll bind on 0.0.0.0          */
	memset(&(my_addr.sin_zero), '\0', 8);   /* zero the rest of the structure */

	/* Bind on 0.0.0.0 in MYPORT -> Default: 8080 */
	if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
		log_str(ERROR_LOG, "ERROR: Failed to bind, port probably already in use");
		exit(1);
	}

	/* Start listening for connections */
	if (listen(sockfd, MAXCON) == -1) {
		log_str(ERROR_LOG, "ERROR: Failed to start the main listener");
		exit(1);
	}

	printf("Server started successfully on port %s\n", MYPORT);
	fflush(stdout);

	/* Run forever */
	while(1) {
		sin_size = sizeof(struct sockaddr_in);
		/* Accept a new client in new_connection socket descriptor */
		if ((new_connection = accept(sockfd, (struct sockaddr *)&their_addr, (socklen_t*)&sin_size)) == -1) {
			log_str(ERROR_LOG, "ERROR: Unable to accept new connection");
			continue;
		}

		/* Create a new thread to handle this connection */
		if((ret = pthread_create(&tid, NULL, *Handler, (void *)(intptr_t)new_connection)) != 0) {
			log_str(ERROR_LOG, "ERROR: Not able to create the handler thread");
			continue;
		}

	}

	return 0;
}

