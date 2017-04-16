#include "Noeud.h"


// Constructeur & Destructeur
Noeud::Noeud(Tablier _tab)
	:m_antecedent(nullptr), m_x(0), m_y(0), m_tab(_tab), m_profondeur(0), m_meilleurNombreDePion(0)
{
	// Nothing
}

Noeud::Noeud(Noeud * _antecedent, Tablier _tab, int _x, int _y)
	:m_antecedent(_antecedent), m_x(_x), m_y(_y), m_tab(_tab)
{
	m_tab.poserPion(_x, _y); // On pose le pion joué précédemment
	m_tab.avancerTour(); // Aux adversaires de jouer
	m_profondeur = _antecedent->m_profondeur + 1; // On s'enfonce dans la profondeur
	m_meilleurNombreDePion = m_tab.nombreDePion(BLANC); // On note le score pour les blancs (la machine)
}

Noeud::~Noeud()
{

}

// Méthodes
Noeud * Noeud::descendre(int x, int y)
{
	m_successeur.push_back(new Noeud(this, m_tab, x, y));
	return m_successeur.back();
}
