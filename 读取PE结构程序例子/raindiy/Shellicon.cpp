// Shellicon.cpp: implementation of the Shellicon class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Shellicon.h"
#include "resource.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Shellicon::Shellicon()
{

}

Shellicon::~Shellicon()
{

}
//////////////////////////////////////////////////////////////////////////
///����Ҽ�Сͼ��
//////////////////////////////////////////////////////////////////////////
VOID Shellicon::CreateShellIcon(int id,HWND hWnd,LPSTR namem,int msg)
{

	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);// �ṹ�ĳ��ȣ��á�λ��������λ��
	nid.hWnd = hWnd;	//��Ϣ���͵Ĵ��ھ��
	nid.uID = id;//�ڹ����ж����ͼ��ID
	nid.uFlags = NIF_ICON | NIF_MESSAGE|NIF_TIP ;
	nid.uCallbackMessage = msg;//�Զ������Ϣ����
	nid.hIcon=LoadIcon((HINSTANCE)GetWindowLong(hWnd,GWL_HINSTANCE),MAKEINTRESOURCE(id));
	strcpy(nid.szTip,namem);
	
	Shell_NotifyIcon(NIM_ADD,&nid);
}
//////////////////////////////////////////////////////////////////////////
///ɾ���Ҽ�Сͼ��
//////////////////////////////////////////////////////////////////////////
VOID Shellicon::DelShellIcon(int id,HWND hWnd,LPSTR namem,int msg)
{

	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);// �ṹ�ĳ��ȣ��á�λ��������λ��
	nid.hWnd = hWnd;	//��Ϣ���͵Ĵ��ھ��
	nid.uID = id;//�ڹ����ж����ͼ��ID
	nid.uFlags = NIF_ICON | NIF_MESSAGE|NIF_TIP;
	nid.uCallbackMessage = msg;//�Զ������Ϣ����
	nid.hIcon=LoadIcon((HINSTANCE)GetWindowLong(hWnd,GWL_HINSTANCE),MAKEINTRESOURCE(id));
	strcpy(nid.szTip,namem);

	Shell_NotifyIcon(NIM_DELETE,&nid);
}





