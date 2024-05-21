#include "operations.h"
#include "game.h"
#include "CompositeShapes.h"
#include "cmath"
#include "corecrt_math_defines.h"
/////////////////////////////////// class operation  //////////////////
operation::operation(game* r_pGame)
{
	pGame = r_pGame;
}


/////////////////////////////////// class operAddSign  //////////////////

operAddSign::operAddSign(game* r_pGame):operation(r_pGame)
{
}

void operAddSign::Act()
{
	window* pw = pGame->getWind();

	grid* pGrid = pGame->getGrid();
	if (pGrid->getActiveShape() == nullptr) {
		//align reference point to the nearest grid point
		int xGrid = config.RefX - config.RefX % config.gridSpacing;
		int yGrid = config.RefY - config.RefX % config.gridSpacing;

		//take the aligned point as the sign shape ref point
		point signShapeRef = { xGrid,yGrid };

		//create a sign shape
		shape* psh = new Sign(pGame, signShapeRef);

		//Add the shape to the grid

		pGrid->setActiveShape(psh);
	}
	else {
		pGame->printMessage("Delete the active shape first");
	}


}

operAddICE::operAddICE(game* r_pGame) : operation(r_pGame)
{
}

void operAddICE::Act()
{
	window* pw = pGame->getWind();
	grid* pGrid = pGame->getGrid();
	if (pGrid->getActiveShape() == nullptr) {
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;
	point triShapeRef = { xGrid,yGrid };
	shape* psh = new IceCream(pGame, triShapeRef);
	pGrid->setActiveShape(psh);
}
	else {
		pGame->printMessage("Delete the active shape first");
	}

}

operAddCar::operAddCar(game* r_pGame) : operation(r_pGame)
{
}

void operAddCar::Act()
{
	window* pw = pGame->getWind();
	grid* pGrid = pGame->getGrid();
	if (pGrid->getActiveShape() == nullptr) {
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;
	point triShapeRef = { xGrid,yGrid };
	shape* psh = new Car(pGame, triShapeRef);
	pGrid->setActiveShape(psh);
	}
	else {
		pGame->printMessage("Delete the active shape first");
	}
}

operAddHome::operAddHome(game* r_pGame) : operation(r_pGame)
{
}

void operAddHome::Act()
{
	window* pw = pGame->getWind();
	grid* pGrid = pGame->getGrid();
	if (pGrid->getActiveShape() == nullptr) {
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;
	point triShapeRef = { xGrid,yGrid };
	shape* psh = new Home(pGame, triShapeRef);
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);
}
	else {
	pGame->printMessage("Delete the active shape first");
	}
}

operAddBird::operAddBird(game* r_pGame) : operation(r_pGame)
{
}

void operAddBird::Act()
{
	window* pw = pGame->getWind();
	grid* pGrid = pGame->getGrid();
	if (pGrid->getActiveShape() == nullptr) {
		int xGrid = config.RefX - config.RefX % config.gridSpacing;
		int yGrid = config.RefY - config.RefX % config.gridSpacing;
		point triShapeRef = { xGrid,yGrid };
		shape* psh = new Bird(pGame, triShapeRef);
		pGrid->setActiveShape(psh);
	}
	else {
		pGame->printMessage("Delete the active shape first");
	}
}


operINC::operINC(game* r_pGame) : operation(r_pGame)
{
}

void operINC::Act()
{

	grid* grid = pGame->getGrid();
	shape* shape = grid->getActiveShape();
	if (config.gridHeight - shape->getShapeHeight() > 0 ) {
		shape->resize(2);
		grid->setActiveShape(shape);
	}
	else {
		pGame->printMessage("you reached the maximum");
	}
	
}

operDEC::operDEC(game* r_pGame) : operation(r_pGame)
{
}

void operDEC::Act()
{
	double scale =  0.5;
	grid* grid = pGame->getGrid();
	shape* shape = grid->getActiveShape();
	shape->resize(scale);
	grid->setActiveShape(shape);

}

operDEL::operDEL(game* r_pGame) : operation(r_pGame)
{
}

void operDEL::Act()
{
	grid* grid = pGame->getGrid();
	grid->Delshape();
}

operAddTree::operAddTree(game* r_pGame) : operation(r_pGame)
{
}

void operAddTree::Act()
{
	window* pw = pGame->getWind();
	grid* pGrid = pGame->getGrid();
	if (pGrid->getActiveShape() == nullptr) {
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;
	point triShapeRef = { xGrid,yGrid };
	shape* psh = new Tree(pGame, triShapeRef);
	pGrid->setActiveShape(psh);
	}
	else {
		pGame->printMessage("you reached the maximum");
	}
}

operROTATE::operROTATE(game* r_pGame) : operation(r_pGame)
{
}

void operROTATE::Act()
{
	grid* grid = pGame->getGrid();
	shape* shape = grid->getActiveShape();

	shape->rotate();

}
oper_MOVE_UP::oper_MOVE_UP(game* r_pGame) :operation(r_pGame)
{
}

void oper_MOVE_UP::Act() {
	grid* pGrid = pGame->getGrid();
	shape* currentShape = pGrid->getActiveShape();
	currentShape->Up(config.gridSpacing);
	pGrid->setActiveShape(currentShape);
}

oper_MOVE_DOWN::oper_MOVE_DOWN(game* r_pGame) :operation(r_pGame)
{
}

void oper_MOVE_DOWN::Act() {
	grid* pGrid = pGame->getGrid();
	shape* currentShape = pGrid->getActiveShape();
	currentShape->Down(config.gridSpacing);
	pGrid->setActiveShape(currentShape);
}

oper_MOVE_RIGHT::oper_MOVE_RIGHT(game* r_pGame) :operation(r_pGame)
{
}

void oper_MOVE_RIGHT::Act() {
	grid* pGrid = pGame->getGrid();
	shape* currentShape = pGrid->getActiveShape();
	currentShape->Right(config.gridSpacing);
	pGrid->setActiveShape(currentShape);
}

oper_MOVE_LEFT::oper_MOVE_LEFT(game* r_pGame) :operation(r_pGame)
{
}

void oper_MOVE_LEFT::Act() {
	grid* pGrid = pGame->getGrid();
	shape* currentShape = pGrid->getActiveShape();
	currentShape->Left(config.gridSpacing);
	pGrid->setActiveShape(currentShape);
}

operSAVE::operSAVE(game* r_pGame) :operation(r_pGame)
{
}

void operSAVE::Act()
{
	grid* pGrid = pGame->getGrid();
	string filename = "Save.txt";
	pGrid->saveGameProgress(filename);
}
operEXIT::operEXIT(game* r_pGame) : operation(r_pGame)
{
}

void operEXIT::Act()
{

	grid* grid = pGame->getGrid();
	shape* shape = grid->getActiveShape();
	string filename = "Save.txt";
	grid->saveGameProgress(filename);
	delete shape;
	shape = nullptr;
}

oper_Select_level::oper_Select_level(game* r_pGame) : operation(r_pGame)
{
}

void oper_Select_level::Act()
{
	grid* pGrid = pGame->getGrid();
	pGrid->selectgamelevel();
}

operLoad::operLoad(game* r_pGame) :operation(r_pGame)
{
}

void operLoad::Act()
{

	grid* pGrid = pGame->getGrid();
	string filename = "Save.txt";
	pGrid->loadGamePtogress(filename);
}

