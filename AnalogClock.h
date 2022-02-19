#ifndef _AnalogClock_h
#define _AnalogClock_h

#include "Simple_window.h"
#include "Graph.h"
#include <cmath>
#include "GUI.h"
#include <time.h>
#include <string>
#include <cmath>
#include "std_lib_facilities.h"

const int xmax = 400;
const int ymax = 400;
using namespace Graph_lib;
using namespace std;



class Hands : Open_polyline			// 闹钟的指针 时、分、秒公用一个基础类
{
	friend class AnalogClock;
public:
	Fl_Color c;
	Hands(Point start, Point end, Fl_Color color)
	{
		add(Point(start));
		add(Point(end));
		c = color;
	}
	void draw_lines() const;
};


class AnalogClock : Simple_window 
{
	friend class Hands;
public:
	AnalogClock(Point xy, int w, int h, const string& title): Simple_window(xy, w, h, title),
	quit_button(Point(x_max() - 70, 0), 70, 20, "退出", cb_quit)
	{
		attach(quit_button);

		while (true) {
			Fl::wait();		// 特别注意这里，必须wait 不然直接sleep挂起进程会导致白屏
			Sleep(1000);
			//cout << "sleep" << endl;
			draw_shape();
			Fl::redraw();
		}
	}
	void interFace_init();
	Vector_ref<Hands> s;
	Vector_ref<Text> tmpText;
	void draw_shape();
	Button quit_button;

private:
	time_t rawtime;
	bool button_pushed;
	void print_current_time(time_t& rt);
	void Text_time_refresh();	// 文字版本的时间刷新；
	static void cb_quit(Address, Address addr) { reference_to<AnalogClock>(addr).quit(); }
	void quit() { hide(); }
};

#endif