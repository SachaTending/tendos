#include <keyboard.h>
#include "printf.h"
#include "inlineasm.h"
#include "types.h"
#include "stdbool.h"

static char key_buffer[256];

#define SC_MAX 57

const char scancode_to_char[] = {
  '?', '?', '1', '2', '3', '4', '5',
  '6', '7', '8', '9', '0', '-', '=',
  '?', '?', 'Q', 'W', 'E', 'R', 'T',
  'Y', 'U', 'I', 'O', 'P', '[', ']',
  '?', '?', 'A', 'S', 'D', 'F', 'G',
  'H', 'J', 'K', 'L', ';', '\\', '`',
  '?', '\\\\', 'Z', 'X', 'C', 'V', 'B',
  'N', 'M', ',', '.', '/', '?', '?',
  '?', ' '
};

void print_backspace() {
    int newCursor = get_cursor() - 2;
    set_char_at_video_memory(' ', newCursor);
    set_cursor(newCursor);
}

#define BACKSPACE 0x0E

bool backspace(char buffer[]) {
    int len = string_length(buffer);
    if (len > 0) {
        buffer[len - 1] = '\0';
        return true;
    } else {
        return false;
    }
}

void keyboard_callback() {
    uint8_t scancode = inb(0x60);
    if (scancode > SC_MAX) return;

    if (scancode == BACKSPACE) {
        if (backspace(key_buffer)) {
            print_backspace();
        }
    } else {
        char letter = scancode_to_char[(int) scancode];
        append(key_buffer, letter);
        char str[2] = {letter, '\0'};
        printf(str);
    }
}

int string_length(char s[]) {
    int i = 0;
    while (s[i] != '\0') {
        ++i;
    }
    return i;
}

void append(char s[], char n) {
    int len = string_length(s);
    s[len] = n;
    s[len + 1] = '\0';
}

void shell() {
	int i = 0;
  char *stringabc = "TendOS\n";
	while (i == 0) {
    char status = inb(0x64);
    if (status & 1) {
      int abcdefgh = 0;
      while (stringabc[abcdefgh] != 0) {
          // write_serial(stringabc[abcdefgh]);
          abcdefgh++;
      };
      keyboard_callback();
    }
	}
}

void userland_setup()
{
	printf("Userland: Userland setuping...\n");
	printf("Userland: Userland setuped!\n");
}

void go_to_userland() {
	printf("Userland: Welcome to userland zone!\n");
	shell();
}