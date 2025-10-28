all: main

main: main.cpp Graph.cpp Network.cpp User.cpp registry.cpp
	g++ main.cpp Graph.cpp Network.cpp User.cpp registry.cpp -o main

run:
	./main

clean:
	del main.exe
