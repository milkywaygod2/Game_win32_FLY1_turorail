#pragma once
class CObj;
class CMdl_02AI;

void Evt_createObj(CObj* _pObj, OBJ_TYPE _eObjType);
void Evt_deleteObj(CObj* _pObj, OBJ_TYPE _eObjType);
void Evt_changeScn(SCN_TYPE _eScnType);
void Evt_changeAI_state(CMdl_02AI* _pAI, MTR_STATE _eNextState);


//자주반복되는
template<typename T>
void Freq_clearVec(vector<T>& _eType)
{
	for (size_t i = 0; i < _eType.size(); ++i)
	{
		if (nullptr != _eType[i])
			delete _eType[i]; //배열주소가 가리키는 메모리삭제
	}
	_eType.clear(); //배열 주소뭉치 삭제
}

template<typename T1, typename T2>
void Freq_clearMap(map<T1, T2>& _map)
{
	typename map<T1, T2>::iterator iter = _map.begin();
	
	for (; iter != _map.end(); ++iter)
	{
		if (nullptr != iter->second)
		{
			delete iter->second; //mgr_Rsc쪽 소멸자 실행시, 가상함수로 private실행됨(TXR쪽)
		}
	}
	_map.clear();
}

void fscanfSpace(char* _pOutBuff, FILE* _pFile);
void saveWstring(const wstring& _str, FILE* _pFile); //wstring을 주소에 저장
void loadWstring(wstring& _str, FILE* _pFile); //주소에 있는 wstring을 로드
