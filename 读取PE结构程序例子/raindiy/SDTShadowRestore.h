//file:SDTShadowRestore.h

#ifndef SDTSHADOWRESTORE_H

#define SDTSHADOWRESTORE_H

#include <windows.h>
#include <Tchar.h>

typedef struct _SYSTEM_SERVICE_TABLE 
{ 
   PVOID   ServiceTableBase; 
   PULONG   ServiceCounterTableBase; 
   ULONG   NumberOfService; 
   ULONG   ParamTableBase; 
}SYSTEM_SERVICE_TABLE,*PSYSTEM_SERVICE_TABLE;

typedef struct _SERVICE_DESCRIPTOR_TABLE
{
  PVOID KiServiceTabe;
  PVOID W32pServiceTable;
  PVOID Reserved_1;
  PVOID Reserved_2;
}SERVICE_DESCRIPTOR_TABLE,*PSERVICE_DESCRIPTOR_TABLE;


class SDTShadowRestore
{
public:
  SDTShadowRestore(void)
  {
    m_dwWin32kBase = 0;
    m_dwW32pServiceTable = 0;
    m_KeServiceDescriptorTableShadow = 0;
    //this->Init();
  }
  ~SDTShadowRestore(void)
  {
    if(m_pKernelName)
    {
      ::GlobalFree(m_pKernelName);
    }
  }

  void SetListShowSys(HWND hwnd);           //����list��ֵ�����ڻ�ȡ�������ں˶���
private:
  void AnsiToPTSTR(PTSTR DesStr, char *SourceStr, DWORD cbDesStr);
  
private:
  PIMAGE_OPTIONAL_HEADER m_pWin32kOptionalHeader;           //��ѡͷ�ĵ�ַ����RVA
  HMODULE m_hWin32kModule;              //�Լ����ص�Win32k.sys�ں�ģ���ģ����
  LPTSTR m_pKernelName;           //�ں˺���ģ����
  HMODULE m_hKernelModule;            //�ں˺���ģ��ntoskrnl.exe����ntkrnlpa.exe
  DWORD m_dwKernelBase;         //�ں˻�ַ
  DWORD m_dwWin32kBase;         //Win32k.sys��ַ
  PSERVICE_DESCRIPTOR_TABLE m_KeServiceDescriptorTableShadow;         //�ں���SSDT Shadow����ʵ�ڴ��ַ
  DWORD m_dwW32pServiceTable;      //ԭʼW32pServiceTaable����ʵ��ַ
};

#endif   
