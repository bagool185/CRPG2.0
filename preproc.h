#pragma region Active Preprocessor Block

#ifndef _DEPRECATION_DISABLE 			// disable the warnings generated via _CRT_SECURE_NO_DEPRECATE

#define _DEPRECATION_DISABLE   

#if (_MSC_VER >= 1400)         
#pragma warning(disable: 4996) 
#endif 

#endif 

/* Active Preprocessor Block endregion */

#pragma endregion

#pragma region Extended ASCII

/* ASCII codes for the special characters used in building the map and so */

#define WALL       219
#define	FENCE	   216
#define GRASS	   191
#define	SNOW       178
#define MOBS	   -98
#define WATER	   -80
#define	BRIDGE	   -16
#define GOAL       33      
#define WHITESPACE 32
#define PLAYER	   1

/*Extended ASCII endregion */
#pragma endregion

#pragma region Libraries

#include <Windows.h>		// necessary for Windows API
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

#pragma endregion

#pragma region Sounds

#pragma comment(lib, "Winmm.lib" )  // add the Winmm.lib to the build

/* You'll have to add those wav files to the resources so it would work*/

#define BEEP_POINT	 PlaySound(MAKEINTRESOURCE(IDR_WAVE1),GetModuleHandle(0),SND_RESOURCE|SND_ASYNC);	// plays beep-01.wav
#define BEEP_ENEMY   PlaySound(MAKEINTRESOURCE(IDR_WAVE2),GetModuleHandle(0),SND_RESOURCE|SND_ASYNC);   // plays beep-03.wav

/* Sounds endregion */
#pragma endregion

#pragma region Map

#define MapHW tempMap[h][w]
#define pX	  crtPosX
#define pY    crtPosY 

/* Measurements of the map */

#define WIDTH  65	
#define HEIGHT 15

/* Map endregion */

#pragma endregion






