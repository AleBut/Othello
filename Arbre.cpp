#include "Arbre.h"
#include "console.h"
#include <iostream>
// Constructeur & Destructeur
Arbre::Arbre(Tablier _tab)
    :m_firstNoeud(_tab)
{

}

Arbre::~Arbre()
{
    // Libération de la mémoire
    for(int profondeur=1; profondeur < PROFONDEUR; profondeur++)
    {
        for(auto elem : m_tabNoeuds[profondeur])
        {
            delete elem;
        }
    }
}

// Methodes
void Arbre::trouverMeilleurCoup(int &xDonne, int &yDonne)
{
    /// Traitement:
    this->tracerArbre();
    this->remonterArbre();
    this->Dessin();
    // On choisit au niveau de profondeur 1 quel coup jouer
    for(auto elem : m_tabNoeuds[1]) // Le maximum ayant déjà été déterminé, on regarde à quel X/Y joué il correspond
    {
        if(elem->m_meilleurNombreDePion == elem->m_antecedent->m_meilleurNombreDePion)
        {
            xDonne = elem->m_x;
            yDonne = elem->m_y;
            return;
        }
    }
}

void Arbre::tracerArbre()
{
    /// Traitement
    // Initialisation du niveau de profondeur 0
    m_tabNoeuds[0].push_back(&m_firstNoeud);

    // Autre niveau: On développe l'arbre en largeur
    for(int profondeur=0; profondeur < PROFONDEUR-1; profondeur++) // Jusqu'au niveau désiré
    {
        for(auto elem : m_tabNoeuds[profondeur]) // On veut traiter tout les noeuds d'un meme niveau
        {
            for(int y=0; y<TAB_TAILLE; y++) // Recherche de toute les possibilités de coordonnées
            {
                for(int x=0; x<TAB_TAILLE; x++)
                {
                    if(elem->m_tab.selectionValide(x, y))// Si une sélection est valide, alors
                        m_tabNoeuds[profondeur+1].push_back(elem->descendre(x, y)); // On ajoute le noeud à l'arbre et au tableau
                }
            }
        }
    }
}
void Arbre::Dessin()
{
    int hauteur;
    int largeur=1;
    int color=1;
    Noeud* ptrtmp; // pointeur tampon
    m_pConsole->gotoLigCol(ESPACEMENT_X*TAB_TAILLE+10, 1); //on place le curseur au bon endroit
    m_pConsole->setColor(COLOR_WHITE,COLOR_BLACK);
    std::cout << m_firstNoeud.m_x << "." << m_firstNoeud.m_y; // on affiche les coordonnées du dernier pion joué
    m_tabNoeuds[0].front()->antecedent=COLOR_WHITE;
    for(int i=0; i<PROFONDEUR-1; i++)
    {
        hauteur=0;
        for(auto elem : m_tabNoeuds[i]) // on parcours tous les element de la profondeur actuelle
        {
            ptrtmp=elem; //l'adresse de l'élément va dans le tampon
            for(auto elem1 : m_tabNoeuds[i+1]) // on regarde tous les noeuds à la profondeur +1
            {
                if(elem1->m_antecedent==ptrtmp) //si l'element a pour antécedent le noeud qu'on regarde
                {
                    m_pConsole->setColor(elem->antecedent,COLOR_BLACK);
                    m_pConsole->gotoLigCol(ESPACEMENT_X*TAB_TAILLE+10+largeur*10, 1+ hauteur*2); // on place le curseur la ou il faut
                    std::cout << elem1->m_x << "." << elem1->m_y << ":";
                    switch(color)
                    {
                    case 1 :
                        m_pConsole->setColor(COLOR_RED,COLOR_BLACK);
                        elem1->antecedent=COLOR_RED;
                        color++;
                        break;
                        case 2 :
                        m_pConsole->setColor(COLOR_BLUE,COLOR_BLACK);
                        elem1->antecedent=COLOR_BLUE;
                        color++;
                        break;
                        case 3 :
                        m_pConsole->setColor(COLOR_GREEN,COLOR_BLACK);
                        elem1->antecedent=COLOR_GREEN;
                        color++;
                        break;
                        case 4 :
                        m_pConsole->setColor(COLOR_YELLOW,COLOR_BLACK);
                        elem1->antecedent=COLOR_YELLOW;
                        color++;
                        break;
                        case 5 :
                        m_pConsole->setColor(COLOR_PURPLE,COLOR_BLACK);
                        elem1->antecedent=COLOR_PURPLE;
                        color++;
                        break;
                        case 6 :
                        m_pConsole->setColor(COLOR_GRAY,COLOR_BLACK);
                        elem1->antecedent=COLOR_GRAY;
                        color=1;
                      break;
                    }
                    if(i%2==1)
                    std::cout<< -(elem1->m_meilleurNombreDePion); // si c'est un coup du joueur l'ia perds des pions donc -
                    if(i%2==0)
                    std::cout<< +(elem1->m_meilleurNombreDePion); // si c'est un coup de l'ia elle gagne des pions donc +
                    hauteur++; // on incremente la hauteur pour pas que les noeuds se superposent
                }
            }

        }
        largeur++; // on avance dans la largeur de l'arbre
    }

}
void Arbre::remonterArbre()
{
    /// Traitement
    for(int profondeur = PROFONDEUR-1; profondeur > 0; profondeur--)
    {
        for(auto elem : m_tabNoeuds[profondeur])
        {
            if((elem->m_antecedent->m_tab.m_tourDeJouer == NOIR)	&& (elem->m_meilleurNombreDePion < elem->m_antecedent->m_meilleurNombreDePion)) // m_meilleurNombreDePion prend la valeur minimum si pion précédent est noir (joueur)
                elem->m_antecedent->m_meilleurNombreDePion = elem->m_meilleurNombreDePion;

            if((elem->m_antecedent->m_tab.m_tourDeJouer == BLANC)	&& (elem->m_meilleurNombreDePion > elem->m_antecedent->m_meilleurNombreDePion)) // m_meilleurNombreDePion prend la valeur maximum si pion précédent est blanc (joueur)
                elem->m_antecedent->m_meilleurNombreDePion = elem->m_meilleurNombreDePion;
        }
    }
}
