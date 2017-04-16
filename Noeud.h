#ifndef NOEUD_H_INCLUDED
#define NOEUD_H_INCLUDED

#include <vector>

#include "Tablier.h"

class Noeud
{
public:
	Noeud * m_antecedent; // Noeud pr�c�dent
	std::vector<Noeud *> m_successeur;
	Tablier m_tab;

	int m_x, m_y; // Coo du pion jou�
	int m_profondeur; // Profondeur: impaire => Le joueur adverse joue, paire => L'IA joue
	int m_meilleurNombreDePion; // Permet de comparer la meilleure "option" de jouer rapportant le plus de point


	// Constructeur & Destructeur
	Noeud(Tablier _tab); // Constructeur du 1er noeud
	Noeud(Noeud * _antecedent, Tablier _tab, int _x, int _y); // Constructeur des autres noeuds descendant du 1er
	~Noeud();

	// M�thode
	Noeud * descendre(int x, int y); // Cr�er un noeud fille � partir d'un noeud m�re et des coo du nouveau pion pos�
};

#endif // NOEUD_H_INCLUDED
