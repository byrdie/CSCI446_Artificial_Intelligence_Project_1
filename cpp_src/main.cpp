/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: byrdie
 *
 * Created on September 19, 2016, 10:37 AM
 */

#include <cstdlib>
#include <string>

#include "cairo_int.h"
#include "map_problem_gen.h"



using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    Cairo * cairo = new Cairo();
    
    problem_gen(10, WIDTH, cairo);
            
    cairo->finish();
    
    return 0;
}

