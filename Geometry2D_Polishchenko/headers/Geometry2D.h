//
//  Geometry2D.h
//  Geometry2D_Polishchenko
//
//  Created by Roman Polishchenko on 5/26/19.
//  Copyright © 2019 Roman Polishchenko. All rights reserved.
//

#ifndef Geometry2D_h
#define Geometry2D_h

#include <stdio.h>
#include "common.h"

// ================= Point2D ================= //

typedef struct Point2D {
    DTYPE x;
    DTYPE y;
} Point2D;

// function to create a point with given coordinates
Point2D createPoint(DTYPE x, DTYPE y);

// ================= Segment2D ================= //

typedef struct Segment2D {
    Point2D a;
    Point2D b;
    DTYPE length;
} Segment2D;

// function to create a segment with given points
Segment2D createSegment(Point2D a, Point2D b);

// Scalar multiplication of two vectors formed by two segments
DTYPE multS(Segment2D s1, Segment2D s2);

// vector multiplication of two vectors formed by two segments
DTYPE mult(Segment2D s1, Segment2D s2);

// ================= Triangle2D ================= //

typedef struct Triangle2D {
    Point2D a;
    Point2D b;
    Point2D c;
    
} Triangle2D;

// function to create a triangle with given points
Triangle2D createTriangle(Point2D a, Point2D b, Point2D c);

// square of triangle [vector multiplication formula]
DTYPE square(Triangle2D t);

// perimeter of trianle [sum of lengths of sides]
DTYPE perimeter(Triangle2D t);

// incirle radius
DTYPE incircleRadius(Triangle2D t);

// excircle radius
DTYPE excircleRadius(Triangle2D t);

// mass center 
Point2D massCenter(Triangle2D t);

// functions to calculate radian measure of angles within vertices
DTYPE angleA(Triangle2D t);
DTYPE angleB(Triangle2D t);
DTYPE angleC(Triangle2D t);

// ================= Line2D ================= //

typedef struct Line2D {
    /* ax + by + c = 0
     */
    DTYPE a;
    DTYPE b;
    DTYPE c;
} Line2D;

Point2D instersectSS(Segment2D p1, Segment2D p2);
Point2D instersectLS(Line2D p1, Segment2D p2);
Point2D instersectLL(Line2D p1, Line2D p2);

#endif /* Geometry2D_h */
