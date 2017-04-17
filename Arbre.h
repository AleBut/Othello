#ifndef ARBRE_H_INCLUDED
#define ARBRE_H_INCLUDED

#include "Noeud.h"

class Arbre
{
private:
	Noeud m_firstNoeud; // Noeud de d�part de l'arbre, �tant l'�chequier actuel
	std::vector<Noeud  *> m_tabNoeuds[PROFONDEUR]; // Tableau stockant les pointeurs sur les noeuds par niveau de profondeur les noeuds par niveau de profondeur

public:
	// Constructeur & Destructeur
	Arbre(Tablier _tab);
	~Arbre();

	// Methodes
	void trouverMeilleurCoup(int &x, int &y); // Trouve en fonction de la profondeur le meilleur coup que la machine peut jouer
	void tracerArbre(); // On trace toute les possibilit�s
	void remonterArbre(); // On remonte l'arbre des racines en s�lectionnant le Min ou Max
};

#endif // ARBRE_H_INCLUDED
