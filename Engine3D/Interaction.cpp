#include "Interaction.h"


void Interaction::beginText() {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
	glMatrixMode(GL_MODELVIEW);
}

void Interaction::drawBitmapString(float x, float y, float z, string score)
{
	glRasterPos3f(x, y, z);
	for (int counter = 0; score[counter] != '\0'; counter++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, score[counter]);
}

void Interaction::drawStrokeString(float x, float y, float z, string winner)
{
	zoom = 15;
	glPushMatrix();
	glColor3f(0.0, 1.0, 1.0);
	glRasterPos3f(x, y, z);
	glTranslatef(x, y, z);
	for (int counter = 0; winner[counter] != '\0'; counter++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, winner[counter]);

	glPopMatrix();
}

void Interaction::endText() {
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void Interaction::spinGoal() {
	goalSpin += 25;

	if (goalSpin > 360)
		goalSpin = goalSpin - 360;

	glutPostRedisplay();
}

Interaction::Interaction(float mazeSize, int w, int h) {
	theMaze = CreateMaze(mazeSize, mazeSize);

	height = h;
	width = w;
	zoom = 5;

	yRot = 0;
	goalSpin = 0;
	cameraDir = 0;

	prevX = 0;
	yCounter = 0;
	yChecker = 0;
}


void Interaction::display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	gluLookAt(0, sin(44.7) * zoom, cos(44.7) * zoom, 0, 0, 0, 0, 1, -1);

	glRotatef(yRot, 0, 1, 0);
	draw();
	glPopMatrix();

	beginText();
	if(theMaze.getScore() ==3)
		drawStrokeString(10, height - 300, 0, "Wygrales");
	else {
		drawBitmapString(10, height - 25, 0, "Labirynt!");
		drawBitmapString(10, height - 50, 0, theMaze.scoreString());
	}
	endText();

	glutSwapBuffers();
}


void Interaction::arrowKeys(int key) {
	if (theMaze.getScore() == 3) {}
	else
		switch (key) {
		case GLUT_KEY_UP:  
			theMaze.movePlayer((0 + cameraDir) % 4);
			glutPostRedisplay();
			break;
		case GLUT_KEY_LEFT: 
			theMaze.movePlayer((3 + cameraDir) % 4);
			glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN:  
			theMaze.movePlayer((2 + cameraDir) % 4);
			glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT: 
			theMaze.movePlayer((1 + cameraDir) % 4);
			glutPostRedisplay();
			break;
		}
}
void Interaction::mouse(int x, int y) {
	int dir = 0;

	if (yChecker > x) {
		yCounter += 1;
		dir = 1;
	}
	else {
		yCounter -= 1;
		dir = 2;
	}
	yRot = prevX + yCounter;

	if (dir == 1) {
		if (yRot >= 360)
			yRot = yRot - 360;
		if (yRot == 45 || yRot == 135 || yRot == 225 || yRot == 315)
			orientLeft();
	}
	if (dir == 2) {
		if (yRot <= 0)
			yRot = 360 - yRot;
		if (yRot == 45 || yRot == 135 || yRot == 225 || yRot == 315)
			orientRight();
	}

	yChecker = x;
}
void Interaction::mouse2(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		prevX = yRot;
		yCounter = 0;
	}
	if (button == GLUT_RIGHT_BUTTON) {
		if (state == GLUT_DOWN)
			zoom = 15;
		else
			zoom = 5;
	}
}

inline void Interaction::drawWall(float xA, float yA, float zA, float xB, float yB, float zB) {
	glNormal3f(-1, 0, 0);	
	glVertex3f(xA, yA, zA); glVertex3f(xA, yA, zB);
	glVertex3f(xA, yB, zB); glVertex3f(xA, yB, zA);
	glNormal3f(1, 0, 0);	
	glVertex3f(xB, yA, zB);	glVertex3f(xB, yA, zA);
	glVertex3f(xB, yB, zA); glVertex3f(xB, yB, zB);
	glNormal3f(0, 0, 1);	
	glVertex3f(xA, yA, zB); glVertex3f(xB, yA, zB);
	glVertex3f(xB, yB, zB); glVertex3f(xA, yB, zB);
	glNormal3f(0, 0, -1);	
	glVertex3f(xA, yA, zA); glVertex3f(xA, yB, zA);
	glVertex3f(xB, yB, zA);	glVertex3f(xB, yA, zA);
	glNormal3f(0, 1, 0); 		
	glVertex3f(xA, yB, zA); glVertex3f(xA, yB, zB);
	glVertex3f(xB, yB, zB); glVertex3f(xB, yB, zA);
}

void Interaction::draw() {
	glTranslatef(0, .5, 0);
	if (playerObj == 1) {
		glColor3f(0, 1, 1);
		glutSolidSphere(0.32f, 13, 26);
	}
	else if (playerObj == 2) {
		glColor3f(0, 1, 0);
		glutSolidCube(0.5);
	}
	else if (playerObj == 3) {
		glColor3f(0.878,0.941,0.278);
		glutSolidTorus(0.1, 0.3, 12, 12);
		
	}

	glTranslatef(-.4 - theMaze.findPlayer().x, -0.5, -.4 - theMaze.findPlayer().y);

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);

	float mazeHeight = theMaze.height();
	float mazeWidth = theMaze.width();

	drawWall(0, -0.01, -0.2, mazeWidth, 0, mazeHeight - 0.2);

	glColor3f(1, 0, 0);

	drawWall(-0.2, 0, -0.2, 0, 1, mazeHeight - .2);
	drawWall(-0.2, 0, mazeHeight - .2, mazeWidth, 1, mazeHeight);
	glEnd();

	for (int counter = 0; counter < mazeHeight; counter++) {
		for (int counter2 = 0; counter2 < mazeWidth; counter2++) {
			glBegin(GL_QUADS);
			drawWall(0.8, 0.0, -0.2, 1.0, 1.0, 0.0);
			if (!theMaze.stepChecker(0, Location(counter2, counter)))
				drawWall(0.0, 0.0, -0.2, 0.8, 1.0, 0.0);
			if (!theMaze.stepChecker(1, Location(counter2, counter)))
				drawWall(0.8, 0.0, 0.0, 1.0, 1.0, 0.8);
			glEnd();
			glTranslatef(1, 0, 0);
		}
		glTranslatef(-mazeWidth, 0, 1);
	}

	glPushMatrix();
	glTranslatef(theMaze.findGoal().x + 0.4, 0.5, theMaze.findGoal().y - theMaze.height() + 0.4);
	glColor3f(1.0, 1.0, 0.0);
	glRotatef(goalSpin, 0, 1, 0);
	glutSolidTeapot(.25);
	glPopMatrix();
	glPopMatrix();
}


void Interaction::orientRight() {
	if (cameraDir == 0)
		cameraDir = 3;
	else
		cameraDir--;
}

void Interaction::orientLeft() {
	if (cameraDir == 3)
		cameraDir = 0;
	else
		cameraDir++;
}

void Interaction::reshapeViewport(int w, int h) {
	height = h;
	width = w;
}

Interaction::Interaction() {
	return;
}

