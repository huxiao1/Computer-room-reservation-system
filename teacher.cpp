#include "teacher.h"

//默认构造
Teacher::Teacher()
{

}

//有参构造 (职工编号，姓名，密码)
Teacher::Teacher(int empId, string name, string pwd)
{
    //初始化属性
	this->m_EmpId = empId;
	this->m_Name = name;
	this->m_Pwd = pwd;
}

//菜单界面
void Teacher::operMenu()
{
    cout << "welcome teacher " << this->m_Name << " login!" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|      1.search all reservation    |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|      2.process reservation       |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.logout                |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "input your choice:" << endl;
}

//查看所有预约
void Teacher::showAllOrder()
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

		cout << "reserve day" << of.m_orderData[i]["date"];
		cout << " reserve time:" << (of.m_orderData[i]["interval"] == "1" ? "morning" : "afternoon");
		cout << " username:" << of.m_orderData[i]["stuId"];
		cout << " name:" << of.m_orderData[i]["stuName"];
		cout << " computer room:" << of.m_orderData[i]["roomId"];
		string status = " status ";  // 0 取消的预约   1 审核中   2 已预约 -1 预约失败
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

//审核预约
void Teacher::validOrder()
{
    OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "no history record" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "processing records:" << endl;

	vector<int> v;
	int index = 0;
	for (int i = 0; i < of.m_Size; i++)
	{
		if (of.m_orderData[i]["status"] == "1")
		{
			v.push_back(i);
			cout << ++index << ".";
			cout << "reserve day" << of.m_orderData[i]["date"];
			cout << " reserve time" << (of.m_orderData[i]["interval"] == "1" ? "morning" : "afternoon");
			cout << " computerroom" << of.m_orderData[i]["roomId"];
			string status = " status ";  // 0取消的预约   1 审核中   2 已预约  -1 预约失败
			if (of.m_orderData[i]["status"] == "1")
			{
				status += "processing";
			}
			cout << status << endl;
		}
	}
	cout << "input process record,type 0 to return" << endl;
	int select = 0;
	int ret = 0;
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
				cout << "input process result" << endl;
				cout << "1.pass" << endl;
				cout << "2.failed" << endl;
				cin >> ret;

				if (ret == 1)
				{
					of.m_orderData[v[select - 1]]["status"] = "2";
				}
				else
				{
					of.m_orderData[v[select - 1]]["status"] = "-1";
				}
				of.updateOrder();
				cout << "process ending" << endl;
				break;
			}
		}
		cout << "error" << endl;
	}

	system("pause");
	system("cls");
}