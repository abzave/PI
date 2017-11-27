#include "Calculo.h"
#include "Tiempo.h"

using namespace std;

bool Calculo::calculando = false;   //Inicializa "calculando"

Calculo::Calculo(){ //Constructor

    tiempo = 0; //Inicializa "tiempo"
    porcentaje = 0; //Inicializa "porcentaje"
    PI = 0; //Inicializa "PI"

}

void Calculo::calcular(INT64 sumatoria, int digitos, HWND barraProgreso){    //Calcula PI en mononucleo

    calculando = true;  //Marca el inicio del calculo
    PI = 0; //Cambia el valor de "PI"
    int count = 1;  //Contador
    LPCSTR mensajeFinal;    //Almacena los resultados en un string
    static RESULTADOS resultados;   //Almacena los resultados
    Tiempo temporizador;

    temporizador.iniciar();  //Marca el inicio de la ejecucion
    for(long long int i = 0; i <= sumatoria; i++){

        PI = PI + (pow(-1, i) / (2 * i + 1));   //Formula de Leibniz

        /*La comprobacion del tiempo se añadio para reducir significativamente el tiempo de calculo ya
        que al estar actualizando la barra de progreso la duracion del calculo aumentaba significativamente*/

        temporizador.finalizar();  //Marca el tiempo actual
        if(temporizador.duracion() == 1 * count){ //Comprueba que haya pasado un segundo

            porcentaje = ((double)i / (double)sumatoria) * 100; //Calculo el porcentaje de calculo
            SendMessage(barraProgreso, PBM_SETPOS, (WPARAM)porcentaje, 0);  //Actualiza la barra de progreso

            count++;

        }

    }

    temporizador.finalizar();  //Marca el final de la ejecucion
    tiempo = temporizador.duracion();    //Calcula el total del tiempo de ejecucion

    SendMessage(barraProgreso, PBM_SETPOS, (WPARAM)0, 0);   //Resetea la barra de progreso

    resultados.digitos = digitos;   //Guarda la cantidad de digitos
    resultados.PI = PI * 4; //Guarda el resultado del calculo

    mensajeFinal = duracion(&resultados, digitos);  //Almacena el mensaje a mostrar

    MessageBox(NULL, mensajeFinal, "Resultados", MB_ICONASTERISK); //Mensaje con los resultados
    escribir(&resultados);  //Guarda los resultados en "output.rst"

    calculando = false; //Marca el final del calculo

}

LPCSTR Calculo::duracion(RESULTADOS* resultados, int digitos){

    stringstream resultadosTexto("");   //Almacena el mensaje

    if(tiempo < 0.000001){  //nanosegundo

        tiempo = tiempo * 1000000000;   //Pasa el tiempo a una unidad menor y lo almacena

        resultados -> tiempo = tiempo;  //Guarda el tiempo de ejecucion
        resultados -> codigo = 1;   //Guarda el codigo correspondiente a "ns"

        resultadosTexto << "Resultado: " << fixed << setprecision(digitos) << resultados -> PI << endl << setprecision(1) <<
        "Tiempo: " << resultados -> tiempo << " nanosegundos a " << resultados -> digitos << " digitos";    //Guarda el mensaje

    }else if(tiempo < 0.001){   //microsegundo

        tiempo = tiempo * 1000000;  //Pasa el tiempo a una unidad menor y lo almacena

        resultados -> tiempo = tiempo;  //Guarda el tiempo de ejecucion
        resultados -> codigo = 2;   //Guarda el codigo correspondiente a "us"

        resultadosTexto << "Resultado: " << fixed << setprecision(digitos) << resultados -> PI << endl << setprecision(1) <<
        "Tiempo: " << resultados -> tiempo << " microsegundos a " << resultados -> digitos << " digitos";   //Guarda el mensaje

    }else if(tiempo < 1){   //milisegundo

        tiempo = tiempo * 1000; //Pasa el tiempo a una unidad menor y lo almacena

        resultados -> tiempo = tiempo;  //Guarda el tiempo de ejecucion
        resultados -> codigo = 3;   //Guarda el codigo correspondiente a "ms"

        resultadosTexto << "Resultado: " << fixed << setprecision(digitos) << resultados -> PI << endl << setprecision(1) <<
        "Tiempo: " << resultados -> tiempo << " milisegundos a " << resultados -> digitos << " digitos";    //Guarda el mensaje

    }else if(tiempo < 60){  //segundo

        resultados -> tiempo = tiempo;  //Guarda el tiempo de ejecucion
        resultados -> codigo = 4;   //Guarda el codigo correspondiente a "s"

        resultadosTexto << "Resultado: " << fixed << setprecision(digitos) << resultados -> PI << endl << setprecision(1) <<
        "Tiempo: " << resultados -> tiempo << " segundos a " << resultados -> digitos << " digitos";    //Guarda el mensaje


    }else if(tiempo > 60 && tiempo < 3600){ //minutos

        tiempo = tiempo / 60;   //Pasa el tiempo a una unidad mayor y lo almacena

        resultados -> tiempo = tiempo;  //Guarda el tiempo de ejecucion
        resultados -> codigo = 5;   //Guarda el codigo correspondiente a "m"

        resultadosTexto << "Resultado: " << fixed << setprecision(digitos) << resultados -> PI << endl << setprecision(1) <<
        "Tiempo: " << resultados -> tiempo << " minutos a " << resultados -> digitos << " digitos"; //Guarda el mensaje

    }else if(tiempo > 3600){    //horas

        tiempo = tiempo / 3600; //Pasa el tiempo a una unidad mayor y lo almacena

        resultados -> tiempo = tiempo;  //Guarda el tiempo de ejecucion
        resultados -> codigo = 6;   //Guarda el codigo correspondiente a "h"

        resultadosTexto << "Resultado: " << fixed << setprecision(digitos) << resultados -> PI << endl << setprecision(1) <<
        "Tiempo: " << resultados -> tiempo << " horas a " << resultados -> digitos << " digitos";   //Guarda el mensaje

    }

    return resultadosTexto.str().c_str();   //Regresa el mensaje

}

void Calculo::escribir(RESULTADOS* mensaje){    //Almacena los datos


    FILE* ficheroEntrada;   //Archivo

    if(!(ficheroEntrada = fopen("output.rst", "ab"))){  //Abre el archivo

        MessageBox(NULL, "Error al crear archivo", "Error", MB_ICONERROR);  //Mensaje de error

    }

    fwrite(mensaje, sizeof(RESULTADOS), 1, ficheroEntrada); //Guarda los datos en "output.rst"
    fclose(ficheroEntrada); //Cierra el archivo

}

bool Calculo::estaCalculando(){ //Getter de "Calculando"

    return calculando;

}

double Calculo::getPI(){    //Getter de "PI"

    return PI * 4;

}

double Calculo::getTiempo(){    //Getter de "tiempo"

    return tiempo;

}
