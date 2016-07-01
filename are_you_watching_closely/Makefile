CFLAGS := -Wall -pedantic -Werror -Wextra -Wno-format
SOURCES := base_convert.c flags.c printf.c decimal.c hexa.c octal.c printing.c unsigned.c 
OBJECTS := $(patsubst %.c, %.o, $(SOURCES))
OUTPUT := libprintf.a

all: $(OUTPUT)

libprintf.a: $(OBJECTS)
	ar rcs $(OUTPUT) $(OBJECTS)

.o:.c
	gcc $(CFLAGS) -c $< -o $@

clean: 
	rm -f $(OBJECTS) $(OUTPUT)

re: clean all
