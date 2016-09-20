/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cairo_int.cpp
 * Author: byrdie
 *
 * Created on September 19, 2016, 11:17 AM
 */

#include <cstdlib>
#include "cairo_int.h"

using namespace std;

Cairo::Cairo() {
    surface = cairo_pdf_surface_create("test.pdf", WIDTH, HEIGHT);
    cr = cairo_create(surface);
}

void Cairo::finish() {
    cairo_show_page(cr);
    cairo_destroy(cr);
    cairo_surface_flush(surface);
    cairo_surface_destroy(surface);
}

void Cairo::draw_point(Point * pt){
    float x = pt->x;
    float y = pt->y;
    
    cairo_set_line_width(cr, 5);
    cairo_arc(cr, x,y, 1, 0,2 * M_PI);
    cairo_fill(cr);
}

void Cairo::draw_line(Graph_edge * edge){
    
    float x0 = edge->start_point->pt->x;
    float y0 = edge->start_point->pt->y;
    float x1 = edge->end_point->pt->x;
    float y1 = edge->end_point->pt->y;
    
    cairo_set_line_width(cr, 0.5);
    cairo_move_to(cr, x0, y0);
    cairo_line_to(cr, x1, y1);
    cairo_stroke(cr);
    
}


