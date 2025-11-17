#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct nodo {
    int nro;
    int original; 
    struct nodo *sgte;
    struct nodo *ante;
};

struct Pila {
    int dato;
    Pila *sgte;
};

typedef struct nodo *TpLista;

TpLista crearNodo(int valor);
void MostrarLista(TpLista lista);
void InsertaInicioLista(TpLista &lista, int valor);
void MostrarPila(Pila *pila);
void insertarNodoPila(Pila *&pila, int valor);
int extraerNodoPila(Pila *&pila);
void modificarListaMultiplicandoPor2(TpLista lista);
void modificarListaSumaInversa(TpLista lista);
void MostrarListaConOriginal(TpLista lista);
void MostrarLista(TpLista lista);

int generarAleatorio() {
    int num;
    do {
        num = rand() % 201 - 100; 
    } while (num == 0);
    return num;
}

int generarPositivo() {
    int num;
    do {
        num = rand() % 100 + 1; 
    } while (num <= 0);
    return num;
}

int generarNegativo() {
    int num;
    do {
        num = -(rand() % 100 + 1); 
    } while (num >= 0);
    return num;
}

void insertarNodoPila(Pila *&pila, int valor) {
    Pila *nuevo = new Pila;
    nuevo->dato = valor;
    nuevo->sgte = pila;
    pila = nuevo;
}

void MostrarPila(Pila *pila) {
    Pila *aux = pila;
    cout << "\nPila actual:\n";
    while (aux != NULL) {
        cout << aux->dato << " ";
        aux = aux->sgte;
    }
    cout << endl;
}

int extraerNodoPila(Pila *&pila) {
    if (pila == NULL) {
        cout << "La pila esta vacia" << endl;
        return 0;
    }
    Pila *aux = pila;
    int dato = aux->dato;
    pila = aux->sgte;
    delete aux;
    return dato;
}

TpLista crearNodo(int valor) {
    TpLista nuevo = new(struct nodo);
    nuevo->nro = valor;
    nuevo->original = valor; 
    nuevo->sgte = NULL;
    nuevo->ante = NULL;
    return nuevo;
}

void MostrarListaConOriginal(TpLista lista) {
    int i = 0;
    TpLista retorno = NULL;
    cout << "\nLista en ida (valor actual y original):\n";
    while (lista != NULL) {
        cout << i+1 << ") Valor actual: " << lista->nro << " - Valor original: " << lista->original << endl;
        retorno = lista;
        lista = lista->sgte;
        i++;
    }
    lista = retorno;
    i = 0;
    cout << "\nLista en vuelta (valor actual y original):\n";
    while (lista != NULL) {
        cout << i+1 << ") Valor actual: " << lista->nro << " - Valor original: " << lista->original << endl;
        lista = lista->ante;
        i++;
    }
}

void MostrarLista(TpLista lista) {
    int i = 0;
    TpLista retorno = NULL;
    cout << "\nLista en ida :\n";
    while (lista != NULL) {
        cout << i+1 << ") Valor actual: " << lista->nro <<endl;
        retorno = lista;
        lista = lista->sgte;
        i++;
    }
    lista = retorno;
    i = 0;
    cout << "\nLista en vuelta :\n";
    while (lista != NULL) {
        cout << i+1 << ") Valor actual: " << lista->nro << endl;
        lista = lista->ante;
        i++;
    }
}

void InsertaInicioLista(TpLista &lista, int valor) {
    TpLista nuevo = crearNodo(valor);
    if (lista != NULL) {
        nuevo->sgte = lista;
        lista->ante = nuevo;
    }
    lista = nuevo;
}

void modificarListaMultiplicandoPor2(TpLista lista) {
    cout << "\nModificando la lista multiplicando cada valor por 2 (ida):\n";
    while (lista != NULL) {
        lista->nro *= 2;
        lista = lista->sgte;
    }
}

void modificarListaSumaInversa(TpLista lista) {
    TpLista ultimo = lista;
    while (ultimo->sgte != NULL) {
        ultimo = ultimo->sgte;
    }
    cout << "\nModificando la lista sumando valores en la vuelta:\n";
    while (ultimo != NULL && ultimo->ante != NULL) {
        ultimo->ante->nro += ultimo->nro; 
        ultimo = ultimo->ante;
    }
}

void menu() {
    system("cls"); 
    cout << "\n\LABORATORIO 5";
    cout << "\n\tMENU\n";
    cout << "1. Inserta el nodo positivo y negativo a la pila\n";
    cout << "2. Extrae dos nodos de la pila,suma y agrega en la lista doblemente enlazada\n";
    cout << "3. Recorre la lista de ida y vuelta, modificando los valores\n";
    cout << "0. Salir\n";
    cout << "Ingresar la opcion ---> ";
}

int main() {
    srand(time(NULL));  
    Pila *pila = NULL;
    TpLista lista = NULL;
    char opc = ' ';
    
    do {
        menu();
        cin >> opc;
        switch (opc) {
            case '1': {
                int numPos = generarPositivo(); 
                int numNeg = generarNegativo(); 
                insertarNodoPila(pila, numPos);
                insertarNodoPila(pila, numNeg);
                MostrarPila(pila);
                break;
            }
            case '2': {
                if (pila == NULL || pila->sgte == NULL) {
                    cout << "No hay suficientes nodos en la pila para extraer." << endl;
                } else {
                    int valor1 = extraerNodoPila(pila);
                    int valor2 = extraerNodoPila(pila);
                    int suma = valor1 + valor2;
                    InsertaInicioLista(lista, suma);
                    MostrarPila(pila);
                    MostrarLista(lista);
                }
                break;
            }
            case '3': {
                if (lista == NULL) {
                    cout << "La lista está vacía." << endl;
                } else {
                    MostrarLista(lista);
                    modificarListaMultiplicandoPor2(lista); 
                    MostrarListaConOriginal(lista);
                    modificarListaSumaInversa(lista);
                    MostrarListaConOriginal(lista);
                }
                break;
            }
            case '0': {
                cout << "Saliendo del programa..." << endl;
                break;
            }
            default:
                cout << "La opción es inválida." << endl;
        }
        system("pause");  
    } while (opc != '0');
    
    return 0;
}


