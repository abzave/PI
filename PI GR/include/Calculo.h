#ifndef CALCULO_H
#define CALCULO_H
#include <windows.h>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <tchar.h>
#include <stdio.h>
#include <string>
#include <fstream>

    class Calculo{
        public:

            Calculo();   //Constructor
            void calcular(INT64, int);   //Calcula PI en mononucleo
            double getPI();  //Getter de "PI"
            double getTiempo();  //Getter de "tiempo"

            typedef struct{

                double PI;
                double tiempo;
                int digitos;

            }RESULTADOS;

        private:

            void escribir(RESULTADOS*);
            double performanceCounter(LARGE_INTEGER*, LARGE_INTEGER*);   //Calcula el tiempo de ejecucion
            double PI, tiempo, porcentaje;  //"PI" almacena PI    "tiempo" almacena el tiempo de ejecucion  "porcentaje" almacena el progreso del calculo
            LARGE_INTEGER ini, fin; //Marcadores de tiempo de ejecucion

    };

#endif // CALCULO_H
