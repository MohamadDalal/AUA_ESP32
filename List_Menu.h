#ifndef MOI_LIST_MENU_H
#define MOI_LIST_MENU_H

#include "Menus.h"
// This source says making an abstract Menu class to inherit is not really a good idea.
class List_Menu;
class List_Option;
//class Test_List_Menu;

class List_Menu : public Menu {

  protected:
    U8G2* u8g2;
    //List_Option optionArr[5];
    static const int optionCount = 3;
    List_Option *optionArr[optionCount];
    int cursorIndex = 0;
    int optionIndex = 0;
    bool lastInputDown = false;
  public:
    List_Menu();
    //List_Menu(U8G2* Display, int ID):Menu(Display, ID); // This is a way to call the parent's non-default constructor form the child's non-default constructor
    //                                                    // I will not do this because I would like to use this classes init function and initialize using it.
    List_Menu(U8G2* Display, int ID);
    void init(U8G2* Display, int ID);
    void drawScreen();
    int decodeInput(int input);                         // Decodes input provided by menu manager or input manager and returns ID of the new menu to be used. Returns -1 if no menu change is needed.
    
};

class List_Option : public MenuOption{

  private:
    String optionLabel = "";
  public:
    List_Option();
    List_Option(int nextMenu, String Label);
    void init(int nextMenu, String Label);
    String getLabel();
    //char* getLabelChar();

// I am not entirely sure why this is not working, but I think I am not allowed to inherit from a class in the same h file (95% sure it is not true).
// The error I am getting is invalid use of incomplete type class or something like that.
/*class Test_List_Menu: public List_Menu {
  
  public:
    Test_List_Menu();
    Test_List_Menu(U8G2* Display, int ID);
    void init(U8G2* Display, int ID);
    //Test_List_Menu(U8G2* Display, int ID) : List_Menu(Display, ID);
  
};*/

};
#endif
