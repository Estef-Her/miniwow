#ifndef USA_H
#define USA_H
#include<iostream>
#include"Equipamento.h"
#include"Personaje.h"
class Usa {

 private:

    Personaje _personaje;
    Equipamento _equipamento;

 public:
    Usa();
    Usa(Personaje _per,Equipamento _eq);
    ~Usa();
    Personaje getPersonaje();
    Equipamento getEquipamento();
    void setPersonaje(Personaje _per);
    void setEquipamento(Equipamento _eq);


};
#endif