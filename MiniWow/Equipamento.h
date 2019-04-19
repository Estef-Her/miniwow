#ifndef EQUIPAMENTO_H
#define EQUIPAMENTO_H
#include<iostream>
#include<string>
#include<sstream>

class Equipamento {

 private:
    int id;
    char* nombre;
    int nivel;

 public:
    Equipamento();
    Equipamento(int _id,char* _nombre, int nivel);
    ~Equipamento();
    int getId();
    char* getNombre();
    int getNivel();
    void setId(int _id);
    void setNombre(char* _nombre);
    void setNivel(int _niv);
	string toString();
};
#endif