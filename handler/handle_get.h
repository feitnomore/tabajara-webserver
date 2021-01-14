/*
 * Tabajara HTTP Server 1.2
 * handle_get.h -- This file contains the initialization
 *                 routines for the http server.
 * 
 * Marcelo Feitoza Parisi 
 */

void handle_get(void* threadfd, char* rcv_buf, char* theirip) {

    char snd_buf[MAXOUTPUT];
    char empty[]=" ";
    char req[50];
    char *http_cmd;
    int i, j, flag_slash = 0;
	struct stat file_properties;

	char newreq[300];

    http_cmd = strtok(rcv_buf, empty);
    http_cmd = strtok(NULL, empty);
	i = strlen(http_cmd);

    /* Checking if request path is ROOT */
	if(i == 1 && strstr(http_cmd,"/")) { 
		strcpy(req, "/index.html");
		strcat(req, "\0");
		flag_slash = 1;
	} else {
		for(j = 0; j < i; j++) {
			req[j] = http_cmd[j+1];
			req[j+1] = '\0';
		}
	}

    /* Is this an empty request or bad request? */
	if(strlen(req) == 1 && flag_slash != 1) {
		int response_size = strlen(br_p1)+strlen(br_p2)+strlen(br_p3)+100;
	
		/* Building error 400 */
		char *response_content = malloc(sizeof(char)*response_size);
		char length[15];
		int content_size;
		strcpy(response_content, br_p1);
		strcat(response_content, MYHOST);
		strcat(response_content, br_p2);
		strcat(response_content, MYPORT);
		strcat(response_content, br_p3);
		strcat(response_content, "\0");
		content_size = strlen(response_content);
		snprintf(length,sizeof(length),"%d",(int)content_size);
		char *response_headers = generate_response_header(404, "Now", length, "text/html");
		strcpy(snd_buf, response_headers);

		/* Sending Response Headers */
		if (send((int)(intptr_t)threadfd, snd_buf, strlen(snd_buf), 0) == -1) {
			log_str(ERROR_LOG, "Error sending response headers");
		}
		
		/* Sending contents */
		if (send((int)(intptr_t)threadfd, response_content, content_size, 0) == -1) {
			log_str(ERROR_LOG, "Error sending contents");
		}

		/* Free Memory */
		free(response_content);

		/* Logging */
		log_access(ACCESS_LOG, theirip, "GET", req, 400, content_size);
		log_error(ERROR_LOG, theirip, "GET", req, 400, content_size);

	}
		
	/* Not a bad request */
	else if(strlen(req) > 2) {
		if(flag_slash == 1) {
			strcpy(http_cmd, req);
		}

		memcpy(newreq, MYDOCS, 6);
		strcat(newreq, http_cmd);
		strcat(newreq, "\0");
		int filedes;
			
		/* Tyring to open the file */
		if((filedes = open(newreq, O_RDONLY)) != -1) {
			stat(newreq, &file_properties);
			char length[20];
			snprintf(length,sizeof(length),"%d",(int)file_properties.st_size);
			time_t last_m = file_properties.st_mtime;
			char *last_modif = ctime(&last_m);
			char *type;
			type = find_mime(newreq);
			char *response_headers = generate_response_header(200, last_modif, length, type);
			strcpy(snd_buf, "");
			strcpy(snd_buf, response_headers);
			char *file_content;
				
			/* Mapping the file to the memory */
			if ((file_content = mmap (0, file_properties.st_size, PROT_READ, MAP_SHARED, filedes, 0)) == (caddr_t) -1) {
				log_str(ERROR_LOG, "mmap error for input");
			}
				
			/* Sending Response Headers */
			if (send((int)(intptr_t)threadfd, snd_buf, strlen(snd_buf), 0) == -1) {
				log_str(ERROR_LOG, "Error sending response headers");
			}
				
			/* Sending contents */
			if (send((int)(intptr_t)threadfd, file_content, file_properties.st_size, 0) == -1) {
				log_str(ERROR_LOG, "Error sending contents");
			}
				
			close(filedes);

			/* Logging */
			log_access(ACCESS_LOG, theirip, "GET", req, 200, (int)file_properties.st_size);
			
		/* Error opening the file */
		} else {
			int response_size = strlen(nf_p1)+strlen(nf_p2)+strlen(nf_p3)+strlen(nf_p4)+100;		
	
			/* Building error 404 */
			char *response_content = malloc(sizeof(char)*response_size);
			char length[15];
			int content_size;
			strcpy(response_content, nf_p1);
			strcat(response_content, req);
			strcat(response_content, nf_p2);
			strcat(response_content, MYHOST);
			strcat(response_content, nf_p3);
			strcat(response_content, MYPORT);
			strcat(response_content, nf_p4);
			strcat(response_content, "\0");
			content_size = strlen(response_content);
			snprintf(length,sizeof(length),"%d",(int)content_size);
			char *response_headers = generate_response_header(404, "Now", length, "text/html");
			strcpy(snd_buf, response_headers);

			/* Sending Response Headers */
			if (send((int)(intptr_t)threadfd, snd_buf, strlen(snd_buf), 0) == -1) {
				log_str(ERROR_LOG, "Error sending response headers");
			}
				
			/* Sending contents */
			if (send((int)(intptr_t)threadfd, response_content, content_size, 0) == -1) {
				log_str(ERROR_LOG, "Error sending contents");
			}

			/* Free Memory */
			free(response_content);

			/* Logging */
			log_access(ACCESS_LOG, theirip, "GET", req, 404, content_size);
		}
			
	}
		
	/* 
	 * 400 - Bad Request
	 */
	else {
		int response_size = strlen(br_p1)+strlen(br_p2)+strlen(br_p3)+100;
	
		/* Building error 400 */
		char *response_content = malloc(sizeof(char)*response_size);
		char length[15];
		int content_size;
		strcpy(response_content, br_p1);
		strcat(response_content, MYHOST);
		strcat(response_content, br_p2);
		strcat(response_content, MYPORT);
		strcat(response_content, br_p3);
		strcat(response_content, "\0");
		content_size = strlen(response_content);
		snprintf(length,sizeof(length),"%d",(int)content_size);
		char *response_headers = generate_response_header(404, "Now", length, "text/html");
		strcpy(snd_buf, response_headers);

		/* Sending Response Headers */
		if (send((int)(intptr_t)threadfd, snd_buf, strlen(snd_buf), 0) == -1) {
			log_str(ERROR_LOG, "Error sending response headers");
		}
			
		/* Sending contents */
		if (send((int)(intptr_t)threadfd, response_content, content_size, 0) == -1) {
			log_str(ERROR_LOG, "Error sending contents");
		}

		/* Free Memory */
		free(response_content);

		/* Logging */
		log_access(ACCESS_LOG, theirip, "GET", req, 400, content_size);
		log_error(ERROR_LOG, theirip, "GET", req, 400, content_size);
	}
}