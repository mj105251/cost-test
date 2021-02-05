#pragma once
#include<iostream>
#include<string>
using namespace std;
#include"Person.h"
#include<vector>
#include<map>
//#include<fstream>
class SpeechManger
{
public:
	//构造函数
	SpeechManger();
	//析构函数
	~SpeechManger();
	//显示菜单
	void ShowMenu();
	//退出系统
	void ExitSystem();
	//初始化属性
	void InialSpeecher();
	//创建选手
	void CreatSpeecher();
	//比赛选手容器
	vector<int>v1;
	//晋级选手容器
	vector<int>v2;
	//胜利前三名选手容器
	vector<int>vVictory;
	//创建map容器，int为选手编号，Person为选手的基本信息
	map<int, Person>m_speecher;
	//记录比赛轮数
	int m_round;
	//开始比赛
	void StartSpeech();
	//抽签
	void speechDraw();
	//比赛
	void speechContest();
	//显示晋级结果
	void showResult();
	//保存晋级结果
	void saveResult();
	//读取晋级结果
	void readResult();
	//判断文件是否为空
	bool fileIsEmpty;
	//记录往届信息
	map<int, vector<string>>m_record;
	//显示往届信息
	void showRecord();
	//清空比赛记录
	void clearRecord();
};