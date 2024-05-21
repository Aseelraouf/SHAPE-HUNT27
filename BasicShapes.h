//Header file for Basic shapes in the game
#pragma once
#include "shape.h"

////////////////////////////////////////////////////  class Rect  ///////////////////////////////////////
//Rectanle class
/*							wdth
					---------------------
					|					|
			hght    |		 x			|     x is the reference point of the rectangle
					|					|
					--------------------
*/


class Rect :public shape
{
	int hght, wdth; //height and width of the recangle
public:
	Rect(game* r_pGame, point ref, int r_hght, int r_wdth);


	virtual void draw() const;
	virtual void resize(double factor);
	virtual void rotate();
	int gethght() const;
	int getwdth() const;
	bool Match(shape* sh);
	void setrefPoint(point p);
	
};


////////////////////////////////////////////////////  class circle  ///////////////////////////////////////
//Reference point of the circle is its center
class circle :public shape
{
	//Add data memebrs for class circle
	int rad;
	point refPoint;
public:
	circle(game* r_pGame, point ref, int r);	//add more parameters for the constructor if needed
	virtual void draw() const;
	virtual void resize(double factor);
	virtual void rotate();
	int getrad() const;
	bool Match(shape* sh);
	void setrefPoint(point p);
};

////////////////////////////////////////////////////  triangle class  ///////////////////////////////////////

class Triangle : public shape      //ref point is the middle point of the base 
{
	int base, width;
	Position type;
	point refPoint;
public:
	Triangle(game* r_pGame, point ref, int r_lenght, Position r_t);
	virtual void draw() const;
	virtual void resize(double factor);
	virtual void rotate();
	int getbase() const;
	int getwidth() const;
	bool Match(shape* sh);
	void setrefPoint(point p);
};

