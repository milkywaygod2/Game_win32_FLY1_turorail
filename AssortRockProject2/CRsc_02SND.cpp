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
		assert(nullptr); // 사운드 객체 생성되지 않음

	// 확장자 이름 구별하기
	wchar_t szExt[10] = { 0 };
	_wsplitpath_s(_strPath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 10);

	if (!wcscmp(szExt, L".wav")) // WAV 파일 로드
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
	hFile = mmioOpen((wchar_t*)strFilePath.c_str(), NULL, MMIO_READ);//wave파일을 연다.

	if (nullptr == hFile)
	{
		MessageBox(NULL, L"사운드 리소스 경로에 파일 없음", L"사운드 로딩 실패", MB_OK);
		return false;
	}

	//Chunk 청크 구조체, 문자열로 색인을 인식해서 WaveFormat 및 버퍼선언정보를 읽어온다.
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
		MessageBox(NULL, L"사운드버퍼생성실패", L"", MB_OK);
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

	// 초기 음량 절반으로 설정
	setSoundVolume(50.f);

	return true;
}


void CRsc_02SND::playSound(bool _bLoop)
{
	// Play 함수의 1번째 2번째 인자는 0 으로 이미 예약되어있다.
	// 3번째 변수는 사운드를 반복재생 할 것인지 아닌지를 결정한다.
	m_pDsoundBuff->SetCurrentPosition(0);

	if (_bLoop)
		m_pDsoundBuff->Play(0, 0, DSBPLAY_LOOPING);
	else
		m_pDsoundBuff->Play(0, 0, 0);
}

void CRsc_02SND::playSoundBGM(bool _bLoop)
{
	mgr_Snd::GetInst()->setSoundBGM(this);

	// Play 함수의 1번째 2번째 인자는 0 으로 이미 예약되어있다.
	// 3번째 변수는 사운드를 반복재생 할 것인지 아닌지를 결정한다.
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

void CRsc_02SND::setSoundPercent(float _fPosition) //재생바
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

	// 1 ~ 100 사이값을 데시벨 단위로 변경
	int iVolume = (LONG)(-2000.0 * log10(100.f / _fVolume));

	if (iVolume < -10000)
		iVolume = -10000;
	return  iVolume;
}
