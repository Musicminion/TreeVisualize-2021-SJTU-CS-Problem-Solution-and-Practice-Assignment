
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Text_Display.H>
#include "GUI.h"

namespace Graph_lib {

    //------------------------------------------------------------------------------

    void Button::attach(Window& win)
    {
        pw = new Fl_Button(loc.x, loc.y, width, height, label.c_str());
        pw->callback(reinterpret_cast<Fl_Callback*>(do_it), &win); // pass the window
        own = &win;
    }

    //------------------------------------------------------------------------------

    int In_box::get_int()
    {
        Fl_Input& pi = reference_to<Fl_Input>(pw);
        // return atoi(pi.value());
        const char* p = pi.value();
        if (!isdigit(p[0])) return -999999;
        return atoi(p);
    }

    //------------------------------------------------------------------------------
    /*
    string In_box::get_string()
    {
        Fl_Input& pi = reference_to<Fl_Input>(pw);
        // return atoi(pi.value());
        //const char* p = pi.value();
        string boxstr = pi.value();
        return boxstr;
    }
    */

    string In_box::get_string()
    {
        Fl_Input& pi = reference_to<Fl_Input>(pw);
        return string(pi.value());
    }
    //------------------------------------------------------------------------------

    void In_box::attach(Window& win)
    {
        pw = new Fl_Input(loc.x, loc.y, width, height, label.c_str());
        own = &win;
    }

    //------------------------------------------------------------------------------

    void Out_box::put(const string& s)
    {
        buff->append(s.c_str());
        line_NUM_ALL++;

        disp->scroll(line_NUM_ALL - 2, 0);
        // 这里我手动修改了Out box的继承属性 使其个性化的适应本大作业的需求与输出
        // 多行输出，自动统计行数，自动刷新位置保证可见最新消息
        // 通常是一次滚动对应三条消息
    }

    //------------------------------------------------------------------------------
    
    void Out_box::attach(Window& win)
    {
        disp = new Fl_Text_Display(xy_x, xy_y, ww, hh, 0);
        disp->buffer(buff);
        own = &win;
    }
    
    //------------------------------------------------------------------------------

    int Menu::attach(Button& b)
    {
        b.width = width;
        b.height = height;

        switch (k) {
        case horizontal:
            b.loc = Point(loc.x + offset, loc.y);
            offset += b.width;
            break;
        case vertical:
            b.loc = Point(loc.x, loc.y + offset);
            offset += b.height;
            break;
        }
        selection.push_back(b); // b is NOT OWNED: pass by reference
        return int(selection.size() - 1);
    }

    //------------------------------------------------------------------------------

    int Menu::attach(Button* p)
    {
        Button& b = *p;
        b.width = width;
        b.height = height;

        switch (k) {
        case horizontal:
            b.loc = Point(loc.x + offset, loc.y);
            offset += b.width;
            break;
        case vertical:
            b.loc = Point(loc.x, loc.y + offset);
            offset += b.height;
            break;
        }
        selection.push_back(&b); // b is OWNED: pass by pointer
        return int(selection.size() - 1);
    }

    //------------------------------------------------------------------------------

}; // of namespace Graph_lib
