#include "toolbar.h"
#include "game.h"
//#include "grid.h"


////////////////////////////////////////////////////  class toolbar   //////////////////////////////////////////////
toolbar::toolbar(game* pG)
{	
	height = config.toolBarHeight;
	width = config.windWidth;
	this->pGame = pG;
	window* pWind = pGame->getWind();
	
	//You can draw the tool bar icons in any way you want.

	//First prepare List of images for each toolbar item
	toolbarItemImages[ITM_SIGN] = "images\\toolbarItems\\toolbar_Sign.jpg";
	toolbarItemImages[ITM_Icecream] = "images\\toolbarItems\\toolbar_ICECREAM.jpg";
	toolbarItemImages[ITM_BIRD] = "images\\toolbarItems\\toolbar_Bird.jpg";
	toolbarItemImages[ITM_HOME] = "images\\toolbarItems\\toolbar_House.jpg";
	toolbarItemImages[ITM_CAR] = "images\\toolbarItems\\toolbar_Car.jpg";
	toolbarItemImages[ITM_TREE] = "images\\toolbarItems\\toolbar_Tree.jpg";
	toolbarItemImages[ITM_INCREASE] = "images\\toolbarItems\\toolbar_Increase.jpg";
	toolbarItemImages[ITM_DECREASE] = "images\\toolbarItems\\toolbar_Decrease.jpg";
	toolbarItemImages[ITM_ROTATE] = "images\\toolbarItems\\toolbar_Rotate.jpg";
	toolbarItemImages[ITM_REFRESH] = "images\\toolbarItems\\toolbar_Refresh.jpg";
	toolbarItemImages[ITM_HINT] = "images\\toolbarItems\\toolbar_Hint.jpg";
	toolbarItemImages[ITM_DELETE] = "images\\toolbarItems\\toolbar_Delete.jpg";
	toolbarItemImages[ITM_GAMELEVEL] = "images\\toolbarItems\\toolbar_Gamelevel.jpg";
	toolbarItemImages[ITM_SAVE] = "images\\toolbarItems\\toolbar_SavenLoad.jpg";
	toolbarItemImages[ITM_LOAD]= "images\\toolbarItems\\toolbar_Load.jpg";
	toolbarItemImages[ITM_EXIT] = "images\\toolbarItems\\toolbar_Exit.jpg";

	//Draw toolbar item one image at a time
	for (int i = 0; i < ITM_CNT; i++)
		pWind->DrawImage(toolbarItemImages[i], i * config.toolbarItemWidth, 0, config.toolbarItemWidth, height);

	// Draw a line under the toolbar
	pWind->SetPen(DARKBLUE, 3);
	pWind->DrawLine(0, height, width, height);

	// Update level, score, and lives on toolbar
	updateToolbar();

	//Draw a line under the toolbar
	pWind->SetPen(DARKBLUE, 3);
	pWind->DrawLine(0, height,width , height);
}



//handles clicks on toolbar icons, returns ITM_CNT if the click is not inside the toolbar
toolbarItem toolbar::getItemClicked(int x)
{
	// Print a message in the status bar indicating the clicked item
	
	if (x > ITM_CNT * config.toolbarItemWidth)	//click outside toolbar boundaries
		return ITM_CNT;

	//Check which toolbar item was clicked
	return (toolbarItem)(x / config.toolbarItemWidth);
}

void toolbar::updateToolbar() {
	window* pWind = pGame->getWind();

	// Level
	int textX2 = (ITM_CNT * config.toolbarItemWidth + (30));
	int textY2 = config.toolBarHeight / 3;
	pWind->SetPen(BLACK, 30);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(textX2, textY2, "Level: " + to_string(pGame->getLevel()));

	// Score
	int textX = (ITM_CNT * config.toolbarItemWidth + (30));
	int textY = 0;
	pWind->DrawString(textX, textY, "Score: " + to_string(pGame->getScore()));

	// Lives
	int textX3 = (ITM_CNT * config.toolbarItemWidth + (30));
	int textY3 = 2 * config.toolBarHeight / 3;
	pWind->DrawString(textX3, textY3, "Lives: " + to_string(pGame->getLives()));
}