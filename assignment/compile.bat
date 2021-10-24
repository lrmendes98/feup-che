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