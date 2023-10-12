// riemann_mpi.c
#include <stdio.h>
#include <mpi.h>

// Definir la función a integrar
double f(double x) {
    return x * x; // Por ejemplo, x^2
}

double compute_sum(double a, double b, int n, double h) {
    double sum = 0.0;
    for(int i = 0; i < n; i++) {
        sum += f(a + i * h);
    }
    return sum * h;
}

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double a = 0.0; // Límite inferior
    double b = 1.0; // Límite superior
    int n = 1000000; // Número de intervalos
    double h = (b - a) / n; // Tamaño del intervalo
    
    int local_n = n / size; // Número de intervalos por proceso
    double local_a = a + rank * local_n * h; // Límite inferior local
    double start_time, end_time;

    start_time = MPI_Wtime();
    
    double local_sum = compute_sum(local_a, local_a + local_n * h, local_n, h); // Suma local
    
    double total_sum;
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    end_time = MPI_Wtime(); // Detener el cronometro
    
    if(rank == 0) {
        printf("Aproximación de la integral: %f\n", total_sum);
        printf("Tiempo recorrido = %f segundos\n", end_time - start_time);
    }
    
    
    MPI_Finalize();
    return 0;
}

