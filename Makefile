# Specify the compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -g

# Source files
SRCS = drum_machine.cpp

# Output executable
TARGET = CMDrum

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

