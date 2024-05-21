#pragma once
#include <string>
using namespace std;
#include "CMUgraphicsLib\CMUgraphics.h"

class game;     //forward declaration

struct point
{
	int x, y;
};

enum ShapeType
{
	//Basic shapes
	RCT,	//rectangle
	CRC,	//circle
	TRI,	//triangle

	//Composite shapes
	SIGN,	//a street sign

	//TODO: Add more types
};
enum Position { 
	INV,
	NOR 
};

//Base class for all shapes including Basic shapes, Composite shapes
class shape
{
protected:
	point RefPoint;		//Each shape must have a reference point
	point NewRef;
    game* pGame;        //pointer to game object
	color fillColor;	//shape fill color
	color borderColor;	//shape border color
	int ShapeHeight;
	int rotationCount;
	int resizeCount;
	int Type;

	double pi = 22.0 / 7.0;
	double angle[5] = { 0,  pi / 2.0,  pi, 3.0 * pi / 2.0, 2.0 * pi }; //array of angles of rotation

public:
    shape(game* r_pGame, point ref);
    virtual void draw() const=0;//for a shape to draw itself on the screen
	void setRefPoint(point p);
	point getRefPoint() const ;
	int getShapeHeight() const;


	//-- The following functions should be supported by the shape class
	//-- It should be overridden by each inherited shape
	//-- Decide the parameters that you should pass to each function	

	virtual void rotate() = 0;	//Rotate the shape

	virtual void resize(double factor) = 0;	//Resize the shape

	virtual void Up(double d);
	virtual void Down(double d);
	virtual void Right(double d) ;
	virtual void Left(double d) ;
	virtual bool Match(shape* sh)=0;
	int getType() const;
	virtual int getRotationCount() const;
	virtual int getResizeCount() const;



	//virtual void move() = 0;		//Move the shape
	//virtual void save(ofstream &OutFile) = 0;	//Save the shape parameters to the file
	//virtual void load(ifstream &Infile) = 0;	//Load the shape parameters to the file

};




