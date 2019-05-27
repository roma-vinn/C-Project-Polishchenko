//
//  io.h
//  Geometry2D_Polishchenko
//
//  Created by Roman Polishchenko on 5/27/19.
//  Copyright © 2019 Roman Polishchenko. All rights reserved.
//

#ifndef io_h
#define io_h

#include <stdio.h>
#include "common.h"
#include "Geometry2D.h"

extern ITYPE in_file;

extern FILE *output;


// read structs from 'input', n - size
Point2D **readPoint(FILE *input, ITYPE *n);
Segment2D **readSegment(FILE *input, ITYPE *n);
Line2D **readLine(FILE *input, ITYPE *n);
Triangle2D **readTriangle(FILE *input, ITYPE *n);

// info about triangle
void addTriangleInfo(Triangle2D *t);

// show info about intersections
void addIntersectionSS(Segment2D *p1, Segment2D *p2);
void addIntersectionLS(Line2D *p1, Segment2D *p2);
void addIntersectionLL(Line2D *p1, Line2D *p2);


//
void showSquares(Triangle2D *p1, Line2D *p2);
#endif /* io_h */
