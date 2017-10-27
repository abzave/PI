#include "Calculo.h"

using namespace std;

Calculo::Calculo(){

    tiempo = 0; //Inicializa "tiempo"
    porcentaje = 0; //Inicializa "porcentaje"
    PI = 0; //Inicializa "PI"

}
double Calculo::performanceCounter(LARGE_INTEGER *ini, LARGE_INTEGER *fin){

    LARGE_INTEGER freq; //Almacena la frecuencia del procesador
    QueryPerformanceFrequency(&freq);   //Obtiene la frequencia del procesador

    return (double)(fin -> QuadPart - ini -> QuadPart) / (double)freq.QuadPart; //Realiza el calculo del tiempo de ejecucion y lo devuelve

}
int Calculo::calcular(long long int sumatoria, int digitos){

    int count = 1;  //Contador de minutos transcurridos
    PI = 0; //Cambia el valor de PI
    QueryPerformanceCounter(&ini);  //Marca el inicio de la ejecucion

    for(long long int i = 0; i <= sumatoria; i++){

        PI = PI + (pow(-1, i) / (2 * i + 1));   //Formula de Leibniz

        QueryPerformanceCounter(&fin);  //Marcador para calcular el tiempo transcurrido
        if(performanceCounter(&ini, &fin) == 60 * count){

            porcentaje = ((double)i / (double)sumatoria) * 100; //Calcula el porcentaje de ejecucion
            cout << fixed << setprecision(1) << porcentaje << "%" << endl;  //Imprime el porcentaje
            count++;

        }

    }

    QueryPerformanceCounter(&fin);  //Marca el final de la ejecucion
    tiempo = performanceCounter(&ini, &fin);    //Calcula el total del tiempo de ejecucion

    cout << fixed << setprecision(digitos) << endl << PI * 4 << endl;   //Imprime el resultado del calculo

    if(tiempo < 0.000001){

        tiempo = tiempo * 1000000000;   //Pasa el tiempo a una unidad menor y lo almacena

        cout << fixed << setprecision(2) << tiempo << " nanosegundos a " << digitos << " digitos" << endl << endl;  //Imprime el tiempo
        return 0;   //Codigo para especificar unidad de tiempo

    }else if(tiempo < 0.001){

        tiempo = tiempo * 1000000;  //Pasa el tiempo a una unidad menor y lo almacena

        cout << fixed << setprecision(2) << tiempo << " microsegundos a " << digitos << " digitos" << endl << endl; //Imprime el tiempo
        return 1;   //Codigo para especificar unidad de tiempo

    }else if(tiempo < 1){

        tiempo = tiempo * 1000; //Pasa el tiempo a una unidad menor y lo almacena

        cout << fixed << setprecision(2) << tiempo << " milisegundos a " << digitos << " digitos" << endl << endl;  //Imprime el tiempo
        return 2;   //Codigo para especificar unidad de tiempo

    }else if(tiempo < 60){

        cout << fixed << setprecision(2) << tiempo << " segundos a " << digitos << " digitos" << endl << endl;  //Imprime el tiempo
        return 3;   //Codigo para especificar unidad de tiempo

    }else if(tiempo > 60 && tiempo < 3600){

        tiempo = tiempo / 60;   //Pasa el tiempo a una unidad mayor y lo almacena

        cout << fixed << setprecision(2) << tiempo << " minutos a " << digitos << " digitos" << endl << endl;   //Imprime el tiempo
        return 4;   //Codigo para especificar unidad de tiempo

    }else if(tiempo > 3600){

        tiempo = tiempo / 3600; //Pasa el tiempo a una unidad mayor y lo almacena

        cout << fixed << setprecision(2) << tiempo << " horas a " << digitos << " digitos" << endl << endl; //Imprime el tiempo
        return 5;   //Codigo para especificar unidad de tiempo

    }

}
double Calculo::getPI(){

    return PI * 4;

}
double Calculo::getTiempo(){

    return tiempo;

}
