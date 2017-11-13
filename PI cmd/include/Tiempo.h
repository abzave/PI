#ifndef TIEMPO_H
#define TIEMPO_H

#include <windows.h>

class Tiempo
{
    public:

        void iniciar(); //Marca el inicio
        void finalizar();   //Marca el final
        double duracion();

    private:

        double performanceCounter(LARGE_INTEGER*, LARGE_INTEGER*);   //Calcula el tiempo de ejecucion

        /*Marcadores de tiempo de ejecucion*/

        LARGE_INTEGER inicio;
        LARGE_INTEGER fin;

};

#endif // TIEMPO_H
