#ifndef MOI_LIST_MENU_H
#define MOI_LIST_MENU_H

#include "Menus.h"
// This source says making an abstract Menu class to inherit is not really a good idea.
class List_Menu : public Menu {

  private:
    U8G2* u8g2;
    List_Option optionArr[3];
  public:
    List_Menu();
    
};

class List_Option : public MenuOption{

  private:
    String optionLabel = "";
  public:
    List_Option();
  
};
#endif
