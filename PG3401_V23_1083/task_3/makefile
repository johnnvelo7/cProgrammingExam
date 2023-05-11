#MakeFile for TASK 3

INCLDIR = ./include
CC = gcc
CFLAGS = -O2
CFLAGS += -I$(INCLDIR)
LIBS += -L/home/bruce/Documents/lib -Ipgdbglog

OBJDIR = obj

_DEPS = database.h inputvalidation.h
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS = main.o database.o inputvalidation.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	@echo "Compiling TASK 3..."	
	@$(CC) -c -o $@ $< $(CFLAGS)
		
main: $(OBJDIR)/main.o $(OBJDIR)/database.o $(OBJDIR)/inputvalidation.o $(DEPS) 
	@gcc -o $@ $^ $(CFLAGS) $(LIBS)
	@echo "TASK 3 compiled successfully! :D"	
		
.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~
