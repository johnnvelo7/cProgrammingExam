#MakeFile Template

INCLDIR = ./include
CC = gcc
CFLAGS = -O2
CFLAGS += -I$(INCLDIR)
LIBS += -L/home/bruce/Documents/lib -Ipgdbglog

OBJDIR = obj

_DEPS = beautifier.h
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS = main.o beautifier.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	@echo "Compiling TASK 6..."
	@$(CC) -c -o $@ $< $(CFLAGS)
		
main: $(OBJDIR)/main.o $(OBJDIR)/beautifier.o $(DEPS) 
	@gcc -o $@ $^ $(CFLAGS) $(LIBS)
	@echo "TASK 6 compiled successfully! :D"
		
.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~
