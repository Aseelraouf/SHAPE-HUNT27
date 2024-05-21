#include "game.h"
#include "gameConfig.h"
#include <ctime>  
#include <cstdlib>



game::game() : level(1), score(0), lives(5) // Initialize level to 1, score to 0, and lives to 5

{

	//Create the main window
	createWind(config.windWidth, config.windHeight, config.wx, config.wy);

	//Create and draw the toolbar
	createToolBar();

	//Create and draw the grid
	createGrid();
	shapesGrid->draw();	//draw the grid and all shapes it contains.

	//Create and clear the status bar
	clearStatusBar();
	generateRandomShapes(level); // Adjust the level as needed


}

game::~game()
{
	delete pWind;
	delete shapesGrid;
	delete gameToolbar;

}


//////////////////////////////////////////////////////////////////////////////////////////
void game::createWind(int w, int h, int x, int y) 
{
	pWind = new window(w, h, x, y);
	pWind->SetBrush(config.bkGrndColor);
	pWind->SetPen(config.bkGrndColor, 1);
	pWind->DrawRectangle(0, 0, w, h);
}
//////////////////////////////////////////////////////////////////////////////////////////
void game::clearStatusBar() const
{
	//Clear Status bar by drawing a filled rectangle
	pWind->SetPen(config.statusBarColor, 1);
	pWind->SetBrush(config.statusBarColor);
	pWind->DrawRectangle(0, config.windHeight - config.statusBarHeight, config.windWidth, config.windHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the mode
void game::createToolBar()
{
	gameToolbar = new toolbar(this);
}

void game::createGrid()
{	
	//calc some grid parameters
	point gridUpperLeftPoint = { 0, config.toolBarHeight };
	int gridHeight = config.windHeight - config.toolBarHeight - config.statusBarHeight;
	//create the grid
	shapesGrid = new grid(gridUpperLeftPoint, config.windWidth, gridHeight, this);
}

operation* game::createRequiredOperation(toolbarItem clickedItem)
{
	operation* op=nullptr;
	switch (clickedItem)
	{
	case ITM_SIGN:
		printMessage("Sign item clicked.");
		op = new operAddSign(this);
		break;
	case ITM_Icecream :
		printMessage("Ice cream item clicked.");
		op = new operAddICE(this);
		break;
	case ITM_BIRD :
		printMessage("Bird item clicked.");
		op = new operAddBird(this);
		break;
	case ITM_CAR :
		printMessage("Car item clicked.");
		op = new operAddCar(this);
		break;
	case ITM_HOME :
		printMessage("Home item clicked.");
		op = new operAddHome(this);
		break;
	case ITM_DECREASE :
		printMessage("Decrease (-) item clicked.");
		op = new operDEC(this);
		break;
	case ITM_INCREASE :
		printMessage("Increase (+) item clicked.");
		op = new operINC(this);
		break;
	case ITM_DELETE :
		printMessage("Delete item clicked.");
		op = new operDEL(this);
		break;
	case ITM_TREE:
		printMessage("Tree item clicked.");
		op = new operAddTree(this);
		break;
	case ITM_ROTATE:
		printMessage("Rotate item clicked.");
		op = new operROTATE(this);
		break;
	case ITM_HINT:
		printMessage("Hint item clicked.");
		break;
	case ITM_REFRESH:
		printMessage("Refresh item clicked.");
		break;
	case ITM_SAVE:
		printMessage("Save item clicked.");
		op = new operSAVE(this);
		break;
	case ITM_LOAD:
		printMessage("Load item clicked.");
		op = new operLoad(this);
		break;
	case ITM_GAMELEVEL:
		printMessage("Game Level item clicked.");
		op = new oper_Select_level(this);
		break;
	case ITM_EXIT:
		printMessage("Exit item clicked.");
		op = new operEXIT(this);
		break;


	}
	return op;
}


//////////////////////////////////////////////////////////////////////////////////////////

void game::printMessage(string msg) const	//Prints a message on status bar
{
	clearStatusBar();	//First clear the status bar

	pWind->SetPen(config.penColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, config.windHeight - (int)(0.85 * config.statusBarHeight), msg);
}



window* game::getWind() const		//returns a pointer to the graphics window
{
	return pWind;
}



string game::getSrting() const
{
	string Label;
	char Key;
	keytype ktype;
	pWind->FlushKeyQueue();
	while (1)
	{
		ktype = pWind->WaitKeyPress(Key);
		if (ktype == ESCAPE)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if (Key == 8)	//BackSpace is pressed
			if (Label.size() > 0)
				Label.resize(Label.size() - 1);
			else
				Key = '\0';
		else
			Label += Key;
		printMessage(Label);
	}
}

grid* game::getGrid() const
{
	// TODO: Add your implementation code here.
	return shapesGrid;
}

////////////////////////////////////////////////////////////////////////

void game::run()
{
	//This function reads the position where the user clicks to determine the desired operation
	int x, y;
	bool isExit = false;
	operation* op;
	char keyPressed;
	//Change the title
	pWind->ChangeTitle("- 202200244- SHAPE HUNT (SEC1-T06) - 202200278 -");
	toolbarItem clickedItem = ITM_CNT;
	do
	{
		pWind->GetKeyPress(keyPressed);
		if (shapesGrid->getActiveShape() != nullptr) {
			if (keyPressed) {
				if (keyPressed == 32) // ASCII for space bar
				{
					shapesGrid->handleMatch();
				}
				if (keyPressed == 8 || keyPressed == 'w') {
					printMessage("ARROW_UP/W is being clicked");
					op = new oper_MOVE_UP(this);
					op->Act();
					shapesGrid->draw();
				}
				else if (keyPressed == 2 || keyPressed == 's') {
					printMessage("ARROW_DOWN/S is being clicked");
					op = new oper_MOVE_DOWN(this);
					op->Act();
					shapesGrid->draw();
				}
				else if (keyPressed == 6 || keyPressed == 'd') {
					printMessage("ARROW_RIGHT/D is being clicked");
					op = new oper_MOVE_RIGHT(this);
					op->Act();
					shapesGrid->draw();
				}
				else if (keyPressed == 4 || keyPressed == 'a') {
					printMessage("ARROW_LEFT/A is being clicked");
					op = new oper_MOVE_LEFT(this);
					op->Act();
					shapesGrid->draw();
				}
				
			}
		}
		
		//printMessage("Ready...");
		//1- Get user click
		pWind->GetMouseClick(x, y);	//Get the coordinates of the user click

		//2-Explain the user click
		//If user clicks on the Toolbar, ask toolbar which item is clicked
		if (y >= 0 && y < config.toolBarHeight)
		{
			clickedItem = gameToolbar->getItemClicked(x);

			//3-create the approp operation accordin to item clicked by the user
			op = createRequiredOperation(clickedItem);
			if (op)
				op->Act();

			//4-Redraw the grid after each action
			shapesGrid->draw();

		}

	} while (clickedItem != ITM_EXIT && lives > 0);
}



void game::setLevel(int newLevel)
{
	this->level = newLevel;
	int Xco = (config.toolbarItemWidth * (ITM_CNT));
	int Yco = config.toolBarHeight;
	pWind->SetPen(config.bkGrndColor, 1);
	pWind->SetBrush(config.bkGrndColor);
	pWind->DrawRectangle(Xco, 0, 1350, Yco);
	int textX2 = (ITM_CNT * config.toolbarItemWidth + (30));
	int textY2 = config.toolBarHeight / 3;

	

	pWind->SetPen(BLACK, 10);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");

	pWind->DrawString(textX2, textY2, "Level: " + std::to_string(newLevel));
	int textX = (ITM_CNT * config.toolbarItemWidth + (30));
	int textY = 0;
	pWind->DrawString(textX, textY, "Score: " + std::to_string(score));
	int textX3 = (ITM_CNT * config.toolbarItemWidth + (30));
	int textY3 = 2 * config.toolBarHeight / 3;
	pWind->DrawString(textX3, textY3, "Lives: " + std::to_string(lives));
}

void game::setScore(int newScore)  // Update score string on screen
{
	this->score = newScore;
	int Xco = (config.toolbarItemWidth * (ITM_CNT));
	int Yco = config.toolBarHeight;
	pWind->SetPen(config.bkGrndColor, 1);
	pWind->SetBrush(config.bkGrndColor);
	pWind->DrawRectangle(Xco, 0, 1350, Yco);
	

	
	pWind->SetPen(BLACK, 30);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	int textX = (ITM_CNT * config.toolbarItemWidth + (30));
	int textY = 0;
	pWind->DrawString(textX, textY, "Score: " + to_string(newScore));
	int textX3 = (ITM_CNT * config.toolbarItemWidth + (30));
	int textY3 = 2 * config.toolBarHeight / 3;
	pWind->DrawString(textX3, textY3, "Lives: " + std::to_string(lives));
	int textX2 = (ITM_CNT * config.toolbarItemWidth + (30));
	int textY2 = config.toolBarHeight / 3;
	pWind->DrawString(textX2, textY2, "Level: " + std::to_string(level));
}
void game::setLives(int newLives) {
	this->lives = newLives;

	// Update lives string on screen
	pWind->SetPen(BLACK, 30);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	int textX3 = (ITM_CNT * config.toolbarItemWidth + (30));
	int textY3 = 2 * config.toolBarHeight / 3;
	pWind->DrawString(textX3, textY3, "Lives: " + to_string(newLives));
}

void game::incrementScore(int num)
{
	score += num;
}

void game::decrementScore(int num)
{
	score -= num;
}

void game::generateRandomShapes(int level)
{
	// Seed the random number generator
	srand(time(nullptr));

	int numShapes = (2 * level) - 1;

	for (int i = 0; i < numShapes; ++i)
	{

		toolbarItem randomShape = static_cast<toolbarItem>(rand() % 5 + 1); // Randomly choose a shape type /


		int maxSize = 100; // assume maximum size is 100 

		int x = rand() % (config.windWidth) + 1;
		int y = rand() % (config.gridHeight) +1 ;
		x = x - x % config.gridSpacing;
	    y= y - y % config.gridSpacing;

		shape* newShape = nullptr;
		switch (randomShape)
		{
		case ITM_SIGN:
			newShape = new Sign(this, { x, y });
			break;
		case ITM_Icecream:
			newShape = new IceCream(this, { x, y });
			break;
		case ITM_BIRD:
			newShape = new Bird(this, { x, y });
			break;
		case ITM_CAR:
			newShape = new Car(this, { x, y });
			break;
		case ITM_HOME:
			newShape = new Home(this, { x, y });
			break;
		case ITM_TREE:
			newShape = new Home(this, { x, y });
			break;
		}

		shapesGrid->addShape(newShape);
	}

	shapesGrid->draw();


}
