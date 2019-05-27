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

ITYPE in_file = 0;

FILE *output;

int main(int argc, const char * argv[]) {
    FILE *f = stdin;
    
    // test functions ?
    char* choice = (char*) malloc(sizeof(char) * 10);
    printf("Make unit-tests? y/n: ");
    fgets(choice, sizeof(char) * 10, f);
    if (choice[0] == 'y') {
        printf("Testing...\nHas a mistakes: %d.\n\n", test_Geometry2D());
    } else if (choice[0] != 'n') {
        printf("Incorrect input. Treated like 'n'.\n\n");
    }
    
    // Input type
    ITYPE p_count = 0, s_count = 0, l_count = 0, t_count = 0;
    printf("Input from:\n1. Files.\n2. Console.\n");
    fgets(choice, sizeof(char) * 10, f);
    
    Point2D ** point = NULL;
    Segment2D ** segment = NULL;
    Line2D ** line = NULL;
    Triangle2D ** triangle = NULL;
    
    // CONSOLE INPUT
    if (choice[0] == '2') {
        fprintf(stdout, "Enter the number of points: ");
        point = readPoint(stdin, &p_count);
        for (UTYPE i = 0; i < p_count; ++i) {
            printf("point[%zu].x = %lf, point[%zu].y = %lf\n",
                   i, point[i]->x, i, point[i]->y);
        }
        
        fprintf(stdout, "Enter the number of Segments: ");
        segment = readSegment(stdin, &s_count);
        for (UTYPE i = 0; i < s_count; ++i) {
            printf("segment[%zu].a = (%lf, %lf), segment[%zu].b = (%lf, %lf)\n",
                   i, segment[i]->a->x, segment[i]->a->y,
                   i, segment[i]->b->x, segment[i]->b->y);
        }
        
        fprintf(stdout, "Enter the number of Lines: ");
        line = readLine(stdin, &l_count);
        for (UTYPE i = 0; i < l_count; ++i) {
            printf("line[%zu].a = %lf, line[%zu].b = %lf, line[%zu].c = %lf\n",
                   i, line[i]->a, i, line[i]->b, i, line[i]->c);
        }
        
        fprintf(stdout, "Enter the number of Triangles: ");
        triangle = readTriangle(stdin, &t_count);
        for (UTYPE i = 0; i < t_count; ++i) {
            printf("triangle[%zu].a = (%lf, %lf)\ntriangle[%zu].b = (%lf, %lf)"
                   "\ntriangle[%zu].c = (%lf, %lf)\n\n",
                   i, triangle[i]->a->x, triangle[i]->a->y,
                   i, triangle[i]->b->x, triangle[i]->b->y,
                   i, triangle[i]->c->x, triangle[i]->c->y);
        }
        
    } else {
        // FILE INPUT
        FILE *point_input = fopen("points_input.txt", "r");
        if (point_input == NULL) perror("File opening error");
        
        FILE *segment_input = fopen("segment_input.txt", "r");
        if (segment_input == NULL) perror("File opening error");
        
        FILE *line_input = fopen("line_input.txt", "r");
        if (line_input == NULL) perror("File opening error");
        
        FILE *triangle_input = fopen("triangle_input.txt", "r");
        if (triangle_input == NULL) perror("File opening error");
        
        point = readPoint(point_input, &p_count);
        for (UTYPE i = 0; i < p_count; ++i) {
            printf("point[%zu].x = %lf, point[%zu].y = %lf\n", i, point[i]->x, i, point[i]->y);
        }
        
        segment = readSegment(segment_input, &s_count);
        for (UTYPE i = 0; i < s_count; ++i) {
            printf("segment[%zu].a = (%lf, %lf), segment[%zu].b = (%lf, %lf)\n",
                   i, segment[i]->a->x , segment[i]->a->y,
                   i, segment[i]->b->x , segment[i]->b->y);
        }

        line = readLine(line_input, &l_count);
        for (UTYPE i = 0; i < l_count; ++i) {
            printf("line[%zu].a = %lf, line[%zu].b = %lf, line[%zu].c = %lf\n",
                   i, line[i]->a, i, line[i]->b,
                   i, line[i]->c);
        }

        triangle = readTriangle(triangle_input, &t_count);
        for (UTYPE i = 0; i < t_count; ++i) {
            printf("triangle[%zu].a = (%lf, %lf)\n"
                   "triangle[%zu].b = (%lf, %lf)\n"
                   "triangle[%zu].c = (%lf, %lf)\n",
                   i, triangle[i]->a->x, triangle[i]->a->y,
                   i, triangle[i]->b->x, triangle[i]->b->y,
                   i, triangle[i]->c->x, triangle[i]->c->y);
        }
        
        fclose(point_input);
        fclose(segment_input);
        fclose(line_input);
        fclose(triangle_input);
    }
    
    // save information in the file ?
    fprintf(stdout, "Save the info in the file 'output.txt'? y/n: ");
    fgets(choice, sizeof(char) * 10, f);
    if (choice[0]=='y') {
        in_file = 1;
        output = fopen("output.txt", "w");
        fclose(output);
        output = fopen("output.txt", "a");
        if (output == NULL) perror("File opening error");
        fprintf(stdout, "Info will be saved.\n");
    } else {
        in_file = 0;
        fprintf(stdout, "Info won't be saved.\n");
    }
    
    ITYPE flag = 1;
    ITYPE choiceNum = 0;
    while (flag) {
        fprintf(stdout, "Choose action:\n");
        fprintf(stdout, "1. Show info about triangle.\n");
        fprintf(stdout, "2. Find intersection of two segments.\n");
        fprintf(stdout, "3. Find intersection of line and segment.\n");
        fprintf(stdout, "4. Find intersection of two lines.\n");
        fprintf(stdout, "5. Show squares of figures that line cuts from triangle.\n");
        fprintf(stdout, "0. Exit.\n");
        fgets(choice, sizeof(char) * 10, f);
        choiceNum = atoi(choice);
        char *num = (char*) malloc(sizeof(char) * 10 + 1);
        ITYPE k = 0, m = 0;
        switch (choiceNum) {
                // 1. Show info about triangle.
            case 1:
                if (t_count == 0) {
                    fprintf(stdout, "There isn't any triangles. "
                            "Choose another action.\n");
                } else {
                    fprintf(stdout, "Number of triangle: ");
                    fgets(num, 11, f);
                    k = atoi(num);
                    if (k >= 0 && k <= t_count-1) {
                        addTriangleInfo(triangle[k]);
                    }
                }
                break;

                // 2. Find intersection of two segments.
            case 2:
                if (s_count < 2) {
                    fprintf(stdout, "Not enough segments. "
                            "Choose another action.\n");
                } else {
                    fprintf(stdout, "Number of first segment: ");
                    fgets(num, 11, f);
                    k = atoi(num);
                    fprintf(stdout, "Number of second segment: ");
                    fgets(num, 11, f);
                    m = atoi(num);
                    if (k != m && k >= 0 && m >= 0 &&
                        k <= s_count-1 && m <= s_count-1) {
                        addIntersectionSS(segment[k], segment[m]);
                    } else {
                        fprintf(stdout, "Incorrect indeces: %d and %d\n", k, m);
                    }
                }
                break;

                // 3. Find intersection of line and segment.
            case 3:
                if (s_count < 1 || l_count < 1) {
                    fprintf(stdout, "Not enough segments or lines. "
                            "Choose another action.\n");
                } else {
                    fprintf(stdout, "Number of line: ");
                    fgets(num, 11, f);
                    k = atoi(num);
                    fprintf(stdout, "Number of segment: ");
                    fgets(num, 11, f);
                    m = atoi(num);
                    if (k != m && k >= 0 && m >= 0 &&
                        k <= l_count-1 && m <= s_count-1) {
                        addIntersectionLS(line[k], segment[m]);
                    } else {
                        fprintf(stdout, "Incorrect indeces: %d and %d\n", k, m);
                    }
                }
                break;

                // 4. Find intersection of two lines.
            case 4:
                if (l_count < 2) {
                    fprintf(stdout, "Not enough lines. "
                            "Choose another action.\n");
                } else {
                    fprintf(stdout, "Number of first line: ");
                    fgets(num, 11, f);
                    k = atoi(num);
                    fprintf(stdout, "Number of second line: ");
                    fgets(num, 11, f);
                    m = atoi(num);
                    if (k != m && k >= 0 && m >= 0 &&
                        k <= l_count-1 && m <= l_count-1) {
                        addIntersectionLL(line[k], line[m]);
                    } else {
                        fprintf(stdout, "Incorrect indeces: %d and %d\n", k, m);
                    }
                }
                break;

                // 5. Show squares of figures that line cuts from triangle.
            case 5:
//                figuresSquares
                if (l_count < 1 || t_count < 1) {
                    fprintf(stdout, "Not enough lines or triangles. "
                            "Choose another action.\n");
                } else {
                    fprintf(stdout, "Number of line: ");
                    fgets(num, 11, f);
                    k = atoi(num);
                    fprintf(stdout, "Number of triangle: ");
                    fgets(num, 11, f);
                    m = atoi(num);
                    if (k != m && k >= 0 && m >= 0 &&
                        k <= l_count-1 && m <= t_count-1) {
                        showSquares(triangle[m], line[k]);
                    } else {
                        fprintf(stdout, "Incorrect indeces: %d and %d\n", k, m);
                    }
                }
                break;

                // 0. Exit.
            case 0:
                flag = 0;
                fprintf(stdout, "Shutting down...\n");
                break;
                
                // Incorrect command
            default:
                fprintf(stdout, "Incorrect command. Type"
                        "one of the numbers [0, .., 5]\n");
                break;
        }
        
        free(num);
    }
    free(choice);
    
    // free memory for all arrays
    for (UTYPE i = 0; i < p_count; ++i) {
        freePoint(point[i]);
    }
    free(point);
    
    for (UTYPE i = 0; i < s_count; ++i) {
        freeSegment(segment[i]);
    }
    free(segment);
    
    for (UTYPE i = 0; i < l_count; ++i) {
        freeLine(line[i]);
    }
    free(line);
    
    for (UTYPE i = 0; i < t_count; ++i) {
        freeTriangle(triangle[i]);
    }
    free(triangle);
    return 0;
}
