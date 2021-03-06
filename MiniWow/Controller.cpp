#include <stdio.h>
#include <stdlib.h>
#include "Jugador.cpp"
#include <C:\Users\dh173\OneDrive\Documentos\GitHub\miniwow\MiniWow\sqlite3.h>
#include <iostream>
#include<string>
#include<list>
#include<vector>
#include"Usa.cpp"
#include<iterator>
#include"Faccion.cpp"
#include<time.h>
#include<Windows.h>
#include"Equipamento.cpp"
#include"Personaje.cpp"
#define BUFFER_SIZE 256
using namespace std;
vector<Equipamento> vec;  // Vector de Equipamento global
//Cambios mas actuales 
class Controller{
	private:
	///HOLA JOSUE 
	    sqlite3 *db;
        char *zErrMsg = 0;
        int rc;
        char *sql;
        const char* data = "Callback function called";
	public:
	
	Controller (){
		
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
	void closeDataBase(){
        sqlite3_close(this->db);
    }
	
	static int callback(void *data, int argc, char **argv, char **azColName){
        int i = 0;
        for(i = 0; i<argc; i++){
            //printf("%s ", azColName[i], argv[i] ? argv[i] : "NULL");
            printf("%s    ", argv[i] ? argv[i] : "NULL");
          
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
                object->setId(x);
            }
            else{
                object->setNombreP(data[i]);
            }
        }
       
        f->push_back(*object);
        return 0;
    }
	static int mycallbackRegiones(void *lista, int count , char **data, char **columnNames){
        list<int>* f = static_cast<list<int>*>(lista);
        int ob ;
        int w ;
        for(int i = 0; i<count; i++){
            if(i ==0 ){
                w = atoi(data[i]);
            }
        }
        f->push_back(w);
        return 0;
    }
    static int mycallbackJugador(void *jugador, int count, char **data, char **columnNames){
        cout<<"Entra a la llamada "<<endl;
        Jugador * j = (Jugador*)jugador;
        for (int i = 0; i < count; i++){
            if(i==1){
                if (data[i]){
                    j->setNombre(data[i]);
                    cout << j->getNombre() << endl;
                    j->setStatus(1);
                }
                else{
                    j->setNombre("NULL");
                    cout << j->getNombre() << endl;
                }
            }
         
            
        }
        system("pause");
        return 0;
    }
    void salidaSistema(){
            system("cls");
            cout << "Gracias por utilizar el sistema" << endl;
            cout << "Saliendo " << endl;
    }

    void menuInicio()
    {
	openDataBase();	
        int choice=0;
		do{
            system("cls");
			cout<<("        Inicio\n");
            cout<<endl;
            cout<<("1. Iniciar Sesion\n");
            cout<<("2. Registrarse\n");
            cout<<("3. Salir\n");
            cout << endl;
            cout<<"Ingrese la opcion que desea realizar ";
            cin>> choice ;
 
            switch (choice){
				case 1: menuIniciarSesion();
                    break;
                case 2: registrarJugador();
                    break;
                case 3: salidaSistema();
                    break;
                default: system("cls");
                         printf("Digite una opcion valida!\n");
                         Sleep(2000);
                     break;
            }
 
        }while(choice != 3);
	}
	void insertarJugadores(Jugador jugador){
		sqlite3_stmt *stmt;  
		cout<<"Abre metodo "<<jugador.getNombre()<<" "<< jugador.getId()<<" "<<endl;
		char sSQL [BUFFER_SIZE] = "\0";
		
		
        sprintf(sSQL, "insert into jugador  values ('%s','%s', %i);", jugador.getId().c_str() ,jugador.getNombre().c_str(),jugador.getStatus());
        rc = sqlite3_exec(db,sSQL, callback, (void*)data, &zErrMsg); 
        if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        } else {
            fprintf(stdout, "Operation done successfully\n");
			menuJugador(jugador.getId());
        }
        
        }

	
	void iniciarJugador(string user){
        openDataBase();
        Jugador *j = new Jugador();
        sqlite3_stmt *stmt;  
		cout<<"Abre metodo"<<user<<" "<<endl;
        string query = "select jugador.nombre from jugador where jugador.nombre = '" + user + "';";
        cout<<query<<endl;
        rc = sqlite3_exec(db, query.c_str(), mycallbackJugador, j, &zErrMsg);
        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        }
      
        if(j->getNombre() =="NULL"){
                cout << "El usuario " << user << " no existe en la base de datos " << endl;
                cout << "Por favor, registre su usuario o vuelva a intentarlo" << endl;
         }
            else{
                menuJugador(user);
            }
        
        system("pause");
      
	}
	void jugador(){
		
	}
	void menuIniciarSesion(){
        system("cls");
		string username;
		cout<<"Por favor, digite su nombre de usuario "<<endl;
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
			cout<<("3. Eliminar personaje\n");
            cout<<("4. Salir\n");
            cin>> choice ;
 
            switch (choice){
				case 1:trasladarPersonaje(apodo);
                    break;
                case 2: equiparPersonaje(apodo);
                    break;
                case 3: eliminarPersonaje(apodo);
                    break;
                case 4:printf("Saliendo...\n");
                    break;
                default:printf("Digite una opcion valida!\n");
                     break;
            }
 
        }while(choice ==1 && choice == 2 && choice ==3);
	}
	void eliminarPersonaje(string apodo){
		char sSQL [BUFFER_SIZE] = "\0";
        sprintf(sSQL, "delete from personaje where nombre= '%s';",apodo.c_str());
        rc = sqlite3_exec(db,sSQL, callback, (void*)data, &zErrMsg); 
        if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        } else {
            fprintf(stdout, "Operation done successfully\n");
        }
	}
	void verRegion(string apodo){
		char sSQL [BUFFER_SIZE] = "\0";
       
		
        sprintf(sSQL, "select personaje.nombre, region.nombre , continente.nombre from personaje, region, continente where continente.id=region.continente AND region.id= personaje.region AND personaje.nombre='%s';",apodo.c_str());
        rc = sqlite3_exec(db,sSQL, callback, (void*)data, &zErrMsg); 
        if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        } else {
			cout<<"La Ubicacion actual"<<endl;
            fprintf(stdout, "Operation done successfully\n");
        }
	}
	int verContinentes(){
		int choice=0;
		char sSQL [BUFFER_SIZE] = "\0";
        sprintf(sSQL, "select * from continente ;");
        rc = sqlite3_exec(db,sSQL, callback, (void*)data, &zErrMsg); 
        if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        } else{
            fprintf(stdout, "Operation done successfully\n");
			cout<<"Digite el id del Continente al que quiere transportarse"<<endl;
			cin>>choice;
        }
		return choice;
	}
	int verRegionesXContinente(int id){
		system("cls");
        cout << "--Regiones--"<< endl;
        string query = "select region.id , region.nombre from region where continente=" + to_string(id);
        rc = sqlite3_exec(db, query.c_str(), callback, (void *)data, &zErrMsg);
        int choice=0;
        cout << "Digite el id de la region a la que desea trasladarse " << endl;
        cin>>choice;
		return choice;
	}
	
	
	void trasladarPersonaje(string apodo){
		openDataBase();
		verRegion(apodo);
		int continente= verContinentes();
		int region = verRegionesXContinente(continente);
		actualizarRegion(apodo,region);
		cout<<"Traslado Finalizdo!"<<endl;
		cout<<"Continente :"<<continente<<endl;
		cout<<"Region : "<<region<<endl;
		
	}
	void actualizarRegion(string apodo,int region){
		char sSQL [BUFFER_SIZE] = "\0";
        sprintf(sSQL, "update personaje set region =%i where nombre='%s';",region,apodo.c_str());
        rc = sqlite3_exec(db,sSQL, callback, (void*)data, &zErrMsg); 
        if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        } else{
            fprintf(stdout, "Operation done successfully\n");
        }
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
	void personaje(string apodo){
			char sSQL [BUFFER_SIZE] = "\0";
        sprintf(sSQL, "select * from personaje  where nombre='%s';",apodo.c_str());
        rc = sqlite3_exec(db,sSQL, callback, (void*)data, &zErrMsg); 
        if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        } else {
			cout<<"apodo,genero,color,jugador,faccion,raza,clase,region,armamento,nivel"<<endl;
            fprintf(stdout, "Operation done successfully\n");
		    menuPersonajes(apodo);
        }
	}
	void verPersonajes(string user){
		
		char sSQL [BUFFER_SIZE] = "\0";
        
        sprintf(sSQL, "select * from personaje where jugador='%s';",user.c_str());
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
		    personaje(choice);
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

    int verRegionezContinente(int con){
		int region;
		int id;
        srand(time(NULL));
		char sSQL [BUFFER_SIZE] = "\0";
        system("cls");
        list<int> * listRegiones = new list<int>();
        sprintf(sSQL, "SELECT region.id from region where region.continente='%i';", con);
        rc = sqlite3_exec(db, sSQL, mycallback, listRegiones, &zErrMsg);
        list<int>::iterator it;
        for (it = listRegiones->begin(); it != listRegiones->end(); it++)
        {
            cout << " " << *it << endl;
        }
        cout<<"Ejecutado"<<endl;
        if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        }else {
			int tam=listRegiones->size();
         	region =0+rand()%tam;
            fprintf(stdout, "Operation done successfully\n");
            list<int>::iterator it;
			int i=0;
            for (it = listRegiones->begin(); it != listRegiones->end(); it++)
            {
				if(i==region){
					id=*it;
                    return id;
				}
				i++;
            }
        }
		
	}
        
	
	
	void registrarJugador(){
		openDataBase();
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
		
	}
	
	void crearPersonajes(string user){
		openDataBase();
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
        int resultInsert = this->insertarPersonaje(user, userName, genero, color, faccion, raza, clase);
        if(resultInsert){
            cout<<"Se ha registrado el personaje con nombre "<<userName<<" exitosamente"<<endl;
            
        }
        else{
            cout << "No se ha podido ingresar el personaje, por favor vuelva a intentarlo" <<endl;
        }
    }
     int verRazasPorFaccion(int raza){
        system("cls");
        cout<<"Razas Disponibles para "<< raza <<endl;
          cout<<"Id  "<<"     "<<"Nombre"<<endl;
        string query = "select raza.id, raza.nombre from existen,raza where existen.raza = raza.id and existen.faccion = "+ to_string(raza)+";";
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
		//cout<<query<<endl;
		
        rc = sqlite3_exec(db, query.c_str(), callback, (void *)data, &zErrMsg);
        int choice;
        cout << "Digite el id de la clase que desea escoger" << endl;
        cin>>choice;
        return choice;
    }
    int insertarPersonaje(string user, string username, string genero, string color, int faccion, int raza, int clase)
    {
       // openDataBase();
        cout<<"Insertando"<<endl;
	    int continente=0;
	    if(faccion==1 && raza!=13){
			if(raza==5){
				cout<<"Caso Especial Draneis"<<endl;
				continente=1;
			}else{
			continente=2;}
		}
		if(faccion==2 && raza!=13){
			if(raza==11){
				continente=2;
			}else{
			continente=1;}
		}
		if(raza==13){
			continente=3;
		}
		//cout<<"Ramdon "<<continente<<endl;
		int region= verRegionezContinente(continente);
        string query = "insert into personaje(nombre, genero,color, jugador, faccion, raza, clase, region, armamento, nivel) values('" + username + "','" + genero + "', '" + color + "', '"+user + "'," + to_string(faccion)  + "," + to_string(raza) + "," + to_string(clase) +","+ to_string(region)+ ","+to_string(0)+","+to_string(0)+");";
        rc = sqlite3_exec(db, query.c_str(), callback, (void *)data, &zErrMsg);
        if (rc != SQLITE_OK)
            return 0;
        else
             return 1; //succesful;
        
        
    }
};