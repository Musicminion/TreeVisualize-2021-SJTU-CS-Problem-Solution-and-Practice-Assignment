#include "VisualizeMain.h"

using namespace Graph_lib;


// 函数添加时 高优先级的函数放在前面 低优先级的放在后面 核心的按钮操作与TreeMaster函数在UI初始化后面





// -------------------------------------------UI 初始化------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------
VisualizeMain::VisualizeMain(int scrW, int scrH)
	:Window{ Point(0 ,0),scrW ,scrH , "Main" },
	button_exit{ Point{int(0.025 * x_max()),int(0.8 * y_max())},int(0.08 * x_max()),40,"退出",
		[](Address,Address pw) {reference_to<VisualizeMain>(pw).buttonPressed_exit(); } },
	button_readfileAuto{ Point{int(0.025 * x_max()),int(0.7 * y_max())},int(0.08 * x_max()),40,"自动读取文件",
		[](Address,Address pw) {reference_to<VisualizeMain>(pw).buttonPressed_readfileAuto(); } },
	button_readfileManu{ Point{int(0.025 * x_max()),int(0.6 * y_max())},int(0.08 * x_max()),40,"手动读取文件",
		[](Address,Address pw) {reference_to<VisualizeMain>(pw).buttonPressed_readfileManu(); } },
	button_refresh{ Point{int(0.025 * x_max()),int(0.5 * y_max())},int(0.08 * x_max()),40,"清空数据",
		[](Address,Address pw) {reference_to<VisualizeMain>(pw).buttonPressed_refresh(); } },
	button_nextRead{ Point{int(0.415 * x_max()),int(0.93 * y_max())},int(0.13 * x_max()),40,"继续读取队列中文件",
		[](Address,Address pw) {reference_to<VisualizeMain>(pw).buttonPressed_nextRead(); } },
	button_findRelated{ Point{int(0.8 * x_max()),int(0.93 * y_max())},int(0.1 * x_max()),40,"查找匹配节点",
		[](Address,Address pw) {reference_to<VisualizeMain>(pw).buttonPressed_findRelated(); } },
	processBar1(Point{ int(0.025 * x_max()),int(0.045 * x_max()) }, Point{ int(0.125 * x_max()),int(0.060 * x_max()) }),
	processBar2(Point{ int(0.025 * x_max()),int(0.085 * x_max()) }, Point{ int(0.125 * x_max()),int(0.100 * x_max()) }),
	processBar3(Point{ int(0.025 * x_max()),int(0.125 * x_max()) }, Point{ int(0.125 * x_max()),int(0.140 * x_max()) }),
	processBar4(Point{ int(0.025 * x_max()),int(0.165 * x_max()) }, Point{ int(0.125 * x_max()),int(0.180 * x_max()) }),
	processBar1Title(Point{ int(0.025 * x_max()),int(0.040 * x_max()) }, "文件读取与数据对接"),
	processBar2Title(Point{ int(0.025 * x_max()),int(0.080 * x_max()) }, "树的构建与可视化"),
	processBar3Title(Point{ int(0.025 * x_max()),int(0.120 * x_max()) }, "同构的判断"),
	processBar4Title(Point{ int(0.025 * x_max()),int(0.160 * x_max()) }, "同构链接的呈现"),
	inputbox(Point{ int(0.025 * x_max()),int(0.390 * y_max()) }, int(0.1 * x_max()), int(0.04 * y_max()), ""),
	inboxTitle(Point{ int(0.025 * x_max()),int(0.385 * y_max()) }, "目录输入框：(Ctrl+V)"),
	inputreminderText(Point{ int(0.008 * x_max()),int(0.450 * y_max()) }, "请粘贴目标文件夹的目录"),
	infoOutTitle(Point{ int(0.025 * x_max()),int(0.9 * y_max()) }, "信息框"),
	infoOut(Point{ int(0.025 * x_max()),int(0.905 * y_max()) }, int(0.375 * x_max()), int(0.087 * y_max()), ""),
	NodeNameIn(Point{ int(0.625 * x_max()),int(0.93 * y_max()) }, int(0.15 * x_max()), int(0.05 * y_max()), "输入节点"),
	line1(Point{ int(0.135 * x_max()),int(0.05 * y_max()) }, Point{ int(0.135 * x_max()),int(0.89 * y_max()) }),
	line2(Point{ int(0.5675 * x_max()),int(0.05 * y_max()) }, Point{ int(0.5675 * x_max()),int(0.89 * y_max()) })
{

	ScreenWidth = scrW;
	ScreenHeight = scrH;

	Tree1_height = -1;
	Tree2_height = -1;
	ifsimular = false;
	Tree1_OriginalDataError = 0;
	Tree2_OriginalDataError = 0;
	Tree1_NodeError = 0;
	Tree2_NodeError = 0;

	// 颜色初始化
	
	processBar1.set_color(Color::black);
	processBar1.set_fill_color(Color::white);
	processBar2.set_color(Color::black);
	processBar2.set_fill_color(Color::white);
	processBar3.set_color(Color::black);
	processBar3.set_fill_color(Color::white);
	processBar4.set_color(Color::black);
	processBar4.set_fill_color(Color::white);



	line1.set_color(250);
	line2.set_color(250);

	color(254);
	inputreminderText.set_color(Color::red);

	// 窗口吸附
	attach(button_exit);
	attach(button_readfileAuto);
	attach(button_readfileManu);
	attach(button_refresh);
	attach(button_nextRead);
	attach(button_findRelated);

	attach(processBar1);
	attach(processBar2);
	attach(processBar3);
	attach(processBar4);

	attach(processBar1Title);
	attach(processBar2Title);
	attach(processBar3Title);
	attach(processBar4Title);


	attach(infoOut);
	attach(inputbox);
	attach(inboxTitle);
	attach(infoOutTitle);
	attach(inputreminderText);
	attach(NodeNameIn);

	attach(line1);
	attach(line2);


	// 基础变量在这里初始化
	Tree1_iflegal = true;
	Tree2_iflegal = true;		// 先信任树的合法
	infoOut.put("[友情提示] 你好呀!欢迎使用程序 ~ 请准备好相关文件\n");
	infoOut.put("[自动读取] 说明：读取当前目录下的所有符合条件的文件\n");
	infoOut.put("[手动读取] 说明：手动粘贴树所在文件夹的目录，然后检索\n");
	
	
}

//	----------------------------------------- 按钮的控制函数和tree master函数全部在这个模块中 --------------------------------------
//	-----------------------------------------------------------------------------------------------------------------------------

void VisualizeMain::buttonPressed_exit()
{
	try {
		hide();
	}
	catch (const std::exception&)
	{
		infoOut.put("[出现错误] 程序异常无法关闭\n");
	}
	
}
void VisualizeMain::buttonPressed_readfileAuto()
{
	try
	{
		// 避免用户重复按下按钮 每次开始时刷新一次变量

		Tree1_clear();
		Tree2_clear();
		STSTEM_var_refresh();

		findCurrentPlace();
		PrimefileFocus(currentfilePlace, OriginalAllfilePlace);
		Selector(OriginalAllfilePlace, FinalPlaceResult);

		// 目录筛选完成，控制权全部交给tree master
		TreeCenterMaster();

		
	}
	catch (const std::exception&)
	{
		
		infoOut.put("[自动读取] 程序出现异常\n");
		buttonPressed_refresh();
		gui_main();

	}
	
	
	
	
}
void VisualizeMain::buttonPressed_readfileManu()
{
	try
	{
		// 避免用户重复按下按钮 每次开始时刷新一次变量
		Tree1_clear();
		Tree2_clear();
		STSTEM_var_refresh();

		ManualfilePlace = inputbox.get_string();
		if (ManualfilePlace.size() > 0)
		{
			infoOut.put("[手动读取] 目录已加载\n");
			cout << ManualfilePlace << endl;
			PrimefileFocus(ManualfilePlace, OriginalAllfilePlace);
			Selector(OriginalAllfilePlace, FinalPlaceResult);

			// 目录筛选完成，控制权全部交给tree master
			TreeCenterMaster();
		}
		else
		{
			infoOut.put("[手动读取] 目录为空，请重新输入\n");
		}

		gui_main();
	}

	catch (const std::exception&)
	{
		infoOut.put("[手动读取] 程序出现异常\n");
		buttonPressed_refresh();
		gui_main();
	}


}

void VisualizeMain::buttonPressed_refresh()
{
	try
	{
		Tree1_clear();
		Tree2_clear();
		STSTEM_var_refresh();
	}
	catch (const std::exception&)
	{

	}

}
void VisualizeMain::buttonPressed_nextRead()
{
	try
	{
		Tree1_clear();
		Tree2_clear();
		TreeCenterMaster();
	}
	catch (const std::exception&)
	{

	}

}




void VisualizeMain::buttonPressed_findRelated()
{
	try
	{
		bool iffindthis = false;
		string tmp = NodeNameIn.get_string();
		string outmes;
		if (ifsimular == true)
			infoOut.put("[匹配提示] 开始匹配 ");
		else
		{
			infoOut.put("[匹配提示] 不同构，请勿点击匹配按钮\n");
			return;
		}

		// 每次按钮颜色刷新前先要把按钮的颜色全部都初始化一次
		// 然后再去查找目标的圆圈 设置对应的颜色
		for (int i = 0; i < Tree1_Circle.size(); i++)
		{
			Tree1_Circle[i].set_fill_color(254);
			attach(Tree1_Circle[i]);
			attach(Tree1_Text[i]);
			Fl::redraw();
		}

		for (int i = 0; i < Tree2_Circle.size(); i++)
		{
			Tree2_Circle[i].set_fill_color(254);
			attach(Tree2_Circle[i]);
			attach(Tree2_Text[i]);
			Fl::redraw();
		}

		
		if ((isomorphismNameToName1_2.count(tmp)) >= 1)
		{
			outmes += tmp;
			outmes += "匹配";
			outmes += isomorphismNameToName1_2[tmp];
			outmes += " \n";

			iffindthis = true;

			for (int i = 0; i < Tree1_Circle.size(); i++)
			{
				if (Tree1_Circle[i].center().x == Tree1_NameToNode[tmp]->xxPositon && Tree1_Circle[i].center().y == Tree1_NameToNode[tmp]->yyPositon)
				{
					Tree1_Circle[i].set_fill_color(250);
				}
			}

			for (int i = 0; i < Tree2_Circle.size(); i++)
			{
				if (Tree2_Circle[i].center().x == Tree2_NameToNode[isomorphismNameToName1_2[tmp]]->xxPositon && Tree2_Circle[i].center().y == Tree2_NameToNode[isomorphismNameToName1_2[tmp]]->yyPositon)
				{
					Tree2_Circle[i].set_fill_color(250);
				}
			}
			Fl::redraw();
			infoOut.put(outmes);
			return;
		}

		if ((isomorphismNameToName2_1.count(tmp)) >= 1)
		{
			outmes += tmp;
			outmes += "匹配";
			outmes += isomorphismNameToName2_1[tmp];
			outmes += " \n";
			iffindthis = true;

			for (int i = 0; i < Tree2_Circle.size(); i++)
			{

				if (Tree2_Circle[i].center().x == Tree2_NameToNode[tmp]->xxPositon && Tree2_Circle[i].center().y == Tree2_NameToNode[tmp]->yyPositon)
				{
					Tree2_Circle[i].set_fill_color(250);
					Fl::redraw();
				}
			}

			for (int i = 0; i < Tree1_Circle.size(); i++)
			{
				if (Tree1_Circle[i].center().x == Tree1_NameToNode[isomorphismNameToName2_1[tmp]]->xxPositon && Tree1_Circle[i].center().y == Tree1_NameToNode[isomorphismNameToName2_1[tmp]]->yyPositon)
				{
					Tree1_Circle[i].set_fill_color(250);
					Fl::redraw();
				}
			}
			
			infoOut.put(outmes);
			return;
		}

		if (iffindthis == false)
		{
			outmes += "输入不对，请重新输入\n";
			infoOut.put(outmes);
			return;
		}
		
		
	}
	catch (const std::exception&)
	{

	}
}


int VisualizeMain::TreeCenterMaster()
{


	try {

		if (FinalPlaceResult.size() >= 2)
		{
			Tree1_OriginalData_Get();
			Tree2_OriginalData_Get();



			Tree1_OriginalData_Analysis();
			Tree2_OriginalData_Analysis();

			
			if (Tree1_iflegal == false || Tree2_iflegal == false)
			{
				Tree1_clear();
				Tree2_clear();
			}


			Tree1_NameToNode_Build();
			Tree2_NameToNode_Build();
			progressbar1refresh(100);
		
			Tree1_Build();
			Tree2_Build();
			

			Tree1_heightRefresh(Tree1_realRootNode, 1);
			Tree2_heightRefresh(Tree2_realRootNode, 1);

			// 警告 下面的函数必须在heightRefresh();后面调用！
			Tree1_RankInHeightRefresh();
			Tree2_RankInHeightRefresh();

			Tree1_PositionRefresh();
			Tree2_PositionRefresh();

			
			if (Tree1_iflegal == true && Tree2_iflegal == true)
			{
				ifsimular = if_isomorphism(Tree1_realRootNode, Tree2_realRootNode);
				if (ifsimular == true)
				{
					Tree_detectingAreaGenerator();
				}
				else
				{
					infoOut.put("[消息提醒] 树不同构，可视化已完成\n");
					progressbar2refresh(100);
					progressbar3refresh(100);
				}
			}

			Tree1_draw();
			Tree2_draw();

			if (ifsimular == true && Tree1_iflegal == true && Tree2_iflegal == true)
			{
				ButtonMatching();
				infoOut.put("[消息提醒] 树同构，可视化与匹配全部完成\n");
				progressbar2refresh(100);
				progressbar3refresh(100);
				progressbar4refresh(100);
			}


			if (FinalPlaceResult.size() >= 2)
			{
				string tmpinfoout = "[消息提醒] 单机继续读取将读取下一组树文件 队列中剩下文件 ";
				tmpinfoout += to_string(FinalPlaceResult.size());
				tmpinfoout += "\n";
				infoOut.put(tmpinfoout);
			}

			else
			{
				infoOut.put("[消息提醒] 队列中没有可读取的文件 单机退出可关闭 \n");
			}

		}
		else
		{
			infoOut.put("队列无可读取文件，请单击清空重新读取文件\n");
		}

		return gui_main();

	}

	catch (...)
	{
		infoOut.put("错误出现，请检查文件、树的合法性");
		buttonPressed_refresh();
	}


	return gui_main();
}












//	-----------------------------------------------------------------------------------------------------------------------------

// 初步识别文件
void VisualizeMain::PrimefileFocus(string path, vector<string>& files)
{
	try
	{
		//文件句柄  
		long hFile = 0;
		//文件信息  
		struct _finddata_t fileinfo;
		string p;
		if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
		{
			do
			{
				//如果是目录,迭代之  
				//如果不是,加入列表  
				if ((fileinfo.attrib & _A_SUBDIR))
				{

					// if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					//	PrimefileFocus(p.assign(path).append("\\").append(fileinfo.name), files);
					// 此功能已删除 不考虑子目录，否则可能会卡死
				}
				else
				{
					files.push_back(p.assign(path).append("\\").append(fileinfo.name));
				}
			} while (_findnext(hFile, &fileinfo) == 0);
			_findclose(hFile);
		}

		for (int i = 0; i < files.size(); i++)
		{
			cout << files[i] << endl;
		}
	}
	
	catch (const std::exception&)
	{
		infoOut.put("[出现错误] 文件目录检索异常，请检查文件\n");
		buttonPressed_refresh();
	}
	
}



bool VisualizeMain::if_Select(string& obj)
{
	for (int i = 0; i < obj.size(); i++)
	{
		if (obj[i] == '\0')
		{
			obj.erase(obj.begin() + i);
		}
	}

	int pointPlace = -1;
	for (int i = 1; i < 5; i++)
	{
		if (obj.size() - i >= 0 && obj[obj.size() - i] == '.')
		{
			pointPlace = obj.size() - i;
			break;
		}
	}

	if (pointPlace >= 0 && obj.size() - pointPlace > 0)
	{
		string filesort = obj.substr(pointPlace, obj.size() - pointPlace);
		//cout << filesort << endl;
		if (filesort == ".in" || filesort == ".csv" || filesort == ".txt")
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{

		return false;
	}

}


void VisualizeMain::Selector(vector<string>& beforeSel, vector<string>& AfterSel)
{
	for (int i = 0; i < beforeSel.size(); i++)
	{
		string tmpstr = beforeSel[i];
		if (if_Select(tmpstr) == true)
		{
			AfterSel.push_back(beforeSel[i]);
		}

	}
	string tmp = "[自动读取] 已经筛选出";
	tmp += to_string(AfterSel.size());
	tmp += "个文件,进入队列\n";
	infoOut.put(tmp);
	cout << "筛选出" << AfterSel.size() << endl;
}



void VisualizeMain::findCurrentPlace()
{
	try
	{
		char* buffer;
		//也可以将buffer作为输出参数
		if ((buffer = _getcwd(NULL, 0)) == NULL)
		{
			perror("getcwd error");
			infoOut.put("[自动读取] 目录获取失败,请检查操作系统权限！\n");
		}
		else
		{
			//printf("%s\n", buffer);
			currentfilePlace += buffer;
			free(buffer);
		}

		cout << currentfilePlace << endl;
		infoOut.put("[自动读取] 文件目录获取成功\n");
	}
	catch (const std::exception&)
	{
		infoOut.put("[自动读取] 目录获取失败,请检查操作系统权限！\n");
	}
	

}



void VisualizeMain::STSTEM_var_refresh()
{

	currentfilePlace.clear();
	ManualfilePlace.clear();
	OriginalAllfilePlace.clear();					// 保存原始的所有文件的目录 检索支持子目录
	FinalPlaceResult.clear();						// 保存筛选后的最终的 txt，csv，或者其他类型的树文件
	infoOut.put("[系统刷新] 系统变量刷新完成\n");
}


void VisualizeMain::Tree1_OriginalData_Get()
{
	try
	{
		ifstream tree1_ifs;
		tree1_ifs.open(FinalPlaceResult.front(), ios::in);
		if (tree1_ifs.is_open())
		{
			string buf;
			while (getline(tree1_ifs, buf))
			{
				Tree1_OriginalData.push_back(buf);
				cout << buf << endl;
				buf.clear();
			}

			FinalPlaceResult.erase(FinalPlaceResult.begin());
			infoOut.put("[文件读取] 打开第一个文件成功\n");
			
		}
		else
		{
			infoOut.put("[错误] 打开第一个文件失败\n");
		}
	}
	catch (const std::exception&)
	{
		infoOut.put("[错误] 打开第一个文件失败\n");
	}
}

void VisualizeMain::Tree2_OriginalData_Get()
{
	try
	{
		ifstream tree2_ifs;
		tree2_ifs.open(FinalPlaceResult.front(), ios::in);
		if (tree2_ifs.is_open())
		{
			string buf;
			while (getline(tree2_ifs, buf))
			{
				Tree2_OriginalData.push_back(buf);
				cout << buf << endl;
				buf.clear();
			}

			FinalPlaceResult.erase(FinalPlaceResult.begin());
			infoOut.put("[文件读取] 打开第二个文件成功\n");

		}
		else
		{
			infoOut.put("[错误信息] 打开第二个文件失败\n");
		}
	}
	catch (const std::exception&)
	{
		infoOut.put("[错误信息] 打开第二个文件失败\n");
		buttonPressed_refresh();
	}
}


void VisualizeMain::Tree1_OriginalData_Analysis()
{
	try
	{
		for (int i = 0; i < Tree1_OriginalData.size(); i++)
		{

			int divideNum = -1;

			if (Tree1_OriginalData[i].size() == 0)
				continue;

			for (int j = 0; j < Tree1_OriginalData[i].size() - 1; j++)
			{
				if (Tree1_OriginalData[i][j] == '-' && Tree1_OriginalData[i][j + 1] == '>')
				{
					divideNum = j;
					break;
				}
			}

			if (divideNum == -1)
			{
				//cout << "找不到dividenum" << endl;
				Tree1_OriginalDataError++;
				continue;
			}

			else
			{
				string leftname = Tree1_OriginalData[i].substr(0, divideNum);
				string rightname = Tree1_OriginalData[i].substr(divideNum + 2, Tree1_OriginalData[i].size() - divideNum);

				if (leftname.empty() == false && rightname.empty() == false && leftname != rightname)
				{
					Tree1_RootToSon_NameRelation[leftname].push_back(rightname);
				}
				else
				{
					Tree1_OriginalDataError++;
					continue;
				}

			}
			
		}

		if (Tree1_RootToSon_NameRelation.size() == 0)
		{
			Tree1_iflegal = false;
			infoOut.put("[错误信息] 第一个文件是空树\n");
			return;
		}

		else
		{
			string tmpstr = "[文件解析] 第一个文件解析完成 检测到";
			tmpstr += to_string(Tree1_OriginalDataError);
			tmpstr += "个错误\n";
			infoOut.put(tmpstr);
		}

	}
	catch (const std::exception&)
	{
		infoOut.put("[错误信息] 第一个文件解析失败\n");
		buttonPressed_refresh();
	}
	
	
}


void VisualizeMain::Tree2_OriginalData_Analysis()
{
	try
	{
		for (int i = 0; i < Tree2_OriginalData.size(); i++)
		{

			int divideNum = -1;

			if (Tree2_OriginalData[i].size() == 0)
				continue;

			for (int j = 0; j < Tree2_OriginalData[i].size() - 1; j++)
			{
				if (Tree2_OriginalData[i][j] == '-' && Tree2_OriginalData[i][j + 1] == '>')
				{
					divideNum = j;
					break;
				}
			}

			if (divideNum == -1)
			{
				//cout << "找不到dividenum" << endl;
				Tree2_OriginalDataError++;
				continue;
			}

			else
			{
				string leftname = Tree2_OriginalData[i].substr(0, divideNum);
				string rightname = Tree2_OriginalData[i].substr(divideNum + 2, Tree2_OriginalData[i].size() - divideNum);

	
				if (leftname.empty() == false && rightname.empty() == false && leftname != rightname)
				{
					Tree2_RootToSon_NameRelation[leftname].push_back(rightname);
				}
				else
				{
					Tree2_OriginalDataError++;
					continue;
				}



			}

		}

		if (Tree2_RootToSon_NameRelation.size() == 0)
		{
			Tree2_iflegal = false;
			infoOut.put("[错误信息] 第二个文件是空树\n");
			return;
		}

		else
		{
			string tmpstr = "[文件解析] 第二个文件解析完成 检测到";
			tmpstr += to_string(Tree2_OriginalDataError);
			tmpstr += "个错误\n";
			infoOut.put(tmpstr);
		}

	}
	catch (const std::exception&)
	{
		infoOut.put("[错误信息] 第二个文件解析失败\n");
		buttonPressed_refresh();
	}


}


// 注意 函数首先要用名字空间的名字去申请节点 构建名字到节点的映射

void VisualizeMain::Tree1_NameToNode_Build()
{
	try
	{
		if (Tree1_iflegal == true)
		{
			
			for (auto pt = Tree1_RootToSon_NameRelation.begin(); pt != Tree1_RootToSon_NameRelation.end(); pt++)
			{
				Tree1_NameToNode[pt->first] = NULL;
				
				for (int i = 0; i < pt->second.size(); i++)
				{
					Tree1_NameToNode[pt->second[i]] = NULL;
				}

			}

			// 先建立名字空间

			// 再根据名字空间去申请节点
			for (auto pt = Tree1_NameToNode.begin(); pt != Tree1_NameToNode.end(); pt++)
			{
				Node* tmp = new Node(pt->first);
				pt->second = tmp;
			}
		
		}

	}
	catch (const std::exception&)
	{
		buttonPressed_refresh();
	}
	

}


// 注意 函数首先要用名字空间的名字去申请节点 构建名字到节点的映射

void VisualizeMain::Tree2_NameToNode_Build()
{
	try
	{
		if (Tree2_iflegal == true)
		{

			for (auto pt = Tree2_RootToSon_NameRelation.begin(); pt != Tree2_RootToSon_NameRelation.end(); pt++)
			{
				Tree2_NameToNode[pt->first] = NULL;

				for (int i = 0; i < pt->second.size(); i++)
				{
					Tree2_NameToNode[pt->second[i]] = NULL;
				}

			}

			// 先建立名字空间

			// 再根据名字空间去申请节点
			for (auto pt = Tree2_NameToNode.begin(); pt != Tree2_NameToNode.end(); pt++)
			{
				Node* tmp = new Node(pt->first);
				pt->second = tmp;
			}

		}
	}
	catch (const std::exception&)
	{
		buttonPressed_refresh();
	}


}


void VisualizeMain::Tree1_Build()
{
	try
	{
		// 考虑到可能有一个节点有两个父亲节点，所以必须检查一次
		map<string, int> nameCount;
		int errorCount = 0;
		for (auto pt = Tree1_RootToSon_NameRelation.begin(); pt != Tree1_RootToSon_NameRelation.end(); pt++)
		{
			for (int x = 0; x < pt->second.size(); x++)
			{
				nameCount[Tree1_NameToNode[pt->second[x]]->nodeName]++;

				if (nameCount[Tree1_NameToNode[pt->second[x]]->nodeName] >= 2)
				{
					Tree1_iflegal = false;
					errorCount++;
				}
			}

		}

		if (Tree1_iflegal == false)
		{
			string tpword = "[错误提示] 节点有多个父亲节点，树一构建终止！错误数";
			tpword += to_string(errorCount);
			tpword += "\n";

			infoOut.put(tpword);
		}

		// 
		if (Tree1_iflegal == true)
		{
			
			for (auto pt = Tree1_RootToSon_NameRelation.begin(); pt != Tree1_RootToSon_NameRelation.end(); pt++)
			{
				for (int x = 0; x < pt->second.size(); x++)
				{
					Tree1_NameToNode[pt->first]->childNode.push_back(Tree1_NameToNode[pt->second[x]]);
				}
				
			}

			

			//再刷新一下根节点
			string startstr = Tree1_RootToSon_NameRelation.begin()->first;

			while (1)
			{
				
				bool iffind = false;
				
				for (auto pt = Tree1_RootToSon_NameRelation.begin(); pt != Tree1_RootToSon_NameRelation.end(); pt++)
				{
					for (int j = 0; j < pt->second.size(); j++)
					{
						if (pt->second[j] == startstr)
						{
							iffind = true;
							startstr = pt->second[j];
							break;
						}
					}

					if (iffind == true)
					{
						break;
					}

				}

				

				if (iffind == false )
				{
					break;
				}

			}

			Tree1_realRootNode = Tree1_NameToNode[startstr];
			queue<Node*> tmpNodeque;
			tmpNodeque.push(Tree1_realRootNode);

			while (!tmpNodeque.empty())
			{
				
				Node* tmpn = tmpNodeque.front();

				cout << tmpn->nodeName << endl;
				tmpn->iflegal = true;	// 根据根节点，确定合法的节点 最后再检查是否所有的节点都是合法的
				tmpNodeque.pop();

				for (int i = 0; i < tmpn->childNode.size(); i++)
				{
					tmpNodeque.push(tmpn->childNode[i]);
				}

			}

			for (auto pt = Tree1_NameToNode.begin(); pt != Tree1_NameToNode.end(); pt++)
			{
				if (pt->second->iflegal == false)
				{
					Tree1_NodeError++;
					Tree1_iflegal = false;
				}
			}

			string tmpstr = "[文件解析] 第一个树构建完成 检测到";
			tmpstr += to_string(Tree1_NodeError);
			tmpstr += "个节点错误\n";
			infoOut.put(tmpstr);

		}
	}
	catch (const std::exception&)
	{
		buttonPressed_refresh();
	}
	
}


void VisualizeMain::Tree2_Build()
{
	try
	{
		// 考虑到可能有一个节点有两个父亲节点，所以必须检查一次
		map<string, int> nameCount;
		int errorCount = 0;
		for (auto pt = Tree2_RootToSon_NameRelation.begin(); pt != Tree2_RootToSon_NameRelation.end(); pt++)
		{
			for (int x = 0; x < pt->second.size(); x++)
			{
				nameCount[Tree2_NameToNode[pt->second[x]]->nodeName]++;

				if (nameCount[Tree2_NameToNode[pt->second[x]]->nodeName] >= 2)
				{
					Tree2_iflegal = false;
					errorCount++;
				}
			}

		}

		if (Tree2_iflegal == false)
		{
			string tpword = "[错误提示] 节点有多个父亲节点，树二构建终止！错误数";
			tpword += to_string(errorCount);
			tpword += "\n";

			infoOut.put(tpword);
		}

		// 






		if (Tree2_iflegal == true)
		{
			for (auto pt = Tree2_RootToSon_NameRelation.begin(); pt != Tree2_RootToSon_NameRelation.end(); pt++)
			{
				for (int x = 0; x < pt->second.size(); x++)
				{
					Tree2_NameToNode[pt->first]->childNode.push_back(Tree2_NameToNode[pt->second[x]]);
				}
			}



			//再刷新一下根节点
			string startstr = Tree2_RootToSon_NameRelation.begin()->first;

			while (1)
			{
				bool iffind = false;

				for (auto pt = Tree2_RootToSon_NameRelation.begin(); pt != Tree2_RootToSon_NameRelation.end(); pt++)
				{
					for (int j = 0; j < pt->second.size(); j++)
					{
						if (pt->second[j] == startstr)
						{
							iffind = true;
							startstr = pt->second[j];
							break;
						}
					}

					if (iffind == true)
					{
						break;
					}

				}

				if (iffind == false)
				{
					break;
				}

			}

			Tree2_realRootNode = Tree2_NameToNode[startstr];
			queue<Node*> tmpNodeque;
			tmpNodeque.push(Tree2_realRootNode);

			while (!tmpNodeque.empty())
			{
				Node* tmpn = tmpNodeque.front();
				tmpn->iflegal = true;	// 根据根节点，确定合法的节点 最后再检查是否所有的节点都是合法的
				tmpNodeque.pop();

				for (int i = 0; i < tmpn->childNode.size(); i++)
				{
					tmpNodeque.push(tmpn->childNode[i]);
				}

			}

			for (auto pt = Tree2_NameToNode.begin(); pt != Tree2_NameToNode.end(); pt++)
			{
				if (pt->second->iflegal == false)
				{
					Tree2_NodeError++;
					Tree2_iflegal = false;
				}
			}

			string tmpstr = "[文件解析] 第二个树构建完成 检测到";
			tmpstr += to_string(Tree2_NodeError);
			tmpstr += "个节点错误\n";
			infoOut.put(tmpstr);

		}
	}
	catch (const std::exception&)
	{
		buttonPressed_refresh();
	}

}


void VisualizeMain::Tree1_heightRefresh(Node* curnode, int curHeight)
{
	if (curnode != NULL)
	{
		curnode->height = curHeight;
		cout << "当前节点" << curnode->nodeName << endl;
		Tree1_height = (curHeight > Tree1_height) ? curHeight : Tree1_height;

		for (int i = 0; i < curnode->childNode.size(); i++)
		{
			if (curnode->childNode[i] != NULL)
			{
				Tree1_heightRefresh(curnode->childNode[i], curHeight + 1);
			}
		}

	}
}


void VisualizeMain::Tree2_heightRefresh(Node* curnode, int curHeight)
{
	if (curnode != NULL)
	{
		curnode->height = curHeight;
		cout << "当前节点" << curnode->nodeName << endl;
		Tree2_height = (curHeight > Tree2_height) ? curHeight : Tree2_height;

		for (int i = 0; i < curnode->childNode.size(); i++)
		{
			if (curnode->childNode[i] != NULL)
			{
				Tree2_heightRefresh(curnode->childNode[i], curHeight + 1);
			}
		}

	}
}

void VisualizeMain::Tree1_RankInHeightRefresh()
{
	try
	{
		if (Tree1_iflegal == true)
		{
			queue<Node*>tmpque;
			tmpque.push(Tree1_realRootNode);

			while(!tmpque.empty())
			{
				Node* tmpn = tmpque.front();
				Tree1_heightToNode[tmpn->height].push_back(tmpn);
				tmpque.pop();

				for (int i = 0; i < tmpn->childNode.size(); i++)
				{
					tmpque.push(tmpn->childNode[i]);
				}
			}

			for (auto iter = Tree1_heightToNode.begin(); iter != Tree1_heightToNode.end(); iter++)
			{
				for (int i = 0; i < iter->second.size(); i++)
				{
					iter->second[i]->RankInHeight = i + 1;
				}
			}

		}
	
	}
	catch (const std::exception&)
	{
		buttonPressed_refresh();
	}
	
}



void VisualizeMain::Tree2_RankInHeightRefresh()
{
	try
	{
		if (Tree2_iflegal == true)
		{
			queue<Node*>tmpque;
			tmpque.push(Tree2_realRootNode);

			while (!tmpque.empty())
			{
				Node* tmpn = tmpque.front();
				Tree2_heightToNode[tmpn->height].push_back(tmpn);
				tmpque.pop();

				for (int i = 0; i < tmpn->childNode.size(); i++)
				{
					tmpque.push(tmpn->childNode[i]);
				}
			}

			for (auto iter = Tree2_heightToNode.begin(); iter != Tree2_heightToNode.end(); iter++)
			{
				for (int i = 0; i < iter->second.size(); i++)
				{
					iter->second[i]->RankInHeight = i + 1;
					cout << iter->second[i]->nodeName << "-" << iter->second[i]->height << "-" << iter->second[i]->RankInHeight << endl;
				}
			}

		}

	}
	catch (const std::exception&)
	{
		buttonPressed_refresh();
	}


}


bool VisualizeMain::if_isomorphism(Node* tree1, Node* tree2)
{
	if (tree1 == NULL && tree2 == NULL)
		return true;
	if (tree1 != NULL && tree2 == NULL)
		return false;
	if (tree1 == NULL && tree2 != NULL)
		return false;
	if (tree1 != NULL && tree2 != NULL)
	{
		if (tree1->childNode.size() != tree2->childNode.size())
			return false;
		
		if (tree1->childNode.size() == 0 && tree2->childNode.size() == 0)
		{
			tree1->matchingNode = tree2;
			tree2->matchingNode = tree1;
			isomorphismNameToName1_2[tree1->nodeName] = tree2->nodeName;
			isomorphismNameToName2_1[tree2->nodeName] = tree1->nodeName;
			cout << tree1->nodeName << " matching1 " << tree2->nodeName << endl;
			return true;
		}

		bool* bookRight;
		bookRight = new bool[tree2->childNode.size()];
		
		for (int m = 0; m < (tree2->childNode.size()); m++)
		{
			bookRight[m] = false;
		}
		
		bool ifNOMatchingI = false;		// 这里先信任所有的i系列节点可以找到匹配，找不到匹配后修正

		for (int i = 0; i < tree1->childNode.size(); i++)
		{
			int j = 0;
			bool ifFindImatch = false; // 这里拒绝信任所有的j系列节点可以找到匹配，找到匹配后修正

			for (j = 0; j < (tree2->childNode.size()); j++)
			{
				if (bookRight[j] == false && if_isomorphism(tree1->childNode[i], tree2->childNode[j]) == true)
				{
					ifFindImatch = true;
					bookRight[j] = true;
					/*
					tree1->childNode[i]->matchingNode = tree2->childNode[j];
					tree2->childNode[j]->matchingNode = tree1->childNode[i];
					isomorphismNameToName1_2[tree1->childNode[i]->nodeName] = tree2->childNode[j]->nodeName;
					isomorphismNameToName2_1[tree2->childNode[i]->nodeName] = tree1->childNode[j]->nodeName;
					*/
					break;
				}
			}


			if (ifFindImatch == false)
			{
				ifNOMatchingI = true;
				cout << i << j << endl;
				cout << tree1->childNode[i]->nodeName << "无法找到" << endl;
				return false;
			}

			
		}

		delete[] bookRight;


		if (ifNOMatchingI == false)
		{
			tree1->matchingNode = tree2;
			tree2->matchingNode = tree1;
			isomorphismNameToName1_2[tree1->nodeName] = tree2->nodeName;
			isomorphismNameToName2_1[tree2->nodeName] = tree1->nodeName;

			cout << tree1->nodeName << " matching2 " << tree2->nodeName << endl;
			return true;
		}
			
	}
}

void VisualizeMain::Tree1_PositionRefresh()
{
	if (Tree1_iflegal == true && Tree1_height > 0)
	{
		for (auto iter = Tree1_NameToNode.begin(); iter != Tree1_NameToNode.end(); iter++)
		{
			if ((iter->second->height) > 7)
			{
				iter->second->yyPositon = -1;
				iter->second->xxPositon = -1;
				iter->second->ifVIsualize = false;
				continue;
			}

			iter->second->xxScale = int(0.4325 * x_max() / Tree1_heightToNode[iter->second->height].size());
			iter->second->yyScale = int(0.9 * y_max() / min(Tree1_height, 7));
			iter->second->xxPositon = int(iter->second->xxScale * ((iter->second->RankInHeight) - 0.5) + 0.135 * x_max());
			iter->second->yyPositon = int(iter->second->yyScale * ((iter->second->height) - 0.5));
			iter->second->ifVIsualize = true;
		}
	}
	
}


void VisualizeMain::Tree2_PositionRefresh()
{
	if (Tree2_iflegal == true && Tree2_height > 0)
	{
		for (auto iter = Tree2_NameToNode.begin(); iter != Tree2_NameToNode.end(); iter++)
		{
			if ((iter->second->height) > 7)
			{
				iter->second->yyPositon = -1;
				iter->second->xxPositon = -1;
				iter->second->ifVIsualize = false;
				continue;
			}

			iter->second->xxScale = int(0.4325 * x_max() / Tree2_heightToNode[iter->second->height].size());
			iter->second->yyScale = int(0.9 * y_max() / min(Tree2_height, 7));
			iter->second->xxPositon = int(iter->second->xxScale * ((iter->second->RankInHeight) - 0.5) + 0.5675 * x_max());
			iter->second->yyPositon = int(iter->second->yyScale * ((iter->second->height) - 0.5));
			iter->second->ifVIsualize = true;
		}
	}
	
}


void VisualizeMain::Tree1_clear()
{
	ifsimular = false;
	progressbar1refresh(1);
	progressbar2refresh(1);
	progressbar3refresh(1);
	progressbar4refresh(1);
	
	Tree1_iflegal = true;
	Tree1_height = -1;
	Tree1_OriginalDataError = 0;
	Tree1_NodeError = 0;
	Tree1_realRootNode = NULL;

	for (int i = 0; i < Tree1_Circle.size(); i++)
	{
		detach(Tree1_Circle[i]);
	}

	for (int i = 0; i < Tree1_Line.size(); i++)
	{
		detach(Tree1_Line[i]);
	}

	for (int i = 0; i < Tree1_Text.size(); i++)
	{
		detach(Tree1_Text[i]);
	}


	for (auto pt = Tree1_NameToNode.begin(); pt != Tree1_NameToNode.end(); pt++)
	{
		delete pt->second;
	}

	for (int i = 0; i < Tree1_detectingArea.size(); i++)
	{
		delete Tree1_detectingArea[i];
	}

	Tree1_OriginalData.clear();
	Tree1_RootToSon_NameRelation.clear();
	Tree1_NameToNode.clear();
	Tree1_heightToNode.clear();
	Tree1_Circle.clearVector();
	Tree1_Line.clearVector();
	Tree1_Text.clearVector();
	Tree1_detectingArea.clear();
	isomorphismNameToName1_2.clear();
	Fl::redraw();

}
void VisualizeMain::Tree2_clear()
{
	Tree2_iflegal = true;
	Tree2_height = -1;
	Tree2_OriginalDataError = 0;
	Tree2_NodeError = 0;
	Tree2_realRootNode = NULL;

	for (int i = 0; i < Tree2_Circle.size(); i++)
	{
		detach(Tree2_Circle[i]);
	}

	for (int i = 0; i < Tree2_Line.size(); i++)
	{
		detach(Tree2_Line[i]);
	}

	for (int i = 0; i < Tree2_Text.size(); i++)
	{
		detach(Tree2_Text[i]);
	}


	for (auto pt = Tree2_NameToNode.begin(); pt != Tree2_NameToNode.end(); pt++)
	{
		delete pt->second;
	}

	for (int i = 0; i < Tree2_detectingArea.size(); i++)
	{
		delete Tree2_detectingArea[i];
	}

	Tree2_OriginalData.clear();
	Tree2_RootToSon_NameRelation.clear();
	Tree2_NameToNode.clear();
	Tree2_heightToNode.clear();
	Tree2_Circle.clearVector();
	Tree2_Line.clearVector();
	Tree2_Text.clearVector();
	Tree2_detectingArea.clear();
	isomorphismNameToName2_1.clear();
	Fl::redraw();

}


void VisualizeMain::Tree_detectingAreaGenerator()
{
	for (auto iter = Tree1_NameToNode.begin(); iter != Tree1_NameToNode.end(); iter++)
	{
		int xxp = iter->second->xxPositon;
		int yyp = iter->second->yyPositon;
		int len = int(0.62 * min(iter->second->xxScale, iter->second->yyScale));

		xxp = xxp - len / 2;
		yyp = yyp - len / 2;

		//cout << "开始产生1" << endl;
		
		begin();
		MatchingButton* tmp = new MatchingButton(xxp, yyp, len, len, iter->first);
		tmp->callback(cb);
		end();
		Fl::redraw();
		Tree1_detectingArea.push_back(tmp);
	}

	for (auto iter = Tree2_NameToNode.begin(); iter != Tree2_NameToNode.end(); iter++)
	{
		int xxp = iter->second->xxPositon;
		int yyp = iter->second->yyPositon;
		int len = int(0.62 * min(iter->second->xxScale, iter->second->yyScale));

		xxp = xxp - len / 2;
		yyp = yyp - len / 2;

		//cout << "开始产生1" << endl;
		begin();
		MatchingButton* tmp = new MatchingButton(xxp, yyp, len, len, iter->first);
		tmp->callback(cb);
		end();
		Fl::redraw();
		Tree2_detectingArea.push_back(tmp);
	}

}

void VisualizeMain::Tree1_draw()
{
	try
	{
		if (Tree1_iflegal == false)
		{
			infoOut.put("[错误提醒] 树一非法，拒绝可视化。请检查\n");
			return;
		}

		for (auto iter = Tree1_NameToNode.begin(); iter != Tree1_NameToNode.end(); iter++)
		{
			auto obj = iter->second;

			if (obj->ifVIsualize == false)
				continue;

			Tree1_Circle.push_back(new Graph_lib::Circle(Point(obj->xxPositon, obj->yyPositon), int(0.3 * min(obj->xxScale, obj->yyScale))));
			Tree1_Circle[Tree1_Circle.size() - 1].set_color(250);
			attach(Tree1_Circle[Tree1_Circle.size() - 1]);

			Tree1_Text.push_back(new Text(Point(obj->xxPositon, obj->yyPositon), obj->nodeName));
			Tree1_Text[Tree1_Text.size() - 1].set_color(Color::black);
			attach(Tree1_Text[Tree1_Text.size() - 1]);


			for (int i = 0; i < obj->childNode.size(); i++)
			{
				// iter 是爸爸  obj->childNode[i] 是儿子
				int fatherR = int(0.3 * min(obj->xxScale, obj->yyScale));
				int sonR = int(0.3 * min(obj->childNode[i]->xxScale, obj->childNode[i]->yyScale));

				int fatherX = obj->xxPositon;
				int fatherY = obj->yyPositon;
				int sonX = obj->childNode[i]->xxPositon;
				int sonY = obj->childNode[i]->yyPositon;

				int fatherX_dx = fatherR * (sonX - fatherX) / sqrt((sonX - fatherX) * (sonX - fatherX) + (sonY - fatherY) * (sonY - fatherY));
				int fatherY_dy = fatherR * (sonY - fatherY) / sqrt((sonX - fatherX) * (sonX - fatherX) + (sonY - fatherY) * (sonY - fatherY));
				int sonX_dx = -sonR * (sonX - fatherX) / sqrt((sonX - fatherX) * (sonX - fatherX) + (sonY - fatherY) * (sonY - fatherY));
				int sonY_dy = -sonR * (sonY - fatherY) / sqrt((sonX - fatherX) * (sonX - fatherX) + (sonY - fatherY) * (sonY - fatherY));

				Tree1_Line.push_back(new Graph_lib::Line(Point(fatherX + fatherX_dx, fatherY + fatherY_dy), Point(sonX + sonX_dx, sonY + sonY_dy)));
				Tree1_Line[Tree1_Line.size() - 1].set_color(250);
				attach(Tree1_Line[Tree1_Line.size() - 1]);

			}

			Fl::redraw();

		}

		infoOut.put("[操作提醒] 树一可视化完成\n");
	}
	catch (const std::exception&)
	{
		infoOut.put("[错误提醒] 树一可视化失败，请检查\n");
		buttonPressed_refresh();
	}
	
}



void VisualizeMain::Tree2_draw()
{
	try
	{
		if (Tree2_iflegal == false)
		{
			infoOut.put("[错误提醒] 树二非法，拒绝可视化。请检查\n");
			return;
		}

		for (auto iter = Tree2_NameToNode.begin(); iter != Tree2_NameToNode.end(); iter++)
		{
			auto obj = iter->second;

			if (obj->ifVIsualize == false)
				continue;

			Tree2_Circle.push_back(new Graph_lib::Circle(Point(obj->xxPositon, obj->yyPositon), int(0.3 * min(obj->xxScale, obj->yyScale))));
			Tree2_Circle[Tree2_Circle.size() - 1].set_color(250);
			attach(Tree2_Circle[Tree2_Circle.size() - 1]);

			Tree2_Text.push_back(new Text(Point(obj->xxPositon, obj->yyPositon), obj->nodeName));
			Tree2_Text[Tree2_Text.size() - 1].set_color(Color::black);
			attach(Tree2_Text[Tree2_Text.size() - 1]);


			for (int i = 0; i < obj->childNode.size(); i++)
			{
				// iter 是爸爸  obj->childNode[i] 是儿子
				int fatherR = int(0.3 * min(obj->xxScale, obj->yyScale));
				int sonR = int(0.3 * min(obj->childNode[i]->xxScale, obj->childNode[i]->yyScale));

				int fatherX = obj->xxPositon;
				int fatherY = obj->yyPositon;
				int sonX = obj->childNode[i]->xxPositon;
				int sonY = obj->childNode[i]->yyPositon;

				int fatherX_dx = fatherR * (sonX - fatherX) / sqrt((sonX - fatherX) * (sonX - fatherX) + (sonY - fatherY) * (sonY - fatherY));
				int fatherY_dy = fatherR * (sonY - fatherY) / sqrt((sonX - fatherX) * (sonX - fatherX) + (sonY - fatherY) * (sonY - fatherY));
				int sonX_dx = -sonR * (sonX - fatherX) / sqrt((sonX - fatherX) * (sonX - fatherX) + (sonY - fatherY) * (sonY - fatherY));
				int sonY_dy = -sonR * (sonY - fatherY) / sqrt((sonX - fatherX) * (sonX - fatherX) + (sonY - fatherY) * (sonY - fatherY));

				Tree2_Line.push_back(new Graph_lib::Line(Point(fatherX + fatherX_dx, fatherY + fatherY_dy), Point(sonX + sonX_dx, sonY + sonY_dy)));
				Tree2_Line[Tree2_Line.size() - 1].set_color(250);
				attach(Tree2_Line[Tree2_Line.size() - 1]);

			}

			Fl::redraw();

		}

		infoOut.put("[操作提醒] 树二可视化完成\n");
	}
	catch (const std::exception&)
	{
		infoOut.put("[错误提醒] 树二可视化失败，请检查\n");
		buttonPressed_refresh();
	}

}


void VisualizeMain::ButtonMatching()
{
	for (int i = 0; i < Tree1_detectingArea.size(); i++)
	{
		string tmp = Tree1_detectingArea[i]->NodeName;

		for (int j = 0; j < Tree1_Circle.size(); j++)
		{
			if (Tree1_Circle[j].center().x == Tree1_NameToNode[tmp]->xxPositon && Tree1_Circle[j].center().y == Tree1_NameToNode[tmp]->yyPositon)
			{
				Tree1_detectingArea[i]->thisCircle = &(Tree1_Circle[j]);
				Tree1_detectingArea[i]->thisText = &(Tree1_Text[j]);
				cout << "Binding !!" << endl;
				break;
			}

		}

		for (int j = 0; j < Tree2_Circle.size(); j++)
		{

			if (Tree2_Circle[j].center().x == Tree2_NameToNode[isomorphismNameToName1_2[tmp]]->xxPositon && Tree2_Circle[j].center().y == Tree2_NameToNode[isomorphismNameToName1_2[tmp]]->yyPositon)
			{
				Tree1_detectingArea[i]->matchingCircle = &(Tree2_Circle[j]);
				Tree1_detectingArea[i]->matchingText = &(Tree2_Text[j]);
				cout << "Binding !!" << endl;
				break;
			}
		}

	}


	for (int i = 0; i < Tree2_detectingArea.size(); i++)
	{
		string tmp = Tree2_detectingArea[i]->NodeName;

		for (int j = 0; j < Tree2_Circle.size(); j++)
		{
			if (Tree2_Circle[j].center().x == Tree2_NameToNode[tmp]->xxPositon && Tree2_Circle[j].center().y == Tree2_NameToNode[tmp]->yyPositon)
			{
				Tree2_detectingArea[i]->thisCircle = &(Tree2_Circle[j]);
				Tree2_detectingArea[i]->thisText = &(Tree2_Text[j]);
				break;
			}

		}

		for (int j = 0; j < Tree1_Circle.size(); j++)
		{

			if (Tree1_Circle[j].center().x == Tree1_NameToNode[isomorphismNameToName2_1[tmp]]->xxPositon && Tree1_Circle[j].center().y == Tree1_NameToNode[isomorphismNameToName2_1[tmp]]->yyPositon)
			{
				Tree2_detectingArea[i]->matchingCircle = &(Tree1_Circle[j]);
				Tree2_detectingArea[i]->matchingText = &(Tree1_Text[j]);
				break;
			}


		}

	}




}

















// 下面的函数属于辅助功能 进度条
// --------------------------------------------------------------------------------------------------------------------------------
void VisualizeMain::progressbar1refresh(int num)
{
	if (vec1.size() != 0)
	{
		for (int i = 0; i < vec1.size(); i++)
		{
			detach(vec1[i]);
		}
	}

	vec1.clearVector();
	vec1.push_back(new Graph_lib::Rectangle(Point{ int(0.025 * x_max()),int(0.045 * x_max()) }, Point{ int((0.025 + 0.1 * num / 100) * x_max()),int(0.060 * x_max()) }));
	vec1[vec1.size() - 1].set_fill_color(250);
	attach(vec1[vec1.size() - 1]);

	Fl::redraw();
}


void VisualizeMain::progressbar2refresh(int num)
{
	if (vec2.size() != 0)
	{
		for (int i = 0; i < vec2.size(); i++)
		{
			detach(vec2[i]);
		}
	}

	vec2.clearVector();
	vec2.push_back(new Graph_lib::Rectangle(Point{ int(0.025 * x_max()),int(0.085 * x_max()) }, Point{ int((0.025 + 0.1 * num / 100) * x_max()),int(0.100 * x_max()) }));
	vec2[vec2.size() - 1].set_fill_color(250);
	attach(vec2[vec2.size() - 1]);
	Fl::redraw();
}

void VisualizeMain::progressbar3refresh(int num)
{
	if (vec3.size() != 0)
	{
		for (int i = 0; i < vec3.size(); i++)
		{
			detach(vec3[i]);
		}
	}

	vec3.clearVector();
	vec3.push_back(new Graph_lib::Rectangle(Point{ int(0.025 * x_max()),int(0.125 * x_max()) }, Point{ int((0.025 + 0.1 * num / 100) * x_max()),int(0.140 * x_max()) }));
	vec3[vec3.size() - 1].set_fill_color(250);
	attach(vec3[vec3.size() - 1]);
	Fl::redraw();
}

void VisualizeMain::progressbar4refresh(int num)
{
	if (vec4.size() != 0)
	{
		for (int i = 0; i < vec4.size(); i++)
		{
			detach(vec4[i]);
		}
	}

	vec4.clearVector();
	vec4.push_back(new Graph_lib::Rectangle(Point{ int(0.025 * x_max()),int(0.165 * x_max()) }, Point{ int((0.025 + 0.1 * num / 100) * x_max()),int(0.180 * x_max()) }));
	vec4[vec4.size() - 1].set_fill_color(250);
	attach(vec4[vec4.size() - 1]);
	Fl::redraw();
}


// --------------------------------------------------------------------------------------------------------------------------------



/*
VisualizeMain::VisualizeMain(int scrW, int scrH)
	:Window{ Point(0 ,0),scrW ,scrH , "Main" },
	button_exit{ Point{int(0.025 * x_max()),int(0.8 * y_max())},int(0.08 * x_max()),40,"退出",
		[](Address,Address pw) {reference_to<VisualizeMain>(pw).buttonPressed_exit(); } },
	button_readfileAuto{ Point{int(0.025 * x_max()),int(0.7 * y_max())},int(0.08 * x_max()),40,"自动读取文件",
		[](Address,Address pw) {reference_to<VisualizeMain>(pw).buttonPressed_readfileAuto(); } },
	button_readfileManu{ Point{int(0.025 * x_max()),int(0.6 * y_max())},int(0.08 * x_max()),40,"手动读取文件",
		[](Address,Address pw) {reference_to<VisualizeMain>(pw).buttonPressed_readfileManu(); } },
	button_refresh{ Point{int(0.025 * x_max()),int(0.5 * y_max())},int(0.08 * x_max()),40,"清空数据",
		[](Address,Address pw) {reference_to<VisualizeMain>(pw).buttonPressed_refresh(); } },
	button_nextRead{ Point{int(0.325 * x_max()),int(0.93 * y_max())},int(0.13 * x_max()),40,"继续读取队列中文件",
		[](Address,Address pw) {reference_to<VisualizeMain>(pw).buttonPressed_nextRead(); } },
	button_findRelated{ Point{int(0.8 * x_max()),int(0.93 * y_max())},int(0.1 * x_max()),40,"查找匹配节点",
		[](Address,Address pw) {reference_to<VisualizeMain>(pw).buttonPressed_findRelated(); } },
	processBar1(Point{ int(0.025 * x_max()),int(0.045 * x_max()) }, Point{ int(0.125 * x_max()),int(0.060 * x_max()) }),
	processBar2(Point{ int(0.025 * x_max()),int(0.085 * x_max()) }, Point{ int(0.125 * x_max()),int(0.100 * x_max()) }),
	processBar3(Point{ int(0.025 * x_max()),int(0.125 * x_max()) }, Point{ int(0.125 * x_max()),int(0.140 * x_max()) }),
	processBar4(Point{ int(0.025 * x_max()),int(0.165 * x_max()) }, Point{ int(0.125 * x_max()),int(0.180 * x_max()) }),
	processBar1Title(Point{ int(0.025 * x_max()),int(0.040 * x_max()) }, "文件读取与数据对接"),
	processBar2Title(Point{ int(0.025 * x_max()),int(0.080 * x_max()) }, "树的构建与可视化"),
	processBar3Title(Point{ int(0.025 * x_max()),int(0.120 * x_max()) }, "同构的判断"),
	processBar4Title(Point{ int(0.025 * x_max()),int(0.160 * x_max()) }, "同构链接的呈现"),
	inputbox(Point{ int(0.025 * x_max()),int(0.390 * y_max()) }, int(0.1 * x_max()), int(0.04 * y_max()), ""),
	inboxTitle(Point{ int(0.025 * x_max()),int(0.385 * y_max()) },"目录输入框：(Ctrl+V)"),
	inputreminderText(Point{ int(0.025 * x_max()),int(0.450 * y_max()) }, "请粘贴目标文件夹的目录"),
	infoOutTitle(Point{ int(0.025 * x_max()),int(0.92 * y_max()) }, "信息框"),
	infoOut(Point{ int(0.025 * x_max()),int(0.93 * y_max()) }, int(0.29 * x_max()), int(0.05 * y_max()), ""),
	NodeNameIn(Point{ int(0.625 * x_max()),int(0.93 * y_max()) },int(0.15 * x_max()), int(0.05 * y_max()), "输入节点"),
	line1(Point{ int(0.135 * x_max()),int(0.05 * y_max()) },Point{ int(0.135 * x_max()),int(0.89 * y_max()) }),
	line2(Point{ int(0.5675 * x_max()),int(0.05 * y_max()) }, Point{ int(0.5675 * x_max()),int(0.89 * y_max()) })
{

	ScreenWidth = scrW;
	ScreenHeight = scrH;
	Tree1_height = -1;
	Tree2_height = -1;
	ifsimular = false;

	// 颜色初始化
	//processBar1.set_fill_color
	processBar1.set_color(Color::black);
	processBar1.set_fill_color(Color::white);
	processBar2.set_color(Color::black);
	processBar2.set_fill_color(Color::white);
	processBar3.set_color(Color::black);
	processBar3.set_fill_color(Color::white);
	processBar4.set_color(Color::black);
	processBar4.set_fill_color(Color::white);

	

	line1.set_color(250);
	line2.set_color(250);

	color(254);
	inputreminderText.set_color(Color::red);

	// 窗口吸附
	attach(button_exit);
	attach(button_readfileAuto);
	attach(button_readfileManu);
	attach(button_refresh);
	attach(button_nextRead);
	attach(button_findRelated);

	attach(processBar1);
	attach(processBar2);
	attach(processBar3);
	attach(processBar4);

	attach(processBar1Title);
	attach(processBar2Title);
	attach(processBar3Title);
	attach(processBar4Title);
	

	attach(infoOut);
	attach(inputbox);
	attach(inboxTitle);
	attach(infoOutTitle);
	attach(inputreminderText);
	attach(NodeNameIn);

	attach(line1);
	attach(line2);
	
	
	// 基础变量在这里初始化
	Tree1_iflegal = true;
	Tree2_iflegal = true;		// 先信任树的合法
	infoOut.put("你好呀!欢迎使用程序 ~ 请准备好相关文件");
	
	
}

void VisualizeMain::buttonPressed_exit()
{
	hide();
}


void VisualizeMain::buttonPressed_readfileAuto()
{
	// 避免用户重复按下按钮 每次开始时刷新一次变量
	Tree1_clear();
	Tree2_clear();
	STSTEM_var_refresh();

	findCurrentPlace();
	PrimefileFocus(currentfilePlace, OriginalAllfilePlace);
	Selector(OriginalAllfilePlace, FinalPlaceResult);
	
	// 目录筛选完成，控制权全部交给tree master
	TreeCenterMaster();

	gui_main();
}

void VisualizeMain::buttonPressed_readfileManu()
{
	// 避免用户重复按下按钮 每次开始时刷新一次变量
	Tree1_clear();
	Tree2_clear();
	STSTEM_var_refresh();

	ManualfilePlace = inputbox.get_string();
	if (ManualfilePlace.size() > 0)
	{
		infoOut.put("【手动读取】目录已加载");
		cout << ManualfilePlace << endl;
		PrimefileFocus(ManualfilePlace, OriginalAllfilePlace);
		Selector(OriginalAllfilePlace, FinalPlaceResult);
		
		// 目录筛选完成，控制权全部交给tree master
		TreeCenterMaster();
	}
	else
	{
		infoOut.put("【手动读取】目录为空，请重新输入");
	}
	
	gui_main();
}

// 清空会清空所有的数据
void VisualizeMain::buttonPressed_refresh()
{
	currentfilePlace = "";
	ManualfilePlace = "";
	Tree1_clear();
	Tree2_clear();
	STSTEM_var_refresh();
	
	progressbar1refresh(1);
	progressbar2refresh(1);
	progressbar3refresh(1);
	progressbar4refresh(1);
	infoOut.put("【清空数据】数据清空完成");

	gui_main();
}

void VisualizeMain::buttonPressed_nextRead()
{
	Tree1_clear();
	Tree2_clear();

	if (FinalPlaceResult.size() >= 2)
	{
		TreeCenterMaster();
	}
	else
	{
		infoOut.put("队列中没有可以读取的文件，请重新添加文件");
	}
	gui_main();
}




void VisualizeMain::findCurrentPlace()
{
	char* buffer;
	//也可以将buffer作为输出参数
	if ((buffer = _getcwd(NULL, 0)) == NULL)
	{
		perror("getcwd error");
		infoOut.put("【自动读取】目录获取失败,请检查操作系统权限！");
	}
	else
	{
		//printf("%s\n", buffer);
		currentfilePlace += buffer;
		free(buffer);
	}

	cout << currentfilePlace << endl;
	infoOut.put("【自动读取】文件目录获取成功");

}

*/



/*
// 初步识别文件
void VisualizeMain::PrimefileFocus(string path, vector<string>& files)
{
	//文件句柄  
	long hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之  
			//如果不是,加入列表  
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				
				// if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				//	PrimefileFocus(p.assign(path).append("\\").append(fileinfo.name), files);
				
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}

	for (int i = 0; i < files.size(); i++)
	{
		cout << files[i] << endl;
	}
}

bool VisualizeMain::if_Select(string& obj)
{
	for (int i = 0; i < obj.size() ; i++)
	{
		if (obj[i] == '\0')
		{
			obj.erase(obj.begin() + i);
		}
	}

	int pointPlace = -1;
	for (int i = 1; i < 5; i++)
	{
		if (obj.size() - i >= 0 && obj[obj.size() - i] == '.')
		{
			pointPlace = obj.size() - i;
			break;
		}
	}

	if (pointPlace >= 0 && obj.size() - pointPlace > 0)
	{
		string filesort = obj.substr(pointPlace, obj.size() - pointPlace);
		//cout << filesort << endl;
		if (filesort == ".in" || filesort == ".csv" || filesort == ".txt")
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		
		return false;
	}
		
}


void VisualizeMain::Selector(vector<string>& beforeSel, vector<string>& AfterSel)
{
	for (int i = 0; i < beforeSel.size(); i++)
	{
		string tmpstr = beforeSel[i];
		if (if_Select(tmpstr) == true)
		{
			AfterSel.push_back(beforeSel[i]);
		}
		
	}
	string tmp = "【文件过滤】已经筛选出";
	tmp += to_string(AfterSel.size());
	tmp += "个文件,进入队列";
	infoOut.put(tmp);
	cout << "筛选出" << AfterSel.size() << endl;
}


// function deal with tWO fire in the queue
// before function will be executed, if will Auto check if queue size >= 2
int VisualizeMain::TreeCenterMaster()
{
	try {

		if (FinalPlaceResult.size() >= 2)
		{
			Tree1_OriginalData_Get();
			Tree2_OriginalData_Get();

			if (Tree1_iflegal == false || Tree2_iflegal == false)
			{
				cout << "【错误】读取文件内容时出现问题" << endl;
				infoOut.put("【错误】读取文件内容时出现问题");
				buttonPressed_refresh();
			}

			

			Tree1_OriginalData_Analysis();
			Tree2_OriginalData_Analysis();

			if (Tree1_iflegal == false || Tree2_iflegal == false)
			{
				infoOut.put("【错误】文件解析错误，请检查文件内容");
				buttonPressed_refresh();
			}

			Tree1_NameToNode_Build();
			Tree2_NameToNode_Build();
			progressbar1refresh(100);

			if (Tree1_iflegal == false || Tree2_iflegal == false)
			{
				infoOut.put("【错误】节点名字空间建立失败，请检查合法性");
				buttonPressed_refresh();

			}

			Tree1_Build();
			Tree2_Build();

			if (Tree1_iflegal == false || Tree2_iflegal == false)
			{
				infoOut.put("【错误】树的链接建立失败");
				buttonPressed_refresh();

			}



			ifsimular = if_isomorphism(Tree1_realRootNode, Tree2_realRootNode);
			// tree build succeed! then check if they are simular
			progressbar3refresh(100);
			// 如果同构就建立监测区域，追踪鼠标
			if (ifsimular == true)
			{
				Tree1_heightRefresh(Tree1_realRootNode, 1);
				Tree1_NodepositionRefresh(Tree1_realRootNode, NULL);
				Tree2_heightRefresh(Tree2_realRootNode, 1);
				Tree2_NodepositionRefresh(Tree2_realRootNode, NULL);

				DetectingAreaGenerator();

			}

			
			
			Tree1_draw();
			Tree2_draw();
			

			if (Tree1_iflegal == false || Tree2_iflegal == false)
			{
				infoOut.put("【错误】树的可视化失败");

			}

			infoOut.put("【提示】树的可视化成功");
			progressbar2refresh(100);
			
			if (Tree1_iflegal == true || Tree2_iflegal == true)
			{
				if (ifsimular == true)
				{
					infoOut.put("【提示】可视化成功，两棵树同构");
					isomorphismLink(Tree1_realRootNode, Tree2_realRootNode);
					//progressbar3refresh(100);
					TmpPrinter_isomorphismNameToName1();
					//progressbar4refresh(100);

					ButtonMatchingGenetor();
				}

				else
				{
					infoOut.put("【提示】可视化成功，两棵树不同构");

				}
			}
			progressbar4refresh(100);
		}
		else
		{
			infoOut.put("队列无可读取文件，请单击清空重新读取文件");
		}

		return gui_main();


	}

	catch (...)
	{
		infoOut.put("错误出现，请检查文件、树的合法性");
		buttonPressed_refresh();
	}

	
}


void VisualizeMain::Tree1_OriginalData_Get()
{
	ifstream tree1_ifs;
	tree1_ifs.open(FinalPlaceResult.front(), ios::in);
	if (tree1_ifs.is_open())
	{
		string buf;
		while (getline(tree1_ifs, buf))
		{
			Tree1_OriginalData.push_back(buf);
			cout << buf << endl;
			buf.clear();
		}

		FinalPlaceResult.erase(FinalPlaceResult.begin());
		cout << "读取结束" << endl;
		//progressbar1refresh(25);
	}
	else
	{
		cout << "打开失败" << endl;
	}
}


void VisualizeMain::Tree2_OriginalData_Get()
{
	ifstream tree2_ifs;
	tree2_ifs.open(FinalPlaceResult.front(), ios::in);
	if (tree2_ifs.is_open())
	{
		string buf;
		while (getline(tree2_ifs, buf))
		{
			Tree2_OriginalData.push_back(buf);
			cout << buf << endl;
			buf.clear();
		}

		FinalPlaceResult.erase(FinalPlaceResult.begin());
		cout << "读取结束" << endl;
		//progressbar1refresh(50);
	}
	else
	{
		cout << "打开失败" << endl;
	}
}


void VisualizeMain::Tree1_OriginalData_Analysis()
{
	for (int i = 0; i < Tree1_OriginalData.size(); i++)
	{
		
		
		int divideNum = -1;

		if (Tree1_OriginalData[i].size() == 0)
			continue;

		for (int j = 0; j < Tree1_OriginalData[i].size() - 1; j++)
		{
			if (Tree1_OriginalData[i][j] == '-' && Tree1_OriginalData[i][j + 1] == '>')
			{
				divideNum = j;
				break;
			}
		}
		
		if (divideNum <= 0 )
		{
			cout << "找不到dividenum" << endl;
			Tree1_iflegal = false;
			return;
		}
		
		else
		{
			string leftname = Tree1_OriginalData[i].substr(0, divideNum);
			string rightname = Tree1_OriginalData[i].substr(divideNum + 2, Tree1_OriginalData[i].size() - divideNum);
			//cout << "lN" << leftname << "RN" << rightname << endl;
			if (Tree1_RootToSon_NameRelationLeft.count(leftname) == 1)
			{
				if(Tree1_RootToSon_NameRelationRight.count(leftname) == 0)
				{
					Tree1_RootToSon_NameRelationRight[leftname] = rightname;
				}
			}
			
			else if (Tree1_RootToSon_NameRelationLeft.count(leftname) == 0)
			{
				Tree1_RootToSon_NameRelationLeft[leftname] = rightname;
			}
		}
		//progressbar1refresh(50 + i * 25 / Tree1_OriginalData.size());
	}
	
	if (Tree1_RootToSon_NameRelationRight.size() + Tree1_RootToSon_NameRelationLeft.size() == 0)
	{
		Tree1_iflegal = false;
		return;
	}

	TmpPrinter_Tree1_RootToSon_NameRelation();
}

void VisualizeMain::Tree2_OriginalData_Analysis()
{
	for (int i = 0; i < Tree2_OriginalData.size(); i++)
	{
		int divideNum = -1;
		
		if (Tree2_OriginalData[i].size() == 0)
			continue;
		
		for (int j = 0; j < Tree2_OriginalData[i].size() - 1; j++)
		{
			if (Tree2_OriginalData[i][j] == '-' && Tree2_OriginalData[i][j + 1] == '>')
			{
				divideNum = j;
				break;
			}
		}

		if (divideNum <= 0 )
		{
			cout << "找不到dividenum" << endl;
			Tree2_iflegal = false;
			return;
		}

		else
		{
			string leftname = Tree2_OriginalData[i].substr(0, divideNum);
			string rightname = Tree2_OriginalData[i].substr(divideNum + 2, Tree2_OriginalData[i].size() - divideNum);
			//cout << "lN" << leftname << "RN" << rightname << endl;
			if (Tree2_RootToSon_NameRelationLeft.count(leftname) == 1)
			{
				if (Tree2_RootToSon_NameRelationRight.count(leftname) == 0)
				{
					Tree2_RootToSon_NameRelationRight[leftname] = rightname;
				}
			}

			else if (Tree2_RootToSon_NameRelationLeft.count(leftname) == 0)
			{
				Tree2_RootToSon_NameRelationLeft[leftname] = rightname;
			}
		}
		//progressbar1refresh(75 + i * 25 / Tree2_OriginalData.size());
	}
	
	//progressbar1refresh(100);

	if (Tree2_RootToSon_NameRelationRight.size() + Tree2_RootToSon_NameRelationLeft.size() == 0)
	{
		Tree2_iflegal = false;
		return;
	}

	TmpPrinter_Tree2_RootToSon_NameRelation();
}

// 注意 函数首先要用名字空间的名字去申请节点 构建名字到节点的映射

void VisualizeMain::Tree1_NameToNode_Build()
{
	if (Tree1_iflegal == true)
	{
		
		for (auto pt = Tree1_RootToSon_NameRelationLeft.begin(); pt != Tree1_RootToSon_NameRelationLeft.end(); pt++)
		{
			Tree1_NameToNode[pt->first] = NULL;
			Tree1_NameToNode[pt->second] = NULL;
		}

		for (auto pt = Tree1_RootToSon_NameRelationRight.begin(); pt != Tree1_RootToSon_NameRelationRight.end(); pt++)
		{
			Tree1_NameToNode[pt->first] = NULL;
			Tree1_NameToNode[pt->second] = NULL;
		}
		// 先建立名字空间

		// 再根据名字空间去申请节点
		for (auto pt = Tree1_NameToNode.begin(); pt != Tree1_NameToNode.end(); pt++)
		{
			Node* tmp = new Node(pt->first, NULL, NULL);
			pt->second = tmp;
		}
		
		

		//progressbar2refresh(25);
	}
	
}


void VisualizeMain::Tree2_NameToNode_Build()
{
	if (Tree1_iflegal == true)
	{
		for (auto pt = Tree2_RootToSon_NameRelationLeft.begin(); pt != Tree2_RootToSon_NameRelationLeft.end(); pt++)
		{
			Tree2_NameToNode[pt->first] = NULL;
			Tree2_NameToNode[pt->second] = NULL;
		}

		for (auto pt = Tree2_RootToSon_NameRelationRight.begin(); pt != Tree2_RootToSon_NameRelationRight.end(); pt++)
		{
			Tree2_NameToNode[pt->first] = NULL;
			Tree2_NameToNode[pt->second] = NULL;
		}
		// 先建立名字空间

		// 再根据名字空间去申请节点
		for (auto pt = Tree2_NameToNode.begin(); pt != Tree2_NameToNode.end(); pt++)
		{
			Node* tmp = new Node(pt->first, NULL, NULL);
			pt->second = tmp;
		}
		//progressbar2refresh(50);
	}

}


void VisualizeMain::Tree1_Build()
{
	if (Tree1_iflegal == true)
	{
		for (auto pt = Tree1_RootToSon_NameRelationLeft.begin(); pt != Tree1_RootToSon_NameRelationLeft.end(); pt++)
		{
			Tree1_NameToNode[pt->first]->left = Tree1_NameToNode[pt->second];
			//cout << pt->first << pt->second << "conbined " << endl;
		}

		for (auto pt = Tree1_RootToSon_NameRelationRight.begin(); pt != Tree1_RootToSon_NameRelationRight.end(); pt++)
		{
			Tree1_NameToNode[pt->first]->right = Tree1_NameToNode[pt->second];
			//cout << pt->first << pt->second << "conbined " << endl;
		}

		//再刷新一下根节点
		string startstr = Tree1_RootToSon_NameRelationLeft.begin()->second;
		
		while (1)
		{
			bool iffind1 = false;
			bool iffind2 = false;
			for (auto pt = Tree1_RootToSon_NameRelationLeft.begin(); pt != Tree1_RootToSon_NameRelationLeft.end(); pt++)
			{
				if ((pt->second) == startstr)
				{
					startstr = pt->first;
					iffind1 = true;
					break;
				}
			}

			for (auto pt = Tree1_RootToSon_NameRelationRight.begin(); pt != Tree1_RootToSon_NameRelationRight.end(); pt++)
			{
				if ((pt->second) == startstr)
				{
					startstr = pt->first;
					iffind1 = true;
					break;
				}
			}

			if (iffind1 == false && iffind2 == false)
			{
				break;
			}

		}

		Tree1_realRootNode = Tree1_NameToNode[startstr];
		
		cout << startstr << "这个是找到的根节点" << endl;
	}
	

}


void VisualizeMain::Tree2_Build()
{
	if (Tree2_iflegal == true)
	{
		for (auto pt = Tree2_RootToSon_NameRelationLeft.begin(); pt != Tree2_RootToSon_NameRelationLeft.end(); pt++)
		{
			Tree2_NameToNode[pt->first]->left = Tree2_NameToNode[pt->second];
		}

		for (auto pt = Tree2_RootToSon_NameRelationRight.begin(); pt != Tree2_RootToSon_NameRelationRight.end(); pt++)
		{
			Tree2_NameToNode[pt->first]->right = Tree2_NameToNode[pt->second];
		}

		//再刷新一下根节点
		string startstr = Tree2_RootToSon_NameRelationLeft.begin()->second;

		while (1)
		{
			bool iffind1 = false;
			bool iffind2 = false;
			for (auto pt = Tree2_RootToSon_NameRelationLeft.begin(); pt != Tree2_RootToSon_NameRelationLeft.end(); pt++)
			{
				if ((pt->second) == startstr)
				{
					startstr = pt->first;
					iffind1 = true;
					break;
				}
			}

			for (auto pt = Tree2_RootToSon_NameRelationRight.begin(); pt != Tree2_RootToSon_NameRelationRight.end(); pt++)
			{
				if ((pt->second) == startstr)
				{
					startstr = pt->first;
					iffind1 = true;
					break;
				}
			}

			if (iffind1 == false && iffind2 == false)
			{
				break;
			}

		}

		Tree2_realRootNode = Tree2_NameToNode[startstr];
		cout << startstr << "这个是找到的根节点" << endl;
		
		
	}
	
}

void VisualizeMain::Tree1_draw()
{
	Tree1_heightRefresh(Tree1_realRootNode, 1);
	Tree1_NodepositionRefresh(Tree1_realRootNode, NULL);
	
	cout << "tree1 h=" << Tree1_height << endl;
	
	Tree1_attachNow(Tree1_realRootNode);
	//progressbar2refresh(75);
}


void VisualizeMain::Tree2_draw()
{
	Tree2_heightRefresh(Tree2_realRootNode, 1);
	Tree2_NodepositionRefresh(Tree2_realRootNode, NULL);

	cout << "tree2 h=" << Tree2_height << endl;
	
	Tree2_attachNow(Tree2_realRootNode);
	//progressbar2refresh(100);
}





bool VisualizeMain::if_isomorphism(Node* tree1, Node* tree2)
{
	if (tree1 == NULL && tree2 == NULL)
		return 1;
	if ((tree1 != NULL && tree2 == NULL) || (tree2 != NULL && tree1 == NULL))
		return false;
	if (if_isomorphism(tree1->left, tree2->left) == true && if_isomorphism(tree1->right, tree2->right) == true)
		return true;
	if (if_isomorphism(tree1->left, tree2->right) == true && if_isomorphism(tree1->right, tree2->left) == true)
	{
		Node* tmp = tree2->right;
		tree2->right = tree2->left;
		tree2->left = tmp;
		return true;
	}
}


// 一大轮结束后 才允许调用！
void VisualizeMain::STSTEM_var_refresh()
{
	currentfilePlace.clear();
	ManualfilePlace.clear();
	OriginalAllfilePlace.clear();					// 保存原始的所有文件的目录 检索支持子目录
	FinalPlaceResult.clear();						// 保存筛选后的最终的 txt，csv，或者其他类型的树文件
	isomorphismNameToName1.clear();

	
}



void VisualizeMain::Tree1_free()
{
	Tree1_clear();
}



void VisualizeMain::Tree2_free()
{
	Tree2_clear();
}

void VisualizeMain::Tree1_heightRefresh(Node* curnode, int curHeight)
{
	if (curnode != NULL)
	{
		curnode->height = curHeight;
		cout << "当前节点" << curnode->NodeName << endl;
		Tree1_height = (curHeight > Tree1_height) ? curHeight : Tree1_height;
		if (curnode->left != NULL)
		{
			Tree1_heightRefresh(curnode->left, curHeight + 1);
			//cout << "开始递归第" << curHeight + 1 << endl;
		}

		if (curnode->right != NULL)
		{
			Tree1_heightRefresh(curnode->right, curHeight + 1);
			//cout << "开始递归第" << curHeight + 1 << endl;
		}
	}
}


void VisualizeMain::Tree2_heightRefresh(Node* curnode, int curHeight)
{
	if (curnode != NULL)
	{
		curnode->height = curHeight;
		Tree2_height = (curHeight > Tree2_height) ? curHeight : Tree2_height;
		if (curnode->left != NULL)
		{
			Tree2_heightRefresh(curnode->left, curHeight + 1);
		}

		if (curnode->right != NULL)
		{
			Tree2_heightRefresh(curnode->right, curHeight + 1);
		}
	}
}


void VisualizeMain::Tree1_NodepositionRefresh(Node* curnode, Node* lastnode)
{
	if (curnode != NULL)
	{
		if (curnode->height > 7)
			return;
		else if (lastnode == NULL)
		{
			//cout << "1开始计算" << curnode->NodeName << endl;
			curnode->xxPosition = int(0.135 * x_max() + 0.4325 * 0.5 * x_max());
			curnode->yyPosition = int(y_max() * (curnode->height - 0.5) * 0.9 / Tree1_height);
			curnode->xxScale = 0.4325 * x_max();
			curnode->yyScale = 0.9 * y_max() / Tree1_height;

			if (curnode->left != NULL)
			{
				Tree1_NodepositionRefresh(curnode->left, curnode);
				
			}

			if (curnode->right != NULL)
			{
				Tree1_NodepositionRefresh(curnode->right, curnode);
				
			}

		}
		else if (lastnode != NULL)
		{
			curnode->xxScale = (lastnode->xxScale) / 2 ;
			curnode->yyScale = lastnode->yyScale;
			if (curnode == (lastnode->left))
			{
				curnode->xxPosition = lastnode->xxPosition - (curnode->xxScale) / 2;
				curnode->yyPosition = lastnode->yyPosition + curnode->yyScale;
			}

			else if (curnode == (lastnode->right))
			{
				curnode->xxPosition = lastnode->xxPosition + (curnode->xxScale) / 2;
				curnode->yyPosition = lastnode->yyPosition + curnode->yyScale;
			}

			
			if (curnode != NULL && curnode->left != NULL)
			{
				
				Tree1_NodepositionRefresh(curnode->left, curnode);
			}
			

			if (curnode != NULL && curnode->right != NULL)
			{
				
				Tree1_NodepositionRefresh(curnode->right, curnode);
			}
			

		}

	}
}



void VisualizeMain::Tree2_NodepositionRefresh(Node* curnode, Node* lastnode)
{
	if (curnode != NULL)
	{
		if (curnode->height > 7)
			return;
		else if (lastnode == NULL)
		{
			//cout << "1开始计算" << curnode->NodeName << endl;
			curnode->xxPosition = int(0.5675 * x_max() + 0.4325 * 0.5 * x_max());
			curnode->yyPosition = int(y_max() * (curnode->height - 0.5) * 0.9 / Tree2_height);
			curnode->xxScale = 0.4325 * x_max();
			curnode->yyScale = 0.9 * y_max() / Tree2_height;

			if (curnode->left != NULL)
			{
				Tree2_NodepositionRefresh(curnode->left, curnode);

			}

			if (curnode->right != NULL)
			{
				Tree2_NodepositionRefresh(curnode->right, curnode);

			}

		}
		else if (lastnode != NULL)
		{
			curnode->xxScale = (lastnode->xxScale) / 2;
			curnode->yyScale = lastnode->yyScale;
			if (curnode == (lastnode->left))
			{
				curnode->xxPosition = lastnode->xxPosition - (curnode->xxScale) / 2;
				curnode->yyPosition = lastnode->yyPosition + curnode->yyScale;
			}

			else if (curnode == (lastnode->right))
			{
				curnode->xxPosition = lastnode->xxPosition + (curnode->xxScale) / 2;
				curnode->yyPosition = lastnode->yyPosition + curnode->yyScale;
			}


			if (curnode != NULL && curnode->left != NULL)
			{

				Tree2_NodepositionRefresh(curnode->left, curnode);
			}


			if (curnode != NULL && curnode->right != NULL)
			{

				Tree2_NodepositionRefresh(curnode->right, curnode);
			}
		}
	}
}


void VisualizeMain::Tree1_attachNow(Node* obj)							// 实际画图函数
{
	if (obj != NULL)
	{
		Tree1_Circle.push_back(new Graph_lib::Circle(Point(obj->xxPosition, obj->yyPosition), int(0.3 * min(obj->xxScale, obj->yyScale))));
		Tree1_Circle[Tree1_Circle.size() - 1].set_color(Color::black);
		attach(Tree1_Circle[Tree1_Circle.size() - 1]);

		Tree1_Text.push_back(new Text(Point(obj->xxPosition, obj->yyPosition), obj->NodeName));
		Tree1_Text[Tree1_Text.size() - 1].set_color(Color::blue);
		attach(Tree1_Text[Tree1_Text.size() - 1]);

		int r1dx = (0.3 * min(obj->xxScale, obj->yyScale)) * (obj->xxScale / 2) / sqrt((obj->xxScale / 2) * (obj->xxScale / 2) + (obj->yyScale * obj->yyScale));
		int r1dy = (0.3 * min(obj->xxScale, obj->yyScale)) * (obj->yyScale) / sqrt((obj->xxScale / 2) * (obj->xxScale / 2) + (obj->yyScale) * (obj->yyScale));
		


		if (obj->left != NULL)
		{
			Node* tmp1 = obj->left;
			int r2dx = 0.3 * min(tmp1->xxScale, tmp1->yyScale) * (tmp1->xxScale / 2) / sqrt((tmp1->xxScale / 2) * (tmp1->xxScale / 2) + (tmp1->yyScale * tmp1->yyScale));
			int r2dy = 0.3 * min(tmp1->xxScale, tmp1->yyScale) * tmp1->yyScale / sqrt((tmp1->xxScale / 2) * (tmp1->xxScale / 2) + (tmp1->yyScale * tmp1->yyScale));
			
			Tree1_Line.push_back(new Graph_lib::Line(Point(obj->xxPosition - r1dx, obj->yyPosition + r1dy), Point(obj->left->xxPosition + r2dx, obj->left->yyPosition - r2dy)));
			Tree1_Line[Tree1_Line.size() - 1].set_color(Color::black);
			attach(Tree1_Line[Tree1_Line.size() - 1]);
			Tree1_attachNow(obj->left);
			Fl::redraw();
		}

		if (obj->right != NULL)
		{
			Node* tmp1 = obj->right;
			int r3dx = 0.3 * min(tmp1->xxScale, tmp1->yyScale) * (tmp1->xxScale / 2) / sqrt((tmp1->xxScale / 2) * (tmp1->xxScale / 2) + (tmp1->yyScale * tmp1->yyScale));
			int r3dy = 0.3 * min(tmp1->xxScale, tmp1->yyScale) * tmp1->yyScale / sqrt((tmp1->xxScale / 2) * (tmp1->xxScale / 2) + (tmp1->yyScale * tmp1->yyScale));


			Tree1_Line.push_back(new Graph_lib::Line(Point(obj->xxPosition + r1dx, obj->yyPosition + r1dy), Point(obj->right->xxPosition - r3dx, obj->right->yyPosition - r3dy)));
			Tree1_Line[Tree1_Line.size() - 1].set_color(Color::black);
			attach(Tree1_Line[Tree1_Line.size() - 1]);
			Tree1_attachNow(obj->right);
			Fl::redraw();
		}
	}
	
}

void VisualizeMain::Tree2_attachNow(Node* obj)							// 实际画图函数
{
	if (obj != NULL)
	{
		Tree2_Circle.push_back(new Graph_lib::Circle(Point(obj->xxPosition, obj->yyPosition), int(0.3 * min(obj->xxScale, obj->yyScale))));
		Tree2_Circle[Tree2_Circle.size() - 1].set_color(Color::black);
		attach(Tree2_Circle[Tree2_Circle.size() - 1]);

		Tree2_Text.push_back(new Text(Point(obj->xxPosition, obj->yyPosition), obj->NodeName));
		Tree2_Text[Tree2_Text.size() - 1].set_color(Color::blue);
		attach(Tree2_Text[Tree2_Text.size() - 1]);

		int r1dx = 0.3 * min(obj->xxScale, obj->yyScale) * (obj->xxScale / 2) / sqrt((obj->xxScale / 2) * (obj->xxScale / 2) + (obj->yyScale * obj->yyScale));
		int r1dy = 0.3 * min(obj->xxScale, obj->yyScale) * (obj->yyScale) / sqrt((obj->xxScale / 2) * (obj->xxScale / 2) + (obj->yyScale) * (obj->yyScale));



		if (obj->left != NULL)
		{
			Node* tmp1 = obj->left;
			int r2dx = 0.3 * min(tmp1->xxScale, tmp1->yyScale) * (tmp1->xxScale / 2) / sqrt((tmp1->xxScale / 2) * (tmp1->xxScale / 2) + (tmp1->yyScale * tmp1->yyScale));
			int r2dy = 0.3 * min(tmp1->xxScale, tmp1->yyScale) * tmp1->yyScale / sqrt((tmp1->xxScale / 2) * (tmp1->xxScale / 2) + (tmp1->yyScale * tmp1->yyScale));

			Tree2_Line.push_back(new Graph_lib::Line(Point(obj->xxPosition - r1dx, obj->yyPosition + r1dy), Point(obj->left->xxPosition + r2dx, obj->left->yyPosition - r2dy)));
			Tree2_Line[Tree2_Line.size() - 1].set_color(Color::black);
			attach(Tree2_Line[Tree2_Line.size() - 1]);
			Tree2_attachNow(obj->left);
			Fl::redraw();
		}

		if (obj->right != NULL)
		{
			Node* tmp1 = obj->right;
			int r3dx = 0.3 * min(tmp1->xxScale, tmp1->yyScale) * (tmp1->xxScale / 2) / sqrt((tmp1->xxScale / 2) * (tmp1->xxScale / 2) + (tmp1->yyScale * tmp1->yyScale));
			int r3dy = 0.3 * min(tmp1->xxScale, tmp1->yyScale) * tmp1->yyScale / sqrt((tmp1->xxScale / 2) * (tmp1->xxScale / 2) + (tmp1->yyScale * tmp1->yyScale));


			Tree2_Line.push_back(new Graph_lib::Line(Point(obj->xxPosition + r1dx, obj->yyPosition + r1dy), Point(obj->right->xxPosition - r3dx, obj->right->yyPosition - r3dy)));
			Tree2_Line[Tree2_Line.size() - 1].set_color(Color::black);
			attach(Tree2_Line[Tree2_Line.size() - 1]);
			Tree2_attachNow(obj->right);
			Fl::redraw();
		}
	}
	
}





// 下面的函数属于控制台的临时打印输出
// --------------------------------------------------------------------------------------------------------------------------------
void VisualizeMain::TmpPrinter_Tree1_RootToSon_NameRelation()
{
	for (auto iter = Tree1_RootToSon_NameRelationLeft.begin(); iter != Tree1_RootToSon_NameRelationLeft.end(); iter++)
	{
		cout << iter->first << " " << iter->second << endl;
	}

	for (auto iter = Tree1_RootToSon_NameRelationRight.begin(); iter != Tree1_RootToSon_NameRelationRight.end(); iter++)
	{
		cout << iter->first << " " << iter->second << endl;
	}

}


void VisualizeMain::TmpPrinter_Tree2_RootToSon_NameRelation()
{
	for (auto iter = Tree2_RootToSon_NameRelationLeft.begin(); iter != Tree2_RootToSon_NameRelationLeft.end(); iter++)
	{
		cout << iter->first << " " << iter->second << endl;
	}

	for (auto iter = Tree2_RootToSon_NameRelationRight.begin(); iter != Tree2_RootToSon_NameRelationRight.end(); iter++)
	{
		cout << iter->first << " " << iter->second << endl;
	}


}


void VisualizeMain::TmpPrinter_isomorphismNameToName1()
{
	for (auto iter = isomorphismNameToName1.begin(); iter != isomorphismNameToName1.end(); iter++)
	{
		cout << iter->first << " " << iter->second << endl;
	}
}


// --------------------------------------------------------------------------------------------------------------------------------

void VisualizeMain::isomorphismLink(Node* tree1, Node* tree2)
{
	if (tree1 != NULL && tree2 != NULL)
	{
		isomorphismNameToName1[tree1->NodeName] = tree2->NodeName;
		isomorphismNameToName2[tree2->NodeName] = tree1->NodeName;
	}
		
	if (tree1->left != NULL && tree2->left != NULL)
		isomorphismLink(tree1->left, tree2->left);
	if (tree1->right != NULL && tree2->right != NULL)
		isomorphismLink(tree1->right, tree2->right);
}



// 下面的函数属于辅助功能 进度条
// --------------------------------------------------------------------------------------------------------------------------------
void VisualizeMain::progressbar1refresh(int num)
{	
	if (vec1.size() != 0)
	{
		for (int i = 0; i < vec1.size(); i++)
		{
			detach(vec1[i]);
		}
	}


	vec1.push_back(new Graph_lib::Rectangle (Point{ int(0.025 * x_max()),int(0.045 * x_max()) }, Point{ int((0.025 + 0.1 * num / 100) * x_max()),int(0.060 * x_max()) }));
	vec1[vec1.size() - 1].set_fill_color(250);
	attach(vec1[vec1.size() - 1]);
	
	Fl::redraw();
}


void VisualizeMain::progressbar2refresh(int num)
{
	if (vec2.size() != 0)
	{
		for (int i = 0; i < vec2.size(); i++)
		{
			detach(vec2[i]);
		}
	}

	vec2.push_back(new Graph_lib::Rectangle(Point{ int(0.025 * x_max()),int(0.085 * x_max()) }, Point{ int((0.025 + 0.1 * num / 100) * x_max()),int(0.100 * x_max()) }));
	vec2[vec2.size() - 1].set_fill_color(250);
	attach(vec2[vec2.size() - 1]);
	Fl::redraw();
}

void VisualizeMain::progressbar3refresh(int num)
{
	if (vec3.size() != 0)
	{
		for (int i = 0; i < vec3.size(); i++)
		{
			detach(vec3[i]);
		}
	}

	vec3.push_back(new Graph_lib::Rectangle(Point{ int(0.025 * x_max()),int(0.125 * x_max()) }, Point{ int((0.025 + 0.1 * num / 100) * x_max()),int(0.140 * x_max()) }));
	vec3[vec3.size() - 1].set_fill_color(250);
	attach(vec3[vec3.size() - 1]);
	Fl::redraw();
}

void VisualizeMain::progressbar4refresh(int num)
{
	if (vec4.size() != 0)
	{
		for (int i = 0; i < vec4.size(); i++)
		{
			detach(vec4[i]);
		}
	}

	vec4.push_back(new Graph_lib::Rectangle(Point{ int(0.025 * x_max()),int(0.165 * x_max()) }, Point{ int((0.025 + 0.1 * num / 100) * x_max()),int(0.180 * x_max()) }));
	vec4[vec4.size() - 1].set_fill_color(250);
	attach(vec4[vec4.size() - 1]);
	Fl::redraw();
}



void VisualizeMain::buttonPressed_findRelated()
{
	bool iffindthis = false;
	string tmp = NodeNameIn.get_string();
	string outmes;
	if (ifsimular == true)
		outmes += "【信息】同构且已经可视化完成 ";
	else
	{
		outmes += "【信息】不同构，请勿点击匹配按钮 ";
		infoOut.put(outmes);
		return;
	}
	
	// 每次按钮颜色刷新前先要把按钮的颜色全部都初始化一次
	// 然后再去查找目标的圆圈 设置对应的颜色
	for (int i = 0; i < Tree1_Circle.size(); i++)
	{
		Tree1_Circle[i].set_fill_color(254);
		attach(Tree1_Circle[i]);
		attach(Tree1_Text[i]);
		Fl::redraw();
	}

	for (int i = 0; i < Tree2_Circle.size(); i++)
	{
		Tree2_Circle[i].set_fill_color(254);
		attach(Tree2_Circle[i]);
		attach(Tree2_Text[i]);
		Fl::redraw();
	}
	


	if ((isomorphismNameToName1.count(tmp)) >= 1)
	{
		
		outmes += tmp;
		outmes += "匹配";
		outmes += isomorphismNameToName1[tmp];
		outmes += " ";
		iffindthis = true;

		
		for (int i = 0; i < Tree1_Circle.size(); i++)
		{

			if (Tree1_Circle[i].center().x == Tree1_NameToNode[tmp]->xxPosition && Tree1_Circle[i].center().y == Tree1_NameToNode[tmp]->yyPosition)
			{
				Tree1_Circle[i].set_fill_color(250);
				
				//attach(Tree1_Circle[i]);
				//attach(Tree1_Text[i]);
				Fl::redraw();
			}
		}
		
		for (int i = 0; i < Tree2_Circle.size(); i++)
		{
				
			if (Tree2_Circle[i].center().x == Tree2_NameToNode[isomorphismNameToName1[tmp]]->xxPosition && Tree2_Circle[i].center().y == Tree2_NameToNode[isomorphismNameToName1[tmp]]->yyPosition)
			{
				Tree2_Circle[i].set_fill_color(250);

				//attach(Tree2_Circle[i]);
				//attach(Tree2_Text[i]);
				Fl::redraw();
			}
		}


		
	}

	if ((isomorphismNameToName2.count(tmp)) >= 1)
	{
		outmes += tmp;
		outmes += "匹配";
		outmes += isomorphismNameToName2[tmp];
		outmes += " ";
		iffindthis = true;


		for (int i = 0; i < Tree2_Circle.size(); i++)
		{
			
			
			if (Tree2_Circle[i].center().x == Tree2_NameToNode[tmp]->xxPosition && Tree2_Circle[i].center().y == Tree2_NameToNode[tmp]->yyPosition)
			{
				Tree2_Circle[i].set_fill_color(250);

				//attach(Tree2_Circle[i]);
				//attach(Tree2_Text[i]);
				Fl::redraw();
			}


		}

		for (int i = 0; i < Tree1_Circle.size(); i++)
		{
			
			
			
			if (Tree1_Circle[i].center().x == Tree1_NameToNode[isomorphismNameToName2[tmp]]->xxPosition && Tree1_Circle[i].center().y == Tree1_NameToNode[isomorphismNameToName2[tmp]]->yyPosition)
			{
				Tree1_Circle[i].set_fill_color(250);

				//attach(Tree1_Circle[i]);
				//attach(Tree1_Text[i]);
				Fl::redraw();
			}
		}




	}

	if (iffindthis == false)
	{
		outmes += "输入不对，请重新输入";
	}

	infoOut.put(outmes);

}


void VisualizeMain::Tree1_drawClear()
{
	for (int i = 0; i < Tree1_Circle.size(); i++)
	{
		detach(Tree1_Circle[i]);
	}

	for (int i = 0; i < Tree1_Line.size(); i++)
	{
		detach(Tree1_Line[i]);
	}

	for (int i = 0; i < Tree1_Text.size(); i++)
	{
		detach(Tree1_Text[i]);
	}
	Tree1_Circle.clearVector();
	Tree1_Line.clearVector();
	Tree1_Text.clearVector();
	

	Fl::redraw();
}


void VisualizeMain::Tree2_drawClear()
{
	
	for (int i = 0; i < Tree2_Circle.size(); i++)
	{
		detach(Tree2_Circle[i]);
	}

	for (int i = 0; i < Tree2_Line.size(); i++)
	{
		detach(Tree2_Line[i]);
	}

	for (int i = 0; i < Tree2_Text.size(); i++)
	{
		detach(Tree2_Text[i]);
	}
	Tree2_Circle.clearVector();
	Tree2_Line.clearVector();
	Tree2_Text.clearVector();


	Fl::redraw();
}




void VisualizeMain::Tree1_clear()
{
	Tree1_drawClear();
	
	for (auto iter = Tree1_NameToNode.begin(); iter != Tree1_NameToNode.end(); iter++)
	{
		delete iter->second;
	}

	for (int i = 0; i < Tree1_detectingArea.size(); i++)
	{
		delete Tree1_detectingArea[i];
	}

	Tree1_iflegal = true;
	Tree1_height = -1;
	Tree1_OriginalData.clear();
	Tree1_RootToSon_NameRelationLeft.clear();
	Tree1_RootToSon_NameRelationRight.clear();
	Tree1_NameToNode.clear();
	Tree1_detectingArea.clear();

}



void VisualizeMain::Tree2_clear()
{
	Tree2_drawClear();

	for (auto iter = Tree2_NameToNode.begin(); iter != Tree2_NameToNode.end(); iter++)
	{
		delete iter->second;
	}

	for (int i = 0; i < Tree2_detectingArea.size(); i++)
	{
		delete Tree2_detectingArea[i];
	}

	Tree2_iflegal = true;
	Tree2_height = -1;
	Tree2_OriginalData.clear();
	Tree2_RootToSon_NameRelationLeft.clear();
	Tree2_RootToSon_NameRelationRight.clear();
	Tree2_NameToNode.clear();
	Tree2_detectingArea.clear();

}

void VisualizeMain::DetectingAreaGenerator()
{
	
	for (auto iter = Tree1_NameToNode.begin(); iter != Tree1_NameToNode.end(); iter++)
	{
		int xxp = iter->second->xxPosition;
		int yyp = iter->second->yyPosition;
		int len = int(0.6 * min(iter->second->xxScale, iter->second->yyScale));

		xxp = xxp - len / 2;
		yyp = yyp - len / 2;

		//cout << "开始产生1" << endl;
		begin();
		MatchingButton* tmp = new MatchingButton(xxp, yyp, len, len, iter->first);
		tmp->callback(cb);
		end();
		Fl::redraw();
		Tree1_detectingArea.push_back(tmp);
	}

	for (auto iter = Tree2_NameToNode.begin(); iter != Tree2_NameToNode.end(); iter++)
	{
		int xxp = iter->second->xxPosition;
		int yyp = iter->second->yyPosition;
		int len = int(0.6 * min(iter->second->xxScale, iter->second->yyScale));

		xxp = xxp - len / 2;
		yyp = yyp - len / 2;

		//cout << "开始产生1" << endl;
		begin();
		MatchingButton* tmp = new MatchingButton(xxp, yyp, len, len, iter->first);
		tmp->callback(cb);
		end();
		Fl::redraw();
		Tree2_detectingArea.push_back(tmp);
	}




}


void VisualizeMain::ButtonMatchingGenetor()
{
	cout << "strat Matching" << endl;
	for (int i = 0; i < Tree1_detectingArea.size(); i++)
	{
		string tmp = Tree1_detectingArea[i]->NodeName;
		
		for (int j = 0; j < Tree1_Circle.size(); j++)
		{
			if (Tree1_Circle[j].center().x == Tree1_NameToNode[tmp]->xxPosition && Tree1_Circle[j].center().y == Tree1_NameToNode[tmp]->yyPosition)
			{
				Tree1_detectingArea[i]->thisCircle = &(Tree1_Circle[j]);
				cout << "Binding !!" << endl;
				break;
			}

		}

		for (int j = 0; j < Tree2_Circle.size(); j++)
		{

			if (Tree2_Circle[j].center().x == Tree2_NameToNode[isomorphismNameToName1[tmp]]->xxPosition && Tree2_Circle[j].center().y == Tree2_NameToNode[isomorphismNameToName1[tmp]]->yyPosition)
			{
				Tree1_detectingArea[i]->matchingCircle = &(Tree2_Circle[j]);
				cout << "Binding !!" << endl;
				break;
			}
		}
		
	}


	for (int i = 0; i < Tree2_detectingArea.size(); i++)
	{
		string tmp = Tree2_detectingArea[i]->NodeName;

		for (int j = 0; j < Tree1_Circle.size(); j++)
		{
			if (Tree2_Circle[j].center().x == Tree2_NameToNode[tmp]->xxPosition && Tree2_Circle[j].center().y == Tree2_NameToNode[tmp]->yyPosition)
			{
				Tree2_detectingArea[i]->thisCircle = &(Tree2_Circle[j]);
				break;
			}

		}

		for (int j = 0; j < Tree1_Circle.size(); j++)
		{

			if (Tree1_Circle[j].center().x == Tree1_NameToNode[isomorphismNameToName2[tmp]]->xxPosition && Tree1_Circle[j].center().y == Tree1_NameToNode[isomorphismNameToName2[tmp]]->yyPosition)
			{
				Tree2_detectingArea[i]->matchingCircle = &(Tree1_Circle[j]);
				break;
			}

			
		}

	}

}

*/