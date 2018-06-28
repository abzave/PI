#include "Calculo.h"

using namespace std;

/*Constructor*/
Calculo::Calculo(){
    tiempo = 0;
    porcentaje = 0;
    PI = 0;
}

/*
Entradas: Sumatoria y digitos de tipo entero
Salidas: Imprime en pantalla el resultado del calculo y devuelve el código de la duración
Funcionamiento: Calcula con la formula de Leibniz PI y calcula cuanto se duró en esta operación
*/
int Calculo::calcular(unsigned int sumatoria,unsigned short int digitos){
    int segundos = 1;
    Tiempo temporizador;
    PI = 0;
    system("cls");
    temporizador.iniciar();
    for(int i = 0; i <= sumatoria; i++){
        PI = PI + (pow(-1, i) / (2 * i + 1));
        temporizador.finalizar();
        segundos = mostrarPorcentaje(temporizador.duracion(), i, sumatoria, segundos);
    }
    temporizador.finalizar();
    tiempo = temporizador.duracion();
    system("cls");
    cout << fixed << setprecision(digitos) << endl << PI * 4 << endl;
    return duracion(digitos);
}

/*
Entradas: Sumatoria de tipo entero de 64 bits y digitos de tipo entero
Salidas: Imprime en pantalla el resultado del calculo y devuelve el código de la duración
Funcionamiento: Calcula con la formula de Leibniz PI y calcula cuanto se duró en esta operación
*/
int Calculo::calcular(unsigned long long int sumatoria, unsigned short int digitos){
    int segundos = 1;
    PI = 0;
    Tiempo temporizador;
    system("cls");
    temporizador.iniciar();
    for(long long int i = 0; i <= sumatoria; i++){
        PI = PI + (pow(-1, i) / (2 * i + 1));
        temporizador.finalizar();
        segundos = mostrarPorcentaje(temporizador.duracion(), i, sumatoria, segundos);
    }
    temporizador.finalizar();
    tiempo = temporizador.duracion();
    system("cls");
    cout << fixed << setprecision(digitos) << endl << PI * 4 << endl;
    return duracion(digitos);
}

/*
Entradas: digitos de tipo entero
Salidas: Devuelve un código según el tiempo durado e imprime este tiempo
Funcionamiento: Adapta el tiempo durado a la magnitud más cercana y lo imprime por pantalla
*/
int Calculo::duracion(unsigned short int digitos){
    if(tiempo < 0.000001){  //nanosegundos
        tiempo = tiempo * 1000000000;
        cout << fixed << setprecision(2) << tiempo << " nanosegundos a " << digitos << " digitos" << endl << endl;
        return 0;
    }else if(tiempo < 0.001){   //microsegundos
        tiempo = tiempo * 1000000;
        cout << fixed << setprecision(2) << tiempo << " microsegundos a " << digitos << " digitos" << endl << endl;
        return 1;
    }else if(tiempo < 1){   //milisegundos
        tiempo = tiempo * 1000;
        cout << fixed << setprecision(2) << tiempo << " milisegundos a " << digitos << " digitos" << endl << endl;
        return 2;
    }else if(tiempo < 60){  //segundos
        cout << fixed << setprecision(2) << tiempo << " segundos a " << digitos << " digitos" << endl << endl;
        return 3;
    }else if(tiempo > 60 && tiempo < 3600){ //minutos
        tiempo = tiempo / 60;
        cout << fixed << setprecision(2) << tiempo << " minutos a " << digitos << " digitos" << endl << endl;
        return 4;
    }else if(tiempo > 3600){    //horas
        tiempo = tiempo / 3600;
        cout << fixed << setprecision(2) << tiempo << " horas a " << digitos << " digitos" << endl << endl;
        return 5;
    }else{
        return -1;
    }
}

/*
Entradas: tiempo transcurrido, iteración, total y segundos de tipo entero
Salidas: Imprime en panatalla el porcentaje del calculo con una barra de carga y devuelve segundos
Funcionamiento: Cada segundo Imprime en pantalla en porcentaje con base a iteración y total que se lleva del calculo y devuelve los segundos
*/
int Calculo::mostrarPorcentaje(unsigned int tiempoTranscurrido, unsigned int iteracion, unsigned int total, unsigned int segundos){
    if(tiempoTranscurrido == segundos){
        porcentaje = ((double)iteracion / (double)total) * 100;
        system("cls");
        cout << fixed << setprecision(1) << porcentaje << "%" << endl;
        for(int i = 10; i < porcentaje; i += 10){
            printf("%c", 219);
        }
        segundos++;
    }
    return segundos;
}

/*
Entradas: tiempo transcurrido y segundos de tipo entero y iteración y total de tipo entero de 64 bits
Salidas: Imprime en panatalla el porcentaje del calculo con una barra de carga y devuelve segundos
Funcionamiento: Cada segundo Imprime en pantalla en porcentaje con base a iteración y total que se lleva del calculo y devuelve los segundos
*/
int Calculo::mostrarPorcentaje(unsigned int tiempoTranscurrido, unsigned long long int iteracion, unsigned long long int total, unsigned int segundos){
    if(tiempoTranscurrido == segundos){
        porcentaje = ((double)iteracion / (double)total) * 100;
        system("cls");
        cout << fixed << setprecision(1) << porcentaje << "%" << endl;
        for(int i = 10; i < porcentaje; i += 10){
            printf("%c", 219);
        }
        segundos++;
    }
    return segundos;
}

/*Getters*/
double Calculo::getPI(){
    return PI * 4;
}
double Calculo::getTiempo(){
    return tiempo;
}
