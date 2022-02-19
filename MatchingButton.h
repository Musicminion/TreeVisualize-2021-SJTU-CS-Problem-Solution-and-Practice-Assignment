#ifndef _MatchingButton_h
#define _MatchingButton_h

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/fl_ask.H>
#include <iostream>
#include "Simple_window.h"
#include "Window.h"
#include "Graph.h"
#include "std_lib_facilities.h"

using namespace Graph_lib;


static void cb(Fl_Widget* s, void* data)
{
    fl_alert("提示：将鼠标放在节点上将会自动检测并且匹配");
    
}



class MatchingButton : public Fl_Button
{
private:
    int handle(int e)
    {
        switch (e)
        {
        case  FL_ENTER:
            
            if (thisCircle != NULL && matchingCircle != NULL && thisText != NULL && matchingText != NULL)
            {
                cout << "in" << endl;
                thisCircle->set_fill_color(250);
                thisCircle->draw();
                matchingCircle->set_fill_color(250);
                matchingCircle->draw();
                thisText->draw();
                matchingText->draw();
                Fl::redraw();
            }      
            return 1;
        case  FL_LEAVE:
            
            if (thisCircle != NULL && matchingCircle != NULL && thisText != NULL && matchingText != NULL)
            {
                cout << "out" << endl;
                thisCircle->set_fill_color(254);
                thisCircle->draw();
                matchingCircle->set_fill_color(254);
                matchingCircle->draw();
                thisText->draw();
                matchingText->draw();
                Fl:redraw();
            }
            return 1;
        default: return Fl_Button::handle(e);
        }
    }
  
public:
    Graph_lib::Circle* thisCircle;
    Graph_lib::Text* thisText;
    Graph_lib::Circle* matchingCircle;  //两个指针指向对应的圆圈
    Graph_lib::Text* matchingText;
    string NodeName;

    MatchingButton(int x, int y, int w, int h, string l) : Fl_Button(x, y, w, h, "")
    {
        
        NodeName = l;
        color(254);
        thisCircle = NULL;
        matchingCircle = NULL;
        draw();
        redraw();
        
        Fl::redraw();
        
    }

    ~MatchingButton()
    {
        hide();
    }

};



#endif


