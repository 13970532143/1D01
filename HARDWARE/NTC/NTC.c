#include "NTC.h"
#include "math.h"
const float Rp=10000.0; //10K
const float T2 = (273.15+25.0);;//T2
const float Bx = 3435.0;//B
const float Ka = 273.15;
float Get_Temp(float Rt)
{
    float temp;
    //like this R=5000, T2=273.15+25,B=3470, RT=5000*EXP(3470*(1/T1-1/(273.15+25)),  
    temp = Rt/Rp;
    temp = log(temp);//ln(Rt/Rp)
    temp/=Bx;//ln(Rt/Rp)/B
    temp+=(1/T2);
    temp = 1/(temp);
    temp-=Ka;
    return temp;
}


