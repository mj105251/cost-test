#include"speechmanger.h"
#include<algorithm>
#include<deque>
#include<string>
#include<numeric>
#include<functional>
#include<fstream>
speechmanger::speechmanger()
{
	this->initspeech();
	this->creatspeaker();
	this->loadrecord();
}
speechmanger::~speechmanger()
{

}
void speechmanger::showmenu()
{
	cout << "********************" << endl;
	cout << "***1.开始演讲比赛***" << endl;
	cout << "***2.查看往届记录***" << endl;
	cout << "***3.清空比赛记录***" << endl;
	cout << "***0.退出比赛程序***" << endl;
	cout << "********************" << endl;
	cout << endl;
}
void speechmanger::existsystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}
void speechmanger::initspeech()
{
	//容器保证为空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_speaker.clear();
	//初始化比赛轮数
	this->m_index = 1;
	//将记录的容器清空
	this->m_record.clear();
}
void speechmanger::creatspeaker()
{
	string nameseed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameseed.size(); i++)
	{
		string name = "选手";
		name += nameseed[i];
		speaker sp;
		sp.m_name = name;
		for (int j = 0; j < 2; j++)
		{
			sp.m_score[j] = 0;
		}
		this->v1.push_back(i + 10001);//将编号存入v1容器中
		this->m_speaker.insert(make_pair(i + 10001, sp));
	}
}
void speechmanger::startspeech()
{
	//第一轮比赛
	//1.抽签
	this->speechdraw();
	//2.比赛
	/*this->speechdraw();*/
	this->speechcontest();
	//3.显示晋级结果
	this->showscore();
	//第二轮比赛
	this->m_index++;
	//1.抽签
	this->speechdraw();
	//2.比赛
	this->speechcontest();
	//3.显示最终结果
	this->showscore();
	//4.保存分数
	this->saverecord();
	//重置比赛，获取记录
	this->initspeech();
	this->creatspeaker();
	this->loadrecord();
	cout << "本届比赛完毕" << endl;
	system("pause");
	system("cls");
}
void speechmanger::speechdraw()
{
	cout << "第<<" << this->m_index << ">>轮比赛选手正在抽签" << endl;
	cout << "-------------------" << endl;
	cout << "抽签后演讲比赛顺序如下：" << endl;
	if (this->m_index == 1)
	{
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << "";
		}
		cout << endl;
	}
	cout << "-------------------" << endl;
	system("pause");
	cout << endl;
}
void speechmanger::speechcontest()
{
	cout << "第<<" << this->m_index << ">>轮比赛正式开始" << endl;
	multimap<double, int, greater<double>>groupscore;//临时容器保存选手分数和编号
	int num = 0;//记录人员数，6人为一组

	vector<int>v_src;
	if (this->m_index == 1)
	{
		v_src = v1;
	}
	else
	{
		v_src = v2;
	}
	//遍历所有参赛选手
	for (vector<int>::iterator it = v_src.begin(); it != v_src.end(); it++)
	{
		num++;
		//评委打分
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			//cout<<score<<" ";
			d.push_back(score);
		}
		//cout << endl;
		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();
		d.pop_back();
		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();
		//每人平均分
		//cout << "第<<" << num / 6 << "小组选手比赛情况：" << endl;
		//cout << "编号：" << *it << " "<<"选手：" << this->m_speaker[*it].m_name <<" "
		//	<< "平均分数"<<avg<< endl;
		this->m_speaker[*it].m_score[this->m_index - 1] = avg;
		//6人一组，用临时容器保存
		groupscore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次：" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupscore.begin();
				it != groupscore.end(); it++)
			{
				cout << "编号：" << it->second << "姓名：" << this->m_speaker[it->second].m_name << "分数：" 
					<< this->m_speaker[it->second].m_score[this->m_index-1] << endl;
			}
			cout << endl;
			int count = 0;
			//取前三名
			for (multimap<double, int, greater<double>>::iterator it = groupscore.begin(); 
				it != groupscore.end()&&count<3; it++,count++)
			{
				if (this->m_index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					vVictory.push_back((*it).second);
				}
			}
			groupscore.clear();
		}
	}
	cout << "-----------第" << this->m_index << "轮比赛完毕---------" << endl;
	//cout << endl;
	system("pause");
}
void speechmanger::showscore()
{
	cout << "----------第" << this->m_index << "轮晋级选手信息如下：----------" << endl;
	vector<int>v;
	if (this->m_index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "选手编号：" << *it << "姓名：" << this->m_speaker[*it].m_name 
			<< "得分：" << this->m_speaker[*it].m_score[this->m_index-1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->showmenu();
}
void speechmanger::saverecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//如果没有文件生成新文件，如果有文件再文件尾添加文件
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_speaker[*it].m_score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "记录已经保存" << endl;
	this->fileIsEmpty = false;
}
void speechmanger::loadrecord()
{
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		//cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件为空" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件不为空
	this->fileIsEmpty = false;
	ifs.putback(ch);//读取的单个字符放回去
	string data;
	int index = 0;
	while (ifs >> data)
	{
		vector<string>v;
		int pos = -1;//查到","位置变量
		int start = 0;

		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)//没有找到
			{
				break;
			}
			string tmp = data.substr(start, pos - start);
			v.push_back(tmp);
			start = pos + 1;

		}
		this->m_record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
}
void speechmanger::showrecord()
{
	if (this->fileIsEmpty)
	{
		cout << "文件为空或文件不存在" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_record.size(); i++)
		{
			cout << "第" << i + 1 << "届" <<
				"冠军编号：" << this->m_record[i][0] << "得分：" << this->m_record[i][1] << " "
				"亚军编号：" << this->m_record[i][2] << "得分：" << this->m_record[i][3] << " "
				"季军编号：" << this->m_record[i][4] << "得分：" << this->m_record[i][5] << endl;
		}
	}
	
	system("pause");
	system("cls");
}
void speechmanger::clearrecord()
{
	cout << "确认清空？" << endl;
	cout << "1.确认" << endl;
	cout << "2.返回" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);//如果文件存在删除文件并重新创建新的文件
		ofs.close();
		//初始化属性
		this->initspeech();
		//创建选手
		this->creatspeaker();
		//获取往届记录
		this->loadrecord();
		cout << "清空成功" << endl;
	}
}
