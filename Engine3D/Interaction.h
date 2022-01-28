#ifndef INTERACTIONE_H
#define INTERACTION_H

#include <string>
#include <Windows.h>
#include <GL/GL.h>
#include <GL/glut.h>


#include "CreateMaze.h"

class	Interaction
{
private:
	/**
	 * Glowny obiekt labiryntu
	 */
	CreateMaze theMaze;  	
	float yRot;  			
	int prevX;				
	int yCounter;			
	int yChecker;			
	double zoom;  			
	int cameraDir;  		
	int goalSpin;  			
	int height; 			
	int width; 				

	/**
	 * Metoda sluzaca do narysowania labiryntu
	 */
	void drawWall(float xA, float yA, float zA, float xB, float yB, float zB);
	void draw();

	/**
	 * Ustalenie sterowania po rotacji myszka
	 */
	void orientRight();		
	void orientLeft();		
	void beginText();
	void drawBitmapString(float x, float y, float z, string score);
	void drawStrokeString(float x, float y, float z, string score);
	void endText();

public:
	Interaction(float mazeSize, int w, int h);
	Interaction();
	void display();
	void reshapeViewport(int w, int h);

	/**
	 * Obsluga myszki
	 */
	void mouse(int x, int y);
	void mouse2(int button, int state, int x, int y);
	/**
	 * Obsluga klawiatury
	 */
	void arrowKeys(int key);

	void spinGoal();	
	int playerObj;			
};

#endif
