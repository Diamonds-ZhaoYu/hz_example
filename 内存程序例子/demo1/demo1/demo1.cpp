// demo1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"   
#include <windows.h> 
#include <conio.h>

//�������ַ
#define SUNNY_NUMBER_ADDR	0x006A9EC0

//��һ���ַ
#define MONEY_NUMBER_ADDR	0x006A9EC0

/**
* �޸����ⷽ��
*/
void change_sunny_number(HANDLE hProcess)
{
	DWORD sunny; 
	
	DWORD baseAddr = SUNNY_NUMBER_ADDR;
	DWORD stackAddr;
	DWORD dataAdrr;

	////�����ַ��ȡ������ַ
	ReadProcessMemory (hProcess,(void *)baseAddr,&stackAddr,4,0);      	
	printf("\nһ��ƫ�ƻ���ַ�� 0x%x\n",stackAddr);

	//�����ַ + һ��ƫ�� = һ����ַ
	stackAddr = stackAddr + 0x768 ;
	printf("\nһ������ַ�� 0x%x\n",stackAddr);

	//������ƫ�ƻ���ַ
	ReadProcessMemory(hProcess,(void *)stackAddr,&dataAdrr,4,0);		
	printf("\nһ��ƫ�ƻ���ַ�� 0x%x\n",dataAdrr);

	//����ƫ�� + ����ƫ�� = �����ַ
	dataAdrr = dataAdrr + 0x5560 ;
	printf("\n��������ַ�� 0x%x\n",dataAdrr);

	//д������
	printf("\n����Ҫ�������⣿��");
	scanf_s("%d",&sunny);
	DWORD res = WriteProcessMemory(hProcess, (void *)dataAdrr, &sunny, 4, 0);	

	if ( res == NULL )
	{
		printf("\n�޸�ʧ��\n");
	}
	else
	{
		printf("\n�޸ĳɹ�\n");	
	}
	
}

/**
*  �޸Ľ��
*/
void change_money_number(HANDLE hProcess)
{
	DWORD money;
	DWORD baseAddr =  MONEY_NUMBER_ADDR,stackAddr,dataAdrr;
	
	//��һ�ַ��ȡ����ַ
	ReadProcessMemory (hProcess,(void *)baseAddr,&stackAddr,4,0);


	//һ��ƫ��82C��ַ��ȡ����ƫ�ƻ���ַ
	stackAddr = stackAddr + 0x82C ;
	ReadProcessMemory(hProcess,(void *)stackAddr,&dataAdrr,4,0); 



	//д�����ڴ�
	printf("\n����Ҫ���ٽ�ң���");
	scanf_s("%ld",&money); 
	dataAdrr = dataAdrr + 0x28 ; 
	DWORD res = WriteProcessMemory(hProcess,(void *)dataAdrr,&money,4,0); 

	if ( res == NULL )
	{
		printf("\n�޸�ʧ��\n");
	}		
	else
	{
		printf("\n�޸ĳɹ�\n");
	} 

}


int main(void)
{
	
	DWORD Pid;			//����PID
	HANDLE hProcess=0;  //���̾��

	 //��ô��ھ��
	HWND hWnd = ::FindWindow(NULL,TEXT("ֲ���ս��ʬ���İ�"));   
	if( hWnd == NULL )	
	{
		printf("\nδ������Ϸ���� ����������Ϸ\n");
	}
	else if ( hWnd !=  NULL )
	{
		//��ý���pid
		GetWindowThreadProcessId(hWnd,&Pid);									 
		
		//�򿪽��� ��ȡ���в���Ȩ��
		hProcess = OpenProcess(PROCESS_ALL_ACCESS,FALSE,Pid);
		if ( hProcess == NULL )
		{	
			printf("\n����Ϸ����ʧ��\n");
			_getch();
			return -1;
		}
		else
		{
			printf("\n�ɹ�����Ϸ����,���ھ����0x%x,����PID��%d\n",hWnd,Pid);
		}
		
		
		change_sunny_number(hProcess);	//�޸�����

		change_money_number(hProcess);	//�޸Ľ��

    }
	_getch();
	return 0;
}
