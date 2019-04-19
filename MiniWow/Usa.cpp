#include"Usa.h"

Usa::Usa(){

}
  Usa::Usa(Personaje _per,Equipamento _eq){
      this->_personaje=_per;
      this->_equipamento=_eq;
  }
  Usa::~Usa(){

  }
   Personaje Usa::getPersonaje(){
    return this->_personaje;
   }
   Equipamento  Usa::getEquipamento(){
       return this->_equipamento;
   }
    void Usa::setPersonaje(Personaje _per){
        this->_personaje=_per;
    }
    void Usa::setEquipamento(Equipamento _eq){
        this->_equipamento=_eq;
    }