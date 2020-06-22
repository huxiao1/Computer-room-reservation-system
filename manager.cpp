#include "manager.h"


//默认构造
Manager::Manager()
{
}

//有参构造
Manager::Manager(string name, string pwd)
{
    this->m_Name = name;
    this->m_Pwd = pwd;

    //初始化容器
    this->initVector();

    //获取机房信息
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom c;
	while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
	{
		vCom.push_back(c);
	}
	cout << "current computer room number is:" << vCom.size() << endl;
	ifs.close();
}

//选择菜单
void Manager::operMenu()
{
    cout << "Welcome manager"<<this->m_Name << "login in!" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.add username        |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|        2.search username       |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|     3.search computer room     |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|      4.clear reservation       |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|     0.cancellation login       |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "input your choice:" << endl;
}

//添加账号  
void Manager::addPerson()
{
    cout<<"input the type of the newly insert username:"<<endl;
    cout<<"1.add student"<<endl;
    cout<<"2.add teacher"<<endl;

    string filename;
    string tip;
    ofstream ofs;
    string errorTip;

    int select = 0;
    cin>>select;

    if (select == 1)
    {
        filename = STUDENT_FILE;
        tip = "input student username: ";
        errorTip = "username repeat";
    }
    else
    {
        filename = TEACHER_FILE;
        tip = "input teacher username:";
        errorTip = "username repeat";
    }

    ofs.open(filename,ios::out|ios::app);
    int id;
    string name;
    string pwd;
    int flag = 1;
    cout<<tip<<endl;

    while (true)
	{
        if(flag != 1)
            cout<<tip<<endl;
		flag = 2;
        cin >> id;

		bool ret = this->checkRepeat(id, 1);

		if (ret) //有重复
		{
			cout << errorTip << endl;
		}
		else
		{
			break;
		}
	}
    
    cout<<"input name:"<<endl;
    cin>>name;

    cout<<"input pwd:"<<endl;
    cin>>pwd;

    ofs<<id<<" "<<name<<" "<<pwd<<" "<<endl;   //写文件
    cout<<"add succeed!"<<endl;

    system("pause");
    system("cls");

    ofs.close();
    //初始化容器
    /*
    bug描述：
        * 虽然可以检测重复的账号，但是刚添加的账号由于没有更新到容器中，因此不会做检测
        * 导致刚加入的账号的学生号或者职工编号，再次添加时依然可以重复

    解决方案：
        * 在每次添加新账号时，重新初始化容器
    */
    this->initVector();
}

void printStudent(Student & s)
{
	cout << "username:" << s.m_Id << "   name:" << s.m_Name << "   pwd:" << s.m_Pwd << endl;
}

void printTeacher(Teacher & t)
{
	cout << "username:" << t.m_EmpId << "   name:" << t.m_Name << "   pwd:" << t.m_Pwd << endl;
}

//查看账号
void Manager::showPerson()
{
    cout << "choose search content:" << endl;
	cout << "1.search all students" << endl;
	cout << "2.search all teachers" << endl;

	int select = 0;

	cin >> select;
    
	if (select == 1)
	{
		cout << "the info of all students" << endl;
		for_each(vStu.begin(), vStu.end(), printStudent);
	}
	else
	{
		cout << "the info of all teachers" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}
	system("pause");
	system("cls");
}

//查看机房信息
void Manager::showComputer()
{
    cout << "the info of computer room is:" << endl;
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
	{
		cout << "computer room number is" << it->m_ComId << "   the max capacity of the computer room is:" << it->m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}

//清空预约记录
void Manager::cleanFile()
{
    ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();

	cout << "clear succeed!" << endl;
	system("pause");
	system("cls");
}

void Manager::initVector()
{
    //确保容器清空
    vStu.clear();
    vTea.clear();

    //读取学生文件中信息
    ifstream ifs;
    ifs.open(STUDENT_FILE,ios::in);
    if (!ifs.is_open())
    {
        cout<<"file read error"<<endl;
        return;
    }

    Student s;
    while (ifs>>s.m_Id && ifs>>s.m_Name && ifs>>s.m_Pwd)
    {
        vStu.push_back(s);
    }
    cout<<"current student number is:"<<vStu.size()<<endl;
    ifs.close();
    
    //读取老师文件信息
	ifs.open(TEACHER_FILE, ios::in);

	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_Name &&  ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	}
	cout << "current teacher number is:" << vTea.size() << endl;

	ifs.close();
}

bool Manager::checkRepeat(int id,int type)
{
    if (type == 1)
    {
        for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			if (id == it->m_Id)
			{
				return true;
			}
		}
    }
    else
	{
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			if (id == it->m_EmpId)
			{
				return true;
			}
		}
	}
	return false;
}