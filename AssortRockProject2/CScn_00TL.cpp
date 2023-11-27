#include "pch.h"
#include "CScn_00TL.h"

#include "resource.h" //������ ���ν�����
void CStest(DWORD_PTR, DWORD_PTR);

CScn_00TL::CScn_00TL(){}
CScn_00TL::~CScn_00TL(){}

void CScn_00TL::setTileIdx()
{
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vCursorPos = CURSOR_POS;
		vCursorPos = mgr_Cam::GetInst()->getRealPos(vCursorPos);

		//Ÿ����ġŽ��(�ε���Ȯ��)
		int	iCol = (int)vCursorPos.x / TILE_SIZE;
		int	iRow = (int)vCursorPos.y / TILE_SIZE;
		int iTileX = (int)getTileX();
		int iTileY = (int)getTileY();
		if (vCursorPos.x < 0.f || vCursorPos.y < 0.f
			|| iCol >= iTileX || iRow >= iTileY)
		{ return; }

		UINT iIdx = iRow * iTileX + iCol;

		const vector<CObj*>& vecTile = Scn_getObjGroup(OBJ_TYPE::TL);
		((CObj_04TL*)vecTile[iIdx])->addTileIdx();
	}	
}
void CScn_00TL::saveTileData()
{
	wchar_t szName[256] = {};
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->getMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = mgr_Path::GetInst()->getCttPath();
	strTileFolder += L"tile";

	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	//Modal���
	if (GetSaveFileName(&ofn))
	{
		saveTile(szName);
	}
}
void CScn_00TL::saveTile(const wstring& _strFilePath)
{
	//Ŀ�� ������Ʈ
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _strFilePath.c_str(),L"wb");
	assert(pFile);

	//Ÿ�� ���μ��� ��������
	UINT xCount = getTileX();
	UINT yCount = getTileY();

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);

	const vector<CObj*>& vecTile = Scn_getObjGroup(OBJ_TYPE::TL);

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CObj_04TL*)vecTile[i])->save(pFile);
	}

	fclose(pFile);
}
void CScn_00TL::loadTileData()
{
	wchar_t szName[256] = {};
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->getMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = mgr_Path::GetInst()->getCttPath();
	strTileFolder += L"tile";

	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	//Modal���
	if (GetOpenFileName(&ofn))
	{
		wstring strRltvPath = mgr_Path::GetInst()->getRltvPath(szName);
		loadTile(strRltvPath);
	}
}
void CScn_00TL::Enter()
{
	Vec2 vResolution = CCore::GetInst()->getResolution();

	//�޴����̱�
	CCore::GetInst()->CCore_attachMenu();

	//�ʱ� Ÿ�� ����
	Scn_createTile(5, 5);
	
	//UI 1�� ������
	CObj_05UI* pUI_Panel = new UI_Panel;
	pUI_Panel->Obj_setName(L"ParentUI");
	pUI_Panel->Obj_setScale(Vec2(300.f, 120.f));
	pUI_Panel->Obj_setPos(Vec2(vResolution.x - pUI_Panel->Obj_getScale().x, 0.f));

	UI_Btn* pUI_Btn = new UI_Btn;
	pUI_Btn->Obj_setName(L"ChildUI");
	pUI_Btn->Obj_setScale(Vec2(80.f, 30.f));
	pUI_Btn->Obj_setPos(Vec2(0.f,0.f));
	((UI_Btn*)pUI_Btn)->setBtnCallBack(this,(SCN_FUNC)&CScn_00TL::saveTileData);

	pUI_Panel->addChild(pUI_Btn);
	Scn_addObj(pUI_Panel, OBJ_TYPE::UI);

	//Ŭ�� UI
	CObj_05UI* pClonePanel = pUI_Panel->clone();
	pClonePanel->Obj_setPos(pClonePanel->Obj_getPos() + Vec2(-300.f, 0.f));
	((UI_Btn*)pClonePanel->getChildUI()[0])->setBtnCallBack(CStest, 0, 0);
	Scn_addObj(pClonePanel, OBJ_TYPE::UI);

	m_pUI = pClonePanel;

	//ī�޶� ����
	mgr_Cam::GetInst()->setPsyLookat(vResolution / 2.f);

	mgr_Cam::GetInst()->fadein(2.f);
}

void CScn_00TL::update()
{
	CScn::update();

	setTileIdx();

	if (KEY_TAP(KEY::ENTER))
	{
		Evt_changeScn(SCN_TYPE::STT);
	}

	if (KEY_TAP(KEY::P))
	{
		//mgr_UI::GetInst()->setFocusedUI(m_pUI);
		saveTileData();
	}
	if (KEY_TAP(KEY::L))
	{
		loadTileData();
	}

}

void CScn_00TL::Exit()
{
	CCore::GetInst()->CCore_detachMenu();
	Scn_clearAll();
}






//----------
void CStest(DWORD_PTR, DWORD_PTR) { Evt_changeScn(SCN_TYPE::STT); }



//=========================
//TILE_COUNT ������ ���ν���
//=========================,������/�۾����Ǽ��� ���� CScn_00TL.cpp�� ��ġ

INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			UINT iXcount = GetDlgItemInt(hDlg, IDC_EDIT_TILE_COUNTX, nullptr, false);
			UINT iYcount = GetDlgItemInt(hDlg, IDC_EDIT_TILE_COUNTY, nullptr, false);
			CScn* pCurScn = mgr_Scn::GetInst()->getCurScn();

			//CScn_00TLȮ��
			CScn_00TL* pIsToolScn = dynamic_cast<CScn_00TL*>(pCurScn); //�����ٿ� ĳ����, �����ϸ� nullptr��ȯ
			assert(pIsToolScn);

			//������ ����
			pIsToolScn->Scn_clearObj(OBJ_TYPE::TL);
			pIsToolScn->Scn_createTile(iXcount,iYcount);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}return (INT_PTR)FALSE;
}