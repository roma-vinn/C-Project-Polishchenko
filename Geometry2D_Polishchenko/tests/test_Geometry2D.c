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

    if (!PD_EQL(segm01.length, 4) || !PD_EQL(segm02.length, 3)) {
        return 1;
    }
    
    Triangle2D t = createTriangle(p0, p1, p2);
   
    if (!PD_EQL(perimeter(t), 12)) {
        return 1;
    }

    if (!PD_EQL(square(t), 6)) {
        return 1;
    }
    
    return 0;
}
