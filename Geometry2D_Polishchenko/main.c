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
    printf("Testing Geometry2D. Has a mistakes: %d.\n", test_Geometry2D());
    
    return 0;
}
