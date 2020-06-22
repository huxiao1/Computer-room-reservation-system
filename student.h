#pragma once
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
#include "identity.h"
#include "globalFile.h"
#include "computerRoom.h"
#include "orderFile.h"

//学生类
class Student:public Identity
{
    public:
        Student();           //默认构造
        Student(int id,string name,string pwd);    //有参构造

        virtual void operMenu();     //菜单界面

        void applyOrder();           //申请预约
        void showMyOrder();          //查看我的预约
        void showAllOrder();         //查看所有预约
        void cancelOrder();          //取消预约

        int m_Id;                    //学生学号
        vector<ComputerRoom> vCom;   //机房容器
};