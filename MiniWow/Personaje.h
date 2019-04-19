#ifndef PERSONAJE_H
#define PERSONAJE_H
#include<iostream>
#include"Jugador.h"
#include"Faccion.h"
#include"Raza.cpp"
#include"Clase.cpp"
#include"Region.cpp"
#include<string>
class Personaje{

 private:
	string genero;
	string colorPiel;
    string nombre;
    Jugador jugador;
	Faccion faccion;
	Raza raza;
	Clase clase ;
	Region region;
    int armamento;
	int nivel;
 public:
    Personaje();
    Personaje(string _genero, string _coloPiel, string _nombre, Jugador _jugador, Faccion _faccion, Raza _raza, Clase _clase, Region _region, int arm, int niv);
    ~Personaje();
	string getGenero();
	string getColorPiel();
    string getNombre();
	Jugador getJugador();
	Faccion getFaccion();
	Raza getRaza();
	Clase getClase();
	Region getRegion();
	int getArmamento();
	int getNivel();
	void setGenero(string _genero);
	void setColorPiel(string _color);
    void setNombre(string _nombre);
	void setJugador(Jugador _jugador);
	void setFaccion(Faccion _faccion);
	void setRaza(Raza _raza);
	void setClase(Clase _clase);
	void setRegion(Region _region);
	void setArmamento(int arm);
	void setNivel(int niv);
};
#endif