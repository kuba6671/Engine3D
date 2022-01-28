#include "CreateMaze.h"


CreateMaze::CreateMaze(float height, float width) {
	goal = Location(width - 1, height - 1);		
	player = Location(0.0, 0.0);				
	srand(time(0));
	score = 0;								

	theMaze.resize(height);
	setChecker.resize(height);

	for (int counter = 0; counter < height; counter++)
	{
		theMaze[counter].resize(width, MazePart(false, false));
		setChecker[counter].resize(width, NULL);

		for (int counter2 = 0; counter2 < width; counter2++)
			setChecker[counter][counter2] = (counter * width) + counter2;
	}

	for (int counter = 0; counter < theMaze.size() * theMaze[0].size() * 10; counter++)
		makeMaze(Location(rand() % (int)theMaze[0].size(), rand() % (int)theMaze.size()));
}

bool CreateMaze::stepChecker(unsigned int dir, Location start) {
	if (dir == 0)
		return theMaze[start.y][start.x].upClear;
	else if (dir == 1)
		return theMaze[start.y][start.x].rightClear;
	else if (dir == 2 & start.y < theMaze.size() - 1)
		return theMaze[start.y + 1][start.x].upClear;
	else if (dir == 3 & start.x > 0)
		return theMaze[start.y][start.x - 1].rightClear;
	return false;
}

Location CreateMaze::partStepper(Location start, int dir) {
	if (dir == 0)
		return Location(start.x, start.y - 1);
	else if (dir == 1)
		return Location(start.x + 1, start.y);
	else if (dir == 2)
		return Location(start.x, start.y + 1);
	else if (dir == 3)
		return Location(start.x - 1, start.y);
	else
		return start;
}

bool CreateMaze::makeMaze(Location start) {
	int dir = rand() % 2;								
	int setID = setChecker[start.y][start.x];
	int newSetID;

	if ((dir == 0 && start.y == 0) || (dir == 1 && start.x == theMaze[0].size() - 1))
		return false;

	if (dir == 0) {
		newSetID = setChecker[start.y - 1][start.x];
		if (newSetID == setID)
			return false;
		theMaze[start.y][start.x].upClear = true;
	}

	if (dir == 1) {
		newSetID = setChecker[start.y][start.x + 1];
		if (newSetID == setID)
			return false;
		theMaze[start.y][start.x].rightClear = true;
	}

	for (int row = 0; row < theMaze.size(); row++)
		for (int column = 0; column < theMaze[0].size(); column++)
			if (setChecker[row][column] == setID)
				setChecker[row][column] = newSetID;
}

void CreateMaze::resetMaze() {
	for (int row = 0; row < theMaze.size(); row++)
		for (int column = 0; column < theMaze[0].size(); column++) {
			theMaze[row][column].upClear = false;
			theMaze[row][column].rightClear = false;
			setChecker[row][column] = (row * theMaze[0].size()) + column;
		}

	for (int counter = 0; counter < theMaze.size() * theMaze[0].size() * 10; counter++)
		makeMaze(Location(rand() % (int)theMaze[0].size(), rand() % (int)theMaze.size()));

	goal = Location(rand() % (int)(height() - 1), rand() % (int)(width() - 1));

	if (goal.x == player.x && goal.y == player.y)
		resetMaze();

	score++;
}

void CreateMaze::movePlayer(int dir) {
	if (stepChecker(dir, player)) {
		player = partStepper(player, dir);

		if (player.x == goal.x && player.y == goal.y)
			resetMaze();
	}
}

Location CreateMaze::findPlayer() { return player; }
float CreateMaze::height() { return theMaze.size(); }
float CreateMaze::width() { return theMaze[1].size(); }
Location CreateMaze::findGoal() { return goal; }
CreateMaze::CreateMaze() { return; }

string CreateMaze::scoreString() {
	stringstream output;
	output << "Wynik: " << score << "/3";
	return output.str();
}

int CreateMaze::getScore() {
	return score;
}







