#ifndef RAZA_H
#define RAZA_H
#include<iostream>
#include<string>
class Raza {

 private:
    int id;
    string nombre;

 public:
    Raza();
    Raza(int _id,string _nombre);
    ~Raza();
    int getId();
    string getNombre();
    void setId(int _id);
    void setNombre(string _nombre);





};
#endif