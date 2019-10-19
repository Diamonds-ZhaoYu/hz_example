#include "stdafx.h"
#include "Resource.h"
#include "main.h"


HINSTANCE hInst;

struct ParamFunc
{
	HWND parentHwnd;
	HWND qqHwnd;
};

/**
*  �ı䴰��
*/
DWORD WINAPI FuncProc( LPVOID lpParameter)
{
    struct ParamFunc *lps;
	TCHAR  szText[1024],Tz[1024];

	
	lps = (struct ParamFunc *)lpParameter;
	
	HWND pHwnd = lps->parentHwnd;
	
	HWND qq = lps->qqHwnd;
	
	RECT rect;
	
	GetWindowRect(qq,&rect);
	
	SetForegroundWindow(qq);
	SetCursorPos(rect.left+90,rect.top+57);
	Sleep(10);
	mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
	mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
	Sleep(10);
	
    SetCursorPos(rect.left+90+752,rect.top+57+445);	
	Sleep(100);
	SetForegroundWindow(qq);
	Sleep(100);
	mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
	mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
		
	return NULL;	
}

/**
*  
*   LPVOID lpParameter ������� 
*/ 
DWORD WINAPI ThreadProc( LPVOID lpParameter)
{
	struct ParamFunc *lps;
	TCHAR  szText[1024],Tz[1024];
	int i;
	
	lps = (struct ParamFunc *)lpParameter;
	
	HWND pHwnd = lps->parentHwnd;
	HWND qq = lps->qqHwnd;
	HWND q1 = GetWindow(qq,GW_HWNDNEXT); 
	
	//������� 
	SendDlgItemMessage(pHwnd,IDC_MSGTEXT,WM_GETTEXT,sizeof(szText),(LPARAM)szText);
	
	
	//ģ�����뷢����Ϣ
	while(1)
	{
		Sleep(1000);
		
		SendMessage(qq,WM_SYSCOMMAND,SC_KEYMENU,(WPARAM)0x4c);

		for(i = 0;i < strlen(szText);i++)
		{
				//1 & 0 = 0  1 & 1=1R
			SendMessage(qq, WM_CHAR, szText[i]& 0xFF , NULL);
		}
	
		SendMessage(qq, WM_KEYDOWN, VK_RETURN , NULL);
		SendMessage(qq, WM_CHAR, VK_RETURN , NULL);
		SendMessage(qq, WM_KEYUP, VK_RETURN , NULL);
		
	}
	
	return NULL;
}



HWND getqq;
DWORD dwThreadId; 
HANDLE hThread;
HANDLE hThread1;
BOOL WINAPI Main_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
	int id;
	HICON hIcon;

   
    switch(uMsg)
    {
    	case WM_INITDIALOG:
		{       
			//ע���ȼ� 
			RegisterHotKey(hWnd,100,/**MOD_ALT*/ NULL,VK_HOME ); //VK_HOME 
			hInst = (HINSTANCE) GetWindowLong(hWnd, GWL_HINSTANCE);
    		/* Set app icons */
			hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICONAPP));
			SendMessage(hWnd, WM_SETICON, TRUE,  (LPARAM)hIcon);
			SendMessage(hWnd, WM_SETICON, FALSE, (LPARAM)hIcon);
		}
		    return TRUE;
		case WM_HOTKEY:		//hotkeyȫ����Ϣ�����¼�
		{
			TCHAR szTitle[1024];
			//��ȡ��ȡ���ö��������ƣ��ı䱾��������
			getqq	= GetForegroundWindow();
			SendMessage(getqq,WM_GETTEXT,sizeof(szTitle),(LPARAM)szTitle);
			SendMessage(hWnd,WM_SETTEXT,0,(LPARAM)szTitle);
		}
			break; 
   		case WM_COMMAND:	//����ؼ���Ϣ
   			id = LOWORD(wParam);
   			switch( id )
		    {
		        case IDC_OK:		//��ʼ������Ϣ
		         {
					 struct ParamFunc lp;
					 lp.parentHwnd = hWnd;
					 lp.qqHwnd = getqq;
					 hThread = CreateThread(NULL,0,ThreadProc,(LPVOID)&lp,0,&dwThreadId);
				 } 
		        break;
		        case IDC_STOP:    //��ͣ������Ϣ
				{
					
					if(hThread)
					{
						 if(hThread)
						 {
	 						TerminateThread(hThread,0);
						    CloseHandle(hThread);	
	 					 }
					  	 if(hThread1)
						 {
	 						TerminateThread(hThread1,0);
						    CloseHandle(hThread1);	
	 					 }

					}
					
				
				}
				break; 
				case IDC_CLICK:		//�ı䴰��
				{
				     struct ParamFunc lp;
			         lp.parentHwnd = hWnd;
	                 lp.qqHwnd = getqq;
					 hThread1 = CreateThread(NULL,0,FuncProc,(LPVOID)&lp,0,&dwThreadId);	
				}
				break;
				case IDC_CANCEL:	//�ر�Ӧ��
		          
		            EndDialog(hWnd, id);
		        break;
		        default:
					break;
		    }
   			break;
		case WM_CLOSE:		//�رմ�����Ϣ
		    ExitThread(0);
			//�ر��ȼ� 
			UnregisterHotKey(hWnd,100);
			EndDialog(hWnd, 0);
			break;
    }

    return FALSE;
}

