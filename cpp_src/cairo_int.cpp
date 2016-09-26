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

Cairo::Cairo(char * filename) {

    surface = cairo_pdf_surface_create(filename, WIDTH, HEIGHT);


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
    cairo_arc(cr, x, y, 5, 0, 2 * M_PI);

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

void Cairo::draw_poly(Point * poly[], int N, Color color, bool highlighted) {
    int i;
    float x0, y0, x1, y1;

    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_move_to(cr, poly[0]->x, poly[0]->y);
    cairo_set_line_width(cr, 2);

//    if (highlighted) {
//        cairo_set_line_width(cr, 8);
//        cairo_set_source_rgb(cr, 0, 0, 0);
//    }

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
            cairo_set_source_rgb(cr, hf(0xFF), hf(0x00), hf(0x00));
            break;
        case blue:
            cairo_set_source_rgb(cr, hf(0x00), hf(0x47), hf(0xAB));
            break;
        case green:
            cairo_set_source_rgb(cr, hf(0x00), hf(0xB5), hf(0x00));
            break;
        case purple:
            cairo_set_source_rgb(cr, hf(0xFF), hf(0x00), hf(0xAB));
            break;
    }
    cairo_fill(cr);

}

void Cairo::draw_poly(Point * poly[], int N, int color, bool highlighted) {
    int i;
    float x0, y0, x1, y1;

    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_move_to(cr, poly[0]->x, poly[0]->y);
    cairo_set_line_width(cr, 2);
    
    if (highlighted) {
        cairo_set_line_width(cr, 8);
        cairo_set_source_rgb(cr, 0, 0, 0);
    }

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
        case RGBP:
            cairo_set_source_rgb(cr, hf(0x80), hf(0x3F), hf(0x56));
            break;
        case RGB:
            cairo_set_source_rgb(cr, hf(0x55), hf(0x54), hf(0x39));
            break;
        case GBP:
            cairo_set_source_rgb(cr, hf(0x55), hf(0x54), hf(0x72));
            break;
        case RBP:
            cairo_set_source_rgb(cr, hf(0xAA), hf(0x18), hf(0x72));
            break;
        case RGP:
            cairo_set_source_rgb(cr, hf(0xAA), hf(0x3C), hf(0x39));
            break;
        case RG:
            cairo_set_source_rgb(cr, hf(0x80), hf(0x5B), hf(0x00));
            break;
        case GB:
            cairo_set_source_rgb(cr, hf(0x00), hf(0x7E), hf(0x56));
            break;
        case BP:
            cairo_set_source_rgb(cr, hf(0x80), hf(0x24), hf(0xAB));
            break;
        case RB:
            cairo_set_source_rgb(cr, hf(0x80), hf(0x24), hf(0x56));
            break;
        case GP:
            cairo_set_source_rgb(cr, hf(0x80), hf(0x5B), hf(0x56));
            break;
        case RP:
            cairo_set_source_rgb(cr, hf(0xFF), hf(0x00), hf(0x56));
            break;
        case RED:
            cairo_set_source_rgb(cr, hf(0xFF), hf(0x00), hf(0x00));
            break;
        case BLUE:
            cairo_set_source_rgb(cr, hf(0x00), hf(0x47), hf(0xAB));
            break;
        case GREEN:
            cairo_set_source_rgb(cr, hf(0x00), hf(0xB5), hf(0x00));
            break;
        case PURPLE:
            cairo_set_source_rgb(cr, hf(0xFF), hf(0x00), hf(0xAB));
            break;
        default:
            cout << hex << color << endl;
            cairo_set_source_rgb(cr, 0, 0, 0);

    }
    cairo_fill(cr);

}

float hf(int hex) {
    return (float) hex / 0xFF;
}

void Cairo::draw_label(char * l_label, char * r_label) {
    cairo_text_extents_t te;
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_select_font_face(cr, "Georgia",
            CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 1.2);
    cairo_text_extents(cr, "a", &te);
    cairo_move_to(cr, 0, 0);
    cairo_show_text(cr, l_label);
//    cairo_move_to(cr, te.width, 0);
//    cairo_show_text(cr, l_label);
}