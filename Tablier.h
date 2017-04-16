#ifndef TABLIER_H_INCLUDED
#define TABLIER_H_INCLUDED


#include "Config.h"

class Tablier
{
	public:
		int m_nombreDePions; // Nombre de pion totale
		char m_tab[TAB_TAILLE][TAB_TAILLE]; // Tablier
		char m_tourDeJouer; // Quel joueur doit jouer?


		// Constructeur & Destructeur
		Tablier();
		Tablier(Tablier const& copy);
		~Tablier();

		// Méthodes
		void reinitialiserTablier(); // On réinitialise le tablier
		void chargerTablier(); // On charge le tablier
		void sauvegarderTablier(); // On sauvegarde le tablier

		bool selectionValide(int x, int y); // On vérifie si la case est valide
		void poserPion(int x, int y); // On pose un pion sur cette case
		bool caseLibre(int x, int y); // On vérifie si la case est libre
		int nombreDePion(char couleur); // Renvoit le nombre de pions des joueurs jouant


		void avancerTour(); // On avance le tour en changeant la variable m_tourDeJouer
		bool finDuJeux(); // Returne vrai si on ne peut plus poser de pion

};

#endif // TABLIER_H_INCLUDED
