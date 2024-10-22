// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Only for educational purposes. I am not responsible for damage to devices or misuse for illegal activities
// arduino DUE: execution of windows built-in functions over native USB port
// written by: bodinhalace
// V: 1.0
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#include <Keypad.h>
#include "Keyboard.h"

// keypad 
const byte radky = 4;
const byte sloupce = 4;
char keys[radky][sloupce] = {
  {'*', '7', '4', '1'},
  {'0', '8', '5', '2'},
  {'#', '9', '6', '3'},
  {'D', 'C', 'B', 'A'}
  
};

byte pinyRadku[radky] = {5, 4, 3, 2};      //2, 3, 4, 5
byte pinySloupcu[sloupce] = {6, 7, 8, 9};  //6, 7, 8, 9
Keypad klavesnice = Keypad( makeKeymap(keys), pinyRadku, pinySloupcu, radky, sloupce);
// end keypad

// keyboard
char WIN_KEY=KEY_LEFT_GUI; //Windows key 
char ENTER=KEY_RETURN; // Enter key 
char ALT = KEY_LEFT_ALT; // Alt key
char F4 = KEY_F4; //fnc key F4
char SHIFT = KEY_LEFT_SHIFT;
char CTRL = KEY_LEFT_CTRL;
int WAIT = 150; // time for adjust 
int WAIT_X = 50; // typing speed
// end kyboard

// win control functions

void open_cmd(){
  // btn 1
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

  
void open_explorer(){
  // btn2
  Keyboard.press(WIN_KEY);
  Keyboard.press('r');
  delay(WAIT);
  Keyboard.release(WIN_KEY);
  Keyboard.release('r');
  delay(WAIT);
  Keyboard.println("explorer");
  delay(WAIT);
  Keyboard.press(ENTER);
  delay(WAIT);
  Keyboard.release(ENTER);
  }

void open_taskmgr(){
  // btn 3
  Keyboard.press(WIN_KEY);
  Keyboard.press('r');
  delay(WAIT);
  Keyboard.release(WIN_KEY);
  Keyboard.release('r');
  delay(WAIT);
  Keyboard.println("taskmgr");
  delay(WAIT);
  Keyboard.press(ENTER);
  delay(WAIT);
  Keyboard.release(ENTER);
  }

void open_edge(){
  //btn 4
  Keyboard.press(WIN_KEY);
  Keyboard.press('r');
  delay(WAIT);
  Keyboard.release(WIN_KEY);
  Keyboard.release('r');
  delay(WAIT);
  Keyboard.println("msedge");
  delay(WAIT);
  Keyboard.press(ENTER);
  delay(WAIT);
  Keyboard.release(ENTER);
  }

void open_ffx(){
  // btn 5 (open firefox if installed)
  Keyboard.press(WIN_KEY);
  Keyboard.press('r');
  delay(WAIT);
  Keyboard.release(WIN_KEY);
  Keyboard.release('r');
  delay(WAIT);
  Keyboard.println("firefox");
  delay(WAIT);
  Keyboard.press(ENTER);
  delay(WAIT);
  Keyboard.release(ENTER);
  }    

void open_y2b(){
  // btn 6 
  Keyboard.press(WIN_KEY);
  Keyboard.press('r');
  delay(WAIT);
  Keyboard.release(WIN_KEY);
  Keyboard.release('r');
  delay(WAIT);
  Keyboard.println("https://www.youtube.com");
  delay(WAIT);
  Keyboard.press(ENTER);
  delay(WAIT);
  Keyboard.release(ENTER);
  }

void open_cpl(){
  // btn 7
  Keyboard.press(WIN_KEY);
  Keyboard.press('r');
  delay(WAIT);
  Keyboard.release(WIN_KEY);
  Keyboard.release('r');
  delay(WAIT);
  Keyboard.println("control");
  delay(WAIT);
  Keyboard.press(ENTER);
  delay(WAIT);
  Keyboard.release(ENTER);
  }

void open_notepad(){
  //btn 8 
  Keyboard.press(WIN_KEY);
  Keyboard.press('r');
  delay(WAIT);
  Keyboard.release(WIN_KEY);
  Keyboard.release('r');
  delay(WAIT);
  Keyboard.println("notepad");
  delay(WAIT);
  Keyboard.press(ENTER);
  delay(WAIT);
  Keyboard.release(ENTER);
  }

void ping_g_dns(){
  // btn 9
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
  delay(500);
  
  Keyboard.press('p');
  Keyboard.release('p');
  delay(WAIT_X);
  Keyboard.press('i');
  Keyboard.release('i');
  delay(WAIT_X);
  Keyboard.press('n');
  Keyboard.release('n');
  delay(WAIT_X);
  Keyboard.press('g');
  Keyboard.release('g');
  delay(WAIT_X);
  Keyboard.press(' ');
  Keyboard.release(' ');
  delay(WAIT_X);
  Keyboard.press(SHIFT);
  Keyboard.press('8');
  Keyboard.release('8');
  Keyboard.release(SHIFT);
  delay(WAIT_X);
  Keyboard.press('.');
  Keyboard.release('.');
  delay(WAIT_X);
  Keyboard.press(SHIFT);
  Keyboard.press('8');
  Keyboard.release('8');
  Keyboard.release(SHIFT);
  delay(WAIT_X);
  Keyboard.press('.');
  Keyboard.release('.');
  delay(WAIT_X);
  Keyboard.press(SHIFT);
  Keyboard.press('8');
  Keyboard.release('8');
  Keyboard.release(SHIFT);
  Keyboard.press('.');
  Keyboard.release('.');
  delay(WAIT_X);
  Keyboard.press(SHIFT);
  Keyboard.press('8');
  Keyboard.release('8');
  Keyboard.release(SHIFT);
  
  
  delay(WAIT);
  Keyboard.press(ENTER);
  //delay(WAIT);
  Keyboard.release(ENTER);



  }      


void altf4(){
  // btn A (close window)
  Keyboard.press(ALT);
  delay(100);
  Keyboard.press(F4);
  //delay(100);
  Keyboard.release(ALT);
  Keyboard.release(F4);
  
  }

void winm(){
  // btn B (minimize all windows)
  Keyboard.press(WIN_KEY);
  delay(100);
  Keyboard.press('m');
  //delay(100);
  Keyboard.release(WIN_KEY);
  Keyboard.release('m');
  
  }
  
void winl(){
  // btn C (lock screen)
  Keyboard.press(WIN_KEY);
  delay(100);
  Keyboard.press('l');
  //delay(100);
  Keyboard.release(WIN_KEY);
  Keyboard.release('l');
  
  }

void osk(){
  // btn D (on screen keyboard)
  Keyboard.press(WIN_KEY);
  Keyboard.press('r');
  delay(WAIT);
  Keyboard.release(WIN_KEY);
  Keyboard.release('r');
  delay(WAIT);
  Keyboard.println("osk");
  delay(WAIT);
  Keyboard.press(ENTER);
  delay(WAIT);
  Keyboard.release(ENTER);
  
  }


void log_me_in(){
  //btn * 
  // password define example
  delay(WAIT_X);
  Keyboard.press('A');
  Keyboard.release('A');
  delay(WAIT_X);
  Keyboard.press('b');
  Keyboard.release('b');
  delay(WAIT_X);
  Keyboard.press('c');
  Keyboard.release('c');
  delay(WAIT_X);
  Keyboard.press('d');
  Keyboard.release('d');
  delay(WAIT_X);
  Keyboard.press('e');
  Keyboard.release('e');
  delay(WAIT_X);
  Keyboard.press('f');
  Keyboard.release('f');
  delay(WAIT_X);
  Keyboard.press(SHIFT); // holding shift while entering numbers
  Keyboard.press('0');
  Keyboard.release('0');
  delay(WAIT_X);
  Keyboard.press('1');
  Keyboard.release('1');
  delay(WAIT_X);
  Keyboard.press('0');
  Keyboard.release('0');
  delay(WAIT_X);
  Keyboard.press('1');
  Keyboard.release('1');
  Keyboard.release(SHIFT); // release shift
  // end of password define example

  //enter press to confirm password
  delay(WAIT);
  Keyboard.press(ENTER);
  Keyboard.release(ENTER);
   //output = Abcdef0101
  }   

// BTN # = ENTER


// end win control 






//------------------------main functions------------------------------
void setup() {  
  Serial.begin(9600);
}

void loop() {
  char klavesa = klavesnice.getKey();
   /* if (klavesa=='1') {
    //Serial.print("Stisknuta klavesa: ");
    //Serial.println(klavesa);
  } */
  // ------------------------------------
 
   if (klavesa=='0') {
     // require press number 1 before
     Keyboard.println("ipconfig /all");
     Keyboard.press(ENTER);
     delay(WAIT);
     Keyboard.release(ENTER); 
  }
   
   
   if (klavesa=='1') {
    open_cmd();
  }

   if (klavesa=='2') {
    open_explorer();
  }

   if (klavesa=='3') {
    open_taskmgr();
  }

   if (klavesa=='4') {
    open_edge();
  }

   if (klavesa=='5') {
    open_ffx();
  }

   if (klavesa=='6') {
    open_y2b();
  }

   if (klavesa=='7') {
    open_cpl();
  }

   if (klavesa=='8') {
    open_notepad();
  }

   if (klavesa=='9') {
   ping_g_dns(); 
  }  

   if (klavesa=='A') {
    altf4();
  }

   if (klavesa=='B') {
    winm();
  }

   if (klavesa=='C') {
    winl();
  }
 
   if (klavesa=='D') {
    osk(); 
  }
   if (klavesa=='*') {
    log_me_in();
  } 
  
   if (klavesa=='#') {
    //assigned to press enter key
     Keyboard.press(ENTER);
     Keyboard.release(ENTER);
  } 



}
