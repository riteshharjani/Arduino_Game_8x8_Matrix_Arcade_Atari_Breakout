#ifndef __AR_SMILEY_H__
#define __AR_SMILEY_H__

/*
 * Note below smileys faces works with
 * LedControl arduino library
 */

byte smiley_happy[8] = {
	B00111100,
	B01000010,
	B10100101,
	B10000001,
	B10100101,
	B10011001,
	B01000010,
	B00111100,
};

byte smiley_sad[8] = {
	B00111100,
	B01000010,
	B10100101,
	B10000001,
	B10011001,
	B10100101,
	B01000010,
	B00111100,
};
#endif
