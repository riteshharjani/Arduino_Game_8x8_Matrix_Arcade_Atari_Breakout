#include "Breakout.h"

enum GameState state = GAME_STOP;
Breakout game;

void setup() {
	Serial.begin(115200);
	Serial.println("Starting Breakout");
	game.setup();
	Serial.println("Play");
}

/*
 * TODO: To restart the game as of now reset of arduino board
 * is used to play it again.
 * 1. Fix this by giving some option to user.
 * 2. No Game score added.
 * 3. Add more game levels by increasing speed.
 * 4. Let stars also provide a deflection to ball instead of we passing it
 *    through.
 * 5. Add more game options to select??
 */
void loop() {
	Serial.print("game state ");
	Serial.println(state);
	switch (state) {
	case GAME_OVER:
		game.game_over();
		break;
	case GAME_STOP:
		state = game.run();
		break;
	case GAME_PLAY:
		state = game.run();
		break;
	case GAME_WON:
		game.game_won();
		break;
	default:
		Serial.println("default state ??");
		break;
	}
	delay(100);
}
