main: main.cpp Object3D.cpp Game.cpp
	g++ -std=c++17 -Wall main.cpp Object3D.cpp Game.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f main