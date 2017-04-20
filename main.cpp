#include <allegro.h>

#include "Game.h"
#include "GraphicAllegro.h"

int main(int argc, char *argv[])
{
	// Allegro
	if(GRAPH) graphique::demarer_allegro();

	Game g1;
	g1.lancerJeux();

    return 0;
}
END_OF_MAIN();
