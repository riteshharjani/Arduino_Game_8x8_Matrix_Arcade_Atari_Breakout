#ifndef __AR_PLAYER_H__
#define __AR_PLAYER_H__
#include <LedControl.h>

enum player_dir {
	MOVE_NONE,
	MOVE_FRONT,
	MOVE_BACK,
};

class Player {
public:
	/*
	 * consider length of player to be 3.
	 * and pos_row is the leftmost end of it.
	 */
	int pos_row = 7;
	int pos_col = 2;
	int pos_prev;
	byte bval;
	int speed = 0;
	LedControl *lc;

	Player() {
		//
	}

	void run();

	void setup(LedControl *ptr) {
		lc = ptr;
		update();
	}

	void update() {
		byte val = 0;
		for (int i = pos_col; i < pos_col + 3; i++) {
			val |= (1 << (7 - i));
		}
		//lc->setRow(0, pos_row, val);
		bval = val;
	}

	/*
	 * range of this x can come from 0 - 1023
	 */
	void move(enum player_dir dir) {
		if (dir == MOVE_FRONT) {
			pos_col++;
			speed = 1;
		} else if (dir == MOVE_BACK) {
			pos_col--;
			speed = -1;
		}
		if (pos_col < 0)
			pos_col = 0;
		else if (pos_col > 5)
			pos_col = 5;
		Serial.print("Player pos ");
		Serial.print(pos_col);
		Serial.print(" - ");
		Serial.println(pos_col + 2);
		update();
	}
	
	void fill(byte *board, int size) {
		board[pos_row] = bval;
	}
};

Player *player_init();

#endif
