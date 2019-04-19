#ifndef CLASE_H
#define CLASE_H
#include<iostream>
#include<string>
class Clase{

 private:
    int id;
    string nombre;

 public:
    Clase();
    Clase(int _id,string _nombre);
    ~Clase();
    int getId();
    string getNombre();
    void setId(int _id);
    void setNombre(string _nombre);
};
#endif