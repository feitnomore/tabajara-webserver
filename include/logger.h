/*
 * Tabajara HTTP Server 1.2
 * logget.h -- This file contains some helper 
 *             functions for logging.
 * 
 * Marcelo Feitoza Parisi 
 */

/* For error logging */
void log_error(int logtype, char *theirip, char *command, char *request, int response, int size) {
	FILE *LOG;

	/* Getting Current Time */
	time_t now;
	time(&now);

	char *timestamp = ctime(&now);

	if ( ERROR_LOG == 1 ) {
		if ((LOG = fopen(ERROR_LOGFILE, "a")) == NULL) {
			printf("ERROR: Unable to open error log file.\n");
		} else {
			fprintf(LOG, "[%s] - %s - %s %s - %d %d\n", strtok(timestamp, "\n"), theirip, command, request, response, size);
			fclose(LOG);
		}
		if (ERROR_LOG_STDOUT == 1) {
			printf("[%s] - %s - %s %s - %d %d\n", strtok(timestamp, "\n"), theirip, command, request, response, size);
			fflush(stdout);
		}
	}
}

/* For access logging */	
void log_access(int logtype, char *theirip, char *command, char *request, int response, int size) {
	FILE *LOG;

	/* Getting Current Time */
	time_t now;
	time(&now);

	char *timestamp = ctime(&now);

	if (ACCESS_LOG == 1) {
		if ((LOG = fopen(ACCESS_LOGFILE, "a")) == NULL) {
			printf("ERROR: Unable to open access log file.\n");
		} else {
			fprintf(LOG, "[%s] - %s - %s %s - %d %d\n", strtok(timestamp, "\n"), theirip, command, request, response, size);
			fclose(LOG);
		}
		if (ACCESS_LOG_STDOUT == 1) {
			printf("[%s] - %s - %s %s - %d %d\n", strtok(timestamp, "\n"), theirip, command, request, response, size);
			fflush(stdout);
		}
	}
}
	
void log_debug(char *msg) {
	/* SHOULD GO TO SCREEN: TBD */
}

/* For error logging: STRING */
void log_str(int logtype, char *msg) {
	FILE *LOG;

	/* Getting Current Time */
	time_t now;
	time(&now);

	char *timestamp = ctime(&now);

	if ( ERROR_LOG == 1 ) {
		if ((LOG = fopen(ERROR_LOGFILE, "a")) == NULL) {
			printf("ERROR: Unable to open error log file.\n");
		} else {
			fprintf(LOG, "[%s] %s\n", strtok(timestamp, "\n"), msg);
			fclose(LOG);
		}
		if (ERROR_LOG_STDOUT == 1) {
			printf("[%s] %s\n", strtok(timestamp, "\n"), msg);
			fflush(stdout);
		}
	}
}
