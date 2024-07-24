#include "game.h"

void GameTetris::swap_int(int& a, int& b) {
	int t = a;
	a = b;
	b = t;
}

void GameTetris::reverse_vert(int src[][FIELD_SIZE]) {
	int i = 0, j = FIELD_SIZE - 1;
	for (; i < j; ++i, --j) {
		for (int c = 0; c < FIELD_SIZE; ++c)
			swap_int(src[i][c], src[j][c]);
	}
}

void GameTetris::transponse(int dst[][FIELD_SIZE], int src[][FIELD_SIZE]) {
	for (int i = 0; i < FIELD_SIZE; ++i) {
		for (int j = 0; j < FIELD_SIZE; ++j)
			dst[j][i] = src[i][j];
	}
}

void GameTetris::transponse(int src[][FIELD_SIZE]) {
	for (int i = 0; i < FIELD_SIZE; ++i) {
		for (int j = i; j < FIELD_SIZE; ++j)
			swap_int(src[j][i], src[i][j]);
	}
}

WORD GameTetris::get_color(int type) {
	WORD color;
	switch (type) {
	case CELL_MOVE:
		color = MOVE_COLOR;
		break;
	case CELL_BUSY:
		color = BOX_COLOR;
		break;
	default:
		color = BOOM_COLOR;
		break;
	}
	return color;
}

BOOL GameTetris::isKeyEvent(void) {
	if (isKeyState(VK_LEFT) || isKeyState('A') || isKeyState(VK_RIGHT) || isKeyState('D'))
		return TRUE;
	return FALSE;
}

GameTetris::GameTetris(void) : FormClass() {}

void GameTetris::OnCreate(void) {
	srand(static_cast<unsigned int>(time(NULL)));
	const WCHAR title[] = { 0x422, 0x435, 0x442, 0x440, 0x438, 0x441, 0x0 };
	SetConsoleTitleW(title);
	setBufferSize(getWidth(), getHeight() / 7);
	SMALL_RECT rc = getWindowSize();
	rc.Bottom = getHeight() - 1;
	setWindowSize(rc, TRUE);
	left_field = 8;
	right_field = left_field + WIDTH_SIZE;
	move_time = 0;
	move_figure = once_figure = FALSE;
	figure_x = figure_y = 0;
	delay = DELAY_GAME;
	field_cnt = FIELD_ROWS + FIELD_COLS;
	field_rect.Left = left_field;
	field_rect.Top = 0;
	field_rect.Right = right_field;
	field_rect.Bottom = getHeight() - 1;
	field_size.X = FIELD_COLS;
	field_size.Y = FIELD_ROWS;

	title_game();
}

void GameTetris::run(DWORD msec) {
	while (TRUE) {
		getAsyncMessage();
		Sleep(msec);
	}
}

void GameTetris::getAsyncMessage(void) {
	INPUT_RECORD recs[128];
	COORD pt;
	DWORD num = 0;
	if (PeekConsoleInput(hin, recs, sizeof(recs) / sizeof(recs[0]), &num)) {

		BOOL ismsg = FALSE;
		for (DWORD i = 0; i < num; ++i) {
			switch (recs[i].EventType) {
			case KEY_EVENT:

				if (recs[i].Event.KeyEvent.bKeyDown)
					OnKeyDown(recs[i].Event.KeyEvent.wVirtualKeyCode);
				else
					OnKeyUp(recs[i].Event.KeyEvent.wVirtualKeyCode);

				ismsg = TRUE;
				break;
			}
		}

		if (ismsg) { Reset(); }
		OnProcess();
	}
}

DWORD GameTetris::CreateMainForm(void) {      //создание
	hin = GetStdHandle(STD_INPUT_HANDLE);
	if (hin == INVALID_HANDLE_VALUE)
		return GetLastError();

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

	OnCreate();
	return NO_ERROR;
}

void GameTetris::OnKeyDown(WORD key) {
	switch (key) {
	case VK_LEFT: //движение влево
	case 'A':
		if (move_object(-1, 0))
			draw_field();
		break;
	case VK_RIGHT: //движение вправо
	case 'D':
		if (move_object(1, 0))
			draw_field();
		break;
	case VK_DOWN: //движение вниз
	case 'S':
		if (move_object(0, 1))
			draw_field();
		break;
	case VK_UP: //вращение
	case 'W':
		if (rotate())
			draw_field();
		break;
	}
}

void GameTetris::OnKeyUp(WORD key) {
	if (key == VK_ESCAPE)
		ExitProcess(0);
}

void GameTetris::OnProcess(void) {
	DWORD tick = GetTickCount64();
	if ((tick - move_time) > delay) {
		move_time = tick;
		update_frame();
	}
}

void GameTetris::start_game(void) {
	init_field();
	draw_field();
	draw_play();
	build_figure();
}

void GameTetris::init_field(void) {
	delay = DELAY_GAME;
	once_figure = FALSE;
	memset(field, 0, sizeof(field));
	memset(field_boxs, 0, sizeof(field_boxs));
}

void GameTetris::update_frame(void) {
	if (move_figure && !isKeyEvent()) 
		move_object(0, 1);
	draw_field();
}

void GameTetris::draw_field(void) {
	memset(field, 0, sizeof(field));
	for (int i = 0; i < T_ROWS; ++i) {
		for (int j = 0; j < T_COLUMNS; ++j) {
			if (field_boxs[i][j] & CELL_BUSY)
				draw_box(j * CELL_WIDTH, i * CELL_HEIGHT, get_color(field_boxs[i][j]));
		}
	}
	COORD pos = { 0, 0 };
	WriteConsoleOutputA(getOutput(), field, field_size, pos, &field_rect);
}

BOOL GameTetris::move_object(int x, int y) {
	int ret = 1;
	put_figure(CELL_NONE);
	if (x == -1) {//движение влево

		ret = is_move_figure(-1, 0);
		if (ret == 1)
			--figure_x;
	}
	else if (x == 1) {//движение вправо

		ret = is_move_figure(1, 0);
		if (ret == 1)
			++figure_x;
	}
	else if (y == 1) {//движение вниз
		ret = is_move_figure(0, 1);
		if (ret == 1)
			++figure_y;
		else if (ret == EOF_FIGURE) {
			put_figure(CELL_BUSY);
			boom_boxs_line();
			//проверить на проигрыш
			if (is_game_over()) {//вы проиграли
				game_over();
				return 0;
			}
			else
				build_figure();
			return 1;
		}
	}
	put_figure(CELL_MOVE);
	return (ret != 0) ? TRUE : FALSE;
}

int GameTetris::is_move_figure(int dx, int dy) {
	int x, y;
	for (int i = 0; i < FIELD_SIZE; ++i) {
		for (int j = 0; j < FIELD_SIZE; ++j) {
			if (figure[i][j] == CELL_NONE)
				continue;
			if (dx != 0) { //проверка на движение влево или вправо
				x = figure_x + j + dx;
				y = figure_y + i;
				if (x < 0 || x >= T_COLUMNS)
					return 0;
				else if (field_boxs[y][x] & CELL_BUSY)
					return 0;
			}
			else if (dy == 1) { //проверка на движение вниз
				x = figure_x + j;
				y = figure_y + i + dy;
				if (y < 0)
					continue;
				else if ((y >= T_ROWS) || (field_boxs[y][x] & CELL_BUSY))
					return EOF_FIGURE;
			}
		}
	}
	return 1;
}

void GameTetris::put_figure(int flag) {
	int x, y;
	for (int i = 0; i < FIELD_SIZE; ++i) {
		for (int j = 0; j < FIELD_SIZE; ++j) {
			if (figure[i][j] & CELL_BUSY) {
				x = figure_x + j;
				y = figure_y + i;
				if ((x < 0) || (x >= T_COLUMNS) || (y < 0) || (y >= T_ROWS))
					continue;

				field_boxs[y][x] = flag;
			}
		}
	}
}

void GameTetris::draw_box(short int x, short int y, WORD color) {
	const CHAR top[] = "\xDA\xC4\xBF";
	fieldText(top, 3, x, y);

	const CHAR bottom[] = "\xC0\xC4\xD9";
	fieldText(bottom, 3, x, y + 1);

	fieldColor(color, x, y, 3);
	fieldColor(color, x, y + 1, 3);
}

void GameTetris::put_box(short int x, short int y, WORD color) {
	const CHAR top[] = "\xDA\xC4\xBF";
	writeText(top, 3, x, y, color);

	const CHAR bottom[] = "\xC0\xC4\xD9";
	writeText(bottom, 3, x, y + 1, color);
}

void GameTetris::draw_play(void) {
	const WORD  c = (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	const short h = getHeight();
	for (short i = 0; i < h; ++i) {
		fillChar('\xBA', left_field - 1, i, 1UL);
		fillAttribute(c, left_field - 1, i, 1);
		fillChar('\xBA', right_field, i, 1UL);
		fillAttribute(c, right_field, i, 1);
	}
	const WORD color = (BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	drawRect(0, 0, left_field - 1, getHeight(), color);
	drawRect(right_field + 1, 0, right_field + (getWidth() - right_field), getHeight(), color);
	const WORD  color1 = COLOR_WHITE;
	const WCHAR desc[] = { 0x421, 0x41B, 0x415, 0x414, 0x423, 0x42E, 0x429, 0x410, 0x42F, 0x20, 0x424, 0x418, 0x413, 0x423, 0x420, 0x410 };
	writeText(desc, right_field + 4, 1, sizeof(desc) / sizeof(desc[0]));
	fillAttribute(color1, right_field + 4, 1, sizeof(desc) / sizeof(desc[0]));
	const WCHAR score[] = { 0x41E, 0x427, 0x41A, 0x418 };
	writeText(score, right_field + 10, 18, sizeof(score) / sizeof(score[0]));
	fillAttribute(color1, right_field + 10, 18, sizeof(score) / sizeof(score[0]));
	drawRect(right_field + 4, 19, right_field + 20, 21, 0);
}

void GameTetris::build_figure(void) {
	const int N = 16;
	const char fgs[FIELD_SIZE * N][FIELD_SIZE] = {
		{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0},
		{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0},
		{0, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0},
		{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1},
		{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0},
		{0, 0, 0, 0}, {1, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0},
		{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0},
		{0, 0, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0},
		{0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0},
		{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 1, 0},
		{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0},
		{0, 0, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0},
		{0, 0, 0, 0}, {0, 1, 1, 1}, {0, 1, 1, 1}, {0, 0, 0, 0},
		{0, 0, 0, 0}, {0, 1, 1, 0}, {1, 1, 1, 1}, {0, 0, 0, 0},
		{1, 1, 1, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0},
		{0, 1, 1, 1}, {0, 0, 0, 1}, {0, 0, 0, 1}, {0, 0, 0, }
	};

	if (!once_figure) {
		once_figure = TRUE;
		const int row1 = (rand() % N) * FIELD_SIZE;
		const int row2 = (rand() % N) * FIELD_SIZE;
		for (int i = 0; i < FIELD_SIZE; ++i) {
			for (int j = 0; j < FIELD_SIZE; ++j) {
				next_figure[i][j] = static_cast<int>(fgs[row1 + i][j]);
				figure[i][j] = static_cast<int>(fgs[row2 + i][j]);
			}
		}
	}
	else {
		for (int r = 0; r < FIELD_SIZE; ++r)
			memcpy(figure[r], next_figure[r], FIELD_SIZE * sizeof(int));
		const int row = (rand() % N) * FIELD_SIZE;
		for (int i = 0; i < FIELD_SIZE; ++i) {
			for (int j = 0; j < FIELD_SIZE; ++j)
				next_figure[i][j] = static_cast<int>(fgs[row + i][j]);
		}
	}

	if ((rand() % 2) != 0) //транспонировать если что
		transponse(next_figure);
	draw_next_figure();
	move_figure = TRUE;
	figure_x = rand() % (T_COLUMNS - FIELD_SIZE);
	figure_y = -FIELD_SIZE;
}

void GameTetris::draw_next_figure(void) {
	short x = right_field + 6;
	short y = 4;
	drawRect(x - 1, y - 1, x + (FIELD_SIZE * CELL_WIDTH) + 1, y + (FIELD_SIZE * CELL_HEIGHT), BACKGROUND_BLUE);
	drawCharRect('\xB1', x - 1, y - 1, x + (FIELD_SIZE * CELL_WIDTH) + 1, y + (FIELD_SIZE * CELL_HEIGHT));
	drawFrame(x - 2, y - 2, x + (FIELD_SIZE * CELL_WIDTH) + 1, y + (FIELD_SIZE * CELL_HEIGHT) + 1, BACKGROUND_GREEN | BACKGROUND_BLUE);
	for (int i = 0; i < FIELD_SIZE; ++i) {
		for (int j = 0; j < FIELD_SIZE; ++j) {
			if (next_figure[i][j] & CELL_BUSY)
				put_box(x + j * CELL_WIDTH, y + i * CELL_HEIGHT, MOVE_COLOR);
		}
	}
}

void GameTetris::fieldText(LPCSTR s, DWORD n, short int x, short int y) {
	if ((x >= 0 && (x + short(n)) <= FIELD_COLS) && (y >= 0 && y < FIELD_ROWS)) {
		int i = y * FIELD_COLS + x;
		while (*s)
			field[i++].Char.AsciiChar = *s++;
	}
}

void GameTetris::fieldColor(WORD color, short int x, short int y, DWORD n) {
	if ((x >= 0 && (x + short(n)) <= FIELD_COLS) && (y >= 0 && y < FIELD_ROWS)) {
		int i = y * FIELD_COLS + x;
		int j = i + static_cast<short int>(n);
		while (i < j)
			field[i++].Attributes = color;
	}
}

BOOL GameTetris::rotate(void) {
	int i, j, temp[FIELD_SIZE][FIELD_SIZE];
	transponse(temp, figure);
	reverse_vert(temp);
	put_figure(CELL_NONE);
	BOOL ok = TRUE;
	int row, col;
	for (i = 0; i < FIELD_SIZE; ++i) {
		for (j = 0; j < FIELD_SIZE; ++j) {
			if (temp[i][j] & CELL_BUSY) {
				row = figure_y + i;
				col = figure_x + j;
				if (row < 0)
					continue;
				else if ((row >= T_ROWS) || (col >= T_COLUMNS) || (col < 0)) {
					ok = FALSE;
					goto _not;
				}
				else if (field_boxs[row][col] & CELL_BUSY) {
					ok = FALSE;
					goto _not;
				}
			}
		}
	}
_not:
	if (ok) {
		for (i = 0; i < FIELD_SIZE; ++i)
			memcpy(figure[i], temp[i], FIELD_SIZE * sizeof(int));
	}
	put_figure(CELL_MOVE);
	return ok;
}

BOOL GameTetris::is_game_over(void) {
	for (int j = 0; j < T_COLUMNS; ++j) {
		if (field_boxs[0][j] & CELL_BUSY)
			return TRUE;
	}
	return FALSE;
}

void GameTetris::boom_boxs_line(void) {
	int first, last, i, j, n;
	while ((first = find_line(last)) != -1) {
		for (i = first; i < last; ++i) {
			for (j = 0; j < T_COLUMNS; ++j)
				field_boxs[i][j] = CELL_BOOM;
		}
		draw_field();
		Sleep(100);
		MessageBeep((UINT)-1);
		n = last - first;
		for (i = last - 1; i > n; --i) {
			for (j = 0; j < T_COLUMNS; ++j)
				field_boxs[i][j] = field_boxs[i - n][j];
		}
		for (i = 0; i < n; ++i)
			memset(field_boxs[i], 0, T_COLUMNS * sizeof(int));
	}
}

int GameTetris::find_line(int& last) {
	int  j, first = -1;
	last = -1;
	for (int i = 0; i < T_ROWS; ++i) {
		j = 0;
		while ((j < T_COLUMNS) && (field_boxs[i][j] & CELL_BUSY))
			++j;

		if (j == T_COLUMNS) {
			first = i;
			break;
		}
	}
	if (first == -1)
		return -1;
	last = first + 1;
	for (int r = first + 1; r < T_ROWS; ++r) {
		j = 0;
		while ((j < T_COLUMNS) && (field_boxs[r][j] & CELL_BUSY))
			++j;

		if (j == T_COLUMNS)
			last = r + 1;
		else
			break;
	}
	return first;
}

void GameTetris::title_game(void) {
	SMALL_RECT rc = { 0, 0, getWidth(), getHeight() };
	const WORD col = BACKGROUND_BLUE | BACKGROUND_GREEN;
	drawRect(0, 0, getWidth(), 3, col);
	drawRect(0, getHeight() - 4, getWidth(), getHeight(), col);
	drawFrame(20, 14, getWidth() - 22, 28, BACKGROUND_BLUE);
	const WCHAR menu1[] = { 0x41D, 0x410, 0x427, 0x410, 0x422, 0x42C, 0x20, 0x418, 0x413, 0x420, 0x410, 0x422, 0x42C, 0x20, 0x41A, 0x41B, 0x410, 0x412, 0x418, 0x428, 0x410, 0x20, 0x45, 0x4E, 0x54, 0x45, 0x52 };
	writeText(menu1, 26, 19, sizeof(menu1) / sizeof(menu1[0]));
	fillAttribute(COLOR_WHITE, 26, 19, sizeof(menu1) / sizeof(menu1[0]));
	const WCHAR menu2[] = { 0x412, 0x42B, 0x425, 0x41E, 0x414, 0x20, 0x41A, 0x41B, 0x410, 0x412, 0x418, 0x428, 0x410, 0x20, 0x45, 0x53, 0x43 };
	writeText(menu2, 31, 23, sizeof(menu2) / sizeof(menu2[0]));
	fillAttribute(COLOR_WHITE, 31, 23, sizeof(menu2) / sizeof(menu2[0]));
	const WCHAR desc[] = { 0x423, 0x43F, 0x440, 0x430, 0x432, 0x43B, 0x435, 0x43D, 0x438, 0x435, 0x20, 0x438, 0x433, 0x440, 0x43E, 0x439 };
	writeText(desc, 3, getHeight() - 7, sizeof(desc) / sizeof(desc[0]));
	const WCHAR ctrl[] = { 0x41A, 0x43B, 0x430, 0x432, 0x438, 0x448, 0x430, 0x20, 0x432, 0x43B, 0x435, 0x432, 0x43E, 0x2F, 0x41, 0x2C, 0x20, 0x432, 0x43F, 0x440, 0x430, 0x432, 0x43E, 0x2F, 0x44, 0x2C, 0x20, 0x432, 0x43D, 0x438, 0x437, 0x2F, 0x53, 0x2C, 0x20, 0x432, 0x432, 0x435, 0x440, 0x445, 0x2F, 0x57 };
	writeText(ctrl, 3, getHeight() - 6, sizeof(ctrl) / sizeof(ctrl[0]));
	time_t    lt = time(NULL);
	struct tm* t = localtime(&lt);
	LPSTR s = asctime(t);
	int n = strlen(s) - 1;
	//writeText(s, n, (getWidth() - n) / 2, getHeight() - 2, col | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	WORD key;
	while ((key = FormClass::GetKey(getInput())) != WORD(~0)) {
		if (key == VK_RETURN) {
			MessageBeep((UINT)-1);
			fillChar(' ', rc);
			start_game();
			break;
		}
		else if (key == VK_ESCAPE) {//выход
			ExitProcess(0);
			return;
		}
	}
}

void GameTetris::game_over(void) {
	drawFrame(field_rect.Left, field_rect.Top, field_rect.Right, field_rect.Bottom, BACKGROUND_RED | BACKGROUND_INTENSITY);
	drawRect(field_rect.Left + 1, field_rect.Top + 1, field_rect.Right, field_rect.Bottom - 1, BACKGROUND_RED);
	drawCharRect(' ', field_rect.Left, field_rect.Top, field_rect.Right, field_rect.Bottom);
	short x = right_field + 6;
	short y = 4;
	drawRect(x - 1, y - 1, x + (FIELD_SIZE * CELL_WIDTH) + 1, y + (FIELD_SIZE * CELL_HEIGHT), BACKGROUND_RED);
	drawCharRect(' ', x - 1, y - 1, x + (FIELD_SIZE * CELL_WIDTH) + 1, y + (FIELD_SIZE * CELL_HEIGHT));
	drawRect(left_field + 5, 10, left_field + 43, 20, 0);
	const WCHAR title[] = { 0x1, 0x20, 0x412, 0x42B, 0x20, 0x41F, 0x420, 0x41E, 0x418, 0x413, 0x420, 0x410, 0x41B, 0x418, 0x20, 0x1 };
	writeText(title, left_field + 16, 11, sizeof(title) / sizeof(title[0]));
	fillAttribute(FOREGROUND_RED | FOREGROUND_INTENSITY, left_field + 16, 11, sizeof(title) / sizeof(title[0]));
	const WCHAR menu1[] = { 0x41D, 0x410, 0x427, 0x410, 0x422, 0x42C, 0x20, 0x417, 0x410, 0x41D, 0x41E, 0x412, 0x41E, 0x20, 0x41A, 0x41B, 0x410, 0x412, 0x418, 0x428, 0x410, 0x20, 0x45, 0x4E, 0x54, 0x45, 0x52 };
	writeText(menu1, left_field + 10, 15, sizeof(menu1) / sizeof(menu1[0]));
	fillAttribute(FOREGROUND_GREEN | FOREGROUND_INTENSITY, left_field + 10, 15, sizeof(menu1) / sizeof(menu1[0]));
	const WCHAR menu2[] = { 0x412, 0x42B, 0x425, 0x41E, 0x414, 0x20, 0x41A, 0x41B, 0x410, 0x412, 0x418, 0x428, 0x410, 0x20, 0x45, 0x53, 0x43 };
	writeText(menu2, left_field + 15, 18, sizeof(menu2) / sizeof(menu2[0]));
	fillAttribute(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY, left_field + 15, 18, sizeof(menu2) / sizeof(menu2[0]));
	WORD key;
	while ((key = FormClass::GetKey(getInput())) != WORD(~0)) {
		if (key == VK_RETURN) {
			start_game();
			MessageBeep((UINT)-1);
			Sleep(100);
			break;
		}
		else if (key == VK_ESCAPE) {//выход
			ExitProcess(0);
			break;
		}
	}
}