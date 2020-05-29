#ifndef __AR_STARS_H__
#define __AR_STARS_H__

class Stars {
public:
	byte locs[3];
	int count;

	Stars() {
		locs[0] = B11111111;
		locs[1] = B11111111;
		locs[2] = B11111111;
		count = 8 * 3;
	}


	void setup(void *ptr) {
		// do nothing;
	}

	void fill(byte *board, int size) {
		for (int i = 0; i < 3; i++) {
			board[i] = locs[i];
		}
	}

	void update(int row, int col) {
		if (locs[row] & (1 << (7 - col)))
			count--;
		locs[row] &= ~(1 << (7 - col));
		Serial.print("Stars count = ");
		Serial.println(count);
	}
};
#endif
