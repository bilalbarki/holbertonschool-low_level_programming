CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic
SOURCES = cross.c print_char.c string_to_int.c
OBJECTS = $(SOURCES:.c=.o)
OUTPUT = cross

all: $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(OUTPUT)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(OUTPUT)

re:
	rm -f $(OBJECTS) $(OUTPUT)
	$(MAKE)
