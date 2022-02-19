#include "TreeVisualize.h"
using namespace std;

TreeVisualize::TreeVisualize()
{
	// init var
	ScreenWidth = 0;
	ScreenHeight = 0;
	if_continue = 0;
	// Prog begin;
	GetScreenInfo();
	WelcomePage();
	
}

TreeVisualize::~TreeVisualize()
{

}


void TreeVisualize::GetScreenInfo()
{
	ScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	ScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);
}

int TreeVisualize::WelcomePage()
{
	
	WelcomeWin w1(ScreenWidth, ScreenHeight);
	w1.color(254);
	w1.show();
	
	return gui_main();
}
