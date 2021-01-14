/*
 * Tabajara HTTP Server 1.2
 * error.h -- This file contains strings with some
 *            default http error messages.
 * 
 * Marcelo Feitoza Parisi 
 */

/* Templates for Bad Request */
char *br_p1 = "<HTML><HEAD>\n<TITLE>400 Bad Request</TITLE>\n</HEAD><BODY>\n<H1>Bad Request</H1>\nYour browser sent a request that this server could not understand.<P>\nThe request line contained invalid characters following the protocol string.<P>\n<HR>\n<ADDRESS>Tabajara HTTP Server 1.2 at ";
char *br_p2 = " Port ";
char *br_p3 = "</ADDRESS>\n</BODY></HTML>";

/* Templates for Not Found */
char *nf_p1 = "<HTML><HEAD>\n<TITLE>404 Not Found</TITLE>\n</HEAD><BODY>\n<H1>Not Found</H1>\nThe requested URL ";
char *nf_p2 = " was not found on this server.<P>\n<HR>\n<ADDRESS>Tabajara HTTP Server 1.2 at "; 
char *nf_p3 = " Port ";
char *nf_p4 = "</ADDRESS>\n</BODY></HTML>";
