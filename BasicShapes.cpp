#include "BasicShapes.h"
#include "gameConfig.h"
#include "game.h"
#include "cmath"
#include "corecrt_math_defines.h"

////////////////////////////////////////////////////  class Rect  ///////////////////////////////////////

Rect::Rect(game* r_pGame, point ref, int r_hght, int r_wdth) :shape(r_pGame, ref)
{
	pGame = r_pGame;
	hght = r_hght;
	wdth = r_wdth;
}

void Rect::draw() const
{
	window* pW = pGame->getWind();	//get interface window
	pW->SetPen(config.penColor, config.penWidth);
	pW->SetBrush(config.fillColor);
	point upperLeft, lowerBottom;
	upperLeft.x = RefPoint.x - wdth / 2;
	upperLeft.y = RefPoint.y - hght / 2;
	lowerBottom.x = RefPoint.x + wdth / 2;
	lowerBottom.y = RefPoint.y + hght / 2;



	pW->DrawRectangle(upperLeft.x, upperLeft.y, lowerBottom.x, lowerBottom.y, FILLED);
}

void Rect::resize(double factor)
{
	wdth *= factor;
	hght *= factor;
}


void Rect::rotate()
{
	
	double temp = wdth;
	wdth = hght;
	hght = temp;

	
}

int Rect::gethght() const
{
	return hght;
}

int Rect::getwdth() const
{
	return wdth;
}

bool Rect::Match(shape* sh)
{
	Rect* rec= dynamic_cast<Rect* > (sh);
	if (rec) {
		return RefPoint.x == rec->getRefPoint().x && RefPoint.y == rec->getRefPoint().y && hght == rec->hght && wdth == rec->wdth;
	}
	return false;
}

void Rect::setrefPoint(point p)
{
}


////////////////////////////////////////////////////  class circle  ///////////////////////////////////////

circle::circle(game* r_pGame, point ref, int r) :shape(r_pGame, ref)
{
	pGame = r_pGame;
	rad = r;
}

void circle::draw() const
{
	window* pW = pGame->getWind();	//get interface window
	pW->SetPen(borderColor, config.penWidth);
	pW->SetBrush(fillColor);
	pW->DrawCircle(RefPoint.x, RefPoint.y, rad, FILLED);
}

void circle::resize(double factor)
{
	rad *= factor;
}

void circle::rotate()
{

}

int circle::getrad() const
{
	return rad;
}

bool circle::Match(shape* sh)
{
	circle* cir = dynamic_cast<circle*> (sh);
	if (cir) {
		return RefPoint.x == cir->getRefPoint().x && RefPoint.y == cir->getRefPoint().y && rad== cir->rad;
	}
	return false;
}

void circle::setrefPoint(point p)
{
	refPoint = p;
}

////////////////////////////////////////////////////  class triangle  ///////////////////////////////////////


Triangle::Triangle(game* r_pGame, point ref, int r_lenght, Position r_t) :shape(r_pGame, ref)
{
	pGame = r_pGame;
	base = r_lenght;
	type = r_t;
	width = 0;

}

void Triangle::draw() const
{

	window* pW = pGame->getWind();
	pW->SetPen(config.penColor, config.penWidth);
	pW->SetBrush(config.fillColor);
	point baseleft, baseright, vertex; // ref point is the middle point of the base 

	


	baseleft.x = RefPoint.x - base / 2;
	baseleft.y = RefPoint.y + width / 2;
	baseright.x = RefPoint.x + base / 2;
	baseright.y = RefPoint.y - width / 2;
	vertex.x = RefPoint.x + 2 * width / 3;
	

	if (type == INV)
	{
		//vertex.y = RefPoint.y + height;
		vertex.y = RefPoint.y + sqrt(3)* base / 2;

		pW->DrawTriangle(baseleft.x, baseleft.y, baseright.x, baseright.y, vertex.x, vertex.y, FILLED);
	}
	else
	{
		//vertex.y = RefPoint.y - height;
		vertex.y = RefPoint.y - sqrt(3)* base / 2;

		pW->DrawTriangle(baseleft.x, baseleft.y, baseright.x, baseright.y, vertex.x, vertex.y, FILLED);

	}

}

void Triangle::resize(double factor)
{
	base *= factor;
	width *= factor;
}

void Triangle::rotate()
{

	if (type == INV)
	{
		int temp;
		temp = base;
		if (base != 0)
		{
			base = -width;
		}
		if (width != 0)
		{
			base = width;
		}
		width = -temp;
		draw();
	}
	else
	{
		int temp;
		temp = base;
		if (base != 0)
		{
			base = width;
		}
		if (width != 0)
		{
			base = -width;
		}
		width = temp;
		draw();
	}

	
}
int Triangle::getbase() const
{
	return base;
}
int Triangle::getwidth() const
{
	return width;
}
bool Triangle::Match(shape* sh)
{
	Triangle* tri = dynamic_cast<Triangle*> (sh);
	if (tri) {
		return RefPoint.x == tri->getRefPoint().x && RefPoint.y == tri->getRefPoint().y && base == tri->base && width == tri->width;
	}
	return false;
}

void Triangle::setrefPoint(point p)
{

}
