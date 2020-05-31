#include <utility.h>
int iHSV[3];
//h:0-360,s:0.0-1.0,v:0.0-1.0
rgb hsv2rgb(hsv HSV)
{
    rgb RGB;
    double H = HSV.h, S = HSV.s, V = HSV.v,
            P, Q, T,
            fract;

    (H == 360.)?(H = 0.):(H /= 60.);
    fract = H - floor(H);

    P = V*(1. - S);
    Q = V*(1. - S*fract);
    T = V*(1. - S*(1. - fract));

    if      (0. <= H && H < 1.)
        RGB = (rgb){.r = V, .g = T, .b = P};
    else if (1. <= H && H < 2.)
        RGB = (rgb){.r = Q, .g = V, .b = P};
    else if (2. <= H && H < 3.)
        RGB = (rgb){.r = P, .g = V, .b = T};
    else if (3. <= H && H < 4.)
        RGB = (rgb){.r = P, .g = Q, .b = V};
    else if (4. <= H && H < 5.)
        RGB = (rgb){.r = T, .g = P, .b = V};
    else if (5. <= H && H < 6.)
        RGB = (rgb){.r = V, .g = P, .b = Q};
    else
        RGB = (rgb){.r = 0., .g = 0., .b = 0.};

    return RGB;
}

hsv MQTTThingHSVScale(String hsvStr){
    hsv HSV;
    unsigned int i = 0;
    while(hsvStr.indexOf(",")!=-1){
      // take the substring from the start to the first occurence of a comma, convert it to int and save it in the array
      iHSV[i] = hsvStr.substring(0,hsvStr.indexOf(",")).toInt();
      i++; // increment our data counter
      //cut the data string after the first occurence of a comma
      hsvStr = hsvStr.substring(hsvStr.indexOf(",")+1);
    }
    // get the last value out of the string, which as no more commas in it
    iHSV[i] = hsvStr.toInt();    
    HSV.h = iHSV[0];
    HSV.s = (double)iHSV[1] / 100;
    HSV.v = (double)iHSV[2] / 100;
    return HSV;
}