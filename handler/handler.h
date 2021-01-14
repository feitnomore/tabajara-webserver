/*
 * Tabajara HTTP Server 1.2
 * handler.h -- This file contains the main thread
 *              handler for the connection received.
 * 
 * Marcelo Feitoza Parisi 
 */

void* Handler(void* connection)
{
	/* Retrieve client information */
	struct sockaddr_in client;
	socklen_t addr_size = sizeof(struct sockaddr_in);
	int res = getpeername((int)(intptr_t)connection, (struct sockaddr *)&client, &addr_size);
	char *client_ip = inet_ntoa(client.sin_addr);

	/* Failed to get client ip addr */
	if(res != 0) {
		log_str(ERROR_LOG, "WARNING: Unable to get client IP");
	}

	/* Buffers for I/O, command mapping,
	 * size calculation, string tokenization,
	 * and so on...
	 */
	char received_buf[MAXINPUT];
	char original_buf[MAXINPUT];
	char *http_cmd;
	char empty[]=" ";
	int numbytes, i;
	
	/* Receiving the full client request
	 * at once inside buf
	 */
	if ((numbytes = recv((int)(intptr_t)connection, received_buf, sizeof(received_buf), 0)) == -1) {
		log_str(ERROR_LOG, "ERROR: Unable to read client request");
		exit(1);
	}

	/* Empty request -> QUIT */
	if(strlen(received_buf) < 1) {
		log_str(ERROR_LOG, "Received empty request");
		close((int)(intptr_t)connection);
		return 0;
	}

	/* save buffer before tokenization */
	strcpy(original_buf, received_buf);

	/* Let's split the request in
	 * tokens to handle it 
	 */
	http_cmd = strtok(received_buf, empty);

	/* Conveting command to upper case */
	for(i=0; i < strlen(http_cmd); i++) {
		http_cmd[i] = toupper(http_cmd[i]);
	}

	/* Checking the first token
	 * to see if the verb was GET
	 */
	if(strstr(http_cmd,"GET")) {
		handle_get(connection, original_buf, client_ip);
	}


	/* Checking the first token
	 * to see if the verb was POST
	 */
	else if(strstr(http_cmd, "POST")) {
		handle_post(connection, original_buf, client_ip);		
	}

	/* Checking the first token
	 * to see if the verb was PUT
	 */
	else if(strstr(http_cmd, "PUT")) {
		handle_put(connection, original_buf, client_ip);		
	}
	
	/* Checking the first token
	 * to see if the verb was HEAD
	 */
	else if(strstr(http_cmd,"HEAD")) {
		handle_head(connection, original_buf, client_ip);
	}

	/* Close the socket */
	close((int)(intptr_t)connection);

    return 0;
}
