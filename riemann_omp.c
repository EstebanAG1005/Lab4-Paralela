// Ejercicio#4- Paralela
// Esteban Aldana Guerra - 20591

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

// Función para integrar x^2
double f1(double x)
{
    return x * x;
}

// Función para integrar 2x^3
double f2(double x)
{
    return 2 * x * x * x;
}

// Función para integrar sin(x)
double f3(double x)
{
    return sin(x);
}

// Función que implementa la regla del trapezoide
double trapezoides(double (*func)(double), double a, double b, int n, int threads)
{
    double h = (b - a) / n;
    double result = 0.5 * (func(a) + func(b));

    int n_local = n / threads;

#pragma omp parallel num_threads(threads)
    {
        int ID = omp_get_thread_num();
        double a_local = a + ID * n_local * h;
        double b_local = a_local + n_local * h;

        double local_result = 0.0;
        for (int i = 1; i <= n_local; i++)
        {
            local_result += func(a_local + i * h);
        }

#pragma omp critical
        {
            result += local_result;
        }
    }

    result *= h;
    return result;
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: ./executable a b num_threads\n");
        return 1;
    }

    double a = atof(argv[1]);
    double b = atof(argv[2]);
    int threads = atoi(argv[3]);

    // Comienza a medir el tiempo
    double start_time = omp_get_wtime();
    
    if (a == 0 && b == 1)
    {
        printf("con n = 10000000 trapezides, usando %d threads, nuestra aproximacion ", threads);
        printf("de la integral de %lf a %lf de x^2 es %lf\n", a, b, trapezoides(f1, a, b, 10000000, threads));
    }
    else if (a == 3 && b == 7)
    {
        printf("con n = 10000000 trapezides, usando %d threads, nuestra aproximacion ", threads);
        printf("de la integral de %lf a %lf de 2x^3 es %lf\n", a, b, trapezoides(f2, a, b, 10000000, threads));
    }
    else if (a == 1 && b == 2)
    {
        printf("con n = 10000000 trapezides, usando %d threads, nuestra aproximacion ", threads);
        printf("de la integral de %lf a %lf de sin(x) es %lf\n", a, b, trapezoides(f3, a, b, 10000000, threads));
    }
    else
    {
        printf("Función no especificada para el intervalo dado.\n");
    }

    // Finaliza la medición del tiempo y calcula la duración
    double end_time = omp_get_wtime();
    printf("El cálculo tomó %f segundos para completarse.\n", end_time - start_time);

    return 0;
}
