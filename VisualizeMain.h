#ifndef _VisualizeMain_h
#define _VisualizeMain_h

#include <fstream>
#include <direct.h>
#include "GUI.h"
#include <io.h>
#include "Window.h"
#include "Simple_window.h"
#include "Graph.h"
#include "Point.h"
#include <iostream>
#include "std_lib_facilities.h"
#include "MatchingButton.h"
#include <time.h>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <queue>


using namespace Graph_lib;

class Node
{
public:
	string nodeName;
	vector<Node*> childNode;
	int xxScale;
	int yyScale;
	int xxPositon;
	int yyPositon;
	int height;
	int RankInHeight;		// height-RankInHeight 反映节点的位置坐标
	bool iflegal;			// 是否有效的节点 开始的时候默认为非法节点，当在树的构建中操作后认定为合法节点
	bool ifVIsualize;
	Node* matchingNode;

	Node()
	{
		nodeName = "";
		xxScale = 0;
		yyScale = 0;
		xxPositon = 0;
		yyPositon = 0;
		height = 0;
		RankInHeight = 0;
		iflegal = false;
		ifVIsualize = false;
		matchingNode = NULL;
	}

	Node(string namestr)
	{
		nodeName = namestr;
		xxScale = 0;
		yyScale = 0;
		xxPositon = 0;
		yyPositon = 0;
		height = 0;
		RankInHeight = 0;
		iflegal = false;
		ifVIsualize = false;
		matchingNode = NULL;
	}
};


class VisualizeMain : Window
{
	friend class TreeVisualize;
	friend class Node;
public:
	VisualizeMain(int width, int height);
	

private:
	// ------------------------------------------------------------------------------------------------------------------
	// ---------------------------------------------以下是基础图形变量----------------------------------------------------
	// 基础变量数据 屏幕像素数据
	int ScreenWidth;
	int ScreenHeight;

	// 基础控件数据 包括按钮 这些数据的即使在清空按钮点下之后都不会改变，属于背景类型
	// 基础按钮
	Button button_exit;
	Button button_readfileAuto;
	Button button_readfileManu;
	Button button_refresh;
	Button button_nextRead;
	Button button_findRelated;

	// 按钮控件所对应的函数调用！
	void buttonPressed_exit();
	void buttonPressed_readfileAuto();
	void buttonPressed_readfileManu();
	void buttonPressed_refresh();
	void buttonPressed_nextRead();
	void buttonPressed_findRelated();




	// 基础图形 进度条
	Graph_lib::Rectangle processBar1;
	Graph_lib::Rectangle processBar2;
	Graph_lib::Rectangle processBar3;
	Graph_lib::Rectangle processBar4;
	Vector_ref<Graph_lib::Rectangle> vec1;
	Vector_ref<Graph_lib::Rectangle> vec2;
	Vector_ref<Graph_lib::Rectangle> vec3;
	Vector_ref<Graph_lib::Rectangle> vec4;

	// 基础图形 进度条 四个进度条控制中心
	void progressbar1refresh(int num);
	void progressbar2refresh(int num);
	void progressbar3refresh(int num);
	void progressbar4refresh(int num);


	// 基础图形 分割线条
	Graph_lib::Line line1;
	Graph_lib::Line line2;

	// 基础图形 输入框和输出框
	In_box inputbox;
	Out_box infoOut;
	In_box NodeNameIn;

	// 基础信息 进度条标题
	Text processBar1Title;
	Text processBar2Title;
	Text processBar3Title;
	Text processBar4Title;
	Text inboxTitle;
	Text infoOutTitle;
	Text inputreminderText;

	// ---------------------------------------------以上是基础图形变量----------------------------------------------------
	// ------------------------------------------------------------------------------------------------------------------




	// --------下面的是系统变量模块--------下面的是系统变量模块--------下面的是系统变量模块--------下面的是系统变量模块--------下面的是系统变量模块--------
	// -----------------------------------------------------------------------------------------------------------------------------------------
	// 特别警告！谨慎刷新！特别警告！谨慎刷新！特别警告！谨慎刷新！特别警告！谨慎刷新！特别警告！谨慎刷新！特别警告！谨慎刷新！特别警告！谨慎刷新！特别警告！谨慎刷新！
	// 模块涉及到文件信息！模块涉及到文件信息！模块涉及到文件信息！模块涉及到文件信息！模块涉及到文件信息！模块涉及到文件信息！模块涉及到文件信息！
	// 
	// 
	// 每次处理一大轮（就是说文件队列清空之后算一大轮）后，下面的所有的变量才允许刷新清空
	// 但是，一小轮结束后，只需要清空画布，两个树相关的执行回收即可
	// 后台变量
	// ------------------------------------------------------------------------------------------------------------------
	string currentfilePlace;								// 自动读取的文件目录
	string ManualfilePlace;									// 手动输入的文件目录
	vector <string> OriginalAllfilePlace;					// 保存原始的所有文件的目录 检索支持子目录
	vector <string> FinalPlaceResult;						// 保存筛选后的最终的 txt，csv，或者其他类型的树文件
	map <string, string> isomorphismNameToName1_2;			// 同构关系的保存 tree1 -> tree2
	map <string, string> isomorphismNameToName2_1;			// 同构关系的保存 tree2 -> tree1

	// 后台变量的控制函数
	// ------------------------------------------------------------------------------------------------------------------
	
	void findCurrentPlace();
	void PrimefileFocus(string path, vector<string>& files);
	bool if_Select(string& obj);
	void Selector(vector<string>& beforeSel, vector<string>& AfterSel);
	
	void STSTEM_var_refresh();

	// STSTEM_var_refresh();控制文件信息的刷新 不涉及树相关的信息的刷新
	// ------------------------------------------------------------------------------------------------------------------








	// 树相关的实现构想，原始的字符串读取 读取文件后写入 Tree1_OriginalData
	// 然后解析 Tree1_OriginalData 的每一行元素 
	// 用->为分隔符 检查每一行的合法性
	// 合法:分割之后建立 原始文件中左名字到右名字的映射 所有节点的名字空间（映射的值 初始化为NULL）
	// 非法:计数但是不报错停止，直接忽略非法行
	// 如果在读取中出现错误，在信息框予以提示
	// 然后利用 Tree1_RootToSon_NameRelation（原始文件左名字到右名字的映射） 构建爸爸节点名字到孩子节点名字空间的映射
	// 
	// 
	// 

	// center master函数 在阅读完目录后，所有的控制权交给下面的这个函数 每次处理两个文件 文件不足不予处理
	
	// ------------------------------------------------------------------------------------------------------------------
	
	
	
	
	int TreeCenterMaster();											// read and deal with Two tree file!
	bool if_isomorphism(Node* tree1, Node* tree2);
	void Tree_detectingAreaGenerator();								// 产生探测区域 同构才允许使用
	void ButtonMatching();											// 按钮绑定

	bool ifsimular;													// 是否同构
														
	// tree1
	bool Tree1_iflegal;												// 树的合法 通讯工具
	int Tree1_height;												// 树的高度
	int Tree1_OriginalDataError;									// 原始的字符串读取的错误计数器
	int Tree1_NodeError;											// 节点的错误计数器
	int Tree1_Height;												// 树的高度
	Node* Tree1_realRootNode;										// 真实的树的一级节点
	vector<string> Tree1_OriginalData;								// 原始的字符串读取 读取文件后写入这个数组 再解析
	map<string, vector<string>> Tree1_RootToSon_NameRelation;		// 根节点到儿子映射
	map<string, Node*> Tree1_NameToNode;							// 由节点名字到该节点指针的映射 key值相当于树的节点的名字空间 
	map<int, vector<Node*>> Tree1_heightToNode;						// 高度到节点指针的集合
	Vector_ref<Circle> Tree1_Circle;								// 树一的圆圈集合！
	Vector_ref<Line> Tree1_Line;									// 树一的直线集合！
	Vector_ref<Text> Tree1_Text;									// 树一的文本集合！
	vector<MatchingButton*> Tree1_detectingArea;					// 树一的监测区域
	
	
	void Tree1_OriginalData_Get();
	void Tree1_OriginalData_Analysis();
	void Tree1_NameToNode_Build();
	void Tree1_Build();
	void Tree1_clear();
	void Tree1_heightRefresh(Node* curnode, int curHeight);			// tree1 高度刷新
	void Tree1_RankInHeightRefresh();								// tree1 节点排名刷新
	void Tree1_PositionRefresh();
	void Tree1_draw();
	

	// tree2
	bool Tree2_iflegal;												// 树的合法 通讯工具
	int Tree2_height;												// 树的高度
	int Tree2_OriginalDataError;									// 原始的字符串读取的错误计数器
	int Tree2_NodeError;											// 节点的错误计数器
	int Tree2_Height;												// 树的高度
	Node* Tree2_realRootNode;										// 真实的树的一级节点
	vector<string> Tree2_OriginalData;								// 原始的字符串读取 读取文件后写入这个数组 再解析
	map<string, vector<string>> Tree2_RootToSon_NameRelation;		// 根节点到儿子映射
	map<string, Node*> Tree2_NameToNode;							// 由节点名字到该节点指针的映射 key值相当于树的节点的名字空间 
	map<int, vector<Node*>> Tree2_heightToNode;						// 高度到节点指针的集合
	Vector_ref<Circle> Tree2_Circle;								// 树二的圆圈集合！
	Vector_ref<Line> Tree2_Line;									// 树二的直线集合！
	Vector_ref<Text> Tree2_Text;									// 树二的文本集合！
	vector<MatchingButton*> Tree2_detectingArea;					// 树二的监测区域
	
	void Tree2_OriginalData_Get();
	void Tree2_OriginalData_Analysis();
	void Tree2_NameToNode_Build();
	void Tree2_Build();
	void Tree2_clear();
	void Tree2_heightRefresh(Node* curnode, int curHeight);			// tree2 高度刷新
	void Tree2_RankInHeightRefresh();								// tree1 节点排名刷新
	void Tree2_PositionRefresh();
	void Tree2_draw();




};





#endif








/*
class Node
{
	friend class VisualizeMain;
public:
	// 基础数据 节点的名字，节点的左右关系
	string NodeName;	// 字符串表示节点的唯一标识名词
	Node* left;			// 指针指向左右节点 初始化为空
	Node* right;

	// 考虑到最终大小要适应屏幕，所以xx yy的规模要做适应性调整，并单独的全部重新计算!
	int xxScale;		
	int yyScale;			// 规模计算
	int xxPosition;
	int yyPosition;			// 圆心计算
	int height;				// 顶部的是高度1;

	Node(string str, Node* le, Node* rh)
	{
		NodeName = str;
		left = le;
		right = rh;
		
	}

	
	
};


class VisualizeMain : Window
{
	friend class TreeVisualize;
	friend class Node;


public:
	VisualizeMain(int width, int height);
	
	


private:
	// ------------------------------------------------------------------------------------------------------------------
	// 基础变量数据 屏幕像素数据
	int ScreenWidth;
	int ScreenHeight;
	
	// 基础控件数据 包括按钮 这些数据的即使在清空按钮点下之后都不会改变，属于背景类型
	// 基础按钮
	Button button_exit;
	Button button_readfileAuto;
	Button button_readfileManu;
	Button button_refresh;
	Button button_nextRead;
	Button button_findRelated;
	
	// 基础图形 进度条
	Graph_lib::Rectangle processBar1;
	Graph_lib::Rectangle processBar2;
	Graph_lib::Rectangle processBar3;
	Graph_lib::Rectangle processBar4;
	Vector_ref<Graph_lib::Rectangle> vec1;
	Vector_ref<Graph_lib::Rectangle> vec2;
	Vector_ref<Graph_lib::Rectangle> vec3;
	Vector_ref<Graph_lib::Rectangle> vec4;
	


	// 基础图形 分割线条
	Graph_lib::Line line1;
	Graph_lib::Line line2;

	// 基础图形 输入框和输出框
	In_box inputbox;
	Out_box infoOut;
	In_box NodeNameIn;

	// 基础信息 进度条标题
	Text processBar1Title;
	Text processBar2Title;
	Text processBar3Title;
	Text processBar4Title;
	Text inboxTitle;
	Text infoOutTitle;
	Text inputreminderText;
	// ------------------------------------------------------------------------------------------------------------------


	// 特别警告！每次处理一大轮（就是说文件队列清空之后算一大轮）后，下面的所有的变量全部要刷新清空
	// 但是，一小轮结束后，只需要清空画布，两个树相关的执行回收即可
	// 后台变量
	// ------------------------------------------------------------------------------------------------------------------
	string currentfilePlace;
	string ManualfilePlace;
	vector <string> OriginalAllfilePlace;					// 保存原始的所有文件的目录 检索支持子目录
	vector <string> FinalPlaceResult;						// 保存筛选后的最终的 txt，csv，或者其他类型的树文件
	map <string, string> isomorphismNameToName1;			// 同构关系的保存 tree1 -> tree2
	map <string, string> isomorphismNameToName2;			// 同构关系的保存 tree2 -> tree1
	bool ifsimular;											// 是否同构
	void STSTEM_var_refresh();								// 后台变量全部初始化
	void DetectingAreaGenerator();							// 根据两个树的节点产生监测区域
	void ButtonMatchingGenetor();							// 监测区域绑定图形
	// ------------------------------------------------------------------------------------------------------------------
	
	// 树相关的实现构想，原始的字符串读取 读取文件后写入 Tree1_OriginalData
	// 然后解析 Tree1_OriginalData 的每一行元素 用->为分隔符 建立 原始文件左名字到右名字的映射
	// 然后利用 Tree1_RootToSon_NameRelation（原始文件左名字到右名字的映射） 构建 名字到节点的映射 相当于树的节点的名字空间
	// 上面的部分需要修正 可能有一对多 那就需要两个以上的映射来保存
	// 
	// 下面的部分特别注意！！！！！！！！！
	// 特别注意 构建的过程中 需要用二级指针 Tree1_vitualRootNode 构造一级指针的数组下放，得到一级指针的节点，一级指针的节点再去申请node节点
	// 虚拟根节点不是节点，具体要寻找节点还需要通过函数来实现！！
	// 
	// 在回收的时候，先回收所有的node节点，再回收 一级指针，最后回收二级指针 注意  Tree1_realRootNode 无需回收！
	
	
	
	// tree1
	bool Tree1_iflegal;										// 树的合法 通讯工具
	int Tree1_height;										// 树的高度
	//Node** Tree1_vitualRootNode;							// 虚拟根节点，二级指针用来下放，得到一系列的一级指针，这个节点目的就是用来申请节点
	Node* Tree1_realRootNode;								// 真实的树的一级节点
	vector<string> Tree1_OriginalData;						// 原始的字符串读取 读取文件后写入这个数组 再解析
	map<string, string> Tree1_RootToSon_NameRelationLeft;	// 根节点到左儿子映射
	map<string, string> Tree1_RootToSon_NameRelationRight;	// 根节点到右儿子映射
	map<string, Node*> Tree1_NameToNode;					// 由节点名字到该节点指针的映射 key值相当于树的节点的名字空间 
	Vector_ref<Circle> Tree1_Circle;						// 树一的圆圈集合！
	Vector_ref<Line> Tree1_Line;							// 树一的直线集合！
	Vector_ref<Text> Tree1_Text;							// 树一的文本集合！
	vector<MatchingButton*> Tree1_detectingArea;			// 树一的监测区域


	// tree2
	bool Tree2_iflegal;
	int Tree2_height;										// 树的高度
	//Node** Tree2_vitualRootNode;							// 虚拟根节点，二级指针用来下放，得到一系列的一级指针，这个节点目的就是用来申请节点
	Node* Tree2_realRootNode;								// 真实的树的一级节点
	vector<string> Tree2_OriginalData;						// 原始的字符串读取 读取文件后写入这个数组 再解析
	map<string, string> Tree2_RootToSon_NameRelationLeft;	// 根节点到左儿子映射
	map<string, string> Tree2_RootToSon_NameRelationRight;	// 根节点到右儿子映射
	map<string, Node*> Tree2_NameToNode;					// 由节点名字到该节点指针的映射 key值相当于树的节点的名字空间 
	Vector_ref<Circle> Tree2_Circle;						// 树2的圆圈集合！
	Vector_ref<Line> Tree2_Line;							// 树2的直线集合！
	Vector_ref<Text> Tree2_Text;							// 树2的文本集合！
	vector<MatchingButton*> Tree2_detectingArea;			// 树二的监测区域

	// 按钮控件所对应的函数调用！
	void buttonPressed_exit();
	void buttonPressed_readfileAuto();
	void buttonPressed_readfileManu();
	void buttonPressed_refresh();
	void buttonPressed_nextRead();
	void buttonPressed_findRelated();

	// 树相关的所有的功能
	int TreeCenterMaster();				// read and deal with Two tree file!
	
	// tree1的操作函数
	// 特别警告：所有的操作只有在树合法的前提下 才允许进行！  Tree1_iflegal是通讯报错工具！
	void Tree1_OriginalData_Get();								// 函数pop掉队列的一个文件目录字符串，开始读取文件，然后写入OriginalData
	void Tree1_OriginalData_Analysis();							// 原始数据解析 用->为分隔符 建立 原始文件左名字到右名字的映射
	void Tree1_NameToNode_Build();								// 由节点名字到该节点指针的映射 key值相当于树的节点的名字空间 
	void Tree1_Build();											// 建立树的链接形式
	void Tree1_draw();											// 画图总控
	void Tree1_attachNow(Node* obj);							// 实际画图函数

	void Tree1_drawClear();										// 画布清空
	void Tree1_clear();											// 清理所有的变量，归还申请的内存
	void Tree1_heightRefresh(Node* curnode, int curHeight);		// tree1 高度刷新
	void Tree1_NodepositionRefresh(Node* curnode, Node* lastnode);// 节点的所有的位置计算,计算依据是高度


	// tree2的操作函数
	// 特别警告：所有的操作只有在树合法的前提下 才允许进行！  Tree2_iflegal是通讯报错工具！
	void Tree2_OriginalData_Get();										// 函数pop掉队列的一个文件目录字符串，开始读取文件，然后写入OriginalData
	void Tree2_OriginalData_Analysis();									// 原始数据解析 用->为分隔符 建立 原始文件左名字到右名字的映射
	void Tree2_NameToNode_Build();										// 由节点名字到该节点指针的映射 key值相当于树的节点的名字空间 
	void Tree2_Build();													// 建立树的链接形式
	void Tree2_draw();													// 画图总控
	void Tree2_attachNow(Node* obj);									// 实际画图函数

	void Tree2_drawClear();												// 画布清空
	void Tree2_clear();													// 清理所有的变量，归还申请的内存
	void Tree2_heightRefresh(Node* curnode, int curHeight);				// tree2 高度刷新
	void Tree2_NodepositionRefresh(Node* curnode, Node* lastnode);		// 节点的所有的位置计算,计算依据是高度

	bool if_isomorphism(Node* tree1, Node* tree2);						// 同构判断函数
	void isomorphismLink(Node* tree1, Node* tree2);												// 产生一系列的按钮 点击实现匹配	





	void Tree1_free();						// 释放tree1资源
	void Tree2_free();						// 释放tree2资源


	
	// 辅助功能
	void findCurrentPlace();												// 查找当前所在的exe文件的根目录
	void PrimefileFocus(string TargetFolder, vector<string>& files);		// 查找txt，csv，或者其他类型的文件
	void Selector(vector<string>& beforeSel, vector<string>& AfterSel);		// 过滤装置，只保留后缀是txt csv 或者in的文件！
	bool if_Select(string& obj);											// 判断目录的末端是否是合条件的！
	
	// 四个进度条控制中心
	void progressbar1refresh(int num);
	void progressbar2refresh(int num);
	void progressbar3refresh(int num);
	void progressbar4refresh(int num);


	// 控制台的输出检查
	void TmpPrinter_Tree1_RootToSon_NameRelation();
	void TmpPrinter_Tree2_RootToSon_NameRelation();
	void TmpPrinter_isomorphismNameToName1();


	

};

#endif

*/