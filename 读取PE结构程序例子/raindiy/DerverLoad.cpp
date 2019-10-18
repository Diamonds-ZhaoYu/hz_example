// DerverLoad.cpp: implementation of the DerverLoad class.
//
//////////////////////////////////////////////////////////////////////

#include "DerverLoad.h"
#include <windows.h>
#include "resource.h"
#include "OpenMyFile.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DerverLoad::DerverLoad()
{

}

DerverLoad::~DerverLoad()
{

}
//////////////////////////////////////////////////////////////////////////
////���ڴ�������
//////////////////////////////////////////////////////////////////////////
BOOL CreateSys(HWND hwnd)
{
	
	TCHAR szPath[MAX_PATH] = {0};
	
	GetDlgItemText(hwnd,IDC_SYSFILEPATH,szPath,sizeof(MAX_PATH));
	
	BOOL bRet = FALSE;
	
	SC_HANDLE hServiceMgr=NULL;//SCM�������ľ��
	SC_HANDLE hServiceDDK=NULL;//NT��������ķ�����
	
	//�򿪷�����ƹ�����
	hServiceMgr = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS );
	
	if( hServiceMgr == NULL )  
	{
		//OpenSCManagerʧ��
		MessageBox(NULL,"OpenSCManager() Faild  ! \n","OpenSCManager() Faild %d ! \n",MB_OK);
		bRet = FALSE;

	}
	else
	{
		////OpenSCManager�ɹ�
		bRet = TRUE;

	}
	
	//������������Ӧ�ķ���
	hServiceDDK = CreateService( hServiceMgr,
		"rain", //�����������ע����е�����  
		"rain", // ע������������ DisplayName ֵ  
		SERVICE_ALL_ACCESS, // ������������ķ���Ȩ��  
		SERVICE_KERNEL_DRIVER,// ��ʾ���صķ�������������  
		SERVICE_DEMAND_START, // ע������������ Start ֵ  
		SERVICE_ERROR_IGNORE, // ע������������ ErrorControl ֵ  
		szPath, // ע������������ ImagePath ֵ  
		NULL,  
		NULL,  
		NULL,  
		NULL, NULL);  
	
	DWORD dwRtn;
	//�жϷ����Ƿ�ʧ��
	if( hServiceDDK == NULL )  
	{  
		dwRtn = GetLastError();
		if( dwRtn != ERROR_IO_PENDING && dwRtn != ERROR_SERVICE_EXISTS )  
		{  
			//��������ԭ�򴴽�����ʧ��
			MessageBox(NULL,"����ʧ�� ! \n","��ʾ",MB_OK);
			bRet = FALSE;
		}  
		else  
		{
			//���񴴽�ʧ�ܣ������ڷ����Ѿ�������
			MessageBox(NULL,"�Ѿ������� ! \n","��ʾ",MB_OK);
			bRet = TRUE;
		}
	} 
	else
	{
		bRet = TRUE;
		MessageBox(NULL,"�����ɹ���","��ʾ",MB_OK);
	}

	if(hServiceDDK)
	{
		CloseServiceHandle(hServiceDDK);
	}
	
	if(hServiceMgr>0)
	{
		CloseServiceHandle(hServiceMgr);
	}

	return bRet;
}


VOID Start(HWND hwnd)
{
	SC_HANDLE hService=NULL;//NT��������ķ�����
	BOOL bRet;
	SC_HANDLE hSCM=NULL;//SCM�������ľ��
	TCHAR szPath[MAX_PATH] = {0};
	
	GetDlgItemText(hwnd,IDC_SYSFILEPATH,szPath,sizeof(MAX_PATH));
	
	//�򿪷�����ƹ�����
	hSCM = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS );
	
	//�򿪶�Ӧ�ķ���
	hService = OpenService( hSCM, "rain", SERVICE_ALL_ACCESS );  
	
	
	//�����������
	bRet= StartService( hService, NULL, NULL );  
	if( !bRet )  //�������񲻳ɹ�
	{  
		MessageBox(NULL,"��������Ѿ�����  ! \n","��ʾ\n",MB_OK);
	}
	else
	{
		MessageBox(NULL,"�����ɹ� ! \n","��ʾ",MB_OK);
	}

	if(hService)
	{
		CloseServiceHandle(hService);
	}

	if(hSCM>0)
	{
		CloseServiceHandle(hSCM);
	}
}

BOOL CloseSys( char * szSvrName)
{
	//һ�������õ��ı���
	BOOL bRet = FALSE;
	SC_HANDLE hSCM=NULL;//SCM�������ľ��,�������OpenSCManager�ķ���ֵ
	SC_HANDLE hService=NULL;//NT��������ķ��������������OpenService�ķ���ֵ
	SERVICE_STATUS SvrSta;
	//����SCM������
	hSCM = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS );  
	if( hSCM == NULL )  
	{
		//����SCM������ʧ��
		bRet = FALSE;
		goto BeforeLeave;
	}  
	//������������Ӧ�ķ���
	hService = OpenService( hSCM, szSvrName, SERVICE_ALL_ACCESS );  
	
	if( hService == NULL )  
	{
		bRet = FALSE;
		goto BeforeLeave;
	}  

	//��ֹͣ�����������ֹͣʧ�ܣ�ֻ�������������ܣ��ٶ�̬���ء�  
	if( !ControlService( hService, SERVICE_CONTROL_STOP , &SvrSta ) )  
	{  
		MessageBox(NULL,"ֹͣ����ʧ��!","��ʾ",MB_OK);
	}  
	else  
	{
		//ֹͣ��������ɹ�
		MessageBox(NULL,"ֹͣ����ɹ�!","��ʾ",MB_OK);
	}  
	
	bRet = TRUE;
	//�� �뿪ǰ�رմ򿪵ľ��
BeforeLeave:
	if(hService>0)
	{
		CloseServiceHandle(hService);
	}
	if(hSCM>0)
	{
		CloseServiceHandle(hSCM);
	}
	return bRet;	
}

//ж����������  
BOOL UnLoadSys( char * szSvrName )  
{
	//һ�������õ��ı���
	BOOL bRet = FALSE;
	SC_HANDLE hSCM=NULL;//SCM�������ľ��,�������OpenSCManager�ķ���ֵ
	SC_HANDLE hService=NULL;//NT��������ķ��������������OpenService�ķ���ֵ
	SERVICE_STATUS SvrSta;
	//����SCM������
	hSCM = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS );  
	if( hSCM == NULL )  
	{
		//����SCM������ʧ��
		bRet = FALSE;
		goto BeforeLeave;
	}  
	//������������Ӧ�ķ���
	hService = OpenService( hSCM, szSvrName, SERVICE_ALL_ACCESS );  
	
	if( hService == NULL )  
	{
		bRet = FALSE;
		goto BeforeLeave;
	}  
	else  
	{  
		//TRACE( "OpenService() ok ! \n" );  //����������Ӧ�ķ��� �ɹ�
	}  
	//��ֹͣ�����������ֹͣʧ�ܣ�ֻ�������������ܣ��ٶ�̬���ء�  
	if( !ControlService( hService, SERVICE_CONTROL_STOP , &SvrSta ) )  
	{  
	
	}  
 
	//�嶯̬ж����������  
	if( !DeleteService( hService ) )  //TRUE//FALSE
	{
		//ж��ʧ��
		MessageBox(NULL,"ж�ط���ʧ��!","��ʾ",MB_OK);
	}  
	else  
	{  
		//ж�سɹ�
		MessageBox(NULL,"ж�ط���ɹ�!","��ʾ",MB_OK);
		
	}  
	bRet = TRUE;
	//�� �뿪ǰ�رմ򿪵ľ��
BeforeLeave:
	if(hService>0)
	{
		CloseServiceHandle(hService);
	}
	if(hSCM>0)
	{
		CloseServiceHandle(hSCM);
	}
	return bRet;	
} 


BOOL WINAPI DerverLoad::RainSysMain_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
		{
    		case WM_INITDIALOG:
					//���غ���
		
				return TRUE;
   			case WM_COMMAND:
				{	
					CommandMg(LOWORD(wParam),hWnd,wParam,lParam);
				}
   				break;
			case WM_CLOSE:
				{
					EndDialog(hWnd,0);
				}
				break;
		}

	return FALSE;	
}
void DerverLoad::CommandMg(int id,HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	switch(id)
	{
		case IDC_SYS_BLOAD:
			{
				OpenMyFile open;
				open.lpMystrFilter = TEXT("SYS����\0*.sys\0\0");
				open.lpMystrTitle = TEXT("������");
				BOOL fal = open.OpenFileDlls(hwnd,(HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE),IDC_SYSFILEPATH);  //�򿪳���	
				
				if(fal)
				{
					EnableWindow(GetDlgItem(hwnd,ID_SYS_LOAD),1);
				}
			
			
			}
			break;
		case ID_SYS_LOAD:
			{
				BOOL fal = CreateSys(hwnd);
				if(fal)
				{
					EnableWindow(GetDlgItem(hwnd,ID_SYS_LOAD),0);
					EnableWindow(GetDlgItem(hwnd,IDC_SYS_START),1);
					EnableWindow(GetDlgItem(hwnd,IDC_SYS_CLOSE),0);
					EnableWindow(GetDlgItem(hwnd,ID_SYS_UNLOAD),1);
				
				}
			}
			break;
		case IDC_SYS_START:
			{
				Start(hwnd);
				EnableWindow(GetDlgItem(hwnd,ID_SYS_LOAD),0);
				EnableWindow(GetDlgItem(hwnd,IDC_SYS_START),0);
				EnableWindow(GetDlgItem(hwnd,IDC_SYS_CLOSE),1);
				EnableWindow(GetDlgItem(hwnd,ID_SYS_UNLOAD),1);
			}
			break;
		case IDC_SYS_CLOSE:   //�رշ���
			{
				CloseSys("rain");
				EnableWindow(GetDlgItem(hwnd,ID_SYS_LOAD),1);
				EnableWindow(GetDlgItem(hwnd,IDC_SYS_START),1);
				EnableWindow(GetDlgItem(hwnd,IDC_SYS_CLOSE),0);
				EnableWindow(GetDlgItem(hwnd,ID_SYS_UNLOAD),1);
			}
			break;
		case ID_SYS_UNLOAD:
			{
				UnLoadSys("rain");
				EnableWindow(GetDlgItem(hwnd,ID_SYS_LOAD),0);
				EnableWindow(GetDlgItem(hwnd,IDC_SYS_START),0);
				EnableWindow(GetDlgItem(hwnd,IDC_SYS_CLOSE),0);
				EnableWindow(GetDlgItem(hwnd,ID_SYS_UNLOAD),0);
			}
			break;
	}
}