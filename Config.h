#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

// Infos basiques tablier
#define TAB_TAILLE 8
#define NBRE_PIONS TAB_TAILLE * TAB_TAILLE
#define NOIR 'n'
#define BLANC 'b'
#define VIDE 'x'

// Code ASCII
#define LOGO_PION char(254)
#define LOGO_VIDE char(158)

// Fichier de sauvegarde
#define SAVEFILE "save.txt"

// Affichage sur la console
#define X0 5
#define Y0 3
#define ESPACEMENT_Y 2
#define ESPACEMENT_X 4

#define XMSG 2*X0 + ESPACEMENT_X*TAB_TAILLE
#define YMSG Y0 + (ESPACEMENT_Y*TAB_TAILLE)/2

// Retour GETCH clavier
#define BUTTON_ENTER 	13
#define BUTTON_ESC 		27


#endif // CONFIG_H_INCLUDED
