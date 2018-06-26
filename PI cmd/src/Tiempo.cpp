#include "Tiempo.h"
/*
Entradas: inicio y fin de tipo puntero a un large_initeger
Salidas: Calcula la diferencia de tiempo en segundos entre inicio y fin
Funcionamiento: Aplica una media entre inicio y fin con la frecuencia del procesador
*/
double Tiempo::performanceCounter(LARGE_INTEGER* inicio, LARGE_INTEGER* fin){ //Calcula el tiempo de ejecucion
    LARGE_INTEGER frecuencia; //Almacena la frecuencia del procesador
    QueryPerformanceFrequency(&frecuencia);   //Obtiene la frequencia del procesador
    return (double)(fin -> QuadPart - inicio -> QuadPart) / (double)frecuencia.QuadPart; //Realiza el calculo del tiempo de ejecucion y lo devuelve

}

/*
Entradas: N/A
Salidas: Guarda en inicio el tiempo actual
Funcionamiento: Inicia el "cronometro"
*/
void Tiempo::iniciar(){ //Marca el inicio
    QueryPerformanceCounter(&inicio);
}

/*
Entradas: N/A
Salidas: Guarda en fin el tiempo actual
Funcionamiento: Finaliza el "cronometro"
*/
void Tiempo::finalizar(){   //Marca el final
    QueryPerformanceCounter(&fin);
}

/*
Entradas: N/A
Salidas: Devuelve el tiempo transcurrido
Funcionamiento: Devuelve el tiempo en segundo transcurrido entre los llamdados a iniciar y finalizar
*/
double Tiempo::duracion(){
    return performanceCounter(&inicio, &fin);
}


