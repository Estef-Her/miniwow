#include"Equipamento.h"

Equipamento::Equipamento(){

}
Equipamento::Equipamento(int _id,char* _nombre, int _nivel){
    id=_id;
    nombre=_nombre;
    nivel=_nivel;
}
Equipamento::~Equipamento(){

}
int Equipamento::getId(){
    return id;
}
char* Equipamento::getNombre(){
    return nombre;
}
int Equipamento::getNivel(){
    return nivel;
}
void Equipamento::setId(int _id){
    id=_id;
}
void Equipamento::setNombre(char* _nombre){
    nombre=_nombre;
}
void Equipamento::setNivel(int _niv){
    nivel=_niv;
}
std::string Equipamento::toString(){
 std::stringstream s;
 s<<"Id: "<<getId()<<std::endl;
 s<<"Nombre: "<<getNombre()<<std::endl;
 s<<"Nivel: "<<getNivel()<<std::endl;
    return s.str();
}