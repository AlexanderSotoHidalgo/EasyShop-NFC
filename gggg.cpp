#include <iostream>
#include <iomanip>

using namespace std;

struct nodo {
     int codigo;
    float peso;
    struct nodo* siguiente;
};

typedef struct nodo *TpLista;

// Función para agregar un paquete al final de la lista
void agregarPaquete(TpLista &cabeza, int codigo, float peso) {
    TpLista nuevo = new nodo{codigo, peso, NULL};
    
    if (!cabeza) {
        cabeza = nuevo;
    } else {
        TpLista temp = cabeza;
        while (temp->siguiente != NULL) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo;
    }
}

// Función para calcular la cantidad total de paquetes
int contarPaquetes(TpLista cabeza) {
    int contador = 0;
    TpLista temp = cabeza;
    while (temp != NULL) {
        contador++;
        temp = temp->siguiente;
    }
    return contador;
}

// Función para calcular el peso promedio de los paquetes
float pesoPromedio(TpLista cabeza) {
    if (!cabeza) return 0;
    float sumaPesos = 0;
    int contador = 0;
    TpLista temp = cabeza;
    while (temp != NULL) {
        sumaPesos += temp->peso;
        contador++;
        temp = temp->siguiente;
    }
    return sumaPesos / contador;
}

// Función para mostrar la lista de paquetes
void mostrarPaquetes(TpLista cabeza) {
    TpLista temp = cabeza;
    cout << "Lista de Paquetes:\n";
    while (temp != NULL) {
        cout << "Código: " << temp->codigo << " - Peso: " << fixed << setprecision(2) << temp->peso << " kg\n";
        temp = temp->siguiente;
    }
    cout << endl;
}

// Método de ordenación por selección
void ordenarPorSeleccion(TpLista &cabeza) {
    if (!cabeza) return;
    TpLista i = cabeza;
    while (i != NULL) {
        TpLista menor = i;
        TpLista j = i->siguiente;
        while (j != NULL) {
            if (j->peso < menor->peso) {
                menor = j;
            }
            j = j->siguiente;
        }
        // Intercambio de datos
        if (i != menor) {
            swap(i->peso, menor->peso);
            swap(i->codigo, menor->codigo);
        }
        i = i->siguiente;
    }
}

// Método de ordenación por inserción
void ordenarPorInsercion(TpLista &cabeza) {
    if (!cabeza) return;
    TpLista ordenada = NULL;
    TpLista actual = cabeza;
    while (actual != NULL) {
        TpLista siguiente = actual->siguiente;
        if (!ordenada || actual->peso < ordenada->peso) {
            actual->siguiente = ordenada;
            ordenada = actual;
        } else {
            TpLista temp = ordenada;
            while (temp->siguiente && temp->siguiente->peso < actual->peso) {
                temp = temp->siguiente;
            }
            actual->siguiente = temp->siguiente;
            temp->siguiente = actual;
        }
        actual = siguiente;
    }
    cabeza = ordenada;
}

// Método de ordenación por intercambio (burbuja)
void ordenarPorIntercambio(TpLista &cabeza) {
    if (!cabeza) return;
    bool huboIntercambio;
    do {
        huboIntercambio = false;
        TpLista temp = cabeza;
        while (temp->siguiente != NULL) {
            if (temp->peso > temp->siguiente->peso) {
                swap(temp->peso, temp->siguiente->peso);
                swap(temp->codigo, temp->siguiente->codigo);
                huboIntercambio = true;
            }
            temp = temp->siguiente;
        }
    } while (huboIntercambio);
}
void ordenarBurbuja(TpLista &cabeza) {
    if (!cabeza) return;
    bool huboIntercambio;
    do {
        huboIntercambio = false;
        TpLista temp = cabeza;
        while (temp-> siguiente != NULL) {
            if (temp->peso > temp->siguiente->peso) {
                // Intercambio de valores
                swap(temp->peso, temp->siguiente->peso);
                swap(temp->codigo, temp->siguiente->codigo);
                huboIntercambio = true;
            }
            temp = temp->siguiente;
        }
    } while (huboIntercambio);
}

int main() {
    TpLista cabeza = NULL;
    int opcion, codigo;
    float peso;
    
    do {
        cout << "1. Agregar paquete\n2. Mostrar lista de paquetes\n3. Ordenar por Selección\n";
        cout << "4. Ordenar por Inserción\n5. Ordenar por Intercambio\n6. Ordenar por Burbuja\n7. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese el código del paquete: ";
                cin >> codigo;
                cout << "Ingrese el peso del paquete (kg): ";
                cin >> peso;
                agregarPaquete(cabeza, codigo, peso);
                cout << "\nPaquete agregado!\n";
                mostrarPaquetes(cabeza);
                cout << "Cantidad de paquetes: " << contarPaquetes(cabeza) << endl;
                cout << "Peso promedio: " << fixed << setprecision(2) << pesoPromedio(cabeza) << " kg\n";
                break;
            case 2:
                mostrarPaquetes(cabeza);
                cout << "Cantidad de paquetes: " << contarPaquetes(cabeza) << endl;
                cout << "Peso promedio: " << fixed << setprecision(2) << pesoPromedio(cabeza) << " kg\n";
                break;
            case 3:
                ordenarPorSeleccion(cabeza);
                cout << "\nLista ordenada por selección:\n";
                mostrarPaquetes(cabeza);
                break;
            case 4:
                ordenarPorInsercion(cabeza);
                cout << "\nLista ordenada por inserción:\n";
                mostrarPaquetes(cabeza);
                break;
            case 5:
                ordenarPorIntercambio(cabeza);
                cout << "\nLista ordenada por intercambio:\n";
                mostrarPaquetes(cabeza);
                break;
            case 6:
                ordenarBurbuja(cabeza);
                cout << "\nLista ordenada por Burbuja:\n";
                mostrarPaquetes(cabeza);
                break;
            case 7:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción no válida!\n";
                break;
        }
    } while (opcion != 7);

    return 0;
}
