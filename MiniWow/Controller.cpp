#include <stdio.h>
#include <stdlib.h>
#include "Jugador.cpp"
#include <C:\Users\Josue\Desktop\miniwow\MiniWow\sqlite3.h>
#include <iostream>
#include<string>
#include<list>
#include<iterator>
#include"Faccion.cpp"

#define BUFFER_SIZE 256
using namespace std;

class Controller{
	private:
	    sqlite3 *db;
        char *zErrMsg = 0;
        int rc;
        char *sql;
        const char* data = "Callback function called";
	public:
	
	Controller (){
		openDataBase();
	}
	int openDataBase(){
		rc = sqlite3_open("miniwow.db", &db);
   
        if( rc ) {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
            return(0);
        } else {
            fprintf(stderr, "Opened database successfully\n");
        }
	}
	
	static int callback(void *data, int argc, char **argv, char **azColName){
        int i = 0;
        Faccion * f = new Faccion();
        //fprintf(stderr, "%s: ", (const char*)data);
        for(i = 0; i<argc; i++){
            //printf("%s ", azColName[i], argv[i] ? argv[i] : "NULL");
            printf("%s ", argv[i] ? argv[i] : "NULL");
          
       }
   
        printf("\n");
        return 0;
    }
    //prueba
    static int mycallback(void *lista, int count , char **data, char **columnNames){
        list<Faccion>* f = static_cast<list<Faccion>*>(lista);
        Faccion *object = new Faccion();
        Faccion *w = new Faccion();
        for(int i = 0; i<count; i++){
            if(i ==0 ){
                int x = atoi(data[i]);
               // cout << "esto es data" << x << endl;
                object->setId(x);
                //cout << "objeto" << object->getId() << endl;
            }
            
            else{
                object->setNombreP(data[i]);
            }
        }
        system("pause");
        f->push_back(*object);
        cout<<object->getNombreP()<<endl;
        cout<<"Se ha ingresado nuevos objeto a la lista"<<endl;
        system("pause");
        return 0;
    }

        void menuInicio()
    {
        int choice=0;
		do{
			cout<<("Inicio\n");
            cout<<("1. Iniciar Sesion\n");
            cout<<("2. Registrarse\n");
            cout<<("3. Salir\n");
            cin>> choice ;
 
            switch (choice){
				case 1:menuIniciarSesion();
                    break;
                case 2:registrarJugador();
                    break;
                case 3:printf("Saliendo...\n");
                    break;
 
                default:printf("Digite una opcion valida!\n");
                     break;
            }
 
        }while(choice ==1 && choice == 2);
	}
	void insertarJugadores(Jugador jugador){
		sqlite3_stmt *stmt;  
		cout<<"Abre metoodod "<<jugador.getNombre()<<" "<< jugador.getId()<<" "<<endl;
		char sSQL [BUFFER_SIZE] = "\0";
		
        int b = jugador.getId().length();  
        char id [b+1]; 
        strcpy(id, jugador.getId().c_str()); 
		
		int n = jugador.getNombre().length();  
        char nombre [n + 1]; 
        strcpy(nombre, jugador.getNombre().c_str()); 
		
        sprintf(sSQL, "insert into jugador  values ('%s','%s', %i);", id ,nombre,jugador.getStatus());
        rc = sqlite3_exec(db,sSQL, callback, (void*)data, &zErrMsg); 
        if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        } else {
            fprintf(stdout, "Operation done successfully\n");
        }
        
        }

	}
	void iniciarJugador(string user){
		sqlite3_stmt *stmt;  
		cout<<"Abre metoodod "<<user<<" "<<endl;
		char sSQL [BUFFER_SIZE] = "\0";
		
        int b = user.length();  
        char id [b+1]; 
        strcpy(id, user.c_str()); 
		
        sprintf(sSQL, "select * from jugador where id='%s';",id );
        rc = sqlite3_exec(db,sSQL, callback, (void*)data, &zErrMsg); 
        if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        } else {
            fprintf(stdout, "Operation done successfully\n");
			menuJugador(user);
        }
        
	}
	void menuIniciarSesion(){
		string username;
		cout<<"Digite su nombre de usuario"<<endl;
		cin>>username;
		iniciarJugador(username);
	} 
    void menuPersonajes(string apodo){
		int choice=0;
		do{
            system("cls");
			cout<<"Bienvenido " << apodo << endl;
            cout<<("1. Trasladar personaje \n");
            cout<<("2. Equipar Personaje\n");
            cout<<("3. Salir\n");
            cin>> choice ;
 
            switch (choice){
				case 1:trasladarPersonaje(apodo);
                    break;
                case 2: equiparPersonaje(apodo);
                    break;
                case 3:printf("Saliendo...\n");
                    break;
 
                default:printf("Digite una opcion valida!\n");
                     break;
            }
 
        }while(choice ==1 && choice == 2);
	}
	void trasladarPersonaje(string apodo){
		
	}
	void equiparPersonaje(string apodo){
		
	}
	void menuJugador(string user){
		int choice=0;
		do{
            system("cls");
			cout<<"Bienvenido " << user << endl;
            cout<<("1. Ver Personajes \n");
            cout<<("2. Crear Personajes\n");
            cout<<("3. Salir\n");
            cin>> choice ;
 
            switch (choice){
				case 1:verPersonajes(user);
                    break;
                case 2: crearPersonajes(user);
                    break;
                case 3:printf("Saliendo...\n");
                    break;
 
                default:printf("Digite una opcion valida!\n");
                     break;
            }
 
        }while(choice ==1 && choice == 2);
	}
	void verPersonajes(string user){
		char sSQL [BUFFER_SIZE] = "\0";
        int b = user.length();  
        char id [b+1]; 
        strcpy(id, user.c_str()); 
		
        sprintf(sSQL, "select * from personaje where jugador='%s';",id );
        rc = sqlite3_exec(db,sSQL, callback, (void*)data, &zErrMsg); 
        if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        } else {
			cout<<"apodo,genero,color,jugador,faccion,raza,clase,region,armamento,nivel"<<endl;
            fprintf(stdout, "Operation done successfully\n");
			string choice;
            cout<<"Digite el apodo de su  personaje para ver mas opciones"<<endl;
            cin>>choice;
		    menuPersonajes(choice);
        }
		
	}
	int verFacciones(){
        system("cls");
        list<Faccion> * listFacciones = new list<Faccion>();
        rc = sqlite3_exec(db, "SELECT * from Faccion", mycallback, listFacciones, &zErrMsg);

        if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        } 
        else {
			 
             fprintf(stdout, "Operation done successfully\n");
        }
        cout<<" Facciones disponibles "<<endl;
        cout<<"Id  "<<"   "<<"Nombre"<<endl;
        list<Faccion>::iterator it;
         for (it = listFacciones->begin(); it != listFacciones->end(); it++)
        {
            cout<<it->getId()<<"      "<<it->getNombreP()<<endl;
        }
        int choice;
        cout<<"Digite el id de la faccion que desea escoger"<<endl;
        cin>>choice;
        return choice;
        //verRazasPorFaccion(choice);
        }
        
	}
	
	void registrarJugador(){
        system("cls");
		string nombre;
		string username;
		cout<<"Digite el nombre ";cin>>nombre;
		cout<<"Digite el nombre de usuario ";cin>>username;
	    Jugador jugador = Jugador();
		jugador.setId(username);
		jugador.setNombre(nombre);
		jugador.setStatus(true);
		insertarJugadores(jugador);
		menuJugador(username);
	}
	
	void crearPersonajes(string user){
        system("cls");
		string userName;
		string genero;
		string color;
		cout<<"Digite un apodo para su personaje :";cin>>userName;
		cout<<"Indique un genero para el personaje "<<endl;
		int choice;
		do{
            cout<<("1. Femenino  \n");
            cout<<("2. Masculino \n");
            cin>> choice ;
            switch (choice){
				case 1:
				    genero="Femenino";
                    break;
                case 2:
				    genero="Masculino";
                    break;
 
                default:printf("Digite una opcion valida!\n");
                     break;
		    }
		}while(choice!=2 && choice !=1);
		do{
		cout<<"Digite un color de piel : verde , azul , roja , morena "<<endl;
		cin>>color;
		}while(color != "verde" && color != "azul" && color!="roja"&& color!="morena");
		
		int faccion = verFacciones();
        int raza = verRazasPorFaccion(faccion);
        int clase = verClasesporRaza(raza);
        this->insertarPersonaje(jugador, userName, genero, color, faccion, raza, clase);

	}
     int verRazasPorFaccion(int raza){
        system("cls");
        cout<<"Razas Disponibles para "<< raza <<endl;
        string query = "select raza.id, raza.nombre from existen,raza where existen.raza = raza.id and existen.faccion = "+ to_string(raza);
        rc = sqlite3_exec(db, query.c_str(), callback, (void *)data, &zErrMsg);
        int choice;
        cout << "Digite el id de la raza que desea escoger" << endl;
        cin >> choice;
        return choice;
      //  verClasesporRaza(choice);
    }
    int verClasesporRaza(int raza){
        system("cls");
        cout << "Clases disponibles para " << raza << endl;
        string query = "select clase.id, clase.nombre from tienen,clase where tienen.clase = clase.id and tienen.raza = " + to_string(raza);
        rc = sqlite3_exec(db, query.c_str(), callback, (void *)data, &zErrMsg);
        int choice;
        cout << "Digite el id de la clase que desea escoger" << endl;
        cin>>choice;
        return choice;
    }
    void insertarPersonaje(Jugador jugador, string username, string genero, string color, int faccion, int raza, int clase)
    {
        string query = "insert into personaje(nombre, genero,color, jugador, faccion, raza, clase"

    }
};