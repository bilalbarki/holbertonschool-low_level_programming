CFLAGS := -Wall -Werror -Wextra -pedantic
CFILES := op_functions.c get_op_func.c main.c
OFILES := $(patsubst %.c, %.o, $(CFILES))
OUTPUT := 2-calculator

all: 2-calculator

2-calculator: $(OFILES)
	gcc $(CFLAGS) $(OFILES) -o $(OUTPUT)

main.o: main.c
	gcc $(CFLAGS) -c main.c

get_op_func.o: get_op_func.c
	gcc $(CFLAGS) -c get_op_func.c

op_functions.o: op_functions.c
	gcc $(CFLAGS) -c op_functions.c

clean:
	rm -f $(OFILES) $(OUTPUT)
