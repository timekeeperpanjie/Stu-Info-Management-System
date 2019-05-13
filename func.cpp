#include "func.h"



void Link_Initial(FILE *usrFilePointer,FILE *stuFilePointer,pUSR_ACCOUNT *ppUsrLink,pSTU_INFO *ppStuLink)
{
	int i;
	USR_ACCOUNT *pUsrLink,*pUsrLinkTail,*pUsrNode,UsrAccountTemp;					//用户链表
	STU_INFO *pStuLink,*pStuLinkTail,*pStuNode,StuInfoTemp;						//学生链表
	pUsrLink=*ppUsrLink;
	pStuLink=*ppStuLink;
//读取用户链表
	while(EOF!=fscanf(usrFilePointer,"%s %s %d",&UsrAccountTemp.usr_name,&UsrAccountTemp.usr_pwd,&UsrAccountTemp.role))
	{
		if(NULL==pUsrLink)
		{
			pUsrLink=pUsrLinkTail=pUsrNode=(pUSR_ACCOUNT)calloc(1,sizeof(USR_ACCOUNT));				//pUsrLink需要指向链表头
			pUsrNode->pNext_Usr_Account=NULL;
			strcpy(pUsrNode->usr_name,UsrAccountTemp.usr_name);							//字符串只能拷贝 不能赋值
			strcpy(pUsrNode->usr_pwd,UsrAccountTemp.usr_pwd);
			pUsrNode->role=UsrAccountTemp.role;
		}else{
			pUsrNode=(pUSR_ACCOUNT)calloc(1,sizeof(USR_ACCOUNT));				//pUsrLink需要指向链表头
			pUsrNode->pNext_Usr_Account=NULL;
			strcpy(pUsrNode->usr_name,UsrAccountTemp.usr_name);							//字符串只能拷贝 不能赋值
			strcpy(pUsrNode->usr_pwd,UsrAccountTemp.usr_pwd);
			pUsrNode->role=UsrAccountTemp.role;
			pUsrLinkTail->pNext_Usr_Account=pUsrNode;
			pUsrLinkTail=pUsrNode;
		}
	}
//读取学生链表
	while(EOF!=fscanf(stuFilePointer,"%d %s %c %lf %lf %lf %lf %lf",&StuInfoTemp.stu_id,&StuInfoTemp.stu_name,&StuInfoTemp.sex,&StuInfoTemp.stu_course_score[0],\
		&StuInfoTemp.stu_course_score[1],&StuInfoTemp.stu_course_score[2],&StuInfoTemp.stu_course_score[3],&StuInfoTemp.stu_course_score[4]))
	{
		if(NULL==pStuLink)
		{
			pStuLink=pStuLinkTail=pStuNode=(pSTU_INFO)calloc(1,sizeof(STU_INFO));				//pStuLink需要指向链表头
			pStuNode->pNext_Stu_Info=NULL;
			pStuNode->stu_id=StuInfoTemp.stu_id;							//字符串只能拷贝 不能赋值
			strcpy(pStuNode->stu_name,StuInfoTemp.stu_name);
			pStuNode->sex=StuInfoTemp.sex;
			for(i=0;i<5;i++)
			{
				pStuNode->stu_course_score[i]=StuInfoTemp.stu_course_score[i];
			}
		}else{
			pStuNode=(pSTU_INFO)calloc(1,sizeof(STU_INFO));
			pStuNode->pNext_Stu_Info=NULL;
			pStuNode->stu_id=StuInfoTemp.stu_id;
			strcpy(pStuNode->stu_name,StuInfoTemp.stu_name);
			pStuNode->sex=StuInfoTemp.sex;
			for(i=0;i<5;i++)
			{
				pStuNode->stu_course_score[i]=StuInfoTemp.stu_course_score[i];
			}
			pStuLinkTail->pNext_Stu_Info=pStuNode;
			pStuLinkTail=pStuNode;
		}
	}
	*ppUsrLink=pUsrLink;
	*ppStuLink=pStuLink;
}

USR_ACCOUNT_TYPE Sign_On_Page(pUSR_ACCOUNT pUsrLink)//返回值0表示普通登录，1表示管理员登录，-1表示登录错误
{
	int i,signal=0,wrongTime=1;
	char name[20];
	char pwd[20];
	pUSR_ACCOUNT linkHead=pUsrLink;
sign:
	i=0;
	system("cls");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("                 -----------------------------------------------                      \r");
	printf("                                                                                      \r");
	printf("                   STUDENT   INFORMATION   MANAGEMENT   SYSTEM                        \r");
	printf("                                                                                      \r");
	printf("                 -----------------------------------------------                      \r");
	printf("\n");
	printf("\n");
	printf("\n");
	if(signal==0)
		printf("                                     LOG ON                                           \n");
	else if(signal==1)
		printf("                              Worng Name!Try Again                                    \n");
	else
		printf("                              Worng Pwd! Try Again                                    \n");
	if(wrongTime>1) printf("                                 %d time last\n",4-wrongTime);
	printf("\n");
	printf("                                 User Name:");
	fflush(stdin);
	scanf("%s",&name);
	printf("                                 User  Pwd:");
	while(pwd[i]=_getch(),pwd[i]!=13)
	{
		if(pwd[i]=='\b'&&i>0)
		{
			printf("\b \b");
			i--;
		}else if(pwd[i]!='\b'&&i>=0){
			printf("*");
			i++;
		}else{
			continue;
		}
	}
	pwd[i]='\0';
	printf("\n");
	while(NULL!=pUsrLink)
	{
		if(strcmp(pUsrLink->usr_name,name)==0)//用户名匹配
		{
			if(strcmp(pUsrLink->usr_pwd,pwd)==0)//密码匹配
			{
				if(pUsrLink->role==1)			//是管理员就回1，不是就回0
					return 1;
				else
					return 0;
			}
			signal=2;
			wrongTime++;
			goto sign;
		}else{
			pUsrLink=pUsrLink->pNext_Usr_Account;
		}
	}
	signal=1;
	pUsrLink=linkHead;
	if(wrongTime<3)		//只能登录错误3次
	{
		wrongTime++;
		goto sign;
	}else{
		return -1;
	}
	return -1;
}

int Sign_Wrong_Page()
{
	char useless;
	system("cls");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("                 -----------------------------------------------                      \r");
	printf("                                                                                      \r");
	printf("                   STUDENT   INFORMATION   MANAGEMENT   SYSTEM                        \r");
	printf("                                                                                      \r");
	printf("                 -----------------------------------------------                      \r");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("                              Sign Wrong!\n");
	printf("                           Press Enter To Quit...\n");
	useless=_getch();
	return -1;
}

MENU_TYPE Sign_General_Page()
{
	char c;
	system("cls");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("                 -----------------------------------------------                      \r");
	printf("                                                                                      \r");
	printf("                   STUDENT   INFORMATION   MANAGEMENT   SYSTEM                        \r");
	printf("                                                                                      \r");
	printf("                 -----------------------------------------------                      \r");
	printf("\n");
	printf("                              General   Mode\n");
	printf("\n");
	printf("                         1.search  student  information                               \r");
	printf("\n");
	printf("                         9.exit                                                       \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("select operating index:");
	while(c=_getch(),!(c=='1'||c=='9'));//保证输入的正确性
	return c-'0';
}

MENU_TYPE Sign_Admin_Page()
{
	char c;
	system("cls");
	printf("\n");
	printf("\n");
	printf("                 -----------------------------------------------                      \r");
	printf("                                                                                      \r");
	printf("                   STUDENT   INFORMATION   MANAGEMENT   SYSTEM                        \r");
	printf("                                                                                      \r");
	printf("                 -----------------------------------------------                      \r");
	printf("                                                                                      \r");
	printf("                              Administrator   Mode                                    \r");
	printf("                                                                                      \r");
	printf("                         1.search  student  information                               \r");
	printf("                         2.add     student  information                               \r");
	printf("                         3.update  student  information                               \r");
	printf("                         4.delete  student  information                               \r");
	printf("                         5.add     user  account                                      \r");
	printf("                         6.update  user  account                                      \r");
	printf("                         7.delete  user  account                                      \r");
	printf("                         8.search  user  account                                      \r");
	printf("                         9.exit                                                       \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("select operating index:");//保证输入的正确性
	while(c=_getch(),c<'1'||c>'9');
	return c-'0';
}

int Stu_Exist(pSTU_INFO *pLink,int id)//查询学生存在性 引用指针
{
	while((*pLink)!=NULL)
	{
		if((*pLink)->stu_id==id)
			return 1;
		else
			*pLink=(*pLink)->pNext_Stu_Info;
	}
	return 0;
}

int Usr_Exist(pUSR_ACCOUNT *pLink,char *name)//查询用户存在性 引用指针
{
	while((*pLink)!=NULL)
	{
		if(strcmp((*pLink)->usr_name,name)==0)
			return 1;
		else
			*pLink=(*pLink)->pNext_Usr_Account;
	}
	return 0;
}

int Search_Stu_Page_General(pSTU_INFO pStuLink)//普通用户搜索学生页面
{
	char c,useless;//useless用于卡住页面输出错误
	char stuname[20];
	int stuid;
	pSTU_INFO cur=pStuLink;
research:
	cur=pStuLink;
	system("cls");
	printf("\n");
	printf("\n");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("                                    S I M S                                           \r");
	printf("\r");
	printf("                                                                                      \r");
	printf("                          Search  Student  Information                                \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("                                1.search  by  name                                    \r");
	printf("                                                                                      \r");
	printf("                                2.search  by  id                                      \r");
	printf("                                                                                      \r");
	printf("                                3.return                                              \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("select operating index:");//保证输入的正确性
	while(c=_getch(),c!='1'&&c!='2'&&c!='3');
	if(c=='1')
	{
		cur=pStuLink;
		system("cls");
		printf("\n");
		printf("\r");
		printf("\r");
		printf("\r");
		printf("                                    S I M S                                           \r");
		printf("\r");
		printf("                                                                                      \r");
		printf("                          Search  Student  Information                                \r");
		printf("                                                                                      \r");
		printf("                                                                                      \r");
reInputName:
		cur=pStuLink;
		printf("Student's Name:");
		fflush(stdin);
		gets(stuname);

		if(stuname==NULL)
		{
			printf("Wrong Input!\n");//错误输入 就重新输入
			goto reInputName;
		}
		while(cur!=NULL)
		{
			if(strcmp(cur->stu_name,stuname)==0)
			{
				printf("\n          Num  Name      Sex  Score1  Score2  Score3  Score4  Score5\n");
				printf("          %d %-10s %c %7.2lf %7.2lf %7.2lf %7.2lf %7.2lf\n",cur->stu_id,cur->stu_name,cur->sex,cur->stu_course_score[0],\
					cur->stu_course_score[1],cur->stu_course_score[2],cur->stu_course_score[3],cur->stu_course_score[4]);
				printf("\nPress Enter To Return:");
				useless=_getch();
				goto research;
			}else{
				cur=cur->pNext_Stu_Info;
			}
		}
		printf("\nThis data not exist!\nPress Enter To Return:");
		useless=_getch();
		goto research;
	}else if(c=='2'){
		cur=pStuLink;
		system("cls");
reInputId:
		cur=pStuLink;
		printf("\n");
		printf("\r");
		printf("\r");
		printf("\r");
		printf("                                    S I M S                                           \r");
		printf("\r");
		printf("                                                                                      \r");
		printf("                          Search  Student  Information                                \r");
		printf("                                                                                      \r");
		printf("Student's Id:");
		fflush(stdin);
		scanf("%d",&stuid);

		if(stuid>10000||stuid<1000)
		{
			printf("Wrong Input!\n");//错误输入 就重新输入
			goto reInputId;
		}
		while(cur!=NULL)
		{
			if(cur->stu_id==stuid)
			{
				printf("\n          Num  Name      Sex  Score1  Score2  Score3  Score4  Score5\n");
				printf("          %d %-10s %c %7.2lf %7.2lf %7.2lf %7.2lf %7.2lf\n",cur->stu_id,cur->stu_name,cur->sex,cur->stu_course_score[0],\
					cur->stu_course_score[1],cur->stu_course_score[2],cur->stu_course_score[3],cur->stu_course_score[4]);
				printf("\nPress Enter To Return:");
				useless=_getch();
				goto research;
			}else{
				cur=cur->pNext_Stu_Info;
			}
		}
		printf("\nThis data not exist!\nPress Enter To Return:");
		useless=_getch();
		goto research;
	}else{//return
		return 1;
	}
}

int Search_Stu_Page_Admin(pSTU_INFO pStuLink)//管理员搜索学生页面
{
	char c,useless;//useless用于卡住页面输出错误
	char stuname[20]={0};
	int stuid=0;
	pSTU_INFO cur=pStuLink;
research:
	cur=pStuLink;
	system("cls");
	printf("\n");
	printf("\n");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("                                    S I M S                                           \r");
	printf("\r");
	printf("                                                                                      \r");
	printf("                          Search  Student  Information                                \r");
	printf("                                                                                      \r");
	printf("                                0.search  all                                         \r");
	printf("                                                                                      \r");
	printf("                                1.search  by  name                                    \r");
	printf("                                                                                      \r");
	printf("                                2.search  by  id                                      \r");
	printf("                                                                                      \r");
	printf("                                3.return                                              \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("select operating index:");//保证输入的正确性
	while(c=_getch(),c!='0'&&c!='1'&&c!='2'&&c!='3');
	if(c=='0')
	{
		cur=pStuLink;
		system("cls");
		while(NULL!=cur)//输出全部学生信息
		{
			printf("\n          Num  Name      Sex  Score1  Score2  Score3  Score4  Score5\n");
			printf("           %d %-10s %c %7.2lf %7.2lf %7.2lf %7.2lf %7.2lf\n",cur->stu_id,cur->stu_name,cur->sex,cur->stu_course_score[0],\
				cur->stu_course_score[1],cur->stu_course_score[2],cur->stu_course_score[3],cur->stu_course_score[4]);
			cur=cur->pNext_Stu_Info;
		}
		printf("\nPress Enter To Return:");
		useless=_getch();
		goto research;
	}else if(c=='1'){
		cur=pStuLink;
		system("cls");
reInputName:
		cur=pStuLink;
		printf("Student's Name:");
		//gets(stuname);
		fflush(stdin);
		scanf("%s",&stuname);
		if(stuname==NULL)
		{
			printf("Wrong Input!\n");//错误输入 就重新输入
			goto reInputName;
		}
		while(cur!=NULL)
		{
			if(strcmp(cur->stu_name,stuname)==0)
			{
				printf("\nNum  Name      Sex  Score1  Score2  Score3  Score4  Score5\n");
				printf("%d %-10s %c %7.2lf %7.2lf %7.2lf %7.2lf %7.2lf\n",cur->stu_id,cur->stu_name,cur->sex,cur->stu_course_score[0],\
					cur->stu_course_score[1],cur->stu_course_score[2],cur->stu_course_score[3],cur->stu_course_score[4]);
				printf("\nPress Enter To Return:");
				useless=_getch();
				goto research;

			}else{
				cur=cur->pNext_Stu_Info;
			}
		}
		printf("\nThis data not exist!\nPress Enter To Return:");
		useless=_getch();
		goto research;
	}else if(c=='2'){
		system("cls");
reInputId:
		cur=pStuLink;
		printf("Student's Id:");
		fflush(stdin);
		scanf("%d",&stuid);

		if(stuid>10000||stuid<1000)
		{
			printf("Wrong Input!Student's number is from 1000 to 9999\n");//错误输入 就重新输入
			goto reInputId;
		}
		while(cur!=NULL)
		{
			if(cur->stu_id==stuid)
			{
				printf("\nNum  Name      Sex  Score1  Score2  Score3  Score4  Score5\n");
				printf("%d %-10s %c %7.2lf %7.2lf %7.2lf %7.2lf %7.2lf\n",cur->stu_id,cur->stu_name,cur->sex,cur->stu_course_score[0],\
					cur->stu_course_score[1],cur->stu_course_score[2],cur->stu_course_score[3],cur->stu_course_score[4]);
				printf("\nPress Enter To Return:");
				useless=_getch();
				goto research;
			}else{
				cur=cur->pNext_Stu_Info;
			}
		}
		printf("This data not exist!\nPress Enter To Return:");
		useless=_getch();
		goto research;
	}else{//return
		return 1;
	}
}

int Add_Stu_Page(pSTU_INFO *ppStuLink)
{
	int ret;
	char useless;
	pSTU_INFO StuInfoTemp,LinkTail;
	StuInfoTemp=(pSTU_INFO)calloc(1,sizeof(STU_INFO));
	LinkTail=*ppStuLink;
	system("cls");
	printf("\n");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("                                    S I M S                                           \r");
	printf("\r");
	printf("                                                                                      \r");
	printf("                            Add  Student  Information                                 \r");
	printf("                                                                                      \r");
	printf("\n          Num  Name      Sex  Score1  Score2  Score3  Score4  Score5\n");
	printf("          1010  minmin     m    95.5     92      93.5    89      91.5 (example)\n");
	fflush(stdin);
	printf("          ");
	ret=scanf("%d %s %c %lf %lf %lf %lf %lf",&StuInfoTemp->stu_id,&StuInfoTemp->stu_name,&StuInfoTemp->sex,&StuInfoTemp->stu_course_score[0],\
		&StuInfoTemp->stu_course_score[1],&StuInfoTemp->stu_course_score[2],&StuInfoTemp->stu_course_score[3],&StuInfoTemp->stu_course_score[4]);
	if(ret!=8)
	{
		printf("\nWrong Input!Press Enter To Retern...");
		useless=_getch();
		return 1;
	}
	//判断是否重复
	while(LinkTail!=NULL)
	{
		if(LinkTail->stu_id==StuInfoTemp->stu_id)
		{
			printf("\nThis student's data is already exist!Press Enter To Retern...");
			useless=_getch();
			return 1;
		}else{
			LinkTail=LinkTail->pNext_Stu_Info;
		}
	}
	//顺序添加到链表
	Stu_Insert(ppStuLink,StuInfoTemp);//学生信息插入

	return 0;
}

int Update_Stu_Page(pSTU_INFO *ppStuLink)//更新学生信息
{
	int i,ret;
	char c,useless;
	pSTU_INFO StuInfoTemp,LinkTail;
	StuInfoTemp=(pSTU_INFO)calloc(1,sizeof(STU_INFO));
	LinkTail=*ppStuLink;
	system("cls");
	printf("\n");
	printf("\n");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("                                    S I M S                                           \r");
	printf("\r");
	printf("                                                                                      \r");
	printf("                          Update  Student  Information                                \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("                                1.update  by  id                                      \r");
	printf("                                                                                      \r");
	printf("                                2.return                                              \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("select operating index:");//保证输入的正确性
	while(c=_getch(),c!='1'&&c!='2');
	if(c=='1')
	{
		system("cls");
		printf("\n");
		printf("\r");
		printf("\r");
		printf("\r");
		printf("                                    S I M S                                           \r");
		printf("\r");
		printf("                                                                                      \r");
		printf("                          Update  Student  Information                                \r");
		printf("                                                                                      \r");
		printf("                                                                                      \r");
		printf("Student's id:");
		scanf("%d",&StuInfoTemp->stu_id);
		if(Stu_Exist(&LinkTail,StuInfoTemp->stu_id))//学生存在
		{
			printf("\n          Num  Name      Sex  Score1  Score2  Score3  Score4  Score5\n");
			printf("           %d %-10s %c %7.2lf %7.2lf %7.2lf %7.2lf %7.2lf\n",LinkTail->stu_id,LinkTail->stu_name,LinkTail->sex,LinkTail->stu_course_score[0],\
				LinkTail->stu_course_score[1],LinkTail->stu_course_score[2],LinkTail->stu_course_score[3],LinkTail->stu_course_score[4]);
reinput:
			printf("Input %s's update scores\n",LinkTail->stu_name);
			printf("Score1  Score2  Score3  Score4  Score5\n");
			ret=scanf("%lf %lf %lf %lf %lf",&StuInfoTemp->stu_course_score[0],&StuInfoTemp->stu_course_score[1],\
				&StuInfoTemp->stu_course_score[2],&StuInfoTemp->stu_course_score[3],&StuInfoTemp->stu_course_score[4]);
			if(ret==5)
			{
				for(i=0;i<5;i++)//更新成绩
				{
					LinkTail->stu_course_score[i]=StuInfoTemp->stu_course_score[i];
				}
				return 0;
			}else{
				printf("\nWrong Input!\n");
				goto reinput;
			}
		}else{//学生不存在
			printf("\nThis data not exist!Press Enter To Return...");
			useless=_getch();
			return 1;
		}
	}else if(c=='2'){
		return 1;
	}
	return 1;
}

int Delete_Stu_Page(pSTU_INFO *ppStuLink)//更新学生信息
{
	//int i,ret;
	char c,useless;
	pSTU_INFO StuInfoTemp,LinkTail,LinkPre;
	StuInfoTemp=(pSTU_INFO)calloc(1,sizeof(STU_INFO));
	LinkTail=*ppStuLink;
	system("cls");
	printf("\n");
	printf("\n");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("                                    S I M S                                           \r");
	printf("\r");
	printf("                                                                                      \r");
	printf("                          Delete  Student  Information                                \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("                                1.delete  by  id                                      \r");
	printf("                                                                                      \r");
	printf("                                2.return                                              \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("select operating index:");//保证输入的正确性
	while(c=_getch(),c!='1'&&c!='2');
	if(c=='1')
	{
		system("cls");
		printf("\n");
		printf("\r");
		printf("\r");
		printf("\r");
		printf("                                    S I M S                                           \r");
		printf("\r");
		printf("                                                                                      \r");
		printf("                            Delete  Student  Information                                 \r");
		printf("                                                                                      \r");
		printf("Student's id:");
		scanf("%d",&StuInfoTemp->stu_id);
		if(Stu_Exist(&LinkTail,StuInfoTemp->stu_id))//学生存在
		{
			printf("\n          Num  Name      Sex  Score1  Score2  Score3  Score4  Score5\n");
			printf("          %d %-10s %c %7.2lf %7.2lf %7.2lf %7.2lf %7.2lf\n",LinkTail->stu_id,LinkTail->stu_name,LinkTail->sex,LinkTail->stu_course_score[0],\
				LinkTail->stu_course_score[1],LinkTail->stu_course_score[2],LinkTail->stu_course_score[3],LinkTail->stu_course_score[4]);
//reinput:
			printf("\nPress \"Enter\" To Delete\n");
			c=_getch();
			if(c=='\r')
			{
				LinkPre=*ppStuLink;
				if(LinkPre==LinkTail)//首结点就是要删除结点
				{
					LinkPre=LinkPre->pNext_Stu_Info;
					free(LinkTail);
					*ppStuLink=LinkPre;
					return 0;
				}
				while(LinkPre->pNext_Stu_Info!=LinkTail)//找到删除结点的前驱
				{
					LinkPre=LinkPre->pNext_Stu_Info;
				}
				LinkPre->pNext_Stu_Info=LinkTail->pNext_Stu_Info;
				free(LinkTail);//释放节点
				return 0;
			}else{
				printf("\nDelete Operation Has Been Canceled!\nPress Key To Return...");
				c=_getch();
				return 1;
			}
		}else{//学生不存在
			printf("\nThis data not exist!\nPress Enter To Return...");
			useless=_getch();
			return 1;
		}
	}else if(c=='2'){
		return 1;
	}
	return 1;
}

int Add_Usr_Page(pUSR_ACCOUNT *ppUsrLink)//管理员添加用户
{
	int ret;
	char useless;
	pUSR_ACCOUNT UsrAccountTemp,LinkTail;
	UsrAccountTemp=(pUSR_ACCOUNT)calloc(1,sizeof(USR_ACCOUNT));
	LinkTail=*ppUsrLink;
	system("cls");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("                                    S I M S                                           \r");
	printf("\r");
	printf("                                                                                      \r");
	printf("                             Add  User  Information                                   \r");
	printf("                                                                                      \r");
	printf("\n                         Name    Password    Role\n");
	printf("                         panjie     panjie      1    (example)\n");
	printf("                         ");
	ret=scanf("%s %s %d",&UsrAccountTemp->usr_name,&UsrAccountTemp->usr_pwd,&UsrAccountTemp->role);

	if(ret!=3||UsrAccountTemp->role>1||UsrAccountTemp->role<0)//输入不满足规范
	{
		printf("\nWrong Input!Press Enter To Retern...");
		useless=_getch();
		return 1;
	}
	//判断是否重复
	while(LinkTail!=NULL)
	{
		if(strcmp(LinkTail->usr_name,UsrAccountTemp->usr_name)==0)
		{
			printf("\nThis user's data is already exist!Press Enter To Retern...");
			useless=_getch();
			return 1;
		}else{
			LinkTail=LinkTail->pNext_Usr_Account;
		}
	}
	//添加到学生链表尾
	LinkTail=*ppUsrLink;
	while(LinkTail->pNext_Usr_Account!=NULL)
		LinkTail=LinkTail->pNext_Usr_Account;
	LinkTail->pNext_Usr_Account=UsrAccountTemp;
	UsrAccountTemp->pNext_Usr_Account=NULL;
	return 0;
}

int Update_Usr_Page(pUSR_ACCOUNT *ppUsrLink)//管理员更新用户
{
	int /*i,*/ret;
	char c,useless;
	pUSR_ACCOUNT UsrAccountTemp,LinkTail;
	UsrAccountTemp=(pUSR_ACCOUNT)calloc(1,sizeof(USR_ACCOUNT));
	LinkTail=*ppUsrLink;
	system("cls");
	printf("\n");
	printf("\n");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("                                    S I M S                                           \r");
	printf("\r");
	printf("                                                                                      \r");
	printf("                           Update  User  Information                                  \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("                                1.update  by  username                                \r");
	printf("                                                                                      \r");
	printf("                                2.return                                              \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("select operating index:");//保证输入的正确性
	while(c=_getch(),c!='1'&&c!='2');
	if(c=='1')
	{
		system("cls");
		printf("\n");
		printf("\r");
		printf("\r");
		printf("\r");
		printf("                                    S I M S                                           \r");
		printf("\r");
		printf("                                                                                      \r");
		printf("                            Update  User  Information                                 \r");
		printf("                                                                                      \r");
		printf("User's name:");
		fflush(stdin);
		scanf("%s",&UsrAccountTemp->usr_name);
		if(Usr_Exist(&LinkTail,UsrAccountTemp->usr_name))//学生存在
		{
			printf("\n                    Name    Password    Role\n");
			printf("                    %-8s %-12s %-d\n",LinkTail->usr_name,LinkTail->usr_pwd,LinkTail->role);
reinput:
			printf("Input User %s's Update Information:",LinkTail->usr_name);
			ret=scanf("%s %d",&UsrAccountTemp->usr_pwd,&UsrAccountTemp->role);
			if(ret==2&&(UsrAccountTemp->role==1||UsrAccountTemp->role==0))
			{
				strcpy(LinkTail->usr_pwd,UsrAccountTemp->usr_pwd);
				LinkTail->role=UsrAccountTemp->role;
				return 0;
			}else{
				printf("\nWrong Input!\n");
				goto reinput;
			}
		}else{
			printf("\nThis user's data is not exist!Press Enter To Retern...");
			useless=_getch();
			return 1;
		}
	}else if(c=='2'){
		return 1;
	}
	return 1;
}

int Delete_Usr_Page(pUSR_ACCOUNT *ppUsrLink)//更新学生信息
{
	//int i,ret;
	char c,useless;
	pUSR_ACCOUNT UsrAccountTemp,LinkTail,LinkPre;
	UsrAccountTemp=(pUSR_ACCOUNT)calloc(1,sizeof(USR_ACCOUNT));
	LinkTail=*ppUsrLink;
	system("cls");
	printf("\n");
	printf("\n");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("                                    S I M S                                           \r");
	printf("\r");
	printf("                                                                                      \r");
	printf("                            Delete  User  Information                                 \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("                               1.delete  by  username                                 \r");
	printf("                                                                                      \r");
	printf("                               2.return                                               \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("select operating index:");//保证输入的正确性
	while(c=_getch(),c!='1'&&c!='2');
	if(c=='1')
	{
		system("cls");
		printf("\n");
		printf("\n");
		printf("\r");
		printf("\r");
		printf("\r");
		printf("                                    S I M S                                           \r");
		printf("\r");
		printf("                                                                                      \r");
		printf("                            Delete  User  Information                                 \r");
		printf("                                                                                      \r");
		printf("                                                                                      \r");
		printf("User's name:");
		fflush(stdin);
		scanf("%s",&UsrAccountTemp->usr_name);
		if(Usr_Exist(&LinkTail,UsrAccountTemp->usr_name))//学生存在
		{
			printf("\n                    Name    Password    Role\n");
			printf("                    %-8s %-12s %-d\n",LinkTail->usr_name,LinkTail->usr_pwd,LinkTail->role);
//reinput:
			printf("\nPress \"Enter\" To Delete\n");
			c=_getch();
			if(c=='\r')
			{
				LinkPre=*ppUsrLink;
				if(LinkPre==LinkTail)//首结点就是要删除结点
				{
					LinkPre=LinkPre->pNext_Usr_Account;
					free(LinkTail);
					*ppUsrLink=LinkPre;
					return 0;
				}
				while(LinkPre->pNext_Usr_Account!=LinkTail)//找到删除结点的前驱
				{
					LinkPre=LinkPre->pNext_Usr_Account;
				}
				LinkPre->pNext_Usr_Account=LinkTail->pNext_Usr_Account;
				free(LinkTail);//释放节点
				return 0;
			}else{
				printf("\nDelete Operation Has Been Canceled!\nPress Key To Return...");
				c=_getch();
				return 1;
			}
		}else{//用户不存在
			printf("\nThis data not exist!\nPress Enter To Return...");
			useless=_getch();
			return 1;
		}
	}else if(c=='2'){
		return 1;
	}
	return 1;
}

int Search_Usr_Page(pUSR_ACCOUNT pUsrLink)//管理员搜索用户页面
{
	char c,useless;//useless用于卡住页面输出错误
	char usrname[20]={0};
	//int stuid=0;
	pUSR_ACCOUNT cur=pUsrLink;
reSearch:
	cur=pUsrLink;
	system("cls");
	printf("\n");
	printf("\n");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("                                    S I M S                                           \r");
	printf("\r");
	printf("                                                                                      \r");
	printf("                           Search  User  Information                                  \r");
	printf("                                                                                      \r");
	printf("                                0.search  all                                         \r");
	printf("                                                                                      \r");
	printf("                                1.search  by  name                                    \r");
	printf("                                                                                      \r");
	printf("                                2.return                                              \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("                                                                                      \r");
	printf("select operating index:");//保证输入的正确性
	while(c=_getch(),c!='0'&&c!='1'&&c!='2');
	if(c=='0')
	{
		system("cls");
		printf("\r");
		printf("\r");
		printf("                                    S I M S                                           \r");
		printf("\r");
		printf("                                                                                      \r");
		printf("                           Search  User  Information                                  \r");
		printf("                                                                                      \r");
		while(NULL!=cur)//输出全部用户信息
		{
			printf("\n                         Name    Password    Role\n");
			printf("                         %-8s %-12s %-d\n",cur->usr_name,cur->usr_pwd,cur->role);
			cur=cur->pNext_Usr_Account;
		}
		printf("\nPress Enter To Return:");
		useless=_getch();
		goto reSearch;
	}else if(c=='1'){
		system("cls");
reInputName:
		cur=pUsrLink;
		printf("User's Name:");
		//gets(stuname);
		fflush(stdin);
		scanf("%s",&usrname);
		if(usrname==NULL)
		{
			printf("Wrong Input!\n");//错误输入 就重新输入
			goto reInputName;
		}
		while(cur!=NULL)
		{
			if(strcmp(cur->usr_name,usrname)==0)//找到用户
			{
				printf("\nName    Password    Role\n");
				printf("%-8s %-12s %-d\n",cur->usr_name,cur->usr_pwd,cur->role);
				printf("\nPress Enter To Return:");
				useless=_getch();
				goto reSearch;
			}else{
				cur=cur->pNext_Usr_Account;
			}
		}//没找到用户
		printf("\nThis data not exist!\nPress Enter To Return:");
		useless=_getch();
		goto reSearch;
	}else if(c=='2'){
		return 1;
	}
	return 1;
}

void Stu_Insert(pSTU_INFO *ppStuLink,STU_INFO *pStuInfoTemp)//学生信息插入
{
	pSTU_INFO curNode,preNode;
	preNode=NULL;
	curNode=*ppStuLink;
	while(curNode!=NULL)
	{
		if(preNode==NULL&&pStuInfoTemp->stu_id<curNode->stu_id)//就是第一个结点
		{
			*ppStuLink=pStuInfoTemp;
			pStuInfoTemp->pNext_Stu_Info=curNode;
			preNode=pStuInfoTemp;
			return;
		}else if(pStuInfoTemp->stu_id<curNode->stu_id){
			preNode->pNext_Stu_Info=pStuInfoTemp;
			pStuInfoTemp->pNext_Stu_Info=curNode;
			return;
		}else{
			preNode=curNode;
			curNode=curNode->pNext_Stu_Info;
		}

	}
	preNode->pNext_Stu_Info=pStuInfoTemp;
	pStuInfoTemp->pNext_Stu_Info=NULL;
}

void Data_Save(pUSR_ACCOUNT *ppUsrLink,pSTU_INFO *ppStuLink)
{
	FILE *usrFilePointer,*stuFilePointer;	//文件指针	
	usrFilePointer=fopen("usr_account.txt","w");
	stuFilePointer=fopen("stu_info.txt","w");
//读取用户链表
	while(*ppUsrLink!=NULL)
	{
		fprintf(usrFilePointer,"%s %s %d\n",(*ppUsrLink)->usr_name,(*ppUsrLink)->usr_pwd,(*ppUsrLink)->role);
		*ppUsrLink=(*ppUsrLink)->pNext_Usr_Account;
	}
	while(*ppStuLink!=NULL)
	{
		fprintf(stuFilePointer,"%d %s %c %5.2lf %5.2lf %5.2lf %5.2lf %5.2lf\n",(*ppStuLink)->stu_id,(*ppStuLink)->stu_name,(*ppStuLink)->sex,(*ppStuLink)->stu_course_score[0],\
			(*ppStuLink)->stu_course_score[1],(*ppStuLink)->stu_course_score[2],(*ppStuLink)->stu_course_score[3],(*ppStuLink)->stu_course_score[4]);
		*ppStuLink=(*ppStuLink)->pNext_Stu_Info;
	}
	fclose(usrFilePointer);
	fclose(stuFilePointer);

}
