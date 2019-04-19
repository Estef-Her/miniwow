#include"Region.h"

    Region::Region(){
		
	}
    Region::Region(Continente _continente, int _id,string _nombre,string _capital){
		continente=_continente;
		id=_id;
		nombre=_nombre;
		capital=_capital;
	}
    Region::~Region(){
		
	}
	Continente Region:: getContinente(){
		return continente;
	}
    int Region:: getId(){
		return id;
	}
    string Region::getNombre(){
		return nombre;
	}
	string Region::getCapital{
		return capital;
	}
	void Region::setContinente(Continente cont){
		continente=cont;
	}
    void Region::setId(int _id){
		id=_id;
	}
    void Region::setNombre(string _nombre){
		nombre=_nombre;
	}
    void Region::setCapital(string _capital){
		capital=_capital;
	}