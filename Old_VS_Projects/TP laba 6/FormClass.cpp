#include "FormClass.h"

DWORD FormClass::CreateNewConsole(console* con) {
	con->hout = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); // консоль вывода
	if (con->hout == INVALID_HANDLE_VALUE) { return GetLastError(); }
	con->hin = CreateFileW(L"CONIN$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0UL, NULL);  // консоль ввода
	if (con->hin == INVALID_HANDLE_VALUE) {
		DWORD err = GetLastError();
		CloseHandle(con->hout);
		con->hout = INVALID_HANDLE_VALUE;
		return err;
	}
	DWORD mode = 0;
	if (GetConsoleMode(carr.front().hin, &mode)) { SetConsoleMode(con->hin, mode); }
	COORD size;
	size.X = carr.front().width;
	size.Y = carr.front().height;
	SetConsoleScreenBufferSize(con->hout, size);
	CONSOLE_SCREEN_BUFFER_INFO inf = { 0 };
	if (GetConsoleScreenBufferInfo(con->hout, &inf)) {
		con->width = inf.dwSize.X;
		con->height = inf.dwSize.Y;
	}
	else {
		con->width = size.X;
		con->height = size.Y;
	}
	return NO_ERROR;
}

FormClass::FormClass(void) {
	hout = INVALID_HANDLE_VALUE;
	hin = INVALID_HANDLE_VALUE;
	async_loop = 0;
	width = 0;
	height = 0;
}

DWORD FormClass::CreateMainForm(void) {
	hin = GetStdHandle(STD_INPUT_HANDLE);
	if (hin == INVALID_HANDLE_VALUE) { return GetLastError(); }
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hout == INVALID_HANDLE_VALUE) {
		hin = INVALID_HANDLE_VALUE;
		return GetLastError();
	}
	CONSOLE_SCREEN_BUFFER_INFO inf = { 0 };
	if (GetConsoleScreenBufferInfo(hout, &inf)) {
		width = inf.dwSize.X;
		height = inf.dwSize.Y;
	}
	console con;
	con.hout = hout;
	con.hin = hin;
	con.width = width;
	con.height = height;
	carr.add(con);
	return NO_ERROR;
}

DWORD FormClass::AddBuffer(void) {
	console con;
	DWORD ret = CreateNewConsole(&con);
	if (ret == ERROR_SUCCESS) { carr.add(con); }
	return ret;
}

WORD FormClass::GetKey(HANDLE hin) {
	INPUT_RECORD rs[128];
	DWORD num;
	BOOL  ret;
	while (1) {
		num = 0;
		ret = ReadConsoleInput(hin, rs, sizeof(rs) / sizeof(rs[0]), &num);
		if (!ret) { continue; }
		for (DWORD i = 0; i < num; ++i) {
			switch (rs[i].EventType) {
			case KEY_EVENT:
				if (rs[i].Event.KeyEvent.bKeyDown) { return rs[i].Event.KeyEvent.wVirtualKeyCode; }
				break;
			}
		}
	}
	return WORD(~0);
}

BOOL FormClass::writeText(LPCWSTR str, short x, short y, DWORD len) {
	DWORD n = 0;
	COORD p = { x, y };
	return WriteConsoleOutputCharacterW(hout, str, len, p, &n);
}

void FormClass::writeText(LPCSTR str, int len, short x, short y, WORD color) {
	DWORD n = 0, l = static_cast<DWORD>(len);
	COORD p = { x, y };
	WriteConsoleOutputCharacterA(hout, str, l, p, &n);
	FillConsoleOutputAttribute(hout, color, l, p, &n);
}

void FormClass::OnKeyDown(WORD key) {
	if (key == VK_ESCAPE)
		ExitProcess(0);
}

void FormClass::drawRect(short x1, short y1, short x2, short y2, WORD color) {
	DWORD n = 0;
	DWORD l = (DWORD)(x2 - x1);
	COORD p = { x1, y1 };
	for (short y = y1; y <= y2; ++y) {
		p.Y = y;
		FillConsoleOutputAttribute(hout, color, l, p, &n);
	}
}

void FormClass::drawRect(const SMALL_RECT& rc, WORD color) {
	drawRect(rc.Left, rc.Top, rc.Right, rc.Bottom, color);
}

void FormClass::drawCharRect(CHAR ch, short x1, short y1, short x2, short y2) {
	DWORD n = 0;
	DWORD l = (DWORD)(x2 - x1);
	COORD p = { x1, y1 };
	for (short y = y1; y <= y2; ++y) {
		p.Y = y;
		FillConsoleOutputCharacterA(hout, ch, l, p, &n);
	}
}

void FormClass::drawFrame(short x1, short y1, short x2, short y2, WORD color) {
	DWORD n = 0;
	DWORD l = (DWORD)(x2 - x1);
	COORD p = { x1, y1 };
	FillConsoleOutputAttribute(hout, color, l, p, &n);
	p.Y = y2;
	FillConsoleOutputAttribute(hout, color, l, p, &n);
	for (short i = y1; i <= y2; ++i) {
		p.Y = i;
		p.X = x1;
		FillConsoleOutputAttribute(hout, color, 1, p, &n);
		p.X = x2;
		FillConsoleOutputAttribute(hout, color, 1, p, &n);
	}
}

void FormClass::drawFrame(const SMALL_RECT& rc, WORD color) {
	drawFrame(rc.Left, rc.Top, rc.Right, rc.Bottom, color);
}

void FormClass::fillChar(CHAR ch, const SMALL_RECT& rc) {
	DWORD l = (DWORD)(rc.Right - rc.Left);
	DWORD n = 0;
	COORD p = { rc.Left, 0 };
	for (short i = rc.Top; i <= rc.Bottom; ++i) {
		p.Y = i;
		FillConsoleOutputCharacterA(hout, ch, l, p, &n);
	}
}

BOOL FormClass::fillChar(CHAR ch, short x, short y, DWORD len) {
	DWORD n = 0;
	COORD p = { x, y };
	return FillConsoleOutputCharacterA(hout, ch, len, p, &n);
}

BOOL FormClass::fillAttribute(WORD color, short x, short y, DWORD len = 1) {
	DWORD n = 0;
	COORD p = { x, y };
	return FillConsoleOutputAttribute(hout, color, len, p, &n);
}

void  FormClass::setBufferSize(short new_width, short new_height) {
	COORD scr = { new_width, new_height };
	if (SetConsoleScreenBufferSize(hout, scr)) {
		width = new_width;
		height = new_height;
	}
}

BOOL FormClass::setWindowSize(SMALL_RECT& rc, BOOL absolute) {
	COORD sz = GetLargestConsoleWindowSize(hout);
	if (rc.Right > sz.X) { rc.Right = sz.X; }
	if (rc.Bottom > sz.Y) { rc.Bottom = sz.Y; }
	return SetConsoleWindowInfo(hout, absolute, &rc);
}

SMALL_RECT FormClass::getWindowSize(void) const {
	CONSOLE_SCREEN_BUFFER_INFO cinf;
	if (GetConsoleScreenBufferInfo(hout, &cinf)) { return cinf.srWindow; }
	SMALL_RECT rc = { 0 };
	return rc;
}

BOOL FormClass::Reset(void) {
	return FlushConsoleInputBuffer(hin);
}

short FormClass::getWidth(void) const {
	return width;
}

short FormClass::getHeight(void) const {
	return height;
}

HANDLE FormClass::getInput(void) const {
	return hin;
}

HANDLE FormClass::getOutput(void) const {
	return hout;
}