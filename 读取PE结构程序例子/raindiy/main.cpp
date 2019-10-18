#include <windows.h>
#include <COMMCTRL.H>
#include "main.h"
#include "create.h"   //�������ڴ����
#include "resource.h"   
#include "myprocess.h"  //�������
#include "rightmenu.h" //�����Ҽ��˵�
#include "OpenMyFile.h"

HINSTANCE hInst;

BOOL WINAPI Main_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    switch(uMsg)
    {
    	case WM_INITDIALOG:
				//���غ���
				return InitDiaLog(hWnd,uMsg,wParam,lParam);
   		case WM_COMMAND:
			{
				//��Ϣ������
   				CommandMg(LOWORD(wParam),hWnd,wParam,lParam);
		    }
   			break;
		case WM_CLOSE:
			{
				//�رմ���
				CloseMg(hWnd,uMsg,wParam,lParam);
			}
			break;
		case WM_LBUTTONDBLCLK:
			{
				//MessageBox(NULL,"","",MB_OK);
			}
			break;
		case WM_CONTEXTMENU:  //����Ҽ��˵�
			{
				ListBoxAddMenu(hWnd,hInst,wParam,lParam);	
			
				//MessageBox(NULL,"","",MB_OK);
			}
			break;
		case WM_SYSCOMMAND:
			{
				//CommandMg(LOWORD(wParam),hWnd,wParam,lParam);

			
			//	MessageBox(NULL,"SSS","SSS",MB_OK);
		
			}
			break;
		case WM_NOTIFY: //������listview
			{
				CommandMgLive(((LPNMHDR)lParam)->code,hWnd,wParam,lParam);
			}
			break;
	
    }

	return FALSE;
}

/**  �����߳� **/
DWORD WINAPI ThreadProc( LPVOID lpParameter)
{

	HWND hwnd = (HWND)lpParameter;
	
	while(1)
	{

		//ListView_DeleteAllItems(GetDlgItem(hwnd,IDC_LIST3));
		EnumMyProcess(hwnd,2);
	
		Sleep(3000);
	}
	return 0;
}
/**  �����߳� **/
DWORD WINAPI ThreadProc1( LPVOID lpParameter)
{

	HWND hwnd = (HWND)lpParameter;
	
	while(1)
	{
		ListAddOrSub(hwnd);
		Sleep(3000);
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////
///////���غ���
//////////////////////////////////////////////////////////////////////////
BOOL InitDiaLog(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
		HICON incon;
		DWORD dwThreadId,dwThreadId1;
		HWND list1 = GetDlgItem(hWnd,IDC_LIST2);
		
		//��ô�����Ϣ
		hInst = (HINSTANCE) GetWindowLong(hWnd, GWL_HINSTANCE);			
	
		//ListView_InsertColumn(list,0,&lvc);
		
		//ListView_SubItemHitTest(list,lp);
		CreateMyListView(hWnd);
		EnumMyProcess(hWnd,1);
		CreateThread(NULL,0,ThreadProc,(LPVOID)hWnd,0,&dwThreadId);
		CreateThread(NULL,0,ThreadProc1,(LPVOID)hWnd,0,&dwThreadId);
		
	 //ע���ȼ� 
		  //  RegisterHotKey(hWnd,100,/**MOD_ALT*/ NULL,VK_HOME ); //VK_HOME 
		
    		/* Set app icons 
		
		   	SendMessage(list1,LB_ADDSTRING,1,(LPARAM)"����1");
		SendMessage(list1,LB_ADDSTRING,0,(LPARAM)"����");
		*/
		    //hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICONAPP));
		    //SendMessage(hWnd, WM_SETICON, TRUE,  (LPARAM)hIcon);
		    //SendMessage(hWnd, WM_SETICON, FALSE, (LPARAM)hIcon);
		 
			/*
		    * Add initializing code here
		    */
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
///////��Ϣ������
//////////////////////////////////////////////////////////////////////////
void CommandMg(int id,HWND hwnd, WPARAM wParam, LPARAM lParam)
{

	switch(id)
	{
		
	case IDC_LOAD:
		{
		
			
			//MessageBox(NULL,"","",MB_OK);
			OpenMyFile open;
			open.lpMystrFilter = TEXT("dll���ӿ�\0*.dll\0\0");
			open.lpMystrTitle = TEXT("��DLL");
			open.OpenFileDlls(hwnd,hInst,IDC_FILEPATH);  //�򿪳���
		}
		break;
	case IDC_ZHURU:
		{
		
			InDll(hwnd);
		}
		break;
	case ID_MENU_DLL:  //����˵�
		{
			//ж��
			CallUndll(hwnd);
		}
		break;
    case ID_MENU_COPY:  //����һ��
		{
			CallCopyRow(hwnd);
		}
		break;
	case ID_MENUALLCOPY: //����ȫ��
		{
			CallCopyAllRow(hwnd);
		}
		break;
	case ID_MENU_1:  //����
		{
			CallCopyById(hwnd,0);
		}
		break;
	case ID_MENU_2: //���Ƹ�����
		{
			CallCopyById(hwnd,1);
		}
		break;
	case ID_MENU_3: //���ƽ�����
		{
			CallCopyById(hwnd,2);
		}
		break;	
	case ID_MENU_4: //����ÿ��
		{
			CallCopyByRow(hwnd);
		}
		break;
	case ID_MENU_5: //����ȫ��
		{
			CallCopyByAllRow(hwnd);
		}
		break;
	case ID_MENU_6: //��������
		{
		
			TCHAR szFile[125] = {0},szPath[MAX_PATH] = {0};
			


			HWND hwnd1 = GetDlgItem(hwnd,IDC_LIST3);
			int num = ListView_GetSelectionMark(hwnd1);
			if(num == -1)
			{
				MessageBox(NULL,"��ѡ����Ҫ�����Ķ���!","��ʾ",MB_OK);

				return;
			}

			ListView_GetItemText(hwnd1,num,2,szFile,sizeof(szFile)+1);
	
			if(MessageBox(NULL,"ȷ��Ҫ�����ý���ô��","��ʾ",MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				//ExitProcess(atoi(szFile));
				
				HANDLE hAndle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, atoi(szFile));
				TerminateProcess(hAndle,0);
				CloseHandle(hAndle);				

				
			}

			

		}
	break;
	default:
		
			break;
	}
}


//////////////////////////////////////////////////////////////////////////
///////��Ϣ������
//////////////////////////////////////////////////////////////////////////
void CommandMgLive(int id,HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	switch(id)
	{
	case NM_DBLCLK:
		{
			switch(LOWORD(wParam))
			{
				case IDC_LIST3:  //���listview
					{
						GetProMoudle(hwnd);
					}
					break;
			}
			
		}			
		break;
		
	default:
		
			break;
	}
}





void CloseMg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//PostQuitMessage(0);
	EndDialog(hWnd,0);
}