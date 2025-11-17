#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Definición de la estructura de nodo de una lista doblemente enlazada
struct Nodo {
    int valor;
    Nodo *sgte;
    Nodo *ante;
};

typedef Nodo* TpLista;  // Definición de TpLista

// Función para crear un nodo nuevo
TpLista crearNodo(int valor) {
    TpLista nuevo = new Nodo;
    nuevo->valor = valor;
    nuevo->sgte = NULL;
    nuevo->ante = NULL;
    return nuevo;
}

// Función para insertar un nodo al final de la lista
void insertarFinal(TpLista &lista, int valor) {
    TpLista nuevo = crearNodo(valor);
    if (lista == NULL) {
        lista = nuevo;
    } else {
        TpLista aux = lista;
        while (aux->sgte != NULL) {
            aux = aux->sgte;
        }
        aux->sgte = nuevo;
        nuevo->ante = aux;
    }
}

// Función para mostrar la lista
void mostrarLista(TpLista lista) {
    TpLista aux = lista;
    while (aux != NULL) {
        cout << aux->valor << " ";
        aux = aux->sgte;
    }
    cout << endl;
}

// Función para mostrar el estado actual del vector de pivotes
void mostrarVector(const vector<int> &arreglo, int posicionPivote) {
    cout << "Estado actual del vector: ";
    for (int i = 0; i < posicionPivote; i++) {
        cout << arreglo[i] << " ";
    }
    cout << endl;
}

// Función para intercambiar valores de dos nodos
void intercambiar(TpLista a, TpLista b) {
    int temp = a->valor;
    a->valor = b->valor;
    b->valor = temp;
}

// Función para particionar y mover el pivote
void particionar(TpLista &inicio, TpLista &fin) {
    TpLista pivote = inicio;
    TpLista der = fin;

    // Recorre desde el último nodo hacia el primero (pivote)
    while (der != inicio) {
        if (pivote->valor > der->valor) {
            intercambiar(pivote, der);  // Intercambia si es necesario
        }
        der = der->ante;  // Mueve al nodo anterior
    }
}

// Función que realiza el proceso con la lista y el vector
void ordenarPorPivote(TpLista &lista, vector<int> &arreglo, int &posicionPivote) {
    if (lista == NULL) return;

    // Encontrar el último nodo
    TpLista fin = lista;
    while (fin->sgte != NULL) {
        fin = fin->sgte;
    }

    // Aplicar el proceso de pivote
    particionar(lista, fin);

    // Colocar el pivote en el vector
    arreglo[posicionPivote] = lista->valor;
    posicionPivote++;

    // Mostrar el estado actual
    cout << "Después de procesar pivote " << lista->valor << ":" << endl;
    cout << "Lista actual: ";
    mostrarLista(lista);
    mostrarVector(arreglo, posicionPivote);

    // Eliminar el pivote de la lista y repetir
    TpLista temp = lista;
    if (lista->sgte != NULL) {
        lista = lista->sgte;
        lista->ante = NULL;
        delete temp;
        ordenarPorPivote(lista, arreglo, posicionPivote);
    }
}

int main() {
    srand(time(0));
    TpLista lista = NULL;
    int n;

    // Solicitar el número de elementos en la lista y validar que sea >= 5
    do {
        cout << "Ingrese el número de elementos en la lista (n >= 5): ";
        cin >> n;
        if (n < 5) {
            cout << "Error: El número de elementos debe ser mayor o igual a 5." << endl;
        }
    } while (n < 5);

    // Llenar la lista con valores aleatorios entre 1 y 100
    for (int i = 0; i < n; i++) {
        int valor = rand() % 100 + 1;
        insertarFinal(lista, valor);
    }

    // Mostrar la lista inicial
    cout << "Lista inicial: ";
    mostrarLista(lista);

    // Inicializar el vector donde se almacenarán los pivotes
    vector<int> arreglo(n);
    int posicionPivote = 0;

    // Aplicar el proceso de pivote y ordenamiento
    ordenarPorPivote(lista, arreglo, posicionPivote);

    // Mostrar el arreglo final con los pivotes ordenados
    cout << "Arreglo final ordenado: ";
    for (int i = 0; i < n; i++) {
        cout << arreglo[i] << " ";
    }
    cout << endl;

    return 0;
}

