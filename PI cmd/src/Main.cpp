#include <fstream>
#include <string>
#include <stdlib.h>
#include "Calculo.h"

using namespace std;

void escribirResultados(int, int, double, double);
void leerResultados();
string obtenerUnidad(int);
void opcionCalcular(int, Calculo);
int pedirCantidadDeDigitos();

int main(int argc, char *argv[]){
	int opciones = 0;
	Calculo calculador;
	cout << "Ingrese una opcion" << endl;
	while(true){	//Menu
		cout << "1) Calcular PI" << endl;
		cout << "2) Ver resultados" << endl;
		cout << "3) salir" << endl;
		cin >> opciones;
		switch(opciones){
			case 1:	//Opcion "Calcular PI"
			    system("cls");
				int opcion;
				opcion = pedirCantidadDeDigitos();
				opcionCalcular(opcion, calculador);
				break;
			case 2: //Opcion "Ver resultados"
			    system("cls");
				leerResultados();
				cout << endl;
				break;
			case 3:	//Opcion "Salir"
				exit(0);
				break;
			default:
                system("cls");
				cout << "Selecione una opcion valida" << endl;
		}
	}
	return 0;
}

/*
Entradas: Digitos de tipo entero, codigo de tipo entero, tiempo de tipo double y resultado de tipo double
Salidas: Escribe en el archivo los resultados del benchmark
Funcionamiento: Escribe en el archivo output.txt y le da formato a los datos que se le pasan por parametro (los resultados del benchmark)
*/
void escribirResultados(int digitos, int codigo, double tiempo, double resultado){
	ofstream archivo;
	archivo.open("output.txt", fstream::in | fstream::app);
	archivo << "DIGITOS: " << digitos << endl << endl;
	archivo << "Duracion: " << fixed << setprecision(digitos) << tiempo << obtenerUnidad(codigo) << endl;
    archivo << "Resultado: " << resultado << endl << endl;
	archivo.close();
}

/*
Entradas: N/A
Salidas: Imprime en pantalla lo que hay en output.txt
Funcionamiento: Abre output.txt e imprime en pantalla su contenido
*/
void leerResultados(){
	ifstream archivo ("output.txt");
	string cadena;
	while(getline(archivo, cadena)){
        cout << cadena << endl;
	}
	archivo.close();
}

string obtenerUnidad(int codigo){
    switch(codigo){
        case 0: //nanosegundos
            return "ns";
        case 1: //microsegundos
            return "us";
        case 2: //milisegundos
            return "ms";
        case 3: //segundos
            return "s";
        case 4: //minutos
            return "min";
            break;
        case 5: //horas
            return "h";
        default:
            return "Sin especificar unidad";
    }
}

/*
Entradas: opcion de tipo entero y calculador de tipo Calculo
Salidas: Calcula una cantidad de digitos de PI acorde a la opción pasada por parametro
Funcionamiento: Verifica la opción pasada y calcula los dígitos de PI deseados y luego llama a escribir
*/
void opcionCalcular(int opcion, Calculo calculador){
    int codigo;
    switch(opcion){
    /*Los datos del parametro "sumatoria" son el minimo para obtener un resultado correcto*/
        case 1:     //Opcion 1 dígito
            codigo = calculador.calcular(19, 1);
            escribirResultados(1, codigo, calculador.getTiempo(), calculador.getPI());
            break;
        case 2:     //Opcion 2 dígito
            codigo = calculador.calcular(293, 2);
            escribirResultados(2, codigo, calculador.getTiempo(), calculador.getPI());
            break;
        case 3:     //Opcion 4 dígito
            codigo = calculador.calcular(17375, 4);
            escribirResultados(4, codigo, calculador.getTiempo(), calculador.getPI());
            break;
        case 4:     //Opcion 6 dígito
            codigo = calculador.calcular(20000004, 6);
            escribirResultados(6, codigo, calculador.getTiempo(), calculador.getPI());
            break;
        case 5:     //Opcion 8 dígito
            codigo = calculador.calcular(117000001, 8);
            escribirResultados(8, codigo, calculador.getTiempo(), calculador.getPI());
            break;
        case 6:     //Opcion 10 dígito
            codigo = calculador.calcular(16343000102LL, 10);
            escribirResultados(10, codigo, calculador.getTiempo(), calculador.getPI());
            break;
        case 7:     //Opcion volver
            system("cls");
            break;
        default:
            system("cls");
            cout << "Error: Selecione una opcion valida" << endl;
    }
}

/*
Entradas: N/A
Salidas: opción seleccionada por el usuario
Funcionamiento: Imprime en pantalla un menú y le pide al usuario que seleccione una opción
*/
int pedirCantidadDeDigitos(){
    int opcion;
    while(true){
        cout << "Ingrese la cantidad de digitos a calcular" << endl;
        cout << "1) 1 digito" << endl;
        cout << "2) 2 digitos" << endl;
        cout << "3) 4 digitos" << endl;
        cout << "4) 6 digitos" << endl;
        cout << "5) 8 digitos" << endl;
        cout << "6) 10 digitos" << endl;
        cout << "7) Atras" << endl;
        cin >> opcion;
        if (opcion > 0 && opcion < 8){
            break;
        }else{
            cout << "Error: Debe ingresar un número entre 1 y 7" << endl;
        }
    }
    return opcion;
}
