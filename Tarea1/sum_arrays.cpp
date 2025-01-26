#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

#define ARRAY_SIZE 1000   // Tamaño de los arreglos
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
    std::cout << "Suma de Arreglos en Paralelo\n\n";

    float A[ARRAY_SIZE], B[ARRAY_SIZE], C[ARRAY_SIZE];
    srand(static_cast<unsigned>(time(0))); // Semilla para la generación de números aleatorios

    // Llenar los arreglos A y B con valores aleatorios
    fillArray(A, ARRAY_SIZE);
    fillArray(B, ARRAY_SIZE);

    // Suma paralela de los arreglos A y B en C
    #pragma omp parallel for shared(A, B, C) schedule(static, CHUNK)
    for (int index = 0; index < ARRAY_SIZE; index++) {
        C[index] = A[index] + B[index];
    }

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

    return 0;
}
