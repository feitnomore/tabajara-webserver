/*
 * Tabajara HTTP Server 1.2
 * header.h -- This file contains the function responsible
 *             for the http response header creation.
 * 
 * Marcelo Feitoza Parisi 
 */

char *generate_response_header(int response_code, char *last_modif, char *content_length, char *content_type)
{
	/* String to hold our response headers */
	char *response_header = malloc(sizeof(char)*99999);
	strcpy(response_header,"");
	
	/* Getting Current time */
	time_t now;
	time(&now);

	/*
	 * HTTP Headers
	 */
	char http_ok[] = "HTTP/1.1 200 OK";
	char http_nf[] = "HTTP/1.1 404 Not Found";
	char http_br[] = "HTTP/1.1 400 Bad Request";
	char http_connection[] = "Connection: close";
	char http_date[] = "Date: ";
	char *http_date_now= ctime(&now);
	char http_server[] = "Server: Tabajara HTTP Server 1.2";
	char http_last_modified[] = "Last-Modified: ";
	char http_content_length[] = "Content-Lenght: ";
	char http_content_type[] = "Content-Type: ";
	char newline[]="\n";

	/*
	 * Checking the response code
	 */
	switch(response_code) {
		case 200:
			strncat(response_header, http_ok, 15);
			break;
		case 404:
			strncat(response_header, http_nf, 22);
			break;
		case 400:
			strncat(response_header, http_br, 24);
			break;
		default:
			strncat(response_header, http_br, 24);
	}

	strcat(response_header, newline);

	/* Connection Header */
	strncat(response_header, http_connection, 17);
	strcat(response_header, newline);

	/* Date Header */
	strncat(response_header, http_date, 6);
	strcat(response_header, http_date_now);
	
	/* Server Header */
	strncat(response_header, http_server, 28);
	strcat(response_header, newline);

	/* Last-Modified Header */
	strncat(response_header, http_last_modified, 15);
	strcat(response_header, last_modif);
	
	/* Content-Length Header */
	strncat(response_header, http_content_length, 16);
	strcat(response_header, content_length);
	strcat(response_header, newline);

	/* Content-Type Header */
	strncat(response_header, http_content_type, 14);
	strcat(response_header, content_type);
	strcat(response_header, newline);

	/* New line to separate the payload from Headers */
	strcat(response_header, newline);

	return response_header;
}
