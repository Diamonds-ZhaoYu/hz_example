#include <windows.h>
#include "resource.h"
#include "myprocess.h"
#include "rightmenu.h"
#include <COMMCTRL.H>
#include <stdio.h>
#ifdef  UNICODE
#define MY_COPY CF_UNICODETEXT
#else
#define MY_COPY CF_TEXT
#endif

LPTSTR lpData = NULL;
HANDLE heap;
//////////////////////////////////////////////////////////////////////////
///��õ�ǰ��DLL
//////////////////////////////////////////////////////////////////////////
VOID CallUndll(HWND hWnd)
{
	TCHAR szDll[MAX_PATH] = {0},szFile[MAX_PATH] = {0};
	BOOL fal;
	HWND list1 = GetDlgItem(hWnd,IDC_LIST2);
	
	if(MessageBox(NULL,"ȷ��Ҫж��DLL��","��ʾ",MB_YESNO | MB_ICONQUESTION) != IDYES)
	{

		
		return;
	}


	int num = SendMessage(list1,LB_GETCURSEL,0,0);
	

	if(num == -1)
	{
		MessageBox(NULL,"��ѡ����Ҫ�����Ķ���!","��ʾ",MB_OK);

		return;
	}
	//���DLL
	SendMessage(list1,LB_GETTEXT,num,(LPARAM)szDll);
	ListView_GetItemText(GetDlgItem(hWnd,IDC_LIST3),ListView_GetSelectionMark(GetDlgItem(hWnd,IDC_LIST3)),2,szFile,sizeof(szFile)+1);

	fal = UnloadDll(atoi(szFile),szDll);
	if(fal)
	{
		MessageBox(NULL,"ж��DLL�ɹ�!","��ʾ",MB_OK);
		SendMessage(list1,LB_DELETESTRING,num,0);
	}
	else
	{
		MessageBox(NULL,"ж��DLLʧ��!","��ʾ",MB_OK);
	}

}
//////////////////////////////////////////////////////////////////////////
///���Ƶ�ǰ��
//////////////////////////////////////////////////////////////////////////
VOID CallCopyRow(HWND hWnd)
{

	HGLOBAL buffer1;
	char *buffer;
	TCHAR szDll[MAX_PATH] ={0};
	HWND list1 = GetDlgItem(hWnd,IDC_LIST2);
	
	int num = SendMessage(list1,LB_GETCURSEL,0,0);
	

	if(num == -1)
	{
		MessageBox(NULL,"��ѡ����Ҫ�����Ķ���!","��ʾ",MB_OK);

		return;
	}
	
	buffer1 = GlobalAlloc(GMEM_DDESHARE,MAX_PATH+1);
		
	buffer = (char*)GlobalLock(buffer1);
	
	SendMessage(list1,LB_GETTEXT,num,(LPARAM)szDll);
	
	//sprintf(szDll,"%s - By��Rain",szDll);
	strcpy(buffer,szDll);
	//���DLL
	GlobalUnlock(buffer1);
	
	//lstrcpy(lpData,szDll);
	//�򿪼��а�
	if(OpenClipboard(NULL))
	{
		//���ü��а�����
		EmptyClipboard();
	//	MessageBox(NULL,szDll,szDll,MB_OK);
		SetClipboardData(MY_COPY,buffer1);
		
	}
	CloseClipboard();
	/***
		if(OpenClipboard(NULL))
	{
		LPTSTR t1 =  GetClipboardData(MY_COPY);
		MessageBox(NULL,t1,t1,MB_OK);
	}
	CloseClipboard();
	***/
}

//////////////////////////////////////////////////////////////////////////
///���Ƶ�ǰȫ����
//////////////////////////////////////////////////////////////////////////
VOID CallCopyAllRow(HWND hWnd)
{

	HGLOBAL buffer1;
	char *buffer,*b,*b1; 

	TCHAR szDll[MAX_PATH] ={0},szFile[8000]={0};
	int max = 0;
	HWND list1 = GetDlgItem(hWnd,IDC_LIST2);
	int i = 0;
	//���ȫ������
	int count = SendMessage(list1,LB_GETCOUNT,0,0);
	
	for (;i < count;i++)
	{
		max += MAX_PATH;
	

		ZeroMemory(szDll,sizeof(szDll));	
		SendMessage(list1,LB_GETTEXT,i,(LPARAM)szDll);
		if(i == 0)
		{
			b1 =(char*)malloc(max);
			sprintf(b1,"%s",szDll);
		}
		else
		{
			
			b = (char*)malloc(sizeof(b1));
			b = b1;
			b1 =(char*)malloc(max);
			
			sprintf(b1,"%s\r\n%s",b,szDll);
		}
		
	}

	
	buffer1 = GlobalAlloc(GMEM_DDESHARE,max+1);
		
	buffer = (char*)GlobalLock(buffer1);
	
	
	
	strcpy(buffer,b1);
	//���DLL
	GlobalUnlock(buffer1);
	
	//�򿪼��а�
	if(OpenClipboard(NULL))
	{
		//���ü��а�����
		EmptyClipboard();
		SetClipboardData(MY_COPY,buffer1);
		
	}
	CloseClipboard();

}

//////////////////////////////////////////////////////////////////////////
///����Listview
//////////////////////////////////////////////////////////////////////////
VOID CallCopyById(HWND hWnd,int id)
{

	HGLOBAL buffer1;
	char *buffer;
	TCHAR szFile[125] = {0};
	HWND hwnd1 = GetDlgItem(hWnd,IDC_LIST3);
	int num = ListView_GetSelectionMark(hwnd1);
	
	if(num == -1)
	{
		MessageBox(NULL,"��ѡ����Ҫ�����Ķ���!","��ʾ",MB_OK);

		return;
	}
	ListView_GetItemText(hwnd1,num,id,szFile,sizeof(szFile)+1);

	buffer1 = GlobalAlloc(GMEM_DDESHARE,MAX_PATH+1);	
	buffer = (char*)GlobalLock(buffer1);
	

	strcpy(buffer,szFile);

	GlobalUnlock(buffer1);
	

	//�򿪼��а�
	if(OpenClipboard(NULL))
	{
		//���ü��а�����
		EmptyClipboard();

		SetClipboardData(MY_COPY,buffer1);
		
	}
	CloseClipboard();	
}

//////////////////////////////////////////////////////////////////////////
///����Listview��ǰ��
//////////////////////////////////////////////////////////////////////////
VOID CallCopyByRow(HWND hWnd)
{

	HGLOBAL buffer1;
	char *buffer; 
	TCHAR szFile[500]={0},s1[MAX_PATH] ={0},s2[MAX_PATH] ={0},s3[MAX_PATH] ={0},s4[MAX_PATH] ={0};

	HWND hwnd1 = GetDlgItem(hWnd,IDC_LIST3);
	int num = ListView_GetSelectionMark(hwnd1);
	if(num == -1)
	{
		MessageBox(NULL,"��ѡ����Ҫ�����Ķ���!","��ʾ",MB_OK);

		return;
	}
	//��õ�ǰ��
	ListView_GetItemText(hwnd1,num,0,s1,sizeof(s1)+1);
	ListView_GetItemText(hwnd1,num,1,s2,sizeof(s2)+1);
	ListView_GetItemText(hwnd1,num,2,s3,sizeof(s3)+1);
	ListView_GetItemText(hwnd1,num,3,s4,sizeof(s4)+1);
	
	sprintf(szFile,"%s\t%s\t%s\t%s",s1,s2,s3,s4);

	buffer1 = GlobalAlloc(GMEM_DDESHARE,sizeof(szFile) + 1);
		
	buffer = (char*)GlobalLock(buffer1);
	
	
	
	strcpy(buffer,szFile);
	//���DLL
	GlobalUnlock(buffer1);
	
	//�򿪼��а�
	if(OpenClipboard(NULL))
	{
		//���ü��а�����
		EmptyClipboard();
		SetClipboardData(MY_COPY,buffer1);
		
	}
	CloseClipboard();

}

//////////////////////////////////////////////////////////////////////////
///����Listview��ǰ��
//////////////////////////////////////////////////////////////////////////
VOID CallCopyByAllRow(HWND hWnd)
{

	HGLOBAL buffer1;
	char *buffer,*szFile,*b1; 
	TCHAR s1[100] ={0},s2[100] ={0},s3[100] ={0},s4[100] ={0};

	int max = 0;
	int i = 0;
	HWND hwnd1 = GetDlgItem(hWnd,IDC_LIST3);
	
	//���ȫ������
	int count = ListView_GetItemCount(hwnd1);
	
	for (;i < count;i++)
	{
		max += (100 + 20)*4 ;
		ZeroMemory(s1,sizeof(s1));	
		ZeroMemory(s2,sizeof(s2));
		ZeroMemory(s3,sizeof(s3));
		ZeroMemory(s4,sizeof(s4));

		ListView_GetItemText(hwnd1,i,0,s1,sizeof(s1)+1);
		ListView_GetItemText(hwnd1,i,1,s2,sizeof(s2)+1);
		ListView_GetItemText(hwnd1,i,2,s3,sizeof(s3)+1);
		ListView_GetItemText(hwnd1,i,3,s4,sizeof(s4)+1);
	
		if(i == 0)
		{
			szFile =(char*)malloc(max);
			sprintf(szFile,"����:%s\t������:%s\t����ID:%s\t�߳�:%s",s1,s2,s3,s4);
		}
		else
		{
			b1 =(char*)malloc(sizeof(szFile));
			b1 = szFile;
			szFile =(char*)malloc(max);
			sprintf(szFile,"%s\r\n����:%s\t������:%s\t����ID:%s\t�߳�:%s",b1,s1,s2,s3,s4);
		}
		
	}

	
	buffer1 = GlobalAlloc(GMEM_DDESHARE,max+1);
		
	buffer = (char*)GlobalLock(buffer1);
	
	
	
	strcpy(buffer,szFile);
	//���DLL
	GlobalUnlock(buffer1);
	
	//�򿪼��а�
	if(OpenClipboard(NULL))
	{
		//���ü��а�����
		EmptyClipboard();
		SetClipboardData(MY_COPY,buffer1);
		
	}
	CloseClipboard();

}
