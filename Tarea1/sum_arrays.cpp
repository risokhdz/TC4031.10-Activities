#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

#define CHUNK 100 // Tamaño del chunk para el bucle for paralelo
#define SHOW 10   // Número de elementos a mostrar

// Función para imprimir los primeros SHOW elementos de un arreglo
void printArray(const float *array) {
    std::cout << "[ ";
    for (int index = 0; index < SHOW; index++) {
        std::cout << array[index];
        if (index < SHOW - 1) {
            std::cout << ", ";
        }
    }
    std::cout << " ]" << std::endl;
}

// Función para llenar un arreglo con valores aleatorios
void fillArray(float *array, int size) {
    for (int index = 0; index < size; index++) {
        array[index] = static_cast<float>(rand() % 100); // Valores aleatorios entre 0 y 99
    }
}

int main() {
    int array_size;
    std::cout << "Ingrese el tamaño del array (entre 1000 y 100000): ";
    std::cin >> array_size;

    // Limitar el tamaño del array entre 1000 y 100000
    if (array_size < 1000) {
        array_size = 1000;
    } else if (array_size > 100000) {
        array_size = 100000;
    }

    std::cout << "Suma de Arreglos en Paralelo\n\n";
    std::cout << "Tamaño del array: " << array_size << std::endl;

    float *A = new float[array_size];
    float *B = new float[array_size];
    float *C = new float[array_size];
    srand(static_cast<unsigned>(time(0))); // Semilla para la generación de números aleatorios

    // Llenar los arreglos A y B con valores aleatorios
    fillArray(A, array_size);
    fillArray(B, array_size);

    double start_time = omp_get_wtime(); // Tiempo de inicio

    // Suma paralela de los arreglos A y B en C
    #pragma omp parallel for shared(A, B, C) schedule(static, CHUNK)
    for (int index = 0; index < array_size; index++) {
        C[index] = A[index] + B[index];
    }

    double end_time = omp_get_wtime(); // Tiempo de fin

    // Imprimir los primeros elementos de cada arreglo basandose en la constante SHOW
    std::cout << "Primeros " << SHOW << " elementos del array A:" << std::endl;
    printArray(A);
    std::cout << std::endl;
    
    std::cout << "Primeros " << SHOW << " elementos del array B:" << std::endl;
    printArray(B);
    std::cout << std::endl;
    
    std::cout << "Primeros " << SHOW << " elementos del array C (Suma de A y B):" << std::endl;
    printArray(C);
    std::cout << std::endl;

    std::cout << "Tiempo de ejecución: " << (end_time - start_time) << " segundos" << std::endl;

    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}
