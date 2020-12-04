CXX = g++
INCLUDES = -I "./"
CXXFLAGS = -g `pkg-config --cflags --libs opencv`
OBJECTS = read_image.o
OBJECTS += fractal_dimension.o
SANITFLAGS = -fsanitize=address


all: sanitize


%.o: %.cpp %.h
	$(CXX) $(INCLUDES) -c $< -o $@


sanitize: $(OBJECTS)
	$(CXX) $(INCLUDES) $(CXXFLAGS) $(SANITFLAGS) $^ -o x.read_image
	@echo "END RUN WITH SANITIZERS"

run: script.sh sanitize
	bash $<

erase:
	rm -f x* Data_FD/*.csv *~

clean:	erase
	rm -f *.o
