#include "Calculo.h"
#include "Tiempo.h"

using namespace std;

Calculo::Calculo(){ //Constructor

    tiempo = 0; //Inicializa "tiempo"
    porcentaje = 0; //Inicializa "porcentaje"
    PI = 0; //Inicializa "PI"

}
int Calculo::calcular(long long int sumatoria, int digitos){    //Calcula PI en mononucleo

    int segundos = 1;  //Contador de segundos transcurridos
    PI = 0; //Cambia el valor de PI
    Tiempo temporizador;

    system("cls");

    temporizador.iniciar(); //Marca el inicio de la ejecucion

    for(long long int i = 0; i <= sumatoria; i++){

        PI = PI + (pow(-1, i) / (2 * i + 1));   //Formula de Leibniz

        temporizador.finalizar();   //Marcador para calcular el tiempo transcurrido
        if(temporizador.duracion() == 2 * segundos){    //Comprueba que haya pasado medio minuto

            porcentaje = ((double)i / (double)sumatoria) * 100; //Calcula el porcentaje de ejecucion

            system("cls");  //Limpia la pantalla
            cout << fixed << setprecision(1) << porcentaje << "%" << endl;  //Imprime el porcentaje

            for(int i = 10; i < porcentaje; i += 10){   //Aumenta la barra cada 10%

                printf("%c", 219);  //Imprime el caracter ascii 219 como barra de progreso

            }

            cout << endl << "Esto puede llegar a durar un rato" << endl;    //Aviso

            segundos++;

        }

    }

    temporizador.finalizar();  //Marca el final de la ejecucion
    tiempo = temporizador.duracion();    //Calcula el total del tiempo de ejecucion

    system("cls");  //Limpia la pantalla

    cout << fixed << setprecision(digitos) << endl << PI * 4 << endl;   //Imprime el resultado del calculo

    return duracion(digitos);   //Regresa el codigo de duracion

}
int Calculo::duracion(int digitos){

    if(tiempo < 0.000001){  //nanosegundos

        tiempo = tiempo * 1000000000;   //Pasa el tiempo a una unidad menor y lo almacena

        cout << fixed << setprecision(2) << tiempo << " nanosegundos a " << digitos << " digitos" << endl << endl;  //Imprime el tiempo
        return 0;   //Codigo para especificar unidad de tiempo

    }else if(tiempo < 0.001){   //microsegundos

        tiempo = tiempo * 1000000;  //Pasa el tiempo a una unidad menor y lo almacena

        cout << fixed << setprecision(2) << tiempo << " microsegundos a " << digitos << " digitos" << endl << endl; //Imprime el tiempo
        return 1;   //Codigo para especificar unidad de tiempo

    }else if(tiempo < 1){   //milisegundos

        tiempo = tiempo * 1000; //Pasa el tiempo a una unidad menor y lo almacena

        cout << fixed << setprecision(2) << tiempo << " milisegundos a " << digitos << " digitos" << endl << endl;  //Imprime el tiempo
        return 2;   //Codigo para especificar unidad de tiempo

    }else if(tiempo < 60){  //segundos

        cout << fixed << setprecision(2) << tiempo << " segundos a " << digitos << " digitos" << endl << endl;  //Imprime el tiempo
        return 3;   //Codigo para especificar unidad de tiempo

    }else if(tiempo > 60 && tiempo < 3600){ //minutos

        tiempo = tiempo / 60;   //Pasa el tiempo a una unidad mayor y lo almacena

        cout << fixed << setprecision(2) << tiempo << " minutos a " << digitos << " digitos" << endl << endl;   //Imprime el tiempo
        return 4;   //Codigo para especificar unidad de tiempo

    }else if(tiempo > 3600){    //horas

        tiempo = tiempo / 3600; //Pasa el tiempo a una unidad mayor y lo almacena

        cout << fixed << setprecision(2) << tiempo << " horas a " << digitos << " digitos" << endl << endl; //Imprime el tiempo
        return 5;   //Codigo para especificar unidad de tiempo

    }

}
double Calculo::getPI(){    //Getter de "PI"

    return PI * 4;

}
double Calculo::getTiempo(){    //Getter de "tiempo"

    return tiempo;

}
