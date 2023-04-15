#pragma once

#ifndef _MAIN_APP_HEADER_HPP_
#define _MAIN_APP_HEADER_HPP_

#include <Windows.h>
#include <cstdlib>
#include <string>
#include <math.h>
#include <random>
using namespace std;


#define WIDTH 1000
#define HEIGHT 680
#define X_CENTER 310
#define Y_CENTER 310
#define X_CLETKA 20
#define Y_CLETKA 20
#define button_graph_1 1
#define button_graph_2 2
#define id_edit_text_1 99
#define id_edit_text_2 98
#define id_edit_text_3 97
#define id_edit_text_4 96
#define id_edit_text_min 110
#define id_edit_text_max 111
#define id_edit_text_main 100
#define id_edit_1 101
#define id_edit_2 102
#define id_edit_3 103
#define id_edit_4 104
#define id_edit_min 105
#define id_edit_max 106
#define menu_c_1 3
#define menu_c_2 4
#define menu_c_3 5
#define menu_c_4 6
#define menu_c_5 7


HINSTANCE hinst;
HDC dc;
HFONT font;
PAINTSTRUCT ps;
HPEN hpen;
HPEN hpen1;
HPEN hpen2;
HPEN hpen3;
HPEN hpen4;
HPEN hpen5;
HPEN hpen6;
HPEN hpen7;
HWND edit_line_min;
HWND edit_line_max;
HWND edit_line_1;
HWND edit_line_2;
HWND edit_line_3;
HWND edit_line_4;
HWND text_line_main_1;
HWND text_line_main_2;
HWND text_line_1;
HWND text_line_2;
HWND text_line_3;
HWND text_line_4;
HWND text_line_min;
HWND text_line_max;
HMENU menu_popup_1;
HMENU menu_1;
bool start;
int graph;
float k;
float c;
float b;
float l;
float min_g;
float max_g;
char argv_edit_1[100];
char argv_edit_2[100];
char argv_edit_3[100];
char argv_edit_4[100];
char argv_edit_min[100];
char argv_edit_max[100];


//main

LRESULT CALLBACK WndProc(
    HWND hwnd, 
    UINT msg, 
    WPARAM wp, 
    LPARAM lp
);

//-------------------------------------

//interface

void CreateWidgets(HWND hwnd, HDC dc);
void CreateInterfaceMain(HWND hwnd);
void CreateInterfaceLine(HWND hwnd, HDC dc);
void CreateInterfaceParabola(HWND hwnd, HDC dc);
void CreateInterfaceGiperbola(HWND hwnd, HDC dc);
void CreateInterfaceSin(HWND hwnd, HDC dc);
void CreateInterfaceCos(HWND hwnd, HDC dc);
void CreateMyMenu(HWND hwnd);
void DestroyInterface();

//-------------------------------------

//graphic
HPEN RandomHpen();
void Paint_Start(HDC dc);
void Paint_Cletka(HDC dc);
void Paint_CletkaAddX(int amount);
void Paint_CletkaAddY(int amount);
void Paint_Graphik(HDC dc, HWND hwnd);
void LineGraphik(HDC dc, float k, float b, float min_g, float max_g);
void ParabolaGraphik(HDC dc, float a, float b, float c, float min_g, float max_g);
void GiperbolaGraphik(HDC dc, float a, float b, float c, float l, float min_g, float max_g);
void SinGraphik(HDC dc, float a, float b, float c, float l, float min_g, float max_g);
void CosGraphik(HDC dc, float a, float b, float c, float l, float min_g, float max_g);
void CaseGraph(HWND hwnd, int v, HDC dc);

//-------------------------------------

#endif