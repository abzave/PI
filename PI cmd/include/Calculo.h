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

            Calculo();   //Constructor
            int calcular(long long int, int);   //Calcula PI en mononucleo
            double getPI();  //Getter de "PI"
            double getTiempo();  //Getter de "tiempo"

        private:

            double performanceCounter(LARGE_INTEGER*, LARGE_INTEGER*);   //Calcula el tiempo de ejecucion
            double PI, tiempo, porcentaje;  //"PI" almacena PI    "tiempo" almacena el tiempo de ejecucion  "porcentaje" almacena el progreso del calculo
            LARGE_INTEGER ini, fin; //Marcadores de tiempo de ejecucion

    };

#endif // CALCULO_H
