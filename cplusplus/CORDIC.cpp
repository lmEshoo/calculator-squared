//
//  main.cpp
//  CordicFunction
//
//  Created by Matt Remick on 4/2/13.
//  Copyright (c) 2013 Matt Remick. All rights reserved.
//

#include <iostream>
#include <math.h>

using namespace std;

double referenceAngle( double x);
double cordicFunctionCosine(double input, int degree);
double cordicFunctionSin(double input, int degree);
double cordicFunctionTangent(double input, int degree);
bool die(const string &msg);


int main(int argc, const char * argv[])
{
    //main c|:)

    return 0;
}

bool die(const string &msg) {
    cerr <<endl << "fatal error: " <<msg <<endl;
    exit( EXIT_FAILURE );
}

//function to retrieve the inputs reference angle if the input is greater than one radian
double referenceAngle( double x){
    int k = 0;
    double pi = 3.14159;
    int quadrant = 0;
    double referenceAngle = 0;
    
    //determining which quadrant the input is in
    k = floor(x/(pi/2));
    quadrant = k % 4;
    
    //if the input is in quandrants 1 or 3
    if (quadrant == 0 || quadrant == 2) {
        referenceAngle = x - ((pi/2)*k);
    }
    
    //if the input is in quadeant two or four
    else {
        referenceAngle = (pi/2) - (x - ((pi/2)*k));
    }
    
    return referenceAngle;
}

double cordicFunctionCosine(double input, int degree){
    
    double kn;
    double v[] = {1,0};
    double powerOfTwo;
    double angle;
    int i = 0;
    int sigma;
    double factor;
    double temp_v0;
    int quadrant;
    double pi = 3.14159;
    int k;
    
    //determining the quadrant of the input
    if (input > 1.57079) {
        k = floor(input/(pi/2));
        quadrant = 1+(k % 4);
    }
    
    else quadrant = 1;
    
    //reference angle function if input is greater than one radian
    if (input > 1.57) {
        input = referenceAngle(input);
    }
    

    
    // Initialization of tables of constants used by CORDIC
    // need a table of arctangents of negative powers of two, in radians:
    // angles = atan(2.^-(0:27));
    double angles[] =  {                //len = 28 //arctangents
               0.78539816339745,   0.46364760900081,   0.24497866312686,   0.12435499454676,
               0.06241880999596,   0.03123983343027,   0.01562372862048,   0.00781234106010,
               0.00390623013197,   0.00195312251648,   0.00097656218956,   0.00048828121119,
               0.00024414062015,   0.00012207031189,   0.00006103515617,   0.00003051757812,
               0.00001525878906,   0.00000762939453,   0.00000381469727,   0.00000190734863,
               0.00000095367432,   0.00000047683716,   0.00000023841858,   0.00000011920929,
               0.00000005960464,   0.00000002980232,   0.00000001490116,   0.00000000745058 };
    
    double Kvalues[] = {
               0.70710678118655,   0.63245553203368,   0.61357199107790,   0.60883391251775,
               0.60764825625617,   0.60735177014130,   0.60727764409353,   0.60725911229889,
               0.60725447933256,   0.60725332108988,   0.60725303152913,   0.60725295913894,
               0.60725294104140,   0.60725293651701,   0.60725293538591,   0.60725293510314,
               0.60725293503245,   0.60725293501477,   0.60725293501035,   0.60725293500925,
               0.60725293500897,   0.60725293500890,   0.60725293500889,   0.60725293500888 };
                                        //len = 24  //k values
    
    if (degree > 24) {
        kn = Kvalues[23];
    }
    
    else kn = Kvalues[degree];
        
    angle = angles[0];
    powerOfTwo = 1;
    
    //determining whether to rotate positively or negatively 
    while (i < degree) {
        
        if (input < 0) {
            sigma = -1;
        }
        
        else {
            sigma = 1;
        }
    
    //changing the factor, which approches zero 
    factor = sigma * powerOfTwo;
                
    //    int v[] = {1,0};
    //multiplying the matrices, essentially rotating the vector
    temp_v0 = v[0];
    v[0] = (1*v[0]) + ((-1)*(factor*v[1]));
    
    v[1] = (factor*temp_v0) + (1*v[1]);
    
    //changing the input
    input -= sigma * angle;
        
    //powerOfTwo gets smaller and smaller to make the factor approach zero
    powerOfTwo = powerOfTwo / 2.0;
    
    //still need to figure this one out, need time lol
    if (i+2 > 27) {
        angle = angle / 2.0;
    }
    
    else angle = angles[i+1];
    
    i++;
    }
    
    //final x coordinate multiplied by the k value
    v[0] *= kn;
    
    //determining if positive or negative
    if (quadrant == 2 || quadrant == 3) {
        v[0] *= -1;
    }
    
    return v[0];
    
}

double cordicFunctionSin(double input, int degree){
    
    double kn;
    double v[] = {1,0};
    double powerOfTwo;
    double angle;
    int i = 0;
    int sigma;
    double factor;
    double temp_v0;
    int quadrant;
    double pi = 3.14159;
    int k;
    
    if (input > 1.57079) {
        k = floor(input/(pi/2));
        quadrant = 1+(k % 4);
    }
    
    else quadrant = 1;
    
    if (input > 1.57) {
        input = referenceAngle(input);
    }
    
    
    
    // Initialization of tables of constants used by CORDIC
    // need a table of arctangents of negative powers of two, in radians:
    // angles = atan(2.^-(0:27));
    double angles[] =  {                //len = 28 //arctangents
        0.78539816339745,   0.46364760900081,   0.24497866312686,   0.12435499454676,
        0.06241880999596,   0.03123983343027,   0.01562372862048,   0.00781234106010,
        0.00390623013197,   0.00195312251648,   0.00097656218956,   0.00048828121119,
        0.00024414062015,   0.00012207031189,   0.00006103515617,   0.00003051757812,
        0.00001525878906,   0.00000762939453,   0.00000381469727,   0.00000190734863,
        0.00000095367432,   0.00000047683716,   0.00000023841858,   0.00000011920929,
        0.00000005960464,   0.00000002980232,   0.00000001490116,   0.00000000745058 };
    
    double Kvalues[] = {
        0.70710678118655,   0.63245553203368,   0.61357199107790,   0.60883391251775,
        0.60764825625617,   0.60735177014130,   0.60727764409353,   0.60725911229889,
        0.60725447933256,   0.60725332108988,   0.60725303152913,   0.60725295913894,
        0.60725294104140,   0.60725293651701,   0.60725293538591,   0.60725293510314,
        0.60725293503245,   0.60725293501477,   0.60725293501035,   0.60725293500925,
        0.60725293500897,   0.60725293500890,   0.60725293500889,   0.60725293500888 };
                                        //len = 24 //k values
    
    if (degree > 24) {
        kn = Kvalues[23];
    }
    
    else kn = Kvalues[degree];
    
    angle = angles[0];
    powerOfTwo = 1;
    
    //determining whether to rotate positively or negatively
    while (i < degree) {
        
        if (input < 0) {
            sigma = -1;
        }
        
        else {
            sigma = 1;
        }
        //changing the factor, which approches zero
        factor = sigma * powerOfTwo;
        
        //    int v[] = {1,0};
        
        //temporary v[0]
        temp_v0 = v[0];
        
        //multiplying the matrices
        v[0] = (1*v[0]) + ((-1)*(factor*v[1]));
        
        v[1] = (factor*temp_v0) + (1*v[1]);
        
        //changing the input
        input -= sigma * angle;
        
        //powerOfTwo gets smaller and smaller to make the factor approach zero
        powerOfTwo = powerOfTwo / 2.0;
        
        if (i+2 > 27) {
            angle = angle / 2.0;
        }
        
        else angle = angles[i+1];
        
        i++;
    }
    
    //multilying the y coordinate by the k value
    v[1] *= kn;
    
    //determining if positive or negative
    if (quadrant == 3 || quadrant == 4) {
        v[1] *= -1;
    }  
    
    return v[1];

}

double cordicFunctionTangent(double input, int degree){
    
    double tangent;
    
    if (cordicFunctionCosine(input, degree) == 0) {
        die("Error: DIVIDE BY ZERO");
    }
    
    tangent = cordicFunctionSin(input, degree) / cordicFunctionCosine(input, degree);
    
    return tangent;
    
}