#ifndef PART_H
#define PART_H

/**
 * Klasa przechowuje informacje o tym czy konkretna czesc labiryntu jest mozliwa do przejscia
 */
class MazePart {
public:
	bool upClear;
	bool rightClear;

	MazePart(bool up, bool right) {
		upClear = up;
		rightClear = right;
	}

	MazePart() {
		upClear = NULL;
		rightClear = NULL;
	}
};

#endif
