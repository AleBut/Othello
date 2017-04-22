/*!
* \file Noeud.cpp
* \brief Description de la clase Noeud
*/

#include "Noeud.h"


/// Constructeur & Destructeur
Noeud::Noeud(Tablier _tab)
	:m_antecedent(nullptr), m_x(0), m_y(0), m_tab(_tab), m_meilleurNombreDePion(INFINI), m_couleur(COLOR_BLUE)
{
	// Nothing
}

Noeud::Noeud(Noeud * _antecedent, int _x, int _y)
	:m_antecedent(_antecedent), m_x(_x), m_y(_y), m_tab(_antecedent->m_tab), m_meilleurNombreDePion(INFINI)
{
	m_tab.poserPion(_x, _y); // On pose le pion joue precedemment
	m_tab.avancerTour(); // Aux adversaires de jouer
}

Noeud::~Noeud()
{

}



/// Methodes
Noeud * Noeud::descendre(int x, int y)
{
	return new Noeud(this, x, y);
}
