/**
	A simple example to show the impact of some compiler optimizations
	and parallelization in terms of execution time, power and energy.
	
	FEUP, October 2021
	
	
	Measure execution time, power and energy consumption for the following compiler options:
	gcc -std=gnu99 -Os -march=native autovect.c -o autovect_os
	gcc -std=gnu99 -O1 -march=native autovect.c -o autovect_o1
	gcc -std=gnu99 -O2 -march=native autovect.c -o autovect_o2
	gcc -std=gnu99 -O2 -march=native -fopenmp autovect.c -o autovect_o2_omp
	gcc -std=gnu99 -O3 -march=native -fno-tree-vectorize autovect.c -o autovect_o3_wvec
	gcc -std=gnu99 -O3 -march=native autovect.c -o autovect_o3
	gcc -std=gnu99 -Ofast -march=native autovect.c -o autovect_ofast
	gcc -std=gnu99 -O3 -march=native -fno-tree-vectorize -fopenmp autovect.c -o autovect_o3_wvec_omp
	gcc -std=gnu99 -O3 -march=native -fopenmp autovect.c -o autovect_o3_omp
	gcc -std=gnu99 -Ofast -march=native -fopenmp autovect.c -o autovect_ofast_omp
	gcc -std=gnu99 -m64 -Ofast -flto -march=native -funroll-loops autovect.c -o autovect_ofast_1
	gcc -std=gnu99 -m64 -Ofast -flto -march=native -funroll-loops -fopenmp autovect.c -o autovect_ofast_1_omp
	
	Analyze assembly at: https://godbolt.org/
	
	#define N 80000000
	void kernel(float * __restrict A, float * __restrict B, float * __restrict C, float D) {
		int i;
		for (i = 0; i < N; i++) {
			C[i] = (A[i]*B[i])+D;
		}
	}
	
	Analyze impact of:
		-O3  -march=native -fno-tree-vectorize -mno-avx2
		use of __restrict
		use of -mavx2
		-O3  -march=native -fno-tree-vectorize
		-O3  -march=native
		-mavx -mavx2 -mfma -msse4.2 -msse4.1 
		-O3 -mno-fma4 -mno-sse -mno-fma -mno-avx -march=native -fno-tree-vectorize
	
	GCC options:
	https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
	
	x86 options: 
	https://gcc.gnu.org/onlinedocs/gcc/x86-Options.html
*/

#include <stdio.h>
#include <math.h>

//#define WINDOWS_TIMING // for considering timing measurements in Windows

#ifdef WINDOWS_TIMING
	#include <windows.h>
#endif

#ifndef N
# define N 80000000
#endif

/* Default data type is double. */
#ifndef DATA_TYPE
# define DATA_TYPE float
#endif

/* Array declaration. */
DATA_TYPE A[N];
DATA_TYPE B[N];
DATA_TYPE C[N];

/* initialization of arrays */
//static inline
void init_array(DATA_TYPE * __restrict A, DATA_TYPE * __restrict B)
{
  int i;
  #pragma omp parallel for private(i) //num_threads(16)
  for (i = 0; i < N; i++){
      A[i] = (DATA_TYPE) ((int) i / N);
      B[i] = (DATA_TYPE) ((int) i / N);
  }
}


/* kernel */
//static inline
void kernel(DATA_TYPE * __restrict A, DATA_TYPE * __restrict B, DATA_TYPE * __restrict C, DATA_TYPE D)
{
	int i;
	#pragma omp parallel for private(i) //num_threads(16)
    for (i = 0; i < N; i++)
    {
    	C[i] = (A[i]*B[i])+D;
	}
}

/**
	Sum all.
*/
long sumall(DATA_TYPE * C) 
{
	long i;
	long sum = 0L;
	#pragma omp parallel for private(i) reduction(+:sum) //num_threads(16)
	for (i = 0; i < N; i++)
    {
    	sum += (long) C[i];
	}
	return sum;
}

int main(int argc, char** argv)
{
  DATA_TYPE D = (DATA_TYPE) 200;
  
  //mem_flush(A, N);
  //mem_flush(B, N);
  //mem_flush(C, N);

  /* Initialize array. */
  init_array(A, B);
  
  #ifdef WINDOWS_TIMING
	 __int64 freq, start, end;
    long elapsedTime;
    // get ticks per second
    QueryPerformanceFrequency( ( LARGE_INTEGER* )&freq );
    // start timer
    QueryPerformanceCounter( ( LARGE_INTEGER* )&start );
#endif

	/* Kernel */
	kernel(A,B,C,D);

  /* Stop and print timer. */
#ifdef WINDOWS_TIMING	
	QueryPerformanceCounter( ( LARGE_INTEGER* )&end );
    elapsedTime = ( ( end - start ) * 1000 ) / freq;
    printf( "\nelapsed: %ld ms\n", elapsedTime );
#endif

	/* sum all */
	long sum = sumall(C);
	
	printf("sum = %e\n",sum);
	
	return 0;
}
