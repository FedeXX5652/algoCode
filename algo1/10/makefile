EJECUTABLE=read_file
FLAGS=-Wall -Werror -std=c99 -Wconversion
FILE_CARS=cars.csv
CONFIG=config

compile:
	gcc *.c -o ${EJECUTABLE}
compile-flags:
	gcc *.c -o ${EJECUTABLE} ${FLAGS}
run:
	./${EJECUTABLE} ${FILE_CARS} ${CONFIG}
clean:
	rm -f ${EJECUTABLE}
all: clean compile compile-flags run