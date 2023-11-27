#pragma once
//Pre Compiled Header 미리 컴파일된 헤더, 프로젝트 속성에서 활성화해야
//중앙집권 헤더

#include "windows.h"
#include "resource.h"					//윈도우 프로시져용
#pragma comment(lib, "Msimg32.lib")		//TransparentBlt

#include <iostream>						//std::cout<<"아무말"
#include <vector>
using std::vector;

#include <list>
using std::list;

#include <string>
using std::string;
using std::wstring;

#include <map>
using std::map;
using std::make_pair;
using std::iterator;

#include <wchar.h>
#include <math.h>
#include <assert.h>

// sound 용도 - 헤더 순서 중요
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

#include "define.h"						//1-1
#include "struct.h"						//1-2
#include "func.h"						//1-3

#include "CCore.h"						//2

	#include "mgr_Key.h"				//3-1
	#include "mgr_Timer.h"				//3-2
	#include "mgr_Scn.h"				//3-3
	#include "mgr_Path.h"				//3-4
	#include "mgr_Rsc.h"				//3-5
	#include "mgr_Clls.h"				//3-6
	#include "mgr_Evt.h"				//3-7
	#include "mgr_Cam.h"				//3-8
	#include "mgr_UI.h"					//3-9
	#include "mgr_Snd.h"				//3-10

#include "CObj.h"						//4
	//#include "CObj_00DFT.h"			//4-0
	#include "CObj_01PLR.h"				//4-1
	#include "CObj_02MTR.h"				//4-2
	#include "CObj_03MSL.h"				//4-3
	#include "CObj_04TL.h"				//4-4
	#include "CObj_05UI.h"				//4-5
		#include "UI_Panel.h"			//4-5-1
		#include "UI_Btn.h"				//4-5-2
	#include "CObj_06GRD.h"				//4-6

#include "CScn.h"						//5
	#include "CScn_00TL.h"				//5-0
	#include "CScn_01STT.h"				//5-1
	//#include "CScn_02STG_1.h"			//5-2
	//#include "CScn_03STG_2.h"			//5-3

#include "CRsc.h"						//6
	#include "CRsc_01TXR.h"				//6-1
	#include "CRsc_02SND.h"				//6-2

	#include "CCmp_01Cldr.h"			//7-1
	#include "CCmp_02Amtr.h"			//7-2
	#include "CCmp_02Amtrn.h"			//7-3
	#include "CCmp_03RgdB.h"			//7-4
	#include "CCmp_04Grbt.h"			//7-5

	#include "CMdl_01SltGDI.h"			//8-1
	#include "CMdl_02AI.h"				//8-2
		#include "AI_state.h"			//8-2-1
			#include "AI_stateIdle.h"	//8-2-1-1
			#include "AI_stateAttack.h"	//8-2-1-2
			#include "AI_stateDead.h"	//8-2-1-3
			#include "AI_stateTrace.h"	//8-2-1-4

	#include "FactoryMTR.h"				//9-1


