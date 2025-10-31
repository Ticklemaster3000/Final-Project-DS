all: main

main: main.cpp Source/Graph.cpp Source/Network.cpp Source/User.cpp Source/Registry.cpp Source/Location.cpp
	g++ -std=c++17 main.cpp Source/Graph.cpp Source/Network.cpp Source/User.cpp Source/Registry.cpp Source/Location.cpp -Iinclude -o main

run:
	./main

clean:
	del main.exe

