#ifndef CALCULO_H
#define CALCULO_H
#include <math.h>
#include <iostream>
#include <iomanip>
#include <thread>
#include <vector>
#include <stdio.h>
#include "Tiempo.h"


    class Calculo{
        public:
            Calculo();
            int calcular(int, int);
            int calcular(long long int, int);
            double getPI();
            double getTiempo();
        private:
            int duracion(int);
            double PI, tiempo, porcentaje;
            int mostrarPorcentaje(int, int, int, int);
            int mostrarPorcentaje(int, long long int, long long int, int);
    };

#endif // CALCULO_H
