all: main

main: main.cpp Graph.cpp Network.cpp User.cpp registry.cpp
	g++ -std=c++17 main.cpp Source/Graph.cpp Source/Network.cpp Source/User.cpp Source/registry.cpp -Iinclude -o main

run:
	./main

clean:
	del main.exe

