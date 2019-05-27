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

