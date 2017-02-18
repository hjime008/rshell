CC = g++
CFLAGS = -g -Wall -Werror -ansi -pedantic -I.
LFLAGS = -Wall -Werror -I. -lm -o
SRCDIR = src
HEADIR = header
OBJDIR = obj
BINDIR = bin
EXEC = rshell

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(HEADIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

all: $(SOURCES) $(EXEC) move

$(EXEC): $(OBJECTS)
	@$(CC) $(OBJECTS) $(LFLAGS) $(EXEC)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

move:
	mkdir bin && mv $(EXEC) bin
clean:
	rm -f -r $(OBJECTS) bin
