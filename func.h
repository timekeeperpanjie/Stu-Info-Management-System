#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <setjmp.h>

#define USR_NAME_LEN  20
#define USR_PWD_LEN   20

//#define ADMIN         1		//管理员和普通用户
//#define GENERAL       0

typedef int USR_ACCOUNT_TYPE;	//用户类型

//以下不确定
typedef int MENU_TYPE;	//选项编号
typedef int SEARCH_ID;			//id编号
typedef int USR_ACCOUNT_NUM;	//用户编号
typedef int STU_INFO_NUM;
//


typedef struct usr_account_tag{
	char usr_name[USR_NAME_LEN];
	char usr_pwd[USR_PWD_LEN];
	int role;			//1是管理员 0是普通用户
	struct usr_account_tag *pNext_Usr_Account;
}USR_ACCOUNT,*pUSR_ACCOUNT;

typedef struct stu_info_tag{
	int stu_id;
	char stu_name[USR_NAME_LEN];
	char sex;
	double stu_course_score[5];
	struct stu_info_tag *pNext_Stu_Info;
}STU_INFO,*pSTU_INFO;

void Link_Initial(FILE *,FILE *,pUSR_ACCOUNT *,pSTU_INFO *);//启动程序 链表初始化

void Stu_Insert(pSTU_INFO *,STU_INFO *);//学生信息插入

USR_ACCOUNT_TYPE Sign_On_Page(pUSR_ACCOUNT);//登录页面

int Sign_Wrong_Page();//登录错误页面

MENU_TYPE Sign_General_Page();//普通用户页面

MENU_TYPE Sign_Admin_Page();//管理员用户页面

int Stu_Exist(pSTU_INFO *,int);//学生信息存在性判定 1为存在 0为不存在

int Search_Stu_Page_General(pSTU_INFO);//普通用户搜索学生页面

int Search_Stu_Page_Admin(pSTU_INFO);//管理员搜索学生页面

int Add_Stu_Page(pSTU_INFO *);//管理员添加学生

int Update_Stu_Page(pSTU_INFO *);//更新学生信息

int Delete_Stu_Page(pSTU_INFO *);//删除学生信息

int Add_Usr_Page(pUSR_ACCOUNT *);//管理员添加用户

int Update_Usr_Page(pUSR_ACCOUNT *);//管理员更新用户

int Delete_Usr_Page(pUSR_ACCOUNT *);//删除用户信息

int Search_Usr_Page(pUSR_ACCOUNT);//管理员搜索用户页面

void Data_Save(pUSR_ACCOUNT *,pSTU_INFO *);
