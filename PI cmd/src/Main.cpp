#include <fstream>
#include <string>
#include "Calculo.h"

using namespace std;

void escribir(int, int, double, double);	//Almacena los datos
void leer();	//Lee el fichero

int main(int argc, char *argv[]){

	int o = 0;	//Opciones
	int cod = NULL;
	bool valido = false;
	Calculo calc;   //Instancia de calculo

	cout << "Ingrese una opcion" << endl;

	while(true){	//Menu

		cout << "1) Calcular PI" << endl;
		cout << "2) Ver resultados" << endl;
		cout << "3) salir" << endl;
		cin >> o;

		switch(o){	//Validacion de opciones

			case 1:	//Opcion "Calcular PI"

				cout << endl << "Ingrese la cantidad de digitos a calcular" << endl;
				valido = false;

				while(!valido){	//Menu 2

					cout << "1) 1" << endl;
					cout << "2) 2" << endl;
					cout << "3) 4" << endl;
					cout << "4) 6" << endl;
					cout << "5) 8" << endl;
					cout << "6) 10" << endl;
					cin >> o;


					switch(o){	//Validacion de opciones

						case 1:

							cod = calc.calcular(19, 1);	//Calular e imprimir 2 digito de PI
							escribir(1, cod, calc.getTiempo(), calc.getPI());

							valido = true;
							break;

						case 2:	//Opcion "2"

							cod = calc.calcular(293, 2);	//Calular e imprimir 2 digito de PI
							escribir(2, cod, calc.getTiempo(), calc.getPI());

							valido = true;	//Salir del menu 2
							break;

						case 3:	//Opcion "4"

							cod = calc.calcular(17375, 4);	//Calular e imprimir 4 digito de PI
							escribir(4, cod, calc.getTiempo(), calc.getPI());

							valido = true;	//Salir del menu 2
							break;

						case 4:	//Opcion "6"

							cod = calc.calcular(20000004, 6);	//Calular e imprimir 6 digito de PI
							escribir(6, cod, calc.getTiempo(), calc.getPI());

							valido = true;	//Salir del menu
							break;

						case 5:	//Opcion "8"

							cod = calc.calcular(117000001, 8);	//Calular e imprimir 8 digito de PI
							escribir(8, cod, calc.getTiempo(), calc.getPI());

							valido = true;	//Salir del menu
							break;

						case 6:

							cod = calc.calcular(16343000102LL, 10);	//Calular e imprimir 10 digito de PI
							escribir(10, cod, calc.getTiempo(), calc.getPI());

							valido = true;	//Salir del menu
							break;

						default:	//Opcion no valida

							cout << "Selecione una opcion valida" << endl;	//Mensaje de error

					}

				}

				o = 0;	//Resetear opciones
				break;

			case 2:

				leer();
				cout << endl;

				break;

			case 3:	//Opcion "Salir"

				exit(0);
				break;

			default:	//Opcion no valida

				cout << "Selecione una opcion valida" << endl;	//Mensaje de error

		}

	}

	return 0;

}

void escribir(int digitos, int cod, double tiempo, double resultado){

	ofstream f;

	f.open("output.txt", fstream::in | fstream::app);	//fstream::ate para agregar al final del fichero

	switch(cod){

        case 0:

            f << "DIGITOS: " << digitos << endl << endl << "Duracion: " << fixed << setprecision(digitos) << tiempo << "ns" << endl << "Resultado: " << resultado << endl << endl;	//Mensaje que se almacen
            break;

        case 1:

            f << "DIGITOS: " << digitos << endl << endl << "Duracion: " << fixed << setprecision(digitos) << tiempo << "us" << endl << "Resultado: " << resultado << endl << endl;
            break;

        case 2:

            f << "DIGITOS: " << digitos << endl << endl << "Duracion: " << fixed << setprecision(digitos) << tiempo << "ms" << endl << "Resultado: " << resultado << endl << endl;
            break;

        case 3:

            f << "DIGITOS: " << digitos << endl << endl << "Duracion: " << fixed << setprecision(digitos) << tiempo << "s" << endl << "Resultado: " << resultado << endl << endl;
            break;

        case 4:

            f << "DIGITOS: " << digitos << endl << endl << "Duracion: " << fixed << setprecision(digitos) << tiempo << "min" << endl << "Resultado: " << resultado << endl << endl;
            break;

        case 5:

            f << "DIGITOS: " << digitos << endl << endl << "Duracion: " << fixed << setprecision(digitos) << tiempo << "h" << endl << "Resultado: " << resultado << endl << endl;
            break;

        default:

            f << "DIGITOS: " << digitos << endl << endl << "Duracion: " << fixed << setprecision(digitos) << tiempo << "Sin especificar unidad" << endl << "Resultado: " << resultado << endl << endl;

    }

	f.close();

}

void leer(){

	ifstream fe ("output.txt");
	string cadena;	//Almacena el texto del fichero

	while(!fe.eof()){	//Lee hasta que termine el fichero

		cout << cadena << endl;
		fe >> cadena;

	}

	fe.close();

}
