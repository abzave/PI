#include "Calculo.h"

using namespace std;

bool Calculo::calculando = false;

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
void Calculo::calcular(INT64 sumatoria, int digitos, HWND barraProgreso){    //Calcula PI en mononucleo

    calculando = true;
    PI = 0; //Cambia el valor de PI
    int count = 1;
    LPCSTR r;    //Almacena los resultados en un string
    static RESULTADOS result;
    stringstream sstr("");

    QueryPerformanceCounter(&ini);  //Marca el inicio de la ejecucion
    for(long long int i = 0; i <= sumatoria; i++){

        PI = PI + (pow(-1, i) / (2 * i + 1));   //Formula de Leibniz

        QueryPerformanceCounter(&fin);

        if(performanceCounter(&ini, &fin) == 1 * count){

            porcentaje = ((double)i / (double)sumatoria) * 100;
            SendMessage(barraProgreso, PBM_SETPOS, (WPARAM)porcentaje, 0);

            count++;

        }

    }

    QueryPerformanceCounter(&fin);  //Marca el final de la ejecucion
    tiempo = performanceCounter(&ini, &fin);    //Calcula el total del tiempo de ejecucion

    SendMessage(barraProgreso, PBM_SETPOS, (WPARAM)0, 0);

    if(tiempo < 0.000001){  //nanosegundo

        tiempo = tiempo * 1000000000;   //Pasa el tiempo a una unidad menor y lo almacena

        result.digitos = digitos;
        result.PI = PI * 4;
        result.tiempo = tiempo;
        result.codigo = 1;

        sstr << "Resultado: " << fixed << setprecision(digitos) << result.PI << endl << setprecision(1) <<
        "Tiempo: " << result.tiempo << " nanosegundos a " << result.digitos << " digitos";

    }else if(tiempo < 0.001){   //microsegundo

        tiempo = tiempo * 1000000;  //Pasa el tiempo a una unidad menor y lo almacena

        result.digitos = digitos;
        result.PI = PI * 4;
        result.tiempo = tiempo;
        result.codigo = 2;

        sstr << "Resultado: " << fixed << setprecision(digitos) << result.PI << endl << setprecision(1) <<
        "Tiempo: " << result.tiempo << " microsegundos a " << result.digitos << " digitos";

    }else if(tiempo < 1){   //milisegundo

        tiempo = tiempo * 1000; //Pasa el tiempo a una unidad menor y lo almacena

        result.digitos = digitos;
        result.PI = PI * 4;
        result.tiempo = tiempo;
        result.codigo = 3;

        sstr << "Resultado: " << fixed << setprecision(digitos) << result.PI << endl << setprecision(1) <<
        "Tiempo: " << result.tiempo << " milisegundos a " << result.digitos << " digitos";

    }else if(tiempo < 60){  //segundo

        result.digitos = digitos;
        result.PI = PI * 4;
        result.tiempo = tiempo;
        result.codigo = 4;

        sstr << "Resultado: " << fixed << setprecision(digitos) << result.PI << endl << setprecision(1) <<
        "Tiempo: " << result.tiempo << " segundos a " << result.digitos << " digitos";


    }else if(tiempo > 60 && tiempo < 3600){ //minutos

        tiempo = tiempo / 60;   //Pasa el tiempo a una unidad mayor y lo almacena

        result.digitos = digitos;
        result.PI = PI * 4;
        result.tiempo = tiempo;
        result.codigo = 5;

        sstr << "Resultado: " << fixed << setprecision(digitos) << result.PI << endl << setprecision(1) <<
        "Tiempo: " << result.tiempo << " minutos a " << result.digitos << " digitos";

    }else if(tiempo > 3600){    //horas

        tiempo = tiempo / 3600; //Pasa el tiempo a una unidad mayor y lo almacena

        result.digitos = digitos;
        result.PI = PI * 4;
        result.tiempo = tiempo;
        result.codigo = 6;

        sstr << "Resultado: " << fixed << setprecision(digitos) << result.PI << endl << setprecision(1) <<
        "Tiempo: " << result.tiempo << " horas a " << result.digitos << " digitos";

    }

    r = sstr.str().c_str();
    MessageBox(NULL, r, "Resultados", MB_ICONASTERISK); //Mensaje con los resultados
    escribir(&result);

    calculando = false;

}
void Calculo::escribir(RESULTADOS* mensaje){


    FILE* ficheroEntrada;

    if(!(ficheroEntrada = fopen("output.rst", "ab"))){

        MessageBox(NULL, "Error al crear archivo", "Error", MB_ICONERROR);

    }

    fwrite(mensaje, sizeof(RESULTADOS), 1, ficheroEntrada);
    fclose(ficheroEntrada);

}
bool Calculo::estaCalculando(){

    return calculando;

}
double Calculo::getPI(){    //Getter de "PI"

    return PI * 4;

}
double Calculo::getTiempo(){    //Getter de "tiempo"

    return tiempo;

}
