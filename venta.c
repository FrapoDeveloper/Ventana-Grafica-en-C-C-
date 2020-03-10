#include <windows.h>

LRESULT CALLBACK ProcediementoVentana(HWND hwnd,UINT msg, WPARAM wParam,LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstanciaActual,HINSTANCE hInstanciaPrevia,LPSTR lpCmdLinea,int nCmdShow){
    HWND ventana; //manejador de ventana
    MSG mensaje; //intermediario para comunicar los mensajes de la aplicacion    WNDCLASSEX clase;
    WNDCLASSEX clase; //estructura que contienen un conjunto de elementos que caracterizan a una ventana
    clase.cbSize = sizeof(WNDCLASSEX); //tamaño de la clase es igual al tamaño de la estructura    clase.cbClsExtra = 0;
    clase.cbClsExtra = 0; //El número de bytes adicionales para asignar (El sistema inicializa los bytes a cero.)
    clase.style = CS_HREDRAW | CS_VREDRAW;  //se puede dibujar horizontalmente y verticalmente
    clase.lpfnWndProc = ProcediementoVentana;
    /* lpfnWndProc:
    Es la responsable de todo lo relativo al aspecto y al comportamiento de una ventana.
    Puntero a una función de este tipo, esa función es la que se encargará de procesar
    todos los mensajes para esa clase de ventana. Cuando registremos nuestra clase de
    ventana, tendremos que asignar a ese miembro el puntero a nuestro procedimiento de ventana.*/
    clase.hInstance = hInstanciaActual;
    clase.hIcon = LoadIcon(NULL,0);//Identificador de icono
    clase.hIconSm =LoadIcon(NULL,IDI_INFORMATION);//Elegimos que icono queremos
    clase.hCursor = LoadCursor(NULL,IDC_ARROW);//Identificador de cursor, elegimos la forma en que se mostrará
    clase.lpszClassName = "IdentificadorVentana"; //este es el identificador para pasarlo a CreateWindowsEx();
    clase.hbrBackground =CreateSolidBrush( RGB(21,232,189)); //color de la ventana
    if(!RegisterClassEx(&clase)){ //si no esta registrada la clase
        MessageBox( NULL,"No se pudo ejecutar la aplicacion","Error",MB_ICONERROR);
        return EXIT_FAILURE;
    }
    //WS_OVERLAPPED|WS_MINIMIZEBOX|WS_SYSMENU (para que no se maximice)
    ventana = CreateWindowEx(0,"IdentificadorVentana","Hola mundo",WS_OVERLAPPEDWINDOW |WS_SYSMENU,
                             400,80,560,630,HWND_DESKTOP,NULL,hInstanciaActual,NULL);

    ShowWindow(ventana,nCmdShow); //mostramos la ventana
    UpdateWindow(ventana);//actualizamos la ventana en caso hagamos algunos eventos
    //creamos el bucle para saber si nuestro mensaje esta interactuando con el usuario, si será cero significa que acabo el programa
    while(GetMessage(&mensaje,NULL,0,0)>0){
            TranslateMessage(&mensaje);
            DispatchMessage(&mensaje);
    }

}
/*LRESULT : utiliza para representar el valor
 de retorno de los procedimientos de ventana.
 Suele ser un LARGO (de ahí la L ).
 Parámetros del procedimiento de ventana :
        hwnd es el manipulador de la ventana a la que está destinado el mensaje.
        msg es el código del mensaje.
        wParam es el parámetro de tipo palabra asociado al mensaje.
        lParam es el parámetro de tipo doble palabra asociado al mensaje.
 */
LRESULT CALLBACK ProcediementoVentana(HWND hwnd,UINT msg, WPARAM wParam,LPARAM lParam){
 static HINSTANCE Instancia; //no se destruye por ser estatica

    switch(msg){
                case WM_CREATE:{
                          Instancia =((LPCREATESTRUCT)lParam)->hInstance; //cassting para convertir en una structura que lleva almacenada la info de la ventana.
                          break;
                }
                case WM_DESTROY:{
                PostQuitMessage(0); //este cero pasará al bucle while para que acabe el programa
                break;
                }
                default:{
                return DefWindowProc(hwnd, msg,wParam,lParam);
                }

    }
    return 0;
}
