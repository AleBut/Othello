#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED


#include <iostream>

#include "console.h"
#include "Config.h"

class Game
{
private:
	int m_nombreDePions; // Nombre de pion totale
	char m_tablier[TAB_TAILLE][TAB_TAILLE]; // Tablier
	char m_tourDeJouer; // Quel partie doit jouer?

	Console * m_pConsole; // Pointeur sur l'instance console

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

	void reinitialiserTablier(); // On réinitialise le tablier
	void chargerTablier(); // On charge le tablier
	void sauvegarderTablier(); // On sauvegarde le tablier

	void afficherTablier(); // On affiche le tablier
	void afficherMessage(std::string message); // On affiche un message sur le côté

	void selectionCase(int &x, int &y); // On retourne les coordonnées X et Y d'une case choisie par l'utilisateur
	bool selectionValide(int x, int y); // On vérifie si la case est valide
	void poserPion(int x, int y); // On pose un pion sur cette case
	bool caseLibre(int x, int y); // On vérifie si la case est libre

	void avancerTour(); // On avance le tour en changeant la variable m_tourDeJouer
	bool finDuJeux(); // Returne vrai si on ne peut plus poser de pion
	void trouverVainqueur(); // Affiche les scores et le vainqueur

	// Getters & Setters
	int getNombreDePions();

	char * getTableau();

};


#endif // GAME_H_INCLUDED
