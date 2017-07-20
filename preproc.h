#pragma region Active Preprocessor Block

// disable the warnings generated via _CRT_SECURE_NO_DEPRECATE
#ifndef _DEPRECATION_DISABLE 

#define _DEPRECATION_DISABLE   

#if (_MSC_VER >= 1400)         
#pragma warning(disable: 4996) 
#endif 

#endif 

/* Active Preprocessor Block endregion */

#pragma endregion

#pragma region Extended ASCII

/* ASCII codes for the special characters used in building the map and so */

#define WALL       (char)219
#define	FENCE	   (char)216
#define GRASS	   (char)191
#define	SNOW       (char)178
#define MOBS	   (char)-98
#define WATER	   (char)-80
#define	BRIDGE	   (char)-16
#define GOAL       (char)33      
#define WHITESPACE (char)32
#define PLAYER	   (char)64

/*Extended ASCII endregion */
#pragma endregion

#pragma region Libraries
// necessary for Windows API
#include <Windows.h>		
#include <iostream>	
#include <fstream>
#include <vector>			
#include <string>
#include <ctime>
#include <cmath>
#include <map>

/* Libraries endregion */

#pragma endregion 

#pragma region Controls
/* Determinates whether a key is up or down at the time the function is called */

#define UP    (GetAsyncKeyState(VK_UP)&0x8000)		
#define LEFT  (GetAsyncKeyState(VK_LEFT)&0x8000)		
#define DOWN  (GetAsyncKeyState(VK_DOWN)&0x8000)		
#define RIGHT (GetAsyncKeyState(VK_RIGHT)&0x8000)		
#define SPACE (GetAsyncKeyState(VK_SPACE)&0x8000)

/* Controls endregion */
#pragma endregion 

#pragma region Console

#define	CLEAR_SCREEN system("cls");		
#define PAUSE        system("pause > nul");

#pragma endregion

#pragma region Sounds

#pragma comment(lib, "Winmm.lib" )  // add the Winmm.lib to the build

/* You'll have to add those wav files to the resources so it would work*/
// plays button-48.wav
#define BEEP_POINT	 PlaySound(MAKEINTRESOURCE(IDR_WAVE1),GetModuleHandle(0),SND_RESOURCE|SND_ASYNC);	
// plays beep-03.wav
#define BEEP_ENEMY   PlaySound(MAKEINTRESOURCE(IDR_WAVE2),GetModuleHandle(0),SND_RESOURCE|SND_ASYNC);   // plays beep-03.wav

/* Sounds endregion */
#pragma endregion

#pragma region Map

#define MapHW tempMap[h][w]
#define pX	  crtPosX
#define pY    crtPosY 

/* Map endregion */

#pragma endregion






