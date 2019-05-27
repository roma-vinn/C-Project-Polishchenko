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
Point2D *createPoint(DTYPE x, DTYPE y);

// function to free memory for Point
void freePoint(Point2D *point);

// ================= Segment2D ================= //

typedef struct Segment2D {
    Point2D *a;
    Point2D *b;
    DTYPE length;
} Segment2D;

// function to create a segment with 2 given points
Segment2D *createSegment(Point2D *a, Point2D *b);

// function to free memory after using Segment2D
void freeSegment(Segment2D *segment);

// Scalar multiplication of two vectors formed by two segments
DTYPE multS(Segment2D *s1, Segment2D *s2);

// vector multiplication of two vectors formed by two segments
DTYPE mult(Segment2D *s1, Segment2D *s2);

// ================= Triangle2D ================= //

typedef struct Triangle2D {
    Point2D *a;
    Point2D *b;
    Point2D *c;

} Triangle2D;

// function to create a triangle with 3 given points
Triangle2D *createTriangle(Point2D *a, Point2D *b, Point2D *c);

// function to free memory for triangle
void freeTriangle(Triangle2D *t);

// square of triangle [vector multiplication formula]
DTYPE square(Triangle2D *t);

// perimeter of trianle [sum of lengths of sides]
DTYPE perimeter(Triangle2D *t);

// incirle radius and center
DTYPE incircleRadius(Triangle2D *t);
Point2D *incircleCenter(Triangle2D *t);

// excircle radius and center
DTYPE excircleRadius(Triangle2D *t);
Point2D *excircleCenter(Triangle2D *t);

// mass center
Point2D *massCenter(Triangle2D *t);

// functions to calculate radian measure of angles within vertices
DTYPE angleA(Triangle2D *t);
DTYPE angleB(Triangle2D *t);
DTYPE angleC(Triangle2D *t);

// ================= Line2D ================= //

typedef struct Line2D {
    /* ax + by + c = 0
     */
    DTYPE a;
    DTYPE b;
    DTYPE c;
} Line2D;

// function to create a line within 2 given points
Line2D *createLine(Point2D *a, Point2D *b);

// function to free memory for Line
void freeLine(Line2D *line);

// auxilary function to find sign of expression (a * p.x + b * p.y + c)
// could be -1, 0 (if point on the line), 1
ITYPE _pointSign(Line2D *line, Point2D *p);

// functions to check wether two objects have intersection
// return: point of intersection if it exists,
//         Point2D(INF, INF) - if lines are equivalent,
//         Point2D(INF, -INF) - if lines ara parallel.
Point2D *intersectLL(Line2D *p1, Line2D *p2);
Point2D *intersectLS(Line2D *p1, Segment2D *p2);
Point2D *intersectSS(Segment2D *p1, Segment2D *p2);

// functions to find median of triangle from particular vertex
Line2D *medianA(Triangle2D *t);
Line2D *medianB(Triangle2D *t);
Line2D *medianC(Triangle2D *t);

// functions to find bisectors of triangle from particular vertex
/* algo: calculate normed vectors of adjacent sides, calculate
 their sum and build line that corresponds this vector
 */
Line2D *bisectorA(Triangle2D *t);
Line2D *bisectorB(Triangle2D *t);
Line2D *bisectorC(Triangle2D *t);

// functions to find altitudes of triangle from particular vertex
/* algo: line perpendicular to Ax + By + c = 0 has directional vector (A, B)
 */
Line2D *altitudeA(Triangle2D *t);
Line2D *altitudeB(Triangle2D *t);
Line2D *altitudeC(Triangle2D *t);

// squares of figures we've got by deviding triangle with Line
/*
 @param triangle: Triangle
 @param line: Line
 @param s1: square of first figure
 @param s2: square of second figure
 return 0 if line intersect triangle,
        1 - if it isn't
 */
ITYPE figuresSquares(Triangle2D *triangle, Line2D *line, DTYPE *s1, DTYPE *s2);

#endif /* Geometry2D_h */
