yourcode.out: helper.o resources.o server.cpp
	g++ server.cpp helper.o resources.o -pthread -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -Wl,-rpath="/usr/lib/x86_64-linux-gnu" -o server.o 

helper.o: helper.cpp
	g++ -c helper.cpp

resource.o: resource.cpp
	g++ -c resource.cpp
