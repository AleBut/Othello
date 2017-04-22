#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

/*!
* \file Game.h
* \brief Contient la classe Game
*/

#include "Tablier.h"
#include "console.h"

/*! \class Game
* \brief Classe gerant le deroulement d'une partie d'Othello
*/
class Game
{
private:
	Console * m_pConsole; /*!< Pointeur sur l'instance console */

	Tablier m_tablier; /*!< Tablier du jeux */

public:
	/*!
	* \brief Constructeur
	*
	* Constructeur de la classe Game
	*/
	Game();

	/*!
	* \brief Destructeur
	*
	* Destructeur de la classe Game
	*/
	~Game();

public:
	// ***************
	// GESTION DU JEUX
	// ***************

	/*!
	* \brief Lance le jeux
	*
	* Lance une partie d'Othello
	*/
	void lancerJeux();

	/*!
	* \brief Lance le menu
	*
	* Le menu permet de charger/creer un tablier, choisir contre qui jouer (joueur, IA random, IA MinMax)
	*/
	void menu();

	/*!
	* \brief Trouve le vainqueur
	*
	* Retrouve le vainqueur quand le jeux est termine en comptant les pions
	*/
	void trouverVainqueur();

	/*!
	* \brief Selectionne le mode de jeux Joueur contre Joueur
	*
	* Lance un jeux où 2 joueurs vont s'affronter
	*/
	void modeJoueurVJoueur();

	/*!
	* \brief Selectionne le mode de jeux Joueur contre IA random
	*
	* Lance un jeux où l'on affronte une IA jouant de maniere aleatoire
	*/
	void modeIARVJoueur();

	/*!
	* \brief Selectionne le mode de jeux Joueur contre IA Min-Max
	*
	* Lance un jeux où l'on affronte une IA jouant avec l'algorithme Min-Max
	*/
	void modeIAMinMaxVJoueur();

	/*!
	* \brief Le joueur joue
	*
	* Offre la possibilite au joueur de selectionner un pion et jouer
	*/
	void joueurJoue();

	/*!
	* \brief L'IA random joue
	*
	* L'IA va selectionner au hasard un pion et le jouer
	*/
	void IARJoue();

	/*!
	* \brief L'IA Min-Max joue
	*
	* L'IA va anticiper les prochains coups et opter pour le meilleur coup possible avec l'algorithme Min-Max
	*/
	void IAMinMaxJoue();

	// ******************
	// INTERACTION JOUEUR
	// ******************

	/*!
	* \brief Affichage du tablier
	*
	* On affiche le tablier representant le jeux de l'Othello
	*/
	void afficherTablier();

	/*!
	* \brief Affichage d'un message
	*
	* On affiche des messages a côte du tablier indiquant le tour de jouer, le score, qui remporte la partie...
	*
	* \param message : std::string (contenu du message)
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

	/*!
	* \brief Met en surbrillance une case
	*
	* Change l'arriere plan d'une case pour mettre en evidence un element
	*
	* \param x : int (coordonnee en x)
	* \param y : int (coordonnee en y)
	* \param c : Color (couleur de l'arriere plan)
	*/
	void mettreEnSurbrillance(int x, int y, Color c); // Met en surbrillance une case
};


#endif // GAME_H_INCLUDED
