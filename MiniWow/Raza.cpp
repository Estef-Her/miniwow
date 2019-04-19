#include"Raza.h"

Raza::Raza(){
nombre="";
id=-1;
}

Raza::Raza(int _id,string _nombre){
id=_id;    
nombre=_nombre;
}
Raza::~Raza(){
    
}

int Raza::getId(){
return id;
}

string Raza::getNombre(){
 return nombre;
}

void Raza::setId(int _id){
    id=id;
}

void Raza::setNombre(string _nombre){
 nombre=_nombre;
}