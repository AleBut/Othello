/*!
* \file Tablier.cpp
* \brief Description de la classe Tablier
*/

#include "Tablier.h"

#include <fstream> // Dossiers
#include <string> // Concatenation des strings
#include <iostream> // I/O


/// Constructeur & destructeurs
Tablier::Tablier()
		: m_tourDeJouer(NOIR)
{
	// Nothing
}

Tablier::Tablier(Tablier const& copy)
		:m_tourDeJouer(copy.m_tourDeJouer)
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


/// Methodes
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
	/// Donnees
	std::string ligne; // Ligne servant a lire les donnees

	/// Traitement
	std::ifstream fichier(SAVEFILE, std::ios::in); // Ouverture du fichier

	if(!fichier) { // Verification
		std::cout << "Erreur ouverture fichier: " << SAVEFILE << std::endl;
		return;
	}

	getline(fichier, ligne); // On recupere la ligne
	m_tourDeJouer = ligne[0]; // Cette ligne ne comportant qu'une lettre, determinant qui joue a ce moment precis

	for(int y=0; y<TAB_TAILLE; y++)
	{
		getline(fichier, ligne); // On recupere la ligne

		for(int x=0; x<TAB_TAILLE; x++)
		{
			m_tab[x][y] = ligne[x]; // On remplit le tableau
		}
	}

	fichier.close();  // on ferme le fichier
}

void Tablier::sauvegarderTablier()
{
	/// Traitement
	std::ofstream fichier(SAVEFILE, std::ios::out | std::ios::trunc);// Ouverture en ecriture et effacage

	if(!fichier) { // Verification
	std::cout << "Erreur ouverture fichier: " << SAVEFILE << std::endl;
	return;
	}

	fichier << m_tourDeJouer << std::endl; // On ecrit d'abord qui doit jouer a ce tour la

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
	/// Traitement

	if(!(this->caseLibre(x, y)))
		return false;

	if(this->voisinageRecursive(x, y, -1, -1))	return true; // Haut-gauche
	if(this->voisinageRecursive(x, y, 0, -1))	return true; // Haut
	if(this->voisinageRecursive(x, y, 1, -1))	return true; // Haut-droite

	if(this->voisinageRecursive(x, y, -1, 0))	return true; // Gauche
	if(this->voisinageRecursive(x, y, 1, 0))	return true; // Droite

	if(this->voisinageRecursive(x, y, -1, 1))	return true; // Bas-gauche
	if(this->voisinageRecursive(x, y, 0, 1))	return true; // Bas
	if(this->voisinageRecursive(x, y, 1, 1))	return true; // Bas-droite


	// Si aucune des conditions precedentes n'a retourne vraie
	return false;
}

void Tablier::poserPion(int x, int y)
{
	/// Traitement
	if(this->voisinageRecursive(x, y, -1, -1))	this->retournerPionsRecursive(x, y, -1, -1);	// Haut-gauche
	if(this->voisinageRecursive(x, y, 0, -1))	this->retournerPionsRecursive(x, y, 0, -1);		// Haut
	if(this->voisinageRecursive(x, y, 1, -1))	this->retournerPionsRecursive(x, y, 1, -1);		// Haut-droite

	if(this->voisinageRecursive(x, y, -1, 0))	this->retournerPionsRecursive(x, y, -1, 0); 	// Gauche
	if(this->voisinageRecursive(x, y, 1, 0))	this->retournerPionsRecursive(x, y, 1, 0);		// Droite

	if(this->voisinageRecursive(x, y, -1, 1))	this->retournerPionsRecursive(x, y, -1, 1); 	// Bas-gauche
	if(this->voisinageRecursive(x, y, 0, 1))	this->retournerPionsRecursive(x, y, 0, 1); 		// Bas
	if(this->voisinageRecursive(x, y, 1, 1))	this->retournerPionsRecursive(x, y, 1, 1); 		// Bas-droite

	// Pion a l'endroit souhaite
	m_tab[x][y] = m_tourDeJouer;
}

bool Tablier::caseLibre(int x, int y)
{
	if(m_tab[x][y] == VIDE)
		return true;
	else
		return false;
}

bool Tablier::voisinageRecursive(int x, int y, int dx, int dy)
{
	/// Donnees
	int newX = x + dx, newY = y+ dy;

	/// Traitement
	if((newX >= TAB_TAILLE ) || (newX < 0 ) || (newY >= TAB_TAILLE ) || (newY < 0 )) // Si on a depasse le tableau
		return false;

	if(this->caseLibre(newX, newY)) // Si il n'y a aucun pion sur cette case
		return false;

	if((this->caseLibre(x, y)) && (m_tab[newX][newY] == m_tourDeJouer)) // Si il s'agit de poser un pion a côte d'un autre pion allie
		return false;

	if(m_tab[newX][newY] == m_tourDeJouer) // Si le pion suivant est de la même couleur que nous
		return true;
	else
		return this->voisinageRecursive(newX, newY, dx, dy); // Sinon, le pion est blanc et on rappelle la fonction recursive
}

void Tablier::retournerPionsRecursive(int x, int y, int dx, int dy)
{
	/// Donnees
	int newX = x + dx, newY = y + dy;

	/// Traitement
	if(m_tab[newX][newY] == m_tourDeJouer) // On a atteint un pion allie, soit l'extremite de l'encadrement
		return;
	else { 	// Sinon, on est forcement tombe sur un pion ennemi qu'on retourne, et on rappelle la fonction recursive
		m_tab[newX][newY] = m_tourDeJouer;
		this->retournerPionsRecursive(newX, newY, dx, dy);
	}
}



int Tablier::nombreDePion(char couleur)
{
	/// Donnees
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
	// Si aucune condition n'a renvoye false, donc qu'il n'y a pas de selection valide que l'on peut faire, c'est la fin du jeux
	return true;
}
