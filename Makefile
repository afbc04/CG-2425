CFLAGS=-Wall -Iinclude -fno-stack-protector -g -O2

generate: src/figuras/Triangles.o src/gerador/gerador.cpp
	g++ $(LDFLAGS) $(CFLAGS) $^

src/figuras/Triangles.o: src/figuras/Triangles.cpp
	g++ $(LDFLAGS) $(CFLAGS) $^ -o Triangles.o