#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Button.H>
#include <iostream>
#include "Interaction.h"


/**
 * Glowna klasa silnika. Inicjuje gre, zaimplementowana zostala z uzyciem wzorca projektowego singleton.
 */
class Engine
{
	static Engine* engine;

	Engine() {}
public:
	static Engine* getEngine() {
		if (!engine)
			engine = new Engine;
		return engine;
	}
	/**  
	 * Metoda inicjujaca gre
	 * \return 
	 */
	int init();
};

