#ifndef UTILITY_H
#define UTILITY_H

#include <math.h>
#include <Arduino.h>
//https://stackoverflow.com/a/36209005 
//based on Agoston's Computer Graphics and Geometric Modeling: Implementation and Algorithms p. 304, 
//with H ∈ [0, 360] and S,V ∈ [0, 1].

typedef struct {
    double r;       // ∈ [0, 1]
    double g;       // ∈ [0, 1]
    double b;       // ∈ [0, 1]
} rgb;

typedef struct {
    double h;       // ∈ [0, 360]
    double s;       // ∈ [0, 1]
    double v;       // ∈ [0, 1]
} hsv;

extern int iHSV[3];

rgb hsv2rgb(hsv HSV);
hsv MQTTThingHSVScale(String hsvStr);
#endif