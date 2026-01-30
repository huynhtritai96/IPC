CC      := gcc
CFLAGS  := -Wall -Wextra -O2
TARGET  := pipe_demo
SRC     := pipe_demo.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

pipe_gpt: pipe_gpt.c
	$(CC) $(CFLAGS) -o pipe_gpt pipe_gpt.c

clean:
	rm -f $(TARGET)

# make        # builds pipe_demo
# ./pipe_demo
# make clean  # removes the binary