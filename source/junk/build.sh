#!/bin/sh
g++ -O3 -funroll-loops -fwhole-program card_original.cpp -o card_original
g++ -O3 -funroll-loops -fwhole-program card_original.cpp -S
g++ -O3 -funroll-loops -fwhole-program card_raytracer.cpp -o card_raytracer
g++ -O3 -funroll-loops -fwhole-program card_raytracer.cpp -S
g++ -O3 -funroll-loops -fwhole-program card_raytracer_vec.cpp -o card_raytracer_noref_vec
g++ -O3 -funroll-loops -fwhole-program card_raytracer_vec.cpp -S
