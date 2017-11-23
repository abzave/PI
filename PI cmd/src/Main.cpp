#include <fstream>
#include <string>
#include <stdlib.h>
#include "Calculo.h"

using namespace std;

void escribir(int, int, double, double);	//Almacena los datos
void leer();	//Lee el fichero

int main(int argc, char *argv[]){

	int opciones = 0;	//Opciones
	int codigo = -1;  //Codigo de duracion
	bool valido = false;    //Validacion de entrada
	Calculo calculador;   //Instancia de calculo

	cout << "Ingrese una opcion" << endl;

	while(true){	//Menu

		cout << "1) Calcular PI" << endl;
		cout << "2) Ver resultados" << endl;
		cout << "3) salir" << endl;
		cin >> opciones;    //Obtiene el dato ingresado

		switch(opciones){	//Validacion de opciones

			case 1:	//Opcion "Calcular PI"

			    system("cls");  //Limpia la pantalla

				cout << "Ingrese la cantidad de digitos a calcular" << endl;
				valido = false; //Resetear valido

				while(!valido){	//Menu 2

					cout << "1) 1 digito" << endl;
					cout << "2) 2 digitos" << endl;
					cout << "3) 4 digitos" << endl;
					cout << "4) 6 digitos" << endl;
					cout << "5) 8 digitos" << endl;
					cout << "6) 10 digitos" << endl;
					cout << "7) Atras" << endl;
					cin >> opciones;   //Obtiene el dato ingresado


					switch(opciones){	//Validacion de opciones

					    /*Los datos del parametro "sumatoria" son el minimo para obtener un resultado correcto*/

						case 1: //opcion "1"

							codigo = calculador.calcular(19, 1);	//Calular e imprimir 2 digito de PI
							escribir(1, codigo, calculador.getTiempo(), calculador.getPI());   //Almacena los resultados en "output.txt"

							valido = true;
							break;

						case 2:	//Opcion "2"

							codigo = calculador.calcular(293, 2);	//Calular e imprimir 2 digito de PI
							escribir(2, codigo, calculador.getTiempo(), calculador.getPI());   //Almacena los resultados en "output.txt"

							valido = true;	//Salir del menu 2
							break;

						case 3:	//Opcion "4"

							codigo = calculador.calcular(17375, 4);	//Calular e imprimir 4 digito de PI
							escribir(4, codigo, calculador.getTiempo(), calculador.getPI());   //Almacena los resultados en "output.txt"

							valido = true;	//Salir del menu 2
							break;

						case 4:	//Opcion "6"

							codigo = calculador.calcular(20000004, 6);	//Calular e imprimir 6 digito de PI
							escribir(6, codigo, calculador.getTiempo(), calculador.getPI());   //Almacena los resultados en "output.txt"

							valido = true;	//Salir del menu
							break;

						case 5:	//Opcion "8"

							codigo = calculador.calcular(117000001, 8);	//Calular e imprimir 8 digito de PI
							escribir(8, codigo, calculador.getTiempo(), calculador.getPI());   //Almacena los resultados en "output.txt"

							valido = true;	//Salir del menu
							break;

						case 6:

							codigo = calculador.calcular(16343000102LL, 10);	//Calular e imprimir 10 digito de PI
							escribir(10, codigo, calculador.getTiempo(), calculador.getPI());  //Almacena los resultados en "output.txt"

							valido = true;	//Salir del menu
							break;

                        case 7:

                            valido = true;
                            system("cls");

                            break;

						default:	//Opcion no valida

                            system("cls");  //Limpia la pantalla
							cout << "Selecione una opcion valida" << endl;	//Mensaje de error

					}

				}

				opciones = 0;	//Resetear opciones
				break;

			case 2: //Opcion "Ver resultados"

			    system("cls");  //Limpia la pantalla
				leer(); //Lee los datos de "output.txt"
				cout << endl;   //Separa la informacion

				break;

			case 3:	//Opcion "Salir"

				exit(0);    //Salir
				break;

			default:	//Opcion no valida

                system("cls");  //Limpia la pantalla
				cout << "Selecione una opcion valida" << endl;	//Mensaje de error

		}

	}

	return 0;

}

void escribir(int digitos, int codigo, double tiempo, double resultado){

	ofstream fichero;   //Instancia fichero

	fichero.open("output.txt", fstream::in | fstream::app);	//Abre o crea el fichero    fstream::ate para agregar al final del fichero

	switch(codigo){

        case 0: //nanosegundos

            fichero << "DIGITOS: " << digitos << endl << endl << "Duracion: " << fixed << setprecision(digitos) << tiempo << "ns" << endl << "Resultado: " << resultado << endl << endl;	//Mensaje que se almacena
            break;

        case 1: //microsegundos

            fichero << "DIGITOS: " << digitos << endl << endl << "Duracion: " << fixed << setprecision(digitos) << tiempo << "us" << endl << "Resultado: " << resultado << endl << endl;    //Mensaje que se almacena
            break;

        case 2: //milisegundos

            fichero << "DIGITOS: " << digitos << endl << endl << "Duracion: " << fixed << setprecision(digitos) << tiempo << "ms" << endl << "Resultado: " << resultado << endl << endl;    //Mensaje que se almacena
            break;

        case 3: //segundos

            fichero << "DIGITOS: " << digitos << endl << endl << "Duracion: " << fixed << setprecision(digitos) << tiempo << "s" << endl << "Resultado: " << resultado << endl << endl; //Mensaje que se almacena
            break;

        case 4: //minutos

            fichero << "DIGITOS: " << digitos << endl << endl << "Duracion: " << fixed << setprecision(digitos) << tiempo << "min" << endl << "Resultado: " << resultado << endl << endl;   //Mensaje que se almacena
            break;

        case 5: //horas

            fichero << "DIGITOS: " << digitos << endl << endl << "Duracion: " << fixed << setprecision(digitos) << tiempo << "h" << endl << "Resultado: " << resultado << endl << endl; //Mensaje que se almacena
            break;

        default:

            fichero << "DIGITOS: " << digitos << endl << endl << "Duracion: " << fixed << setprecision(digitos) << tiempo << "Sin especificar unidad" << endl << "Resultado: " << resultado << endl << endl;    //Mensaje que se almacena

    }

	fichero.close();    //Cierra el fichero

}

void leer(){

	ifstream fichero ("output.txt");    //Abre el fichero
	string cadena;	//Almacena el texto del fichero

	while(getline(fichero, cadena)){    //Guarda en "cadena" los datos del fichero

        cout << cadena << endl; //Imprime el contenido del fichero

	}

	fichero.close(); //Cierra el fichero

}
