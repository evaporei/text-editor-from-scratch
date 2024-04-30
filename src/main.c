#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include "stringutil.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

struct StringList TEXT;
struct Font FONT;
unsigned char FONT_SIZE;
unsigned char FONT_WIDTH;
struct Color FONT_COLOR;
unsigned int CURSOR_ROW;
unsigned int CURSOR_COL;
unsigned int CURSOR_X;
unsigned int CURSOR_Y;
struct Color CURSOR_COLOR;
float CURSOR_BLINK_TIME;

void handle_user_input(void);
void draw_cursor(void);
void cursor_left(void);
void cursor_right(void);
void cursor_up(void);
void cursor_down(void);

int main(void) {

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Raylib Text Editor");
  SetTargetFPS(60);
  StringListInit(&TEXT, 128);
  TEXT.length = 1;
  FONT = LoadFont("./fonts/CascadiaMono.ttf");
  FONT_SIZE = FONT.baseSize;
  FONT_WIDTH = 10;
  FONT_COLOR = BLACK;
  CURSOR_ROW = 0;
  CURSOR_COL = 0;
  CURSOR_X = 0;
  CURSOR_Y = 0;
  CURSOR_COLOR = BLACK;
  CURSOR_BLINK_TIME = 0.5f;
  SetTextLineSpacing(FONT_SIZE + 1);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    // DrawTextEx(FONT, TEXT.value, (Vector2){0, 0}, FONT_SIZE, 1, FONT_COLOR);
    for (size_t i = 0; i < TEXT.length; i++) {
      struct String s = TEXT.items[i];
      DrawTextEx(FONT, s.value, (Vector2){0, i * (FONT_SIZE + 1)}, FONT_SIZE, 1, FONT_COLOR);
    }
    draw_cursor();
    EndDrawing();
    handle_user_input();
  }

  return 0;

}

struct String* get_current_string(void) {
  return &(TEXT.items[CURSOR_ROW]);
}

void handle_user_input(void) {
  char pressed_char = GetCharPressed();
  if (pressed_char) {
    StringAppend(get_current_string(), pressed_char);
    CURSOR_COL += 1;
  }
  switch (GetKeyPressed()) {
    case KEY_BACKSPACE:
      if (get_current_string()->length == 0) {
        // TODO: Breaks when editor is empty!
        TEXT.length -= 1;
        cursor_left();
        StringRemoveAt(get_current_string(), CURSOR_COL);
        // CURSOR_COL -= 1;
      } else {
        cursor_left();
        StringRemoveAt(get_current_string(), CURSOR_COL);
      }
      break;
    case KEY_ENTER:
      // StringAppend(get_current_string(), '\n');
      CURSOR_ROW += 1;
      CURSOR_COL = 0;
      TEXT.length += 1;
      break;
    case KEY_TAB:
      StringAppend(get_current_string(), ' ');
      StringAppend(get_current_string(), ' ');
      CURSOR_COL += 2;
      break;
    case KEY_LEFT:
      cursor_left();
      break;
    case KEY_RIGHT:
      cursor_right();
      break;
    case KEY_UP:
      cursor_up();
      break;
    case KEY_DOWN:
      cursor_down();
      break;
  }
  CURSOR_X = CURSOR_COL * 17; // TODO: 17 = FONT_SIZE / 2 + 1
  CURSOR_Y = CURSOR_ROW * (FONT_SIZE + 1);
}

void draw_cursor(void) {
  if ((int)(GetTime() / CURSOR_BLINK_TIME) % 2) {
    DrawLine(CURSOR_X + 1, CURSOR_Y, CURSOR_X + 1, CURSOR_Y + FONT_SIZE, CURSOR_COLOR);
  }
}

void cursor_left(void) {
  if (CURSOR_COL > 0) {
    CURSOR_COL -= 1;
    return;
  }
  if (CURSOR_ROW == 0) {
    return;
  }
  CURSOR_ROW -= 1;
  CURSOR_COL = get_current_string()->length;
}

void cursor_right(void) {
  CURSOR_COL += 1;
  if (CURSOR_COL > get_current_string()->length) {
    CURSOR_COL = 0;
    CURSOR_ROW += 1;
  }
}

void cursor_up(void) {
  if (CURSOR_ROW > 0) {
    CURSOR_ROW -= 1;
  } else {
    CURSOR_COL = 0;
  }
}

void cursor_down(void) {
  CURSOR_ROW += 1;
}
