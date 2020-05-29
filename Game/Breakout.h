#ifndef __AR_BREAKOUT_H__
#define __AR_BREAKOUT_H__

#include <LedControl.h>
#include "Player.h"
#include "BallBounce.h"
#include "Stars.h"
#include "Hardware_config.h"
#include "Game.h"

class Breakout {
public:

	const int data = DATA_PIN;
	const int clk = CLK_PIN;
	const int cs = CS_PIN;
	byte board[8] = {0};

	Ball *ball;
	Player *player;
	Stars *stars;
	LedControl lc = LedControl(data, clk, cs, 1);

	Breakout() {
		//
	}

	// to setup all object types (like ball, player, stars)
	// also setup the ledcontrol object for using it in draw method
	void setup();

	// run is the game entry point
	enum GameState run();

	// below two are two draw smiley faces on screen based on won/lose
	void game_over();
	void game_won();

	// To check collision of ball with other objects and return GameSate
	enum GameState check_collision();
	void check_collision_with_player();
	void check_collision_with_stars();
	void check_collision_with_walls();

	// this adds up ball, player and stars location into memory buffer
	// pointed by board[8]
	// TODO: optimize this so that everytime no need of doing reset
	// of this buffer
	void get_all_locations() {
		byte *addr = &board[0];

		/* reset board to null */
		for (byte i = 0; i < 8; i++) {
			addr[i] = B00000000;
		}

		stars->fill(addr, 8);
		player->fill(addr, 8);
		ball->fill(addr, 8);
	}

	// This draws all the objects on the 8x8 LED matrix
	void draw() {
		get_all_locations();
		for (int i = 0; i < 8; i++) {
			lc.setRow(0, i, board[i]);
		}
	}
};
#endif
