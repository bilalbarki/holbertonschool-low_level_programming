CC = gcc
CFLAGS = -Wall -pedantic -Werror -Wextra
INCLUDES = functions.h
SOURCES =  6-string_split.c environment.c main.c print_char.c read_line.c shell_internals2.c strings2.c built_in.c print_free_2d.c search_path.c shell_internals.c strings.c
OBJECTS = $(SOURCES:.c=.o)
OUTPUT = shell.out

all: $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) -o $(OUTPUT)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(OUTPUT)

re:
	rm -f $(OBJECTS) $(OUTPUT)
	$(MAKE)
