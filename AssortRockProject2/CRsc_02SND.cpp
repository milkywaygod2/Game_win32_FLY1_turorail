#include "pch.h"
#include "CRsc_02SND.h"

CRsc_02SND::CRsc_02SND()
	: m_pDsoundBuff(nullptr)
	, m_tDsoundBuffInfo{}
	, m_iDsoundVolume(0)
{
}

CRsc_02SND::~CRsc_02SND()
{
	if (nullptr != m_pDsoundBuff)
		m_pDsoundBuff->Release();
}

int CRsc_02SND::loadSound(const wstring& _strPath)
{
	if (nullptr == mgr_Snd::GetInst()->getSoundMain())
		assert(nullptr); // ���� ��ü �������� ����

	// Ȯ���� �̸� �����ϱ�
	wchar_t szExt[10] = { 0 };
	_wsplitpath_s(_strPath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 10);

	if (!wcscmp(szExt, L".wav")) // WAV ���� �ε�
	{
		if (false == loadSound_wav(_strPath))
			assert(nullptr);
	}
	else
		assert(nullptr);

	return S_OK;
}

bool CRsc_02SND::loadSound_wav(const wstring& _strPath)
{
	HMMIO	hFile; // File Handle

	wstring strFilePath = _strPath;

	//CreateFile
	hFile = mmioOpen((wchar_t*)strFilePath.c_str(), NULL, MMIO_READ);//wave������ ����.

	if (nullptr == hFile)
	{
		MessageBox(NULL, L"���� ���ҽ� ��ο� ���� ����", L"���� �ε� ����", MB_OK);
		return false;
	}

	//Chunk ûũ ����ü, ���ڿ��� ������ �ν��ؼ� WaveFormat �� ���ۼ��������� �о�´�.
	MMCKINFO	pParent;
	memset(&pParent, 0, sizeof(pParent));
	pParent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmioDescend(hFile, &pParent, NULL, MMIO_FINDRIFF);

	MMCKINFO	pChild;
	memset(&pChild, 0, sizeof(pChild));
	pChild.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmioDescend(hFile, &pChild, &pParent, MMIO_FINDCHUNK);

	WAVEFORMATEX	wft;
	memset(&wft, 0, sizeof(wft));
	mmioRead(hFile, (char*)&wft, sizeof(wft));

	mmioAscend(hFile, &pChild, 0);
	pChild.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmioDescend(hFile, &pChild, &pParent, MMIO_FINDCHUNK);



	memset(&m_tDsoundBuffInfo, 0, sizeof(DSBUFFERDESC));
	m_tDsoundBuffInfo.dwBufferBytes = pChild.cksize;
	m_tDsoundBuffInfo.dwSize = sizeof(DSBUFFERDESC);
	m_tDsoundBuffInfo.dwFlags = DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE | DSBCAPS_CTRLVOLUME;
	m_tDsoundBuffInfo.lpwfxFormat = &wft;

	if (FAILED(mgr_Snd::GetInst()->getSoundMain()->CreateSoundBuffer(&m_tDsoundBuffInfo, &m_pDsoundBuff, NULL)))
	{
		MessageBox(NULL, L"������ۻ�������", L"", MB_OK);
		return false;
	}

	void* pWrite1 = NULL;
	void* pWrite2 = NULL;
	DWORD dwlength1, dwlength2;

	m_pDsoundBuff->Lock(0, pChild.cksize, &pWrite1, &dwlength1
		, &pWrite2, &dwlength2, 0L);

	if (pWrite1 != nullptr)
		mmioRead(hFile, (char*)pWrite1, dwlength1);
	if (pWrite2 != nullptr)
		mmioRead(hFile, (char*)pWrite2, dwlength2);

	m_pDsoundBuff->Unlock(pWrite1, dwlength1, pWrite2, dwlength2);

	mmioClose(hFile, 0);

	// �ʱ� ���� �������� ����
	setSoundVolume(50.f);

	return true;
}


void CRsc_02SND::playSound(bool _bLoop)
{
	// Play �Լ��� 1��° 2��° ���ڴ� 0 ���� �̹� ����Ǿ��ִ�.
	// 3��° ������ ���带 �ݺ���� �� ������ �ƴ����� �����Ѵ�.
	m_pDsoundBuff->SetCurrentPosition(0);

	if (_bLoop)
		m_pDsoundBuff->Play(0, 0, DSBPLAY_LOOPING);
	else
		m_pDsoundBuff->Play(0, 0, 0);
}

void CRsc_02SND::playSoundBGM(bool _bLoop)
{
	mgr_Snd::GetInst()->setSoundBGM(this);

	// Play �Լ��� 1��° 2��° ���ڴ� 0 ���� �̹� ����Ǿ��ִ�.
	// 3��° ������ ���带 �ݺ���� �� ������ �ƴ����� �����Ѵ�.
	if (_bLoop)
		m_pDsoundBuff->Play(0, 0, DSBPLAY_LOOPING);
	else
		m_pDsoundBuff->Play(0, 0, 0);
}

void CRsc_02SND::stopSound(bool _bReset)
{
	m_pDsoundBuff->Stop();

	if (_bReset)
		m_pDsoundBuff->SetCurrentPosition(0);
}


void CRsc_02SND::setSoundVolume(float _fVolume)
{
	m_iDsoundVolume = getSoundDecibel(_fVolume);
	m_pDsoundBuff->SetVolume(m_iDsoundVolume);
}

void CRsc_02SND::setSoundPercent(float _fPosition) //�����
{
	stopSound(true);

	DWORD dwBytes = (DWORD)((_fPosition / 100.f) * (float)m_tDsoundBuffInfo.dwBufferBytes);
	m_pDsoundBuff->SetCurrentPosition(dwBytes);

	playSound();
}

int CRsc_02SND::getSoundDecibel(float _fVolume)
{
	if (_fVolume > 100.f)
		_fVolume = 100.f;
	else if (_fVolume <= 0.f)
		_fVolume = 0.00001f;

	// 1 ~ 100 ���̰��� ���ú� ������ ����
	int iVolume = (LONG)(-2000.0 * log10(100.f / _fVolume));

	if (iVolume < -10000)
		iVolume = -10000;
	return  iVolume;
}
