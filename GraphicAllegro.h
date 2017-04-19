#ifndef GRAPHICALLEGRO_H_INCLUDED
#define GRAPHICALLEGRO_H_INCLUDED

#include <string>

#include "Tablier.h"

namespace graphique
{
	void demarer_allegro();

	void afficherTablier(Tablier tab);

	void afficherMessage(std::string message);

	void selectionCase(int &x, int &y);

	void surprise();
}

#endif // GRAPHICALLEGRO_H_INCLUDED
