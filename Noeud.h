#ifndef NOEUD_H_INCLUDED
#define NOEUD_H_INCLUDED

/*!
* \file Noeud.h
* \brief Contient la classe Noeud
*/

#include <vector>
#include "Tablier.h"
#include "Console.h"


/*! \class Noeud
* \brief Classe modelisant un noeud (correspond a un etat donne du jeu) utilise pour l'algorithme MinMax
*/
class Noeud
{
public:
	Noeud * m_antecedent; /*!< Pointeur sur le noeud precedent */
	Tablier m_tab; /*!< Tablier propre au noeud */
	int m_x; /*!< Coordonnee en X du pion joue a partir du noeud precedent */
	int  m_y; /*!< Coordonnee en Y du pion joue a partir du noeud precedent */
	int m_meilleurNombreDePion; /*!< Permet de comparer la meilleure "option" de jouer rapportant le plus de point */
	Color m_couleur; /*!< Permet de mieux visualiser l'arbre */


public:
	/*!
	* \brief Constructeur du 1er noeud
	*
	* Constructeur de la classe Noeud pour le 1er noeud seulement
	*
	* \param _tab : Tablier
	*/
	Noeud(Tablier _tab);

	/*!
	* \brief Constructions des autres noeuds
	*
	* Constructeur des noeuds descendant du 1er
	*
	* \param _antecedent : Noeud * (pointeur sur le noeud antecedent)
	* \param _x : int (coordonnee en x du pion joue)
	* \param _y : int (coordonnee en y du pion joue)
	*/
	Noeud(Noeud * _antecedent, int _x, int _y);

	/*!
	* \brief Destructeur
	*
	* Destructeur de la classe Noeud
	*/
	~Noeud();

public:
	/*!
	* \brief On genere un noeud fille
	*
	* On genere un noeud fille en posant un pion en X & Y
	*
	* \param x : int (coordonnee en x du pion joue)
	* \param y : int (coordonnee en y du pion joue)
	* \return Noeud * (pointeur sur le noeud cree)
	*/
	Noeud * descendre(int x, int y);
};

#endif // NOEUD_H_INCLUDED
