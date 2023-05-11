#MakeFile for TASK 5

INCLDIR = ./include
CC = gcc
CFLAGS = -O2
CFLAGS += -I$(INCLDIR)
LIBS += -L/home/bruce/Documents/lib -Ipgdbglog

OBJDIR = obj

_DEPS = serverclient.h
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS = main.o serverclient.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	@echo "Compiling TASK 5..."
	@$(CC) -c -o $@ $< $(CFLAGS)
		
main: $(OBJDIR)/main.o $(OBJDIR)/serverclient.o $(DEPS) 
	@gcc -o $@ $^ $(CFLAGS) $(LIBS)
	@echo "TASK 5 compiled successfully! :D"
		
.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~
