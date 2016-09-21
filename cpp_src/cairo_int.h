/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cairo_int.h
 * Author: byrdie
 *
 * Created on September 19, 2016, 11:17 AM
 */



#ifndef CAIRO_INT_H
#define CAIRO_INT_H

#include <cairo/cairo.h>
#include <cairo/cairo-pdf.h>
#include <cairo/cairo-ps.h>
#include <math.h>
#include "map_data_types.h"

#define WIDTH 1000
#define HEIGHT 1000

class Graph_point;
class Map;
class Graph_edge;
class Point;

class Cairo{
public:
    cairo_surface_t * surface;
    cairo_t * cr;
    Cairo();
    void draw_point(Point * pt, Color color);
    void draw_line(Graph_edge * edge, Color color);
    void finish();
    void draw_poly(Point * poly[], int N, Color color);
    void draw_poly(Point * poly[], int N, int color);
};


#endif /* CAIRO_INT_H */

