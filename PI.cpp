#include <iostream>
#include <math.h>
#include <iomanip>
#include <windows.h>

using namespace std;

double calcular(int);	//Calcula PI
double performanceCounter(LARGE_INTEGER*, LARGE_INTEGER*);	//Calcula el tiempo de ejecucion

int main(int argc, char *argv[]){
	
	int o = 0;	//Opciones
	bool valido = false;
	
	cout << "Ingrese una opcion" << endl;
	
	while(true){	//Menu
		
		cout << "1) Calcular PI" << endl;
		cout << "2) salir" << endl;
		cin >> o;
		
		switch(o){	//Validacion de opciones
			
			case 1:	//Opcion "Calcular PI"
				
				cout << "Ingrese la cantidad de digitos a calcular" << endl;
				valido = false;
				
				while(!valido){	//Menu 2
					
					cout << "2) 2" << endl;
					cout << "3) 4" << endl;
					cout << "4) 6" << endl;
					cout << "5) 8" << endl;
					cin >> o;
					
					
					switch(o){	//Validacion de opciones
							
						case 1:	//Opcion "2"
						
							cout << fixed << setprecision(2) << calcular(293) << endl;	//Calular e imprimir 2 digito de PI
							
							valido = true;	//Salir del menu 2
							break;
							
						case 2:	//Opcion "4"
							
							cout << fixed << setprecision(4) << calcular(17375) << endl;	//Calular e imprimir 4 digito de PI
							
							valido = true;	//Salir del menu 2
							break;
							
						case 3:	//Opcion "6"
							
							cout << fixed << setprecision(6) << calcular(20000004) << endl;	//Calular e imprimir 6 digito de PI
							
							valido = true;	//Salir del menu 
							break;
							
						case 4:	//Opcion "8"
							
							cout << fixed << setprecision(8) << calcular(117000001) << endl;	//Calular e imprimir 8 digito de PI
							
							valido = true;	//Salir del menu 
							break;
						
						default:	//Opcion no valida
							
							cout << "Selecione una opcion valida" << endl;	//Mensaje de error
						
					}
					
				}
				
				o = 0;	//Resetear opciones
				break;
				
			case 2:	//Opcion "Salir"
				
				exit(0);
				break;
			
			default:	//Opcion no valida
				
				cout << "Selecione una opcion valida" << endl;	//Mensaje de error
				
		}
		
	}
	
	return 0;
	
}

double calcular(int sumatoria){
	
	double PI = 0;
	double tiempo;
	LARGE_INTEGER ini, fin;
	
	QueryPerformanceCounter(&ini);	//Marca el inicio de la ejecion
	
	for(int i = 0; i <= sumatoria; i++){
		
		PI = PI + (pow(-1, i) / (2 * i + 1));	//Formula de Leibniz
		
	}
	
	QueryPerformanceCounter(&fin);	//Marca el final de la ejecion
	
	tiempo = performanceCounter(&fin, &ini);	//Calcula el tiempo de ejecucion
	
	if(tiempo < 1){
		
		cout << tiempo * 1000 << " milisegundos" << endl;	//Imprime el tiempo de ejecucion en milisegundos
		
	}else if(tiempo < 60){
	
		cout << tiempo << " segundos" << endl;	//Imprime el tiempo de ejecucion en segundos
	
	}else if(tiempo > 60){
		
		cout << tiempo / 60 << " minutos" << endl;	//Imprime el tiempo de ejecucion en minutos
		
	}
	
	
	return PI * 4;
	
}

double performanceCounter(LARGE_INTEGER *fin, LARGE_INTEGER *ini){
	
	LARGE_INTEGER freq;	//Frecuencia del procesador (Hz)
	QueryPerformanceFrequency(&freq);	//Obtiene la frecuencia
	
	return (double)(fin -> QuadPart - ini -> QuadPart) / (double)freq.QuadPart;	//Calcula el tiempo de ejecucion
	
}
