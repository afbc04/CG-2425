CFLAGS=-Wall -Iinclude -fno-stack-protector -g -O2

main: generate engine

generate: bin/Triangles.o bin/Ficheiro.o src/gerador/gerador.cpp
	g++ $(LDFLAGS) $(CFLAGS) $^ -o generator

engine: bin/Triangles.o bin/Ficheiro.o src/engine/engine.cpp
	g++ $(LDFLAGS) $(CFLAGS) $^ -lGL -lGLU -lglut -o engine

bin/Triangles.o: src/figuras/Triangles.cpp
	g++ $(LDFLAGS) $(CFLAGS) $^ -o bin/Triangles.o -c

bin/Ficheiro.o: src/ficheiro3d/Ficheiro.cpp
	g++ $(LDFLAGS) $(CFLAGS) $^ -o bin/Ficheiro.o -c

clean:
	rm engine generator bin/*.o