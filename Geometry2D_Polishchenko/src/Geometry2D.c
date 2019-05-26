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

Point2D massCenter(Triangle2D t) {
    return createPoint((t.a.x + t.b.x + t.c.x)/3, (t.a.y + t.b.y + t.c.y)/3);
}

DTYPE angleA(Triangle2D t) {
    // sides of triangle
    Segment2D ab = createSegment(t.a, t.b),
    ac = createSegment(t.a, t.c);
    
    return acos( multS(ab, ac) / (ab.length * ac.length) );
}

DTYPE angleB(Triangle2D t) {
    // sides of triangle
    Segment2D ba = createSegment(t.b, t.a),
    bc = createSegment(t.b, t.c);
    
    return acos( multS(ba, bc) / (ba.length * bc.length) );
}

DTYPE angleC(Triangle2D t) {
    // sides of triangle
    Segment2D ca = createSegment(t.c, t.a),
    cb = createSegment(t.c, t.b);
    
    return acos( multS(ca, cb) / (ca.length * cb.length) );
}

// ================= Line2D ================= //

Line2D createLine(Point2D a, Point2D b) {
    Line2D line;
    line.a = b.y - a.y;
    line.b = a.x - b.x;
    line.c = a.x * b.y - a.y * b.x;
    
    return line;
}

ITYPE _pointSign(Line2D line, Point2D p) {
    return SIGN(line.a * p.x + line.b * p.y + line.c);
}

// auxilary function for searching determinant
DTYPE _det(DTYPE a11, DTYPE a12, DTYPE a21, DTYPE a22) {
    return a11 * a22 - a12 * a21;
}

Point2D instersectLL(Line2D p1, Line2D p2) {
    // { a1*x + b1*y = -c1,
    // { a2*x + b2*y = -c2, - linear system
    // if det == 0 --> either parallel or equivalent
    if (PD_EQL(_det(p1.a, p1.b, p2.a, p2.b), 0)) {
        // equivalent
        if ( PD_EQL(_det(p1.a, p1.c, p2.a, p2.c), 0)
            && PD_EQL(_det(p1.b, p1.c, p2.b, p2.c), 0) ) {
            return createPoint(INF, INF);
        } else {
            // parallel
            return createPoint(INF, -INF);
        }
    } else {
        // intersection exists
        DTYPE x = - _det(p1.c, p1.b, p2.c, p2.b) / _det(p1.a, p1.b, p2.a, p2.b);
        DTYPE y = - _det(p1.a, p1.c, p2.a, p2.c) / _det(p1.a, p1.b, p2.a, p2.b);
        return createPoint(x, y);
    }
}

Point2D instersectLS(Line2D p1, Segment2D p2) {
    // if both ends of segment are on the line - infinite number of dots
    if (_pointSign(p1, p2.a) == 0 && _pointSign(p1, p2.b) == 0) {
        return createPoint(INF, INF);
    }
    
    // if one of the end of segment is on the line - return it
    if (_pointSign(p1, p2.a) == 0) {
        return p2.a;
    }
    if (_pointSign(p1, p2.b) == 0) {
        return p2.b;
    }
    
    // if ends of segments are on different sides of the line
    if (_pointSign(p1, p2.a) != _pointSign(p1, p2.b)) {
        return instersectLL(p1, createLine(p2.a, p2.b));
    } else {
        return createPoint(INF, -INF);
    }
}

