#ifndef GRAPHICALLEGRO_H_INCLUDED
#define GRAPHICALLEGRO_H_INCLUDED

/*!
* \file GraphicAllegro.h
* \brief Contient le namespace englobant les fonctions relatives a Allegro
*/

#include <string>

#include "Tablier.h"

/*! \namespace graphique
* Espace regroupant toutes les fonctions necessaires pour jouer a l'Othello avec des graphismes
*/
namespace graphique
{
	/*!
	* \brief Initialise Allegro
	*
	* Demarre Allegro, initialise la souris et autres perepheriques necessaires
	*/
	void demarer_allegro();

	/*!
	* \brief Affiche le tablier
	*
	* Affiche dans la fenêtre graphique le tablier
	*
	* \param tab : Tablier (tablier a afficher)
	*/
	void afficherTablier(Tablier tab);

	/*!
	* \brief Affiche un message
	*
	* Affiche un message a droite du tablier
	*
	* \param message : std::string (message a afficher)
	*/
	void afficherMessage(std::string message);

	/*!
	* \brief Retourne les coordonnees d'une case
	*
	* Retourne les coordonnees d'une case X & Y selectionnee par le joueur
	*
	* \param x : reference sur un int (coordonnee en x)
	* \param y : reference sur un int (coordonnee en y)
	*/
	void selectionCase(int &x, int &y);
}

#endif // GRAPHICALLEGRO_H_INCLUDED
