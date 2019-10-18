// MyProcess1.cpp: implementation of the MyProcess class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyProcess1.h"
#include <windows.h>
#include <stdio.h>
#include "resource.h"
#include <commctrl.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define BUFSIZE 1024  

MyProcess::MyProcess()
{

}

MyProcess::~MyProcess()
{

}
void MyProcess::AddDriverInfo(HWND list)
{
	/***
	
	TCHAR szLogicalDriveStrings[BUFSIZE];  
	PCHAR szDrive;  
	TCHAR szD[30] = {0};
    ZeroMemory(szLogicalDriveStrings,BUFSIZE);  
	// ��ȡ�߼������������  
    GetLogicalDriveStrings(BUFSIZE - 1,szLogicalDriveStrings);    
    szDrive = (PCHAR)szLogicalDriveStrings;  
    // ѭ������ÿ����  
    do  
    {  
		SendMessage(list,CB_ADDSTRING,0,(LPARAM)szDrive);

		szDrive += (lstrlen(szDrive)+1);  
	}  
    while(*szDrive!='/x00');
	*/  
	char dc = 'A';
	DWORD dw = GetLogicalDrives();
	TCHAR szD[30] = {0};
	
	while(dw != 0)
	 {
		if((dw&1) != 0)
		{
			sprintf(szD,"%c:\\",dc);
			SendMessage(list,CB_ADDSTRING,0,(LPARAM)szD);
		}
		dc++;
		dw >>= 1;
	 }
}

void MyProcess::SetDeiverTextInfo(HWND ltext,LPSTR lpName)
{
	 
	    UINT DType = GetDriveType(lpName);
		unsigned _int64 i64FreeBytesToCaller;
		unsigned _int64 i64TotalBytes;
		unsigned _int64 i64FreeBytes;
		
		TCHAR info[1024]= {0},type[30] = {0};
         //GetDriveType���������Ի�ȡ���������ͣ�����Ϊ�������ĸ�Ŀ¼
        if(DType == DRIVE_FIXED)
        {
			sprintf(type,"Ӳ��");
        }
        else if(DType == DRIVE_CDROM)
        {
			sprintf(type,"����");
        }
        else if(DType == DRIVE_REMOVABLE)
        {
			sprintf(type,"���ƶ�ʽ����");
        }
        else if(DType == DRIVE_REMOTE)
        {
			sprintf(type,"�������");
        }
        else if(DType == DRIVE_RAMDISK)
        {
			sprintf(type,"����RAM����");
        }
        else if (DType == DRIVE_UNKNOWN)
        {
			sprintf(type,"δ֪�豸");
        }
	 
		//GetDiskFreeSpaceEx���������Ի�ȡ���������̵Ŀռ�״̬,�������ص��Ǹ�BOOL��������

		 BOOL fResult = GetDiskFreeSpaceEx (

                               lpName,

                               (PULARGE_INTEGER)&i64FreeBytesToCaller,

                               (PULARGE_INTEGER)&i64TotalBytes,

                               (PULARGE_INTEGER)&i64FreeBytes);

     

        if(fResult)//ͨ�����ص�BOOL�����ж��������Ƿ��ڹ���״̬

        {
			sprintf(info,"�������ͣ�%s\r\t���̴�С��%d MB\r\t��ʹ�ã�%d MB",type,((__int64)i64TotalBytes/1024/1024),((__int64)i64FreeBytesToCaller /1024/1024));
		} 
		else
		{

		}
		SetWindowText(ltext,info);

}

int dir,int sum;

void MyProcess::findFile(char filePath[],HWND lhwnd)//�������Ҫ�ĺ���
{
char szFind[MAX_PATH] = {0};//����Ҫ�ҵ�
WIN32_FIND_DATA FindFileData;
HANDLE hFind;
char szFile[3000]={0};
TCHAR lFile[MAX_PATH] = {0};
TCHAR info[MAX_PATH] = {0};
strcpy(szFind,filePath);
strcat(szFind,"//*.*");//Ӧ��ͨ��������Ŀ¼�µ������ļ�������Ŀ¼

hFind=FindFirstFile(szFind,&FindFileData);
if(INVALID_HANDLE_VALUE == hFind) return;

while(TRUE)
{

	if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)//����Ŀ¼
	{
		if(FindFileData.cFileName[0]!='.')//.��ʾ��ǰĿ¼������ÿ��Ŀ¼���涼������Ĭ��Ŀ¼����..��.�ֱ��ʾ��һ��Ŀ¼�͵�ǰĿ¼
		{
			strcpy(szFile,filePath);
			strcat(szFile,"//");
			strcat(szFile,FindFileData.cFileName);
			findFile(szFile,lhwnd);//Ѱ�����Ŀ¼������ļ�
		}
		dir++;
	}
	else
	{
		fprintf(stdout,"%s//%s/n",filePath,FindFileData.cFileName);//��ӡ��Ŀ¼�µ��ļ���;���ͳƺ�
		sprintf(lFile,"%s//%s",filePath,FindFileData.cFileName);
		SetWindowText(lhwnd,lFile);
		sum++;
	
	}
	SendMessage(GetDlgItem(GetParent(lhwnd),IDC_PROGRESS1),PBM_SETSTEP,1,0);
				
	SendMessage(GetDlgItem(GetParent(lhwnd),IDC_PROGRESS1),PBM_STEPIT,0,0);
	sprintf(info,"�ļ�������%d   �ļ��У�%d    �ļ�: %d ",(dir+sum),dir,sum);
	SetWindowText(GetDlgItem(GetParent(lhwnd),IDC_FILE_SUM),info);

	
if(!FindNextFile(hFind,&FindFileData))//Ѱ����һ���ļ�
{
	break;
}


}
FindClose(hFind);//�رվ��
}
