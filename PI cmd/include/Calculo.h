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
            int calcular(unsigned int, unsigned short int);
            int calcular(unsigned long long int, unsigned short int);
            double getPI();
            double getTiempo();
        private:
            int duracion(unsigned short int);
            double PI, tiempo, porcentaje;
            int mostrarPorcentaje(unsigned int, unsigned int, unsigned int, unsigned int);
            int mostrarPorcentaje(unsigned int, unsigned long long int, unsigned long long int, unsigned int);
    };

#endif // CALCULO_H
