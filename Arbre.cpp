/*!
* \file Arbre.cpp
* \brief Description de la classe Arbre
*/

#include "Arbre.h"
#include "console.h"

#include <iostream>
#include <windows.h>


/// Constructeur & Destructeur
Arbre::Arbre(Tablier _tab, int _profondeur)
	:m_firstNoeud(_tab), m_profondeur(_profondeur)
{

}

Arbre::~Arbre()
{
	// Liberation de la memoire
	for(int profondeur=1; profondeur < m_profondeur; profondeur++)
	{
		for(auto elem : m_tabNoeuds[profondeur])
		{
			delete elem;
		}
	}
}



/// Methodes
void Arbre::trouverMeilleurCoup(int &xDonne, int &yDonne)
{
	/// Traitement:
	this->tracerArbre();
	this->remonterArbre();

	// On choisit au niveau de profondeur 1 quel coup jouer
	for(auto elem : m_tabNoeuds[1]) // Le maximum ayant deja ete determine, on regarde a quel X/Y joue il correspond
	{
		if(elem->m_meilleurNombreDePion == elem->m_antecedent->m_meilleurNombreDePion) {
			xDonne = elem->m_x;
			yDonne = elem->m_y;
			return;
		}
	}
}

void Arbre::tracerArbre()
{
	/// Traitement
	// Initialisation du niveau de profondeur 0
	m_tabNoeuds[0].push_back(&m_firstNoeud);

	// Autre niveau: On developpe l'arbre en largeur
	for(int profondeur=0; profondeur < m_profondeur-1; profondeur++) // Jusqu'au niveau desire
	{
		for(auto elem : m_tabNoeuds[profondeur]) // On veut traiter tout les noeuds d'un meme niveau
		{
			for(int y=0; y<TAB_TAILLE; y++) // Recherche de toute les possibilites de coordonnees
			{
				for(int x=0; x<TAB_TAILLE; x++)
				{
					if(elem->m_tab.selectionValide(x, y))// Si une selection est valide, alors
						m_tabNoeuds[profondeur+1].push_back(elem->descendre(x, y)); // On ajoute le noeud a l'arbre et au tableau
				}
			}
		}
	}

	// On complete les racines de l'arbre par la valeur du meilleur nombre de coup
	for(auto elem : m_tabNoeuds[m_profondeur-1])
	{
		elem->m_meilleurNombreDePion = elem->m_tab.nombreDePion(BLANC);
	}
}

void Arbre::remonterArbre()
{
	/// Traitement
	for(int profondeur = m_profondeur-1; profondeur > 0; profondeur--)
	{
		for(auto elem : m_tabNoeuds[profondeur])
		{
			// m_meilleurNombreDePion prend la valeur minimum si pion precedent est noir (joueur) ou prend n'importe quelle valeur si il n'a pas ete compare
			if(((elem->m_antecedent->m_tab.m_tourDeJouer == NOIR)	&& (elem->m_meilleurNombreDePion < elem->m_antecedent->m_meilleurNombreDePion)) || (elem->m_antecedent->m_meilleurNombreDePion == INFINI))
				elem->m_antecedent->m_meilleurNombreDePion = elem->m_meilleurNombreDePion;

			// m_meilleurNombreDePion prend la valeur maximum si pion precedent est blanc (joueur) ou prend n'importe quelle valeur si il n'a pas ete compare
			if(((elem->m_antecedent->m_tab.m_tourDeJouer == BLANC)	&& (elem->m_meilleurNombreDePion > elem->m_antecedent->m_meilleurNombreDePion)) || (elem->m_antecedent->m_meilleurNombreDePion == INFINI))
				elem->m_antecedent->m_meilleurNombreDePion = elem->m_meilleurNombreDePion;
		}
	}
}

void Arbre::dessinerConsole()
{
	/// Donnees
	int xInitial = X0, yInitial = Y0 + ESPACEMENT_Y*TAB_TAILLE;
	int largeur;
	Color couleurUtilisee;
	Console * pConsole = Console::getInstance();

	pConsole->setColor(COLOR_BLACK);
	if(GRAPH) { yInitial = Y0; system("cls"); }

	/// Traitement
	for(int profondeur = 0; profondeur < m_profondeur; profondeur++) // On dessine toute la profondeur d l'arbre
	{
		largeur = 0;
		couleurUtilisee = COLOR_GREEN;
		for(auto elem : m_tabNoeuds[profondeur]) // On dessine tout les noeuds sur un même niveau
		{
			pConsole->gotoLigCol((xInitial + 2*profondeur*ESPACEMENT_X), (yInitial + largeur));

			if(elem->m_antecedent == nullptr) // Si on a selectionne le noeud inital
				pConsole->setColor(COLOR_BLACK, elem->m_couleur);
			else {
				pConsole->setColor(COLOR_BLACK, elem->m_antecedent->m_couleur); // Si c'est un noeud banal
				couleurUtilisee = elem->m_couleur = pConsole->nextColor(couleurUtilisee);
			}

			std::cout << elem->m_x << ":" << elem->m_y; // Affichage du coup joue en X & Y
			pConsole->setColor(COLOR_BLACK);
			std::cout << "-";
			pConsole->setColor(COLOR_BLACK, elem->m_couleur);
			std::cout << elem->m_meilleurNombreDePion; // Affichage du meilleurNombreDePion

			largeur++;
		}
	}
}
