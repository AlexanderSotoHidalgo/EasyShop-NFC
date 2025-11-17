#include <iostream>
#include <cstdlib>  
#include <ctime>    

using namespace std;

struct nodo {
    int nro;
    struct nodo* sgte;
};

typedef struct nodo* TpLista;

TpLista crearNodo(int valor);
void MostrarLista(TpLista lista);
void InsertaInicio(TpLista& lista, int valor);
void InsertaFinal(TpLista& lista, int valor);
void opcion1(TpLista& lista);
void opcion2(TpLista& lista);
void opcion3(TpLista lista);
void opcion4(TpLista& lista);
int longitudLista(TpLista lista);

int main() {
    srand(time(0));  
    TpLista lista = NULL;
    char opc = ' ';
    do {
        system("CLS");
        cout << "LABORATORIO 3\n";
        cout << "\n--- MENU ---\n";
        cout << "1.- Crea dos nodos aleatorios y lo añade a la lista" << endl;
        cout << "2.- Inserta en el nodo el valor promedio en la posicion media" << endl;
        cout << "3.- Muestra el nodo positivo mayor y el nodo negativo menor" << endl;
        cout << "4.- Busca y elimina un nodo de la lista" << endl;
        cout << "5.- Muestra los elementos de la lista" << endl;
        cout << "0.- Salir del menu" << endl << endl;
        cout << " Ingresar opcion ---> ";
        cin >> opc;

        switch (opc) {
            case '1':
                opcion1(lista);
                break;
            case '2':
                opcion2(lista);
                break;
            case '3':
                opcion3(lista);
                break;
            case '4':
                opcion4(lista);
                break;
            case '5':
                MostrarLista(lista);
                break;
            case '0':
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "La opcion elegida no existe" << endl;
        }
        system("pause");
    } while (opc != '0');
    return 0;
}

TpLista crearNodo(int valor) {
    TpLista nuevo = new(struct nodo);
    nuevo->nro = valor;
    nuevo->sgte = NULL;
    return nuevo;
}

void MostrarLista(TpLista lista) {
    TpLista t = lista;
    int i = 0;
    while (t != NULL) {
        cout << i + 1 << ") " << t->nro << endl;
        t = t->sgte;
        i=i+1;
    }
}

void InsertaInicio(TpLista& lista, int valor) {
    TpLista n = crearNodo(valor);
    if (lista != NULL)
        n->sgte = lista;
    lista = n;
}

void InsertaFinal(TpLista& lista, int valor) {
    TpLista n = crearNodo(valor);
    if (lista == NULL) {
        lista = n;
    } else {
        TpLista t = lista;
        while (t->sgte != NULL)
            t = t->sgte;
        t->sgte = n;
    }
}

int longitudLista(TpLista lista) {
    int longitud = 0;
    TpLista t = lista;
    while (t != NULL) {
        longitud=longitud+1;
        t = t->sgte;
    }
    return longitud;
}

void opcion1(TpLista& lista) {
    int valorPositivo = (rand() % 50) + 1;  
    int valorNegativo = -(rand() % 50 + 1); 
    InsertaInicio(lista, valorPositivo);
    InsertaFinal(lista, valorNegativo);
    MostrarLista(lista);
}

void opcion2(TpLista& lista) {
    int longitud = longitudLista(lista);
    if (longitud == 0) {
        cout << "La lista esta vacia." << endl;
        return;
    }
    int suma = 0;
    TpLista temp = lista;
    while (temp != NULL) {
        suma = suma + temp->nro;
        temp = temp->sgte;
    }
    int promedio = suma / longitud;
    int posicionMedia = longitud / 2;
    TpLista nuevo = crearNodo(promedio);
    if (posicionMedia == 0) {
        InsertaInicio(lista, promedio);
    } else {
        TpLista actual = lista;
        for (int i = 0; i < posicionMedia - 1; i++) {
            actual = actual->sgte;
        }
        nuevo->sgte = actual->sgte;
        actual->sgte = nuevo;
    }
    MostrarLista(lista);
}

void opcion3(TpLista lista) {
    if (lista == NULL) {
        cout << "La lista esta vacia." << endl;
        return;
    }
    int mayorPositivo = -51;
    int menorNegativo = 51;
    TpLista temp = lista;
    while (temp != NULL) {
        if (temp->nro > 0 && temp->nro > mayorPositivo) {
            mayorPositivo = temp->nro;
        } else if (temp->nro < 0 && temp->nro < menorNegativo) {
            menorNegativo = temp->nro;
        }
        temp = temp->sgte;
    }
    cout << "El nodo positivo mayor es " << mayorPositivo << endl;
    cout << "El nodo negativo menor es " << menorNegativo << endl;
}

void opcion4(TpLista& lista) {
    if (lista == NULL) {
        cout << "La lista está vacia." << endl;
        return;
    }
    int valor;
    cout << "Ingrese el valor a buscar y eliminar: ";
    cin >> valor;
    TpLista actual = lista, anterior = NULL;
    int posicion = 0;
    bool encontrado = false;
    while (actual != NULL) {
        if (actual->nro == valor) {
            encontrado = true;
            break;
        }
        anterior = actual;
        actual = actual->sgte;
        posicion=posicion+1;
    }
    if (encontrado) {
        if (anterior == NULL) {  
            lista = actual->sgte;
        } else {
            anterior->sgte = actual->sgte;
        }
        delete actual;
        cout << "El nodo con valor " << valor << " es eliminado en la posición " << posicion + 1 << "." << endl;
    } else {
        cout << "El valor no fue encontrado en la lista." << endl;
    }
    MostrarLista(lista);
}

