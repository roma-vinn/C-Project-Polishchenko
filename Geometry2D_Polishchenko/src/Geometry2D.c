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

Point2D incircleCenter(Triangle2D t) {
    return intersectLL(bisectorA(t), bisectorB(t));
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

Point2D excircleCenter(Triangle2D t) {
    DTYPE x1 = t.a.x, y1 = t.a.y,
    x2 = t.b.x, y2 = t.b.y,
    x3 = t.c.x, y3 = t.c.y;
    DTYPE x12 = x1 - x2, x23 = x2 - x3, x31 = x3 - x1,
    y12 = y1 - y2, y23 = y2 - y3, y31 = y3 - y1;
    DTYPE z1 = x1 * x1 + y1 * y1,
    z2 = x2 * x2 + y2 * y2,
    z3 = x3 * x3 + y3 * y3;
    DTYPE zx = y12 * z3 + y23 * z1 + y31 * z2,
    zy = x12 * z3 + x23 * z1 + x31 * z2,
    z = x12 * y31 - y12 * x31;
    return createPoint(-zx/(2*z), zy/(2*z));
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
    line.a = a.y - b.y;
    line.b = b.x - a.x;
    line.c = - line.a * a.x - line.b * a.y;
    
    return line;
}

ITYPE _pointSign(Line2D line, Point2D p) {
    return SIGN(line.a * p.x + line.b * p.y + line.c);
}

// auxilary function for searching determinant
DTYPE _det(DTYPE a11, DTYPE a12, DTYPE a21, DTYPE a22) {
    return a11 * a22 - a12 * a21;
}

Point2D intersectLL(Line2D p1, Line2D p2) {
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

Point2D intersectLS(Line2D p1, Segment2D p2) {
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
        return intersectLL(p1, createLine(p2.a, p2.b));
    } else {
        return createPoint(INF, -INF);
    }
}

// auxilary function to check if dot is on the segment
ITYPE _onSegment(Point2D p1, Segment2D p2) {
    if (PD_EQL(createSegment(p1, p2.a).length + createSegment(p1, p2.b).length,
               p2.length)) {
        return 1;
    } else {
        return 0;
    }
    
}

Point2D intersectSS(Segment2D p1, Segment2D p2) {
    // point of intersection of two lines build on given segments
    Point2D p = intersectLL(createLine(p1.a, p1.b), createLine(p2.a, p2.b));
    
    // if it's the only point
    if (p.x != INF) {
        // and if it belongs to both segments
        if (_onSegment(p, p1) && _onSegment(p, p2)) {
            return p;
        } else {
            // else - there isn't intersection
            return createPoint(INF, -INF);
        }
    } else {
        // if lines are parallel --> no common points
        if (p.y == -INF) {
            return createPoint(INF, -INF);
        } else {  // else if lines are equivalent
            // if all of the ends of any segment don't belong to the other one
            // --> no common points
            if (!_onSegment(p1.a, p2) && !_onSegment(p1.b, p2)
                && !_onSegment(p2.a, p1) && !_onSegment(p2.b, p1)) {
                return createPoint(INF, -INF);
            } else {
                Segment2D segm1 = createSegment(p1.a, p2.a),
                segm2 = createSegment(p1.a, p2.b),
                segm3 = createSegment(p1.b, p2.a),
                segm4 = createSegment(p1.b, p2.b);
                DTYPE max_len = MAX(MAX(segm1.length, segm2.length),
                                    MAX(segm3.length, segm4.length));
                // if sum of lengths == max len --> lay consistently on the line
                // --> one common point
                if (PD_EQL(p1.length + p2.length, max_len)) {
                    if (PD_EQL(segm1.length, 0) || PD_EQL(segm2.length, 0)) {
                        return p1.a;
                    } else {
                        return p1.b;
                    }
                } else {
                    // have common part --> infinite number of common points
                    return createPoint(INF, INF);
                }
            }
        }
    }
}

Line2D medianA(Triangle2D t) {
    return createLine(t.a, createPoint((t.b.x + t.c.x)/2, (t.b.y + t.c.y)/2));
}

Line2D medianB(Triangle2D t) {
    return createLine(t.b, createPoint((t.a.x + t.c.x)/2, (t.a.y + t.c.y)/2));
}

Line2D medianC(Triangle2D t) {
    return createLine(t.c, createPoint((t.b.x + t.a.x)/2, (t.b.y + t.a.y)/2));
}

Line2D bisectorA(Triangle2D t) {
    DTYPE ab_x = t.b.x - t.a.x,
    ab_y = t.b.y - t.a.y,
    ac_x = t.c.x - t.a.x,
    ac_y = t.c.y - t.a.y;
    DTYPE ab_len = sqrt(pow(ab_x, 2) + pow(ab_y, 2)),
    ac_len = sqrt(pow(ac_x, 2) + pow(ac_y, 2));
    ab_x /= ab_len;
    ab_y /= ab_len;
    ac_x /= ac_len;
    ac_y /= ac_len;
    DTYPE bisect_x = ab_x + ac_x,
    bisect_y = ab_y + ac_y;
    return createLine(t.a, createPoint(t.a.x + bisect_x, t.a.y + bisect_y));
}

Line2D bisectorB(Triangle2D t) {
    DTYPE ba_x = t.a.x - t.b.x,
    ba_y = t.a.y - t.b.y,
    bc_x = t.c.x - t.b.x,
    bc_y = t.c.y - t.b.y;
    DTYPE ba_len = sqrt(pow(ba_x, 2) + pow(ba_y, 2)),
    bc_len = sqrt(pow(bc_x, 2) + pow(bc_y, 2));
    ba_x /= ba_len;
    ba_y /= ba_len;
    bc_x /= bc_len;
    bc_y /= bc_len;
    DTYPE bisect_x = ba_x + bc_x,
    bisect_y = ba_y + bc_y;
    return createLine(t.b, createPoint(t.b.x + bisect_x, t.b.y + bisect_y));
}

Line2D bisectorC(Triangle2D t) {
    DTYPE cb_x = t.b.x - t.c.x,
    cb_y = t.b.y - t.c.y,
    ca_x = t.a.x - t.c.x,
    ca_y = t.a.y - t.c.y;
    DTYPE cb_len = sqrt(pow(cb_x, 2) + pow(cb_y, 2)),
    ca_len = sqrt(pow(ca_x, 2) + pow(ca_y, 2));
    cb_x /= cb_len;
    cb_y /= cb_len;
    ca_x /= ca_len;
    ca_y /= ca_len;
    DTYPE bisect_x = cb_x + ca_x,
    bisect_y = cb_y + ca_y;
    return createLine(t.c, createPoint(t.c.x + bisect_x, t.c.y + bisect_y));
}

Line2D altitudeA(Triangle2D t) {
    Line2D op_side = createLine(t.b, t.c);
    return createLine(t.a, createPoint(t.a.x + op_side.a, t.a.y + op_side.b));
}

Line2D altitudeB(Triangle2D t) {
    Line2D op_side = createLine(t.a, t.c);
    return createLine(t.b, createPoint(t.b.x + op_side.a, t.b.y + op_side.b));
}

Line2D altitudeC(Triangle2D t) {
    Line2D op_side = createLine(t.b, t.a);
    return createLine(t.c, createPoint(t.c.x + op_side.a, t.c.y + op_side.b));
}
