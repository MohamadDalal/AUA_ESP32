#include "IR_Remote.h"

// Included here instead of the header to avoide double declaration.
/*extern const int IR_KEY_1 = 0xFFA25D; //Old value: 0xFD00FF;
extern const int IR_KEY_2 = 0xFF629D; //Old value: 0xFD807F;
extern const int IR_KEY_3 = 0xFFE21D; //Old value: 0xFD40BF;
extern const int IR_KEY_4 = 0xFF22DD; //Old value: 0xFD20DF; 
extern const int IR_KEY_5 = 0xFF02FD; //Old value: 0xFDA05F;
extern const int IR_KEY_6 = 0xFFC23D; //Old value: 0xFD609F;
extern const int IR_KEY_7 = 0xFFE01F; //Old value: 0xFD10EF;
extern const int IR_KEY_8 = 0xFFA857; //Old value: 0xFD906F;
extern const int IR_KEY_9 = 0xFF906F; //Old value: 0xFD50AF;
extern const int IR_KEY_0 = 0xFF9867; //Old value: 0xFDB04F;
extern const int IR_KEY_STAR = 0xFF6897; //Old value: 0xFD30CF;
extern const int IR_KEY_HASH = 0xFFB04F; //Old value: 0xFD708F;
extern const int IR_KEY_UP_ARROW = 0xFF18E7; //Old value: 0xFD8877;
extern const int IR_KEY_DOWN_ARROW = 0xFF4AB5; //Old value: 0xFD9867;
extern const int IR_KEY_RIGHT_ARROW = 0xFF5AA5; //Old value: 0xFD6897;
extern const int IR_KEY_LEFT_ARROW = 0xFF10EF; //Old value: 0xFD28D7;
extern const int IR_KEY_OK = 0xFF38C7; //Old value: 0xFDA857;*/

IR_Remote::IR_Remote(){}

IR_Remote::IR_Remote(uint16_t pin){
  //IRrecv irrecv(pin);
  //this->irrecv = new IRrecv(pin);
  //this->irrecv->enableIRIn();
  init(pin);
}

void IR_Remote::init(uint16_t pin){
  this->irrecv = new IRrecv(pin);

  this->irrecv->enableIRIn();
  this->Initialized = true;
}

bool IR_Remote::isInitialized(){
  if(!this->Initialized){Serial.println("This IR_Remote object is not initialized");}
  return this->Initialized;
}

int IR_Remote::IR_Read()
{
  if(!isInitialized()){return -1;}
  int TempReturn = 0;
  if (this->irrecv->decode(&results)) {
    if (results.value == 0xFFFFFFFFFFFFFFFF)
    {
      TempReturn = 0xFFFFFFFFFFFFFFFF;
    }
    else
    {
      switch(results.value)
      {
        case IR_KEY::N1           : TempReturn = IR_KEY::N1;              break;
        case IR_KEY::N2           : TempReturn = IR_KEY::N2;              break;
        case IR_KEY::N3           : TempReturn = IR_KEY::N3;              break;
        case IR_KEY::N4           : TempReturn = IR_KEY::N4;              break;
        case IR_KEY::N5           : TempReturn = IR_KEY::N5;              break;
        case IR_KEY::N6           : TempReturn = IR_KEY::N6;              break;
        case IR_KEY::N7           : TempReturn = IR_KEY::N7;              break;
        case IR_KEY::N8           : TempReturn = IR_KEY::N8;              break;
        case IR_KEY::N9           : TempReturn = IR_KEY::N9;              break;
        case IR_KEY::N0           : TempReturn = IR_KEY::N0;              break;
        case IR_KEY::STAR         : TempReturn = IR_KEY::STAR;           break;
        case IR_KEY::HASH         : TempReturn = IR_KEY::HASH;           break;
        case IR_KEY::UP_ARROW     : TempReturn = IR_KEY::UP_ARROW;       break;
        case IR_KEY::DOWN_ARROW   : TempReturn = IR_KEY::DOWN_ARROW;     break;
        case IR_KEY::RIGHT_ARROW  : TempReturn = IR_KEY::RIGHT_ARROW;    break;
        case IR_KEY::LEFT_ARROW   : TempReturn = IR_KEY::LEFT_ARROW;     break;
        case IR_KEY::OK           : TempReturn = IR_KEY::OK;             break;
      }
      //TempReturn = results.value;
    }
    this->irrecv->resume();
  }
  return TempReturn;
}
