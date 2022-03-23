main: main.cpp src/pipeline.cpp src/pipeline.h src/mesh.cpp src/mesh.h src/texture.cpp src/texture.h src/loader/glad.c
	g++ main.cpp src/pipeline.cpp src/mesh.cpp src/texture.cpp src/loader/glad.c -o main -lSDL2

clean:
	rm -f main *.o
