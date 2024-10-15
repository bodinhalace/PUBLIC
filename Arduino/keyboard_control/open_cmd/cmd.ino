#include "Keyboard.h"
//
// ard DUE open cmd over native USB port
//written by bodinhalace 

char WIN_KEY=KEY_LEFT_GUI; //Windows key 
char ENTER=KEY_RETURN; // Enter key 
int WAIT = 150; // time for adjust 

void open_cmd(){
  Keyboard.press(WIN_KEY);
  Keyboard.press('r');
  delay(WAIT);
  Keyboard.release(WIN_KEY);
  Keyboard.release('r');
  delay(WAIT);
  Keyboard.println("cmd");
  delay(WAIT);
  Keyboard.press(ENTER);
  delay(WAIT);
  Keyboard.release(ENTER);
  }

void setup() {
}


void loop() {
  delay(3000);
  open_cmd();
  delay(60000);//1 minute before repetition

}
