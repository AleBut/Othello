#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

#include <iostream>

enum Color
{
    COLOR_BLACK = 0,
    COLOR_WHITE = 15, //1,
    COLOR_GRAY = 8,
    COLOR_RED = 12, //2,
    COLOR_GREEN = 10, //3,
    COLOR_BLUE = 9, //4,
    COLOR_YELLOW = 14, //5,
    COLOR_PURPLE = 5, //6,
    COLOR_DEFAULT = 7, // gris couleur de base de la console
};

class Console
{
    private:
        // Empecher la création
        Console();
        ~Console();

        // Empecher la copie d'objet...
        Console& operator= (const Console&){ return *this;}
        Console (const Console&){}

        // Attributs
        static Console* m_instance;

        // Méthodes privées
        void _setColor(int front, int back);
    public:
        // Méthodes statiques (publiques)
        static Console* getInstance();
        static void deleteInstance();

        // Méthodes publiques
        void gotoLigCol(int lig, int col);
        bool isKeyboardPressed();
        int getInputKey();
        void setColor(Color ecriture, Color arriere);
};

#endif // CONSOLE_H_INCLUDED
