#include "CompositeShapes.h"
#include "gameConfig.h"
#include"corecrt_math_defines.h"

////////////////////////////////////////////////////  class Sign  ///////////////////////////////////////
Sign::Sign(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	//calc the ref point of the Sign base and top rectangles relative to the Sign shape
	point topRef = ref;	//top rect ref is the same as the sign
	point baseRef = { ref.x, ref.y + config.signShape.topHeight / 2 + config.signShape.baseHeight / 2 };


	top = new Rect(pGame, topRef, config.signShape.topHeight, config.signShape.topWdth);
	base = new Rect(pGame, baseRef, config.signShape.baseHeight, config.signShape.baseWdth);
	ShapeHeight = config.signShape.baseHeight + config.signShape.topHeight;
	Type = 1;
	resizeCount = 0;
	rotationCount = 0;
}

void Sign::draw() const
{
	base->draw();
	top->draw();	
}
void Sign::rotate()
{
	rotationCount++;
	point old_point = top->getRefPoint();  // get the old point befor changing 

	base->rotate();
	top->rotate();

	double newtop_hght = top->gethght();
	double newbase_hght = base->gethght();

	if (*Sign_Rotation == angle[4]) {
		Sign_Rotation = angle + 1;
	}
	else {
		Sign_Rotation = Sign_Rotation + 1;
	}

	point baseRef;
	baseRef.x = -((0 + newtop_hght / 2.0 + newbase_hght / 2.0) * sin(*Sign_Rotation)) + old_point.x;
	baseRef.y = ((0 + newtop_hght / 2.0 + newbase_hght / 2.0) * cos(*Sign_Rotation)) + old_point.y;

	base->setRefPoint(baseRef);

}

bool Sign::Match(shape* sh)
{
	Sign* sign = dynamic_cast<Sign*> (sh);
	if (sign) {
		return base->Match(sign->base)&&top->Match(sign->top);
	}
	return false;
	
}



void Sign::resize(double factor)

{
	resizeCount++;
	point oldpoint = top->getRefPoint();
	base->resize(factor);
	top->resize(factor);
	int newtophght = top->gethght();
	int newbasehght = base->gethght();
	int newtopwdth = top->getwdth();
	int newbasewdth = base->getwdth();
	point newbaseRef{};
	if (*Sign_Rotation == angle[0] || *Sign_Rotation == angle[4])
		newbaseRef = { oldpoint.x, oldpoint.y + newtophght / 2 + newbasehght / 2 };
	else if (*Sign_Rotation == angle[1])
		newbaseRef = { oldpoint.x - newtopwdth / 2 - newbasewdth / 2, oldpoint.y };
	else if (*Sign_Rotation == angle[2])
		newbaseRef = { oldpoint.x, oldpoint.y - newtophght / 2 - newbasehght / 2 };
	else if (*Sign_Rotation == angle[3])
		newbaseRef = { oldpoint.x + newtopwdth / 2 + newbasewdth / 2, oldpoint.y };
	base->setRefPoint(newbaseRef);
	ShapeHeight = newtophght + 2 * newbasehght;
}

void Sign::Up(double d) {
	top->Up(d);
	base->Up(d);
}

void Sign::Down(double d) {
	top->Down(d);
	base->Down(d);
}
void Sign::Right(double d) {
	top->Right(d);
	base->Right(d);
}
void Sign::Left(double d) {
	top->Left(d);
	base->Left(d);
}

Rect* Sign::getTop() const
{
	return top;
}

Rect* Sign::getBase() const
{
	return base;
}




////////////////////////////////////////////////////  class Car  ///////////////////////////////////////
Car::Car(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	point topRef = ref;
	point C1Ref = { ref.x - 3 * config.carShape.topWdth / 14 , ref.y + config.carShape.topHeight / 2 + config.carShape.C1Red };
	point C2Ref = { ref.x + 3 * config.carShape.topWdth / 14 , ref.y + config.carShape.topHeight / 2 + config.carShape.C2Red };
	top = new Rect(pGame, topRef, config.carShape.topHeight, config.carShape.topWdth);
	C1 = new circle(pGame, C1Ref, config.carShape.C1Red);
	C2 = new circle(pGame, C2Ref, config.carShape.C2Red);
	ShapeHeight = 2 * config.carShape.C1Red + config.carShape.topHeight;
	Type = 2;
	resizeCount = 0;
	rotationCount = 0;
}

void Car::draw() const
{
	top->draw();
	C1->draw();
	C2->draw();
}


void Car::resize(double factor)
{
	resizeCount++;
	point oldpoint = top->getRefPoint();
	top->resize(factor);
	C1->resize(factor);
	C2->resize(factor);
	int newtopWdth = top->getwdth();
	int newtopHeight = top->gethght();
	int newC1rad = C1->getrad();
	int newC2rad = C2->getrad();
	point newC1Ref{}, newC2Ref{};
	if (*CAR_Rotation == angle[0] || *CAR_Rotation == angle[4]) {
		newC1Ref = { oldpoint.x - 3 * newtopWdth / 14 , oldpoint.y + newtopHeight / 2 + newC1rad };
		newC2Ref = { oldpoint.x + 3 * newtopWdth / 14 , oldpoint.y + newtopHeight / 2 + newC2rad };
	}
	else if (*CAR_Rotation == angle[1]) {
		newC1Ref = { oldpoint.x - newtopWdth / 2 - newC1rad , oldpoint.y + 3 * newtopHeight / 14 };
		newC2Ref = { oldpoint.x - newtopWdth / 2 - newC2rad, oldpoint.y - 3 * newtopHeight / 14 };
	}
	else if (*CAR_Rotation == angle[2]) {
		newC1Ref = { oldpoint.x - 3 * newtopWdth / 14 , oldpoint.y - newtopHeight / 2 - newC1rad };
		newC2Ref = { oldpoint.x + 3 * newtopWdth / 14 , oldpoint.y - newtopHeight / 2 - newC2rad };
	}
	else if (*CAR_Rotation == angle[3]) {
		newC1Ref = { oldpoint.x + newtopWdth / 2 + newC1rad , oldpoint.y + 3 * newtopHeight / 14 };
		newC2Ref = { oldpoint.x + newtopWdth / 2 + newC2rad, oldpoint.y - 3 * newtopHeight / 14 };
	}


	C1->setRefPoint(newC1Ref);
	C2->setRefPoint(newC2Ref);
	ShapeHeight = newtopHeight + 2 * newC1rad;

}

void Car::rotate()
{
	rotationCount++;
	point old_refcar = top->getRefPoint();

	top->rotate();
	C1->rotate();
	C2->rotate();

	

	double newtopwdth = top->getwdth();
	double newtophght = top->gethght();
	double C1_r = C1->getrad();
	double C2_r = C2->getrad();




	if (*CAR_Rotation == angle[4]) {
		CAR_Rotation = angle + 1;

	}
	else {
		CAR_Rotation = CAR_Rotation + 1;
	}

	point newC1_ref, newC2_ref;
	if (*CAR_Rotation == angle[1] || *CAR_Rotation == angle[3]) {

		newC1_ref.x = ((-3 * newtophght / 14) * cos(*CAR_Rotation) - (newtopwdth / 2 + C1_r) * sin(*CAR_Rotation)) + old_refcar.x;
		newC1_ref.y = ((-3 * newtophght / 14) * sin(*CAR_Rotation) + (newtopwdth / 2 + C2_r) * cos(*CAR_Rotation)) + old_refcar.y;

		newC2_ref.x = ((3 * newtophght / 14) * cos(*CAR_Rotation) - (newtopwdth / 2 + C1_r) * sin(*CAR_Rotation)) + old_refcar.x;
		newC2_ref.y = ((3 * newtophght / 14) * sin(*CAR_Rotation) + (newtopwdth / 2 + C2_r) * cos(*CAR_Rotation)) + old_refcar.y;
	}
	else {
		newC1_ref.x = ((-3 * newtopwdth / 14) * cos(*CAR_Rotation) - (newtophght / 2 + C1_r) * sin(*CAR_Rotation)) + old_refcar.x;
		newC1_ref.y = ((-3 * newtopwdth / 14) * sin(*CAR_Rotation) + (newtophght / 2 + C2_r) * cos(*CAR_Rotation)) + old_refcar.y;

		newC2_ref.x = ((3 * newtopwdth / 14) * cos(*CAR_Rotation) - (newtophght / 2 + C1_r) * sin(*CAR_Rotation)) + old_refcar.x;
		newC2_ref.y = ((3 * newtopwdth / 14) * sin(*CAR_Rotation) + (newtophght / 2 + C2_r) * cos(*CAR_Rotation)) + old_refcar.y;
	
	}
	C1->setRefPoint(newC1_ref);
	C2->setRefPoint(newC2_ref);
}

bool Car::Match(shape* sh)
{ 
	Car* car = dynamic_cast<Car*> (sh);
	if (car) {
		return top->Match(car->top) && C1->Match(car->C1) && C2->Match(car->C2);
	}
	return false;
}

void Car::Up(double d) {
	top->Up(d);
	C1->Up(d);
	C2->Up(d);
}

void Car::Down(double d) {
	top->Down(d);
	C1->Down(d);
	C2->Down(d);
}

void Car::Right(double d) {
	top->Right(d);
	C1->Right(d);
	C2->Right(d);
}

void Car::Left(double d) {
	top->Left(d);
	C1->Left(d);
	C2->Left(d);
}

////////////////////////////////////////////////////  class Home  ///////////////////////////////////////
Home::Home(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	point TriRef = ref;
	point RectRef = { ref.x, ref.y + config.homeShape.baseHeight / 2 };
	point FactRef = { ref.x + config.homeShape.topLenght / 2 - config.homeShape.FactWdth / 2  ,ref.y - config.homeShape.topHeight / 2 };
	top = new Triangle(pGame, TriRef, config.homeShape.topLenght, NOR);
	base = new Rect(pGame, RectRef, config.homeShape.baseHeight, config.homeShape.baseWdth);
	fact = new Rect(pGame, FactRef, config.homeShape.FactHeight, config.homeShape.FactWdth);
	ShapeHeight = config.homeShape.baseHeight + config.homeShape.topHeight;
	Type = 3;
	resizeCount = 0;
	rotationCount = 0;
}

void Home::draw() const
{
	top->draw();
	base->draw();
	fact->draw();
}

void Home::resize(double factor)
{
	resizeCount++;
	point oldpoint = top->getRefPoint();
	top->resize(factor);
	base->resize(factor);
	fact->resize(factor);
	int newbaseHeight = base->gethght();
	int newbaseWdth = base->getwdth();
	int newtopLenght = top->getbase();
	int newFactWdth = fact->getwdth();
	int newFactHeight = fact->gethght();
	point newRectRef{}, newFactRef{};
	if (*Home_Rotation == angle[0] || *Home_Rotation == angle[4]) {
		newRectRef = { oldpoint.x, oldpoint.y + newbaseHeight / 2 };
		newFactRef = { oldpoint.x + newtopLenght / 2 - newFactWdth / 2  ,oldpoint.y - newFactHeight / 2 };
	}
	else if (*Home_Rotation == angle[1]) {
		newRectRef = { oldpoint.x - (newbaseWdth / 2), oldpoint.y };
		newFactRef = { oldpoint.x + newbaseWdth / 2  ,oldpoint.y + abs(newtopLenght / 2 - newFactWdth / 2) };
	}
	else if (*Home_Rotation == angle[2]) {
		newRectRef = { oldpoint.x, oldpoint.y - abs(newbaseHeight / 2) };
		newFactRef = { oldpoint.x - abs(newtopLenght / 2 + newFactWdth / 2) ,oldpoint.y + newFactHeight / 2 };
	}
	else if (*Home_Rotation == angle[3]) {
		newRectRef = { oldpoint.x + (newbaseWdth / 2), oldpoint.y };
		newFactRef = { oldpoint.x - newbaseWdth / 2 ,oldpoint.y - abs(newtopLenght / 2 + newFactWdth / 2) };

	}


	base->setRefPoint(newRectRef);
	fact->setRefPoint(newFactRef);
	ShapeHeight = newbaseHeight + newtopLenght;


}


void Home::rotate()
{
	rotationCount++;
	point old_homeref = top->getRefPoint();


	top->rotate();
	base->rotate();
	fact->rotate();

	double newtop_l = top->getbase();
	double newtop_h = top->getwidth();
	double newbas_h = base->gethght();
	double newbas_w = base->getwdth();
	double newFact_w = fact->getwdth();
	double newFact_h = fact->gethght();



	if (*Home_Rotation == angle[4]) {
		Home_Rotation = angle + 1;

	}
	else {
		Home_Rotation = Home_Rotation + 1;
	}


	point new_RectRef, new_FactRef;
	if (*Home_Rotation == angle[1] || *Home_Rotation == angle[3])
	{
		new_RectRef.x = (0 + newbas_w / 2 * -sin(*Home_Rotation)) + old_homeref.x;
		new_RectRef.y = (0 + newbas_w / 2 * cos(*Home_Rotation)) + old_homeref.y;

		new_FactRef.x = ((0 + abs(newtop_h) / 2 - newFact_h / 2) * cos(*Home_Rotation) + (0 - abs(newtop_h) / 2) * -sin(*Home_Rotation)) + old_homeref.x;
		new_FactRef.y = ((0 + abs(newtop_h) / 2 - newFact_h / 2) * sin(*Home_Rotation) + (0 - abs(newtop_h) / 2) * cos(*Home_Rotation)) + old_homeref.y;
	}
	else
	{
		new_RectRef.x = (0 + newbas_h / 2 * -sin(*Home_Rotation)) + old_homeref.x;
		new_RectRef.y = (0 + newbas_h / 2 * cos(*Home_Rotation)) + old_homeref.y;

		new_FactRef.x = ((0 + abs(newtop_l) / 2 - newFact_w / 2) * cos(*Home_Rotation) + (0 - abs(newtop_l) / 2) * -sin(*Home_Rotation)) + old_homeref.x;
		new_FactRef.y = ((0 + abs(newtop_l) / 2 - newFact_w / 2) * sin(*Home_Rotation) + (0 - abs(newtop_l) / 2) * cos(*Home_Rotation)) + old_homeref.y;
	}
	base->setRefPoint(new_RectRef);
	fact->setRefPoint(new_FactRef);

}

bool Home::Match(shape* sh)
{
	Home* home = dynamic_cast<Home*> (sh);
	if (home) {
		return top->Match(home->top) && base->Match(home->base) && fact->Match(home->fact);
	}
	return false;
}

void Home::Up(double d) {
	top->Up(d);
	base->Up(d);
	fact->Up(d);
}

void Home::Down(double d) {
	top->Down(d);
	base->Down(d);
	fact->Down(d);
}

void Home::Right(double d) {
	top->Right(d);
	base->Right(d);
	fact->Right(d);
}

void Home::Left(double d) {
	top->Left(d);
	base->Left(d);
	fact->Left(d);
}



////////////////////////////////////////////////////  class IceCream   ///////////////////////////////////////

IceCream::IceCream(game* r_pGame, point ref) : shape(r_pGame, ref)
{
	point CirRef = ref;
	point TriRef = { ref.x, ref.y  };
	C = new circle(pGame, CirRef, config.icecreamShape.CircleRed);
	base = new Triangle(pGame, TriRef, config.icecreamShape.TriLenght, INV);
	ShapeHeight = config.icecreamShape.TriHeight + 2 * config.icecreamShape.CircleRed;
	Type = 4;
	resizeCount = 0;
	rotationCount = 0;
}

void IceCream::draw() const
{
	C->draw();
	base->draw();
}

void IceCream::resize(double factor)
{
	resizeCount++;
	base->resize(factor);
	C->resize(factor);
	int newTriangleHeight = base->getbase();
	int newred = C->getrad();
	point oldpoint = C->getRefPoint();
	point newTriRef = { };
	

	ShapeHeight = newTriangleHeight + 2 * newred;
}

void IceCream::rotate()
{
	rotationCount++;
	base->rotate();
	C->rotate();
}

bool IceCream::Match(shape* sh)
{
	IceCream* ice = dynamic_cast<IceCream*> (sh);
	if (ice) {
		return base->Match(ice->base) && C->Match(ice->C);
	}
	return false;
}

void IceCream::Up(double d) {
	base->Up(d);
	C->Up(d);
}

void IceCream::Down(double d) {
	base->Down(d);
	C->Down(d);
}

void IceCream::Left(double d) {
	base->Left(d);
	C->Left(d);
}

void IceCream::Right(double d) {
	base->Right(d);
	C->Right(d);
}
////////////////////////////////////////////////////  class Tree   ///////////////////////////////////////

Tree::Tree(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	point bottomRef = ref;
	point middleRef = { ref.x, ref.y - config.treeShape.TriangleHeight / 3 };
	point topRef = { ref.x, ref.y - 2 * config.treeShape.TriangleHeight / 3 };
	point RectRef = { ref.x, ref.y + config.treeShape.RectHeight / 2 };
	base = new Rect(pGame, RectRef, config.treeShape.RectHeight, config.treeShape.RectWdth);
	bottom = new Triangle(pGame, bottomRef, config.treeShape.TriangleLength,NOR);
	middle = new Triangle(pGame, middleRef, config.treeShape.TriangleLength,NOR);
	top = new Triangle(pGame, topRef, config.treeShape.TriangleLength,NOR);
	ShapeHeight = config.treeShape.RectHeight + 5 * config.treeShape.TriangleHeight / 3;
	Type = 5;
	resizeCount = 0;
	rotationCount = 0;
}

void Tree::draw() const
{
	base->draw();
	bottom->draw();
	middle->draw();
	top->draw();
	
}

void Tree::resize(double factor)
{
	resizeCount++;
	point oldpoint = bottom->getRefPoint();
	bottom->resize(factor);
	middle->resize(factor);
	top->resize(factor);
	base->resize(factor);
	int newTriangleHeight = bottom->getbase();
	int newTriangleWdth = bottom->getwidth();
	int newRectHeight = base->gethght();
	int newRectWdth = base->getwdth();
	point newmiddleRef{}, newtopRef{}, newRectRef{};
	if (*Tree_Rotation == angle[0] || *Tree_Rotation == angle[4]) {
		newmiddleRef = { oldpoint.x, oldpoint.y - newTriangleHeight / 3 };
		newtopRef = { oldpoint.x, oldpoint.y - 2 * newTriangleHeight / 3 };
		newRectRef = { oldpoint.x, oldpoint.y + newRectHeight / 2 };
	}
	else if (*Tree_Rotation == angle[1]) {
		newmiddleRef = { oldpoint.x + abs(newTriangleWdth / 3), oldpoint.y };
		newtopRef = { oldpoint.x + abs(2 * newTriangleWdth / 3), oldpoint.y };
		newRectRef = { oldpoint.x - newRectWdth / 2, oldpoint.y };
	}
	else if (*Tree_Rotation == angle[2]) {
		newmiddleRef = { oldpoint.x, oldpoint.y + abs(newTriangleHeight / 3) };
		newtopRef = { oldpoint.x, oldpoint.y + abs(2 * newTriangleHeight / 3) };
		newRectRef = { oldpoint.x, oldpoint.y - newRectHeight / 2 };
	}
	else if (*Tree_Rotation == angle[3]) {
		newmiddleRef = { oldpoint.x - abs(newTriangleWdth / 3), oldpoint.y };
		newtopRef = { oldpoint.x - abs(2 * newTriangleWdth / 3), oldpoint.y };
		newRectRef = { oldpoint.x + newRectWdth / 2, oldpoint.y };
	}
	base->setRefPoint(newRectRef);
	top->setRefPoint(newtopRef);
	middle->setRefPoint(newmiddleRef);
	ShapeHeight = newRectHeight + 3 * newTriangleHeight;
}


void Tree::rotate()
{
	rotationCount++;
	point old_treeref = bottom->getRefPoint();

	base->rotate();
	bottom->rotate();
	middle->rotate();
	top->rotate();

	double newtri_h = top->getbase();
	double newtri_w = top->getwidth();
	double newrect_h = base->gethght();
	double newrect_w = base->getwdth();


	if (*Tree_Rotation == angle[4]) {
		Tree_Rotation = angle + 1;

	}
	else {
		Tree_Rotation = Tree_Rotation + 1;
	}


	point new_middleRef, new_topref, new_Rectref;

	if (*Tree_Rotation == angle[4] || *Tree_Rotation == angle[2])
	{
		new_middleRef.x = (0 - (abs(newtri_h) / 3) * (-sin(*Tree_Rotation))) + old_treeref.x;
		new_middleRef.y = (0 - (abs(newtri_h) / 3) * (cos(*Tree_Rotation))) + old_treeref.y;

		new_topref.x = (0 - (2 * abs(newtri_h) / 3) * (-sin(*Tree_Rotation))) + old_treeref.x;
		new_topref.y = (0 - (2 * abs(newtri_h) / 3) * (cos(*Tree_Rotation))) + old_treeref.y;

		new_Rectref.x = (0 + (newrect_h / 2) * (-sin(*Tree_Rotation))) + old_treeref.x;
		new_Rectref.y = (0 + (newrect_h / 2) * (cos(*Tree_Rotation))) + old_treeref.y;
	}
	else
	{
		new_middleRef.x = (0 - (abs(newtri_w) / 3) * (-sin(*Tree_Rotation))) + old_treeref.x;
		new_middleRef.y = (0 - (abs(newtri_w) / 3) * (cos(*Tree_Rotation))) + old_treeref.y;

		new_topref.x = (0 - (2 * abs(newtri_w) / 3) * (-sin(*Tree_Rotation))) + old_treeref.x;
		new_topref.y = (0 - (2 * abs(newtri_w) / 3) * (cos(*Tree_Rotation))) + old_treeref.y;

		new_Rectref.x = (0 + (newrect_w / 2) * (-sin(*Tree_Rotation))) + old_treeref.x;
		new_Rectref.y = (0 + (newrect_w / 2) * (cos(*Tree_Rotation))) + old_treeref.y;
	}
	
	middle->setRefPoint(new_middleRef);
	top->setRefPoint(new_topref);
	base->setRefPoint(new_Rectref);

	
}
bool Tree::Match(shape* sh)
{
	Tree* tree = dynamic_cast<Tree*> (sh);
	if (tree) {
		return base->Match(tree->base) && bottom->Match(tree->bottom) && middle->Match(tree->middle) && top->Match(tree->top);
	}
	return false;
}
void Tree::Up(double d) {
	bottom->Up(d);
	middle->Up(d);
	top->Up(d);
	base->Up(d);

}
void Tree::Down(double d) {
	bottom->Down(d);
	middle->Down(d);
	top->Down(d);
	base->Down(d);

}
void Tree::Left(double d) {
	bottom->Left(d);
	middle->Left(d);
	top->Left(d);
	base->Left(d);

}

void Tree::Right(double d) {
	bottom->Right(d);
	middle->Right(d);
	top->Right(d);
	base->Right(d);

}
////////////////////////////////////////////////////  class Bird   ///////////////////////////////////////

Bird::Bird(game* r_pGame, point ref) : shape(r_pGame, ref)
{


	point TriLeft = { ref.x - config.birdShape.TriLenght / 2 , ref.y - config.birdShape.RectHeight / 2 };;
	point TriRight = { ref.x + config.birdShape.TriLenght / 2,ref.y - config.birdShape.RectHeight / 2 };
	point RectRef = ref;
	point CircleRef = { ref.x - config.birdShape.TriLenght , ref.y };
	point InvTriLeft = { ref.x - config.birdShape.TriLenght / 2 , ref.y + config.birdShape.RectHeight / 2 };
	point InvTriRight = { ref.x + config.birdShape.TriLenght / 2 , ref.y + config.birdShape.RectHeight / 2 };
	C = new circle(pGame, CircleRef, config.birdShape.Cred);
	main = new Rect(pGame, RectRef, config.birdShape.RectHeight, config.birdShape.RectWdth);
	Tl = new Triangle(pGame, TriLeft, config.birdShape.TriLenght, NOR);
	Tr = new Triangle(pGame, TriRight, config.birdShape.TriLenght, NOR);
	ITl = new Triangle(pGame, InvTriLeft, config.birdShape.TriLenght, INV);
	ITr = new Triangle(pGame, InvTriRight, config.birdShape.TriLenght, INV);
	ShapeHeight = config.birdShape.RectHeight + 2 * config.birdShape.TriHeight;
	Type = 6;
	resizeCount = 0;
	rotationCount = 0;

}

void Bird::draw() const
{
	C->draw();
	main->draw();
	Tl->draw();
	Tr->draw();
	ITl->draw();
	ITr->draw();
}

void Bird::resize(double factor)
{
	resizeCount++;
	point oldpoint = main->getRefPoint();
	C->resize(factor);
	main->resize(factor);
	Tl->resize(factor);
	Tr->resize(factor);
	ITl->resize(factor);
	ITr->resize(factor);
	int newTriLenght = Tl->getbase();
	int newTriWdth = Tl->getwidth();
	int newRectHeight = main->gethght();
	int newRectWdth = main->getwdth();
	point TriLeft{}, TriRight{}, CircleRef{}, InvTriLeft{}, InvTriRight{};
	if (*Bird_Rotation == angle[0] || *Bird_Rotation == angle[4]) {
		TriLeft = { oldpoint.x - newTriLenght / 2 , oldpoint.y - newRectHeight / 2 };;
		TriRight = { oldpoint.x + newTriLenght / 2,oldpoint.y - newRectHeight / 2 };
		CircleRef = { oldpoint.x - newTriLenght , oldpoint.y };
		InvTriLeft = { oldpoint.x - newTriLenght / 2 , oldpoint.y + newRectHeight / 2 };
		InvTriRight = { oldpoint.x + newTriLenght / 2 , oldpoint.y + newRectHeight / 2 };
	}
	else if (*Bird_Rotation == angle[1]) {
		TriLeft = { oldpoint.x + newRectWdth / 2 , oldpoint.y + newTriWdth / 2 };;
		TriRight = { oldpoint.x + newRectWdth / 2,oldpoint.y - newTriWdth / 2 };
		CircleRef = { oldpoint.x  , oldpoint.y - newRectHeight / 2 };
		InvTriLeft = { oldpoint.x - newRectWdth / 2 , oldpoint.y + newTriWdth / 2 };
		InvTriRight = { oldpoint.x - newRectWdth / 2 , oldpoint.y - newTriWdth / 2 };
	}
	else if (*Bird_Rotation == angle[2]) {
		TriLeft = { oldpoint.x - newTriLenght / 2 , oldpoint.y + newRectHeight / 2 };;
		TriRight = { oldpoint.x + newTriLenght / 2,oldpoint.y + newRectHeight / 2 };
		CircleRef = { oldpoint.x - newTriLenght , oldpoint.y };
		InvTriLeft = { oldpoint.x - newTriLenght / 2 , oldpoint.y - newRectHeight / 2 };
		InvTriRight = { oldpoint.x + newTriLenght / 2 , oldpoint.y - newRectHeight / 2 };
	}
	else if (*Bird_Rotation == angle[3]) {
		TriLeft = { oldpoint.x - newRectWdth / 2 , oldpoint.y + newTriWdth / 2 };;
		TriRight = { oldpoint.x - newRectWdth / 2,oldpoint.y - newTriWdth / 2 };
		CircleRef = { oldpoint.x  , oldpoint.y + newRectHeight / 2 };
		InvTriLeft = { oldpoint.x + newRectWdth / 2 , oldpoint.y + newTriWdth / 2 };
		InvTriRight = { oldpoint.x + newRectWdth / 2 , oldpoint.y - newTriWdth / 2 };
	}
	C->setRefPoint(CircleRef);
	Tl->setRefPoint(TriLeft);
	Tr->setRefPoint(TriRight);
	ITl->setRefPoint(InvTriLeft);
	ITr->setRefPoint(InvTriRight);
	ShapeHeight = newRectHeight + 2 * newRectHeight;

}


void Bird::rotate()
{
	rotationCount++;

	point old_birdref = main->getRefPoint();

	C->rotate();
	main->rotate();
	Tl->rotate();
	Tr->rotate();
	ITl->rotate();
	ITr->rotate();

	if (*Bird_Rotation == angle[4]) {
		Bird_Rotation = angle + 1;

	}
	else {
		Bird_Rotation = Bird_Rotation + 1;
	}

	double new_TriLenght = Tl->getwidth();
	double new_Trihight = Tl->getbase();

	double new_RectHeight = main->gethght();
	double new_Recwidth = main->getwdth();

	point new_TriLeft, new_TriRight, new_CircleRef, new_InvTriLeft, new_InvTriRight;

	if (*Bird_Rotation == angle[3] || *Bird_Rotation == angle[1])
	{
		new_TriLeft.x = (0 - abs(new_TriLenght) / 2 * cos(*Bird_Rotation) + (0 - new_Recwidth / 2 * (-sin(*Bird_Rotation)))) + old_birdref.x;
		new_TriLeft.y = (0 - abs(new_TriLenght) / 2 * sin(*Bird_Rotation) + (0 - new_Recwidth / 2 * (cos(*Bird_Rotation)))) + old_birdref.y;

		new_TriRight.x = (0 + abs(new_TriLenght) / 2 * cos(*Bird_Rotation) + (0 - new_Recwidth / 2 * (-sin(*Bird_Rotation)))) + old_birdref.x;
		new_TriRight.y = (0 + abs(new_TriLenght) / 2 * sin(*Bird_Rotation) + (0 - new_Recwidth / 2 * (cos(*Bird_Rotation)))) + old_birdref.y;

		new_CircleRef.x = (0 - abs(new_TriLenght) * cos(*Bird_Rotation)) + old_birdref.x;
		new_CircleRef.y = (0 - abs(new_TriLenght) * sin(*Bird_Rotation)) + old_birdref.y;

		new_InvTriLeft.x = (0 - abs(new_TriLenght) / 2 * cos(*Bird_Rotation) + (0 + new_Recwidth / 2 * (-sin(*Bird_Rotation)))) + old_birdref.x;
		new_InvTriLeft.y = (0 - abs(new_TriLenght) / 2 * sin(*Bird_Rotation) + (0 + new_Recwidth / 2 * (cos(*Bird_Rotation)))) + old_birdref.y;

		new_InvTriRight.x = (0 + abs(new_TriLenght) / 2 * cos(*Bird_Rotation) + (0 + new_Recwidth / 2 * (-sin(*Bird_Rotation)))) + old_birdref.x;
		new_InvTriRight.y = (0 + abs(new_TriLenght) / 2 * sin(*Bird_Rotation) + (0 + new_Recwidth / 2 * (cos(*Bird_Rotation)))) + old_birdref.y;

	}
	else
	{
		new_TriLeft.x = (0 - abs(new_Trihight) / 2 * cos(*Bird_Rotation) + (0 - new_RectHeight / 2 * (-sin(*Bird_Rotation)))) + old_birdref.x;
		new_TriLeft.y = (0 - abs(new_Trihight) / 2 * sin(*Bird_Rotation) + (0 - new_RectHeight / 2 * (cos(*Bird_Rotation)))) + old_birdref.y;

		new_TriRight.x = (0 + abs(new_Trihight) / 2 * cos(*Bird_Rotation) + (0 - new_RectHeight / 2 * (-sin(*Bird_Rotation)))) + old_birdref.x;
		new_TriRight.y = (0 + abs(new_Trihight) / 2 * sin(*Bird_Rotation) + (0 - new_RectHeight / 2 * (cos(*Bird_Rotation)))) + old_birdref.y;

		new_CircleRef.x = (0 - abs(new_Trihight) * cos(*Bird_Rotation)) + old_birdref.x;
		new_CircleRef.y = (0 - abs(new_Trihight) * sin(*Bird_Rotation)) + old_birdref.y;

		new_InvTriLeft.x = (0 - abs(new_Trihight) / 2 * cos(*Bird_Rotation) + (0 + new_RectHeight / 2 * (-sin(*Bird_Rotation)))) + old_birdref.x;
		new_InvTriLeft.y = (0 - abs(new_Trihight) / 2 * sin(*Bird_Rotation) + (0 + new_RectHeight / 2 * (cos(*Bird_Rotation)))) + old_birdref.y;

		new_InvTriRight.x = (0 + abs(new_Trihight) / 2 * cos(*Bird_Rotation) + (0 + new_RectHeight / 2 * (-sin(*Bird_Rotation)))) + old_birdref.x;
		new_InvTriRight.y = (0 + abs(new_Trihight) / 2 * sin(*Bird_Rotation) + (0 + new_RectHeight / 2 * (cos(*Bird_Rotation)))) + old_birdref.y;
	}


	C->setRefPoint(new_CircleRef);
	Tl->setRefPoint(new_TriLeft);
	Tr->setRefPoint(new_TriRight);
	ITl->setRefPoint(new_InvTriLeft);
	ITr->setRefPoint(new_InvTriRight);
}

bool Bird::Match(shape* sh)
{
	Bird* bird = dynamic_cast<Bird*> (sh);
	if (bird) {
		return C->Match(bird->C)&& main->Match(bird->main)&& Tl->Match(bird->Tl)&& Tr->Match(bird->Tr)&& ITl->Match(bird->ITl)&& ITr->Match(bird->ITr);
	}
	return false;
	
}

void Bird::Up(double d) {

	C->Up(d);
	main->Up(d);
	Tl->Up(d);
	Tr->Up(d);
	ITl->Up(d);
	ITr->Up(d);


}
void Bird::Down(double d) {

	C->Down(d);
	main->Down(d);
	Tl->Down(d);
	Tr->Down(d);
	ITl->Down(d);
	ITr->Down(d);


}
void Bird::Left(double d) {

	C->Left(d);
	main->Left(d);
	Tl->Left(d);
	Tr->Left(d);
	ITl->Left(d);
	ITr->Left(d);


}
void Bird::Right(double d) {

	C->Right(d);
	main->Right(d);
	Tl->Right(d);
	Tr->Right(d);
	ITl->Right(d);
	ITr->Right(d);


}