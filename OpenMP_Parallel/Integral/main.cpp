#include <iostream>
#include <omp.h>
#include <time.h>

using namespace std;

double omp_get_wtime( void );

double countFunction(double x){
    return 1 / (1 + x * x);
}

double countIntegral(double a, double b, double dx){
    double n = (b - a) / dx;
    double w = 0, x = 0;
    for(long i = 0; i < n; i++){
        x = a + i*dx;
        w += countFunction(x) * dx;
    }
    return w;
}



double countIntegralParallel(double a, double b, double dx, int k, int m){
    double n = (b - a) / dx;
    double w = 0, x = 0;
    for(long i = k; i < n; i += m){
        x = a + i*dx;
        w += countFunction(x) * dx;
    }
    return w;
}


int main(int argc, char *argv[]) {
    //clock_t tStart = clock();
    long a = 0;
    long b = 1;
    double dx = 0.00000001;
    ///1 wersja
    double start = omp_get_wtime();
    cout << "Wersja 1 = " << countIntegral(a, b, dx) * 4 << endl;
    double end = omp_get_wtime();
    double time1 = end - start;
    //printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    cout << "Time : " << time1 << "s " << endl;
    ///2 wersja
    start = omp_get_wtime();
    //tStart = clock();
    double result[4];
    #pragma omp parallel
    {
        int k, m;
        k = omp_get_thread_num();
        m = omp_get_num_threads();
        double wyn = countIntegralParallel(a, b, dx, k, m);
        result[k] = wyn;
    }
    end = omp_get_wtime();
    time1 = end - start;
    cout << "Wersja 2 = " << (result[0] + result[1] + result[2] + result[3]) * 4 << endl;
    cout << "Time : " << time1 << "s " << endl;
    //printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

   ///3 wersja
   //tStart = clock();
    start = omp_get_wtime();
   double suma;
    long h = (b - a)/ dx;
    #pragma omp parallel for reduction(+: suma)
        for(long i = 0; i < h; i++) suma += countFunction(i*dx)*dx;
    cout << "Wersja 3 = " << suma * 4  << endl;
    end = omp_get_wtime();
    time1 = end - start;
    cout << "Time : " << time1 << "s " << endl;
    return 0;
}
