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

// function to create a point with 2 given coordinates
Point2D createPoint(DTYPE x, DTYPE y);

// ================= Segment2D ================= //

typedef struct Segment2D {
    Point2D a;
    Point2D b;
    DTYPE length;
} Segment2D;

// function to create a segment with 2 given points
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

// function to create a triangle with 3 given points
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

// function to create a line within 2 given points
Line2D createLine(Point2D a, Point2D b);

// auxilary function to find sign of expression (a * p.x + b * p.y + c)
// could be -1, 0 (if point on the line), 1
ITYPE _pointSign(Line2D line, Point2D p);

// functions to check wether two objects have intersection
// return: point of intersection if it exists,
//         Point2D(INF, INF) - if lines are equivalent,
//         Point2D(INF, -INF) - if lines ara parallel.
Point2D intersectLL(Line2D p1, Line2D p2);
Point2D intersectLS(Line2D p1, Segment2D p2);
Point2D intersectSS(Segment2D p1, Segment2D p2);

// functions to find median of triangle from particular vertex
Line2D medianA(Triangle2D t);
Line2D medianB(Triangle2D t);
Line2D medianC(Triangle2D t);

// functions to find bisectors of triangle from particular vertex
Line2D bisectorA(Triangle2D t);
Line2D bisectorB(Triangle2D t);
Line2D bisectorC(Triangle2D t);

#endif /* Geometry2D_h */
