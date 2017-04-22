/*!
* \file Console.cpp
* \brief Contient la description de la classe Console
*/

#include "console.h"
#include <conio.h>
#include <windows.h>

Console* Console::m_instance = NULL;

Console::Console()
{
    m_instance = NULL;
}

Console::~Console()
{

}

void Console::deleteInstance()
{
    delete m_instance;
    m_instance = NULL;
}

Console* Console::getInstance()
{
    if (!Console::m_instance)
    {
        m_instance = new Console();
    }

    return m_instance;
}

void Console::gotoLigCol(int col, int lig)
{
    COORD mycoord;
    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}

int Console::getInputKey()
{
    return getch();
}

bool Console::isKeyboardPressed()
{
    return kbhit();
}

/*
0: noir
1: bleu foncé
2: vert
3: bleu-gris
4: marron
5: pourpre
6: kaki
7: gris clair
8: gris
9: bleu
10: vert fluo
11: turquoise
12: rouge
13: rose fluo
14: jaune fluo
15: blanc
*/
void Console::_setColor(int back, int front)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,front*16+back);
}

void Console::setColor(Color ecriture, Color arriere)
{
	this->_setColor(ecriture, arriere);
}


Color Console::nextColor(Color couleur)
{
    if(couleur == COLOR_WHITE)
		return COLOR_RED;

    if(couleur == COLOR_RED)
		return COLOR_GREEN;

    if(couleur == COLOR_GREEN)
		return COLOR_BLUE;

    if(couleur == COLOR_BLUE)
		return COLOR_YELLOW;

    if(couleur == COLOR_YELLOW)
		return COLOR_PURPLE;

	if(couleur == COLOR_PURPLE)
		return COLOR_WHITE;
}
