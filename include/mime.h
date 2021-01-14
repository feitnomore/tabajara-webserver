/*
 * Tabajara HTTP Server 1.2
 * mime.h -- This file contains a function that maps the
 *           mime-type according to file extension.
 * 
 * Marcelo Feitoza Parisi
 */

char *find_mime(char *s) {
	char *mime;
	char dot[] = ".";
	char *extension;
	int i;
	
	extension = strtok(s, dot);
	
	/* Getting the extension itself */
	for(i=0; i < 1; i++) {
		extension = strtok(NULL, dot);
	}
	
	/* Conveting file extension to lower case */
	for(i=0; i < strlen(extension); i++) {
		extension[i] = tolower(extension[i]);
	}

	if(strstr(extension, "htm") || strstr(extension, "html")) {
		mime = "text/html";
	}
	else if(strstr(extension, "exe")) {
		mime = "application/x-dosexec";
	}
	else if(strstr(extension, "mp3") || strstr(extension, "m3a") || strstr(extension, "m2a") || strstr(extension, "mpga")) {
		mime = "audio/mpeg";
	}
	else if(strstr(extension, "wav")) {
		mime = "audio/x-wav";
	}
	else if(strstr(extension, "png")) {
		mime = "image/png";
	}
	else if(strstr(extension, "jpg") || strstr(extension, "jpeg") || strstr(extension, "jpe")) {
		mime = "image/jpeg";
	}
	else if(strstr(extension, "gif")) {
		mime = "image/gif";
	}
	else if(strstr(extension, "json")) {
		mime = "application/json";
	}
	else if(strstr(extension, "xml")) {
		mime = "application/xml";
	}
	else if(strstr(extension, "txt")) {
		mime = "text/plain";
	}
	else if(strstr(extension, "css")) {
		mime = "text/css";
	}
	else if(strstr(extension, "csv")) {
		mime = "text/csv";
	}
	else if(strstr(extension, "js")) {
		mime = "application/javascript";
	}
	else if(strstr(extension, "pdf")) {
		mime = "application/pdf";
	}
	else {
		mime = "invalid/wrong";
	}
	
	return mime;
}
