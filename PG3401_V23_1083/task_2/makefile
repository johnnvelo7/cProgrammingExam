#MakeFile Template

INCLDIR = ./include
CC = gcc
CFLAGS = -O2
CFLAGS += -I$(INCLDIR)

OBJDIR = obj

_DEPS = main.h eksamen_v23_oppgave2_fib.h eksamen_v23_oppgave2_abun.h eksamen_v23_oppgave2_cube.h eksamen_v23_oppgave2_def.h eksamen_v23_oppgave2_kvad.h eksamen_v23_oppgave2_odd.h eksamen_v23_oppgave2_perf.h eksamen_v23_oppgave2_prim.h

DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS = main.o eksamen_v23_oppgave2_fib.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	@echo "Compiling TASK 2..."
	@$(CC) -c -o $@ $< $(CFLAGS)
	
main: $(OBJDIR)/main.o $(OBJDIR)/eksamen_v23_oppgave2_fib.o $(OBJDIR)/eksamen_v23_oppgave2_abun.o $(OBJDIR)/eksamen_v23_oppgave2_cube.o $(OBJDIR)/eksamen_v23_oppgave2_def.o $(OBJDIR)/eksamen_v23_oppgave2_kvad.o $(OBJDIR)/eksamen_v23_oppgave2_odd.o $(OBJDIR)/eksamen_v23_oppgave2_perf.o $(OBJDIR)/eksamen_v23_oppgave2_prim.o $(DEPS) 
	@gcc -o $@ $^ $(CFLAGS) -lm $(LIBS)
	@echo "TASK 2 compiled successfully! :D"	
		
.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~
