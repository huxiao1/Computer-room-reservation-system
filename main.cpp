#include<iostream>
#include<fstream>
#include<string>
using namespace std;
#include "identity.h"
#include "globalFile.h"
#include "teacher.h"
#include "student.h"
#include "manager.h"
//----------------------------------------manager-=----------------------------------------
//管理员菜单
void managerMenu(Identity * &manager)
{
	while (true)
	{
		//管理员菜单
		manager->operMenu();

		Manager* man = (Manager*)manager;    //父类指针强制转换为子类指针,这样公共的和manager子类的都可以使用了
		int select = 0;

		cin >> select;
        
		if (select == 1)  //添加账号
		{
			cout << "add username" << endl;
			man->addPerson();
		}
		else if (select == 2) //查看账号
		{
			cout << "search username" << endl;
			man->showPerson();
		}
		else if (select == 3) //查看机房
		{
			cout << "search computer room" << endl;
			man->showComputer();
		}
		else if (select == 4) //清空预约
		{
			cout << "clear reservation" << endl;
			man->cleanFile();
		}
		else
		{
			delete manager;
			cout << "cancellation login" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//----------------------------------------student-=----------------------------------------
//学生菜单
void studentMenu(Identity * &student)
{
	while (true)
	{
		//学生菜单
		student->operMenu();

		Student* stu = (Student*)student;
		int select = 0;

		cin >> select;

		if (select == 1) //申请预约
		{
			stu->applyOrder();
		}
		else if (select == 2) //查看自身预约
		{
			stu->showMyOrder();
		}
		else if (select == 3) //查看所有预约
		{
			stu->showAllOrder();
		}
		else if (select == 4) //取消预约
		{
			stu->cancelOrder();
		}
		else
		{
			delete student;
			cout << "logout succeed" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//----------------------------------------teacher-=----------------------------------------
//教师菜单
void TeacherMenu(Identity * &teacher)
{
	while (true)
	{
		//教师菜单
		teacher->operMenu();

		Teacher* tea = (Teacher*)teacher;
		int select = 0;

		cin >> select;

		if (select == 1)
		{
			//查看所有预约
			tea->showAllOrder();
		}
		else if (select == 2)
		{
			//审核预约
			tea->validOrder();
		}
		else
		{
			delete teacher;
			cout << "logout succeed" << endl;
			system("pause");
			system("cls");
			return;
		}

	}
}

//------------------------------------------------main menu--------------------------------------------------------
//登录功能
void LoginIn(string fileName,int type)
{
	Identity *person = NULL;

	//读文件
	ifstream ifs;
	ifs.open(fileName,ios::in);

	//判断文件是否存在
	if (!ifs.is_open())
	{
		cout<<"file is not exist"<<endl;
		return;
	}

	//准备接收用户信息
	int id = 0;
	string name;
	string pwd;

	//判断身份
	if (type == 1)  //student
	{
		cout<<"input your number:"<<endl;
		cin>>id;
	}
	if (type == 2)  //teacher
	{
		cout<<"input your number:"<<endl;
		cin>>id;
	}

	cout<<"input your username:"<<endl;
	cin>>name;

	cout<<"input your password:"<<endl;
	cin>>pwd;

	if (type == 1)
	{
		//学生登录验证
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "student login succeed!" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				studentMenu(person);
				return;
			}
		}
	}
	else if (type == 2)
	{
		//教师登录验证
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "teacher login succeed!" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				TeacherMenu(person);
				return;
			}
		}
	}
	else if(type == 3)
	{
		//管理员登录验证
		string fName;
		string fPwd;
		while (ifs >> fName && ifs >> fPwd)
		{
			if (name == fName && pwd == fPwd)
			{
				cout << "admin login succeed!" << endl;
				//登录成功后，按任意键进入管理员界面
				system("pause");
				system("cls");
				//创建管理员对象
				person = new Manager(name,pwd);
				//进入管理员子菜单
				managerMenu(person);
				return;
			}
		}
	}
	
	cout << "login error!" << endl;

	system("pause");
	system("cls");
	return;
}









int main() {

    int select = 0;

	while (true)
	{
		cout << "======================  Welcome to the COMPUTER ROOM RESERVATION SYSTEM  =====================" << endl;
	    cout << endl << "Input your identity" << endl;
	    cout << "\t\t -------------------------------\n";
	    cout << "\t\t|                               |\n";
	    cout << "\t\t|   1.Student representatives   |\n";
	    cout << "\t\t|                               |\n";
	    cout << "\t\t|   2.teacher                   |\n";
	    cout << "\t\t|                               |\n";
	    cout << "\t\t|   3.administrator             |\n";
	    cout << "\t\t|                               |\n";
	    cout << "\t\t|   0.exit                      |\n";
	    cout << "\t\t|                               |\n";
	    cout << "\t\t -------------------------------\n";
	    cout << "Pls input your choice:";

		cin >> select;       //接受用户选择

		switch (select)
		{
		    case 1:         //学生身份
				LoginIn(STUDENT_FILE,1);
			    break;
		    case 2:         //老师身份
				LoginIn(TEACHER_FILE,2);
			    break;
		    case 3:         //管理员身份
				LoginIn(ADMIN_FILE,3);
			    break;
		    case 0:  //退出系统
                cout<<"See you"<<endl;
                system("pause");
                return 0;
			    break;
		    default:
                cout << "Input error!" << endl;
		        system("pause");
			    system("cls");
			    break;
		}

	}
	system("pause");
	return 0;
}