#ifndef _WelcomeWin_h
#define _WelcomeWin_h

#include "GUI.h"
#include "Window.h"
#include "Simple_window.h"
#include "Graph.h"
#include "Point.h"
#include <iostream>
#include "std_lib_facilities.h"
#include "VisualizeMain.h"
#include <time.h>
#include <string>
#include <cmath>


using namespace Graph_lib;

class WelcomeWin : Window
{
	friend class TreeVisualize;
public:
	WelcomeWin(int scrW, int scrH);

private:

	int ScreenWidth;
	int ScreenHeight;

	Button button_exit;
	Button button_continue;
	Text reminder;
	string infostr;

	void buttonPressed_exit() { hide(); }
	int Run_visualizeMainWindow()
	{ 
		VisualizeMain v1(ScreenWidth, ScreenHeight);
		
		return gui_main();
	}
	void buttonPressed_continue() 
	{	
		hide(); 
		Run_visualizeMainWindow();
	}
	

};

#endif


