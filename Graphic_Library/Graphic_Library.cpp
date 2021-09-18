#include "pch.h" 
#include "Graphic_Library.h"
#include <windows.h>
#include <string.h>
#include <vector>

class Mesh {
public:
    vector <COORD> Vertices;
public:
    vector <COORD> Triangles;
};

class Camera {
public:
    COORD CameraPos;

    Camera(COORD cameraPos) {
        CameraPos.X = cameraPos.X;
        CameraPos.Y = cameraPos.Y;
    }

};

static class ScreenClass {
public:
    __declspec(dllexport) static int SizeX;
public:
    __declspec(dllexport) static int SizeY;

//public:
    //__declspec(dllexport) static vector<string> Screen;

//public:
    //__declspec(dllexport) static vector<vector<DWORD>> ScreenColour;

public:
    __declspec(dllexport) ScreenClass(int sizeX,int sizeY) {
        ScreenClass::SizeX = sizeX;
        ScreenClass::SizeY = sizeY;

        //ScreenClass::Screen.clear();

        //Screen.resize(sizeY);

        for (size_t y = 0; y < sizeY; y++)
        {
            string str;
            //Screen.push_back(str);
            //ScreenColour.resize(sizeY);
            //ScreenColour[y].resize(sizeX);

            for (size_t x = 0; x < sizeX; x++)
            {
                //Screen[y].push_back(*" ");
            }
        }
    }
};
int ScreenClass::SizeX;
int ScreenClass::SizeY;
//vector<string> ScreenClass::Screen;


class GameObject {
public:
    Mesh mesh;
public:
    GameObject* OverlappedObject;
public:
    COORD Pos;
public:
    Mesh MeshObject;
public:
    DWORD Color;
public:
    string Tag = "null";

public:
    __declspec(dllexport) bool SetMesh(vector <COORD> vertices) {
        mesh.Vertices.clear();
        for (size_t i = 0; i < vertices.size(); i++)
        {
            mesh.Vertices.push_back(vertices[i]);
        }
        return true;
    }
public:
    __declspec(dllexport) bool SetTriangles(vector <COORD> vertices) {
        mesh.Vertices.clear();
        for (size_t i = 0; i < vertices.size(); i++)
        {
            mesh.Vertices.push_back(vertices[i]);
        }
        return true;
    }
public:
    
};

static class ConsoleInfo {
public:
    __declspec(dllexport) static WORD Attributes;
public:
    __declspec(dllexport) static COORD GetConsoleCursorPosition()
    {
        HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (GetConsoleScreenBufferInfo(hCon, &csbi))
        {
            return csbi.dwCursorPosition;
        }
        else
        {
            // The function failed. Call GetLastError() for details.
            COORD invalid = { 0, 0 };
            return invalid;
        }
    }

public:
    __declspec(dllexport) static LPTSTR ReadConsoleOut(COORD coord) {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
        LPTSTR lpCharacter = new TCHAR[1];
        DWORD dwReaden = 0;
        ReadConsoleOutputCharacter(hCon, lpCharacter, 1, GetConsoleCursorPosition(), &dwReaden);
        return lpCharacter;
    }

public:
    __declspec(dllexport) static bool SetCursorPosition(COORD coord) {
        HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(hCon, coord);
        return true;
    }

public:
    __declspec(dllexport) static bool SetConsoleColour(DWORD Colour) {
        CONSOLE_SCREEN_BUFFER_INFO Info;
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(hStdout, &Info);
        SetConsoleTextAttribute(hStdout, Colour);

        return true;
    }

public:
    __declspec(dllexport) static bool ResetConsoleColour() {
        CONSOLE_SCREEN_BUFFER_INFO Info;
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(hStdout, &Info);
        SetConsoleTextAttribute(hStdout, 15);

        return true;
    }

public:
    __declspec(dllexport) static bool SetCharachterSize(int sizeX, int sizeY) {
        CONSOLE_FONT_INFOEX cfi;
        cfi.cbSize = sizeof(cfi);
        cfi.nFont = 0;
        cfi.dwFontSize.X = sizeX;                   // Width of each character in the font
        cfi.dwFontSize.Y = sizeY;                  // Height
        cfi.FontFamily = FF_DONTCARE;
        cfi.FontWeight = FW_NORMAL;
        wcscpy_s(cfi.FaceName, L"Consolas"); // Choose your font
        SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
        return true;
    }

public:
    __declspec(dllexport) static bool ShowConsoleCursor(bool showFlag)
    {
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

        CONSOLE_CURSOR_INFO     cursorInfo;

        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = showFlag; // set the cursor visibility
        SetConsoleCursorInfo(out, &cursorInfo);

        return true;
    }
};
WORD ConsoleInfo::Attributes;

static class Draw {
public:
    __declspec(dllexport) static void SetConsoleColour(DWORD Colour)
    {
        CONSOLE_SCREEN_BUFFER_INFO Info;
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(hStdout, &Info);
        SetConsoleTextAttribute(hStdout, Colour);
    }

    /*
public:
    void EraseObject(GameObject object) {
        for (size_t i = 0; i < object.TextureObject.length(); i++)
        {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), object.Pos);
            printf(" ");
            object.Pos.X++;
        }
    }
    */

public:
    __declspec(dllexport) static void DrawObject(COORD coord, GameObject object) {
        ConsoleInfo::SetCursorPosition(coord);
        SetConsoleColour(object.Color);

        for (size_t i = 0; i < object.mesh.Vertices.size(); i++)
        {
            COORD newCursorPos;
            newCursorPos.X = ConsoleInfo::GetConsoleCursorPosition().X + object.mesh.Vertices[0].X;
            newCursorPos.Y = ConsoleInfo::GetConsoleCursorPosition().Y + object.mesh.Vertices[0].Y;

            while (ConsoleInfo::GetConsoleCursorPosition().Y != object.mesh.Vertices[i + 1].Y)
            {
#pragma region Drawning object on axis X
                //-----------------------------------------Positive values----------------------------------------------//
                if (ConsoleInfo::GetConsoleCursorPosition().X < object.mesh.Vertices[i + 1].X + object.Pos.X)
                {
                    newCursorPos.X++;
                    coord.X = newCursorPos.X;
                    ConsoleInfo::SetCursorPosition(coord);
                    printf("#");
                }
                //-----------------------------------------Positive values----------------------------------------------//
                // 
                //-----------------------------------------Negative values----------------------------------------------//
                else if (ConsoleInfo::GetConsoleCursorPosition().X > object.mesh.Vertices[i + 1].X + object.Pos.X)
                {
                    newCursorPos.X--;
                    coord.X = newCursorPos.X;
                    ConsoleInfo::SetCursorPosition(coord);
                    printf("#");
                }
                //-----------------------------------------Negative values----------------------------------------------//
                else
                {
                    coord.X = object.mesh.Vertices[i].X + object.Pos.X;
                    coord.Y--;
                    COORD temp = ConsoleInfo::GetConsoleCursorPosition();
                    ConsoleInfo::SetCursorPosition(coord);
                }
#pragma endregion
            }
        }
    }

public:
    __declspec(dllexport) static bool RenderFrame(vector<GameObject*> allObjects, Camera camera) {

        for (size_t y  = 0; y < ScreenClass::SizeY; y++)
        {
            for (size_t k = 0; k < ScreenClass::SizeX; k++)
            {
                for (size_t z = 0; z < allObjects.size(); z++)
                {
                    vector<COORD> triangles = allObjects[z]->mesh.Triangles;

                    COORD currentPos;
                    currentPos.X = k;
                    currentPos.Y = y;

                    for (size_t t = 0; t < triangles.size(); t+=3)
                    {
                        float x1 = ((triangles[t].X + allObjects[z]->Pos.X) - currentPos.X) * ((triangles[t + 1].Y + allObjects[z]->Pos.Y) - (triangles[t].Y + allObjects[z]->Pos.Y)) - ((triangles[t + 1].X + allObjects[z]->Pos.X) - (triangles[t].X + allObjects[z]->Pos.X)) * ((triangles[t].Y + allObjects[z]->Pos.Y) - currentPos.Y);
                        float x2 = ((triangles[t + 1].X + allObjects[z]->Pos.X) - currentPos.X) * ((triangles[t + 2].Y + allObjects[z]->Pos.Y) - (triangles[t + 1].Y + allObjects[z]->Pos.Y)) - ((triangles[t + 2].X + allObjects[z]->Pos.X) - (triangles[t + 1].X + allObjects[z]->Pos.X)) * ((triangles[t + 1].Y + allObjects[z]->Pos.Y) - currentPos.Y);
                        float x3 = ((triangles[t + 2].X + allObjects[z]->Pos.X) - currentPos.X) * ((triangles[t].Y + allObjects[z]->Pos.Y) - (triangles[t + 2].Y + allObjects[z]->Pos.Y)) - ((triangles[t].X + allObjects[z]->Pos.X) - (triangles[t + 2].X + allObjects[z]->Pos.X)) * ((triangles[t + 2].Y + allObjects[z]->Pos.Y) - currentPos.Y);

                        if (x1 >= 0 && x2 >= 0 && x3 >= 0)
                        {
                            ConsoleInfo::SetCursorPosition(currentPos);
                            ConsoleInfo::SetConsoleColour(allObjects[z]->Color);
                            //ScreenClass::ScreenColour[y][currentPos.X] = allObjects[z]->Color;
                            //ScreenClass::Screen[y][currentPos.X] = *"#";
                            printf("#");
                        }
                        else if(x1 <= 0 && x2 <= 0 && x3 <= 0)
                        {
                            ConsoleInfo::SetCursorPosition(currentPos);
                            ConsoleInfo::SetConsoleColour(allObjects[z]->Color);
                            //ScreenClass::ScreenColour[y][currentPos.X] = allObjects[z]->Color;
                            //ScreenClass::Screen[y][currentPos.X] = *"#";
                            printf("#");
                        }
                    }
                }
            }
        }
           /*
        COORD crd;
        crd.X = 0;
        crd.Y = 0;

        for (size_t y = 0; y < ScreenClass::SizeY; y++)
        {
            printf("%s", ScreenClass::Screen[y].c_str());
            crd.Y++;
        }
                    */
        return true;
    }


public:
    __declspec(dllexport) static bool ClearScreen(char fill = ' ') {
        COORD tl = { 0,0 };
        CONSOLE_SCREEN_BUFFER_INFO s;
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(console, &s);
        DWORD written, cells = s.dwSize.X * s.dwSize.Y;
        FillConsoleOutputCharacter(console, fill, cells, tl, &written);
        FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
        SetConsoleCursorPosition(console, tl);
        return true;
    }

public:
    __declspec(dllexport) static void DrawString(string Texture, COORD coord = GetConsoleCursorPosition(), DWORD Color = 0) {
        SetConsoleColour(Color);
        ConsoleInfo::SetCursorPosition(coord);
        printf("%s", Texture.c_str());
    }
public:
    __declspec(dllexport) static void EraseString(COORD StartCoord, COORD EndCoord) {

        for (int i = 0; i < EndCoord.X - StartCoord.X; i++)
        {
            COORD coord;
            coord.X = StartCoord.X + i;
            coord.Y = StartCoord.Y;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            printf(" ");
        }
    }
};