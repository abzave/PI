#include <Windowsx.h>
#include <stdlib.h>
#include <pthread.h>
#include "Calculo.h"
#define CB_DIGITOS  100

using namespace std;

LPCSTR szWindowClass = "PI";	//Nombre de la aplicacion
LPCSTR szTitle = "PI";	//Nombre de la barra de titulo
HWND ventana, calc, sal, label, cb;	//Elementos

void* tarea(void*); //Funcion que inicia el calculo

LRESULT CALLBACK WndProc(HWND hWnd, UINT msj, WPARAM wParam, LPARAM lParam) {	//Proceso de mensajes

    pthread_t hilo; //Hilo para ejecucion en segundo plano

	switch (msj) {

		case WM_COMMAND:	//Click

			if((HWND)lParam == calc){	//Boton "Calcular PI"

				int indice = SendDlgItemMessage(hWnd, CB_DIGITOS, CB_GETCURSEL, 0, 0);  //Opcion seleccionada en "cb"

				if(pthread_create(&hilo, NULL, tarea, (void*)indice)){  //Ejecuta el calculo en un hilo a parte para evitar cuelgue

                    MessageBox(hWnd, "Error al generar hilo de ejecucion", szTitle, MB_ICONERROR);  //Mensaje de error
                    PostQuitMessage(3); //Cierre del la aplicacion

				}

			}
			if((HWND)lParam == sal){	//Boton "Salir"

				PostQuitMessage(0); //Cierre del la aplicacion

			}

			break;

		case WM_DESTROY:	//Cierre de una ventana

			PostQuitMessage(0);	//Cierre del la aplicacion
			break;

        case WM_CLOSE:  //Cierre de la aplicacion

            DestroyWindow(hWnd);    //Destuye la ventana
            break;

		default:

			return DefWindowProc(hWnd, msj, wParam, lParam);	//Procesamiento por defecto
			break;

	}

	return 0;

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {	//Main

	const char* dig[] = {"1", "2", "4", "6", "8", "10"};    //Elementos del "COMBOBOX"
    int items = (sizeof(dig) / (sizeof(char*)));    //Medida de "dig"

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

		MessageBox(NULL, "Fallo la llamada a RegisterClassEx!", "PI", MB_ICONERROR);	//Mensaje de error
		return 1;

	}

	ventana = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, hInstance, NULL); //Crea la ventana
	calc = CreateWindow("BUTTON", "Calcular PI", WS_CHILD | WS_VISIBLE, 10, 10, 100, 20, ventana, NULL, hInstance, NULL);   //Crea el boton "Calcular PI"
	sal = CreateWindow("BUTTON", "Salir", WS_CHILD | WS_VISIBLE, 520, 410, 90, 20, ventana, NULL, hInstance, NULL); //Crea el boton "Salir"
	label = CreateWindow("STATIC", "Digitos", WS_CHILD | WS_VISIBLE, 60, 45, 45, 30, ventana, NULL, hInstance, NULL);   //Crea el texto "Digitos"
	cb = CreateWindow("COMBOBOX", "", CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE, 10, 40, 50, 150, ventana, (HMENU)CB_DIGITOS, hInstance, NULL);  //Crea el menú desplegable

	for(int i = 0; i < items; i++){

        SendDlgItemMessage(ventana, CB_DIGITOS, CB_ADDSTRING, 0, (LPARAM)dig[i]);   //Añade los elementos de "dig" al menu desplegable

    }
    SendDlgItemMessage(ventana, CB_DIGITOS, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);    //Posiciona el "COMBOBOX" en el primer elemento por defecto

	if (!ventana) {	//Revisa que la ventana se haya creado

		MessageBox(NULL, "Fallo la llamada a Create Window", szTitle, MB_ICONERROR);	//Mensaje de error
		return 2;

	}

	ShowWindow(ventana, nCmdShow);	//Muestra la ventana
	UpdateWindow(ventana);	//Actualiza la ventana

	MSG msj;	//Guarda mensajes

	while (GetMessage(&msj, NULL, 0, 0)) {	//Obtiene los mensajes

		TranslateMessage(&msj);
		DispatchMessage(&msj);	//Envia el mensaje al proceso de mensajes

	}

	return (int)msj.wParam;	//Estatus de salida

}

void* tarea(void* indice){

    Calculo calcu;  //Instancia de Calculo

    switch((int)indice){ //Comprueba opcion del "COMBOBOX"

    /*Los valores del parametro "Sumatoria" son los minimos para obtener un resultado correcto*/

        case 0: //1 digito

            calcu.calcular(19, 1);    //Calcula 1 digito de PI
            break;

        case 1: //2 digitos

            calcu.calcular(293, 2);   //Calcula 2 digitos de PI
            break;

        case 2: //4 digitos

            calcu.calcular(17375, 4); //Calcula 4 digitos de PI
            break;

        case 3: //6 digitos

            calcu.calcular(20000004, 6);  //Calcula 6 digitos de PI
            break;

        case 4: //8 digitos

            calcu.calcular(117000001, 8); //Calcula 8 digitos de PI
            break;

        case 5: //10 digitos

            calcu.calcular(16343000102LL, 10);    //Calcula 10 digitos de PI
            break;

        }

}

