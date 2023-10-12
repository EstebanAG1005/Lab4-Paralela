// Ejercicio#3- Paralela
// Esteban Aldana Guerra - 20591

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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
double trapezoides(double (*func)(double), double a, double b, int n)
{
    double h = (b - a) / n;
    double result = 0.5 * (func(a) + func(b));
    for (int i = 1; i < n; i++)
    {
        result += func(a + i * h);
    }
    result *= h;
    return result;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Usage: %s <a> <b>\n", argv[0]);
        return 1;
    }

    double a = atof(argv[1]);
    double b = atof(argv[2]);
    int n = 10000000; // 10e6

    // Iniciar a medir el tiempo
    clock_t start_time = clock();
    
    if (a == 0.0 && b == 1.0)
    {
        printf("Con n = %d trapezides, nuestra aproximacion de la integral de %lf a %lf de x^2 es %lf\n",
               n, a, b, trapezoides(f1, a, b, n));
    }
    else if (a == 3.0 && b == 7.0)
    {
        printf("Con n = %d trapezides, nuestra aproximacion de la integral de %lf a %lf de 2x^3 es %lf\n",
               n, a, b, trapezoides(f2, a, b, n));
    }
    else if (a == 1.0 && b == 2.0)
    {
        printf("Con n = %d trapezides, nuestra aproximacion de la integral de %lf a %lf de sin(x) es %lf\n",
               n, a, b, trapezoides(f3, a, b, n));
    }
    else
    {
        printf("Intervalo no reconocido.\n");
    }

    // Terminar de medir el tiempo y calcular la duración
    clock_t end_time = clock();
    double duration = ((double) (end_time - start_time)) / CLOCKS_PER_SEC; // Duración en segundos
    
    printf("El cálculo tomó %f segundos para completarse.\n", duration);
    
    return 0;
}
