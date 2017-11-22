#include "Calculo.h"

using namespace std;



Calculo::Calculo(){ //Constructor

    tiempo = 0; //Inicializa "tiempo"
    porcentaje = 0; //Inicializa "porcentaje"
    PI = 0; //Inicializa "PI"

}
double Calculo::performanceCounter(LARGE_INTEGER *ini, LARGE_INTEGER *fin){ //Calcula el tiempo de ejecucion

    LARGE_INTEGER freq; //Almacena la frecuencia del procesador
    QueryPerformanceFrequency(&freq);   //Obtiene la frequencia del procesador

    return (double)(fin -> QuadPart - ini -> QuadPart) / (double)freq.QuadPart; //Realiza el calculo del tiempo de ejecucion y lo devuelve

}
void Calculo::calcular(INT64 sumatoria, int digitos){    //Calcula PI en mononucleo

    int count = 1;  //Contador de minutos transcurridos
    PI = 0; //Cambia el valor de PI
    QueryPerformanceCounter(&ini);  //Marca el inicio de la ejecucion
    TCHAR r[32];    //Almacena los resultados en un string
    static RESULTADOS result;

    for(long long int i = 0; i <= sumatoria; i++){

        PI = PI + (pow(-1, i) / (2 * i + 1));   //Formula de Leibniz

        QueryPerformanceCounter(&fin);  //Marcador para calcular el tiempo transcurrido
        if(performanceCounter(&ini, &fin) == 30 * count){

            porcentaje = ((double)i / (double)sumatoria) * 100; //Calcula el porcentaje de ejecucion
            cout << fixed << setprecision(1) << porcentaje << "%" << endl;  //Imprime el porcentaje
            count++;

        }

    }

    QueryPerformanceCounter(&fin);  //Marca el final de la ejecucion
    tiempo = performanceCounter(&ini, &fin);    //Calcula el total del tiempo de ejecucion

    if(tiempo < 0.000001){  //nanosegundo

        tiempo = tiempo * 1000000000;   //Pasa el tiempo a una unidad menor y lo almacena

        result.digitos = digitos;
        result.PI = PI * 4;
        result.tiempo = tiempo;

        switch(digitos){

            case 1: //1 digito

                sprintf(r, "Resultado: %0.1f\nTiempo: %0.1f nanosegundos a %i digito   ", PI * 4, tiempo, digitos);    //Pasa los datos a un string
                break;

            case 2: //2 digitos

                sprintf(r, "Resultado: %0.2f\nTiempo: %0.1f nanosegundos a %i digitos", PI * 4, tiempo, digitos);   //Pasa los datos a un string
                break;

            case 4: //4 digitos

                sprintf(r, "Resultado: %0.4f\nTiempo: %0.1f nanosegundos a %i digitos", PI * 4, tiempo, digitos);   //Pasa los datos a un string
                break;

            case 6: //6 digitos

                sprintf(r, "Resultado: %0.6f\nTiempo: %0.1f nanosegundos a %i digitos", PI * 4, tiempo, digitos);   //Pasa los datos a un string
                break;

            case 8: //8 digitos

                sprintf(r, "Resultado: %0.8f\nTiempo: %0.1f nanosegundos a %i digitos", PI * 4, tiempo, digitos);   //Pasa los datos a un string
                break;

            case 10:    //10 digitos

                sprintf(r, "Resultado: %0.10f\nTiempo: %0.1f nanosegundos a %i digitos", PI * 4, tiempo, digitos);  //Pasa los datos a un string
                break;

        }

         MessageBox(NULL, r, "Resultados", MB_ICONASTERISK);    //Mensaje con los resultados

    }else if(tiempo < 0.001){   //microsegundo

        tiempo = tiempo * 1000000;  //Pasa el tiempo a una unidad menor y lo almacena

        result.digitos = digitos;
        result.PI = PI * 4;
        result.tiempo = tiempo;

        switch(digitos){

            case 1: //1 digito

                sprintf(r, "Resultado: %0.1f\nTiempo: %0.1f microsegundos a %i digito   ", PI * 4, tiempo, digitos);   //Pasa los datos a un string
                break;

            case 2: //2 digitos

                sprintf(r, "Resultado: %0.2f\nTiempo: %0.1f microsegundos a %i digitos", PI * 4, tiempo, digitos);  //Pasa los datos a un string
                break;

            case 4: //4 digitos

                sprintf(r, "Resultado: %0.4f\nTiempo: %0.1f microsegundos a %i digitos", PI * 4, tiempo, digitos);  //Pasa los datos a un string
                break;

            case 6: //6 digitos

                sprintf(r, "Resultado: %0.6f\nTiempo: %0.1f microsegundos a %i digitos", PI * 4, tiempo, digitos);  //Pasa los datos a un string
                break;

            case 8: //8 digitos

                sprintf(r, "Resultado: %0.8f\nTiempo: %0.1f microsegundos a %i digitos", PI * 4, tiempo, digitos);  //Pasa los datos a un string
                break;

            case 10:    //10 digitos

                sprintf(r, "Resultado: %0.10f\nTiempo: %0.1f microsegundos a %i digitos", PI * 4, tiempo, digitos); //Pasa los datos a un string
                break;

        }

        MessageBox(NULL, r, "Resultados", MB_ICONASTERISK); //Mensaje con los resultados

    }else if(tiempo < 1){   //milisegundo

        tiempo = tiempo * 1000; //Pasa el tiempo a una unidad menor y lo almacena

        result.digitos = digitos;
        result.PI = PI * 4;
        result.tiempo = tiempo;

        switch(digitos){

            case 1: //1 digito

                sprintf(r, "Resultado: %0.1f\nTiempo: %0.1f milisegundos a %i digito   ", PI * 4, tiempo, digitos);    //Pasa los datos a un string
                break;

            case 2: //2 digitos

                sprintf(r, "Resultado: %0.2f\nTiempo: %0.1f milisegundos a %i digitos", PI * 4, tiempo, digitos);   //Pasa los datos a un string
                break;

            case 4: //4 digitos

                sprintf(r, "Resultado: %0.4f\nTiempo: %0.1f milisegundos a %i digitos", PI * 4, tiempo, digitos);   //Pasa los datos a un string
                break;

            case 6: //6 digitos

                sprintf(r, "Resultado: %0.6f\nTiempo: %0.1f milisegundos a %i digitos", PI * 4, tiempo, digitos);   //Pasa los datos a un string
                break;

            case 8: //8 digitos

                sprintf(r, "Resultado: %0.8f\nTiempo: %0.1f milisegundos a %i digitos", PI * 4, tiempo, digitos);   //Pasa los datos a un string
                break;

            case 10:    //10 digitos

                sprintf(r, "Resultado: %0.10f\nTiempo: %0.1f milisegundos a %i digitos", PI * 4, tiempo, digitos);  //Pasa los datos a un string
                break;

        }

        MessageBox(NULL, r, "Resultados", MB_ICONASTERISK); //Mensaje con los resultados

    }else if(tiempo < 60){  //segundo

        result.digitos = digitos;
        result.PI = PI * 4;
        result.tiempo = tiempo;

        switch(digitos){

            case 1: //1 digito

                sprintf(r, "Resultado: %0.1f\nTiempo: %0.1f segundos a %i digito   ", PI * 4, tiempo, digitos);    //Pasa los datos a un string
                break;

            case 2: //2 digitos

                sprintf(r, "Resultado: %0.2f\nTiempo: %0.1f segundos a %i digitos", PI * 4, tiempo, digitos);   //Pasa los datos a un string
                break;

            case 4: //4 digitos

                sprintf(r, "Resultado: %0.4f\nTiempo: %0.1f segundos a %i digitos", PI * 4, tiempo, digitos);   //Pasa los datos a un string
                break;

            case 6: //6 digitos

                sprintf(r, "Resultado: %0.6f\nTiempo: %0.1f segundos a %i digitos", PI * 4, tiempo, digitos);   //Pasa los datos a un string
                break;

            case 8: //8 digitos

                sprintf(r, "Resultado: %0.8f\nTiempo: %0.1f segundos a %i digitos", PI * 4, tiempo, digitos);   //Pasa los datos a un string
                break;

            case 10:    //10 digitos

                sprintf(r, "Resultado: %0.10f\nTiempo: %0.1f segundos a %i digitos", PI * 4, tiempo, digitos);  //Pasa los datos a un string
                break;

        }

        MessageBox(NULL, r, "Resultados", MB_ICONASTERISK); //Mensaje con los resultados

    }else if(tiempo > 60 && tiempo < 3600){ //minutos

        tiempo = tiempo / 60;   //Pasa el tiempo a una unidad mayor y lo almacena

        result.digitos = digitos;
        result.PI = PI * 4;
        result.tiempo = tiempo;

        switch(digitos){

            case 1: //1 digito

                sprintf(r, "Resultado: %0.1f\nTiempo: %0.1f minutos a %i digito   ", PI * 4, tiempo, digitos); //Pasa los datos a un string
                break;

            case 2: //2 digitos

                sprintf(r, "Resultado: %0.2f\nTiempo: %0.1f minutos a %i digitos", PI * 4, tiempo, digitos);    //Pasa los datos a un string
                break;

            case 4: //4 digitos

                sprintf(r, "Resultado: %0.4f\nTiempo: %0.1f minutos a %i digitos", PI * 4, tiempo, digitos);    //Pasa los datos a un string
                break;

            case 6: //6 digitos

                sprintf(r, "Resultado: %0.6f\nTiempo: %0.1f minutos a %i digitos", PI * 4, tiempo, digitos);    //Pasa los datos a un string
                break;

            case 8: //8 digitos

                sprintf(r, "Resultado: %0.8f\nTiempo: %0.1f minutos a %i digitos", PI * 4, tiempo, digitos);    //Pasa los datos a un string
                break;

            case 10:    //10 digitos

                sprintf(r, "Resultado: %0.10f\nTiempo: %0.1f minutos a %i digitos", PI * 4, tiempo, digitos);   //Pasa los datos a un string
                break;

        }

        MessageBox(NULL, r, "Resultados", MB_ICONASTERISK); //Mensaje con los resultados

    }else if(tiempo > 3600){    //horas

        tiempo = tiempo / 3600; //Pasa el tiempo a una unidad mayor y lo almacena

        result.digitos = digitos;
        result.PI = PI * 4;
        result.tiempo = tiempo;

        switch(digitos){

            case 1: //1 digito

                sprintf(r, "Resultado: %0.1f\nTiempo: %0.1f horas a %i digito   ", PI * 4, tiempo, digitos);   //Pasa los datos a un string
                break;

            case 2: //2 digitos

                sprintf(r, "Resultado: %0.2f\nTiempo: %0.1f horas a %i digitos", PI * 4, tiempo, digitos);  //Pasa los datos a un string
                break;

            case 4: //4 digitos

                sprintf(r, "Resultado: %0.4f\nTiempo: %0.1f horas a %i digitos", PI * 4, tiempo, digitos);  //Pasa los datos a un string
                break;

            case 6: //6 digitos

                sprintf(r, "Resultado: %0.6f\nTiempo: %0.1f horas a %i digitos", PI * 4, tiempo, digitos);  //Pasa los datos a un string
                break;

            case 8: //8 digitos

                sprintf(r, "Resultado: %0.8f\nTiempo: %0.1f horas a %i digitos", PI * 4, tiempo, digitos);  //Pasa los datos a un string
                break;

            case 10:    //10 digitos

                sprintf(r, "Resultado: %0.10f\nTiempo: %0.1f horas a %i digitos", PI * 4, tiempo, digitos); //Pasa los datos a un string
                break;

        }

        MessageBox(NULL, r, "Resultados", MB_ICONASTERISK); //Mensaje con los resultados

    }

    escribir(&result);

}
void Calculo::escribir(RESULTADOS* mensaje){


    FILE* ficheroEntrada;
    ficheroEntrada = fopen("output.rst", "ab");
    fwrite(mensaje, sizeof(RESULTADOS), 1, ficheroEntrada);
    fclose(ficheroEntrada);

}
double Calculo::getPI(){    //Getter de "PI"

    return PI * 4;

}
double Calculo::getTiempo(){    //Getter de "tiempo"

    return tiempo;

}
