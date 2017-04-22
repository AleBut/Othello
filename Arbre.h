#ifndef ARBRE_H_INCLUDED
#define ARBRE_H_INCLUDED

/*!
* \file Arbre.h
* \brief Contient la classe Arbre
*/

#include "Noeud.h"


/*! \class Arbre
* \brief Classe generant le trace de l'arbre MinMax et l'exploitant pour obtenir le meilleur coup
*/
class Arbre
{
private:
	int m_profondeur; /*!< Profondeur de l'arbre */
	Noeud m_firstNoeud; /*!< Noeud de depart de l'arbre, etant l'echequier actuel */
	std::vector<Noeud  *> m_tabNoeuds[PROFONDEUR]; /*!< Tableau stockant les pointeurs sur les noeuds par niveau de profondeur */

public:
	/*!
	* \brief Constructeur
	*
	* Constuit un arbre a partir du tablier du jeux actuel
	*
	* \param _tab : Tablier (tablier de jeux actuel)
	*\param _profondeur : int (profondeur de l'arbre)
	*/
	Arbre(Tablier _tab, int _profondeur = PROFONDEUR);

	/*!
	* \brief Destructeur
	*
	* Destructeur de la classe Arbre
	*/
	~Arbre();

public:
	/*!
	* \brief Retourne le meilleur coup a jouer
	*
	* Retourne les coordonnees d'une case X & Y etant consideree sur plusieurs tour comme le meilleur coup
	*
	* \param x : reference sur un int (coordonnee en x)
	* \param y : reference sur un int (coordonnee en y)
	*/
	void trouverMeilleurCoup(int &x, int &y);

	/*!
	* \brief Trace l'arbre
	*
	* On trace toute les possibilites possibles sur une certaine profondeur
	*/
	void tracerArbre();

	/*!
	* \brief On remonte l'arbre
	*
	* On remonte l'arbre des racines en selectionnant le Min ou Max
	*/
	void remonterArbre();

	/*!
	* \brief On dessine l'arbre dans la console
	*
	* On dessine l'arbre de l'algorithme MinMax ou de l'IA Random dans toute son integralite
	*/
	void dessinerConsole();
};

#endif // ARBRE_H_INCLUDED
