// OpenMyFile.cpp: implementation of the OpenMyFile class.
//
//////////////////////////////////////////////////////////////////////

#include "OpenMyFile.h"
#include <windows.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

OpenMyFile::OpenMyFile()
{

}

OpenMyFile::~OpenMyFile()
{

}
//////////////////////////////////////////////////////////////////////////
////// ���ļ�
////// hwnd  �û�����
////// hInst ��Ϣ
//////////////////////////////////////////////////////////////////////////
BOOL OpenMyFile::OpenFileDlls(HWND hWnd,HINSTANCE hInst,int id)
{
	OPENFILENAME OpenFileName;
	TCHAR  szFile[MAX_PATH]      = {0};

	DWORD readsize; 


	OpenFileName.lStructSize       = sizeof(OPENFILENAME);
	OpenFileName.hwndOwner         = hWnd;
	OpenFileName.hInstance         = hInst;
	OpenFileName.lpstrFilter       = lpMystrFilter; //TEXT("����\0*.sys\0ȫ������\0*.*\0\0"); //TEXT("dll���ӿ�\0*.dll\0\0")
	OpenFileName.lpstrCustomFilter = NULL;
	OpenFileName.nMaxCustFilter    = 0;
	OpenFileName.nFilterIndex      = 0;
	OpenFileName.lpstrFile         = szFile;
	OpenFileName.nMaxFile          = sizeof(szFile);
	OpenFileName.lpstrFileTitle    = NULL;
	OpenFileName.nMaxFileTitle     = 0;
	OpenFileName.lpstrInitialDir   = NULL; 
	OpenFileName.lpstrTitle        = lpMystrTitle; //TEXT("��DLL")
	OpenFileName.nFileOffset       = 0;
	OpenFileName.nFileExtension    = 0;
	OpenFileName.lpstrDefExt       = NULL;
  
	//OpenFileName.lpTemplateName    = MAKEINTRESOURCE(IDI_ICONAPP);
	OpenFileName.Flags             =  OFN_EXPLORER ; //| OFN_ENABLEHOOK OFN_SHOWHELP | | OFN_ENABLETEMPLATE | OFN_ENABLEHOOK | OFN_SHOWHELP

	// Call the common dialog function.
	if (GetOpenFileName(&OpenFileName))
	{
		//IDC_FILEPATH
		SetDlgItemText(hWnd,id,szFile);
		return TRUE;
	}
	return FALSE;

}
