#include "Tablier.h"

#include <fstream> // Dossiers
#include <string> // Concaténation des strings
#include <iostream> // I/O


Tablier::Tablier()
		:m_nombreDePions(NBRE_PIONS), m_tourDeJouer(NOIR)
{
	// Nothing
}


Tablier::Tablier(Tablier const& copy)
		:m_nombreDePions(copy.m_nombreDePions), m_tourDeJouer(copy.m_tourDeJouer)
{
	for(int y=0; y<TAB_TAILLE; y++)
	{
		for(int x=0; x<TAB_TAILLE; x++)
		{
			m_tab[x][y] = copy.m_tab[x][y];
		}
	}
}

Tablier::~Tablier()
{
	// Nothing
}


void Tablier::reinitialiserTablier()
{
	// Remplissage tableau
	for(int x=0; x<TAB_TAILLE; x++)
	{
		for(int y=0; y<TAB_TAILLE; y++)
		{
			m_tab[x][y] = VIDE;
		}
	}

	// On pose les 4 pions initaux
	m_tab	[(TAB_TAILLE/2)-1]	[(TAB_TAILLE/2)-1]	= BLANC;
	m_tab	[TAB_TAILLE/2]		[TAB_TAILLE/2]		= BLANC;
	m_tab	[TAB_TAILLE/2]		[(TAB_TAILLE/2)-1]	= NOIR;
	m_tab	[(TAB_TAILLE/2)-1]	[TAB_TAILLE/2]		= NOIR;

	// On reinitialise le tour de jouer
	m_tourDeJouer = NOIR;
}

void Tablier::chargerTablier()
{
	/// Données
	std::string ligne; // Ligne servant à lire les données

	/// Traitement
	std::ifstream fichier(SAVEFILE, std::ios::in); // Ouverture du fichier

	if(!fichier) { // Vérification
		std::cout << "Erreur ouverture fichier: " << SAVEFILE << std::endl;
		return;
	}

	getline(fichier, ligne); // On récupère la ligne
	m_tourDeJouer = ligne[0]; // Cette ligne ne comportant qu'une lettre, déterminant qui joue à ce moment précis

	for(int y=0; y<TAB_TAILLE; y++)
	{
		getline(fichier, ligne); // On récupère la ligne

		for(int x=0; x<TAB_TAILLE; x++)
		{
			m_tab[x][y] = ligne[x]; // On remplit le tableau
		}
	}

	fichier.close();  // on ferme le fichier
}

void Tablier::sauvegarderTablier() //!\\ Changer plus tard le "text.txt" en SAVEFILE
{
	/// Traitement
	std::ofstream fichier("test.txt", std::ios::out | std::ios::trunc);// Ouverture en écriture et effacage

	if(!fichier) { // Vérification
	std::cout << "Erreur ouverture fichier: " << SAVEFILE << std::endl;
	return;
	}

	fichier << m_tourDeJouer << std::endl; // On écrit d'abord qui doit jouer à ce tour là

	for(int y=0; y<TAB_TAILLE; y++)
	{
		for(int x=0; x<TAB_TAILLE; x++)
		{
			fichier << m_tab[x][y]; // On sauvegarde le tableau
		}
		fichier << std::endl;
	}
	fichier.close();
}




bool Tablier::selectionValide(int x, int y)
{
	/// Données
	char pionEnnemi, pion = m_tourDeJouer;

	/// Traitement
	if(pion == NOIR) 	pionEnnemi = BLANC;
	if(pion == BLANC) 	pionEnnemi = NOIR;

	if(!(this->caseLibre(x,y))) // 1er test
		return false;

	if((x-2 >= 0) && (y-2 >= 0))
		if(	(m_tab[x-1][y-1] == pionEnnemi) 	&& 		(m_tab[x-2][y-2] == pion)	)	return true; // Haut-Gauche
	if(y-2 >= 0)
		if(	(m_tab[x][y-1] == pionEnnemi) 		&&		(m_tab[x][y-2] == pion)		)	return true; // Haut
	if((x+2 < TAB_TAILLE) && (y-2 >= 0))
		if(	(m_tab[x+1][y-1] == pionEnnemi) 	&& 		(m_tab[x+2][y-2] == pion) 	)	return true; // Haut-Droit

	if(x-2 >= 0)
		if(	(m_tab[x-1][y] == pionEnnemi) 		&& 		(m_tab[x-2][y] == pion)		)	return true; // Middle-Gauche
	if(x+2 < TAB_TAILLE)
		if(	(m_tab[x+1][y] == pionEnnemi) 		&& 		(m_tab[x+2][y] == pion)		)	return true; // Middle-Droit

	if((x-2 >= 0) && (y+2 < TAB_TAILLE))
		if(	(m_tab[x-1][y+1] == pionEnnemi) 	&& 		(m_tab[x-2][y+2] == pion)	)	return true; // Bas-Gauche
	if(y+2 < TAB_TAILLE)
		if(	(m_tab[x][y+1] == pionEnnemi) 		&&		(m_tab[x][y+2] == pion)		)	return true; // Bas
	if((x+2 < TAB_TAILLE) && (y+2 < TAB_TAILLE))
		if(	(m_tab[x+1][y+1] == pionEnnemi) 	&& 		(m_tab[x+2][y+2] == pion) 	)	return true; // Bas-Droit

	// Si aucune des conditions précédentes n'a retourné vraie
	return false;
}

void Tablier::poserPion(int x, int y)
{
	/// Données
	char pionEnnemi, pion = m_tourDeJouer;

	/// Traitement
	if(pion == NOIR) 	pionEnnemi = BLANC;
	if(pion == BLANC) 	pionEnnemi = NOIR;

	/// Traitement
	// Pion au milieu
	if((x-2 >= 0) && (y-2 >= 0))
		if(	(m_tab[x-1][y-1] == pionEnnemi) 	&& 		(m_tab[x-2][y-2] == pion)	)	m_tab[x-1][y-1] = pion; // Haut-Gauche
	if(y-2 >= 0)
		if(	(m_tab[x][y-1] == pionEnnemi) 		&&		(m_tab[x][y-2] == pion)		)	m_tab[x][y-1] 	= pion; // Haut
	if((x+2 < TAB_TAILLE) && (y-2 >= 0))
		if(	(m_tab[x+1][y-1] == pionEnnemi) 	&& 		(m_tab[x+2][y-2] == pion) 	)	m_tab[x+1][y-1] = pion; // Haut-Droit

	if(x-2 >= 0)
		if(	(m_tab[x-1][y] == pionEnnemi) 		&& 		(m_tab[x-2][y] == pion)		)	m_tab[x-1][y] = pion; // Middle-Gauche
	if(x+2 < TAB_TAILLE)
		if(	(m_tab[x+1][y] == pionEnnemi) 		&& 		(m_tab[x+2][y] == pion)		)	m_tab[x+1][y] = pion; // Middle-Droit

	if((x-2 >= 0) && (y+2 < TAB_TAILLE))
		if(	(m_tab[x-1][y+1] == pionEnnemi) 	&& 		(m_tab[x-2][y+2] == pion)	)	m_tab[x-1][y+1] = pion; // Bas-Gauche
	if(y+2 < TAB_TAILLE)
		if(	(m_tab[x][y+1] == pionEnnemi) 		&&		(m_tab[x][y+2] == pion)		)	m_tab[x][y+1] 	= pion; // Bas
	if((x+2 < TAB_TAILLE) && (y+2 < TAB_TAILLE))
		if(	(m_tab[x+1][y+1] == pionEnnemi) 	&& 		(m_tab[x+2][y+2] == pion) 	)	m_tab[x+1][y+1] = pion; // Bas-Droit

	// Pion à l'endroit souhaité
	m_tab[x][y] = pion;
}

bool Tablier::caseLibre(int x, int y)
{
	if(m_tab[x][y] == VIDE)
		return true;
	else
		return false;
}

int Tablier::nombreDePion(char couleur)
{
	/// Données
	int compteur = 0;

	/// Traitement
	for(int y=0; y<TAB_TAILLE; y++)
	{
		for(int x=0; x<TAB_TAILLE; x++)
		{
			if(m_tab[x][y] == couleur)
				compteur++;
		}
	}
	return compteur;
}

void Tablier::avancerTour()
{
	if(m_tourDeJouer == NOIR)
		m_tourDeJouer = BLANC;
	else
		m_tourDeJouer = NOIR;
}

bool Tablier::finDuJeux()
{
	for(int y=0; y<TAB_TAILLE; y++)
	{
		for(int x=0; x<TAB_TAILLE; x++)
		{
			if(this->selectionValide(x, y))
				return false;
		}
	}
	// Si aucune condition n'a renvoyé false, donc qu'il n'y a pas de sélection valide que l'on peut faire, c'est la fin du jeux
	return true;
}
