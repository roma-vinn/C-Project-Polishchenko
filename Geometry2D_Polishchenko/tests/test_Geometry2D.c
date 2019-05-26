//
//  test_Geometry2D.c
//  Geometry2D_Polishchenko
//
//  Created by Roman Polishchenko on 5/26/19.
//  Copyright © 2019 Roman Polishchenko. All rights reserved.
//

#include "../headers/test_Geometry2D.h"

int test_Geometry2D() {
    Point2D p0 = createPoint(0, 0);
    Point2D p1 = createPoint(4, 0);
    Point2D p2 = createPoint(0, 3);
    Point2D p3 = createPoint(0, -3);
    
    Segment2D segm01 = createSegment(p0, p1);
    Segment2D segm02 = createSegment(p0, p2);
    
    // test if the length calculating correctly
    if (!PD_EQL(segm01.length, 4) || !PD_EQL(segm02.length, 3)) {
        return 1;
    }
    
    // test if multS calculating correctly
    if (!PD_EQL(multS(segm01, segm02), 0)) {
        return 1;
    }
    
    // test if mult calculating correctly
    if (!PD_EQL(mult(segm01, segm02), 12)) {
        return 1;
    }
    
    Triangle2D t = createTriangle(p0, p1, p2);
   
    // test if perimeter calculating correctly
    if (!PD_EQL(perimeter(t), 12)) {
        return 1;
    }
    
    // test if square calculating correctly
    if (!PD_EQL(square(t), 6)) {
        return 1;
    }
    
    // test if incirlce radius calculating correctly
    if (!PD_EQL(incircleRadius(t), 1)) {
        return 1;
    }
    
    // test if excirlce radius calculating correctly
    if (!PD_EQL(excircleRadius(t), 2.5)) {
        return 1;
    }
    
    // test if mass centre point calculating correctly
    Point2D c = massCenter(t);
    if (c.x != 4.0/3.0 || c.y != 1) {
        return 1;
    }
    
    // test if angles calculating correctly
    if (!PD_EQL(angleA(t), M_PI/2.0)) {
        return 1;
    }
    
    // test pointSign function
    Line2D line = createLine(p0, p1);
    if (_pointSign(line, p1) != 0 || _pointSign(line, p2) == _pointSign(line, p3)){
        return 1;
    }
    
    // test instersectLL
    Line2D line1 = createLine(createPoint(0, 0), createPoint(1, 0)),
    line2 = createLine(createPoint(0, 1), createPoint(1, 1)),
    line3 = createLine(createPoint(0, 0), createPoint(0, 1)),
    line4 = createLine(createPoint(1, 1), createPoint(5, 5)),
    line5 = createLine(createPoint(1, 5), createPoint(5, 1));
    if ( intersectLL(line1, line2).y != -INF  // parallel case
        || intersectLL(line1, line1).y != INF  // equivalent
        || (intersectLL(line1, line3).y != 0
            && intersectLL(line1, line3).x != 0)
        || (intersectLL(line4, line5).y != 3
            && intersectLL(line4, line5).x != 3)) {
        return 1;
    }
    
    // test instersectLS
    if ( intersectLS(line1, segm01).y != INF
        || (intersectLS(line3, segm01).x != 0
            && intersectLS(line3, segm01).y != 0)
        || intersectLS(line2, segm01).y != -INF) {
        return 1;
    }
    
    // test intersectSS [all variants]
    Point2D
    ip1 = intersectSS(createSegment(createPoint(1, 1), createPoint(5, 1)),
                      createSegment(createPoint(1, 5), createPoint(5, 5))),
    ip2 = intersectSS(createSegment(createPoint(1, 1), createPoint(5, 5)),
                      createSegment(createPoint(1, 5), createPoint(5, 1))),
    ip3 = intersectSS(createSegment(createPoint(1, 1), createPoint(3, 3)),
                      createSegment(createPoint(3, 3), createPoint(5, 5))),
    ip4 = intersectSS(createSegment(createPoint(1, 1), createPoint(5, 1)),
                      createSegment(createPoint(3, 1), createPoint(5, 1))),
    ip5 = intersectSS(createSegment(createPoint(1, 1), createPoint(5, 1)),
                      createSegment(createPoint(3, 1), createPoint(7, 1)));
    if (ip1.y != -INF || !(PD_EQL(ip2.x, 3) && PD_EQL(ip2.y, 3))
        || !(PD_EQL(ip3.x, 3) && PD_EQL(ip3.y, 3))
        || ip4.y != INF
        || ip5.y != INF) {
        return 1;
    }
    
    // test medianA [same as medianB and medianC]
    Line2D ma = medianA(t);
    if (_pointSign(ma, createPoint(2, 3.0/2.0)) != 0) {
        return 1;
    }
    
    // test bisectorA [same as bisectorB and bisectorC]
    Line2D ba = bisectorA(t);
    if (_pointSign(ba, createPoint(1, 1)) != 0) {
        return 1;
    }
    
    return 0;
}
