#ifndef ARBRE_H_INCLUDED
#define ARBRE_H_INCLUDED

#include "Noeud.h"

class Arbre
{
private:
	Noeud m_firstNoeud; // Noeud de départ de l'arbre, étant l'échequier actuel
	std::vector<Noeud  *> m_tabNoeuds[PROFONDEUR]; // Tableau stockant les pointeurs sur les noeuds par niveau de profondeur les noeuds par niveau de profondeur

public:
	// Constructeur & Destructeur
	Arbre(Tablier _tab);
	~Arbre();

	// Methodes
	void trouverMeilleurCoup(int &x, int &y); // Trouve en fonction de la profondeur le meilleur coup que la machine peut jouer
	void tracerArbre(); // On trace toute les possibilités
	void remonterArbre(); // On remonte l'arbre des racines en sélectionnant le Min ou Max
};

#endif // ARBRE_H_INCLUDED
