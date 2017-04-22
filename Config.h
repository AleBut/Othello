#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

/*!
* \file Config.h
* \brief Contient des valeurs par defaut facilement accesssibles et modifiables
*/

/// MODE GRAPHIQUE ACTIVE
#define GRAPH			true


/// MODE ARBRE DE RECHERCHE ACTIVE
#define ARBRE			true

/// STOCKAGE DONNEES TABLIER
#define TAB_TAILLE 		8
#define NOIR			'n'							// Représente le 1er joueur
#define BLANC 			'b'							// Représente le 2nd joueur, ou l'IA
#define VIDE 			'x'

/// INFO JEUXCONSOLE
#define LOGO_PION 		char(254)
#define LOGO_VIDE 		char(158)

#define X0 				5
#define Y0 				3
#define ESPACEMENT_Y 	2
#define ESPACEMENT_X	4

#define XMSG 			2*X0 + ESPACEMENT_X*TAB_TAILLE
#define YMSG 			Y0 + (ESPACEMENT_Y*TAB_TAILLE)/2

/// INFO JEU GRAPHIQUE
#define PION_TAILLE 	40

#define DIMY 			600
#define DIMX 			350

#define DIM_X_TABLIER 	333
#define DIM_Y_TABLIER 	338

#define GRAPH_X_MESSAGE DIM_X_TABLIER + PION_TAILLE
#define GRAPH_Y_MESSAGE DIM_Y_TABLIER/2


/// FICHIER DE SAUVEARDE
#define SAVEFILE 		"save.txt"

/// RETOUR ASCII CLAVIER
#define BUTTON_ENTER 	13
#define BUTTON_ESC 		27

/// PROFONDEUR ARBRE DE RECHERCHE
#define PROFONDEUR 		5
#define INFINI 65

#endif // CONFIG_H_INCLUDED
