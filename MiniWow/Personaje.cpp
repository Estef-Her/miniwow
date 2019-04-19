    #include"Personaje.h"
	
	Personaje::Personaje(){}
    Personaje::Personaje(string _genero, string _coloPiel, string _nombre, Jugador _jugador, Faccion _faccion, Raza _raza, Clase _clase, Region _region, int arm, int niv){
		genero=_genero;
		colorPiel=_coloPiel;
		nombre=_nombre;
		jugador=_jugador;
		faccion=_faccion;
		raza=_raza;
		clase=_clase;
		region=_region;
		armamento=arm;
		nivel=niv;
	}
    Personaje::~Personaje(){}
	string Personaje::getGenero(){
		return genero;
	}
	string Personaje::getColorPiel(){
		return colorPiel;
	}
    string Personaje::getNombre(){
		return nombre;
	}
	Jugador Personaje::getJugador(){
		return jugador;
	}
	Faccion Personaje::getFaccion(){
		return faccion;
	}
	Raza Personaje::getRaza(){
		return raza;
	}
	Clase Personaje::getClase(){
		return clase;
	}
	Region Personaje::getRegion(){
		return region;
	}
	int Personaje::getArmamento(){
		return armamento;
	}
	int Personaje::getNivel(){
		return nivel;
	}
	void Personaje::setGenero(string _genero){
	     genero=_genero;;
	}
	void Personaje::setColorPiel(string _color){
		colorPiel=_color;
	}
    void Personaje::setNombre(string _nombre){
		nombre=_nombre;
	}
	void Personaje::setJugador(Jugador _jugador){
		jugador=_jugador;
	}
	void Personaje::setFaccion(Faccion _faccion){
		faccion=_faccion;
	}
	void Personaje::setRaza(Raza _raza){
		raza=_raza;
	}
	void Personaje::setClase(Clase _clase){
		clase=_clase;
	}
	void Personaje::setRegion(Region _region){
		region=_region;
	}
	void Personaje::setArmamento(int arm){
		armamento=arm;
	}
	void Personaje::setNivel(int niv){
		nivel=niv;
	}