//
//  main.c
//  Geometry2D_Polishchenko
//
//  Created by Roman Polishchenko on 5/26/19.
//  Copyright © 2019 Roman Polishchenko. All rights reserved.
//

#include <stdio.h>
#include "headers/Geometry2D.h"
#include "headers/test_Geometry2D.h"
#include "headers/io.h"

int main(int argc, const char * argv[]) {
    FILE *point_input = fopen("points_input.txt", "r");
    if (point_input == NULL) {
        exit(1);
    }
    
    FILE *segment_input = fopen("segment_input.txt", "r");
    if (segment_input == NULL) {
        exit(1);
    }
    
    FILE *line_input = fopen("line_input.txt", "r");
    if (line_input == NULL) {
        exit(1);
    }
    
    FILE *triangle_input = fopen("triangle_input.txt", "r");
    if (triangle_input == NULL) {
        exit(1);
    }
    
//    FILE *f = stdin;
    
//    printf("Testing Geometry2D. Has a mistakes: %d.\n", test_Geometry2D());
    
    ITYPE n = 2;
    Point2D ** point = readPoint(point_input, n);
    for (UTYPE i = 0; i < n; ++i) {
        printf("point[%zu].x = %lf, point[%zu].y = %lf\n", i, point[i]->x, i, point[i]->y);
    }
    
    Segment2D ** segment = readSegment(segment_input, n);
    for (UTYPE i = 0; i < n; ++i) {
        printf("segment[%zu].a = (%lf, %lf), segment[%zu].b = (%lf, %lf)\n",
               i, segment[i]->a->x , segment[i]->a->y,
               i, segment[i]->b->x , segment[i]->b->y);
    }
    
    Line2D ** line = readLine(line_input, n+2);
    for (UTYPE i = 0; i < n+2; ++i) {
        printf("line[%zu].a = %lf, line[%zu].b = %lf, line[%zu].c = %lf\n",
               i, line[i]->a, i, line[i]->b,
               i, line[i]->c);
    }
    
    Triangle2D ** triangle = readTriangle(triangle_input, n+2);
    for (UTYPE i = 0; i < n; ++i) {
        printf("triangle[%zu].a = (%lf, %lf)\n"
               "triangle[%zu].b = (%lf, %lf)\n"
               "triangle[%zu].c = (%lf, %lf)\n",
               i, triangle[i]->a->x, triangle[i]->a->y,
               i, triangle[i]->b->x, triangle[i]->b->y,
               i, triangle[i]->c->x, triangle[i]->c->y);
    }
    
    return 0;
}
