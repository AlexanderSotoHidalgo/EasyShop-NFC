#include <iostream>
#include <cstdlib>
#include <ctime>

int generarAleatorio(int min, int max) {
    return min + rand() % (max - min + 1);
}


void mezclarArreglo(int* arr, int n) {
    for (int i = 0; i < n; ++i) {
        int j = rand() % n;
        std::swap(arr[i], arr[j]);
    }
}

int main() {
    srand(time(0)); 

    int n;
    std::cout << "Ingrese el valor de n (mayor de 5): ";
    std::cin >> n;

    if (n <= 5) {
        std::cout << "El valor de n debe ser mayor de 5." << std::endl;
        return 1;
    }

    int* arregloOriginal = new int[n];


    for (int i = 0; i < n / 2; ++i) {
        arregloOriginal[i] = generarAleatorio(-50, -20);
    }
    for (int i = n / 2; i < n; ++i) {
        arregloOriginal[i] = generarAleatorio(20, 50);
    }

    mezclarArreglo(arregloOriginal, n);


    std::cout << "Arreglo original: ";
    for (int i = 0; i < n; ++i) {
        std::cout << arregloOriginal[i] << " ";
    }
    std::cout << std::endl;


    int primerElemento = arregloOriginal[0];
    int ultimoElemento = arregloOriginal[n - 1];
    int sumaExtremos = primerElemento + ultimoElemento;


    int* nuevoArreglo = new int[n - 1];
    nuevoArreglo[0] = sumaExtremos;

    for (int i = 1; i < n - 1; ++i) {
        nuevoArreglo[i] = arregloOriginal[i];
    }

    std::cout << "Nuevo arreglo: ";
    for (int i = 0; i < n - 1; ++i) {
        std::cout << nuevoArreglo[i] << " ";
    }
    std::cout << std::endl;


    delete[] arregloOriginal;
    delete[] nuevoArreglo;

    return 0;
}
