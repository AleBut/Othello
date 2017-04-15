#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "Tablier.h"
#include "console.h"

class Game
{
private:
	Console * m_pConsole; // Pointeur sur l'instance console

	Tablier m_tablier; // Tablier du jeux

public:
	// Constructeur & Destructeur
	Game();
	~Game();

	// Methodes
	void lancerJeux(); // Lance le jeux
	void menu(); // Propose un menu permettant aux utilisateurs de sélectionner des modes de jeux

	void modeJoueurVJoueur(); // Joueurs contre Joueurs
	void modeIARVJoueur(); // Intelligence Artificielle Random contre Joueurs

	void joueurJoue(); // Le joueur sélectionne un pion et joue
	void IARJoue(); // L'IA Random joue

	void afficherTablier(); // On affiche le tablier
	void afficherMessage(std::string message); // On affiche un message sur le côté

	void selectionCase(int &x, int &y); // On retourne les coordonnées X et Y d'une case choisie par l'utilisateur
	void trouverVainqueur(); // Affiche les scores et le vainqueur
};


#endif // GAME_H_INCLUDED
