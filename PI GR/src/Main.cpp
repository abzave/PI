#include <Windowsx.h>
#include <stdlib.h>
#include <pthread.h>
#include "Calculo.h"
#include "Recursos.h"

using namespace std;

LPCSTR szWindowClass = "Clase";	//Nombre de la aplicacion
LPCSTR szTitle = "PI";	//Nombre de la barra de titulo
HWND ventana, calc, sal, ver, label, label2, cb;	//Elementos

void* tarea(void*); //Funcion que inicia el calculo
void mostrar(HWND, Calculo::RESULTADOS*);    //Lee "output.txt"
BOOL CALLBACK DlgResultadosProc(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK WndProc(HWND hWnd, UINT msj, WPARAM wParam, LPARAM lParam) {	//Proceso de mensajes

    static HINSTANCE instancia;
    pthread_t hilo; //Hilo para ejecucion en segundo plano

	switch (msj) {

        case WM_CREATE:

            instancia = ((LPCREATESTRUCT)lParam) -> hInstance;

		case WM_COMMAND:	//Click

			if((HWND)lParam == calc){	//Boton "Calcular PI"

				int indice = SendDlgItemMessage(hWnd, CB_DIGITOS, CB_GETCURSEL, 0, 0);  //Opcion seleccionada en "cb"

				if(pthread_create(&hilo, NULL, tarea, (void*)indice)){  //Ejecuta el calculo en un hilo a parte para evitar cuelgue

                    MessageBox(hWnd, "Error al generar hilo de ejecucion", szTitle, MB_ICONERROR);  //Mensaje de error
                    PostQuitMessage(3); //Cierre del la aplicacion

				}

			}
			if((HWND)lParam == ver){

                DialogBox(instancia, "DlgResultados", ventana, DlgResultadosProc);

			}
			if((HWND)lParam == sal){	//Boton "Salir"

				PostQuitMessage(0); //Cierre del la aplicacion

			}

			break;

            case WM_SIZE:   //Cambio de dimensiones de la ventana

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
	ver = CreateWindow("BUTTON", "Ver resultados", WS_CHILD | WS_VISIBLE, 120, 10, 120, 20, ventana, NULL, hInstance, NULL);
	sal = CreateWindow("BUTTON", "Salir", WS_CHILD | WS_VISIBLE, 520, 410, 90, 20, ventana, (HMENU)ID_SALIR, hInstance, NULL); //Crea el boton "Salir"
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
void mostrar(HWND ventana, Calculo::RESULTADOS* r){

    char buffer[20];

    SetDlgItemInt(ventana, EDT_DIGITOS, r -> digitos, TRUE);

    memset(buffer, '\0', 20);
    sprintf(buffer, "%0.1f", r -> tiempo);
    SetDlgItemText(ventana, EDT_DURACION, buffer);

    switch(r -> digitos){

        case 1:

            memset(buffer, '\0', 20);
            sprintf(buffer, "%0.1f", r -> PI);
            SetDlgItemText(ventana, EDT_RESULTADO, buffer);

            break;

        case 2:

            memset(buffer, '\0', 20);
            sprintf(buffer, "%0.2f", r -> PI);
            SetDlgItemText(ventana, EDT_RESULTADO, buffer);

            break;

        case 4:

            memset(buffer, '\0', 20);
            sprintf(buffer, "%0.4f", r -> PI);
            SetDlgItemText(ventana, EDT_RESULTADO, buffer);

            break;

        case 6:

            memset(buffer, '\0', 20);
            sprintf(buffer, "%0.6f", r -> PI);
            SetDlgItemText(ventana, EDT_RESULTADO, buffer);

            break;

        case 8:

            memset(buffer, '\0', 20);
            sprintf(buffer, "%0.8f", r -> PI);
            SetDlgItemText(ventana, EDT_RESULTADO, buffer);

            break;

        case 10:

            memset(buffer, '\0', 20);
            sprintf(buffer, "%0.10f", r -> PI);
            SetDlgItemText(ventana, EDT_RESULTADO, buffer);

            break;

    }

}
BOOL CALLBACK DlgResultadosProc(HWND ventana, UINT msj, WPARAM wParam, LPARAM lParam){

    static FILE* ficheroSalida;
    static int pos = 0;
    static int resultados = 0;
    Calculo::RESULTADOS r;

    switch(msj){

        case WM_INITDIALOG:

            if(!(ficheroSalida = fopen("output.rst", "rb"))){

                MessageBox(ventana, "Error al abrir el archivo output.txt", "Error", MB_ICONERROR);
                EndDialog(ventana, TRUE);

            }

            fseek(ficheroSalida, 0, SEEK_END);
            resultados = (int)(ftell(ficheroSalida)/sizeof(Calculo::RESULTADOS));

            rewind(ficheroSalida);
            fread(&r, sizeof(Calculo::RESULTADOS), 1, ficheroSalida);
            mostrar(ventana, &r);

            pos = 0;
            EnableWindow(GetDlgItem(ventana, ID_ANTERIOR), FALSE);
            if(resultados == 1){

                EnableWindow(GetDlgItem(ventana, ID_SIGUIENTE), FALSE);

            }

            break;


        case WM_COMMAND:

            switch(LOWORD(wParam)){

                case ID_ANTERIOR:

                    pos--;
                    if(pos < 1){

                        EnableWindow(GetDlgItem(ventana, ID_ANTERIOR), FALSE);

                    }
                    EnableWindow(GetDlgItem(ventana, ID_SIGUIENTE), TRUE);

                    rewind(ficheroSalida);
                    fseek(ficheroSalida, pos * sizeof(Calculo::RESULTADOS), SEEK_SET);
                    fread(&r, sizeof(Calculo::RESULTADOS), 1, ficheroSalida);
                    mostrar(ventana, &r);

                    break;

                case ID_SIGUIENTE:

                    pos++;
                    if(pos >= (resultados - 1)){

                        EnableWindow(GetDlgItem(ventana, ID_SIGUIENTE), FALSE);

                    }
                    EnableWindow(GetDlgItem(ventana, ID_ANTERIOR), TRUE);

                    rewind(ficheroSalida);
                    fseek(ficheroSalida, pos * sizeof(Calculo::RESULTADOS), SEEK_SET);
                    fread(&r, sizeof(Calculo::RESULTADOS), 1, ficheroSalida);
                    mostrar(ventana, &r);

                    break;

                case IDOK:

                    EndDialog(ventana, TRUE);
                    break;

            }

            return TRUE;

        case WM_CLOSE:

            fclose(ficheroSalida);
            EndDialog(ventana, TRUE);
            return TRUE;

    }

    return FALSE;

}

