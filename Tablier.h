#ifndef TABLIER_H_INCLUDED
#define TABLIER_H_INCLUDED

/*!
* \file Tablier.h
* \brief Contient la classe Tablier
*/

#include "Config.h"

/*! \class Tablier
* \brief Classe modifiant le tablier du jeux, s'assure de la validite d'un coup, de l'avancement et de la fin de partie
*/
class Tablier
{
public:
	char m_tab[TAB_TAILLE][TAB_TAILLE]; /*!< Tablier */
	char m_tourDeJouer; /*!< Joueur devant jouer a ce tour */

public:
	/*!
	* \brief Constructeur
	*
	* Constructeur de la classe Tablier
	*/
	Tablier();

	/*!
	* \brief Constructeur par copie
	*
	* Constructeur de la classe Tablier par copie
	*
	* \param copy : Tablier (tablier s'appretant a être copie)
	*/
	Tablier(Tablier const& copy);

	/*!
	* \brief Destructeur
	*
	* Destructeur de la classe Tablier
	*/
	~Tablier();

public:
	// *******************
	// REMPLISSAGE TABLIER
	// *******************

	/*!
	* \brief On reinitialise le tablier
	*
	* Place uniquement 4 pions au milieu du plateau pour un debut de partie classique
	*/
	void reinitialiserTablier();

	/*!
	* \brief Charge un tableau a partir des sauvegardes
	*
	* Charges un tabier a partir du fichier "SAVE.txt"
	*/
	void chargerTablier();

	/*!
	* \brief Sauvegarde le tablier
	*
	* Sauvegarde le tablier dans le fichier "SAVE.txt"
	*/
	void sauvegarderTablier();

	// ***************
	// VALIDATION COUP
	// ***************

	/*!
	* \brief Verification de la validite de la case
	*
	* On verifie si la case de coordonnee X&Y est valide
	*
	* \param x : int (coordonnee en x)
	* \param y : int (coordonnee en y)
	* \return true si on peut poser un pion dans la case selectionnee
	* false sinon
	*/
	bool selectionValide(int x, int y);

	/*!
	* \brief On pose un pion
	*
	* On pose un pion sur la case selectionnee en X&Y
	*
	* \param x : int (coordonnee en x)
	* \param y : int (coordonnee en y)
	*/
	void poserPion(int x, int y);

	/*!
	* \brief On verifie si la case est libre
	*
	* On verifie si la case est libre en X&Y
	*
	* \param x : int (coordonnee en x)
	* \param y : int (coordonnee en y)
	* \return true si la case est libre
	* false sinon
	*/
	bool caseLibre(int x, int y);

	/*!
	* \brief Permet de verifier que la pose d'un pion est valide
	*
	* Permet de verifier dans une direction que la pose d'un pion est valide
	*
	* \param x : int (coordonnee en x)
	* \param y : int (coordonnee en y)
	* \param dx : int (deplacement en x)
	* \param dy : int (deplacement en y)
	*/
	bool voisinageRecursive(int x, int y, int dx, int dy);

	/*!
	* \brief Permet de retourner les pions
	*
	* Permet de retourner les pions dans une direction
	*
	* \param x : int (coordonnee en x)
	* \param y : int (coordonnee en y)
	* \param dx : int (deplacement en x)
	* \param dy : int (deplacement en y)
	*/
	void retournerPionsRecursive(int x, int y, int dx, int dy);

	// ************
	// CALCUL SCORE
	// ************
	/*!
	* \brief On retourne le nombre de pions
	*
	* On retourne le nombre de pions d'une couleur sur le tablier
	*
	* \param couleur : Color (couleur du pion)
	* \return int : nombre de pions sur le tablier
	*/
	int nombreDePion(char couleur); // Renvoit le nombre de pions des joueurs jouant

	// ******************
	// AVANCEMENT DU JEUX
	// ******************

	/*!
	* \brief On avance le tour du joueur
	*
	* On avance le tour en changeant la variable m_tourDeJouer
	*/
	void avancerTour();

	/*!
	* \brief Permet de verifier si l'on peut encore poser un pion
	*
	* Permet de verifier si le joueur peut encore poser un pion sur le tablier
	*
	* \return true si on ne peut plus poser de pion
	* false sinon
	*/
	bool finDuJeux();
};

#endif // TABLIER_H_INCLUDED
