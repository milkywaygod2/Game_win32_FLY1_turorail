#include "pch.h"
#include "func.h"

void Evt_createObj(CObj* _pObj, OBJ_TYPE _eObjType)
{
	tEvt tEvt = {};
	tEvt.eEvt = EVT_TYPE::CREATE_OBJ;
	tEvt.lParam = (DWORD_PTR)_pObj;
	tEvt.wParam = (DWORD_PTR)_eObjType;

	mgr_Evt::GetInst()->addEvt(tEvt);
}

void Evt_deleteObj(CObj* _pObj, OBJ_TYPE _eObjType)
{
	tEvt tEvt = {};
	tEvt.eEvt = EVT_TYPE::DELETE_OBJ;
	tEvt.lParam = (DWORD_PTR)_pObj;
	tEvt.wParam = (DWORD_PTR)_eObjType;

	mgr_Evt::GetInst()->addEvt(tEvt);
}


void Evt_changeScn(SCN_TYPE _eScnType) //�ٷ� �ٲٸ� ���� �̺�Ʈó��
{
	tEvt tEvt = {};
	tEvt.eEvt = EVT_TYPE::CHANGE_SCN;
	tEvt.lParam = (DWORD_PTR)_eScnType;

	mgr_Evt::GetInst()->addEvt(tEvt);
}

void Evt_changeAI_state(CMdl_02AI* _pAI, MTR_STATE _eNextState)
{
	tEvt tEvt = {};
	tEvt.eEvt = EVT_TYPE::CHANGE_AI_STATE;
	tEvt.lParam = (DWORD_PTR)_pAI;
	tEvt.wParam = (DWORD_PTR)_eNextState;

	mgr_Evt::GetInst()->addEvt(tEvt);
}

void fscanfSpace(char* _pOutBuff, FILE* _pFile)
{
	int i = 0;
	while (true)
	{
		char c = (char)getc(_pFile);
		if (c == '\n') //in C '����', "���ڿ�" ... getc�� ����
		{
			_pOutBuff[i++] = '\0'; 
			break; //null �־� ���� ���� ����
		}
		_pOutBuff[i++] = c;
	}
}

void saveWstring(const wstring& _str, FILE* _pFile)
{
	const wchar_t* pStrName = _str.c_str();
	size_t iLen = _str.length();

	fwrite(&iLen, sizeof(size_t), 1, _pFile); //���ڱ��� ����
	fwrite(pStrName, sizeof(wchar_t), iLen, _pFile); //���ڿ� ����
}

void loadWstring(wstring& _str, FILE* _pFile)
{
	size_t iLen = 0;
	fread(&iLen, sizeof(size_t), 1, _pFile);
	wchar_t szBuff[256] = {};	//���޸𸮷� �ϸ� �ȵǰ� �̷��� �迭���� �������ֱ�
	fread(szBuff, sizeof(wchar_t), iLen, _pFile);

	_str = szBuff;
}

