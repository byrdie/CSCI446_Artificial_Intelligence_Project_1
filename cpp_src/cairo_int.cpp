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

void Cairo::draw_point(Point * pt, Color color) {
    float x = pt->x;
    float y = pt->y;

    cairo_set_line_width(cr, 5);
    cairo_arc(cr, x, y, 2, 0, 2 * M_PI);

    switch (color) {
        case red:
            cairo_set_source_rgb(cr, 1, 0, 0);
            break;
        case blue:
            cairo_set_source_rgb(cr, 0, 0, 1);
            break;
        case green:
            cairo_set_source_rgb(cr, 0, 1, 0);
            break;
        case purple:
            cairo_set_source_rgb(cr, 1, 0, 1);
            break;
        case black:
            cairo_set_source_rgb(cr, 0, 0, 0);
            break;
    }

    cairo_fill(cr);
}

void Cairo::draw_line(Graph_edge * edge, Color color) {
    float x0 = edge->start_point->pt->x;
    float y0 = edge->start_point->pt->y;
    float x1 = edge->end_point->pt->x;
    float y1 = edge->end_point->pt->y;
    

    switch (color) {
        case red:
            cairo_set_source_rgb(cr, 1, 0, 0);
            break;
        case blue:
            cairo_set_source_rgb(cr, 0, 0, 1);
            break;
        case green:
            cairo_set_source_rgb(cr, 0, 1, 0);
            break;
        case purple:
            cairo_set_source_rgb(cr, 1, 0, 1);
            break;
        case black:
            cairo_set_source_rgb(cr, 0, 0, 0);
            break;
    }

    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 0.1);
    cairo_move_to(cr, x0, y0);
    cairo_line_to(cr, x1, y1);
    cairo_stroke(cr);

}

void Cairo::draw_poly(Point * poly[], int N, Color color) {
    int i;
    float x0, y0, x1, y1;

    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_move_to(cr, poly[0]->x, poly[0]->y);
    cairo_set_line_width(cr, 1);

    for (i = 0; i < N - 1; i++) {
        x0 = poly[i]->x;
        y0 = poly[i]->y;
        x1 = poly[i + 1]->x;
        y1 = poly[i + 1]->y;
        cairo_line_to(cr, x1, y1);
    }

    cairo_close_path(cr);
    cairo_stroke_preserve(cr);

    switch (color) {
        case nocolor:
            cairo_set_source_rgb(cr, 0.2, 0.2, 0.2);
            break;
        case red:
            cairo_set_source_rgb(cr, 1, 0, 0);
            break;
        case blue:
            cairo_set_source_rgb(cr, 0, 0, 1);
            break;
        case green:
            cairo_set_source_rgb(cr, 0, 1, 0);
            break;
        case purple:
            cairo_set_source_rgb(cr, 1, 0, 1);
            break;
    }
    cairo_fill(cr);

}


