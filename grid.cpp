#include "grid.h"
#include "game.h"
#include "gameConfig.h"
#include <iostream>
using namespace std;

grid::grid(point r_uprleft, int wdth, int hght, game* pG)
{
	uprLeft = r_uprleft;
	height = hght;
	width = wdth;
	pGame = pG;
	rows = height / config.gridSpacing;
	cols = width / config.gridSpacing;
	shapeCount = 0;

	for (int i = 0; i < MaxShapeCount; i++)
		shapeList[i] = nullptr;

	activeShape = nullptr;

}

grid::~grid()
{
	for (int i = 0; i < shapeCount; i++)
		delete shapeList[i];
}

void grid::draw() const
{
	clearGridArea();
	window* pWind = pGame->getWind();
	
	pWind->SetPen(config.gridDotsColor,1);
	pWind->SetBrush(config.gridDotsColor);

	//draw dots showing the grid reference points
	for (int r = 1; r < rows; r++)
		for (int c = 0; c < cols; c++)
			pWind->DrawCircle(c * config.gridSpacing, r * config.gridSpacing + uprLeft.y, 1);
			

	//Draw ALL shapes
	for (int i = 0; i < shapeCount; i++)
			if (shapeList[i])
				shapeList[i]->draw();	//draw each shape

	//Draw the active shape
	if(activeShape)
		activeShape->draw();
}

void grid::clearGridArea() const
{
	window* pWind = pGame->getWind();	
	pWind->SetPen(config.bkGrndColor, 1);
	pWind->SetBrush(config.bkGrndColor);
	pWind->DrawRectangle(uprLeft.x, uprLeft.y, uprLeft.x + width, uprLeft.y + height);
}

//Adds a shape to the randomly created shapes list.
bool grid::addShape(shape* newShape)
{
	newShape->getShapeHeight();
	if (config.gridHeight - newShape->getShapeHeight() < 0) {
		return false;
	}
	else {
		shapeList[shapeCount++] = newShape;
		return true;
	}
	}
	//TODO:
	// 1- Check that the shape can be drawn witout being clipped by grid boundaries : this is done but there is an error while we run it
	// 2- check shape count doesn't exceed maximum count
	// return false if any of the checks fail

	//Here we assume that the above checks are passed

void grid::setActiveShape(shape* actShape)
{
	activeShape = actShape;
}

shape* grid::getActiveShape()
{
	return activeShape;
}

void grid::Delshape()
{
	if (activeShape != nullptr) {
		delete activeShape; 
		activeShape = nullptr;
		draw();
	}
}

shape* grid::getShapeList()
{
	return *(shapeList);
}

int grid::getShapeCount() const
{
	return shapeCount;
}
void grid::handleMatch() {
	// Loop through shapes to find if the click is inside any shape
	for (int i = 0; i < shapeCount; i++) {
		// Check if the active shape and the clicked shape match
		if (activeShape->Match(shapeList[i])) {
			// Match found, print message and delete both shapes
			pGame->printMessage("Match Successed, KEEP UP THE GOOD WORK!");
			delete activeShape;
			 delete shapeList[i];
			activeShape = nullptr;
			shapeList[i] = nullptr;
			draw();
			pGame->setScore(pGame->getScore() +2);// Redraw the grid without the deleted shapes
			shapeCount--;
			break;
		}
		else {
			// Shapes don't match, print message
			pGame->printMessage("Match Failed >> TRY AGAIN!");
			pGame->setScore(pGame->getScore()-1);
		}
	
	}
	if (shapeCount==0) {
		pGame->setLevel(pGame->getLevel() + 1);
		pGame->clearStatusBar();
		pGame->generateRandomShapes(pGame->getLevel());
		pGame->printMessage("You moved up to level" + to_string(pGame->getLevel()));

	}
	
}

void grid::selectgamelevel()
{

	pGame->printMessage("please Enter your game level");
	string slevel = pGame->getSrting();
	while (!checkdigit(slevel)) {
		pGame->printMessage("please Enter a valid number");
		slevel = pGame->getSrting();
	}

	int level = stoi(slevel);
	if (level == 0) {
		pGame->printMessage("please Enter a valid number");
		slevel = pGame->getSrting();
	}
	else
		pGame->setLevel(level);

}

bool grid::checkdigit(string s)
{
	for (int i = 0; i < s.size(); i++) {
		if (isdigit(s[i]))
			return true;
		else
			return false;

	}
}
void grid::saveGameProgress(const string& filename)
{

	ofstream outFile(filename);
	if (!outFile) {
		pGame->printMessage("Error opening file for saving game progress.");
		return;
	}
	outFile << shapeCount<<"\n";

	// Save basic game information
	outFile << pGame->getScore() << " " << pGame->getLevel() << " " << pGame->getLives() << "\n";

	// Save remaining shapes information\
	
	

	outFile << activeShape->getType() << " "
		<< activeShape->getRefPoint().x << " "
		<< activeShape->getRefPoint().y << " "
		<< activeShape->getRotationCount() << " "
		<< activeShape->getResizeCount() << "\n";

	for (int i = 0; i < shapeCount; ++i) {
		shape* shp = shapeList[i];
		outFile << shp->getType() << " "
			<< shp->getRefPoint().x << " "
			<< shp->getRefPoint().y << " "
			<< shp->getRotationCount() << " "
			<< shp->getResizeCount() << "\n";
	}
	outFile.close();
	pGame->printMessage("Game progress saved successfully.\n");
}

void grid::loadGamePtogress(const string& filename)
{
	ifstream infile(filename);
	if(!infile) {
		pGame->printMessage("Error opening file for loading game progress.");
		return;
	}
	int shapecount;
	int score, level, lives;
	infile >> shapecount;
	infile >> score >> level >> lives;
	pGame->setScore(score);
	pGame->setLevel(level);
	pGame->setLives(lives);
	int type; point refpoint; int rotationcount; int resizecount;
	infile >> type >> refpoint.x >> refpoint.y >> rotationcount >> resizecount;
	delete activeShape;

	activeShape = nullptr;
	switch (type)
	{
	case 1:
		activeShape = new Sign(pGame, refpoint);
		break;
	case 4:
		activeShape = new IceCream(pGame, refpoint);
		break;
	case 6:
		activeShape = new Bird(pGame, refpoint);
		break;
	case 2:
		activeShape = new Car(pGame, refpoint);
		break;
	case 3:
		activeShape = new Home(pGame, refpoint);
		break;
	case 5:
		activeShape = new Tree(pGame, refpoint);
		break;
	}

	setActiveShape(activeShape);
	int typelist; point refpointlist; int rotationcountlist; int resizecountlist;
	/*delete[] shapeList;
	shapeList = nullptr;*/
	for (int i = 0; i < shapecount; i++)
	{
		infile >> typelist >> refpointlist.x >> refpointlist.y >> rotationcountlist >> resizecountlist;
		switch (typelist)
		{
		case 1:
			shapeList[i] = new Sign(pGame, refpointlist);
			break;
		case 4:
			shapeList[i] = new IceCream(pGame, refpointlist);
			break;
		case 6:
			shapeList[i] = new Bird(pGame, refpointlist);
			break;
		case 2:
			shapeList[i] = new Car(pGame, refpointlist);
			break;
		case 3:
			shapeList[i] = new Home(pGame, refpointlist);
			break;
		case 5:
			shapeList[i] = new Tree(pGame, refpointlist);
			break;
		}
		addShape(shapeList[i]);
	}


	infile.close();
	shapeCount = shapecount;
	pGame->printMessage("Game progress loaded successfully.\n");
	/*clear(filename);*/
	

}




	


