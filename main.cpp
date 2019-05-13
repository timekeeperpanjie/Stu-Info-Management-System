#include "func.h"



int main(int argc,char *argv[])
{
	char useless;
	int temp;
	MENU_TYPE ret;
	USR_ACCOUNT_TYPE role;
	USR_ACCOUNT *pUsrLink=NULL;					//用户链表
	STU_INFO *pStuLink=NULL;						//学生链表
	FILE *usrFilePointer,*stuFilePointer;	//文件指针	
	usrFilePointer=fopen(argv[1],"r+");
	stuFilePointer=fopen(argv[2],"r+");
//读取用户链表
	Link_Initial(usrFilePointer,stuFilePointer,&pUsrLink,&pStuLink);
	fclose(usrFilePointer);
	fclose(stuFilePointer);
//加载界面
//allStart:
	role=Sign_On_Page(pUsrLink);
	if(role==-1)
	{
		temp=Sign_Wrong_Page();
		if(temp==-1)
		{
			goto end;
		}

	}else if(role==0){
GeneralPage:
		ret=Sign_General_Page();
	}else{
AdminPage:
		ret=Sign_Admin_Page();
	}
//根据页面index和role导流用户		//用户输入数字的正确性由对应页面保证
	switch(ret)
	{
	case 1:
		if(role==1)//对用户分流
		{
			temp=Search_Stu_Page_Admin(pStuLink);
			if(temp==1)
				goto AdminPage;
		}else{//role==0
			temp=Search_Stu_Page_General(pStuLink);
			if(temp==1)
				goto GeneralPage;
		}
		break;
	case 2://添加学生信息
		temp=Add_Stu_Page(&pStuLink);
		if(temp==1)
		{
			goto AdminPage;
		}else{
			printf("\nOperation Success!\nPress Enter To Retern...");
			useless=_getch();
			goto AdminPage;
		}
		break;
	case 3:
		temp=Update_Stu_Page(&pStuLink);
		if(temp==1)
		{
			goto AdminPage;
		}else{
			printf("\nOperation Success!\nPress Enter To Retern...");
			useless=_getch();
			goto AdminPage;
		}
		break;
	case 4:
		temp=Delete_Stu_Page(&pStuLink);
		if(temp==1)
		{
			goto AdminPage;
		}else{
			printf("\nOperation Success!\nPress Enter To Retern...");
			useless=_getch();
			goto AdminPage;
		}
		break;
	case 5:
		temp=Add_Usr_Page(&pUsrLink);
		if(temp==1)
		{
			goto AdminPage;
		}else{
			printf("\nOperation Success!\nPress Enter To Retern...");
			useless=_getch();
			goto AdminPage;
		}
		break;
	case 6:
		temp=Update_Usr_Page(&pUsrLink);
		if(temp==1)
		{
			goto AdminPage;
		}else{
			printf("\nOperation Success!\nPress Enter To Retern...");
			useless=_getch();
			goto AdminPage;
		}
		break;
	case 7:
		temp=Delete_Usr_Page(&pUsrLink);
		if(temp==1)
		{
			goto AdminPage;
		}else{
			printf("\nOperation Success!\nPress Enter To Retern...");
			useless=_getch();
			goto AdminPage;
		}
		break;
	case 8:
		temp=Search_Usr_Page(pUsrLink);
		if(temp==1)
		{
			goto AdminPage;
		}else{
			printf("\nOperation Success!\nPress Enter To Retern...");
			useless=_getch();
			goto AdminPage;
		}
		break;
	default:
		printf("\nDo You Want To Save Data's Change(Y/N):");
		fflush(stdin);
		while(scanf("%c",&useless),useless!='Y'&&useless!='N'&&useless!='y'&&useless!='n');//保证正确输入
		if(useless=='Y'||useless=='y')
		{
			Data_Save(&pUsrLink,&pStuLink);

			printf("\nSave Successed!\nPress Key To Quit...");
end:
			useless=_getch();

		}else{
			printf("\nSave Has Been Canceled!\nPress Key To Quit...");
			useless=_getch();
		}
	}

}
