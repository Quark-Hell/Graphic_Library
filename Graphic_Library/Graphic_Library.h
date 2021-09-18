#include "pch.h"
#include <windows.h>
#include <string>
#include <vector>

using namespace std;

#pragma once

#ifdef GRAPHICLIBRARY_EXPORTS
#define GRAPHICLIBRARY_API extern "C" __declspec(dllexport)
#else
#define GRAPHICLIBRARY_API extern "C" __declspec(dllimport)
#endif


/*---------------------------------Struct------------------------------------------------*/

extern "C" GRAPHICLIBRARY_API struct Mesh;

/*---------------------------------Struct------------------------------------------------*/

/*---------------------------------Class------------------------------------------------*/

extern "C" GRAPHICLIBRARY_API class GameObject;

extern "C" GRAPHICLIBRARY_API class ScreenClass;

extern "C" GRAPHICLIBRARY_API class ConsoleInfo;

extern "C" GRAPHICLIBRARY_API class Camera;

extern "C" GRAPHICLIBRARY_API class Draw;

/*---------------------------------Class------------------------------------------------*/

/*---------------------------------Function------------------------------------------------*/

extern "C" GRAPHICLIBRARY_API bool InitializeScreen(int sizeX, int SizeY);

#pragma region ConsoleInfo Function

extern "C" GRAPHICLIBRARY_API COORD GetConsoleCursorPosition();

extern "C" GRAPHICLIBRARY_API LPTSTR ReadConsoleOut(COORD coord);

extern "C" GRAPHICLIBRARY_API bool SetCursorPosition(COORD coord);

extern "C" GRAPHICLIBRARY_API WORD Attributes;
extern "C" GRAPHICLIBRARY_API bool SetConsoleColour(DWORD Colour);

extern "C" GRAPHICLIBRARY_API bool ResetConsoleColour(WORD Attributes);

extern "C" GRAPHICLIBRARY_API bool SetCharachterSize(int sizeX,int sizeY);

extern "C" GRAPHICLIBRARY_API bool ShowConsoleCursor(bool showFlag);

#pragma endregion

#pragma region Draw Function

extern "C" GRAPHICLIBRARY_API void EraseObject(GameObject object);

extern "C" GRAPHICLIBRARY_API void DrawObject(COORD coord, GameObject object);

extern "C" GRAPHICLIBRARY_API bool RenderFrame(GameObject allObjects, COORD CameraPos);

extern "C" GRAPHICLIBRARY_API bool ClearScreen(char fill);

extern "C" GRAPHICLIBRARY_API void DrawString(string Texture, COORD coord = GetConsoleCursorPosition(), DWORD Color = 0);

#pragma endregion

/*---------------------------------Function------------------------------------------------*/

/*---------------------------------Variables------------------------------------------------*/

#pragma region Screen Variables

extern "C" GRAPHICLIBRARY_API int SizeX;

extern "C" GRAPHICLIBRARY_API int SizeY;

extern "C" GRAPHICLIBRARY_API vector<string> Screen;

#pragma endregion

#pragma region Camera Variables

extern "C" GRAPHICLIBRARY_API COORD CameraPos;

#pragma endregion


/*---------------------------------Variables------------------------------------------------*/