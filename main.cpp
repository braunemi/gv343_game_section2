#include "SFML/Graphics.hpp"
#include "Intro.hpp"
#include "Game.hpp"

int main(int argc, char** argv){
	Game g;
	while(true){
		g.start();
		g.run();
	}
}
