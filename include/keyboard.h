
#ifndef KKEYPRESS_H
#define KKEYPRESS_H

typedef _Bool bool;

#include <stdint.h>

extern unsigned char us_scancode_directory[];

enum scancode_directory_name {
	SCANCODED_ESC = 0,
	SCANCODED_UP = 5, SCANCODED_DOWN = 6, SCANCODED_LEFT = 7, SCANCODED_RIGHT = 8,
	SCANCODED_INS = 9, SCANCODED_DEL = 10,
	SCANCODED_HOME = 11, SCANCODED_END = 12,
	SCANCODED_PAGEUP = 13, SCANCODED_PAGEDOWN = 14,
	SCANCODED_F1 = 15,
	SCANCODED_CAPS = 27, SCANCODED_NUML = 28, SCANCODED_SCROL = 29, 
	SCANCODED_CTRL = 30,
	SCANCODED_LSHIFT = 31, SCANCODED_RSHIFT = 32,
	SCANCODED_LMETA = 33, SCANCODED_RMETA = 34,
	SCANCODED_ALT = 35
};
enum keyboard_modifier_name {
	MODIFIER_CTRL, MODIFIER_ALT, MODIFIER_SHIFT, MODIFIER_META, MODIFIER_CAPS, MODIFIER_NUM, MODIFIER_SCROLL
};

char keycodeFromScancode(uint8_t scancode);
char keyboard_getCapital(char c);

int keyboard_open();
uint8_t keyboard_get();
int keyboard_down(uint8_t scancode);
bool keyboard_modifier(enum keyboard_modifier_name n);

#endif