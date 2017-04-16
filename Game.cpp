#include <stdlib.h> // Clear console & random
#include <sstream> // N�cessaire pour le patch
#include <iostream> // I/O
#include <Windows.h> // Pour la fonction Sleep

#include "Game.h"
#include "Arbre.h"


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
	:m_pConsole(Console::getInstance())
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

	m_pConsole->gotoLigCol(X0, 2*Y0);	std::cout << "[1] Nouvelle partie";
	m_pConsole->gotoLigCol(X0, 3*Y0);	std::cout << "[2] Sauvegarde";

	// Boucle choix
	while(choix < '1' || choix > '2')
	{
		 if(m_pConsole->isKeyboardPressed())
			choix = m_pConsole->getInputKey();
	}

	switch(choix)
	{
		case '1' : m_tablier.reinitialiserTablier(); 	break; // On re-initialise le tablier en tablier d'origine
		case '2' : m_tablier.chargerTablier(); 			break; // On charge les donn�es d'une save
	}

	choix = 0;

	m_pConsole->gotoLigCol(X0, Y0);		std::cout << "Menu: ";
	m_pConsole->gotoLigCol(X0, 2*Y0);	std::cout << "[1] Joueur VS Joueur";
	m_pConsole->gotoLigCol(X0, 3*Y0);	std::cout << "[2] Joueur VS IA Random";
	m_pConsole->gotoLigCol(X0, 4*Y0);	std::cout << "[3] Joueur VS IA MinMax";
	m_pConsole->gotoLigCol(X0, 5*Y0);	std::cout << "[4] Exit";

	// Boucle choix
	while(choix < '1' || choix > '4')
	{
		 if(m_pConsole->isKeyboardPressed())
			choix = m_pConsole->getInputKey();
	}

	// Evenement � d�clencher
	switch(choix)
	{
		case '1': this->modeJoueurVJoueur(); 	break; // Joueur VS Joueur
		case '2': this->modeIARVJoueur(); 		break; // IA Random VS Joueur
		case '3': this->modeIAMinMaxVJoueur();	break; // IA MinMax VS Joueur
		default: 								break;// Ici on se casse
	}
}

void Game::modeJoueurVJoueur()
{
	/// Traitement
	while(!(m_tablier.finDuJeux())) // Tant que le joueur peut jouer un coup valide
	{
		this->afficherTablier(); // Affichage du tablier

		if(m_tablier.m_tourDeJouer == NOIR) // On affiche un message indiquant quel joueur doit jouer
			this->afficherMessage("Les noirs doivent jouer");
		else
			this->afficherMessage("Les blancs doivent jouer");

		this->joueurJoue(); // On joue un pion
		m_tablier.avancerTour(); // On donne aux pions oppos�s le droit de jouer
	}

	this->afficherTablier(); // Petit re-affichage pour actualiser la derni�re pose de pion
	this->trouverVainqueur(); // On trouve le vainqueur
}

void Game::modeIARVJoueur()
{
	/// Traitement
	this->afficherTablier();

	while(!(m_tablier.finDuJeux())) // Tant que le joueur ou l'IA peut jouer un coup valide
	{
		if(m_tablier.m_tourDeJouer == NOIR) { // Le joueur joue
			this->afficherMessage("Les noirs doivent jouer");
			this->joueurJoue(); // On joue un pion
		}
		else if(m_tablier.m_tourDeJouer == BLANC) {
			this->afficherMessage("L'ordinateur joue      ");
			Sleep(1000); // D�lai car l'IA joue instantan�ment ici
			this->IARJoue(); // L'IA joue
		}
		this->afficherTablier(); // Affichage du tablier
		m_tablier.avancerTour(); // On donne aux pions oppos�s le droit de jouer
	}

	this->trouverVainqueur(); // On trouve le vainqueur
}

void Game::modeIAMinMaxVJoueur()
{
	/// Traitement
	this->afficherTablier();

	while(!(m_tablier.finDuJeux())) // Tant que le joueur ou l'IA peut jouer un coup valide
	{
		if(m_tablier.m_tourDeJouer == NOIR) { // Le joueur joue
			this->afficherMessage("Les noirs doivent jouer");
			this->joueurJoue(); // On joue un pion
		}
		else if(m_tablier.m_tourDeJouer == BLANC) {
			this->afficherMessage("L'ordinateur joue      ");
			Sleep(1000); // D�lai car l'IA joue instantan�ment
			this->IAMinMaxJoue(); // L'IA joue
		}
		this->afficherTablier(); // Affichage du tablier
		m_tablier.avancerTour(); // On donne aux pions oppos�s le droit de jouer
	}

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

	} while(!(m_tablier.selectionValide(xSelect, ySelect))); // Tant que la case n'est pas un choix valide

	m_tablier.poserPion(xSelect, ySelect); // On pose le pion et remplace les pions ennemis aux alentours si n�cessaire
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
			if(m_tablier.selectionValide(x, y))
				nombreDeCoupsPossibles++;
		}
	}
		// S�lection du num�ro du coup choisit
		numeroPionSelectionne = (rand() % nombreDeCoupsPossibles) +1;
		nombreDeCoupsPossibles = 0;

		// On joue le coup random
	for(int y=0; y<TAB_TAILLE; y++)
	{
		for(int x=0; x<TAB_TAILLE; x++)
		{
			if(m_tablier.selectionValide(x, y)) {
				nombreDeCoupsPossibles++;

				if(nombreDeCoupsPossibles == numeroPionSelectionne) {
					m_tablier.poserPion(x, y);
					return;
				}
			}
		}
	}
}

void Game::IAMinMaxJoue()
{
	/// Donn�es
	Arbre A(m_tablier);
	int x, y;

	/// Traitement
	A.trouverMeilleurCoup(x, y);
	m_tablier.poserPion(x, y);
}



void Game::afficherTablier()
{
	system("cls");

	for(int y=0; y<TAB_TAILLE; y++)
	{
		for(int x=0; x<TAB_TAILLE; x++)
		{
			m_pConsole->gotoLigCol((X0 + x*ESPACEMENT_X), (Y0+ y*ESPACEMENT_Y));

			switch(m_tablier.m_tab[x][y])
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
	switch(m_tablier.m_tab[x][y])
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

				case BUTTON_ESC: m_tablier.sauvegarderTablier(); // Sauvegarder la partie en cours
				default: 	dx = 0; 	dy = 0; 	break;
			}

			// Blindage pour ne pas d�passer le tableau
			if((x + dx) > (TAB_TAILLE - 1) || (x + dx) < 0)
				dx = 0;
			if((y + dy) > (TAB_TAILLE - 1) || (y + dy) < 0)
				dy = 0;

			// On regrise l'arri�re plan (utiliser la fonction afficher utilise ressources) du curseur pr�c�dent
			m_pConsole->gotoLigCol((X0 + x*ESPACEMENT_X), (Y0+ y*ESPACEMENT_Y));
			switch(m_tablier.m_tab[x][y])
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
			switch(m_tablier.m_tab[x][y])
			{
			case NOIR:	m_pConsole->setColor(COLOR_BLACK, COLOR_RED);	std::cout << LOGO_PION; break;
			case BLANC: m_pConsole->setColor(COLOR_WHITE, COLOR_RED); 	std::cout << LOGO_PION; break;
			default: 	m_pConsole->setColor(COLOR_BLUE, COLOR_RED); 	std::cout << LOGO_VIDE; break;
			}

		}
	}while(bouton != BUTTON_ENTER); // Tant que l'on a pas appuy� sur Enter

	m_pConsole->setColor(COLOR_BLACK, COLOR_GRAY);
}

void Game::trouverVainqueur()
{
	/// Donn�es
	int compteurBlanc = m_tablier.nombreDePion(BLANC);
	int compteurNoir = m_tablier.nombreDePion(NOIR);
	std::string phraseAnnonce;

	/// Traitement
	if(compteurBlanc > compteurNoir) phraseAnnonce = "Les blancs remportent la partie!"; // Choix du message � afficher
	if(compteurBlanc < compteurNoir) phraseAnnonce = "Les noirs remportent la partie!";
	if(compteurBlanc == compteurNoir) phraseAnnonce = "Match nul!";

	phraseAnnonce += " Score: " + patch::to_string(compteurBlanc) + "-" + patch::to_string(compteurNoir); // Score en plus

	this->afficherMessage(phraseAnnonce);
}
