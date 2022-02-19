#include "WelcomeWin.h"

WelcomeWin::WelcomeWin(int scrW, int scrH)
	:Window{ Point(scrW * 0.3,scrH * 0.3),scrW * 0.4,scrH * 0.4, "Welcome!" },
	button_exit{ Point{int(0.6 * x_max()),int(0.8 * y_max())},int(0.3 * x_max()),40,"退出",
		[](Address,Address pw) {reference_to<WelcomeWin>(pw).buttonPressed_exit(); } },
	button_continue{ Point{int(0.1 * x_max()),int(0.8 * y_max())},int(0.3 * x_max()),40,"继续",
		[](Address,Address pw) {reference_to<WelcomeWin>(pw).buttonPressed_continue(); } },
	reminder(Point(int(0.05 * x_max()), int(0.1 * y_max())),"请阅读使用提醒：")
{
	ScreenWidth = scrW;
	ScreenHeight = scrH;
	
	attach(button_exit);
	attach(button_continue);
	reminder.set_color(208);
	attach(reminder);

	
	static Text contentes1(Point(int(0.05 * x_max()), int(0.2 * y_max())), "1、本程序可以读取指定格式的合法树文件，并实现可视化");
	static Text contentes2(Point(int(0.05 * x_max()), int(0.3 * y_max())), "2、请准备好输入文件，推荐使用 txt、in、csv 文件格式");
	static Text contentes3(Point(int(0.05 * x_max()), int(0.4 * y_max())), "3、将准备好的文件放在和本程序相同的目录下，可以自动检索");
	static Text contentes4(Point(int(0.05 * x_max()), int(0.5 * y_max())), "4、其他情况则需要您手动输入/粘贴目标树所在文件夹的目录");
	static Text contentes5(Point(int(0.05 * x_max()), int(0.6 * y_max())), "5、单击继续将进入全屏引导界面，单击退出将关闭程序");
	static Text contentes6(Point(int(0.05 * x_max()), int(0.7 * y_max())), "6、支持连续读取，但请不要放入文件夹");
	
	contentes1.set_color(208);
	contentes2.set_color(208);
	contentes3.set_color(208);
	contentes4.set_color(208);
	contentes5.set_color(208);
	contentes6.set_color(Color::red);

	attach(contentes1);
	attach(contentes2);
	attach(contentes3);
	attach(contentes4);
	attach(contentes5);
	attach(contentes6);
}