#include <stdio.h>
#include <stdlib.h>
#include "Jugador.h"
#include <sqlite3.h>
#include <iostream>
#include<string.h>
#include<list>
#include<vector>
#include"Usa.h"
//#include"Personaje.h"
//#include"Equipamento.h"
#define BUFFER_SIZE 256
#include <bits/stdc++.h> 
using namespace std;
vector<Equipamento> vec;  // Vector de Equipamento global
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
            return 1; 
        }
       
	}
	void closeDataBase(){
        sqlite3_close(this->db);
    }
	static int callback(void *data, int argc, char **argv, char **azColName){
        int i;
        fprintf(stderr, "%s: ", (const char*)data);
        for(i = 0; i<argc; i++){
            printf("%s = %s", azColName[i], argv[i] ? argv[i] : "NULL");
          printf("%s ", argv[i] ? argv[i] : "NULL");
        }
   
        printf("\n");
        return 0;
    }

	void menuInicio(){
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
		//this->openDataBase();
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
        cout<<"Cambios realizados"<<endl;
        //this->closeDataBase();
	}
	void iniciarJugador(string user){
      //  this->openDataBase();
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
       // this->closeDataBase();
        } else {
            fprintf(stdout, "Operation done successfully\n");
            // this->closeDataBase();
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
	//this->openDataBase();
   // this->closeDataBase();	
	}
	void equiparPersonaje(string apodo){
	//this->openDataBase();
    
      
    std::string stm1= "select equipamiento.id,equipamiento.nombre,equipamiento.nivel_requerido from ";
    std::string stm2=" puedeusar,(select * from personaje where personaje.nombre='"+apodo+"') as t1, equipamiento";
    std::string stm3=" where puedeusar.clase=t1.clase AND equipamiento.nivel_requerido=t1.nivel ";
    std::string stm4=stm1+stm2+stm3;
      this->select_stmt(stm4.c_str());
      //  std::cout<<stm4.c_str()<<std::endl;
        std::cout<<"*******************************\n";
       for(int i=0; i<vec.size();i++){
        printf("%s",vec[i].toString().c_str());
        std::cout<<"*******************************\n\n";
       }

      std::cout<<"\n\n\n";
     int id; 
    std::cout<<"Digite el id del armamento que desea equipar\n";
    std::cin>>id;
    std::string stmt="select * from equipamiento where equipamiento.id="+id;
    vec.clear();
    this->select_stmt(stmt.c_str());
    Usa us;
    us.setEquipamento(vec[0]);
    Personaje aux;
    aux.setNombre((char*)apodo.c_str());
    us.setPersonaje(aux);
    char sSQL [BUFFER_SIZE] = "\0";	
        sprintf(sSQL, "insert into usa  values ('%s','%d');",us.getPersonaje().getNombre(),us.getEquipamento().getId() );
        rc = sqlite3_exec(db,sSQL, callback, (void*)data, &zErrMsg); 
        if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        } else {
            fprintf(stdout, "Agregado correctamente en la Base de datos\n");
        }
   
  
     //this->closeDataBase();	
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
            //fprintf(stdout, "Operation done successfully\n");
			string choice;
            cout<<"Digite el apodo de su  personaje para ver mas opciones"<<endl;
            cin>>choice;
		    menuPersonajes(choice);
        }
		
	}
	void verFacciones(){
        system("cls");
		rc = sqlite3_exec(db, "SELECT * from Faccion", callback, (void*)data, &zErrMsg);
   
        if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        } 
        else {
			 
             fprintf(stdout, "Operation done successfully\n");
			 int choice;
             cout<<"Digite el id de la faccion que desea escoger"<<endl;
             cin>>choice;
    
        verRazasPorFaccion(choice);
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
		cout<<"Digite un color de piel , verde , azul , roja , morena "<<endl;
		cin>>color;
		}while(color != "verde" && color != "azul" && color!="roja"&& color!="morena");
		
		verFacciones();
	}
    void verRazasPorFaccion(int raza){
        system("cls");
        cout<<"Razas Disponibles para "<< raza <<endl;
        string query = "select raza.id, raza.nombre from existen,raza where existen.raza = raza.id and existen.faccion = "+ to_string(raza);
        rc = sqlite3_exec(db, query.c_str(), callback, (void *)data, &zErrMsg);
        int choice;
        cout << "Digite el id de la raza que desea escoger" << endl;
        cin >> choice;
        verClasesporRaza(choice);
    }
    void verClasesporRaza(int raza){
        system("cls");
        cout << "Clases disponibles para " << raza << endl;
        string query = "select clase.id, clase.nombre from tienen,clase where tienen.clase = clase.id and tienen.raza = " + to_string(raza);
        rc = sqlite3_exec(db, query.c_str(), callback, (void *)data, &zErrMsg);
        int choice;
        cout << "Digite el id de la clase que desea escoger" << endl;
        cin>>choice;
    }

    void select_stmt(const char* stm){
      
      //Funcion que se utiliza para pasar el query y llamar a la funcion que la ejecuta
        int ret = sqlite3_exec(db, stm, select_callback, NULL, NULL);
        
    }


 static int  select_callback(void *data, int argc, char **argv, char **azColName)
{
   /*
     Mete en el vector un objeto equipamiento que esta en la base
    */
   

    //for(int i=0; i<argc; i++){
        Equipamento eq;

        eq.setId(atoi(argv[0]));
        eq.setNombre(argv[1]);
       eq.setNivel(atoi(argv[2]));
       vec.push_back(eq);

      
   // }

    return 0;
}

};
