CFLAGS := -Wall -Werror -Wextra -pedantic
CFILES := main.c print_char.c
OFILES := $(patsubst %.c,%.o,$(CFILES))
OUTPUT := 2-print_permissions

all: $(OUTPUT)

$(OUTPUT): $(OFILES)
	gcc $(CFLAGS) $(OFILES) -o $(OUTPUT)

main.o: main.c
	gcc $(CFLAGS) -c main.c

print_char.o: print_char.c
	gcc $(CFLAGS) -c print_char.c

clean:
	rm -f $(OFILES) $(OUTPUT)
