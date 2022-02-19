#include "AnalogClock.h"


void Hands::draw_lines() const
{
	fl_color(c);
	Open_polyline::draw_lines();
}

// 命令行测试结果
void AnalogClock::print_current_time(time_t& rt)
{
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

	struct tm* timeinfo;
	timeinfo = localtime(&rt);
	
	printf("[Info]: Current local time and date: %s", asctime(timeinfo));

	//cout << timeinfo->tm_sec << endl;
}


void AnalogClock::interFace_init()
{
	Point center(xmax / 2, ymax / 2);
	static Circle clockC(center, 100);
	clockC.set_color(Color::black);
	attach(clockC);		// 圆环初始化  必须是静态变量不然会爆炸的

	tmpText.push_back(new Text(Point(30, 50), "动态闹钟——今天，你摸鱼了吗"));
	tmpText[tmpText.size() - 1].set_color(Color::red);
	tmpText[tmpText.size() - 1].set_font_size(24);
	attach(tmpText[tmpText.size() - 1]);
	

	for (int i = 0; i < 12; i++)
	{
		int r1 = 95;	// 刻度的起点
		int r2 = 100;	// 刻度的终点
		
		double rad = ((2 * 3.1415926) / 12) * i;

		Point rotated_pt1 = Point(sin(rad) * r2, -cos(rad) * r2);
		Point rotated_pt2 = Point(sin(rad) * r1, -cos(rad) * r1);

		s.push_back(new Hands(Point(rotated_pt1.x + center.x, rotated_pt1.y + center.y), Point(rotated_pt2.x + center.x, rotated_pt2.y + center.y), Color::black));
		attach(s[s.size() - 1]);
	}
	
	string str[12] = { "6","5", "4", "3", "2", "1", "12", "11", "10", "9", "8", "7" };
	
	
	int r3 = 115;	// 数字表盘
	for (int i = 0; i < 12; i++)
	{

		double rad = ((2 * 3.1415926) / 12) * i;

		tmpText.push_back(new Text(Point(center.x + sin(rad) * r3, center.y + cos(rad) * r3), str[i%12]));
		tmpText[tmpText.size() - 1].set_color(Color::black);
		attach(tmpText[tmpText.size() - 1]);

	}
	/*/
	for (int i = 0; i < 1; i++)
	{
		
		double rad = ((2 * 3.1415926) / 12) * i;
		 
		tmpText.push_back(new Text(Point(center.x + sin(rad) * r3, center.y + cos(rad) * r3), str[i]));
		tmpText[tmpText.size() - 1].set_color(Color::red);
		attach(tmpText[tmpText.size() - 1]);
		
	}
	*/
}



void AnalogClock::draw_shape()
{
	if (s.size() != 0)
	{
		for (int i = 0; i < s.size(); i++)
		{
			detach(s[i]);
		}
	}

	if (tmpText.size() != 0)
	{
		for (int i = 0; i < tmpText.size(); i++)
		{
			detach(tmpText[i]);
		}
	}



	Point center(xmax / 2, ymax / 2);

	interFace_init();


	time_t rawT;
	time(&rawT);

	struct tm* timeinfo;
	timeinfo = localtime(&rawT);
	asctime(timeinfo);

	printf("[Info]: Current local time and date: %s", asctime(timeinfo));

	Text_time_refresh();

	// 秒针
	Point origin_Pt1(0, -100);

	double rad = timeinfo->tm_sec * ((2 * 3.1415926) / 60);
	Point rotated_Pt1 = Point(cos(rad) * origin_Pt1.x - sin(rad) * origin_Pt1.y, sin(rad) * origin_Pt1.x + cos(rad) * origin_Pt1.y);

	s.push_back(new Hands(center, Point(rotated_Pt1.x + center.x, rotated_Pt1.y + center.y), Color::red));
	attach(s[s.size() - 1]);

	// 分针
	Point origin_Pt2(0, -80);

	rad = timeinfo->tm_min * ((2 * 3.1415926) / 60);
	Point rotated_Pt2 = Point(cos(rad) * origin_Pt2.x - sin(rad) * origin_Pt2.y, sin(rad) * origin_Pt2.x + cos(rad) * origin_Pt2.y);

	s.push_back(new Hands(center, Point(rotated_Pt2.x + center.x, rotated_Pt2.y + center.y), Color::blue));
	attach(s[s.size() - 1]);

	// 时针
	Point origin_Pt3(0, -60);

	rad = timeinfo->tm_hour * ((2 * 3.1415926) / 12) + (timeinfo->tm_min * ((2 * 3.1415926) / 60)) / 12;
	Point rotated_Pt3 = Point(cos(rad) * origin_Pt3.x - sin(rad) * origin_Pt3.y, sin(rad) * origin_Pt3.x + cos(rad) * origin_Pt3.y);

	s.push_back(new Hands(center, Point(rotated_Pt3.x + center.x, rotated_Pt3.y + center.y), Color::black));
	attach(s[s.size() - 1]);
}

void AnalogClock::Text_time_refresh()
{
	string strWeekday[8] = { "","一","二", "三", "四", "五", "六", "七" };
	
	
	time_t rawT;
	time(&rawT);

	struct tm* timeinfo;
	timeinfo = localtime(&rawT);
	string time_TEXT = "今天是：";
	time_TEXT += to_string(timeinfo->tm_year + 1900);
	time_TEXT += "年";
	time_TEXT += to_string(timeinfo->tm_mon + 1);
	time_TEXT += "月";
	time_TEXT += to_string(timeinfo->tm_mday);
	time_TEXT += "日   ";
	time_TEXT += to_string(timeinfo->tm_hour);
	time_TEXT += ":";
	time_TEXT += to_string(timeinfo->tm_min);
	time_TEXT += ":";
	time_TEXT += to_string(timeinfo->tm_sec);
	time_TEXT += " 星期";
	time_TEXT += strWeekday[timeinfo->tm_wday];

	tmpText.push_back(new Text(Point(60,350), time_TEXT));
	tmpText[tmpText.size() - 1].set_color(Color::blue);
	attach(tmpText[tmpText.size() - 1]);

}