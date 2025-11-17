#include <iostream>
#include <cstdlib>  
#include <ctime>   

using namespace std;

struct Nodo {
    int dato;
    Nodo* siguiente;
};
void insertarInicio(Nodo*& cabeza, Nodo*& cola, int valor);
void insertarFinal(Nodo*& cabeza, Nodo*& cola, int valor);
void mostrarLista(Nodo* cabeza);
void opcion1(Nodo*& cabeza, Nodo*& cola);
void opcion2(Nodo*& cabeza, Nodo*& cola);
void opcion3(Nodo* cabeza);
void opcion4(Nodo*& cabeza, Nodo*& cola);
void opcion5(Nodo* cabeza);
int longitudLista(Nodo* cabeza);
int main() {
    srand(time(0));  
    Nodo* cabeza = NULL;
    Nodo* cola = NULL;
    int opcion;
    do {
    	cout << "LABORATORIO 3\n";
        cout << "\n--- MENU ---\n";
        cout << "1. Crear dos nodos aleatorios y añadir a la lista\n";
        cout << "2. Insertar nodo con el valor promedio en la posicion media\n";
        cout << "3. Mostrar nodo positivo mayor y nodo negativo menor\n";
        cout << "4. Buscar y eliminar un nodo de la lista\n";
        cout << "5. Mostrar los elementos de la lista\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                opcion1(cabeza, cola);
                break;
            case 2:
                opcion2(cabeza, cola);
                break;
            case 3:
                opcion3(cabeza);
                break;
            case 4:
                opcion4(cabeza, cola);
                break;
            case 5:
                opcion5(cabeza);
                break;
            case 6:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opción no válida. Por favor, intente de nuevo." << endl;
        }
    } while (opcion != 6);
    return 0;
}

void insertarInicio(Nodo*& cabeza, Nodo*& cola, int valor) {
    Nodo* nuevo = new Nodo();
    nuevo->dato = valor;
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
    if (cola == NULL) { 
        cola = nuevo;
    }
}

void insertarFinal(Nodo*& cabeza, Nodo*& cola, int valor) {
    Nodo* nuevo = new Nodo();
    nuevo->dato = valor;
    nuevo->siguiente = NULL;
    if (cabeza == NULL) {
        cabeza = cola = nuevo;
    } else {
        cola->siguiente = nuevo;
        cola = nuevo;
    }
}

void mostrarLista(Nodo* cabeza) {
    Nodo* temp = cabeza;
    while (temp != NULL) {
        cout << temp->dato << " -> ";
        temp = temp->siguiente;
    }
    cout << "NULL" << endl;
}

void opcion1(Nodo*& cabeza, Nodo*& cola) {
    int valor1, valor2;
    do {
        valor1 = (rand() % 101) - 50; 
    } while (valor1 == 0);
    do {
        valor2 = (rand() % 101) - 50;  
    } while (valor2 == 0);
    if (valor1 > 0) {
        insertarInicio(cabeza, cola, valor1);
    } else {
        insertarFinal(cabeza, cola, valor1);
    }
    if (valor2 > 0) {
        insertarInicio(cabeza, cola, valor2);
    } else {
        insertarFinal(cabeza, cola, valor2);
    }
    mostrarLista(cabeza);
}

void opcion2(Nodo*& cabeza, Nodo*& cola) {
    int longitud = longitudLista(cabeza);
    if (longitud == 0) {
        cout << "La lista está vacía." << endl;
        return;
    }

    int suma = 0;
    Nodo* temp = cabeza;
    while (temp != NULL) {
        suma += temp->dato;
        temp = temp->siguiente;
    }
    int promedio = suma / longitud;
    int posicionMedia = longitud / 2;
    Nodo* nuevo = new Nodo();
    nuevo->dato = promedio;

    if (posicionMedia == 0) {
        insertarInicio(cabeza, cola, promedio);
    } else {
        Nodo* actual = cabeza;
        for (int i = 0; i < posicionMedia - 1; i++) {
            actual = actual->siguiente;
        }
        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;
    }
    mostrarLista(cabeza);
}

void opcion3(Nodo* cabeza) {
    if (cabeza == NULL) {
        cout << "La lista esta vacia." << endl;
        return;
    }
    int mayorPositivo = -51;
    int menorNegativo = 51;
    Nodo* temp = cabeza;
    while (temp != NULL) {
        if (temp->dato > 0 && temp->dato > mayorPositivo) {
            mayorPositivo = temp->dato;
        } else if (temp->dato < 0 && temp->dato < menorNegativo) {
            menorNegativo = temp->dato;
        }
        temp = temp->siguiente;
    }
    cout << "Nodo positivo mayor: " << mayorPositivo << endl;
    cout << "Nodo negativo menor: " << menorNegativo << endl;
}

void opcion4(Nodo*& cabeza, Nodo*& cola) {
    if (cabeza == NULL) {
        cout << "La lista está vacía." << endl;
        return;
    }

    int valor;
    cout << "Ingrese el valor a buscar y eliminar: ";
    cin >> valor;

    Nodo* actual = cabeza;
    Nodo* anterior = NULL;
    int posicion = 0;
    bool encontrado = false;

    while (actual != NULL) {
        if (actual->dato == valor) {
            encontrado = true;
            break;
        }
        anterior = actual;
        actual = actual->siguiente;
        posicion++;
    }

    if (encontrado) {
        if (anterior == NULL) {  
            cabeza = actual->siguiente;
        } else {
            anterior->siguiente = actual->siguiente;
        }
        if (actual == cola) {  
            cola = anterior;
        }
        delete actual;
        cout << "Nodo con valor " << valor << " eliminado en la posicion " << posicion << "." << endl;
    } else {
        cout << "Valor no encontrado en la lista." << endl;
    }

    mostrarLista(cabeza);
}

void opcion5(Nodo* cabeza) {
    mostrarLista(cabeza);
}

int longitudLista(Nodo* cabeza) {
    int longitud = 0;
    Nodo* temp = cabeza;
    while (temp != NULL) {
        longitud=longitud+1;
        temp = temp->siguiente;
    }
    return longitud;
}

