#ifndef REGION_H
#define REGION_H
#include<iostream>
#include"Continente.h"
#include<string>
class Region{

 private:
    Continente continente;
    int id;
    string nombre;
	string capital;

 public:
    Region();
    Region(Continente _continente, int _id,string _nombre,string _capital);
    ~Region();
	Continente getContinente();
    int getId();
    string getNombre();
	string getCapital;
	void setContinente(Continente cont);
    void setId(int _id);
    void setNombre(string _nombre);
    void setCapital(string _capital);

};
#endif
