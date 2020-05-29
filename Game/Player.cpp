#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include "Player.h"

SimpleTimer timer_longpress;
Player *p;

int tid = -1;
int col;
char auth[] = "YourAuthProvidedByBlynk";
char ssid[] = "WifiName";
char pass[] = "WifiPassword";


Player *player_init() {
	p = new Player();
	Blynk.begin(auth, ssid, pass);
	return p;
}

/*
 * 1 means forward
 * 2 means backward
 * 0 means no move
 */
enum player_dir move_needed(int val, int pos)
{
	/* logic:
	 * in case of joystick the range of value is 0 - 1023
	 * since player could take up position from (left edge) 0 - 5.
	 * That means we need to check for ranges and see if pos already belongs
	 * to correct range. If yes, then no movement is needed
	 */
	int chunk = 1023/6;
	int div = val / chunk;
	pos += 1;
	if (div == (6 - pos))
		return MOVE_NONE;
	else if (div > (6 - pos))
		return MOVE_BACK;
	else
		return MOVE_FRONT;
}

void timer_cb(void *ptr) {
	enum player_dir dir;
	col = *(int*)ptr;
	dir = move_needed(col, p->pos_col);
	if (dir == MOVE_NONE) {
		//p->speed = 0;
//		tid = timer_longpress.setTimeout(10, timer_cb, &col);
		timer_longpress.restartTimer(tid);
		return;
	}
	p->move(dir);
	tid = timer_longpress.setTimeout(10, timer_cb, &col);
	Serial.print("in timer_cb for col=  ");
	Serial.println(col);
}

BLYNK_WRITE(V2) {
	enum player_dir dir;
	col = param[1].asInt();
	dir = move_needed(col, p->pos_col);
	if (col - p->pos_prev > 0)
		p->speed = 1;
	else
		p->speed = -1;
	p->pos_prev = col;
	if (dir == MOVE_NONE)
		return;
	p->move(dir);
	if (tid == -1) {
		Serial.println("setup timer ");
		tid = timer_longpress.setTimeout(10, timer_cb, &col);
	} else {
		timer_longpress.deleteTimer(tid);
		tid = timer_longpress.setTimeout(10, timer_cb, &col);
	}
}

void Player::run() {
	Blynk.run();
	timer_longpress.run();
}
