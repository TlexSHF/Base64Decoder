#MAKEFILE Oppg 5 FILHÅNDTERING

#Extendable flags
INCLDIR = ./include
CC = gcc
CFLAGS = -O2
CFLAGS += -I$(INCLDIR)
CFLAGS += -lm

OBJDIR = obj

#All header files
_DEPS = base64decoder.h
DEPS = $(patsubst %, $(INCLDIR)/%, $(_DEPS))

#All object/source files
_OBJS = main.o base64decoder.o
OBJS = $(patsubst %, $(OBJDIR)/%, $(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

#NameOfProject:
Base64Decoder: $(OBJS)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~
