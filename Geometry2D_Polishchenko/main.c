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

int main(int argc, const char * argv[]) {
    for (int i = 0; i < 1000000; ++i) {
        test_Geometry2D();
        if (i % 100000 == 0) {
            printf("Testing Geometry2D. Has a mistakes: %d.\n", test_Geometry2D());
        }
    }
    
    return 0;
}
