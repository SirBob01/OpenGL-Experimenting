main: src/main.cpp src/pipeline.cpp src/loader/glad.c
	g++ src/main.cpp src/pipeline.cpp src/loader/glad.c -o main -lSDL2

clean:
	rm -f main *.o