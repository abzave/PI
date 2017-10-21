#ifndef CALCULO_H
#define CALCULO_H
#include <windows.h>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <thread>
#include <vector>

    class Calculo{
        public:

            inline Calculo();   //Constructor
            inline int calcular(long long int, int);   //Calcula PI en mononucleo
            inline double getPI();  //Getter de "PI"
            inline double getTiempo();  //Getter de "tiempo"

        private:

            inline double performanceCounter(LARGE_INTEGER*, LARGE_INTEGER*);   //Calcula el tiempo de ejecucion
            double PI, tiempo, porcentaje;  //"PI" almacena PI    "tiempo" almacena el tiempo de ejecucion  "porcentaje" almacena el progreso del calculo
            LARGE_INTEGER ini, fin; //Marcadores de tiempo de ejecucion

    };

#endif // CALCULO_H
