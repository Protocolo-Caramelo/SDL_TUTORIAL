CC = gcc
CFLAGS =  --std=c99 -Wall -Wextra 
CLIBS = `sdl2-config --libs --cflags` -ggdb3 -lSDL2_image -lm

SRC_C = \
		.
SRC_O = bin
SRC_H = \
		.


SRC_C_PATH = $(foreach \
			 wrd, \
			 $(SRC_C), \
			 $(shell find $(wrd) -type f -name "*.c") \
			 )
SRC_O_PATH = $(SRC_C_PATH:%.c=$(SRC_O)/%.o)
SRC_H_PATH = $(foreach \
			 wrd, \
			 $(SRC_H), \
			 -I $(wrd) \
			 )

EXEC = main

# all:
# 	echo ^$(SRC_C_PATH)$
# 	echo
# 	echo ^$(SRC_O_PATH)$
# 	echo
# 	echo ^$(SRC_H_PATH)$
# 

all: $(EXEC)

$(EXEC): $(SRC_O_PATH)
	$(CC) -o $(EXEC) $(CFLAGS) $(SRC_H_PATH) $^ $(CLIBS)

$(SRC_O_PATH): $(SRC_O)/%.o :%.c
	@mkdir -p $(dir $@)
	$(CC) -c $^ $(CFLAGS) $(SRC_H_PATH) -o $@ $(CLIBS)


clean:
	rm -f $(EXEC)
	rm -rf $(SRC_O)
