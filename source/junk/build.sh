#!/bin/sh
g++ -O3 -funroll-loops card_original.cpp -o card_original
g++ -O3 -funroll-loops card_original.cpp -S
g++ -O3 -funroll-loops card_raytracer.cpp -o card_raytracer
g++ -O3 -funroll-loops card_raytracer.cpp -S
g++ -O3 -funroll-loops card_raytracer_noref.cpp -o card_raytracer_noref
g++ -O3 -funroll-loops card_raytracer_noref.cpp -S
