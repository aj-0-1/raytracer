# Target to build the executable and generate the image
all: image.ppm

# Rule to compile the main.cc file
main: main.cc
	g++ -o main main.cc

# Rule to run the executable and redirect output to image.ppm
image.ppm: main
	./main > image.ppm

# Clean up the generated files
clean:
	rm -f main image.ppm
