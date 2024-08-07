# Specify the compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -g

# Source files
SRCS = main.cpp

# Output executable
TARGET = MyProject

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

