TIMESTAMP := $(shell date +%Y%m%d_%H%M%S)
OUTPUT_IMAGE = test_image_$(TIMESTAMP).png

# Define the compiler and flags
CC = gcc
CFLAGS = -Wall -I./include
LDFLAGS = -lm

# Define the source and object files
SRC = main.c ray.c vec3.c color.c
OBJ = $(SRC:.c=.o)

# Define the target executable
TARGET = main

# Target to build the executable
all: $(TARGET) $(OUTPUT_IMAGE)

# Rule to build the executable
$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

# Rule to compile the main.c file
main.o: main.c ray.h vec3.h color.h
	$(CC) $(CFLAGS) -c main.c

# Rule to compile the ray.c file
ray.o: ray.c ray.h vec3.h
	$(CC) $(CFLAGS) -c ray.c

# Rule to compile the vec3.c file
vec3.o: vec3.c vec3.h
	$(CC) $(CFLAGS) -c vec3.c

# Rule to compile the color.c file
color.o: color.c color.h vec3.h
	$(CC) $(CFLAGS) -c color.c

# Rule to generate the image file by running the executable
$(OUTPUT_IMAGE): $(TARGET)
	@echo "Running the executable..."
	@OUTPUT_IMAGE=$(OUTPUT_IMAGE) ./$(TARGET)
	@echo "Checking if image file is created..."
	@ls -l $(OUTPUT_IMAGE)

# Clean up the generated files
clean:
	rm -f $(TARGET) $(OBJ) test_image_*.png

.PHONY: all clean
