#include "Breakout.h"
#include "Smileys.h"

void Breakout::setup() {
	ball = new Ball();
	stars = new Stars();
	player = player_init();

	lc.shutdown(0, false);
	lc.setIntensity(0, 2);
	lc.clearDisplay(0);

	player->setup(&lc);
	ball->setup(&lc);
	stars->setup(&lc);
	draw();
}

void Breakout::check_collision_with_player()
{
	// if middle is hit
	if (ball->pos_col == player->pos_col + 1) {
		ball->dir_row = 0;
	} else if (ball->dir_row == 0) {
		// if either side of the player is hit
		if (ball->pos_col < player->pos_col + 1)
			ball->dir_row = -1;
		else
			ball->dir_row = 1;
	}

	// change direction of ball to up.
	ball->dir_col = -1;
}

void Breakout::check_collision_with_stars() {
	if (ball->pos_row < 3)
		stars->update(ball->pos_row, ball->pos_col);
}

void Breakout::check_collision_with_walls() {

	// check if we hit roof
	if (ball->pos_row == 0 && ball->dir_col == -1)
		ball->dir_col = 1;

	// check if we hit side walls
	if (ball->pos_col == 0 && ball->dir_row == -1)
		ball->dir_row = 1;
	if (ball->pos_col == 7 && ball->dir_row == 1)
		ball->dir_row = -1;
}

enum GameState Breakout::check_collision() {

	if (ball->pos_row == 7 && ball->dir_col == 1 &&
	    (ball->pos_col >= player->pos_col - 1) && (ball->pos_col <= player->pos_col + 3)) {
		// move the ball up if it's stuck inside the player
		// Without this particular line of code, game will never get
		// end.
		ball->pos_row = 6;
		check_collision_with_player();
	}

	// comment this to avoid game_over
	if (ball->pos_row == 7 && ball->dir_col == 1)
		return GAME_OVER;

	// uncomment this to avoid game over
//	if (ball->pos_row == 7 && ball->dir_col == 1)
//		ball->dir_col = -1;

	check_collision_with_stars();
	check_collision_with_walls();
	if (stars->count == 0)
		return GAME_WON;
	return GAME_PLAY;
}

enum GameState Breakout::run() {
	enum GameState ret;
	ball->run();
	ret = (enum GameState)check_collision();
	if (ret == GAME_OVER || ret == GAME_WON) {
		return ret;
	}
	draw();
	player->run();
	return ret;
}

void Breakout::game_over() {
	lc.clearDisplay(0);
	for (int i = 0; i < 8; i++) {
		lc.setRow(0, i, smiley_sad[i]);
	}
}

void Breakout::game_won() {
	lc.clearDisplay(0);
	for (int i = 0; i < 8; i++) {
		lc.setRow(0, i, smiley_happy[i]);
	}
}
