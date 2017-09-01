#include <iostream>
#include <math.h>
#include <iomanip>
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;

double calcular(int, int);	//Calcula PI
double performanceCounter(LARGE_INTEGER*, LARGE_INTEGER*);	//Calcula el tiempo de ejecucion
void escribir(int, string, double, double);
void leer();

int main(int argc, char *argv[]){
	
	int o = 0;	//Opciones
	bool valido = false;
	
	cout << "Ingrese una opcion" << endl;
	
	while(true){	//Menu
		
		cout << "1) Calcular PI" << endl;
		cout << "2) Ver resultados" << endl;
		cout << "3) salir" << endl;
		cin >> o;
		
		switch(o){	//Validacion de opciones
			
			case 1:	//Opcion "Calcular PI"
				
				cout << "Ingrese la cantidad de digitos a calcular" << endl;
				valido = false;
				
				while(!valido){	//Menu 2
					
					cout << "1) 2" << endl;
					cout << "2) 4" << endl;
					cout << "3) 6" << endl;
					cout << "4) 8" << endl;
					cin >> o;
					
					
					switch(o){	//Validacion de opciones
							
						case 1:	//Opcion "2"
						
							cout << fixed << setprecision(2) << calcular(293, 2) << endl;	//Calular e imprimir 2 digito de PI
							
							valido = true;	//Salir del menu 2
							break;
							
						case 2:	//Opcion "4"
							
							cout << fixed << setprecision(4) << calcular(17375, 4) << endl;	//Calular e imprimir 4 digito de PI
							
							valido = true;	//Salir del menu 2
							break;
							
						case 3:	//Opcion "6"
							
							cout << fixed << setprecision(6) << calcular(20000004, 6) << endl;	//Calular e imprimir 6 digito de PI
							
							valido = true;	//Salir del menu 
							break;
							
						case 4:	//Opcion "8"
							
							cout << fixed << setprecision(8) << calcular(117000001, 8) << endl;	//Calular e imprimir 8 digito de PI
							
							valido = true;	//Salir del menu 
							break;
						
						default:	//Opcion no valida
							
							cout << "Selecione una opcion valida" << endl;	//Mensaje de error
						
					}
					
				}
				
				o = 0;	//Resetear opciones
				break;
				
			case 2:
				
				
				
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

double calcular(int sumatoria, int digitos){
	
	double PI = 0;
	double tiempo;
	LARGE_INTEGER ini, fin;
	
	QueryPerformanceCounter(&ini);	//Marca el inicio de la ejecion
	
	for(int i = 0; i <= sumatoria; i++){
		
		PI = PI + (pow(-1, i) / (2 * i + 1));	//Formula de Leibniz
		
	}
	
	QueryPerformanceCounter(&fin);	//Marca el final de la ejecion
	
	tiempo = performanceCounter(&fin, &ini);	//Calcula el tiempo de ejecucion
	
	if(tiempo < 0.001){
		
		cout << tiempo * 1000000 << " microsegundos a " << digitos << " digitos" << endl;
		escribir(digitos, "µs", tiempo * 1000000, PI * 4);
		
	}else if(tiempo < 1){
		
		cout << tiempo * 1000 << " milisegundos a " << digitos << " digitos" << endl;	//Imprime el tiempo de ejecucion en milisegundos
		escribir(digitos, "ms", tiempo * 1000, PI * 4);
		
	}else if(tiempo < 60){
	
		cout << tiempo << " segundos a " << digitos << " digitos" << endl;	//Imprime el tiempo de ejecucion en segundos
		escribir(digitos, "s", tiempo, PI * 4);
	
	}else if(tiempo > 60){
		
		cout << tiempo / 60 << " minutos a " << digitos << " digitos" << endl;	//Imprime el tiempo de ejecucion en minutos
		escribir(digitos, "min", tiempo / 60, PI * 4);
		
	}	
	
	return PI * 4;
	
}

double performanceCounter(LARGE_INTEGER *fin, LARGE_INTEGER *ini){
	
	LARGE_INTEGER freq;	//Frecuencia del procesador (Hz)
	QueryPerformanceFrequency(&freq);	//Obtiene la frecuencia
	
	return (double)(fin -> QuadPart - ini -> QuadPart) / (double)freq.QuadPart;	//Calcula el tiempo de ejecucion
	
}

void escribir(int digitos, string duracion, double tiempo, double resultado){	//Almacena los datos
	
	ofstream f;
	
	f.open("output.txt", fstream::in | fstream::out | fstream::ate);
	
	f << digitos << " DIGITOS" << endl << endl << "Duracion: " << fixed << setprecision(digitos) << tiempo << duracion << endl << "Resultado: " << resultado << endl;
	
	f.close();
	
}

void leer(){
	
	ifstream fe ("output.txt");
	string cadena;
	
	while(!fe.eof()){
		
		fe >> cadena;
		cout << cadena << endl;
		
	}
	
	fe.close();
	
}
