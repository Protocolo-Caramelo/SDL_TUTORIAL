CC = gcc
CFLAGS =  --std=c99 -Wall -Wextra 
CLIBS = `sdl2-config --libs --cflags` -ggdb3 -lSDL2_image -lm

SRC_C = \
		.
SRC_H = \
		.


SRC_C_PATH = $(foreach \
			 wrd, \
			 $(SRC_C), \
			 $(shell find $(wrd) -type f -name "*.c") \
			 )
SRC_O_PATH = $(SRC_C_PATH:%.c=%.o)
SRC_H_PATH = $(foreach \
			 wrd, \
			 $(SRC_H), \
			 -I $(wrd) \
			 )

EXEC = main

# all:
# 	echo $(SRC_C_PATH)
# 	echo $(SRC_O_PATH)
# 	echo $(SRC_H_PATH)
# 

all: $(EXEC)

$(EXEC): $(SRC_O_PATH)
	$(CC) -o $(EXEC) $(CFLAGS) $(SRC_H_PATH) $^ $(CLIBS)

$(SRC_O_PATH): %.o: %.c
	$(CC) -c $^ $(CFLAGS) $(SRC_H_PATH) -o $@ $(CLIBS)

clean:
	rm -f $(SRC_O_PATH) $(EXEC)
