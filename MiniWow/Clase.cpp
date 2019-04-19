#include"Clase.h"

Clase::Clase(){
nombre="";
id=-1;
}

Clase::Clase(int _id,string _nombre){
id=_id;    
nombre=_nombre;
}

Clase::~Clase(){
    
}

int Clase::getId(){
return id;
}

string Clase::getNombre(){
 return nombre;
}
void Clase::setId(int _id){
    id=id;
}

void Clase::setNombre(string _nombre){
 nombre=_nombre;
}