#include "Menus.h"

//------------------------------------------------------------------------Menu class------------------------------------------------------------------------------//
Menu::Menu(){}

Menu::Menu(U8G2* Display, int ID){
  init(Display, ID);
}

void Menu::init(U8G2* Display, int ID){
  this->u8g2 = Display;
  this->menuID = ID;
  this->Initialized = true;
}

bool Menu::isInitialized(){
  if(!this->Initialized){Serial.println("This Menu object is not initialized");}
  return this->Initialized;
}

void Menu::drawScreen(){
  if(!isInitialized()){return;}
  // Later when a display manager is implemented remove the clear and send buffer from this class, and let the display manager do it instead.
  // Maybe also make a pointer to a U8G2 object an argument of this method instead of an attribute of the entire class. (Done?)
  //this->u8g2->clearBuffer();
  //this->u8g2->drawStr(16, 26, "Welcome to the base");
  //this->u8g2->drawStr(16, 42, "Menu class!!");
  this->u8g2->drawStr(16, 26, "Welcome to menu");
  this->u8g2->setCursor(62,42);
  this->u8g2->print(this->menuID);
  //this->u8g2->sendBuffer();
}

int Menu::decodeInput(int input){
  int returnValue = this->menuID;
  switch(input){
    case IR_KEY::RIGHT_ARROW  : Serial.println("Got Right Arrow"); returnValue = (this->menuID+1)%3; break;
    case IR_KEY::LEFT_ARROW   : Serial.println("Got Left Arrow"); returnValue = (3+(this->menuID-1))%3; break;
    case IR_KEY::STAR         : Serial.println("Got Star"); returnValue = this->prevMenuID; break;
    default                   : returnValue = this->menuID;
  }
  return returnValue;
}

int Menu::getMenuID(){return this->menuID;}

void Menu::setPrevMenuID(int ID){this->prevMenuID = ID;}




//------------------------------------------------------------------------MenuOption class------------------------------------------------------------------------//

MenuOption::MenuOption(){}
MenuOption::MenuOption(int nextMenu){init(nextMenu);}
void MenuOption::init(int nextMenu){this->nextMenu = nextMenu;}

bool MenuOption::isInitialized(){
  if(!this->Initialized){Serial.println("This MenuOption object is not initialized");}
  return this->Initialized;
}

int MenuOption::getNextMenu(){return this->nextMenu;}
