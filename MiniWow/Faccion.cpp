#include"Faccion.h"

Faccion::Faccion(){
// this->nombre='\0';
this->id=0;
this->nombrep = "";
}

Faccion::Faccion(int _id, string _nombrep/*char* _nombre*/){
this->id=_id;
this->nombrep = _nombrep;
}
Faccion::~Faccion(){
    
}

int Faccion::getId(){
return this->id;
}

char* Faccion::getNombre(){
 return this->nombre;
}
void Faccion::setId(int _id){
    this->id=_id;
}

void Faccion::setNombre(char* _nombre){
 this->nombre=_nombre;
}

string Faccion::getNombreP()
{
    return this->nombrep;
}
void Faccion::setNombreP(string _nombrep)
{
    this->nombrep = _nombrep;
}