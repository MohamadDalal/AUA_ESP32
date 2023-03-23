#ifndef MOI_MENU_H
#define MOI_MENU_H

#include <Arduino.h>
#include <U8g2lib.h>
#include "IR_Remote.h"

class Menu{

  protected:
    U8G2* u8g2;
    bool Initialized = false;
    int menuID=-1;
    int prevMenuID=-1;                        // Saves the menu ID of the previous menu, so that we can go back to it when the back button is pressed.
    int currentOption=0;                      // Holds index of the currently selected option.
    
  public:
    Menu();
    Menu(U8G2* Display, int ID);
    virtual void init(U8G2* Display, int ID);
    bool isInitialized();
    virtual void drawScreen();
    virtual int decodeInput(int input);               // Decodes input provided by menu manager or input manager and returns ID of the new menu to be used. Returns -1 if no menu change is needed.
    int getMenuID();
    int getPrevMenuID();
    void setPrevMenuID(int ID);
  
};

class MenuOption{

  protected:
    bool Initialized = false;
    int nextMenu=-1;
    
  public:
    MenuOption();
    MenuOption(int nextMenu);
    void init(int nextMenu);
    bool isInitialized();
    int getNextMenu();
  
};

#endif
