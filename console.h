/*!
* \file Console.h
* \brief Contient la classe Console
*/

#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

#include <iostream>

/*!
* \enum Color
*
* On associe a chaque valeur une couleur dans la console
*/
enum Color
{
    COLOR_BLACK = 0, /*!< Couleur noire */
    COLOR_WHITE = 15, /*!< Couleur blanche */
    COLOR_GRAY = 8, /*!< Couleur grise */
    COLOR_RED = 12, /*!< Couleur rouge */
    COLOR_GREEN = 10, /*!< Couleur verte */
    COLOR_BLUE = 9, /*!< Couleure bleue */
    COLOR_YELLOW = 14, /*!< Couleur jaune */
    COLOR_PURPLE = 5, /*!< Couleur violette */
    COLOR_DEFAULT = 7, /*!< Couleure grise par default */
};


/*! \class Console
* \brief Gere le deplacement du curseur sur la console et sa couleur
*/
class Console
{
private:
	// Empecher la creation
	Console();
	~Console();

	// Empecher la copie d'objet...
	Console& operator= (const Console&){ return *this;}
	Console (const Console&){}

	// Attributs
	static Console* m_instance;

	// Methodes privees
	void _setColor(int front, int back);
public:
	/*!
	* \brief Retourne un pointeur
	*
	* Retourne un pointeur sur une instance console
	*/
	static Console* getInstance();

	/*!
	* \brief Libere la console
	*
	* Libere une instance de type console
	*/
	static void deleteInstance();

	// Methodes publiques
	/*!
	* \brief Deplacement curseur
	*
	* Deplace le curseur a la ligne/colonne souhaitee
	*
	* \param lig : int (ligne)
	*\param col : int (colonne)
	*/
	void gotoLigCol(int lig, int col);

	/*!
	* \brief Detecte si une touche a ete pressee
	*
	* \return true si une touche a ete pressee
	* false sinon
	*/
	bool isKeyboardPressed();

	/*!
	* \brief Retourne la touche du clavier pressee
	*
	* Retourne la touche du clavier pressee en nombre selon le code ASCII
	*
	* \return int : code ASCII
	*/
	int getInputKey();

	/*!
	* \brief Definit la couleur
	*
	* Definit la couleur de l'arriere plan et de l'ecriture
	*
	* \param ecriture : Color
	* \param arriere : Color
	*/
	void setColor(Color ecriture, Color arriere = COLOR_GRAY);

	/*!
	* \brief Retourne une couleur
	*
	* Retourne une couleur differente de la couleur donnee
	*
	*\param couleur : color
	* \return Color
	*/
	Color nextColor(Color couleur);
};

#endif // CONSOLE_H_INCLUDED
