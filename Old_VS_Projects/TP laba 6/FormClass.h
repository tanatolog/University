#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS  1
#endif
#pragma once

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "list.h"

class FormClass {
private: 
	BOOL async_loop;
	DWORD CreateNewConsole(console* con);
	void OnKeyDown(WORD key);
protected: 
	HANDLE hout, hin;
	short width;
	short height;
	usefullist carr;
public:
	FormClass(void);
	DWORD CreateMainForm(void);         //cоздание основной формы
	DWORD AddBuffer(void);              //добавление дополнительного буфера
	static WORD GetKey(HANDLE hin);     //приём сообщений от клавиатуры
	BOOL writeText(LPCWSTR str, short x, short y, DWORD len);
	void writeText(LPCSTR str, int len, short x, short y, WORD color); //вывод текста по указанной позиции
	void drawRect(short x1, short y1, short x2, short y2, WORD color); //вывод прямоугольника
	void drawRect(const SMALL_RECT& rc, WORD color);
	void drawCharRect(CHAR ch, short x1, short y1, short x2, short y2); //вывод прямоугольника из символов
	void drawFrame(short x1, short y1, short x2, short y2, WORD color); //вывод рамки прямоугольника
	void drawFrame(const SMALL_RECT& rc, WORD color);
	void fillChar(CHAR ch, const SMALL_RECT& rc); //заливка символами прямоугольника
	BOOL fillChar(CHAR ch, short x, short y, DWORD len);
	BOOL fillAttribute(WORD color, short x, short y, DWORD len); //заливка атрибутами
	void  setBufferSize(short new_width, short new_height); //устанавливает размер буфера консоли
	BOOL setWindowSize(SMALL_RECT& rc, BOOL absolute); //устанавливает размер окна консоли
	SMALL_RECT getWindowSize(void) const;  //возвращает текущий размер окна консоли
	BOOL Reset(void); //очистка консоли
	short getWidth(void) const;  // ширина буфера консоли
	short getHeight(void) const; // высота буфера консоли
	HANDLE getInput(void) const; //указатель на поток ввода
	HANDLE getOutput(void) const; // указатель на поток вывода
};

