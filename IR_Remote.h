#ifndef MOI_IR_REMOTE_H
#define MOI_IR_REMORE_H

//#include <IRremoteESP8266.h>
#include <IRutils.h>


/*extern const int IR_KEY_1;
extern const int IR_KEY_2;
extern const int IR_KEY_3;
extern const int IR_KEY_4;
extern const int IR_KEY_5;
extern const int IR_KEY_6;
extern const int IR_KEY_7;
extern const int IR_KEY_8;
extern const int IR_KEY_9;
extern const int IR_KEY_0;
extern const int IR_KEY_STAR;
extern const int IR_KEY_HASH;
extern const int IR_KEY_UP_ARROW;
extern const int IR_KEY_DOWN_ARROW;
extern const int IR_KEY_RIGHT_ARROW;
extern const int IR_KEY_LEFT_ARROW;
extern const int IR_KEY_OK;*/

// Namespace inspiration (Because the above did not work): https://stackoverflow.com/questions/12042549/define-constant-variables-in-c-header
namespace IR_KEY{
  const int N1 = 0xFFA25D; //Old value: 0xFD00FF;
  const int N2 = 0xFF629D; //Old value: 0xFD807F;
  const int N3 = 0xFFE21D; //Old value: 0xFD40BF;
  const int N4 = 0xFF22DD; //Old value: 0xFD20DF; 
  const int N5 = 0xFF02FD; //Old value: 0xFDA05F;
  const int N6 = 0xFFC23D; //Old value: 0xFD609F;
  const int N7 = 0xFFE01F; //Old value: 0xFD10EF;
  const int N8 = 0xFFA857; //Old value: 0xFD906F;
  const int N9 = 0xFF906F; //Old value: 0xFD50AF;
  const int N0 = 0xFF9867; //Old value: 0xFDB04F;
  const int STAR = 0xFF6897; //Old value: 0xFD30CF;
  const int HASH = 0xFFB04F; //Old value: 0xFD708F;
  const int UP_ARROW = 0xFF18E7; //Old value: 0xFD8877;
  const int DOWN_ARROW = 0xFF4AB5; //Old value: 0xFD9867;
  const int RIGHT_ARROW = 0xFF5AA5; //Old value: 0xFD6897;
  const int LEFT_ARROW = 0xFF10EF; //Old value: 0xFD28D7;
  const int OK = 0xFF38C7; //Old value: 0xFDA857;
}

class IR_Remote{
  private:
    IRrecv* irrecv;
    decode_results results;
    bool Initialized = false;
  public:
    IR_Remote();
    IR_Remote(uint16_t pin);
    void init(uint16_t pin);
    bool isInitialized();
    int IR_Read();
};

#endif  // MOI_IR_REMORE_H
