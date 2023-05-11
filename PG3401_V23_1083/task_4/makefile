#MakeFile for TASK 4

INCLDIR = ./include
CC = gcc
CFLAGS = -O2
CFLAGS += -Wno-implicit-function-declaration
CFLAGS += -I$(INCLDIR)
LINKEXTRA = -lpthread
LIBS += -L/home/bruce/Documents/lib -Ipgdbglog

OBJDIR = obj

_DEPS = threads.h
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS = main.o threads.o 
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	@echo "Compiling TASK 4..."
	@$(CC) -c -o $@ $< $(CFLAGS)
		
main: $(OBJDIR)/main.o $(OBJDIR)/threads.o $(DEPS) 
	@gcc -o $@ $^ $(CFLAGS) $(LINKEXTRA)
	@echo "TASK 4 compiled successfully! :D"
		
.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~
