CC=gcc
FLAGS=-lpthread -static -ggdb -Wall
OUTPUT=httpd
OUTDIR=bin
LOGDIR=logs

All : httpd

httpd : httpd.c
	rm -rf $(OUTDIR)/$(OUTPUT)
	rm -rf $(LOGDIR)/*.log
	mkdir -p $(OUTDIR)
	mkdir -p $(LOGDIR)
	touch $(LOGDIR)/error.log
	touch $(LOGDIR)/access.log
	$(CC) -o $(OUTDIR)/$(OUTPUT) httpd.c $(FLAGS)

clean : 
	rm -rf $(OUTDIR)/$(OUTPUT)
	rm -rf $(LOGDIR)/*.log

