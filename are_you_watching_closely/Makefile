CFLAGS := -Wall -pedantic -Werror -Wextra
HEADER := my_functions.h
SRCDIR := src
CFILES :=  base_convert.c flags.c printf.c src decimal.c hexa.c octal.c printing.c unsigned.c
SOURCES := $(foreach file, $(CFILES), $(SRCDIR)/$(file))
OBJECTS := $(patsubst %.c, %.o, $(SOURCES))

all: libholberton.a

libholberton.a: $(OBJECTS)
	ar -rc libprintf.a $(OBJECTS)

$(OBJECTS):$(SOURCES)
	gcc $(CFLAGS) -Iinc -c $< -o $@

clean:
	rm -f $(OBJECTS) libprintf.a

re:
	rm -f $(OBJECTS)
	make $(OBJECTS)
