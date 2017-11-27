#include <Windowsx.h>
#include <stdlib.h>
#include <pthread.h>
#include "Calculo.h"
#include "Recursos.h"

using namespace std;

LPCSTR szWindowClass = "PI";	//Nombre de la aplicacion
LPCSTR szTitle = "PI";	//Nombre de la barra de titulo
HWND ventana, calcular, salir, ver, label, comboBox, barraProgreso;	//Elementos

void* calculo(void*); //Funcion que inicia el calculo

void mostrar(HWND, Calculo::RESULTADOS*);    //Lee "output.rst"
void agregarResultado(HWND, Calculo::RESULTADOS*);    //Interpreta el resultado en "output.rst"
void agregarCodigo(HWND, Calculo::RESULTADOS*); //Interpreta el codigo de duración en "output.rst"

BOOL CALLBACK DlgResultadosProc(HWND, UINT, WPARAM, LPARAM);    //Proceso de mensajes de "Ver resultados"

LRESULT CALLBACK WndProc(HWND hWnd, UINT mensaje, WPARAM wParam, LPARAM lParam) {	//Proceso de mensajes

    static HINSTANCE instancia; //Instancia de ventana
    pthread_t hilo; //Hilo para ejecucion en segundo plano
    Calculo calculador; //Instancia de Calculo

	switch (mensaje) {

        case WM_CREATE: //Mensaje de creación de la ventana

            instancia = ((LPCREATESTRUCT)lParam) -> hInstance;  //Almacena la instacia de ventana

		case WM_COMMAND:	//Mensaje de click

			if((HWND)lParam == calcular){	//Boton "Calcular PI"

				int indice = SendDlgItemMessage(hWnd, CB_DIGITOS, CB_GETCURSEL, 0, 0);  //Opcion seleccionada en "cb"

				if(calculador.estaCalculando() == false){   //Verifica que no se esté ejecutando otro calculo

                    if(indice != 5){    //Verifica que la cantidad de digitos no sea 10

                        if(pthread_create(&hilo, NULL, calculo, (void*)indice)){  //Ejecuta el calculo en un hilo a parte para evitar cuelgue

                            MessageBox(hWnd, "Error al generar hilo de ejecucion", szTitle, MB_ICONERROR);  //Mensaje de error
                            PostQuitMessage(3); //Cierre del la aplicacion

                        }

                    }else{

                        if((MessageBox(hWnd, "¿Está seguro que desea calcular 10 digitos?\n¡Esta operaación puede llevar demasiado tiempo!",
                        szTitle, MB_ICONWARNING | MB_OKCANCEL)) == IDOK){ //Advertencia

                            if(pthread_create(&hilo, NULL, calculo, (void*)indice)){  //Ejecuta el calculo en un hilo a parte para evitar cuelgue

                                MessageBox(hWnd, "Error al generar hilo de ejecucion", szTitle, MB_ICONERROR);  //Mensaje de error
                                PostQuitMessage(3); //Cierre del la aplicacion

                            }

                        }

                    }

                }else{

                    MessageBox(hWnd, "Calculo en ejecución por favor espere a que termine", szTitle, MB_ICONERROR); //Mensaje de error

                }

			}
			if((HWND)lParam == ver){    //Boton "Ver resultados"

                DialogBox(instancia, "DlgResultados", ventana, DlgResultadosProc);  //Despliega el cuadro de dialogo "DlgResultados"

			}
			if((HWND)lParam == salir){	//Boton "Salir"

				PostQuitMessage(0); //Cierre del la aplicacion

			}

			break;

            case WM_SIZE:   //Mensaje de cambio de dimensiones de la ventana

                RECT rect;  //Almacena coordenadas del control
                int ancho;  //Ancho del control
                int largo;  //Largo del control

                GetWindowRect(GetDlgItem(hWnd, ID_SALIR), &rect);  //Obtiene las coordenadas absolutas despues de la redimension
                ancho = rect.right - rect.left; //Calcula el ancho
                largo = rect.bottom - rect.top; //Calcula el largo

                GetClientRect(hWnd, &rect); //Obtiene las coordenadas relativas despues de la redimension
                MoveWindow(GetDlgItem(hWnd, ID_SALIR), rect.right - ancho - 8, rect.bottom - largo - 8, ancho, largo, TRUE);   //Mueve el control

            break;

		case WM_DESTROY:	//Cierre de una ventana

			PostQuitMessage(0);	//Cierre del la aplicacion
			break;

        case WM_CLOSE:  //Cierre de la aplicacion

            DestroyWindow(hWnd);    //Destuye la ventana
            break;

		default:

			return DefWindowProc(hWnd, mensaje, wParam, lParam);	//Procesamiento por defecto

	}

	return 0;

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {	//Main

	const char* digitos[] = {"1", "2", "4", "6", "8", "10"};    //Elementos del "COMBOBOX"
    int items = (sizeof(digitos) / (sizeof(char*)));    //Medida de "dig"

	WNDCLASSEX wcex;	//Clase de ventana
	wcex.cbSize = sizeof(WNDCLASSEX);	//Tamño de la estructura
	wcex.style = CS_HREDRAW | CS_VREDRAW;	//Estilo
	wcex.lpfnWndProc = WndProc;	//Proceso de mensaje
	wcex.cbClsExtra = 0;	//Bytes extra para la clase de ventana
	wcex.cbWndExtra = 0;	//Bytes extra para las ventanas
	wcex.hInstance = hInstance;	//Instancia
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);	//Icono
	wcex.hCursor = LoadCursor(hInstance, IDC_ARROW);	//Cursor
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);	//Color de fondo
	wcex.lpszMenuName = NULL;	//Nombre del menu
	wcex.lpszClassName = szWindowClass;	//Nombre de la clase
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);	//Icono del sistema

	if (!RegisterClassEx(&wcex)) {	//Registro de la clase

		MessageBox(NULL, "Fallo la llamada a RegisterClassEx!", szTitle, MB_ICONERROR);	//Mensaje de error
		return 1;

	}

	ventana = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, hInstance, NULL); //Crea la ventana
	calcular = CreateWindow("BUTTON", "Calcular PI", WS_CHILD | WS_VISIBLE, 10, 10, 100, 20, ventana, NULL, hInstance, NULL);   //Crea el boton "Calcular PI"
	ver = CreateWindow("BUTTON", "Ver resultados", WS_CHILD | WS_VISIBLE, 120, 10, 120, 20, ventana, NULL, hInstance, NULL);    //Crea el boton "Ver resultados"
	salir = CreateWindow("BUTTON", "Salir", WS_CHILD | WS_VISIBLE, 520, 410, 90, 20, ventana, (HMENU)ID_SALIR, hInstance, NULL); //Crea el boton "Salir"
	label = CreateWindow("STATIC", "Digitos", WS_CHILD | WS_VISIBLE, 60, 45, 45, 30, ventana, NULL, hInstance, NULL);   //Crea el texto "Digitos"
	comboBox = CreateWindow("COMBOBOX", "", CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE, 10, 40, 50, 150, ventana, (HMENU)CB_DIGITOS, hInstance, NULL);  //Crea el menú desplegable
	barraProgreso = CreateWindow(PROGRESS_CLASS, "", PBS_SMOOTH | WS_CHILD | WS_VISIBLE, 250, 10, 100, 20, ventana, (HMENU)PB_PROGRESO, hInstance, NULL);   //Crea la barra de progreso

	for(int i = 0; i < items; i++){

        SendDlgItemMessage(ventana, CB_DIGITOS, CB_ADDSTRING, 0, (LPARAM)digitos[i]);   //Añade los elementos de "dig" al menu desplegable

    }
    SendDlgItemMessage(ventana, CB_DIGITOS, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);    //Posiciona el "COMBOBOX" en el primer elemento por defecto

	if (!ventana) {	//Revisa que la ventana se haya creado

		MessageBox(NULL, "Fallo la llamada a Create Window", szTitle, MB_ICONERROR);	//Mensaje de error
		return 2;

	}

	ShowWindow(ventana, nCmdShow);	//Muestra la ventana
	UpdateWindow(ventana);	//Actualiza la ventana

	MSG mensaje;	//Guarda mensajes

	while (GetMessage(&mensaje, NULL, 0, 0)) {	//Obtiene los mensajes

        /*Envia el mensaje al proceso de mensajes*/

		TranslateMessage(&mensaje);
		DispatchMessage(&mensaje);

	}

	return (int)mensaje.wParam;	//Estatus de salida

}

void* calculo(void* indice){    //Funcion que inicia el calculo

    Calculo calculador;  //Instancia de Calculo

    switch((int)indice){ //Comprueba opcion del "COMBOBOX"

    /*Los valores del parametro "Sumatoria" son los minimos para obtener un resultado correcto*/

        case 0: //1 digito

            calculador.calcular(19, 1, barraProgreso);    //Calcula 1 digito de PI
            break;

        case 1: //2 digitos

            calculador.calcular(293, 2, barraProgreso);   //Calcula 2 digitos de PI
            break;

        case 2: //4 digitos

            calculador.calcular(17375, 4, barraProgreso); //Calcula 4 digitos de PI
            break;

        case 3: //6 digitos

            calculador.calcular(20000004, 6, barraProgreso);  //Calcula 6 digitos de PI
            break;

        case 4: //8 digitos

            calculador.calcular(117000001, 8, barraProgreso); //Calcula 8 digitos de PI
            break;

        case 5: //10 digitos

            calculador.calcular(16343000102LL, 10, barraProgreso);    //Calcula 10 digitos de PI
            break;

    }

}

void mostrar(HWND ventana, Calculo::RESULTADOS* resultados){    //Lee "output.rst"

    char buffer[20];    //buffer para el texto

    SetDlgItemInt(ventana, EDT_DIGITOS, resultados -> digitos, TRUE);   //Muestra la cantidad de digitos

    memset(buffer, '\0', 20);   //Limpia el buffer
    sprintf(buffer, "%0.1f", resultados -> tiempo); //Guarda el tiempo en el buffer
    SetDlgItemText(ventana, EDT_DURACION, buffer);  //Muestra el tiempo de ejecucion

    agregarCodigo(ventana, resultados); //Muesta la unidad de tiempo
    agregarResultado(ventana, resultados);    //Muestra el resultado del calculo

}

void agregarCodigo(HWND ventana, Calculo::RESULTADOS* resultados){  //Interpreta el codigo de duración en "output.rst"

    switch(resultados -> codigo){   //Verifica el codigo

        case 1: //nanosegundo

            SetDlgItemText(ventana, EDT_TIEMPO, "ns");  //Muesta la unidad de tiempo

            break;

        case 2: //microsegundos

            SetDlgItemText(ventana, EDT_TIEMPO, "us");  //Muesta la unidad de tiempo

            break;

        case 3: //milisegundos

            SetDlgItemText(ventana, EDT_TIEMPO, "ms");  //Muesta la unidad de tiempo

            break;

        case 4: //segundos

            SetDlgItemText(ventana, EDT_TIEMPO, "s");   //Muesta la unidad de tiempo

            break;

        case 5: //minutos

            SetDlgItemText(ventana, EDT_TIEMPO, "m");   //Muesta la unidad de tiempo

            break;

        case 6: //horas

            SetDlgItemText(ventana, EDT_TIEMPO, "h");   //Muesta la unidad de tiempo

            break;

    }

}

void agregarResultado(HWND ventana, Calculo::RESULTADOS* resultados){   //Interpreta el resultado en "output.rst"

    char buffer[20];    //buffer para el texto

    switch(resultados -> digitos){  //verifica la cantidad de digitos

        case 1:

            memset(buffer, '\0', 20);   //Limpia el buffer
            sprintf(buffer, "%0.1f", resultados -> PI); //Guarda el resultado con 1 decimal
            SetDlgItemText(ventana, EDT_RESULTADO, buffer); //Muestra el resultado

            break;

        case 2:

            memset(buffer, '\0', 20);   //Limpia el buffer
            sprintf(buffer, "%0.2f", resultados -> PI); //Guarda el resultado con 2 decimales
            SetDlgItemText(ventana, EDT_RESULTADO, buffer); //Muestra el resultado

            break;

        case 4:

            memset(buffer, '\0', 20);   //Limpia el buffer
            sprintf(buffer, "%0.4f", resultados -> PI); //Guarda el resultado con 4 decimales
            SetDlgItemText(ventana, EDT_RESULTADO, buffer); //Muestra el resultado

            break;

        case 6:

            memset(buffer, '\0', 20);   //Limpia el buffer
            sprintf(buffer, "%0.6f", resultados -> PI); //Guarda el resultado con 6 decimales
            SetDlgItemText(ventana, EDT_RESULTADO, buffer); //Muestra el resultado

            break;

        case 8:

            memset(buffer, '\0', 20);   //Limpia el buffer
            sprintf(buffer, "%0.8f", resultados -> PI); //Guarda el resultado con 8 decimales
            SetDlgItemText(ventana, EDT_RESULTADO, buffer); //Muestra el resultado

            break;

        case 10:

            memset(buffer, '\0', 20);   //Limpia el buffer
            sprintf(buffer, "%0.10f", resultados -> PI);    //Guarda el resultado con 10 decimales
            SetDlgItemText(ventana, EDT_RESULTADO, buffer); //Muestra el resultado

            break;

    }

}

BOOL CALLBACK DlgResultadosProc(HWND ventana, UINT mensaje, WPARAM wParam, LPARAM lParam){  //Proceso de mensajes de "Ver resultados"

    static FILE* ficheroSalida; //Fichero
    static int posicion = 0;    //Posicion de navegacion
    static int elementos = 0;   //Elementos en "output.rst"
    Calculo::RESULTADOS resultados; //Almacena los resultados del calculo

    switch(mensaje){

        case WM_INITDIALOG: //Mensaje de creacion del cuadro de dialogo

            if(!(ficheroSalida = fopen("output.rst", "rb"))){   //Abre el archivo

                MessageBox(ventana, "Error al abrir el archivo output.txt", szTitle, MB_ICONERROR); //Mensaje de error
                EndDialog(ventana, TRUE);   //Cierra el cuadro de dialogo

            }

            fseek(ficheroSalida, 0, SEEK_END);  //Posiciona el cursor al final del archivo
            elementos = (int)(ftell(ficheroSalida)/sizeof(Calculo::RESULTADOS));    //Calcula la cantidad de elementos en "output.rst"

            rewind(ficheroSalida);  //Vuelve al inicio del archivo
            fread(&resultados, sizeof(Calculo::RESULTADOS), 1, ficheroSalida);  //Lee el primer resultado
            mostrar(ventana, &resultados);  //Muestra la informacion

            posicion = 0;   //Resetea "posicion"
            EnableWindow(GetDlgItem(ventana, ID_ANTERIOR), FALSE);  //Inhavilita el boton "Anterior"
            if(elementos == 1){ //Verifica que halla más de un elemento

                EnableWindow(GetDlgItem(ventana, ID_SIGUIENTE), FALSE); //Inhavilita el boton "Siguiente"

            }

            break;


        case WM_COMMAND:    //Mensaje de click

            switch(LOWORD(wParam)){

                case ID_ANTERIOR:   //Boton "Anterior"

                    posicion--; //Disminuye una posicion
                    if(posicion < 1){   //Verifica que se esté en la posicion 0

                        EnableWindow(GetDlgItem(ventana, ID_ANTERIOR), FALSE);  //Inhavilita el boton "Anterior"

                    }
                    EnableWindow(GetDlgItem(ventana, ID_SIGUIENTE), TRUE);  //Habilita el boton "Siguiente"

                    rewind(ficheroSalida);  //Vuelve al inicio del archivo
                    fseek(ficheroSalida, posicion * sizeof(Calculo::RESULTADOS), SEEK_SET); //Mueve el cursor al resultado correspondiente a la posicion
                    fread(&resultados, sizeof(Calculo::RESULTADOS), 1, ficheroSalida);  //Lee el resultado que se encuentre en esa posicion
                    mostrar(ventana, &resultados);  //Muestra la informacion

                    break;

                case ID_SIGUIENTE:  //boton "Siguiente"

                    posicion++; //Aumenta una posicion
                    if(posicion >= (elementos - 1)){    //Veficia que este en el ultimo elemento

                        EnableWindow(GetDlgItem(ventana, ID_SIGUIENTE), FALSE); //Inhabilita el boton "Siguiente"

                    }
                    EnableWindow(GetDlgItem(ventana, ID_ANTERIOR), TRUE);   //Habilita el boton "Anterior"

                    rewind(ficheroSalida);  //Vuelve al inicio del archivo
                    fseek(ficheroSalida, posicion * sizeof(Calculo::RESULTADOS), SEEK_SET); //Mueve el cursor al resultado correspondiente a la posicion
                    fread(&resultados, sizeof(Calculo::RESULTADOS), 1, ficheroSalida);  //Lee el resultado que se encuentre en esa posicion
                    mostrar(ventana, &resultados);  //Muestra la informacion

                    break;

                case IDOK:  //Boton "Aceptar"

                    EndDialog(ventana, TRUE);   //Cierra el cuadro de dialogo
                    break;

            }

            return TRUE;

        case WM_CLOSE:  //Mensaje de cierre

            fclose(ficheroSalida);  //Cierra el archivo
            EndDialog(ventana, TRUE);   //Cierra el cuadro de dialogo
            return TRUE;

    }

    return FALSE;

}

