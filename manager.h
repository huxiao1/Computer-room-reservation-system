#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;
#include "identity.h"
#include "globalFile.h"
#include "student.h"
#include "teacher.h"
#include "computerRoom.h"

class Manager:public Identity
{
    public:
        Manager();                          //默认构造
        Manager(string name,string pwd);    //有参构造
        virtual void operMenu();            //选择菜单
        void addPerson();                   //添加账号
        void showPerson();                  //查看账号
        void showComputer();                //查看机房信息
        void cleanFile();                   //清空预约记录
        void initVector();                  //初始化容器,去重用
        bool checkRepeat(int id,int type);  //检测重复 参数:(传入id，传入类型) 返回值：(true 代表有重复，false代表没有重复)

        vector<Student> vStu;               //学生容器
        vector<Teacher> vTea;               //教师容器
        vector<ComputerRoom> vCom;          //机房容器
};