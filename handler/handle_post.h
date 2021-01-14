/*
 * Tabajara HTTP Server 1.2
 * handle_post.h -- This file contains the initialization
 *                  routines for the http server.
 * 
 * Marcelo Feitoza Parisi 
 */

void handle_post(void* threadfd, char* rcv_buf, char* theirip) {

    char snd_buf[MAXOUTPUT];
    char empty[]=" ";
    char req[50];
    char *http_cmd;
    int i, j;

    http_cmd = strtok(rcv_buf, empty);
    http_cmd = strtok(NULL, empty);
	i = strlen(http_cmd);

    /* Checking if request path is ROOT */
	if(i == 1 && strstr(http_cmd,"/")) { 
		strcpy(req, "/index.html");
		strcat(req, "\0"); 
	} else {
		for(j = 0; j < i; j++) {
			req[j] = http_cmd[j+1];
			req[j+1] = '\0';
		}
	}

    int total_post = strlen(br_p1)+strlen(br_p2)+strlen(br_p3)+100;
	
	/* Motando o 400 */
	char *response_content = malloc(sizeof(char)*total_post);
	char lenght[15];
	int content_size;
	strcpy(response_content, br_p1);
	strcat(response_content, MYHOST);
	strcat(response_content, br_p2);
	strcat(response_content, MYPORT);
	strcat(response_content, br_p3);
	strcat(response_content, "\0");
	content_size = strlen(response_content);
	snprintf(lenght,sizeof(lenght),"%d",(int)content_size);
	char *response_headers = generate_response_header(404, "Now", lenght, "text/html");
	strcpy(snd_buf, response_headers);

	/* Sending Response Headers */
	if (send((int)(intptr_t)threadfd, snd_buf, strlen(snd_buf), 0) == -1) {
		log_str(ERROR_LOG, "Error sending response headers");
	}
		
	/* Sending Contents */
	if (send((int)(intptr_t)threadfd, response_content, content_size, 0) == -1) {
		log_str(ERROR_LOG, "Error sending contents");
	}

	/* Free Memory */
	free(response_content);

	/* Logging */
	log_access(ACCESS_LOG, theirip, "POST", req, 400, content_size);
	log_error(ERROR_LOG, theirip, "POST", req, 400, content_size);
	
}