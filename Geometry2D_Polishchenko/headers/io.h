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

// read 'count' structs from 'input'
Point2D **readPoint(FILE *input, ITYPE count);
Segment2D **readSegment(FILE *input, ITYPE count);
Line2D **readLine(FILE *input, ITYPE count);
Triangle2D **readTriangle(FILE *input, ITYPE count);

#endif /* io_h */
