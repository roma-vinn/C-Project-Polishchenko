//
//  test_Geometry2D.c
//  Geometry2D_Polishchenko
//
//  Created by Roman Polishchenko on 5/26/19.
//  Copyright © 2019 Roman Polishchenko. All rights reserved.
//

#include "../headers/test_Geometry2D.h"

int test_Geometry2D() {
    Point2D *p0 = createPoint(0, 0);
    Point2D *p1 = createPoint(4, 0);
    Point2D *p2 = createPoint(0, 3);
    Point2D *p3 = createPoint(0, -3);

    Segment2D *segm01 = createSegment(p0, p1);
    Segment2D *segm02 = createSegment(p0, p2);

    // test if the length calculating correctly
    if (!PD_EQL(segm01->length, 4) || !PD_EQL(segm02->length, 3)) {
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

    Triangle2D *t = createTriangle(p0, p1, p2);

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
    Point2D *c = massCenter(t);
    if (c->x != 4.0/3.0 || c->y != 1) {
        return 1;
    }

    freePoint(c);
    
    // test if angles calculating correctly
    if (!PD_EQL(angleA(t), M_PI/2.0)) {
        return 1;
    }

    // test pointSign function
    Line2D *line = createLine(p0, p1);
    if (_pointSign(line, p1) != 0 || _pointSign(line, p2) == _pointSign(line, p3)){
        return 1;
    }

    freeLine(line);
    
    // test instersectLL [all variants]
    Point2D *tmp_00 = createPoint(0, 0),
    *tmp_10 = createPoint(1, 0),
    *tmp_01 = createPoint(0, 1),
    *tmp_11 = createPoint(1, 1),
    *tmp_55 = createPoint(5, 5),
    *tmp_15 = createPoint(1, 5),
    *tmp_51 = createPoint(5, 1),
    *tmp_31 = createPoint(3, 1),
    *tmp_71 = createPoint(7, 1),
    *tmp_33 = createPoint(3, 3);
    
    Line2D *line1 = createLine(tmp_00, tmp_10),
    *line2 = createLine(tmp_01, tmp_11),
    *line3 = createLine(tmp_00, tmp_01),
    *line4 = createLine(tmp_11, tmp_55),
    *line5 = createLine(tmp_15, tmp_51);
    
    Point2D *inter12 = intersectLL(line1, line2),
    *inter11 = intersectLL(line1, line1),
    *inter13 = intersectLL(line1, line3),
    *inter45 = intersectLL(line4, line5);
                            
    if ( inter12->y != -INF  // parallel case
        || inter11->y != INF  // equivalent
        || (inter13->y != 0
            && inter13->x != 0)
        || (inter45->y != 3
            && inter45->x != 3)) {
        return 1;
    }
    freePoint(inter11); freePoint(inter12);
    freePoint(inter13); freePoint(inter45);
    
    // test instersectLS [all variants]
    Point2D *inter1 = intersectLS(line1, segm01),
    *inter2 = intersectLS(line2, segm01),
    *inter3 = intersectLS(line3, segm01);
    if ( inter1->y != INF
        || (inter3->x != 0
            && inter3->y != 0)
        || inter2->y != -INF) {
        return 1;
    }

    freePoint(inter1); freePoint(inter2); freePoint(inter3);
    
    // test intersectSS [all variants]
    Segment2D *segm_1151 = createSegment(tmp_11, tmp_51),
    *segm_1555 = createSegment(tmp_15, tmp_55),
    *segm_1155 = createSegment(tmp_11, tmp_55),
    *segm_1551 = createSegment(tmp_15, tmp_51),
    *segm_1133 = createSegment(tmp_11, tmp_33),
    *segm_3355 = createSegment(tmp_33, tmp_55),
    *segm_3151 = createSegment(tmp_31, tmp_51),
    *segm_3171 = createSegment(tmp_31, tmp_71);
    
    
    Point2D *ip1 = intersectSS(segm_1151,
                               segm_1555),
    *ip2 = intersectSS(segm_1155,
                       segm_1551),
    *ip3 = intersectSS(segm_1133,
                       segm_3355),
    *ip4 = intersectSS(segm_1151,
                       segm_3151),
    *ip5 = intersectSS(segm_1151,
                       segm_3171);
    if (ip1->y != -INF || !(PD_EQL(ip2->x, 3) && PD_EQL(ip2->y, 3))
        || !(PD_EQL(ip3->x, 3) && PD_EQL(ip3->y, 3))
        || ip4->y != INF
        || ip5->y != INF) {
        freePoint(ip1); freePoint(ip2); freePoint(ip3);
        freePoint(ip4); freePoint(ip5);
        return 1;
    }
    
    freePoint(ip1); freePoint(ip2); freePoint(ip3);
    freePoint(ip4); freePoint(ip5);
    
    // test medianA [same as medianB and medianC]
    Line2D *ma = medianA(t);
    Point2D *tmp = createPoint(2, 3.0/2.0);
    if (_pointSign(ma, tmp) != 0) {
        freePoint(tmp); freeLine(ma);
        return 1;
    }
    freePoint(tmp); freeLine(ma);

    // test bisectorA [same as bisectorB and bisectorC]
    Line2D *ba = bisectorA(t);
    if (_pointSign(ba, tmp_11) != 0) {
        freeLine(ba);
        return 1;
    }
    freeLine(ba);

    // test altitudeB [same as altitudeA and altitudeC]
    Line2D *altitude_b = altitudeB(t);
    Point2D *tmp_110 = createPoint(11, 0);
    if (_pointSign(altitude_b, tmp_110) != 0) {
        freeLine(altitude_b); freePoint(tmp_110);
        return 1;
    }
    freeLine(altitude_b); freePoint(tmp_110);
    
    // test incircleCenter
    Triangle2D *test_t = createTriangle(tmp_00,
                                        tmp_01,
                                        tmp_10);

    Point2D* inC = incircleCenter(test_t);
    if (!PD_EQL(inC->x, 0.29289321881345248) || !PD_EQL(inC->y, 0.29289321881345248)) {
        freeTriangle(test_t);
        return 1;
    }
    free(inC);

    // test excircleCenter
    Point2D *exC = excircleCenter(t);
    if (exC->x != 2 || exC->y != 1.5 ) {
        return 1;
    }
    freePoint(exC);

    // test figuresSquares
    DTYPE s1 = 0, s2 = 0;
    
    Point2D *tmp_20 = createPoint(2, 0),
    *tmp_22 = createPoint(2, 2);
    
    Line2D *med_a = medianA(test_t),
    *alt_b = altitudeB(test_t),
    *tmp_line = createLine(tmp_20, tmp_22);
    
    if (figuresSquares(test_t, med_a, &s1, &s2) || !PD_EQL(s1, s2)) {
        freePoint(tmp_20); freePoint(tmp_22);
        freeLine(med_a); freeLine(alt_b); freeLine(tmp_line);
        return 1;
    }
    if (!figuresSquares(test_t, alt_b, &s1, &s2)) {
        freePoint(tmp_20); freePoint(tmp_22);
        freeLine(med_a); freeLine(alt_b); freeLine(tmp_line);
        return 1;
    }
    if (!figuresSquares(test_t, tmp_line, &s1, &s2)) {
        freePoint(tmp_20); freePoint(tmp_22);
        freeLine(med_a); freeLine(alt_b); freeLine(tmp_line);
        return 1;
    }
    
    // TODO fix memory leak when return 1
    freePoint(p0); freePoint(p1); freePoint(p2); freePoint(p3);
    
    freePoint(tmp_00); freePoint(tmp_10); freePoint(tmp_01);
    freePoint(tmp_11); freePoint(tmp_55); freePoint(tmp_15);
    freePoint(tmp_51); freePoint(tmp_33); freePoint(tmp_31);
    freePoint(tmp_71); freePoint(tmp_20); freePoint(tmp_22);
    
    freeSegment(segm01); freeSegment(segm02);
    
    freeSegment(segm_1151); freeSegment(segm_1555);
    freeSegment(segm_1155); freeSegment(segm_1551);
    freeSegment(segm_1133); freeSegment(segm_3355);
    freeSegment(segm_3151); freeSegment(segm_3171);
    
    freeTriangle(t); freeTriangle(test_t);

    
    freeLine(line1); freeLine(line2); freeLine(line3);
    freeLine(line4); freeLine(line5);
    
    freeLine(med_a); freeLine(alt_b); freeLine(tmp_line);
    

    return 0;
}
