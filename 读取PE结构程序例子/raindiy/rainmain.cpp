#include "StdAfx.h"
#include "rainmain.h"
#include "resource.h"
#include "DerverLoad.h"
#include "main.h"
#include "Shellicon.h"

#include "RainSSDT.h"
#include "RainStatus.h"
#include "RainPe.h"
#include "MyProcess1.h"

#include <commctrl.h>

HMENU      hMenu;
MyProcess  mypro;

VOID OnShowTask(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	if(IDI_ICON1 != wParam)
	{
		return;
	}	
	switch(lParam)
	{
		case WM_RBUTTONUP:  //�Ҽ���Ӳ˵�
		{
			TCHAR sF[125] = {0};

			itoa(wParam,sF,10);
			
				LPPOINT lpoint=new tagPOINT;  
                GetCursorPos(lpoint);//������λ��

				HMENU hMenu;
				HMENU pop;
				TCHAR szF[125] = {0};
		
				if((hMenu = LoadMenu((HINSTANCE)GetWindowLong(hWnd,GWL_HINSTANCE),MAKEINTRESOURCE(IDR_MENU1))) == NULL)
				{
					return;
				}
				if(IDI_ICON1 == wParam)
				{
					pop = GetSubMenu(hMenu,2);
					
					TrackPopupMenu(pop,TPM_NONOTIFY |TPM_LEFTALIGN | TPM_RIGHTBUTTON,lpoint->x ,lpoint->y,0,hWnd,NULL);
				
				}
			
				DestroyMenu(hMenu); //�ͷŲ˵�
				
				delete lpoint;

		}
		break;
		case WM_LBUTTONDBLCLK:  //˫��
		{
			
			if(IsWindowVisible(hWnd))
			{
				ShowWindow(hWnd,SW_HIDE);
			}
			else
			{
				ShowWindow(hWnd,SW_SHOW);
			}			
		}
		break;
	}
	
}



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//������
//////////////////////////////////////////////////////////////////////////
BOOL WINAPI RainMain::RainMain_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
		{
    		case WM_INITDIALOG:
					//���غ���
				return InitDiaLog(hWnd,uMsg,wParam,lParam);
   			case WM_COMMAND:
				{	
					CommandMg(LOWORD(wParam),hWnd,wParam,lParam);
				}
   				break;
			case WM_SHOWTASK:
				{
					OnShowTask(hWnd,wParam,lParam);
				}
				break;
			case WM_CLOSE:
				{
					Shellicon shell;
					shell.DelShellIcon(IDI_ICON1,hWnd,"ByRain����",WM_SHOWTASK);
					PostQuitMessage(0);		
				}
				break;
			case WM_GETTEXT:
				{
					if(LOWORD(wParam) == IDC_MYDRIVER)
					{
						MessageBox(NULL,"","",MB_OK);
					}
				}
				break;
		

		}

	return FALSE;	
}

BOOL RainMain::InitDiaLog(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//-----����Ƥ��
	SetWindowSkin( hWnd, "Dialog" ); 
	SetDialogSkin( "Dialog" );
	SetWindowSkin( hWnd, "Dialog" ); 
	//-----------------------
	SendMessage(hWnd,WM_SETICON,IDI_ICON1,0);
	
	//������С��ͼ��
	Shellicon shell;
	shell.CreateShellIcon(IDI_ICON1,hWnd,"ByRain����",WM_SHOWTASK);

	//����Ӱ��������
	DWORD dwExStyle = GetWindowLong(hWnd, GWL_EXSTYLE);
    dwExStyle = WS_EX_TOOLWINDOW;
    SetWindowLong(hWnd, GWL_EXSTYLE, dwExStyle);

	ShowWindow(hWnd,SW_HIDE);

	
	//SendMessage(GetDlgItem(hWnd,IDC_PROGRESS1),PBM_SETPOS,(WPARAM)1,0);

	RECT rect;
	GetWindowRect(hWnd,&rect);
	SetWindowPos(hWnd,NULL,rect.left,rect.top,(rect.right - rect.left),420,SWP_SHOWWINDOW);

	mypro.AddDriverInfo(GetDlgItem(hWnd,IDC_MYDRIVER));	

	return TRUE;
}

/**  �����߳� **/
DWORD WINAPI ThreadProcReadFile( LPVOID lpParameter)
{
	HWND hwnd = (HWND)lpParameter;
	TCHAR path[MAX_PATH] = {0};
	//IDC_DEZHEN
	//IDC_SERC_STR
	GetDlgItemText(hwnd,IDC_MYDRIVER,path,MAX_PATH);
	mypro.findFile(path,GetDlgItem(hwnd,IDC_SERC_STR));
	
	EnableWindow(GetDlgItem(hwnd,IDOK),TRUE);
	EnableWindow(GetDlgItem(hwnd,IDC_MYDRIVER),TRUE);
	return NULL;
}

void GetLocalTimes(HWND hwnd)
{
	SYSTEMTIME sys; 
	GetLocalTime(&sys);
	TCHAR t[255];
	
	wsprintf(t,TEXT("%d-%02d-%02d  %02d:%02d:%02d"),sys.wYear,
	sys.wMonth,
	sys.wDay,
	sys.wHour,
	sys.wMinute,
	sys.wSecond);
	
} 



void RainMain::CommandMg(int id,HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	Shellicon shell;
	switch(id)
	{
		case ID_MENUPROCESS:  //����	
			{
				DialogBox((HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE),MAKEINTRESOURCE(IDD_DOMAIN),hwnd,Main_Proc);
			}
			break;
		case ID_MENULOADSYS:  //��������
			{
				DialogBox((HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE),MAKEINTRESOURCE(IDD_LODSYS),hwnd,DerverLoad::RainSysMain_Proc);
			}
		break;
		case ID_MENU_RAIN_CLOSE:  //ͼ���Ҽ�С�˵�����ر�
			{

				shell.DelShellIcon(IDI_ICON1,hwnd,"ByRain����",WM_SHOWTASK);
				PostQuitMessage(0);
			}
			break;
		case ID_MENUITEM40017:  //�鿴SSDT����״̬
			{
				DialogBox((HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE),MAKEINTRESOURCE(IDD_SSDT_MAIN),hwnd,RainSSDT::RainMain_Proc);
			}
		break;
		case ID_MENUITEM40016:   //�ں�״̬�鿴
			{
				DialogBox((HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE),MAKEINTRESOURCE(IDD_SYS_STATUS),hwnd,RainStatus::RainStatusMain_Proc);
			}
			break;
		case ID_MENUITEM40014:
			{
				DialogBox((HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE),MAKEINTRESOURCE(IDD_DOMIAN_PE),hwnd,RainPe::RainMain_Proc);
			}
			break;
		case IDOK:
			{
				//IDC_PROGRESS1
				//SendMessage(
				//SendMessage(GetDlgItem(hwnd,IDC_PROGRESS1),PBM_SETSTEP,50,0);
				
				//SendMessage(GetDlgItem(hwnd,IDC_PROGRESS1),PBM_STEPIT,0,0);
				EnableWindow(GetDlgItem(hwnd,IDOK),FALSE);
				EnableWindow(GetDlgItem(hwnd,IDC_MYDRIVER),FALSE);
				DWORD dwThreadId;
				
				SendMessage(GetDlgItem(hwnd,IDC_PROGRESS1),PBM_SETRANGE,0,MAKELPARAM(0,14137));

				CreateThread(NULL,0,ThreadProcReadFile,(LPVOID)hwnd,0,&dwThreadId);

			}
			break; //IDC_D_STRING
		case IDC_MYDRIVER:
			{
				switch(HIWORD(wParam))

				{

					case CBN_SELCHANGE:  //ѡ����Ϣ 
					{
						TCHAR szD[125] = {0};
						GetDlgItemText(hwnd,IDC_MYDRIVER,szD,125);
						if(szD)
						{
							mypro.SetDeiverTextInfo(GetDlgItem(hwnd,IDC_D_STRING),szD);
						}
					}
					break;
				}

			}
			break;

		case IDC_BUTTON1:
			{
				//POINT point;
				TCHAR szName[MAX_PATH] = {0};
				RECT rect;
				GetWindowRect(hwnd,&rect);
				//GetCursorPos()
				GetDlgItemText(hwnd,IDC_BUTTON1,szName,MAX_PATH);
				if(strcmp(szName,"��") == 0)
				{
					SetDlgItemText(hwnd,IDC_BUTTON1,"�ر�");
					SetWindowPos(hwnd,NULL,rect.left,rect.top,(rect.right - rect.left),700,SWP_SHOWWINDOW);
				}
				else
				{
					SetDlgItemText(hwnd,IDC_BUTTON1,"��");
					SetWindowPos(hwnd,NULL,rect.left,rect.top,(rect.right - rect.left),420,SWP_SHOWWINDOW);
				}
				
			}
			break;
	}
}