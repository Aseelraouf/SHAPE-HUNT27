#include "shape.h"
#include "game.h"
#include "gameConfig.h"

shape::shape(game* r_pGame, point ref)
{
	RefPoint = ref;
	pGame = r_pGame;
	fillColor = config.fillColor;
	borderColor = config.penColor;
}

void shape::setRefPoint(point p)
{
	RefPoint = p;
}

point shape::getRefPoint() const
{
	return RefPoint;
}

int shape::getShapeHeight() const
{
	return ShapeHeight;
}

void shape::Up(double d) {
	point oldRefPoint = this->getRefPoint();
	point newRefPoint;
	newRefPoint.x = oldRefPoint.x;
	newRefPoint.y = oldRefPoint.y - d;

	this->setRefPoint(newRefPoint);
}

void shape::Down(double d) {
	point oldRefPoint = this->getRefPoint();
	point newRefPoint;
	newRefPoint.x = oldRefPoint.x;
	newRefPoint.y = oldRefPoint.y + d;

	this->setRefPoint(newRefPoint);
}

void shape::Right(double d) {
	point oldRefPoint = this->getRefPoint();
	point newRefPoint;
	newRefPoint.x = oldRefPoint.x + d;
	newRefPoint.y = oldRefPoint.y;

	this->setRefPoint(newRefPoint);
}

void shape::Left(double d) 
{
	point oldRefPoint = this->getRefPoint();
	point newRefPoint;
	newRefPoint.x = oldRefPoint.x - d;
	newRefPoint.y = oldRefPoint.y;

	this->setRefPoint(newRefPoint);
}

int shape::getType() const
{
	return Type;
}


int shape::getRotationCount() const
{
	return rotationCount;
}

int shape::getResizeCount() const
{
	return resizeCount;
}

