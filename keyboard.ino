#include "MyKeyboard.h"

const int col[] = {2, 3, 15, 14};
const int row[] = {4, 6, 8, 16};
const int rowLED[] = {5, 7, 9, 10};
unsigned int counter = 0;
bool pre[4][4];
char str[][4][4] = 
{
  {"a", "b", "c", "d"},
  {"e", "f", "g", "h"},
  {"i", "j", "k", "l"},
  {"m", "n", "o", "p"},
};
// -1は単純なpressではないことを示す
int keys[4][4] = 
{
  {KEY_F1, KEY_F2, KEY_F3, KEY_F4},
  {KEY_F5, KEY_F6, KEY_F7, KEY_F8},
  {KEY_F9, KEY_F10, KEY_F11, KEY_F12},
  {0xCE, -1, KEY_LEFT_GUI, 0xD4},
};
// 0xCEはprint screen, 0xD4はdel

bool LED[4][4] =
{
  {true, false, true, false},
  {false, true, false, true},
  {true, false, true, false},
  {false, true, false, true},
};
bool LED2[4][4] =
{
//  {true, true, true, true},
  {false, false, false, false},
  {false, false, false, false},
  {false, false, false, false},
  {false, false, false, false},
};

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(col[i], OUTPUT);
    digitalWrite(col[i], LOW);
    pinMode(row[i], INPUT);
    pinMode(rowLED[i], OUTPUT);
    digitalWrite(rowLED[i], LOW);
    for (int j = 0; j < 4; j++) {
      pre[j][i] = false;
    }
  }
}

void loop() {
  counter++;
  for (int i = 0; i < 4; i++) {
    digitalWrite(col[i], HIGH);
    // LED点灯
    for (int j = 0; j < 4; j++) {
      digitalWrite(rowLED[j], !LED2[j][i]);
      /*
      if (counter % 600 < 300)
        digitalWrite(rowLED[j], LED[j][i]);
      else
        digitalWrite(rowLED[j], !LED[j][i]);
      */
    }
    // キー状態読み取り
    for (int j = 0; j < 4; j++) {
      const bool stat = digitalRead(row[j]);
//      if (stat && !pre[j][i]) {
//        Keyboard.print(str[j][i]);
//      }
      if (stat && !pre[j][i]) {
        if (keys[j][i] >= 0) {
          Keyboard.press(keys[j][i]);
        } else {
          if (j == 3 && i == 1) {
            Keyboard.press(0x80); // ctrl
            Keyboard.press(0xB0); // enter
          } else if (j == 3 && i == 2) {
            Keyboard.pressRaw(0x35); // zenkaku
          }
        }
      }
      if (!stat && pre[j][i]){
        if (keys[j][i] >= 0) {
          Keyboard.release(keys[j][i]);
        } else {
          if (j == 3 && i == 1) {
            Keyboard.release(0x80); // ctrl
            Keyboard.release(0xB0); // enter
          } else if (j == 3 && i == 2) {
            Keyboard.releaseRaw(0x35); // zenkaku
          }
        }
      }
      pre[j][i] = stat;
    }
    // LED消灯
    for (int j = 0; j < 4; j++) {
      digitalWrite(rowLED[j], HIGH);
    }
    digitalWrite(col[i], LOW);
  }
}
