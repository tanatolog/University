#pragma once

#include "FormClass.h"

#define  T_COLUMNS    16
#define  T_ROWS       18
#define  CELL_WIDTH   3
#define  CELL_HEIGHT  2
#define  WIDTH_SIZE   (T_COLUMNS * CELL_WIDTH)
#define  FIELD_SIZE   4
#define  FIELD_COLS   (T_COLUMNS * CELL_WIDTH)
#define  FIELD_ROWS   (T_ROWS * CELL_HEIGHT)
#define  CELL_NONE    0x0
#define  CELL_BUSY    0x1
#define  CELL_MOVE    0x3
#define  CELL_BOOM    0x5
#define  C_T_MOVE     0x2
#define  DELAY_GAME   200
#define  MOVE_COLOR   (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_INTENSITY)
#define  BOX_COLOR    (FOREGROUND_RED | FOREGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define  BOOM_COLOR   (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_GREEN)
#define  COLOR_WHITE  (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_GREEN)
#define  EOF_FIGURE   0xFF 
#define  isKeyState(vk)  (GetAsyncKeyState((vk)) & 0x8000)

class GameTetris : public FormClass {
private:
	CHAR_INFO  field[FIELD_ROWS * FIELD_COLS];
	SMALL_RECT field_rect;
	int   field_boxs[T_ROWS][T_COLUMNS];
	int   field_cnt;
	COORD field_size;
	int   figure[FIELD_SIZE][FIELD_SIZE];
	int   next_figure[FIELD_SIZE][FIELD_SIZE];
	DWORD move_time;
	DWORD delay;
	BOOL  move_figure;
	BOOL  once_figure;
	short left_field;
	short right_field;
	short figure_x;
	short figure_y;
	void OnCreate(void);
	void OnKeyDown(WORD);
	void OnKeyUp(WORD);
	void OnProcess(void);
	void init_field(void);
	void draw_field(void);
	void draw_play(void);
	void draw_box(short x, short y, WORD color);
	void put_box(short x, short y, WORD color);
	void update_frame(void);
	void build_figure(void);
	BOOL move_object(int x, int y);
	void put_figure(int flag);
	void fieldText(LPCSTR s, DWORD n, short x, short y);
	void fieldColor(WORD color, short x, short y, DWORD n);
	int  is_move_figure(int dx, int dy);
	BOOL rotate(void);
	BOOL is_game_over(void);
	void boom_boxs_line(void);
	int  find_line(int& last);
	void draw_next_figure(void);
	void game_over(void);
	void start_game(void);
	void title_game(void);
	void getAsyncMessage(void);
	void swap_int(int& a, int& b);
	void reverse_vert(int src[][FIELD_SIZE]);
	void transponse(int dst[][FIELD_SIZE], int src[][FIELD_SIZE]);
	void transponse(int src[][FIELD_SIZE]);
	WORD get_color(int type);
	BOOL isKeyEvent(void);
public:
	GameTetris(void);
	DWORD CreateMainForm(void);
	void run(DWORD msec);
};
