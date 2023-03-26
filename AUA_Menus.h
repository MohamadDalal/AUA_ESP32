#ifndef MOI_AUA_MENUS_H
#define MOI_AUA_H

#include <Arduino.h>
#include "AUA.h"
#include "Menus.h"
#include "List_Menu.h"
//#include "IR_Remote.h"

class AUA_Menu_Manager;
class AUA_Main_Menu;
class AUA_User_Info_Menu;
class AUA_Recent_Menu;

class AUA_Menu_Manager{
  private:
    bool active;
    bool Initialized;
    Menu MenuList[6];
    int currentMenu = 0;
    int previousMenu = 0;
    
  public:
    AUA_Menu_Manager();
    void init();
    bool isInitialized();
    void activate();
    void inactivate();
    bool isActive();
    void drawScreen();
    void decodeInput(int input);               // Decodes input provided by menu manager or input manager and returns ID of the new menu to be used. Returns -1 if no menu change is needed.

};

class AUA_Main_Menu: public List_Menu{
  private:
    static const int optionCount = 5;
    List_Option *optionArr[optionCount];
  
  public:
    AUA_Main_Menu(){};
    
    AUA_Main_Menu(U8G2* Display, int ID){
      init(Display, ID);
    };
    void init(U8G2* Display, int ID){
      this->u8g2 = Display;
      this->menuID = ID;
      this->optionArr[0] = new List_Option(1, "User Info");
      this->optionArr[1] = new List_Option(2, "Recent Play");
      this->optionArr[2] = new List_Option(0, "Best Play");
      this->optionArr[3] = new List_Option(0, "PTT Info");
      this->optionArr[4] = new List_Option(0, "Song Info");
      this->Initialized = true;
    };
};

class AUA_User_Info_Menu: Menu{
  public:
    AUA_User_Info_Menu();
    AUA_User_Info_Menu(U8G2* Display, int ID) : Menu(Display, ID){};
    void drawScreen();
  
};

class AUA_Recent_Menu: Menu{
  public:
    AUA_Recent_Menu() : Menu(){};
    AUA_Recent_Menu(U8G2* Display, int ID) : Menu(Display, ID){};
    void drawScreen();
  
};

#endif
