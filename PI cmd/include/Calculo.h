#ifndef CALCULO_H
#define CALCULO_H
#include <math.h>
#include <iostream>
#include <iomanip>
#include <thread>
#include <vector>
#include <stdio.h>


    class Calculo{
        public:

            Calculo();   //Constructor
            int calcular(long long int, int);   //Calcula PI en mononucleo
            double getPI();  //Getter de "PI"
            double getTiempo();  //Getter de "tiempo"

        private:

            int duracion(int);
            double PI, tiempo, porcentaje;  //"PI" almacena PI    "tiempo" almacena el tiempo de ejecucion  "porcentaje" almacena el progreso del calculo

    };

#endif // CALCULO_H
