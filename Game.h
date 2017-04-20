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
	void menu(); // Propose un menu permettant aux utilisateurs de s�lectionner des modes de jeux

	void modeJoueurVJoueur(); // Joueurs contre Joueurs
	void modeIARVJoueur(); // Intelligence Artificielle Random contre Joueur
	void modeIAMinMaxVJoueur(); // Intelligence Artificielle avec algorithme Minimum Max contre Joueur

	void joueurJoue(); // Le joueur s�lectionne un pion et joue
	void IARJoue(); // L'IA Random joue
	void IAMinMaxJoue(); // L'IA Minimum Max joue

	void afficherTablier(); // On affiche le tablier
	void afficherMessage(std::string message); // On affiche un message sur le c�t�
	void selectionCase(int &x, int &y); // On retourne les coordonn�es X et Y d'une case choisie par l'utilisateur
	void mettreEnSurbrillance(int x, int y, Color c); // Met en surbrillance une case

	/// CONSOLE
	void afficherTablierConsole(); // On affiche le tablier
	void afficherMessageConsole(std::string message); // On affiche un message sur le c�t�
	void selectionCaseConsole(int &x, int &y); // On retourne les coordonn�es X et Y d'une case choisie par l'utilisateur
	void mettreEnSurbrillanceConsole(int x, int y, Color c); // Met en surbrillance une case

	/// GRAPHIQUE
	void afficherTablierGraphique();
	void afficherMessageGraphique(std::string message);
	void selectionCaseGraphique(int &x, int &y);
	void mettreEnSurbrillanceGraphique(int x, int y, Color c);


	void trouverVainqueur(); // Affiche les scores et le vainqueur
};


#endif // GAME_H_INCLUDED
