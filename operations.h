#pragma once
#include <ctime>
#include <random>

class game;
/////////////////////////////////// class operation  //////////////////
//Base class of all operations supported by the application
class operation
{
protected:
	game* pGame;	//pointer to the game class
public:
	operation(game* r_pGame);

	//Function Act:
	//Implements the action that should be taken by this operation
	//Should be overriden by derived classes
	virtual void Act() = 0;
};
/////////////////////////////////// class operAddSign  //////////////////
//Responsible for 
//1- collectign data about a new Sign shape to add
//2- Adding the new shape to the list of shapes (throgh the grid class)
class operAddSign:public operation
{
public:
	operAddSign(game* r_pGame);
	virtual void Act();
};
class operAddICE : public operation
{
public:
	operAddICE(game* r_pGame);
	virtual void Act();


};
class operAddCar : public operation
{
public:
	operAddCar(game* r_pGame);
	virtual void Act();


};
class operAddHome : public operation
{
public:
	operAddHome(game* r_pGame);
	virtual void Act();


};
class operAddBird : public operation
{
public:
	operAddBird(game* r_pGame);
	virtual void Act();


};

class operINC : public operation
{
public:
	operINC(game* r_pGame);
	virtual void Act();


};
class operDEC : public operation
{
public:
	operDEC(game* r_pGame);
	virtual void Act();


};
class operDEL : public operation
{
public:
	operDEL(game* r_pGame);
	virtual void Act();


};
class operAddTree : public operation
{
public:
	operAddTree(game* r_pGame);
	virtual void Act();


};

class operROTATE : public operation
{
public:
	operROTATE(game* r_pGame);
	virtual void Act();


};
class oper_MOVE_UP : public operation
{
public:
	oper_MOVE_UP(game* r_pGame);
	virtual void Act();
};

class oper_MOVE_DOWN : public operation
{
public:
	oper_MOVE_DOWN(game* r_pGame);
	virtual void Act();
};


class oper_MOVE_RIGHT : public operation
{
public:
	oper_MOVE_RIGHT(game* r_pGame);
	virtual void Act();
};


class oper_MOVE_LEFT : public operation
{
public:
	oper_MOVE_LEFT(game* r_pGame);
	virtual void Act();
};
class operSAVE : public operation
{
public:
	operSAVE(game* r_pGame);
	virtual void Act();

};
class operEXIT : public operation
{
public:
	operEXIT(game* r_pGame);
	virtual void Act();

};
class oper_Select_level : public operation {
public:
	oper_Select_level(game* r_pGame);
	virtual void Act();
};
class operLoad : public operation
{
public:
	operLoad(game* r_pGame);
	virtual void Act();

};