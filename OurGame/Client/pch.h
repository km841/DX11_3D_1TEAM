#pragma once
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include "EnginePch.h"
#include "Engine.h"
#include "ClientEnum.h"

#pragma comment(lib, "Engine.lib")
using namespace hm;
#define IDS_APP_TITLE			103
#define IDR_MAINFRAME			128
#define IDD_CLIENT_DIALOG	102
#define IDM_EXIT				105
#define IDI_CLIENT			107
#define IDI_SMALL				108
#define IDC_CLIENT			109
#define IDC_STATIC                      -1


static Vec3 ConvertDir(DirectionEvasion _dir)
{

	Vec3 forwardDir = Vec3(0, 0, 1);
	Vec3 BackwardDir = Vec3(0, 0, -1);
	Vec3 LeftwardDir = Vec3(-1, 0, 0);
	Vec3 RightwardDir = Vec3(1, 0, 0);

	Vec3 totalDir = {};

	if (_dir == DirectionEvasion::FORWARD)
	{
		totalDir = forwardDir;
	}
	if (_dir == DirectionEvasion::BACKWARD)
	{
		totalDir = BackwardDir;
	}
	if (_dir == DirectionEvasion::LEFT)
	{
		totalDir = LeftwardDir;
	}
	if (_dir == DirectionEvasion::RIGHT)
	{
		totalDir = RightwardDir;
	}
	if (_dir == DirectionEvasion::TOPLEFT)
	{
		totalDir = (forwardDir + LeftwardDir) ;
	}
	if (_dir == DirectionEvasion::TOPRIGHT) 
	{
		totalDir = (forwardDir + RightwardDir);
	}
	if (_dir == DirectionEvasion::BOTTOMLEFT)
	{
		totalDir = (BackwardDir + LeftwardDir);
	}
	if (_dir == DirectionEvasion::BOTTOMRIGHT)
	{
		totalDir = (BackwardDir + RightwardDir);
	}
	return totalDir;
}