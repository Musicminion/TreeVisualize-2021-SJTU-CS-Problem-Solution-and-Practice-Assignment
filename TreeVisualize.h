#ifndef _TreeVisualize_h
#define _TreeVisualize_h

#include "GUI.h"
#include "Window.h"
#include "Simple_window.h"
#include "Graph.h"
#include "Point.h"
#include "std_lib_facilities.h"
#include <time.h>
#include <string>
#include <cmath>
#include <iostream>
#include "WelcomeWin.h"


using namespace Graph_lib;


class TreeVisualize
{
	friend class WelcomeWin;

public:
	TreeVisualize();
	~TreeVisualize();

private:
	int ScreenWidth;
	int ScreenHeight;
	int if_continue;

	void GetScreenInfo();
	int WelcomePage();
	
};











#endif 

