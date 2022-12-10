#include "game.h"

//LENGTH OF VECTOR: |V| = sqrt(V.x^2 + V.y^2)
//NORMALIZE VECTOR: U = V / |V|

int main() {
	game game(1200, 1000, "bebra");
	game.run();
	return 0;
}