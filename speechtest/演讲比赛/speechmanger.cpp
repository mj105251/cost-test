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
	cout << "***1.��ʼ�ݽ�����***" << endl;
	cout << "***2.�鿴�����¼***" << endl;
	cout << "***3.��ձ�����¼***" << endl;
	cout << "***0.�˳���������***" << endl;
	cout << "********************" << endl;
	cout << endl;
}
void speechmanger::existsystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}
void speechmanger::initspeech()
{
	//������֤Ϊ��
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_speaker.clear();
	//��ʼ����������
	this->m_index = 1;
	//����¼���������
	this->m_record.clear();
}
void speechmanger::creatspeaker()
{
	string nameseed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameseed.size(); i++)
	{
		string name = "ѡ��";
		name += nameseed[i];
		speaker sp;
		sp.m_name = name;
		for (int j = 0; j < 2; j++)
		{
			sp.m_score[j] = 0;
		}
		this->v1.push_back(i + 10001);//����Ŵ���v1������
		this->m_speaker.insert(make_pair(i + 10001, sp));
	}
}
void speechmanger::startspeech()
{
	//��һ�ֱ���
	//1.��ǩ
	this->speechdraw();
	//2.����
	/*this->speechdraw();*/
	this->speechcontest();
	//3.��ʾ�������
	this->showscore();
	//�ڶ��ֱ���
	this->m_index++;
	//1.��ǩ
	this->speechdraw();
	//2.����
	this->speechcontest();
	//3.��ʾ���ս��
	this->showscore();
	//4.�������
	this->saverecord();
	//���ñ�������ȡ��¼
	this->initspeech();
	this->creatspeaker();
	this->loadrecord();
	cout << "����������" << endl;
	system("pause");
	system("cls");
}
void speechmanger::speechdraw()
{
	cout << "��<<" << this->m_index << ">>�ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "-------------------" << endl;
	cout << "��ǩ���ݽ�����˳�����£�" << endl;
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
	cout << "��<<" << this->m_index << ">>�ֱ�����ʽ��ʼ" << endl;
	multimap<double, int, greater<double>>groupscore;//��ʱ��������ѡ�ַ����ͱ��
	int num = 0;//��¼��Ա����6��Ϊһ��

	vector<int>v_src;
	if (this->m_index == 1)
	{
		v_src = v1;
	}
	else
	{
		v_src = v2;
	}
	//�������в���ѡ��
	for (vector<int>::iterator it = v_src.begin(); it != v_src.end(); it++)
	{
		num++;
		//��ί���
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
		//ÿ��ƽ����
		//cout << "��<<" << num / 6 << "С��ѡ�ֱ��������" << endl;
		//cout << "��ţ�" << *it << " "<<"ѡ�֣�" << this->m_speaker[*it].m_name <<" "
		//	<< "ƽ������"<<avg<< endl;
		this->m_speaker[*it].m_score[this->m_index - 1] = avg;
		//6��һ�飬����ʱ��������
		groupscore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С��������Σ�" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupscore.begin();
				it != groupscore.end(); it++)
			{
				cout << "��ţ�" << it->second << "������" << this->m_speaker[it->second].m_name << "������" 
					<< this->m_speaker[it->second].m_score[this->m_index-1] << endl;
			}
			cout << endl;
			int count = 0;
			//ȡǰ����
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
	cout << "-----------��" << this->m_index << "�ֱ������---------" << endl;
	//cout << endl;
	system("pause");
}
void speechmanger::showscore()
{
	cout << "----------��" << this->m_index << "�ֽ���ѡ����Ϣ���£�----------" << endl;
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
		cout << "ѡ�ֱ�ţ�" << *it << "������" << this->m_speaker[*it].m_name 
			<< "�÷֣�" << this->m_speaker[*it].m_score[this->m_index-1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->showmenu();
}
void speechmanger::saverecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//���û���ļ��������ļ���������ļ����ļ�β����ļ�
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_speaker[*it].m_score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "��¼�Ѿ�����" << endl;
	this->fileIsEmpty = false;
}
void speechmanger::loadrecord()
{
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		//cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "�ļ�Ϊ��" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	//�ļ���Ϊ��
	this->fileIsEmpty = false;
	ifs.putback(ch);//��ȡ�ĵ����ַ��Ż�ȥ
	string data;
	int index = 0;
	while (ifs >> data)
	{
		vector<string>v;
		int pos = -1;//�鵽","λ�ñ���
		int start = 0;

		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)//û���ҵ�
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
		cout << "�ļ�Ϊ�ջ��ļ�������" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_record.size(); i++)
		{
			cout << "��" << i + 1 << "��" <<
				"�ھ���ţ�" << this->m_record[i][0] << "�÷֣�" << this->m_record[i][1] << " "
				"�Ǿ���ţ�" << this->m_record[i][2] << "�÷֣�" << this->m_record[i][3] << " "
				"������ţ�" << this->m_record[i][4] << "�÷֣�" << this->m_record[i][5] << endl;
		}
	}
	
	system("pause");
	system("cls");
}
void speechmanger::clearrecord()
{
	cout << "ȷ����գ�" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.����" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);//����ļ�����ɾ���ļ������´����µ��ļ�
		ofs.close();
		//��ʼ������
		this->initspeech();
		//����ѡ��
		this->creatspeaker();
		//��ȡ�����¼
		this->loadrecord();
		cout << "��ճɹ�" << endl;
	}
}
