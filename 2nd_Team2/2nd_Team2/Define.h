#pragma once

#define		WINCX		1024
#define		WINCY		768

#define		PI			3.141592f
#define		RADIAN		PI / 180.f

#define		PURE		= 0

#define		VK_MAX		 0xff

#define		OBJ_NOEVENT	0	
#define		OBJ_DEAD	1
#define		PlayerSize  100

#define		TIMESCALE	0.1f
#define		TICKSCALE	TIMESCALE * 0.1f

#define		BOSS_APPEAR_COUNT 15
#define		ENERMY_PER_SECOND 0.7f

extern HWND			g_hWnd;

extern DWORD g_dwCurrentTime;
extern DWORD g_dwDeltaTime;