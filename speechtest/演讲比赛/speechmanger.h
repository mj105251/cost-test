#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<map>;
#include"speaker.h"
//设计演讲比赛的管理类
class speechmanger
{
public:
	//构造函数
	speechmanger();
	//析构函数
	~speechmanger();
	//展示菜单
	void showmenu();
	//退出系统
	void existsystem();
	//初始化属性
	void initspeech();
	//创建12名选手
	void creatspeaker();
	//开始比赛
	void startspeech();
	//抽签
	void speechdraw();
	//比赛
	void speechcontest();
	//显示得分
	void showscore();
	//保存比赛记录
	void saverecord();
	//读取记录分数
	void loadrecord();
	//文件为空标志
	bool fileIsEmpty;
	//往届记录
	map<int, vector<string>>m_record;
	//显示往届记录
	void showrecord();
	//清空记录
	void clearrecord();
	//成员属性
	//比赛选手容器
	vector<int>v1;
	//第一轮晋级的选手容器
	vector<int>v2;
	//胜利前三名的选手容器
	vector<int>vVictory;
	//存放编号以及对应的具体选手容器
	map<int, speaker>m_speaker;
	int m_index;
};
