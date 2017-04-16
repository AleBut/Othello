#include "Arbre.h"

#include <iostream>
// Constructeur & Destructeur
Arbre::Arbre(Tablier _tab)
	:m_firstNoeud(_tab)
{

}

Arbre::~Arbre()
{
	// Libération de la mémoire
	for(int profondeur=1; profondeur < PROFONDEUR; profondeur++)
	{
		for(auto elem : m_tabNoeuds[profondeur])
		{
			delete elem;
		}
	}
}

// Methodes
void Arbre::trouverMeilleurCoup(int &xDonne, int &yDonne)
{
	/// Traitement: Etape 1: tracer l'arbre
	// Initialisation du niveau de profondeur 0
	m_tabNoeuds[0].push_back(&m_firstNoeud);

	// Autre niveau: On développe l'arbre en largeur
	for(int profondeur=0; profondeur < PROFONDEUR-1; profondeur++) // Jusqu'au niveau désiré
	{
		for(auto elem : m_tabNoeuds[profondeur]) // On veut traiter tout les noeuds d'un meme niveau
		{
			for(int y=0; y<TAB_TAILLE; y++) // Recherche de toute les possibilités de coordonnées
			{
				for(int x=0; x<TAB_TAILLE; x++)
				{
					if(elem->m_tab.selectionValide(x, y))// Si une sélection est valide, alors
						m_tabNoeuds[profondeur+1].push_back(elem->descendre(x, y)); // On ajoute le noeud à l'arbre et au tableau
				}
			}
		}
	}

	/// Traitement: Etape 2: remonter l'arbre du dernier niveau jusqu'au 1er
	for(int profondeur = PROFONDEUR-1; profondeur > 0; profondeur--)
	{
		for(auto elem : m_tabNoeuds[profondeur])
		{
			if((elem->m_profondeur % 2 == 0) && (elem->m_meilleurNombreDePion < elem->m_antecedent->m_meilleurNombreDePion)) // m_meilleurNombreDePion prend la valeur minimum
				elem->m_antecedent->m_meilleurNombreDePion = elem->m_meilleurNombreDePion;

			if((elem->m_profondeur % 2 == 1) && (elem->m_meilleurNombreDePion > elem->m_antecedent->m_meilleurNombreDePion)) // m_meilleurNombreDePion prend la valeur maximum
				elem->m_antecedent->m_meilleurNombreDePion = elem->m_meilleurNombreDePion;
		}
	}

	/// Traitement: Etape 3: on choisit au niveau de profondeur 1 quel coup jouer
	for(auto elem : m_tabNoeuds[1]) // Le maximum ayant déjà été déterminé, on regarde à quel X/Y joué il correspond
	{
		if(elem->m_meilleurNombreDePion == elem->m_antecedent->m_meilleurNombreDePion) {
			xDonne = elem->m_x;
			yDonne = elem->m_y;
			return;
		}
	}
}
