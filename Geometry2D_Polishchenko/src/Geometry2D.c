//
//  Geometry2D.c
//  Geometry2D_Polishchenko
//
//  Created by Roman Polishchenko on 5/26/19.
//  Copyright © 2019 Roman Polishchenko. All rights reserved.
//

#include "Geometry2D.h"

// ================= Point2D ================= //

Point2D createPoint(DTYPE x, DTYPE y) {
    Point2D point;
    point.x = x;
    point.y = y;
    return point;
}

// ================= Segment2D ================= //

Segment2D createSegment(Point2D a, Point2D b) {
    Segment2D segm;
    segm.a = a;
    segm.b = b;
    segm.length = sqrt(pow(b.x-a.x, 2) + pow(b.y-a.y, 2));
    return segm;
}

// consider that point 'a' is start, 'b' - is end
DTYPE multS(Segment2D s1, Segment2D s2) {
    // segment s1 -> vector (x1, y1)
    DTYPE x1 = s1.b.x - s1.a.x;
    DTYPE y1 = s1.b.y - s1.a.y;
    
    // segment s2 -> vector (x2, y2)
    DTYPE x2 = s2.b.x - s2.a.x;
    DTYPE y2 = s2.b.y - s2.a.y;
    
    return x1 * x2 + y1 * y2;
}

// consider that point 'a' is start, 'b' - is end
DTYPE mult(Segment2D s1, Segment2D s2) {
    // segment s1 -> vector (x1, y1)
    DTYPE x1 = s1.b.x - s1.a.x;
    DTYPE y1 = s1.b.y - s1.a.y;
    
    // segment s2 -> vector (x2, y2)
    DTYPE x2 = s2.b.x - s2.a.x;
    DTYPE y2 = s2.b.y - s2.a.y;
    
    return x1 * y2 - x2 * y1;
}

// ================= Triangle2D ================= //

Triangle2D createTriangle(Point2D a, Point2D b, Point2D c) {
    Triangle2D tr;
    tr.a = a;
    tr.b = b;
    tr.c = c;
    return tr;
}

DTYPE square(Triangle2D t) {
    Segment2D ab = createSegment(t.a, t.b),
    ac = createSegment(t.a, t.c);
    
    return 0.5 * mult(ab, ac);
}

DTYPE perimeter(Triangle2D t) {
    Segment2D ab = createSegment(t.a, t.b),
    ac = createSegment(t.a, t.c),
    bc = createSegment(t.b, t.c);
    
    return ab.length + ac.length + bc.length;
}

DTYPE incircleRadius(Triangle2D t) {
    // radius = S / p = 2 * S / P
    // where S - square, P - perimeter, p - half of perimeter
    return 2 * square(t) / perimeter(t);
}

DTYPE excircleRadius(Triangle2D t) {
    // sides of triangle
    Segment2D ab = createSegment(t.a, t.b),
    ac = createSegment(t.a, t.c),
    bc = createSegment(t.b, t.c);
    
    // half of perimeter
    DTYPE p = perimeter(t) / 2,
    a = ab.length,
    b = bc.length,
    c = ac.length;
    
    return (a * b * c) / (4 * sqrt(p * (p-a) * (p-b) * (p-c)));
}

// ================= Line2D ================= //


