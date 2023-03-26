#include "AUA_Menus.h"

//----------------------------------------------------------------------AUA_Menu_Manager class----------------------------------------------------------------------------//
AUA_Menu_Manager::AUA_Menu_Manager(){
  init();
}
void AUA_Menu_Manager::init(){
  
}

bool AUA_Menu_Manager::isInitialized(){return this->Initialized;}

void AUA_Menu_Manager::activate(){this->active = true;}
void AUA_Menu_Manager::inactivate(){this->active = false;}
bool AUA_Menu_Manager::isActive(){return this->active;}
void AUA_Menu_Manager::drawScreen(){
  
}
void AUA_Menu_Manager::decodeInput(int input){
  
}

//----------------------------------------------------------------------AUA_User_Info_Menu class---------------------------------------------------------------------------//

void AUA_User_Info_Menu::drawScreen(){
  
}

//----------------------------------------------------------------------AUA_Recent_Menu class------------------------------------------------------------------------------//
void AUA_Recent_Menu::drawScreen(){
  
}
