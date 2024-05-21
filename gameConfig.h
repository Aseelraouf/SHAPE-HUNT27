#pragma once
#include "CMUgraphicsLib/CMUgraphics.h"


//The folowing struct contains all game configurations
// (MAY be loaded from a configuration file later)
__declspec(selectany) //This line to prevent "redefinition error"
struct
{
	int	windWidth = 1200, windHeight = 600,	//Window width and height
		wx = 5, wy = 5,			//Window starting coordinates

		//The window is divded into 3 areas: toolbar, Working area, and statusbar
		toolBarHeight = 60,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		toolbarItemWidth = 65,		//Width of each icon in toolbar
		statusBarHeight = 60;	//Status Bar Height

	int remainingHeight = windHeight - toolBarHeight - statusBarHeight;

	int gridHeight = int(remainingHeight * (2 / 3.0)); 		//The grid is where bricks can be drawn

	//Default colors
	color	penColor = LIGHTGRAY,			//color used to draw borders/write messages
		fillColor = DEEPPINK,			//shapes fill color (Default)
		bkGrndColor = LAVENDER,		//Screen Background color
		statusBarColor = DEEPPINK;	//background color of the status
	int penWidth = 3;			//width of the pen that draws shapes


	color gridDotsColor = RED;
	int gridSpacing = 30;	//spacing between grid points

	////// Configuration for the composite shapes //////
	// default Ref Point for any newly created shape 
	int RefX = 810;
	int RefY = windHeight * (0.5);

	////-----  Sign Shape Confoguration ---------////
	// For the Sign shape, define width and height of both rectangles
	struct {
		int baseWdth = 20, baseHeight = 80;
		int topWdth = 100, topHeight = 50;
	}signShape;

	////-----  Car Shape Confoguration ---------////

	struct {
		int topWdth = 140, topHeight = 50;
		int C1Red = 20, C2Red = 20;
	}carShape;

	////-----  Home Shape Confoguration ---------////

	struct {
		int topLenght = 120, topHeight = 60 * sqrt(3);
		int baseWdth = 120, baseHeight = 100;
		int FactHeight = 60 * sqrt(3), FactWdth = 20;

	}homeShape;

	////-----  IceCream Shape Confoguration ---------////

	struct {
		int CircleRed = 45;
		int TriLenght = 110, TriHeight = 55 * sqrt(3);

	}icecreamShape;

	////-----  Tree Shape Confoguration ---------////

	struct {
		int TriangleHeight = 22.5* sqrt(3), TriangleLength = 45;
		int RectWdth = 10, RectHeight = 60;
	}treeShape;

	////-----  Bird Shape Confoguration ---------////
	struct {
		int Cred = 15;
		int RectWdth = 82, RectHeight = 30;
		int TriLenght = 40, TriHeight = 20 * sqrt(3);
	}birdShape;


}config;


enum toolbarItem //The items of the  toolbar (you should add more items)
{
	//Note: Items are ordered here as they appear in the toolbar
	//If you want to change the toolbar items order, just change the order here
	ITM_SIGN,		//Sign shape item
	ITM_Icecream,
	ITM_BIRD,
	ITM_HOME,
	ITM_CAR,
	ITM_TREE,
	ITM_INCREASE,
	ITM_DECREASE,
	ITM_ROTATE,
	ITM_REFRESH,
	ITM_HINT,
	ITM_DELETE,
	ITM_GAMELEVEL,
	ITM_SAVE,
	ITM_LOAD,
	ITM_EXIT,		//Exit item



	ITM_CNT		//no. of toolbar items ==> This should be the last line in this enum

};



