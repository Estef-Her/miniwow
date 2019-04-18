#ifndef FACCION_H
#define FACCION_H
#include<iostream>
#include <string>
using namespace std;

class Faccion {

 public:
    int id;
    char* nombre;
    string nombrep;

 public:
    Faccion();
    Faccion(int _id, string _nombrep/*char* _nombre*/);
    ~Faccion();
    int getId();
    char* getNombre();
    void setId(int _id);
    void setNombre(char* _nombre);
    string getNombreP();
    void setNombreP(string _nombrep);

};
#endif