CFLAGS := -Wall -pedantic -Werror -Wextra
HEADER := holbertonschool.h
SRCDIR := src
CFILES := 0-absolute.c 1-cap_string.c 2-square_root.c 4-positive_or_not.c 0-contact_strings.c 1-nconcat_strings.c 2-string_copy.c 4-reverse_string.c 0-first_digit.c 1-power.c 2-str_len.c 4-strings_compare.c 0-lowercase.c 1-swap_int.c 3-is_prime_number.c 5-reverse_array.c 0-print_number.c 1-uppercase.c 3-print_string.c 5-string_to_integer.c 0-uppercase_string.c 2-print_array.c 3-string_ncopy.c
SOURCES := $(foreach file, $(CFILES), $(SRCDIR)/$(file)) 
OBJECTS := $(patsubst %.c, %.o, $(SOURCES))

all: libholberton.a

libholberton.a: $(OBJECTS)
	ar -rcs libholberton.a $(OBJECTS)

src/%.o:src/%.c
	gcc $(CFLAGS) -c $< -o $@

clean: 
	rm -f $(OBJECTS) libholberton.a

re:
	make clean
	make all
