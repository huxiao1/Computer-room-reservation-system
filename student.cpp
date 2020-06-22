#include "student.h"

Student::Student()
{

}

Student::Student(int id,string name,string pwd)
{
    //初始化属性
    this->m_Id = id;
    this->m_Name = name;
    this->m_Pwd = pwd;

    //获取机房信息
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom c;
	while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
	{
		vCom.push_back(c);
	}

	ifs.close();
}

void Student::operMenu()
{
    cout << "welcome student:" << this->m_Name << "login" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|      1.apply for reservation    |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|      2.search my reservation    |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|      3.search all reservation   |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|       4.cancel reservation      |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          0.logout               |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "input your choice:";
}
        
void Student::applyOrder()
{
    cout << "computer room open from monday to friday!" << endl;
	cout << "input the reserve day:" << endl;
	cout << "1.Monday" << endl;
	cout << "2.Tuesday" << endl;
	cout << "3.Wesdeny" << endl;
	cout << "4.thursday" << endl;
	cout << "5.friday" << endl;
	int date = 0;
	int interval = 0;
	int room = 0;

	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "input error(computer room open from monday to friday)" << endl;
	}


	cout << "input resverve time" << endl;
	cout << "1.morning" << endl;
	cout << "2.afternoon" << endl;

	while (true)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		cout << "input error" << endl;
	}

	cout << "choose computer room" << endl;
	cout << "number1 computer room capcatity" << vCom[0].m_MaxNum << endl;
	cout << "number2 computer room capcatity" << vCom[1].m_MaxNum << endl;
	cout << "number3 computer room capcatity" << vCom[2].m_MaxNum << endl;

	while (true)
	{
		cin >> room;
		if (room >= 1 && room <= 3)
		{
			break;
		}
		cout << "input error" << endl;
	}

	cout << "reserve succeed" << endl;

	ofstream ofs(ORDER_FILE, ios::app);
	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->m_Id << " ";
	ofs << "stuName:" << this->m_Name << " ";
	ofs << "roomId:" << room << " ";
	ofs << "status:" << 1 << endl;

	ofs.close();

	system("pause");
	system("cls");
}

void Student::showMyOrder()
{
    OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "no history record" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size; i++)
	{
		if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_Id)
		{
			cout << "reserve day:" << of.m_orderData[i]["date"];
			cout << " reserve time:" << (of.m_orderData[i]["interval"] == "1" ? "morning" : "afternoon");
			cout << " computer room:" << of.m_orderData[i]["roomId"];
			string status = " status: ";          // 0 取消的预约   1 审核中   2 已预约 -1 预约失败
			if (of.m_orderData[i]["status"] == "1")
			{
				status += "processing";
			}
			else if (of.m_orderData[i]["status"] == "2")
			{
				status += "succeed";
			}
			else if (of.m_orderData[i]["status"] == "-1")
			{
				status += "failed";
			}
			else
			{
				status += "reserve cancel";
			}
			cout << status << endl;
		}
	}
	system("pause");
	system("cls");
}

void Student::showAllOrder()
{
    OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "no history record" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_Size; i++)
	{
		cout << i + 1 << ".";

		cout << "reserve day:" << of.m_orderData[i]["date"];
		cout << " reserve time:" << (of.m_orderData[i]["interval"] == "1" ? "morning" : "afternoon");
		cout << " username:" << of.m_orderData[i]["stuId"];
		cout << " name:" << of.m_orderData[i]["stuName"];
		cout << " computer room:" << of.m_orderData[i]["roomId"];
		string status = " status: ";          // 0 取消的预约   1 审核中   2 已预约 -1 预约失败
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "processing";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "reserve succeed";
		}
		else if (of.m_orderData[i]["status"] == "-1")
		{
			status += "failed";
		}
		else
		{
			status += "reserve cancel";
		}
		cout << status << endl;
	}

	system("pause");
	system("cls");
}

void Student::cancelOrder()
{
    OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "no history record" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "processing or succeed record can cancel,input cancel recod:" << endl;

	vector<int> v;
	int index = 1;
	for (int i = 0; i < of.m_Size; i++)
	{
		if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_Id)
		{
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout <<  index ++  << ".";
				cout << "reserve day:" << of.m_orderData[i]["date"];
				cout << " reserve time:" << (of.m_orderData[i]["interval"] == "1" ? "morning" : "afternoon");
				cout << " computer room:" << of.m_orderData[i]["roomId"];
				string status = " status: ";  // 0 取消的预约   1 审核中   2 已预约  -1 预约失败
				if (of.m_orderData[i]["status"] == "1")
				{
					status += "processing";
				}
				else if (of.m_orderData[i]["status"] == "2")
				{
					status += "succeed";
				}
				cout << status << endl;

			}
		}
	}

	cout << "input the cancel record,type 0 to return" << endl;
	int select = 0;
	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				//	cout << "记录所在位置： " << v[select - 1] << endl;
				of.m_orderData[v[select - 1]]["status"] = "0";
				of.updateOrder();
				cout << "cancel succeed" << endl;
				break;
			}

		}
		cout << "error" << endl;
	}

	system("pause");
	system("cls");
}