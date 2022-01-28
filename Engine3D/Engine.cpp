#include "Engine.h"

Interaction theInteraction;
inline void displayWrapper();
inline void mouseWrapper(int x, int y);
inline void mouse2Wrapper(int button, int state, int x, int y);
inline void spinGoalWrapper(int useless);
inline void arrowKeysWrapper(int key, int x, int y);
inline void play();
inline void mazeSize(Fl_Widget* o, void*);
inline void sphereSize(Fl_Widget* o, void*);
inline void cubeSize(Fl_Widget* o, void*);
inline void cirqueSize(Fl_Widget* o, void*);


int temp, theSize = 5, playerShape = 0;
char** temp2;

Engine* Engine::engine = 0;

int Engine::init()
{
	Fl_Window win(500, 450, "Engine 3D");

	Fl_Box title(-5, -5, 510, 50, "Labirynt!");
	title.box(FL_UP_BOX);
	title.labelsize(36);
	title.labelfont(FL_BOLD + FL_ITALIC);

	Fl_Multiline_Output desc(0, 45, 500, 250, "");
	const char* controlsText = "Aby wygrac gre nalezy 3 razy znalezc czajnik ukryty w labiryncie.\n"
		"Za kazdym razem gdy znajdziesz czajnik, labirynt sie zmienia!\n\n"
		"Sterowanie:\n"
		"Strzalki - poruszanie sie po labiryncie\n"
		"Prawy przycisk myszy - oddalenie widoku, widok z lotu ptaka\n"
		"Lewy przycisk myszy - zmiana kata kamery\n\n";
	const char* setupText = "Konfiguracja:\n"
		"Wybierz poziom trudnosci (5=latwy, 30= trudny).\n"
		"Nastepnie wybierz odpowiedni ksztalt ktorym bedziesz sie poruszal.";

	string buf(controlsText);
	buf.append(setupText);
	const char* combinedChar = buf.c_str();
	desc.value(combinedChar);

	Fl_Value_Slider sizeSlider(100, 300, 300, 50, "Rozmiar labiryntu");
	sizeSlider.type(FL_HORIZONTAL);
	sizeSlider.value(5);
	sizeSlider.minimum(5);
	sizeSlider.maximum(30);
	sizeSlider.step(1);
	sizeSlider.callback(mazeSize);

	Fl_Button sphereButton(50, 400, 120, 25, "Kula");
	sphereButton.callback(sphereSize);
	Fl_Button cubeButton(200, 400, 120, 25, "Kostka");
	cubeButton.callback(cubeSize);
	Fl_Button cirqueButton(350, 400, 120, 25, "Pierscien");
	cirqueButton.callback(cirqueSize);

	win.end();
	win.show();
	return Fl::run();

	return 0;
}

void mazeSize(Fl_Widget* o, void*) {
	Fl_Value_Slider* gettingValue = (Fl_Value_Slider*)o;
	theSize = gettingValue->value();
}

void sphereSize(Fl_Widget* o, void*) {
	playerShape = 1;
	play();
}
void cubeSize(Fl_Widget* o, void*) {
	playerShape = 2;
	play();
}
void cirqueSize(Fl_Widget* o, void*) {
	playerShape = 3;
	play();
}

void play() {
	theInteraction = Interaction(theSize, 500, 500);

	glutInit(&temp, temp2);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(100, 50);
	glutCreateWindow("Labirynt");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, 1.0, 1.0, 400.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST); glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING); glEnable(GL_COLOR_MATERIAL);

	GLfloat ambientLight[] =
	{ 0.1f, 0.1f, 0.1f, 0.1f };
	GLfloat diffuseLight[] =
	{ 0.8f, 0.8f, 0.8f, 0.0f };
	GLfloat specular[] =
	{ 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat lightPos0[] =
	{ 100.0f, 125.0f, 200.0f, 1.0f };

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight); glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular); glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	glEnable(GL_LIGHT0);

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	glutDisplayFunc(displayWrapper); glutMotionFunc(mouseWrapper);
	glutMouseFunc(mouse2Wrapper); glutSpecialFunc(arrowKeysWrapper);
	glutTimerFunc(100, spinGoalWrapper, 0);

	glLineWidth(7);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);

	theInteraction.playerObj = playerShape;
	glutMainLoop();

}
void spinGoalWrapper(int temp) {
	theInteraction.spinGoal();
	glutTimerFunc(80, spinGoalWrapper, 0);
}

void arrowKeysWrapper(int key, int x, int y) {
	theInteraction.arrowKeys(key);
}

void displayWrapper() {
	theInteraction.display();
}

void mouseWrapper(int x, int y) {
	theInteraction.mouse(x, y);
}

void mouse2Wrapper(int button, int state, int x, int y) {
	theInteraction.mouse2(button, state, x, y);
}
