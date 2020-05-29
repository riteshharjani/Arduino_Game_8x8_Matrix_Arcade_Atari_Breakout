#ifndef __AR_BALL_H__
#define __AR_BALL_H__

class Ball {
public:
	int pos_row;
	int pos_col;
	int dir_row;
	int dir_col;
	int speed;
	LedControl *lc;

	Ball() {
		pos_row = 5;
		pos_col = 3;
		dir_row = 0;
		dir_col = 1;
		speed = 200;
	}

	void setup(LedControl *ptr) {
		lc = ptr;
	}

	void display(bool var = false) {
		if (!var)
			lc->setLed(0, pos_row, pos_col, 0);
		else
			lc->setLed(0, pos_row, pos_col, 1);
	}

	void fill(byte *board, int size) {
		board[pos_row] |= 1 << (7 - pos_col);
	}

	void run() {
		pos_row += dir_col;
		pos_col += dir_row;

		Serial.print("Ball pos ");
		Serial.print(pos_row);
		Serial.print(" ");
		Serial.println(pos_col);
	}
};
#endif
