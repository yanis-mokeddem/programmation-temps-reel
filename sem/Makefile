#Makefile cree par Vincent Boyer
#Septembre 2015

#definition des commandes
CC = gcc
RM = rm -f
TAR = tar
MKDIR = mkdir
CHMOD = chmod
CP = rsync -R

#options du compilateur
CFLAGS = 
LDFLAGS = -lpthread

#fichiers et dossiers
PROGNAME = sem
SRC = $(wildcard *.c)
HEADERS= thread.h
OBJS = $(SRC:.c=.o)

PACKAGE=$(PROGNAME)
VERSION = 0.1
distdir = $(PACKAGE)-$(VERSION)
DISTFILES = $(SRC) Makefile $(HEADERS) 

all: $(PROGNAME)

$(PROGNAME): $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) $(PROGNAME) $(OBJS) *~ $(distdir).tgz


dist: distdir
	$(CHMOD) -R a+r $(distdir)
	$(TAR) zcvf $(distdir).tgz $(distdir)
	$(RM) -r $(distdir)

distdir: $(DISTFILES)
	$(RM) -r $(distdir)
	$(MKDIR) $(distdir)
	$(CHMOD) 777 $(distdir)
	$(CP) $(DISTFILES) $(distdir)
