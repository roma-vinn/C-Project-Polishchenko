//
//  io.c
//  Geometry2D_Polishchenko
//
//  Created by Roman Polishchenko on 5/27/19.
//  Copyright © 2019 Roman Polishchenko. All rights reserved.
//

#include "../headers/io.h"

DTYPE getDouble(char* str, UTYPE start, UTYPE stop) {
    char * substr = (char*) malloc(sizeof(char) * (stop-start+1) + 1);
    for (UTYPE i = start; i < stop; ++i) {
        substr[i-start] = str[i];
    }
    DTYPE d = atof(substr);
    free(substr);
    return d;
}

Point2D **readPoint(FILE *input, ITYPE *n) {
    char *num = (char *) malloc(sizeof(char) * 10 + 1);
    ITYPE count = 0;
    fgets(num, sizeof(char) * 10 + 1, input);
    count = atoi(num);
    if (count < 0) perror("Incorrect input data");
    *n = count;
    
    // array of points
    double * coordinates = (double*) malloc(2*sizeof(double));
    Point2D ** point = (Point2D**) malloc(count * sizeof(Point2D*));
    char *content = (char *) malloc(sizeof(char) * 100 * count + 1);
    
    for (UTYPE i = 0; i < count; ++i) {
        if (input == stdin) {
            fprintf(stdout, "Point[%zu]: ", i);
        }
        fgets(content, 100 * count, input);
        coordinates[0] = 0; coordinates[1] = 0;
        UTYPE s_pos = 0, e_pos = 0, k = 0;
        while (content[e_pos] != '\n' && k < 2) {
            ++e_pos;
            if (content[e_pos] == ' ' || content[e_pos] == '\n') {
                coordinates[k] = getDouble(content, s_pos, e_pos);
                ++k;
                ++e_pos;
                s_pos = e_pos;
            }
        }
        point[i] = createPoint(coordinates[0], coordinates[1]);
    }
    free(coordinates);
    free(content); free(num);
    return point;
}

Segment2D **readSegment(FILE *input, ITYPE *n) {
    char *num = (char *) malloc(sizeof(char) * 10 + 1);
    ITYPE count = 0;
    fgets(num, sizeof(char) * 10 + 1, input);
    count = atoi(num);
    if (count < 0) perror("Incorrect input data");
    *n = count;
    
    // array of points
    double * coordinates = (double*) malloc(2*sizeof(double));
    Segment2D ** segment = (Segment2D**) malloc(count * sizeof(Segment2D*));
    char *content = (char *) malloc(sizeof(char) * 100 * count + 1);
    Point2D *p1 = NULL, *p2 = NULL;
    for (UTYPE i = 0; i < count; ++i) {
        if (input == stdin) {
            fprintf(stdout, "Segments[%zu]: ", i);
        }
        fgets(content, 100 * count, input);
        coordinates[0] = 0; coordinates[1] = 0;
        coordinates[2] = 0; coordinates[3] = 0;
        UTYPE s_pos = 0, e_pos = 0, k = 0;
        while (content[e_pos] != '\n' && k < 4) {
            ++e_pos;
            if (content[e_pos] == ' ' || content[e_pos] == '\n') {
                coordinates[k] = getDouble(content, s_pos, e_pos);
                ++k;
                ++e_pos;
                s_pos = e_pos;
            }
        }
        p1 = createPoint(coordinates[0], coordinates[1]);
        p2 = createPoint(coordinates[2], coordinates[3]);
        segment[i] = createSegment(p1, p2);
    }
    free(coordinates);
    free(content); free(num);
    freePoint(p1); freePoint(p2);
    return segment;
}

Line2D **readLine(FILE *input, ITYPE *n) {
    char *num = (char *) malloc(sizeof(char) * 10 + 1);
    ITYPE count = 0;
    fgets(num, sizeof(char) * 10 + 1, input);
    count = atoi(num);
    if (count < 0) perror("Incorrect input data");
    *n = count;
    
    // array of points
    double * coordinates = (double*) malloc(2*sizeof(double));
    Line2D ** line = (Line2D**) malloc(count * sizeof(Line2D*));
    char *content = (char *) malloc(sizeof(char) * 100 * count + 1);
    Point2D *p1 = NULL, *p2 = NULL;
    for (UTYPE i = 0; i < count; ++i) {
        if (input == stdin) {
            fprintf(stdout, "Line[%zu]: ", i);
        }
        fgets(content, 100 * count, input);
        coordinates[0] = 0; coordinates[1] = 0;
        coordinates[2] = 0; coordinates[3] = 0;
        UTYPE s_pos = 0, e_pos = 0, k = 0;
        while (content[e_pos] != '\n' && k < 4) {
            ++e_pos;
            if (content[e_pos] == ' ' || content[e_pos] == '\n') {
                coordinates[k] = getDouble(content, s_pos, e_pos);
                ++k;
                ++e_pos;
                s_pos = e_pos;
            }
        }
        p1 = createPoint(coordinates[0], coordinates[1]);
        p2 = createPoint(coordinates[2], coordinates[3]);
        line[i] = createLine(p1, p2);
    }
    free(coordinates);
    free(content); free(num);
    freePoint(p1); freePoint(p2);
    return line;
}

Triangle2D **readTriangle(FILE *input, ITYPE *n) {
    char *num = (char *) malloc(sizeof(char) * 10 + 1);
    ITYPE count = 0;
    fgets(num, sizeof(char) * 10 + 1, input);
    count = atoi(num);
    if (count < 0) perror("Incorrect input data");
    *n = count;
    
    // array of points
    double * coordinates = (double*) malloc(2*sizeof(double));
    Triangle2D ** triangle = (Triangle2D**) malloc(count * sizeof(Triangle2D*));
    char *content = (char *) malloc(sizeof(char) * 100 * count + 1);
    Point2D *p1 = NULL, *p2 = NULL, *p3 = NULL;
    for (UTYPE i = 0; i < count; ++i) {
        if (input == stdin) {
            fprintf(stdout, "Triangle[%zu]: ", i);
        }
        fgets(content, 100 * count, input);
        coordinates[0] = 0; coordinates[1] = 0;
        coordinates[2] = 0; coordinates[3] = 0;
        coordinates[4] = 0; coordinates[5] = 0;
        UTYPE s_pos = 0, e_pos = 0, k = 0;
        while (content[e_pos] != '\n' && k < 6) {
            ++e_pos;
            if (content[e_pos] == ' ' || content[e_pos] == '\n') {
                coordinates[k] = getDouble(content, s_pos, e_pos);
                ++k;
                ++e_pos;
                s_pos = e_pos;
            }
        }
        p1 = createPoint(coordinates[0], coordinates[1]);
        p2 = createPoint(coordinates[2], coordinates[3]);
        p3 = createPoint(coordinates[4], coordinates[5]);
        triangle[i] = createTriangle(p1, p2, p3);
    }
    free(coordinates);
    free(content); free(num);
    freePoint(p1); freePoint(p2); freePoint(p3);
    return triangle;
}

void addTriangleInfo(Triangle2D *t) {
    fprintf(stdout, "Vertices: a = (%lf, %lf), b = (%lf, %lf), c = (%lf, %lf)\n",
                    t->a->x, t->a->y,
                    t->b->x, t->b->y,
                    t->c->x, t->c->y);
    fprintf(stdout, "Square = %lf, Perimeter = %lf\n", square(t), perimeter(t));
    Point2D *inCenter = incircleCenter(t);
    fprintf(stdout, "Incircle center = (%lf, %lf), radius = %lf\n",
            inCenter->x, inCenter->y, incircleRadius(t));
    freePoint(inCenter);
    Point2D *exCenter = excircleCenter(t);
    fprintf(stdout, "Excircle center = (%lf, %lf), radius = %lf\n",
            exCenter->x, exCenter->y, excircleRadius(t));
    freePoint(exCenter);
    fprintf(stdout, "Angle A = %lf, Angle B = %lf, Angle B = %lf\n",
            angleA(t), angleB(t), angleC(t));
    Point2D *mCenter = massCenter(t);
    fprintf(stdout, "Mass center = (%lf, %lf)\n\n", mCenter->x, mCenter->y);
    freePoint(mCenter);
    
    if (in_file) {
        fprintf(output, "Vertices: a = (%lf, %lf), b = (%lf, %lf), c = (%lf, %lf)\n",
                t->a->x, t->a->y,
                t->b->x, t->b->y,
                t->c->x, t->c->y);
        fprintf(output, "Square = %lf, Perimeter = %lf\n", square(t), perimeter(t));
        Point2D *inCenter = incircleCenter(t);
        fprintf(output, "Incircle center = (%lf, %lf), radius = %lf\n",
                inCenter->x, inCenter->y, incircleRadius(t));
        freePoint(inCenter);
        Point2D *exCenter = excircleCenter(t);
        fprintf(output, "Excircle center = (%lf, %lf), radius = %lf\n",
                exCenter->x, exCenter->y, excircleRadius(t));
        freePoint(exCenter);
        fprintf(output, "Angle A = %lf, Angle B = %lf, Angle B = %lf\n",
                angleA(t), angleB(t), angleC(t));
        Point2D *mCenter = massCenter(t);
        fprintf(output, "Mass center = (%lf, %lf)\n\n", mCenter->x, mCenter->y);
        freePoint(mCenter);
    }
}

void addIntersectionSS(Segment2D *p1, Segment2D *p2) {
    fprintf(stdout, "Segments with ends:\n"
            "s1 - (%lf, %lf) and (%lf, %lf)\n"
            "s2 - (%lf, %lf) and (%lf, %lf)\n",
            p1->a->x, p1->a->y, p1->b->x, p1->b->y,
            p2->a->x, p2->a->y, p2->b->x, p2->b->y);
    
    Point2D *inter = intersectSS(p1, p2);
    if (inter->y == INF) {
        fprintf(stdout, "Infinite number of common points.\n\n");
    } else if (inter->y == -INF) {
        fprintf(stdout, "No common points.\n\n");
    } else {
        fprintf(stdout, "Intersection = (%lf, %lf).\n\n",
                inter->x, inter->y);
    }
    freePoint(inter);
    
    if (in_file) {
        fprintf(output, "Segments with ends:\n"
                "s1 - (%lf, %lf) and (%lf, %lf)\n"
                "s2 - (%lf, %lf) and (%lf, %lf)\n",
                p1->a->x, p1->a->y, p1->b->x, p1->b->y,
                p2->a->x, p2->a->y, p2->b->x, p2->b->y);
        
        Point2D *inter = intersectSS(p1, p2);
        if (inter->y == INF) {
            fprintf(output, "Infinite number of common points.\n\n");
        } else if (inter->y == -INF) {
            fprintf(output, "No common points.\n\n");
        } else {
            fprintf(output, "Intersection = (%lf, %lf).\n\n",
                    inter->x, inter->y);
        }
        freePoint(inter);
    }
}

void addIntersectionLS(Line2D *p1, Segment2D *p2) {
    fprintf(stdout, "Line: ax + by + c = 0,\n"
            "where a = %lf, b = %lf, c = %lf\n",
            p1->a, p1->b, p1->c);
    fprintf(stdout, "Segment with ends (%lf, %lf) and (%lf, %lf)\n",
            p2->a->x, p2->a->y, p2->b->x, p2->b->y);
    
    Point2D *inter = intersectLS(p1, p2);
    if (inter->y == INF) {
        fprintf(stdout, "Infinite number of common points.\n\n");
    } else if (inter->y == -INF) {
        fprintf(stdout, "No common points.\n\n");
    } else {
        fprintf(stdout, "Intersection = (%lf, %lf).\n\n",
                inter->x, inter->y);
    }
    freePoint(inter);
    
    if (in_file) {
        fprintf(output, "Line: ax + by + c = 0,\n"
                "where a = %lf, b = %lf, c = %lf\n",
                p1->a, p1->b, p1->c);
        fprintf(output, "Segment with ends (%lf, %lf) and (%lf, %lf)\n",
                p2->a->x, p2->a->y, p2->b->x, p2->b->y);
        
        Point2D *inter = intersectLS(p1, p2);
        if (inter->y == INF) {
            fprintf(output, "Infinite number of common points.\n\n");
        } else if (inter->y == -INF) {
            fprintf(output, "No common points.\n\n");
        } else {
            fprintf(output, "Intersection = (%lf, %lf).\n\n",
                    inter->x, inter->y);
        }
        freePoint(inter);
    }
}

void addIntersectionLL(Line2D *p1, Line2D *p2) {
    fprintf(stdout, "Line 1: ax + by + c = 0,\n"
            "where a = %lf, b = %lf, c = %lf\n",
            p1->a, p1->b, p1->c);
    fprintf(stdout, "Line 2: ax + by + c = 0,\n"
            "where a = %lf, b = %lf, c = %lf\n",
            p2->a, p2->b, p2->c);
    
    Point2D *inter = intersectLL(p1, p2);
    if (inter->y == INF) {
        fprintf(stdout, "Infinite number of common points.\n\n");
    } else if (inter->y == -INF) {
        fprintf(stdout, "No common points.\n\n");
    } else {
        fprintf(stdout, "Intersection = (%lf, %lf).\n\n",
                inter->x, inter->y);
    }
    freePoint(inter);
    
    if (in_file) {
        fprintf(output, "Line 1: ax + by + c = 0,\n"
                "where a = %lf, b = %lf, c = %lf\n",
                p1->a, p1->b, p1->c);
        fprintf(output, "Line 2: ax + by + c = 0,\n"
                "where a = %lf, b = %lf, c = %lf\n",
                p2->a, p2->b, p2->c);
        
        Point2D *inter = intersectLL(p1, p2);
        if (inter->y == INF) {
            fprintf(output, "Infinite number of common points.\n\n");
        } else if (inter->y == -INF) {
            fprintf(output, "No common points.\n\n");
        } else {
            fprintf(output, "Intersection = (%lf, %lf).\n\n",
                    inter->x, inter->y);
        }
        freePoint(inter);
    }
}

void showSquares(Triangle2D *p1, Line2D *p2){
    fprintf(stdout, "Triangle with vertices:\n"
            "a = (%lf, %lf), b = (%lf, %lf), c = (%lf, %lf)\n",
            p1->a->x, p1->a->y,
            p1->b->x, p1->b->y,
            p1->c->x, p1->c->y);
    fprintf(stdout, "Line: ax + by + c = 0,\n"
            "where a = %lf, b = %lf, c = %lf\n",
            p2->a, p2->b, p2->c);
    
    DTYPE s1 = 0, s2 = 0;
    if (figuresSquares(p1, p2, &s1, &s2)) {
        fprintf(stdout, "Line doesn't intersect triangle.\n\n");
    } else {
        fprintf(stdout, "Line intersect triangle and cuts off two figures:\n"
                "S1 = %lf, S2 = %lf\n\n", s1, s2);
    }
    
    if (in_file) {
        fprintf(output, "Triangle with vertices:\n"
                "a = (%lf, %lf), b = (%lf, %lf), c = (%lf, %lf)\n",
                p1->a->x, p1->a->y,
                p1->b->x, p1->b->y,
                p1->c->x, p1->c->y);
        fprintf(output, "Line: ax + by + c = 0,\n"
                "where a = %lf, b = %lf, c = %lf\n",
                p2->a, p2->b, p2->c);
        
        DTYPE s1 = 0, s2 = 0;
        if (figuresSquares(p1, p2, &s1, &s2)) {
            fprintf(output, "Line doesn't intersect triangle.\n\n");
        } else {
            fprintf(output, "Line intersect triangle and cuts off two figures:\n"
                    "S1 = %lf, S2 = %lf\n\n", s1, s2);
        }
    }
}
