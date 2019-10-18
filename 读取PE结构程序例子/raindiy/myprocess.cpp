#include <windows.h>
#include <tlhelp32.h>
#include <COMMCTRL.H>
#include "myprocess.h"
#include "resource.h"
#include <locale.h>   //�ı��ַ���
#include <tlhelp32.h> 
#include <Psapi.h> //�оٽ�����ϢҪ������ͷ�ļ�
#pragma	comment	(lib, "psapi.lib")  
//////////////////////////////////////////////////////////////////////////
/////////�о�windows����
//////////////////////////////////////////////////////////////////////////
VOID EnumMyProcess(HWND hwnd,int type)
{
 int i = 0;
 BOOL bRet; 
 HANDLE hProcessSnap;
 unsigned long ProcessID = -1;
 PROCESSENTRY32 pe;
 ////----------------------------
 LVITEM lv1,lv2;


 lv1.iSubItem = 0;
 lv1.mask = LVCF_FMT | LVCF_TEXT | LVCF_IMAGE ; //  |
 
 
//---------------------------

 pe.dwSize = sizeof(pe);
 hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

 bRet = Process32First(hProcessSnap, &pe);
 
 while(bRet)
 { 
	 TCHAR Pid[125] = {0},PrentPid[125] = {0},Size[125] = {0};
	 lv1.iItem = i;
	 //���ý�������
	 lv1.pszText = pe.szExeFile;
	  lv1.cchTextMax = strlen(pe.szExeFile) + 1;
	  if(type == 1)
	  {
		 SendMessage(GetDlgItem(hwnd,IDC_LIST3),LVM_INSERTITEM,0,(LPARAM)&lv1);
		 itoa(pe.th32ParentProcessID,PrentPid,10); //������
		 itoa(pe.th32ProcessID,Pid,10);  //����ID
		 itoa(pe.cntThreads,Size,10);
		 
		 ListView_SetItemText(GetDlgItem(hwnd,IDC_LIST3),i,1,PrentPid);
		 ListView_SetItemText(GetDlgItem(hwnd,IDC_LIST3),i,2,Pid);
		 ListView_SetItemText(GetDlgItem(hwnd,IDC_LIST3),i,3,Size);
 	  }
	  else if(type == 2)
	  {
		  
	
		 itoa(pe.th32ParentProcessID,PrentPid,10); //������
		 itoa(pe.th32ProcessID,Pid,10);  //����ID
		 itoa(pe.cntThreads,Size,10);
	
		// ListView_SetItemText(GetDlgItem(hwnd,IDC_LIST3),i,1,PrentPid);
		// ListView_SetItemText(GetDlgItem(hwnd,IDC_LIST3),i,2,Pid);
		 ListView_SetItemText(GetDlgItem(hwnd,IDC_LIST3),i,3,Size);
		 
	  }
	

	 

	
	 //SendMessage(GetDlgItem(hwnd,IDC_LIST3),LVM_INSERTITEM,0,(LPARAM)&lv2);
	 //ListView_InsertItem(GetDlgItem(hwnd,IDC_LIST3),&lv2);
     //ListView_SetItem(GetDlgItem(hwnd,IDC_LIST3),&lv2);
	 //ListView_SetItem()
	

   bRet = Process32Next(hProcessSnap, &pe);
	i++;
 }
 CloseHandle(hProcessSnap);
}

//////////////////////////////////////////////////////////////////////////
////�ж�DLL�Ƿ����
//////////////////////////////////////////////////////////////////////////
int IsDLLInfo(HWND hWnd,char *szDll)
{
	TCHAR szFile[MAX_PATH] = {0};
	HWND list = GetDlgItem(hWnd,IDC_LIST3);
	int count = ListView_GetItemCount(list);
	for (int i= 0;i < count;i++)
	{
		ZeroMemory(szFile,sizeof(szFile));
		ListView_GetItemText(list,i,0,szFile,sizeof(szFile));
		if(strcmp(szDll,szFile) == 0)
		{
			return i;
		}
	}
	return -1;
}
//////////////////////////////////////////////////////////////////////////
////��ӽ���
//////////////////////////////////////////////////////////////////////////
VOID EnumMyProcessAdd(HWND hwnd)
{
 int i = 0;
 BOOL bRet; 
 HANDLE hProcessSnap;
 unsigned long ProcessID = -1;
 PROCESSENTRY32 pe;
 ////----------------------------
 LVITEM lv1,lv2;


 lv1.iSubItem = 0;
 lv1.mask = LVCF_FMT | LVCF_TEXT | LVCF_IMAGE ; //  |
 
//---------------------------

 pe.dwSize = sizeof(pe);
 hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

 bRet = Process32First(hProcessSnap, &pe);
 
 while(bRet)
 { 
	 TCHAR Pid[125] = {0},PrentPid[125] = {0},Size[125] = {0};
	
		
		if(IsDLLInfo(hwnd,pe.szExeFile) == -1)
		{
		 lv1.iItem = i;
		 //���ý�������
		 lv1.pszText = pe.szExeFile;
		 lv1.cchTextMax = strlen(pe.szExeFile) + 1;
		 SendMessage(GetDlgItem(hwnd,IDC_LIST3),LVM_INSERTITEM,0,(LPARAM)&lv1);
		 itoa(pe.th32ParentProcessID,PrentPid,10); //������
		 itoa(pe.th32ProcessID,Pid,10);  //����ID
		 itoa(pe.cntThreads,Size,10);
		// MessageBox(NULL,pe.szExeFile,pe.szExeFile,MB_OK);
		 ListView_SetItemText(GetDlgItem(hwnd,IDC_LIST3),i,1,PrentPid);
		 ListView_SetItemText(GetDlgItem(hwnd,IDC_LIST3),i,2,Pid);
		 ListView_SetItemText(GetDlgItem(hwnd,IDC_LIST3),i,3,Size);
		}
		

   bRet = Process32Next(hProcessSnap, &pe);
	i++;
 }
 CloseHandle(hProcessSnap);
}

BOOL EnumMyProcessCmp(HWND hwnd,char *file)
{
 BOOL bRet; 
 HANDLE hProcessSnap;
 unsigned long ProcessID = -1;
 PROCESSENTRY32 pe;

 pe.dwSize = sizeof(pe);
 hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

   bRet = Process32First(hProcessSnap, &pe);
 
	 while(bRet)
	 { 
    	 //���ý�������
		 if(strcmp(file,pe.szExeFile) == 0)
		 {
			return TRUE;
		 }		 
	

		  bRet = Process32Next(hProcessSnap, &pe);
	}
		
 CloseHandle(hProcessSnap);
 return FALSE;
}

VOID EnumMyProcessSub(HWND hWnd)
{
	TCHAR szFile[MAX_PATH] = {0};
	HWND list = GetDlgItem(hWnd,IDC_LIST3);
	int count = ListView_GetItemCount(list);
	for (int i= 0;i < count;i++)
	{
		ZeroMemory(szFile,sizeof(szFile));
		ListView_GetItemText(list,i,0,szFile,sizeof(szFile));
		if(EnumMyProcessCmp(hWnd,szFile) == FALSE)
		{
			//MessageBox(NULL,szFile,szFile,MB_OK);
			ListView_DeleteItem(list,i);
		}
	}
}

VOID ListAddOrSub(HWND hwnd)
{
	TCHAR num[MAX_PATH] = {0};
	EnumMyProcessAdd(hwnd); //�����̼����о����
	EnumMyProcessSub(hwnd); //�鿴�����ж�û�оͼ�ȥ
	
	int number = ListView_GetItemCount(GetDlgItem(hwnd,IDC_LIST3));
	
	itoa(number,num,10);

	SendMessage(GetDlgItem(hwnd,IDC_NUM),WM_SETTEXT,sizeof(num),(LPARAM)num);
}
//////////////////////////////////////////////////////////////////////////
////���DLL
//////////////////////////////////////////////////////////////////////////
VOID ListProcessModules1(DWORD dwPID,HWND hwnd)
{
	HMODULE hMods[1024];
	HANDLE hProcess;
	DWORD cbNeeded;
	unsigned int i;

	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE,dwPID);
	if(NULL==hProcess)return ;

	//����EnumProcessModules
	if(EnumProcessModules(hProcess,hMods,sizeof(hMods),&cbNeeded))
	{
		for(i=1;i<(cbNeeded/sizeof(HMODULE));i++)
		{
			TCHAR szModName[MAX_PATH];
			if(GetModuleFileNameEx(hProcess,hMods[i],szModName,sizeof(szModName)/sizeof(TCHAR)))
			{
				SendMessage(GetDlgItem(hwnd,IDC_LIST2),LB_ADDSTRING,0,(LPARAM)szModName);
			}
		}
	}
	CloseHandle(hProcess);
}

/************ DBG��Ȩ *****************/
BOOL BDebugProcess2(HANDLE hProcess, LPCTSTR PrivilegeName)
{
HANDLE hToken; 
   TOKEN_PRIVILEGES tkp; 

 
   if (!OpenProcessToken(hProcess, 
        TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
      return( FALSE ); 
 
  
 
   LookupPrivilegeValue(NULL,PrivilegeName, 
        &tkp.Privileges[0].Luid); 
 
   tkp.PrivilegeCount = 1;  // one privilege to set    
   tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
 

 
   AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, 
        (PTOKEN_PRIVILEGES)NULL, 0); 


	if(GetLastError()!=ERROR_SUCCESS)
	{
		MessageBox(NULL,"�������Ȩ��ȫ���ɹ�","�ɹ�",MB_OK);
		return FALSE;
	} 
	
	return TRUE;
}



//////////////////////////////////////////////////////////////////////////
//////����ȫ��ģ��
//////////////////////////////////////////////////////////////////////////
VOID GetProMoudle(HWND hwnd)
{
	//LVITEM lv1;
	int i;
	TCHAR szFile[125] = {0};
	HWND hwnd1 = GetDlgItem(hwnd,IDC_LIST3);
	//SendMessage(hwnd1,LVM_GETITEM,0,(LPARAM)&lv1);
	
	ListView_GetItemText(hwnd1,ListView_GetSelectionMark(hwnd1),2,szFile,sizeof(szFile)+1);
	//ListView_GetItemText(hwnd1,lv1.iItem,2,szFile,sizeof(szFile)+1);
	//ListView_GetEditControl

	for (i = SendMessage(GetDlgItem(hwnd,IDC_LIST2),LB_GETCOUNT,0,0);i >= 0;i--)
	{
		SendMessage(GetDlgItem(hwnd,IDC_LIST2),LB_DELETESTRING,i,0);
	}
	
	//����ģ��
	ListProcessModules1(atoi(szFile),hwnd);			
}

//////////////////////////////////////////////////////////////////////////
///DBUG��Ȩ
//////////////////////////////////////////////////////////////////////////
BOOL EnableDebugPriv(const char * name)
{
    HANDLE hToken;
    TOKEN_PRIVILEGES tp;
    LUID luid;
	tp.PrivilegeCount = 1;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    tp.Privileges[0].Luid = luid;
    if(!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, &hToken)) return FALSE;
    //��ý��̱���ΨһID
    if(!LookupPrivilegeValue(NULL, name, &luid)) return FALSE;
    
    //��������Ȩ��
    if(!AdjustTokenPrivileges(hToken, 0, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL)) return FALSE;
    
    return TRUE;
}

DWORD GetProcessPid(char *szProcName) {     
	DWORD retPid = -1;  
	BOOL hMore;
	HANDLE hProcSnap;
	PROCESSENTRY32 pe32;   //������ſ��ս�����Ϣ��һ���ṹ��;     
	pe32.dwSize = sizeof(pe32);   //���ô�С;     
	//�������н��̵Ŀ���;     
	hProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);     
	if(hProcSnap == INVALID_HANDLE_VALUE)     
	{         
	
		return -1;     
	}     //�������̿��գ���ý�����Ϣ;     
	hMore = Process32First(hProcSnap, &pe32);     
	while(hMore)     
	{            
		if(strcmp(pe32.szExeFile, szProcName)==0)             
		{                 
			retPid = pe32.th32ProcessID;                 
			break;             
		}         
		hMore = Process32Next(hProcSnap,&pe32) ;  //����¸�������Ϣ;     
	}     
	if(retPid == -1) NULL;          
	CloseHandle(hProcSnap);     
	return retPid; 
} 
//////////////////////////////////////////////////////////////////////////
////////����DLL
//////////////////////////////////////////////////////////////////////////
BOOL DllInject(WCHAR* szDllName,DWORD dwRemoteProcessId) 
{     
	void *pszLibFileRemote = NULL;        
	HANDLE hRemoteThread;   
	HANDLE hRemoteProcess;
	PTHREAD_START_ROUTINE pfnStartAddr;
	int cbdll;
    EnableDebugPriv(SE_DEBUG_NAME);
	hRemoteProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwRemoteProcessId);  //��Զ�̽���;     
	//����dll·�����ַ�������Ҫ���ڴ�ռ�;     
	cbdll = sizeof(WCHAR) * lstrlenW(szDllName) + 1;     //ʹ��virtualallocEx ������Զ�̽��̵ĵ�ַ�ռ����dll�ļ���������;     
	pszLibFileRemote = (TCHAR *)VirtualAllocEx( hRemoteProcess, NULL, cbdll, MEM_COMMIT, PAGE_READWRITE);     
	if( WriteProcessMemory(hRemoteProcess,pszLibFileRemote,(PVOID)szDllName, cbdll, NULL)==FALSE)     
	{         
	     
		return FALSE;     
	}     
	//����LoadLibraryW����ڵ�ַ;     
	pfnStartAddr = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(TEXT("Kernel32.dll")), "LoadLibraryW");     
	hRemoteThread = CreateRemoteThread( hRemoteProcess, NULL, 0,pfnStartAddr, pszLibFileRemote, 0, NULL);     
	if(hRemoteThread == NULL)         
	{               
		return FALSE;         
	}     
	WaitForSingleObject(hRemoteThread,INFINITE);  //�ȴ��߳̽���     
	VirtualFreeEx(hRemoteProcess,pszLibFileRemote, 0 ,MEM_RELEASE);  //�ͷ�����Ŀռ�     
	CloseHandle(hRemoteThread);  //�رվ��     
	CloseHandle(hRemoteProcess);     
	return TRUE; 
}   

/**  �����߳� **/
DWORD WINAPI ThreadProc2( LPVOID lpParameter)
{
	BOOL fal;
	TCHAR szFile[125] = {0},szPath[MAX_PATH] = {0};
	WCHAR *szName; 
	HWND hwnd = (HWND)lpParameter;
	HWND hwnd1 = GetDlgItem(hwnd,IDC_LIST3);	
		
	
	ListView_GetItemText(hwnd1,ListView_GetSelectionMark(hwnd1),2,szFile,sizeof(szFile)+1);
	
	GetDlgItemTextA(hwnd,IDC_FILEPATH,szPath,sizeof(szPath));
	szName = (WCHAR*)malloc(MAX_PATH * 2 +1);
	
	setlocale(LC_ALL,"chs");
	mbstowcs(szName,szPath,sizeof(szPath));
///	mbsrtowcs(szName,szPath,sizeof(szPath));
	fal = DllInject(szName,atoi(szFile));
	setlocale(LC_ALL,"C");
	if(fal)
	{
		MessageBox(NULL,"ע��ɹ�","��ʾ",MB_OK);
		SendMessage(GetDlgItem(hwnd,IDC_LIST2),LB_ADDSTRING,0,(LPARAM)szPath);
	}
	else
	{
		MessageBox(NULL,"ʧ��","��ʾ",MB_OK);
	}

	return 0;
}
//////////////////////////////////////////////////////////////////////////
//////����DLL����
//////////////////////////////////////////////////////////////////////////
VOID InDll(HWND hwnd)
{
	DWORD dwThreadId;

	CreateThread(NULL,0,ThreadProc2,(LPVOID)hwnd,0,&dwThreadId);
}
//////////////////////////////////////////////////////////////////////////
////Զ��ж��DLL
//////////////////////////////////////////////////////////////////////////
BOOL UnloadDll(DWORD dwPid, char *strDllName)
{
	LPVOID lpBuf; 
	LPVOID pFun;
	DWORD     dwSize = 0;
	DWORD     dwWritten = 0;
	DWORD     dwHandle = 0; 
    HANDLE hThread;
	HANDLE hProcess;
	 EnableDebugPriv(SE_DEBUG_NAME);
	//��ȡ�������̵ľ����ע���Ǽ�����������Ȼ�����
	hProcess = OpenProcess(PROCESS_CREATE_THREAD|PROCESS_VM_OPERATION|PROCESS_VM_WRITE,
				FALSE, dwPid);
	if(hProcess == NULL)
	{
		MessageBox(NULL, "�޷���ȡ���̾��", "����", MB_OK | MB_ICONERROR);
		return FALSE;
	}


	dwSize = strlen(strDllName)+ 1;//dll��ȫ·�����ĳ��ȣ���������ڴ�Ҫ�õ���

	//���������̷����ڴ棬����һ��ָ��
	lpBuf = VirtualAllocEx(hProcess, NULL, dwSize, MEM_COMMIT, PAGE_READWRITE);

	//������������̿ռ�дʧ�ܾ�ֱ�ӱ�������
	if( !WriteProcessMemory(hProcess, lpBuf, (LPVOID)strDllName, dwSize, &dwWritten)){   
		VirtualFreeEx(hProcess, lpBuf, dwSize, MEM_DECOMMIT);
		CloseHandle(hProcess);
		MessageBox(NULL, "��Ŀ�������д��ʧ��", "����", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	//��ȡGetModuleHandleA������ַ
	pFun = GetProcAddress(GetModuleHandle("Kernel32"), "GetModuleHandleA");

	//�����������д���һ��Զ���̣߳��̺߳���Ϊ���浼����GetModuleHandleA������ΪlpBufָ�룬��
	//�ǵ����ǻ�ȡ��dllȫ·����
	hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pFun,
										lpBuf, 0, NULL);
	//��������߳�ʧ�ܣ�ֱ�ӱ����˳�
	if(hThread == NULL){
	CloseHandle(hProcess);
	MessageBox(NULL, "��Ŀ����̴���Զ���߳�ʧ��", "����", MB_OK | MB_ICONERROR);
		  return FALSE;
	}

	//     �ȴ�GetModuleHandle�������   
	WaitForSingleObject(hThread, INFINITE); 
	//     ���GetModuleHandle�ķ���ֵ   
	GetExitCodeThread(hThread, &dwHandle);

	//     �ͷ�Ŀ�����������Ŀռ�   
	VirtualFreeEx(hProcess, lpBuf, dwSize, MEM_DECOMMIT);
	CloseHandle(hThread);

	//     ʹĿ����̵���FreeLibraryAndExit��ж��DLL,ʵ��Ҳ������FreeLibrary�������ҷ���ǰ�ߺ�һ��
	pFun = GetProcAddress(GetModuleHandle("Kernel32"), "FreeLibraryAndExitThread");
	hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pFun,
							 (LPVOID)dwHandle, 0, NULL);   
	// �ȴ�FreeLibraryAndExitThreadִ�����   
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	CloseHandle(hProcess);

	return TRUE;    //�����ɹ�
}
