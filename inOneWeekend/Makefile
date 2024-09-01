TIMESTAMP := $(shell date +%Y%m%d_%H%M%S)
OUTPUT_IMAGE = test_image_$(TIMESTAMP).png

# Define the compiler and flags
CC = gcc
FORMAT = clang-format
STYLE = -style=Google -extra-credits=false
LDFLAGS = -lm

# Define the source and object files
SRC = main.c ray.c vec3.c color.c hittable.c sphere.c hittable_list.c interval.c camera.c
OBJ = $(SRC:.c=.o)

# Define the target executable
TARGET = main

# Target to build the executable
all: $(TARGET) $(OUTPUT_IMAGE)
format:
	@$(FORMAT) -i main.c ray.c vec3.c color.c hittable.c sphere.c hittable_list.c interval.c camera.c ray.h vec3.h color.h hittable.h sphere.h hittable_list.h interval.h camera.h

# Rule to build the executable
$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

# Generic rule for object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Dependencies
main.o: main.c rtweekend.h sphere.h hittable_list.h camera.h
ray.o: ray.c ray.h vec3.h
vec3.o: vec3.c vec3.h
color.o: color.c color.h vec3.h
hittable.o: hittable.c hittable.h ray.h
sphere.o: sphere.c sphere.h hittable.h vec3.h
hittable_list.o: hittable_list.c hittable_list.h hittable.h
interval.o: interval.c interval.h rtweekend.h

# Rule to generate the image file by running the executable
$(OUTPUT_IMAGE): $(TARGET)
	@echo "Running the executable..."
	@OUTPUT_IMAGE=$(OUTPUT_IMAGE) ./$(TARGET)
	@echo "Checking if image file is created..."
	@ls -l $(OUTPUT_IMAGE)

# Clean up the generated files
clean:
	rm -f $(TARGET) $(OBJ) test_image_*.png

.PHONY: all clean format
