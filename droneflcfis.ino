#define FIS_TYPE float
#define FIS_RESOLUSION 101
#define FIS_MIN -3.4028235E+38
#define FIS_MAX 3.4028235E+38
typedef FIS_TYPE(*_FIS_MF)(FIS_TYPE, FIS_TYPE*);
typedef FIS_TYPE(*_FIS_ARR_OP)(FIS_TYPE, FIS_TYPE);
typedef FIS_TYPE(*_FIS_ARR)(FIS_TYPE*, int, _FIS_ARR_OP);
int AngleRoll,AnglePitch;
int RV,RP;
//#include "fis_header.h"

// Number of inputs to the fuzzy inference system
const int fis_gcI = 3;
// Number of outputs to the fuzzy inference system
const int fis_gcO = 3;
// Number of rules to the fuzzy inference system
const int fis_gcR = 125;

FIS_TYPE g_fisInput[fis_gcI];
FIS_TYPE g_fisOutput[fis_gcO];

// Setup routine runs once when you press reset:
void setup()
{
  Serial.begin(9600);
    // initialize the Analog pins for input.
    // Pin mode for Input: roll
    /*pinMode(0, INPUT);
    // Pin mode for Input: pitch
    pinMode(1 , INPUT);
    // Pin mode for Input: yaw
    pinMode(2 , INPUT);


    // initialize the Analog pins for output.
    // Pin mode for Output: output1
    pinMode(3 , OUTPUT);
    // Pin mode for Output: output2
    pinMode(4 , OUTPUT);
    // Pin mode for Output: output3
    pinMode(5 , OUTPUT);*/

}

// Loop routine runs over and over again forever:
void loop()
{
    // Read Input: roll
    g_fisInput[0] = abs(AngleRoll);
    // Read Input: pitch
    g_fisInput[1] = abs(AnglePitch);
    // Read Input: yaw
    g_fisInput[2] = 0;
     g_fisOutput[0] = RV;
    g_fisOutput[1] = RP;
        g_fisOutput[0] = 0;
    g_fisOutput[1] = 0;
    g_fisOutput[2] = 0;

    fis_evaluate();
    Serial.println(g_fisOutput[0]);
    Serial.println(g_fisOutput[1]);
    Serial.println(g_fisOutput[2]);
/*
    // Set output vlaue: output1
    analogWrite(3 , g_fisOutput[0]);
    // Set output vlaue: output2
    analogWrite(4 , g_fisOutput[1]);
    // Set output vlaue: output3
    analogWrite(5 , g_fisOutput[2]);
    */

}

//***********************************************************************
// Support functions for Fuzzy Inference System                          
//***********************************************************************
// Triangular Member Function
FIS_TYPE fis_trimf(FIS_TYPE x, FIS_TYPE* p)
{
    FIS_TYPE a = p[0], b = p[1], c = p[2];
    FIS_TYPE t1 = (x - a) / (b - a);
    FIS_TYPE t2 = (c - x) / (c - b);
    if ((a == b) && (b == c)) return (FIS_TYPE) (x == a);
    if (a == b) return (FIS_TYPE) (t2*(b <= x)*(x <= c));
    if (b == c) return (FIS_TYPE) (t1*(a <= x)*(x <= b));
    t1 = min(t1, t2);
    return (FIS_TYPE) max(t1, 0);
}

FIS_TYPE fis_min(FIS_TYPE a, FIS_TYPE b)
{
    return min(a, b);
}

FIS_TYPE fis_max(FIS_TYPE a, FIS_TYPE b)
{
    return max(a, b);
}

FIS_TYPE fis_array_operation(FIS_TYPE *array, int size, _FIS_ARR_OP pfnOp)
{
    int i;
    FIS_TYPE ret = 0;

    if (size == 0) return ret;
    if (size == 1) return array[0];

    ret = array[0];
    for (i = 1; i < size; i++)
    {
        ret = (*pfnOp)(ret, array[i]);
    }

    return ret;
}


//***********************************************************************
// Data for Fuzzy Inference System                                       
//***********************************************************************
// Pointers to the implementations of member functions
_FIS_MF fis_gMF[] =
{
    fis_trimf
};

// Count of member function for each Input
int fis_gIMFCount[] = { 5, 5, 5 };

// Count of member function for each Output 
int fis_gOMFCount[] = { 5, 5, 5 };

// Coefficients for the Input Member Functions
FIS_TYPE fis_gMFI0Coeff1[] = { -75, 0, 75 };
FIS_TYPE fis_gMFI0Coeff2[] = { 15, 90, 165 };
FIS_TYPE fis_gMFI0Coeff3[] = { 105, 180, 255 };
FIS_TYPE fis_gMFI0Coeff4[] = { 195, 270, 345 };
FIS_TYPE fis_gMFI0Coeff5[] = { 285, 360, 435 };
FIS_TYPE* fis_gMFI0Coeff[] = { fis_gMFI0Coeff1, fis_gMFI0Coeff2, fis_gMFI0Coeff3, fis_gMFI0Coeff4, fis_gMFI0Coeff5 };
FIS_TYPE fis_gMFI1Coeff1[] = { -75, 0, 75 };
FIS_TYPE fis_gMFI1Coeff2[] = { 15, 90, 165 };
FIS_TYPE fis_gMFI1Coeff3[] = { 105, 180, 255 };
FIS_TYPE fis_gMFI1Coeff4[] = { 195, 270, 345 };
FIS_TYPE fis_gMFI1Coeff5[] = { 285, 360, 435 };
FIS_TYPE* fis_gMFI1Coeff[] = { fis_gMFI1Coeff1, fis_gMFI1Coeff2, fis_gMFI1Coeff3, fis_gMFI1Coeff4, fis_gMFI1Coeff5 };
FIS_TYPE fis_gMFI2Coeff1[] = { -75, 0, 75 };
FIS_TYPE fis_gMFI2Coeff2[] = { 15, 90, 165 };
FIS_TYPE fis_gMFI2Coeff3[] = { 105, 180, 255 };
FIS_TYPE fis_gMFI2Coeff4[] = { 195, 270, 345 };
FIS_TYPE fis_gMFI2Coeff5[] = { 285, 360, 435 };
FIS_TYPE* fis_gMFI2Coeff[] = { fis_gMFI2Coeff1, fis_gMFI2Coeff2, fis_gMFI2Coeff3, fis_gMFI2Coeff4, fis_gMFI2Coeff5 };
FIS_TYPE** fis_gMFICoeff[] = { fis_gMFI0Coeff, fis_gMFI1Coeff, fis_gMFI2Coeff };

// Coefficients for the Output Member Functions
FIS_TYPE fis_gMFO0Coeff1[] = { -1.04166666666667, 0, 1.04166666666667 };
FIS_TYPE fis_gMFO0Coeff2[] = { 0.208333333333333, 1.25, 2.29166666666667 };
FIS_TYPE fis_gMFO0Coeff3[] = { 1.45833333333333, 2.5, 3.54166666666667 };
FIS_TYPE fis_gMFO0Coeff4[] = { 2.70833333333333, 3.75, 4.79166666666667 };
FIS_TYPE fis_gMFO0Coeff5[] = { 3.95833333333333, 5, 6.04166666666667 };
FIS_TYPE* fis_gMFO0Coeff[] = { fis_gMFO0Coeff1, fis_gMFO0Coeff2, fis_gMFO0Coeff3, fis_gMFO0Coeff4, fis_gMFO0Coeff5 };
FIS_TYPE fis_gMFO1Coeff1[] = { -1.04166666666667, 0, 1.04166666666667 };
FIS_TYPE fis_gMFO1Coeff2[] = { 0.208333333333333, 1.25, 2.29166666666667 };
FIS_TYPE fis_gMFO1Coeff3[] = { 1.45833333333333, 2.5, 3.54166666666667 };
FIS_TYPE fis_gMFO1Coeff4[] = { 2.70833333333333, 3.75, 4.79166666666667 };
FIS_TYPE fis_gMFO1Coeff5[] = { 3.95833333333333, 5, 6.04166666666667 };
FIS_TYPE* fis_gMFO1Coeff[] = { fis_gMFO1Coeff1, fis_gMFO1Coeff2, fis_gMFO1Coeff3, fis_gMFO1Coeff4, fis_gMFO1Coeff5 };
FIS_TYPE fis_gMFO2Coeff1[] = { -1.04166666666667, 0, 1.04166666666667 };
FIS_TYPE fis_gMFO2Coeff2[] = { 0.208333333333333, 1.25, 2.29166666666667 };
FIS_TYPE fis_gMFO2Coeff3[] = { 1.45833333333333, 2.5, 3.54166666666667 };
FIS_TYPE fis_gMFO2Coeff4[] = { 2.70833333333333, 3.75, 4.79166666666667 };
FIS_TYPE fis_gMFO2Coeff5[] = { 3.95833333333333, 5, 6.04166666666667 };
FIS_TYPE* fis_gMFO2Coeff[] = { fis_gMFO2Coeff1, fis_gMFO2Coeff2, fis_gMFO2Coeff3, fis_gMFO2Coeff4, fis_gMFO2Coeff5 };
FIS_TYPE** fis_gMFOCoeff[] = { fis_gMFO0Coeff, fis_gMFO1Coeff, fis_gMFO2Coeff };

// Input membership function set
int fis_gMFI0[] = { 0, 0, 0, 0, 0 };
int fis_gMFI1[] = { 0, 0, 0, 0, 0 };
int fis_gMFI2[] = { 0, 0, 0, 0, 0 };
int* fis_gMFI[] = { fis_gMFI0, fis_gMFI1, fis_gMFI2};

// Output membership function set
int fis_gMFO0[] = { 0, 0, 0, 0, 0 };
int fis_gMFO1[] = { 0, 0, 0, 0, 0 };
int fis_gMFO2[] = { 0, 0, 0, 0, 0 };
int* fis_gMFO[] = { fis_gMFO0, fis_gMFO1, fis_gMFO2};

// Rule Weights
FIS_TYPE fis_gRWeight[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

// Rule Type
int fis_gRType[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

// Rule Inputs
int fis_gRI0[] = { 1, 1, 1 };
int fis_gRI1[] = { 2, 1, 1 };
int fis_gRI2[] = { 3, 1, 1 };
int fis_gRI3[] = { 4, 1, 1 };
int fis_gRI4[] = { 5, 1, 1 };
int fis_gRI5[] = { 1, 2, 1 };
int fis_gRI6[] = { 2, 2, 1 };
int fis_gRI7[] = { 3, 2, 1 };
int fis_gRI8[] = { 1, 1, 1 };
int fis_gRI9[] = { 5, 2, 1 };
int fis_gRI10[] = { 1, 3, 1 };
int fis_gRI11[] = { 2, 3, 1 };
int fis_gRI12[] = { 3, 3, 1 };
int fis_gRI13[] = { 4, 3, 1 };
int fis_gRI14[] = { 5, 3, 1 };
int fis_gRI15[] = { 1, 4, 1 };
int fis_gRI16[] = { 2, 4, 1 };
int fis_gRI17[] = { 3, 4, 1 };
int fis_gRI18[] = { 4, 4, 1 };
int fis_gRI19[] = { 5, 4, 1 };
int fis_gRI20[] = { 1, 5, 1 };
int fis_gRI21[] = { 2, 5, 1 };
int fis_gRI22[] = { 3, 5, 1 };
int fis_gRI23[] = { 4, 5, 1 };
int fis_gRI24[] = { 5, 5, 1 };
int fis_gRI25[] = { 1, 1, 2 };
int fis_gRI26[] = { 2, 1, 2 };
int fis_gRI27[] = { 3, 1, 2 };
int fis_gRI28[] = { 4, 1, 2 };
int fis_gRI29[] = { 5, 1, 2 };
int fis_gRI30[] = { 1, 2, 2 };
int fis_gRI31[] = { 2, 2, 2 };
int fis_gRI32[] = { 3, 2, 2 };
int fis_gRI33[] = { 4, 2, 2 };
int fis_gRI34[] = { 5, 2, 2 };
int fis_gRI35[] = { 1, 3, 2 };
int fis_gRI36[] = { 2, 3, 2 };
int fis_gRI37[] = { 3, 3, 2 };
int fis_gRI38[] = { 4, 3, 2 };
int fis_gRI39[] = { 5, 3, 2 };
int fis_gRI40[] = { 1, 4, 2 };
int fis_gRI41[] = { 2, 4, 2 };
int fis_gRI42[] = { 3, 4, 2 };
int fis_gRI43[] = { 4, 4, 2 };
int fis_gRI44[] = { 5, 4, 2 };
int fis_gRI45[] = { 1, 5, 2 };
int fis_gRI46[] = { 2, 5, 2 };
int fis_gRI47[] = { 3, 5, 2 };
int fis_gRI48[] = { 4, 5, 2 };
int fis_gRI49[] = { 5, 5, 2 };
int fis_gRI50[] = { 1, 1, 3 };
int fis_gRI51[] = { 2, 1, 3 };
int fis_gRI52[] = { 3, 1, 3 };
int fis_gRI53[] = { 4, 1, 3 };
int fis_gRI54[] = { 5, 1, 3 };
int fis_gRI55[] = { 1, 2, 3 };
int fis_gRI56[] = { 2, 2, 3 };
int fis_gRI57[] = { 3, 2, 3 };
int fis_gRI58[] = { 4, 2, 3 };
int fis_gRI59[] = { 5, 2, 3 };
int fis_gRI60[] = { 1, 3, 3 };
int fis_gRI61[] = { 2, 3, 3 };
int fis_gRI62[] = { 3, 3, 3 };
int fis_gRI63[] = { 4, 3, 3 };
int fis_gRI64[] = { 5, 3, 3 };
int fis_gRI65[] = { 1, 4, 3 };
int fis_gRI66[] = { 2, 4, 3 };
int fis_gRI67[] = { 3, 4, 3 };
int fis_gRI68[] = { 4, 4, 3 };
int fis_gRI69[] = { 5, 4, 3 };
int fis_gRI70[] = { 1, 5, 3 };
int fis_gRI71[] = { 2, 5, 3 };
int fis_gRI72[] = { 3, 5, 3 };
int fis_gRI73[] = { 4, 5, 3 };
int fis_gRI74[] = { 5, 5, 3 };
int fis_gRI75[] = { 1, 1, 4 };
int fis_gRI76[] = { 2, 1, 4 };
int fis_gRI77[] = { 3, 1, 4 };
int fis_gRI78[] = { 4, 1, 4 };
int fis_gRI79[] = { 5, 1, 4 };
int fis_gRI80[] = { 1, 2, 4 };
int fis_gRI81[] = { 2, 2, 4 };
int fis_gRI82[] = { 3, 2, 4 };
int fis_gRI83[] = { 4, 2, 4 };
int fis_gRI84[] = { 5, 2, 4 };
int fis_gRI85[] = { 1, 3, 4 };
int fis_gRI86[] = { 2, 3, 4 };
int fis_gRI87[] = { 3, 3, 4 };
int fis_gRI88[] = { 4, 3, 4 };
int fis_gRI89[] = { 5, 3, 4 };
int fis_gRI90[] = { 1, 4, 4 };
int fis_gRI91[] = { 2, 4, 4 };
int fis_gRI92[] = { 3, 4, 4 };
int fis_gRI93[] = { 4, 4, 4 };
int fis_gRI94[] = { 5, 4, 4 };
int fis_gRI95[] = { 1, 5, 4 };
int fis_gRI96[] = { 2, 5, 4 };
int fis_gRI97[] = { 3, 5, 4 };
int fis_gRI98[] = { 4, 5, 4 };
int fis_gRI99[] = { 5, 5, 4 };
int fis_gRI100[] = { 1, 1, 5 };
int fis_gRI101[] = { 2, 1, 5 };
int fis_gRI102[] = { 3, 1, 5 };
int fis_gRI103[] = { 4, 1, 5 };
int fis_gRI104[] = { 5, 1, 5 };
int fis_gRI105[] = { 1, 2, 5 };
int fis_gRI106[] = { 2, 2, 5 };
int fis_gRI107[] = { 3, 2, 5 };
int fis_gRI108[] = { 4, 2, 5 };
int fis_gRI109[] = { 5, 2, 5 };
int fis_gRI110[] = { 1, 3, 5 };
int fis_gRI111[] = { 2, 3, 5 };
int fis_gRI112[] = { 3, 3, 5 };
int fis_gRI113[] = { 4, 3, 5 };
int fis_gRI114[] = { 5, 3, 5 };
int fis_gRI115[] = { 1, 4, 5 };
int fis_gRI116[] = { 2, 4, 5 };
int fis_gRI117[] = { 3, 4, 5 };
int fis_gRI118[] = { 4, 4, 5 };
int fis_gRI119[] = { 5, 4, 5 };
int fis_gRI120[] = { 1, 5, 5 };
int fis_gRI121[] = { 2, 5, 5 };
int fis_gRI122[] = { 3, 5, 5 };
int fis_gRI123[] = { 4, 5, 5 };
int fis_gRI124[] = { 5, 5, 5 };
int* fis_gRI[] = { fis_gRI0, fis_gRI1, fis_gRI2, fis_gRI3, fis_gRI4, fis_gRI5, fis_gRI6, fis_gRI7, fis_gRI8, fis_gRI9, fis_gRI10, fis_gRI11, fis_gRI12, fis_gRI13, fis_gRI14, fis_gRI15, fis_gRI16, fis_gRI17, fis_gRI18, fis_gRI19, fis_gRI20, fis_gRI21, fis_gRI22, fis_gRI23, fis_gRI24, fis_gRI25, fis_gRI26, fis_gRI27, fis_gRI28, fis_gRI29, fis_gRI30, fis_gRI31, fis_gRI32, fis_gRI33, fis_gRI34, fis_gRI35, fis_gRI36, fis_gRI37, fis_gRI38, fis_gRI39, fis_gRI40, fis_gRI41, fis_gRI42, fis_gRI43, fis_gRI44, fis_gRI45, fis_gRI46, fis_gRI47, fis_gRI48, fis_gRI49, fis_gRI50, fis_gRI51, fis_gRI52, fis_gRI53, fis_gRI54, fis_gRI55, fis_gRI56, fis_gRI57, fis_gRI58, fis_gRI59, fis_gRI60, fis_gRI61, fis_gRI62, fis_gRI63, fis_gRI64, fis_gRI65, fis_gRI66, fis_gRI67, fis_gRI68, fis_gRI69, fis_gRI70, fis_gRI71, fis_gRI72, fis_gRI73, fis_gRI74, fis_gRI75, fis_gRI76, fis_gRI77, fis_gRI78, fis_gRI79, fis_gRI80, fis_gRI81, fis_gRI82, fis_gRI83, fis_gRI84, fis_gRI85, fis_gRI86, fis_gRI87, fis_gRI88, fis_gRI89, fis_gRI90, fis_gRI91, fis_gRI92, fis_gRI93, fis_gRI94, fis_gRI95, fis_gRI96, fis_gRI97, fis_gRI98, fis_gRI99, fis_gRI100, fis_gRI101, fis_gRI102, fis_gRI103, fis_gRI104, fis_gRI105, fis_gRI106, fis_gRI107, fis_gRI108, fis_gRI109, fis_gRI110, fis_gRI111, fis_gRI112, fis_gRI113, fis_gRI114, fis_gRI115, fis_gRI116, fis_gRI117, fis_gRI118, fis_gRI119, fis_gRI120, fis_gRI121, fis_gRI122, fis_gRI123, fis_gRI124 };

// Rule Outputs
int fis_gRO0[] = { 1, 1, 1 };
int fis_gRO1[] = { 2, 1, 1 };
int fis_gRO2[] = { 3, 1, 1 };
int fis_gRO3[] = { 4, 1, 1 };
int fis_gRO4[] = { 5, 1, 1 };
int fis_gRO5[] = { 1, 2, 1 };
int fis_gRO6[] = { 2, 2, 1 };
int fis_gRO7[] = { 3, 2, 1 };
int fis_gRO8[] = { 1, 1, 1 };
int fis_gRO9[] = { 5, 1, 1 };
int fis_gRO10[] = { 1, 3, 1 };
int fis_gRO11[] = { 2, 3, 1 };
int fis_gRO12[] = { 3, 3, 1 };
int fis_gRO13[] = { 4, 3, 1 };
int fis_gRO14[] = { 5, 3, 1 };
int fis_gRO15[] = { 1, 4, 1 };
int fis_gRO16[] = { 2, 4, 1 };
int fis_gRO17[] = { 3, 4, 1 };
int fis_gRO18[] = { 4, 4, 1 };
int fis_gRO19[] = { 5, 4, 1 };
int fis_gRO20[] = { 1, 5, 1 };
int fis_gRO21[] = { 2, 5, 1 };
int fis_gRO22[] = { 3, 5, 1 };
int fis_gRO23[] = { 4, 5, 1 };
int fis_gRO24[] = { 5, 5, 1 };
int fis_gRO25[] = { 1, 1, 2 };
int fis_gRO26[] = { 2, 1, 2 };
int fis_gRO27[] = { 3, 1, 2 };
int fis_gRO28[] = { 4, 1, 2 };
int fis_gRO29[] = { 5, 1, 2 };
int fis_gRO30[] = { 1, 2, 2 };
int fis_gRO31[] = { 2, 2, 2 };
int fis_gRO32[] = { 3, 2, 2 };
int fis_gRO33[] = { 4, 2, 2 };
int fis_gRO34[] = { 5, 2, 2 };
int fis_gRO35[] = { 1, 3, 2 };
int fis_gRO36[] = { 2, 3, 2 };
int fis_gRO37[] = { 3, 3, 2 };
int fis_gRO38[] = { 4, 3, 2 };
int fis_gRO39[] = { 5, 3, 2 };
int fis_gRO40[] = { 1, 4, 2 };
int fis_gRO41[] = { 2, 4, 2 };
int fis_gRO42[] = { 3, 4, 2 };
int fis_gRO43[] = { 4, 4, 2 };
int fis_gRO44[] = { 5, 4, 2 };
int fis_gRO45[] = { 1, 5, 2 };
int fis_gRO46[] = { 2, 5, 2 };
int fis_gRO47[] = { 3, 5, 2 };
int fis_gRO48[] = { 4, 5, 2 };
int fis_gRO49[] = { 5, 5, 2 };
int fis_gRO50[] = { 1, 1, 3 };
int fis_gRO51[] = { 2, 1, 3 };
int fis_gRO52[] = { 3, 1, 3 };
int fis_gRO53[] = { 4, 1, 3 };
int fis_gRO54[] = { 5, 1, 3 };
int fis_gRO55[] = { 1, 2, 3 };
int fis_gRO56[] = { 2, 2, 3 };
int fis_gRO57[] = { 3, 2, 3 };
int fis_gRO58[] = { 4, 2, 3 };
int fis_gRO59[] = { 5, 2, 3 };
int fis_gRO60[] = { 1, 3, 3 };
int fis_gRO61[] = { 2, 3, 3 };
int fis_gRO62[] = { 3, 3, 3 };
int fis_gRO63[] = { 4, 3, 3 };
int fis_gRO64[] = { 5, 3, 3 };
int fis_gRO65[] = { 1, 4, 3 };
int fis_gRO66[] = { 2, 4, 3 };
int fis_gRO67[] = { 3, 4, 3 };
int fis_gRO68[] = { 4, 4, 3 };
int fis_gRO69[] = { 5, 4, 3 };
int fis_gRO70[] = { 1, 5, 3 };
int fis_gRO71[] = { 2, 5, 3 };
int fis_gRO72[] = { 3, 5, 3 };
int fis_gRO73[] = { 4, 5, 3 };
int fis_gRO74[] = { 5, 5, 3 };
int fis_gRO75[] = { 1, 1, 4 };
int fis_gRO76[] = { 2, 1, 4 };
int fis_gRO77[] = { 3, 1, 4 };
int fis_gRO78[] = { 4, 1, 4 };
int fis_gRO79[] = { 4, 1, 4 };
int fis_gRO80[] = { 1, 2, 4 };
int fis_gRO81[] = { 2, 2, 4 };
int fis_gRO82[] = { 3, 2, 4 };
int fis_gRO83[] = { 4, 2, 4 };
int fis_gRO84[] = { 5, 2, 4 };
int fis_gRO85[] = { 1, 3, 4 };
int fis_gRO86[] = { 2, 3, 4 };
int fis_gRO87[] = { 3, 3, 4 };
int fis_gRO88[] = { 4, 3, 4 };
int fis_gRO89[] = { 5, 3, 4 };
int fis_gRO90[] = { 1, 4, 4 };
int fis_gRO91[] = { 2, 4, 4 };
int fis_gRO92[] = { 3, 4, 4 };
int fis_gRO93[] = { 4, 4, 4 };
int fis_gRO94[] = { 5, 4, 4 };
int fis_gRO95[] = { 1, 5, 4 };
int fis_gRO96[] = { 2, 5, 4 };
int fis_gRO97[] = { 3, 5, 4 };
int fis_gRO98[] = { 4, 5, 4 };
int fis_gRO99[] = { 5, 5, 4 };
int fis_gRO100[] = { 1, 1, 5 };
int fis_gRO101[] = { 2, 1, 5 };
int fis_gRO102[] = { 3, 1, 5 };
int fis_gRO103[] = { 4, 1, 5 };
int fis_gRO104[] = { 5, 1, 5 };
int fis_gRO105[] = { 1, 2, 5 };
int fis_gRO106[] = { 2, 2, 5 };
int fis_gRO107[] = { 3, 2, 5 };
int fis_gRO108[] = { 2, 2, 5 };
int fis_gRO109[] = { 5, 2, 5 };
int fis_gRO110[] = { 1, 3, 5 };
int fis_gRO111[] = { 2, 3, 5 };
int fis_gRO112[] = { 3, 3, 5 };
int fis_gRO113[] = { 4, 3, 5 };
int fis_gRO114[] = { 5, 3, 5 };
int fis_gRO115[] = { 1, 4, 5 };
int fis_gRO116[] = { 2, 4, 5 };
int fis_gRO117[] = { 3, 4, 5 };
int fis_gRO118[] = { 4, 4, 5 };
int fis_gRO119[] = { 5, 4, 5 };
int fis_gRO120[] = { 1, 5, 5 };
int fis_gRO121[] = { 2, 5, 5 };
int fis_gRO122[] = { 3, 5, 5 };
int fis_gRO123[] = { 4, 5, 5 };
int fis_gRO124[] = { 5, 5, 5 };
int* fis_gRO[] = { fis_gRO0, fis_gRO1, fis_gRO2, fis_gRO3, fis_gRO4, fis_gRO5, fis_gRO6, fis_gRO7, fis_gRO8, fis_gRO9, fis_gRO10, fis_gRO11, fis_gRO12, fis_gRO13, fis_gRO14, fis_gRO15, fis_gRO16, fis_gRO17, fis_gRO18, fis_gRO19, fis_gRO20, fis_gRO21, fis_gRO22, fis_gRO23, fis_gRO24, fis_gRO25, fis_gRO26, fis_gRO27, fis_gRO28, fis_gRO29, fis_gRO30, fis_gRO31, fis_gRO32, fis_gRO33, fis_gRO34, fis_gRO35, fis_gRO36, fis_gRO37, fis_gRO38, fis_gRO39, fis_gRO40, fis_gRO41, fis_gRO42, fis_gRO43, fis_gRO44, fis_gRO45, fis_gRO46, fis_gRO47, fis_gRO48, fis_gRO49, fis_gRO50, fis_gRO51, fis_gRO52, fis_gRO53, fis_gRO54, fis_gRO55, fis_gRO56, fis_gRO57, fis_gRO58, fis_gRO59, fis_gRO60, fis_gRO61, fis_gRO62, fis_gRO63, fis_gRO64, fis_gRO65, fis_gRO66, fis_gRO67, fis_gRO68, fis_gRO69, fis_gRO70, fis_gRO71, fis_gRO72, fis_gRO73, fis_gRO74, fis_gRO75, fis_gRO76, fis_gRO77, fis_gRO78, fis_gRO79, fis_gRO80, fis_gRO81, fis_gRO82, fis_gRO83, fis_gRO84, fis_gRO85, fis_gRO86, fis_gRO87, fis_gRO88, fis_gRO89, fis_gRO90, fis_gRO91, fis_gRO92, fis_gRO93, fis_gRO94, fis_gRO95, fis_gRO96, fis_gRO97, fis_gRO98, fis_gRO99, fis_gRO100, fis_gRO101, fis_gRO102, fis_gRO103, fis_gRO104, fis_gRO105, fis_gRO106, fis_gRO107, fis_gRO108, fis_gRO109, fis_gRO110, fis_gRO111, fis_gRO112, fis_gRO113, fis_gRO114, fis_gRO115, fis_gRO116, fis_gRO117, fis_gRO118, fis_gRO119, fis_gRO120, fis_gRO121, fis_gRO122, fis_gRO123, fis_gRO124 };

// Input range Min
FIS_TYPE fis_gIMin[] = { 0, 0, 0 };

// Input range Max
FIS_TYPE fis_gIMax[] = { 360, 360, 360 };

// Output range Min
FIS_TYPE fis_gOMin[] = { 0, 0, 0 };

// Output range Max
FIS_TYPE fis_gOMax[] = { 5, 5, 5 };

//***********************************************************************
// Data dependent support functions for Fuzzy Inference System           
//***********************************************************************
FIS_TYPE fis_MF_out(FIS_TYPE** fuzzyRuleSet, FIS_TYPE x, int o)
{
    FIS_TYPE mfOut;
    int r;

    for (r = 0; r < fis_gcR; ++r)
    {
        int index = fis_gRO[r][o];
        if (index > 0)
        {
            index = index - 1;
            mfOut = (fis_gMF[fis_gMFO[o][index]])(x, fis_gMFOCoeff[o][index]);
        }
        else if (index < 0)
        {
            index = -index - 1;
            mfOut = 1 - (fis_gMF[fis_gMFO[o][index]])(x, fis_gMFOCoeff[o][index]);
        }
        else
        {
            mfOut = 0;
        }

        fuzzyRuleSet[0][r] = fis_min(mfOut, fuzzyRuleSet[1][r]);
    }
    return fis_array_operation(fuzzyRuleSet[0], fis_gcR, fis_max);
}

FIS_TYPE fis_defuzz_centroid(FIS_TYPE** fuzzyRuleSet, int o)
{
    FIS_TYPE step = (fis_gOMax[o] - fis_gOMin[o]) / (FIS_RESOLUSION - 1);
    FIS_TYPE area = 0;
    FIS_TYPE momentum = 0;
    FIS_TYPE dist, slice;
    int i;

    // calculate the area under the curve formed by the MF outputs
    for (i = 0; i < FIS_RESOLUSION; ++i){
        dist = fis_gOMin[o] + (step * i);
        slice = step * fis_MF_out(fuzzyRuleSet, dist, o);
        area += slice;
        momentum += slice*dist;
    }

    return ((area == 0) ? ((fis_gOMax[o] + fis_gOMin[o]) / 2) : (momentum / area));
}

//***********************************************************************
// Fuzzy Inference System                                                
//***********************************************************************
void fis_evaluate()
{
    FIS_TYPE fuzzyInput0[] = { 0, 0, 0, 0, 0 };
    FIS_TYPE fuzzyInput1[] = { 0, 0, 0, 0, 0 };
    FIS_TYPE fuzzyInput2[] = { 0, 0, 0, 0, 0 };
    FIS_TYPE* fuzzyInput[fis_gcI] = { fuzzyInput0, fuzzyInput1, fuzzyInput2};
    FIS_TYPE fuzzyOutput0[] = { 0, 0, 0, 0, 0 };
    FIS_TYPE fuzzyOutput1[] = { 0, 0, 0, 0, 0 };
    FIS_TYPE fuzzyOutput2[] = { 0, 0, 0, 0, 0 };
    FIS_TYPE* fuzzyOutput[fis_gcO] = { fuzzyOutput0, fuzzyOutput1, fuzzyOutput2};
    FIS_TYPE fuzzyRules[fis_gcR] = { 0 };
    FIS_TYPE fuzzyFires[fis_gcR] = { 0 };
    FIS_TYPE* fuzzyRuleSet[] = { fuzzyRules, fuzzyFires };
    FIS_TYPE sW = 0;

    // Transforming input to fuzzy Input
    int i, j, r, o;
    for (i = 0; i < fis_gcI; ++i)
    {
        for (j = 0; j < fis_gIMFCount[i]; ++j)
        {
            fuzzyInput[i][j] =
                (fis_gMF[fis_gMFI[i][j]])(g_fisInput[i], fis_gMFICoeff[i][j]);
        }
    }

    int index = 0;
    for (r = 0; r < fis_gcR; ++r)
    {
        if (fis_gRType[r] == 1)
        {
            fuzzyFires[r] = FIS_MAX;
            for (i = 0; i < fis_gcI; ++i)
            {
                index = fis_gRI[r][i];
                if (index > 0)
                    fuzzyFires[r] = fis_min(fuzzyFires[r], fuzzyInput[i][index - 1]);
                else if (index < 0)
                    fuzzyFires[r] = fis_min(fuzzyFires[r], 1 - fuzzyInput[i][-index - 1]);
                else
                    fuzzyFires[r] = fis_min(fuzzyFires[r], 1);
            }
        }
        else
        {
            fuzzyFires[r] = FIS_MIN;
            for (i = 0; i < fis_gcI; ++i)
            {
                index = fis_gRI[r][i];
                if (index > 0)
                    fuzzyFires[r] = fis_max(fuzzyFires[r], fuzzyInput[i][index - 1]);
                else if (index < 0)
                    fuzzyFires[r] = fis_max(fuzzyFires[r], 1 - fuzzyInput[i][-index - 1]);
                else
                    fuzzyFires[r] = fis_max(fuzzyFires[r], 0);
            }
        }

        fuzzyFires[r] = fis_gRWeight[r] * fuzzyFires[r];
        sW += fuzzyFires[r];
    }

    if (sW == 0)
    {
        for (o = 0; o < fis_gcO; ++o)
        {
            g_fisOutput[o] = ((fis_gOMax[o] + fis_gOMin[o]) / 2);
        }
    }
    else
    {
        for (o = 0; o < fis_gcO; ++o)
        {
            g_fisOutput[o] = fis_defuzz_centroid(fuzzyRuleSet, o);
        }
    }
}