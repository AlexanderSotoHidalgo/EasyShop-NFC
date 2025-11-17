#include <iostream>
using namespace std;

struct nodo {
    string tienda;
    int cajas;
    int distancia;
    struct nodo *sgte;
    struct nodo *ante;
};

typedef struct nodo *TpLista;

// Función para crear un nodo
TpLista crearNodo(string tienda, int cajas, int distancia) {
    TpLista nuevo = new(struct nodo);
    nuevo->tienda = tienda;
    nuevo->cajas = cajas;
    nuevo->distancia = distancia;
    nuevo->sgte = NULL;
    nuevo->ante = NULL;
    return nuevo;
}

// Función para insertar al inicio
void insertaInicio(TpLista &lista, string tienda, int cajas, int distancia) {
    TpLista q = crearNodo(tienda, cajas, distancia);
    if (lista != NULL) {
        lista->ante->sgte = q;
        q->sgte = lista;
        q->ante = lista->ante;
        lista->ante = q;
        lista = q;
    } else {
        lista = q;
        q->sgte = lista;
        q->ante = lista;
    }
}

// Función para insertar al final
void insertaFinal(TpLista &lista, string tienda, int cajas, int distancia) {
    TpLista q = crearNodo(tienda, cajas, distancia);
    if (lista == NULL) {
        lista = q;
        q->sgte = lista;
        q->ante = lista;
    } else {
        lista->ante->sgte = q;
        q->ante = lista->ante;
        q->sgte = lista;
        lista->ante = q;
    }
}

// Función para insertar en una posición específica
void insertaPosicion(TpLista &lista, string tiendaRef, string nuevaTienda, int cajas, int distancia) {
    TpLista p = lista, q = crearNodo(nuevaTienda, cajas, distancia);
    bool flag = false;
    do {
        if (p->tienda == tiendaRef) {
            flag = true;
            break;
        }
        p = p->sgte;
    } while (p != lista);

    if (flag) {
        q->sgte = p;
        p->ante->sgte = q;
        q->ante = p->ante;
        p->ante = q;
    } else {
        cout << "ERROR: Tienda no encontrada..." << endl;
    }
}

// Función para mostrar la ruta y calcular la distancia total
void verLista(TpLista lista) {
    TpLista retorno = NULL, topePrimero = lista;
    int i = 0, distanciaTotal = 0;

    cout << "Ruta de despacho:" << endl;
    while (lista->sgte != topePrimero) {
        cout << i + 1 << ") Tienda: " << lista->tienda << ", Cajas: " << lista->cajas << ", Distancia: " << lista->distancia << " kms" << endl;
        retorno = lista;
        distanciaTotal += lista->distancia;
        lista = lista->sgte;
        i++;
    }
    cout << i + 1 << ") Tienda: " << lista->tienda << ", Cajas: " << lista->cajas << ", Distancia: " << lista->distancia << " kms" << endl;
    distanciaTotal += lista->distancia;

    cout << "Distancia total recorrida: " << distanciaTotal << " kms" << endl;
}

// Función para calcular la distancia adicional de regreso
int distanciaAdicional(TpLista lista, string destino, string puntoActual) {
    TpLista temp = lista;
    int distanciaIda = 0, distanciaVuelta = 0;

    // Buscar el punto actual
    while (temp->tienda != puntoActual) {
        temp = temp->sgte;
    }

    // Calcular la distancia de ida hasta la tienda olvidada
    do {
        distanciaIda += temp->distancia;
        if (temp->tienda == destino) break;
        temp = temp->ante;
    } while (temp != lista);

    // Volver al punto actual
    do {
        distanciaVuelta += temp->distancia;
        temp = temp->sgte;
    } while (temp->tienda != puntoActual);

    return distanciaIda + distanciaVuelta;
}

// Función para eliminar una tienda
void eliminarTienda(TpLista &lista, string tiendaEliminar) {
    TpLista temp = lista;
    do {
        if (temp->tienda == tiendaEliminar) {
            TpLista anterior = temp->ante;
            TpLista siguiente = temp->sgte;
            anterior->sgte = siguiente;
            siguiente->ante = anterior;
            if (temp == lista) lista = siguiente;
            delete(temp);
            return;
        }
        temp = temp->sgte;
    } while (temp != lista);
}

// Función para mostrar la ruta en sentido inverso
void verRutaInversa(TpLista lista) {
    TpLista temp = lista->ante;
    int distanciaTotal = 0;
    cout << "Ruta inversa de regreso:" << endl;
    do {
        cout << "Tienda: " << temp->tienda << ", Distancia: " << temp->distancia << " kms" << endl;
        distanciaTotal += temp->distancia;
        temp = temp->ante;
    } while (temp != lista->ante);
    cout << "Distancia total de regreso: " << distanciaTotal << " kms" << endl;
}

void menu() {
    cout << "\n---- Menu de Opciones ----\n";
    cout << "1. Mostrar la ruta y distancia total\n";
    cout << "2. Agregar la tienda Z\n";
    cout << "3. Calcular distancia adicional al regresar a Tienda B\n";
    cout << "4. Eliminar la Tienda C\n";
    cout << "5. Mostrar ruta inversa y calcular distancia\n";
    cout << "0. Salir\n";
    cout << "Seleccione una opcion: ";
}

int main() {
    TpLista ruta = NULL;

    // Crear la ruta inicial
    insertaFinal(ruta, "Tienda A", 2, 3);
    insertaFinal(ruta, "Tienda B", 1, 5);
    insertaFinal(ruta, "Tienda C", 3, 8);
    insertaFinal(ruta, "Tienda D", 4, 3);
    insertaFinal(ruta, "Tienda E", 1, 5);
    insertaFinal(ruta, "Fabrica", 0, 8);

    int opcion;
    do {
        menu();
        cin >> opcion;

        switch (opcion) {
            case 1:
                verLista(ruta);
                break;
            case 2:
                insertaPosicion(ruta, "Tienda A", "Tienda Z", 3, 2); // Se agrega tienda Z con la distancia correcta
                cout << "Tienda Z agregada correctamente.\n";
                break;
            case 3:
                cout << "Kilómetros adicionales recorridos: " << distanciaAdicional(ruta, "Tienda B", "Tienda D") << " kms\n";
                break;
            case 4:
                eliminarTienda(ruta, "Tienda C");
                cout << "Tienda C eliminada correctamente.\n";
                break;
            case 5:
                verRutaInversa(ruta);
                break;
            case 0:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción inválida. Intente de nuevo.\n";
        }
    } while (opcion != 0);

    return 0;
}

