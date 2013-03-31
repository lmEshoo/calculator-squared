//


#include <iostream>
#include <math.h>

#define myFloor( V ) ((V) >= 0 ? (int)(V) : (int)((V) - 1))


using namespace std;

 double taylorSeriesToCalculateCosine( double x, int degree);
 double taylorSeriesToCalculateSin( double x, int degree);
 double referenceAngle( double x);

 double factorial( int input );

int main(int argc, const char * argv[])
{
    //main...
    
    return 0;
}

// taylor series to calculate cosine
 double taylorSeriesToCalculateCosine( double x,int degree){
    
    int i = 0;
     double accumulation = 0;
    
    //array of derivatives of cos to multiply 
    int cosInputArray[4] = {1,0,-1,0};
     
     //if statement to get the value of the inputs return value
     //if the input is greater than one radian
     if (x > 1.57079) {
         x = referenceAngle(x);
     }
    
    while (i < degree) {
                
        // the value of the derivative array based on the degree
        int input = cosInputArray[i%4];
        
        //the brunt of the taylor series
        //value of the array multiplied by the input to the power of what number loop the program
        //is in, divided by the factorial of what number loop the rpogram is in
        accumulation += input*((pow(x, i))/factorial(i)); 
        i++;
    }
    
    return accumulation;
}

// taylor series to calculate sin
 double taylorSeriesToCalculateSin( double x, int degree){
    
    int i = 0;
     double accumulation = 0;
     
     //array of derivatives of sin
    int sinInputArray[4] = {0,1,0,-1};
     
    //if statement to get the value of the inputs return value
    //if the input is greater than one radian
    if (x > 1.57079) {
         x = referenceAngle(x);
     }
    
    while (i < degree) {
        
        // the value of the derivative array based on the degree
        int input = sinInputArray[i%4];
        
        //the brunt of the taylor series
        //value of the array multiplied by the input to the power of what number loop the program
        //is in, divided by the factorial of what number loop the rpogram is in
        accumulation += input*((pow(x, i))/factorial(i));
        i++;
    }
    
    return accumulation;
}
    

// function to calculate factorial
 double factorial(int input ) {
     double output = 1;
    for( int i = 2; i <= input; ++ i ) {
        output *= i;
    }
    return output;
}

//function to retrieve the inputs reference angle if the input is greater than one radian
 double referenceAngle( double x){
    int k = 0;
     double pi = 3.14159;
    int quadrant = 0;
     double referenceAngle = 0.0;
    
    //determining which quadrant the input is in
    k = myFloor(x/(pi/2));
    quadrant = k % 4;
    
     //if the input is in quandrants 1 or 3
    if (quadrant == 1 || quadrant == 3) {
        referenceAngle = x - ((pi/2)*k);
    }
    
    //if the input is in quadeant two or four
    else {
        referenceAngle = (pi/2) - (x - ((pi/2)*k));
    }
    
    return referenceAngle;
}

/*Taylor Series:
    1. Sin
    2. Cos
    3. x^y   
    4. ln(x) 
 
 CORDIC
    "same as taylor"
    
*/