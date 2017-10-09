#!/bin/sh
g++ -O3 -march=native -fomit-frame-pointer -funroll-loops -fwhole-program card_original.cpp -o bin/card_original
#g++ -O3 -funroll-loops -fwhole-program card_original.cpp -S
g++ -O3 -march=native -fomit-frame-pointer -funroll-loops -fwhole-program card_raytracer.cpp -o bin/card_raytracer
#g++ -O3 -funroll-loops -fwhole-program card_raytracer.cpp -S
g++ -O3 -march=native -fomit-frame-pointer -funroll-loops -fwhole-program card_raytracer_vec.cpp -o bin/card_raytracer_vec
#g++ -O3 -funroll-loops -fwhole-program card_raytracer_vec.cpp -S
gcc -O3 -march=native -fomit-frame-pointer -funroll-loops -fwhole-program mandelbrot.c -o bin/mandelbrot
#gcc -O3 -funroll-loops -fwhole-program mandelbrot.c -S
javac ./Mandelbrot.java -d bin/
