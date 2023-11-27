#pragma once
class CObj;
class CMdl_02AI;

void Evt_createObj(CObj* _pObj, OBJ_TYPE _eObjType);
void Evt_deleteObj(CObj* _pObj, OBJ_TYPE _eObjType);
void Evt_changeScn(SCN_TYPE _eScnType);
void Evt_changeAI_state(CMdl_02AI* _pAI, MTR_STATE _eNextState);


//���ֹݺ��Ǵ�
template<typename T>
void Freq_clearVec(vector<T>& _eType)
{
	for (size_t i = 0; i < _eType.size(); ++i)
	{
		if (nullptr != _eType[i])
			delete _eType[i]; //�迭�ּҰ� ����Ű�� �޸𸮻���
	}
	_eType.clear(); //�迭 �ּҹ�ġ ����
}

template<typename T1, typename T2>
void Freq_clearMap(map<T1, T2>& _map)
{
	typename map<T1, T2>::iterator iter = _map.begin();
	
	for (; iter != _map.end(); ++iter)
	{
		if (nullptr != iter->second)
		{
			delete iter->second; //mgr_Rsc�� �Ҹ��� �����, �����Լ��� private�����(TXR��)
		}
	}
	_map.clear();
}

void fscanfSpace(char* _pOutBuff, FILE* _pFile);
void saveWstring(const wstring& _str, FILE* _pFile); //wstring�� �ּҿ� ����
void loadWstring(wstring& _str, FILE* _pFile); //�ּҿ� �ִ� wstring�� �ε�
