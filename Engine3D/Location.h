#ifndef LOCATION_H	
#define LOCATION_H

/**
 * Klasa przechowuje informacje na temat lokalizacji gracza i lokalizacji obiektu, ktory nalezy znalezc 
 */
class Location {
public:
	float x;
	float y;
	Location(float first, float second) {
		x = first;
		y = second;
	}
	Location() {
		x = NULL;
		y = NULL;
	}
};

#endif

