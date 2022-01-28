#ifndef CREATEMAZE_H
#define CREATEMAZE_H

#include <iostream>
#include <string>
#include <Windows.h>
#include <GL/GL.h>
#include <GL/glut.h>
#include <utility>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <sstream>

#include "Location.h"
#include "MazePart.h"

using namespace std;


/**
 * Klasa tworzaca labirynt z wykorzystaniem algorytmu Kruskala
 */
class CreateMaze
{
private:
	/**
	 * Labirynt sklada sie z obiektow klasy MazePart
	 */
	vector<vector<MazePart> > theMaze;			
	/**
	 * vector liczb uzyty do generowania labiryntu
	 */
	vector<vector<int> > setChecker;	
	/**
	 * Lokalizacja obiektu, ktory nalezy znalezc
	 */
	Location goal;							
	/**
	 * Lokalizacja obiektu gracza
	 */
	Location player;						
	/**
	 * Metoda sluzaca do resetowania labiryntu, po znalezieniu szukanego obiektu
	 */
	void resetMaze();						
	/**
	 * Obiekty po, ktorych porusza sie gracz
	 */
	Location partStepper(Location start, int dir);	
	/**
	 * Zmienna przechowujaca aktualny wynik gracza
	 */
	int score;
public:
	CreateMaze(float height, float width);		
	/**
	 * Metoda sprawdza czy mozna sie poruszyc w danym kierunku
	 * Obsluguje wykrywanie kolizji
	 */
	bool stepChecker(unsigned int dir, Location start);	
														
	/**
	 * Metoda sluzaca do poruszania sie gracza 
	 */
	void movePlayer(int dir);							
	/**
	 * Metoda znajduje i zwraca aktualna pozycje gracza
	 */
	Location findPlayer();
	float height();
	float width();
	/**
	 * Metoda znajduje i zwraca aktualna pozycje szukanego obiektu 
	 */
	Location findGoal();
	CreateMaze();
	string scoreString();
	bool makeMaze(Location start);
	int getScore();
};

#endif
