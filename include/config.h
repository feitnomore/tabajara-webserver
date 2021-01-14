/*
 * Tabajara HTTP Server 1.2
 * config.h -- This file contains some config
 *             constants for the server.
 * 
 * Marcelo Feitoza Parisi 
 */

/* MYPORT = port in which the
 * http server will listen
 * default: 8080
 */
#define MYPORT "8080" 

/* MYHOST = hostname to be used
 * on response headers and error pages
 * default: localhost
 */
#define MYHOST "localhost"

/* MYDOCS = a.k.a document root
 * Place from where files will be served
 * default: htdocs
 */
#define MYDOCS "htdocs"

/* MAXCON = max number of connections
 * our server socket will handle
 * default: 10
 */
#define MAXCON 10

/* ACCESS_LOG = turns on access logging
 * 0 =off , 1 = on
 * default: 0
 */
#define ACCESS_LOG 1

/* ERROR_LOG = turns on error logging
 * 0 = off , 1 = on
 * default: 0
 */
#define ERROR_LOG 1

/* ACCESS_LOG_STDOUT = Log access to stdout
 * 0 = off , 1 = on
 * default: 0
 */
#define ACCESS_LOG_STDOUT 1

/* ERROR_LOG_STDOUT = Log error to stdout
 * 0 = off , 1 = on
 * default: 0
 */
#define ERROR_LOG_STDOUT 0

/* ACCESS_LOGFILE = acces log
 * filename / location
 * default: logs/access.log
 */
#define ACCESS_LOGFILE "logs/access.log"

/* ERROR_LOGFILE = error log
 * filename / location
 * default: logs/error.log
 */
#define ERROR_LOGFILE "logs/error.log"  
