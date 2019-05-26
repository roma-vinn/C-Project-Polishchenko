//
//  test_Geometry2D.c
//  Geometry2D_Polishchenko
//
//  Created by Roman Polishchenko on 5/26/19.
//  Copyright © 2019 Roman Polishchenko. All rights reserved.
//

#include "../headers/test_Geometry2D.h"

int test_Geometry2D() {
    DTYPE x0 = 0;
    DTYPE y0 = 0;
    
    DTYPE x1 = 4;
    DTYPE y1 = 0;
    
    DTYPE x2 = 0;
    DTYPE y2 = 3;
    
    Point2D p0 = createPoint(x0, y0);
    Point2D p1 = createPoint(x1, y1);
    Point2D p2 = createPoint(x2, y2);
    
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
    
    return 0;
}
