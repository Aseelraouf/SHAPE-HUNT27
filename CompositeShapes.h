#pragma once
#include "Basicshapes.h"


////////////////////////////////////////////////////  class Sign  ///////////////////////////////////////
//This class reprsents the composite shape "sign"
//The sign is composed of 2 Recatngles
/*

					 ------------------
					|				   |
					|		 x		   |     x is the reference point of the Sign shape
					|			       |
					 ------------------
						   |   |
						   |   |
						   | . |
						   |   |
						   |   |
							---
*/

//Note: sign reference point is the center point of the top rectangle
class Sign :public shape
{
	Rect* base;
	Rect* top;
	double* Sign_Rotation = angle;
	//pointer to the angle in shape class ( inheritance )

public:
	Sign(game* r_pGame, point ref);
	virtual void draw() const;
	virtual void resize(double factor);
	virtual void rotate();
	virtual bool Match(shape* sh);

	void Up(double d);
	void Down(double d);
	void Right(double d);
	void Left(double d);

	Rect* getTop() const;
	Rect* getBase() const;
};
//Note: Car reference point is the center point of the rectangle
class Car :public shape
{
	Rect* top;
	circle* C1;
	circle* C2;
	double* CAR_Rotation = angle;  //pointer to the angle in shape class ( inheritance )


public:
	Car(game* r_pGame, point ref);
	virtual void draw() const;
	virtual void resize(double factor);
	virtual void rotate();
	virtual bool Match(shape* sh);

	void Up(double d);
	void Down(double d);
	void Right(double d);
	void Left(double d);

};

//Note: Home reference point is the center point of the base in the top triangle
class Home : public shape
{
	Triangle* top;
	Rect* base;
	Rect* fact;
	double* Home_Rotation = angle;  //pointer to the angle in shape class ( inheritance )

public:
	Home(game* r_pGame, point ref);
	virtual void draw() const;
	virtual void resize(double factor);
	virtual void rotate();
	virtual bool Match(shape* sh);
	void Up(double d);
	void Down(double d);
	void Right(double d);
	void Left(double d);

};

//Note: IceCream reference point is the center point of the base in the top triangle
class IceCream : public shape
{
	Triangle* base;
	circle* C;
	double* Ice_Rotation = angle;  //pointer to the angle in shape class ( inheritance )

public:
	IceCream(game* r_pGame, point ref);
	virtual void draw() const;
	virtual void resize(double factor);
	virtual void rotate();
	virtual bool Match(shape* sh);
	void Up(double d);
	void Down(double d);
	void Right(double d);
	void Left(double d);


};

//Note: Tree reference point is the center point of the base for the 1st triangle on the bottom
class Tree : public shape
{
	Triangle* bottom;
	Triangle* middle;
	Triangle* top;
	Rect* base;
	double* Tree_Rotation = angle;  //pointer to the angle in shape class ( inheritance )

public:
	Tree(game* r_pGame, point ref);
	virtual void draw() const;
	virtual void resize(double factor);
	virtual void rotate();
	virtual bool Match(shape* sh);
	void Up(double d);
	void Down(double d);
	void Right(double d);
	void Left(double d);


};

//Note: Bird reference point is the center point of the circle on the left 
class Bird : public shape
{
	circle* C;
	Rect* main;
	Triangle* Tl;
	Triangle* Tr;
	Triangle* ITl;
	Triangle* ITr;
	double* Bird_Rotation = angle;  //pointer to the angle in shape class ( inheritance )

public:
	Bird(game* r_pGame, point ref);
	virtual void draw() const;
	virtual void resize(double factor);
	virtual void rotate();
	virtual bool Match(shape* sh);
	void Up(double d);
	void Down(double d);
	void Right(double d);
	void Left(double d);

};