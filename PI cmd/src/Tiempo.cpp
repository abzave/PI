#include "Tiempo.h"

double Tiempo::performanceCounter(LARGE_INTEGER* inicio, LARGE_INTEGER* fin){ //Calcula el tiempo de ejecucion

    LARGE_INTEGER frecuencia; //Almacena la frecuencia del procesador
    QueryPerformanceFrequency(&frecuencia);   //Obtiene la frequencia del procesador

    return (double)(fin -> QuadPart - inicio -> QuadPart) / (double)frecuencia.QuadPart; //Realiza el calculo del tiempo de ejecucion y lo devuelve

}
void Tiempo::iniciar(){ //Marca el inicio

    QueryPerformanceCounter(&inicio);

}
void Tiempo::finalizar(){   //Marca el final

    QueryPerformanceCounter(&fin);

}
double Tiempo::duracion(){

    return performanceCounter(&inicio, &fin);

}


