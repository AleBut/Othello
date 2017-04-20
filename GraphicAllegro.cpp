#include "GraphicAllegro.h"
#include "Config.h"

#include <allegro.h>


void graphique::demarer_allegro()
{
    // Initialisation
    allegro_init();
    install_keyboard();
    install_mouse();

    if (install_mouse() == -1) {
        allegro_message("[Erreur fatale] Impossible d'installer la souris");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, 0);

    // OUVERTURE MODE GRAPHIQUE (ouverture fenêtre allegro)
    set_color_depth(desktop_color_depth());

    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,DIMY,DIMX,0,0)!=0)
    {
		allegro_message("[Erreur fatale] Probleme ouverture du mode graphique");
		allegro_exit();
		exit(EXIT_FAILURE);
    }

    srand ( time(NULL) );
    show_mouse(screen);
}

void graphique::afficherTablier(Tablier tab)
{
	BITMAP * PAGE, * TABLIER, * PNOIR, * PBLANC;
	PAGE	= create_bitmap(SCREEN_W,SCREEN_H);
	TABLIER	=load_bitmap("images/tablier.bmp",NULL);
	PNOIR	=load_bitmap("images/pionNoir.bmp",NULL);
	PBLANC	=load_bitmap("images/pionBlanc.bmp",NULL);

	clear_to_color(PAGE,makecol(255,255,255)); // On efface le fond blanc
	masked_blit(TABLIER,PAGE, 0,0,0,0,DIM_X_TABLIER, DIM_Y_TABLIER); // On affiche le tablier

	for(int y=0; y<TAB_TAILLE; y++)
	{
		for(int x=0; x<TAB_TAILLE; x++)
		{
			switch(tab.m_tab[x][y])
			{
			case NOIR:	draw_sprite(PAGE, PNOIR, (x*PION_TAILLE), (y*PION_TAILLE)); break;
			case BLANC:	draw_sprite(PAGE, PBLANC, (x*PION_TAILLE), (y*PION_TAILLE));break;
			default:																break;
			}
		}
	}
	blit(PAGE,screen,0,0,0,0,SCREEN_W,SCREEN_H);
}

void graphique::afficherMessage(std::string message)
{
	textprintf_ex(screen, font, GRAPH_X_MESSAGE, GRAPH_Y_MESSAGE, makecol(0,0,0), makecol(255,255,255), message.c_str());
}

void graphique::selectionCase(int &x, int &y)
{
	// Données
	int click, xClick, yClick;

	// Traitement
	while(1)
	{
		if(mouse_b&1) {
				click++;
				// En cas de clic
				if(click == 1) {
					xClick = mouse_x;
					yClick = mouse_y;

					x = (xClick - (xClick%PION_TAILLE))/PION_TAILLE;
					y = (yClick - (yClick%PION_TAILLE))/PION_TAILLE;

					if((x >= 0) && (x < TAB_TAILLE) && (y >= 0) && (y < TAB_TAILLE))
						return;
				}
		}
		else
			click = 0;
	}
}
