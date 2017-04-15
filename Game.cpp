#include <stdlib.h> // Clear console
#include <fstream> // Dossiers
#include <stdlib.h> // Random
#include <string> // Concat�nation des strings
#include <sstream> // N�cessaire pour le patch

#include "Game.h"


// /!\ PATCH A LA FONCTION DE CONVERSION INT � STRING
namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}


// Constructeur & Destructeur
Game::Game()
	:m_nombreDePions(NBRE_PIONS), m_tourDeJouer(NOIR), m_pConsole(Console::getInstance())
{
	system("cls");
	system("color 80");
}

Game::~Game()
{
	m_pConsole->setColor(COLOR_BLACK, COLOR_GRAY); // On remet la couleur d'origine (pr�caution)
	m_pConsole->gotoLigCol(0, (Y0+ TAB_TAILLE*ESPACEMENT_Y));

	// On lib�re la m�moire
	m_pConsole->deleteInstance();
}


// Methodes
void Game::lancerJeux()
{
	/// Traitement �  compl�ter plus tard pour revenir au menu, ou checker quand le jeux est termin�
	this->menu();


	while(!(m_pConsole->getInputKey())) {} // Tant que l'on ne presse pas une touche
}

void Game::menu()
{
	/// Donn�es
	int choix = 0;

	/// Traitement
	system("cls");

	m_pConsole->gotoLigCol(X0, 2*Y0);
	std::cout << "[1] Nouvelle partie";
	m_pConsole->gotoLigCol(X0, 3*Y0);
	std::cout << "[2] Sauvegarde";

	// Boucle choix
	while(choix < '1' || choix > '2')
	{
		 if(m_pConsole->isKeyboardPressed())
			choix = m_pConsole->getInputKey();
	}

	switch(choix)
	{
		case '1' : this->reinitialiserTablier(); break;
		case '2' : this->chargerTablier(); break;
	}

	choix = 0;

	m_pConsole->gotoLigCol(X0, Y0);
	std::cout << "Menu: ";
	m_pConsole->gotoLigCol(X0, 2*Y0);
	std::cout << "[1] Joueur VS Joueur";
	m_pConsole->gotoLigCol(X0, 3*Y0);
	std::cout << "[2] Joueur VS IA Random";
	m_pConsole->gotoLigCol(X0, 4*Y0);
	std::cout << "[3] Exit";

	// Boucle choix
	while(choix < '1' || choix > '3')
	{
		 if(m_pConsole->isKeyboardPressed())
			choix = m_pConsole->getInputKey();
	}

	// Evenement � d�clencher
	switch(choix)
	{
		case '1': // Joueur VS Joueur
			this->modeJoueurVJoueur();
			break;

		case '2': // IA VS Joueur
			this->modeIARVJoueur();
			break;

		default: // Ici aussi on s'casse
			break;
	}
}



void Game::modeJoueurVJoueur()
{
	/// Traitement
	while(!(this->finDuJeux())) // Tant que le joueur peut jouer un coup valide
	{
		this->afficherTablier(); // Affichage du tablier

		if(m_tourDeJouer == NOIR) // On affiche un message indiquant quel joueur doit jouer
			this->afficherMessage("Les noirs doivent jouer");
		else
			this->afficherMessage("Les blancs doivent jouer");

		this->joueurJoue(); // On joue un pion
		this->avancerTour(); // On donne aux pions oppos�s le droit de jouer
	}

	this->afficherTablier(); // Petit re-affichage pour actualiser la derni�re pose de pion
	this->trouverVainqueur(); // On trouve le vainqueur
}

void Game::modeIARVJoueur()
{
	/// Traitement
	while(!(this->finDuJeux())) // Tant que le joueur ou l'IA peut jouer un coup valide
	{
		this->afficherTablier(); // Affichage du tablier

		if(m_tourDeJouer == NOIR) {// Le joueur joue
			this->afficherMessage("Les noirs doivent jouer");
			this->joueurJoue(); // On joue un pion
		}
		else
			this->IARJoue(); // L'IA joue

		this->avancerTour(); // On donne aux pions oppos�s le droit de jouer
	}

	this->afficherTablier(); // Petit re-affichage pour actualiser la derni�re pose de pion
	this->trouverVainqueur(); // On trouve le vainqueur
}



void Game::joueurJoue()
{
	/// Donn�es
	int xSelect = 0, ySelect = 0;

	/// Traitement
	do
	{
		// On s�lectionne une case � l'aide des boutons z, d, s, q, et ENTER pour valider
		this->selectionCase(xSelect, ySelect);

	} while(!(this->selectionValide(xSelect, ySelect))); // Tant que la case n'est pas un choix valide

	this->poserPion(xSelect, ySelect); // On pose le pion et remplace les pions ennemis aux alentours si n�cessaire
}

void Game::IARJoue()
{
	/// Donn�es
	int numeroPionSelectionne = 0, nombreDeCoupsPossibles = 0;

	/// Traitement
		// Nombre de coups possibles
	for(int y=0; y<TAB_TAILLE; y++)
	{
		for(int x=0; x<TAB_TAILLE; x++)
		{
			if(this->selectionValide(x, y))
				nombreDeCoupsPossibles++;
		}
	}
		// S�lection du num�ro du coup choisit
		numeroPionSelectionne = rand() % (nombreDeCoupsPossibles + 1);
		nombreDeCoupsPossibles = 0;

		// On joue le coup random
	for(int y=0; y<TAB_TAILLE; y++)
	{
		for(int x=0; x<TAB_TAILLE; x++)
		{
			if(this->selectionValide(x, y)) {
				nombreDeCoupsPossibles++;

				if(nombreDeCoupsPossibles == numeroPionSelectionne) {
					this->poserPion(x, y);
					return;
				}
			}
		}
	}

}



void Game::reinitialiserTablier()
{
	// Remplissage tableau
	for(int x=0; x<TAB_TAILLE; x++)
	{
		for(int y=0; y<TAB_TAILLE; y++)
		{
			m_tablier[x][y] = VIDE;
		}
	}

	// On pose les 4 pions initaux
	m_tablier	[(TAB_TAILLE/2)-1]	[(TAB_TAILLE/2)-1]	= BLANC;
	m_tablier	[TAB_TAILLE/2]		[TAB_TAILLE/2]		= BLANC;
	m_tablier	[TAB_TAILLE/2]		[(TAB_TAILLE/2)-1]	= NOIR;
	m_tablier	[(TAB_TAILLE/2)-1]	[TAB_TAILLE/2]		= NOIR;
}

void Game::chargerTablier()
{
	/// Donn�es
	std::string ligne; // Ligne servant � lire les donn�es

	/// Traitement
	std::ifstream fichier(SAVEFILE, std::ios::in); // Ouverture du fichier

	if(!fichier) { // V�rification
		std::cout << "Erreur ouverture fichier: " << SAVEFILE << std::endl;
		return;
	}

	getline(fichier, ligne); // On r�cup�re la ligne
	m_tourDeJouer = ligne[0]; // Cette ligne ne comportant qu'une lettre, d�terminant qui joue � ce moment pr�cis

	for(int y=0; y<TAB_TAILLE; y++)
	{
		getline(fichier, ligne); // On r�cup�re la ligne

		for(int x=0; x<TAB_TAILLE; x++)
		{
			m_tablier[x][y] = ligne[x]; // On remplit le tableau
		}
	}

	fichier.close();  // on ferme le fichier
}

void Game::sauvegarderTablier() //!\\ Changer plus tard le "text.txt" en SAVEFILE
{
	/// Traitement
	std::ofstream fichier("test.txt", std::ios::out | std::ios::trunc);// Ouverture en �criture et effacage

	if(!fichier) { // V�rification
	std::cout << "Erreur ouverture fichier: " << SAVEFILE << std::endl;
	return;
	}

	fichier << m_tourDeJouer << std::endl; // On �crit d'abord qui doit jouer � ce tour l�

	for(int y=0; y<TAB_TAILLE; y++)
	{
		for(int x=0; x<TAB_TAILLE; x++)
		{
			fichier << m_tablier[x][y]; // On sauvegarde le tableau
		}
		fichier << std::endl;
	}
	fichier.close();
}



void Game::afficherTablier()
{
	system("cls");

	for(int y=0; y<TAB_TAILLE; y++)
	{
		for(int x=0; x<TAB_TAILLE; x++)
		{
			m_pConsole->gotoLigCol((X0 + x*ESPACEMENT_X), (Y0+ y*ESPACEMENT_Y));

			switch(m_tablier[x][y])
			{
			case NOIR:	m_pConsole->setColor(COLOR_BLACK, COLOR_GRAY);	std::cout << LOGO_PION; break;
			case BLANC:	m_pConsole->setColor(COLOR_WHITE, COLOR_GRAY);	std::cout << LOGO_PION;	break;
			default:	m_pConsole->setColor(COLOR_BLUE, COLOR_GRAY);	std::cout << LOGO_VIDE;	break;
			}
		}
	}
	m_pConsole->setColor(COLOR_BLACK, COLOR_GRAY); // On remet la couleur d'origine (pr�caution)
}

void Game::afficherMessage(std::string message)
{
    m_pConsole->gotoLigCol(XMSG, YMSG);

    std::cout << message;
}




void Game::selectionCase(int &x, int &y)
{
	/// Donn�es
	int bouton = 0, dx, dy; // Bouton recevant la valeur de la touche press�e, d�placement en X et Y

	/// Traitement

	// On colorie la 1�re case [0][0] pour montrer la position initiale du curseur
	m_pConsole->gotoLigCol((X0 + x*ESPACEMENT_X), (Y0+ y*ESPACEMENT_Y));
	switch(m_tablier[x][y])
	{
	case NOIR:	m_pConsole->setColor(COLOR_BLACK, COLOR_RED);	std::cout << LOGO_PION; break;
	case BLANC: m_pConsole->setColor(COLOR_WHITE, COLOR_RED); 	std::cout << LOGO_PION; break;
	default: 	m_pConsole->setColor(COLOR_BLUE, COLOR_RED); 	std::cout << LOGO_VIDE; break;
	}

	do
	{
		if(m_pConsole->isKeyboardPressed()) { // Si une touche est press�e
			bouton = m_pConsole->getInputKey(); // On actualise la valeur de Bout

			// On re-calcule les valeurs de Dx et Dy en fonction de cette derni�re
			switch(bouton)
			{
				case 'z':	dx = 0; 	dy = -1; 	break;
				case 's': 	dx = 0; 	dy = 1; 	break;
				case 'q': 	dx = -1; 	dy = 0; 	break;
				case 'd': 	dx = 1; 	dy = 0; 	break;

				case BUTTON_ESC: this->sauvegarderTablier(); // Sauvegarder la partie en cours
				default: 	dx = 0; 	dy = 0; 	break;
			}

			// Blindage pour ne pas d�passer le tableau
			if((x + dx) > (TAB_TAILLE - 1) || (x + dx) < 0)
				dx = 0;
			if((y + dy) > (TAB_TAILLE - 1) || (y + dy) < 0)
				dy = 0;

			// On regrise l'arri�re plan (utiliser la fonction afficher utilise ressources) du curseur pr�c�dent
			m_pConsole->gotoLigCol((X0 + x*ESPACEMENT_X), (Y0+ y*ESPACEMENT_Y));
			switch(m_tablier[x][y])
			{
			case NOIR:	m_pConsole->setColor(COLOR_BLACK, COLOR_GRAY);	std::cout << LOGO_PION; break;
			case BLANC: m_pConsole->setColor(COLOR_WHITE, COLOR_GRAY); 	std::cout << LOGO_PION; break;
			default: 	m_pConsole->setColor(COLOR_BLUE, COLOR_GRAY); 	std::cout << LOGO_VIDE; break;
			}

			// Calcul de la nouvelle position
			x += dx;
			y += dy;

			// On colorie le curseur
			m_pConsole->gotoLigCol((X0 + x*ESPACEMENT_X), (Y0+ y*ESPACEMENT_Y));
			switch(m_tablier[x][y])
			{
			case NOIR:	m_pConsole->setColor(COLOR_BLACK, COLOR_RED);	std::cout << LOGO_PION; break;
			case BLANC: m_pConsole->setColor(COLOR_WHITE, COLOR_RED); 	std::cout << LOGO_PION; break;
			default: 	m_pConsole->setColor(COLOR_BLUE, COLOR_RED); 	std::cout << LOGO_VIDE; break;
			}

		}
	}while(bouton != BUTTON_ENTER); // Tant que l'on a pas appuy� sur Enter

	m_pConsole->setColor(COLOR_BLACK, COLOR_GRAY);
}

bool Game::selectionValide(int x, int y)
{
	/// Donn�es
	char pionEnnemi, pion = m_tourDeJouer;

	/// Traitement
	if(pion == NOIR) 	pionEnnemi = BLANC;
	if(pion == BLANC) 	pionEnnemi = NOIR;

	if(!(this->caseLibre(x,y))) // 1er test
		return false;

	if((x-2 >= 0) && (y-2 >= 0))
		if(	(m_tablier[x-1][y-1] == pionEnnemi) 	&& 		(m_tablier[x-2][y-2] == pion)	)	return true; // Haut-Gauche
	if(y-2 >= 0)
		if(	(m_tablier[x][y-1] == pionEnnemi) 		&&		(m_tablier[x][y-2] == pion)		)	return true; // Haut
	if((x+2 < TAB_TAILLE) && (y-2 >= 0))
		if(	(m_tablier[x+1][y-1] == pionEnnemi) 	&& 		(m_tablier[x+2][y-2] == pion) 	)	return true; // Haut-Droit

	if(x-2 >= 0)
		if(	(m_tablier[x-1][y] == pionEnnemi) 		&& 		(m_tablier[x-2][y] == pion)		)	return true; // Middle-Gauche
	if(x+2 < TAB_TAILLE)
		if(	(m_tablier[x+1][y] == pionEnnemi) 		&& 		(m_tablier[x+2][y] == pion)		)	return true; // Middle-Droit

	if((x-2 >= 0) && (y+2 < TAB_TAILLE))
		if(	(m_tablier[x-1][y+1] == pionEnnemi) 	&& 		(m_tablier[x-2][y+2] == pion)	)	return true; // Bas-Gauche
	if(y+2 < TAB_TAILLE)
		if(	(m_tablier[x][y+1] == pionEnnemi) 		&&		(m_tablier[x][y+2] == pion)		)	return true; // Bas
	if((x+2 < TAB_TAILLE) && (y+2 < TAB_TAILLE))
		if(	(m_tablier[x+1][y+1] == pionEnnemi) 	&& 		(m_tablier[x+2][y+2] == pion) 	)	return true; // Bas-Droit

	// Si aucune des conditions pr�c�dentes n'a retourn� vraie
	return false;
}

void Game::poserPion(int x, int y)
{
	/// Donn�es
	char pionEnnemi, pion = m_tourDeJouer;

	/// Traitement
	if(pion == NOIR) 	pionEnnemi = BLANC;
	if(pion == BLANC) 	pionEnnemi = NOIR;

	/// Traitement
	// Pion au milieu
	if((x-2 >= 0) && (y-2 >= 0))
		if(	(m_tablier[x-1][y-1] == pionEnnemi) 	&& 		(m_tablier[x-2][y-2] == pion)	)	m_tablier[x-1][y-1] = pion; // Haut-Gauche
	if(y-2 >= 0)
		if(	(m_tablier[x][y-1] == pionEnnemi) 		&&		(m_tablier[x][y-2] == pion)		)	m_tablier[x][y-1] 	= pion; // Haut
	if((x+2 < TAB_TAILLE) && (y-2 >= 0))
		if(	(m_tablier[x+1][y-1] == pionEnnemi) 	&& 		(m_tablier[x+2][y-2] == pion) 	)	m_tablier[x+1][y-1] = pion; // Haut-Droit

	if(x-2 >= 0)
		if(	(m_tablier[x-1][y] == pionEnnemi) 		&& 		(m_tablier[x-2][y] == pion)		)	m_tablier[x-1][y] = pion; // Middle-Gauche
	if(x+2 < TAB_TAILLE)
		if(	(m_tablier[x+1][y] == pionEnnemi) 		&& 		(m_tablier[x+2][y] == pion)		)	m_tablier[x+1][y] = pion; // Middle-Droit

	if((x-2 >= 0) && (y+2 < TAB_TAILLE))
		if(	(m_tablier[x-1][y+1] == pionEnnemi) 	&& 		(m_tablier[x-2][y+2] == pion)	)	m_tablier[x-1][y+1] = pion; // Bas-Gauche
	if(y+2 < TAB_TAILLE)
		if(	(m_tablier[x][y+1] == pionEnnemi) 		&&		(m_tablier[x][y+2] == pion)		)	m_tablier[x][y+1] 	= pion; // Bas
	if((x+2 < TAB_TAILLE) && (y+2 < TAB_TAILLE))
		if(	(m_tablier[x+1][y+1] == pionEnnemi) 	&& 		(m_tablier[x+2][y+2] == pion) 	)	m_tablier[x+1][y+1] = pion; // Bas-Droit

	// Pion � l'endroit souhait�
	m_tablier[x][y] = pion;
}

bool Game::caseLibre(int x, int y)
{
	if(m_tablier[x][y] == VIDE)
		return true;
	else
		return false;
}



void Game::avancerTour()
{
	if(m_tourDeJouer == NOIR)
		m_tourDeJouer = BLANC;
	else
		m_tourDeJouer = NOIR;
}

bool Game::finDuJeux()
{
	for(int y=0; y<TAB_TAILLE; y++)
	{
		for(int x=0; x<TAB_TAILLE; x++)
		{
			if(this->selectionValide(x, y))
				return false;
		}
	}
	// Si aucune condition n'a renvoy� false, donc qu'il n'y a pas de s�lection valide que l'on peut faire, c'est la fin du jeux
	return true;
}

void Game::trouverVainqueur()
{
	/// Donn�es
	int compteurBlanc = 0, compteurNoir = 0;
	std::string phraseAnnonce;

	/// Traitement
	for(int y=0; y<TAB_TAILLE; y++) // Parcours du tableau
	{
		for(int x=0; x<TAB_TAILLE; x++)
		{
			if(m_tablier[x][y] == BLANC) 	compteurBlanc++; // Incr�mentation du compteur
			if(m_tablier[x][y] == NOIR)		compteurNoir++;
		}
	}

	if(compteurBlanc > compteurNoir) phraseAnnonce = "Les blancs remportent la partie!"; // Choix du message � afficher
	if(compteurBlanc < compteurNoir) phraseAnnonce = "Les noirs remportent la partie!";
	if(compteurBlanc == compteurNoir) phraseAnnonce = "Match nul!";

	phraseAnnonce += " Score: " + patch::to_string(compteurBlanc) + "-" + patch::to_string(compteurNoir); // Score en plus

	this->afficherMessage(phraseAnnonce);
}

// Getters & Setters
int Game::getNombreDePions()
{
	return m_nombreDePions;
}

char * Game::getTableau()
{
	return &m_tablier[TAB_TAILLE][TAB_TAILLE];
}
