#include "List_Menu.h"

//----------------------------------------------------------------------List_Menu class---------------------------------------------------------------------------//
List_Menu::List_Menu(){}

List_Menu::List_Menu(U8G2* Display, int ID){
  init(Display, ID);
}

void List_Menu::init(U8G2* Display, int ID){
  this->u8g2 = Display;
  this->menuID = ID;
  this->Initialized = true;
}

void List_Menu::drawScreen(){
  if(!isInitialized()){return;}
  //String daTing = this->optionArr[this->optionIndex]->getLabel();
  //Serial.println(daTing);
  //this->u8g2->drawStr(32, 10, daTing.c_str());
  //this->u8g2->drawStr(32, 10, "Is ya boi");
  switch(this->cursorIndex){
    case 0:
      this->u8g2->drawStr(32, 10, this->optionArr[this->optionIndex]->getLabel().c_str());
      this->u8g2->drawStr(32, 26, this->optionArr[this->optionIndex+1]->getLabel().c_str());
      this->u8g2->drawStr(32, 42, this->optionArr[this->optionIndex+2]->getLabel().c_str());
      break;
    case 1:
      this->u8g2->drawStr(32, 10, this->optionArr[this->optionIndex-1]->getLabel().c_str());
      this->u8g2->drawStr(32, 26, this->optionArr[this->optionIndex]->getLabel().c_str());
      this->u8g2->drawStr(32, 42, this->optionArr[this->optionIndex+1]->getLabel().c_str());
      break;
    case 2:
      this->u8g2->drawStr(32, 10, this->optionArr[this->optionIndex-2]->getLabel().c_str());
      this->u8g2->drawStr(32, 26, this->optionArr[this->optionIndex-1]->getLabel().c_str());
      this->u8g2->drawStr(32, 42, this->optionArr[this->optionIndex]->getLabel().c_str());
      break;
    default:
      Serial.println("Error. Cursor index is out of bounds");
  }
  this->u8g2->drawStr(8, (this->cursorIndex * 16 + 10), "-->");
  //Serial.println("New func here");
}

int List_Menu::decodeInput(int input){
  int returnValue = this->menuID;
  switch(input){
    case IR_KEY::UP_ARROW     :
      this->optionIndex = (this->optionCount+(this->optionIndex-1))%this->optionCount;
      Serial.print("New optionIndex is: "); Serial.println(this->optionIndex);
      if(this->cursorIndex == 0){
        if(this->optionIndex == (optionCount-1)){
          this->cursorIndex = 2;
        }
        else{
          this->cursorIndex = 0;
        }
      }
      else{
        this->cursorIndex--;
      }
      break;
    case IR_KEY::DOWN_ARROW   :
      this->optionIndex = (this->optionIndex+1)%this->optionCount;
      Serial.print("New optionIndex is: "); Serial.println(this->optionIndex);
      if(this->cursorIndex == 2){
        if(this->optionIndex == 0){
          this->cursorIndex = 0;
        }
        else{
          this->cursorIndex = 2;
        }
      }
      else{
        this->cursorIndex++;
      }
      break;
    case IR_KEY::RIGHT_ARROW  : Serial.println("Got Right Arrow"); returnValue = this->optionArr[this->optionIndex]->getNextMenu(); break;
    case IR_KEY::LEFT_ARROW   : Serial.println("Got Left Arrow"); break;
    //case IR_KEY::STAR         : Serial.println("Got Star"); returnValue = this->prevMenuID; break;
    default                   : returnValue = this->menuID;
  }
  return returnValue;
}


//---------------------------------------------------------------------List_Option class--------------------------------------------------------------------------//
List_Option::List_Option(){}
List_Option::List_Option(int nextMenu, String Label){
  init(nextMenu, Label);
}

void List_Option::init(int nextMenu, String Label){
  this->optionLabel = Label;
  //strcpy(this->optionLabel, optionLabel);
  this->nextMenu = nextMenu;
  this->Initialized = true;
}

String List_Option::getLabel(){return this->optionLabel;}


//-------------------------------------------------------------------Test_List_Menu class-------------------------------------------------------------------------//
//Test_List_Menu::Test_List_Menu(){}
/*Test_List_Menu::Test_List_Menu(U8G2* Display, int ID):List_Menu(Display, ID){
   this->optionArr[0] = new List_Option(0, "BaseMenu 0");
   this->optionArr[1] = new List_Option(1, "BaseMenu 1");
   this->optionArr[2] = new List_Option(2, "TestOption 0");
   this->optionArr[3] = new List_Option(2, "TestOption 1");
   this->optionArr[4] = new List_Option(2, "TestOption 2");
}*/
/*Test_List_Menu::Test_List_Menu(U8G2* Display, int ID){
  init(Display, ID);
}
void Test_List_Menu::init(U8G2* Display, int ID){
  this->u8g2 = Display;
  this->menuID = ID;
  this->optionArr[0] = new List_Option(0, "BaseMenu 0");
  this->optionArr[1] = new List_Option(1, "BaseMenu 1");
  this->optionArr[2] = new List_Option(2, "TestOption 0");
  this->optionArr[3] = new List_Option(2, "TestOption 1");
  this->optionArr[4] = new List_Option(2, "TestOption 2");
  this->Initialized = true;
}*/
