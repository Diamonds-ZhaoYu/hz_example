#include "StdAfx.h"
#include "resource.h"
//#include "main.h"
#include "rainmain.h"
#define MAX_LOADSTRING 100
//#pragma comment(lib,"res/SkinMagicLib.lib")
//#pragma comment(lib,"res/DETOURS.lib")
int WINAPI WinMain(HINSTANCE Ihnstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{
	InitSkinMagicLib(Ihnstance, "LSA" , NULL,NULL );//����SkinMagicLib.lib��DETOURS.lib�� 
	//LoadSkinFile("corona.smf");
	LoadSkinFromResource( GetModuleHandle(NULL),"XPBLUE" ,"SKINMAGIC");//���ؾ�̬�Զ���Ƥ����Դ

	DialogBox(Ihnstance,MAKEINTRESOURCE(IDD_RAINMAIN),NULL,RainMain::RainMain_Proc);
	
	ExitSkinMagicLib(); 

	return 0;
}
