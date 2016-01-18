/**
   Author: Aravinth Panchadcharam
   Email: me@aravinth.info
   Date: 18/01/16.
   Project: Macsxperts Aeroponics Vertical Farming
   Description: DF Robot pH Pro (SEN0169)
*/

#include "aero_ph.h"

aero_ph::aero_ph(Print* _serial)
{
  aero_ph::Serial = _serial;
}

int aero_ph::holaPh() {
  counter++;
  return counter;
}

float aero_ph::getPh() {

  static float pHValue, analogValue, voltage;
  analogValue = 4.0;
  for (int i = 0; i <= 40 ; i ++) {
    pHArray[pHArrayIndex++]  = analogValue + 0.1;
  }
  pHArrayIndex = 0;
  voltage = avergearray(pHArray, ArrayLenth) * 5.0 / 1024;
  pHValue = 3.5 * voltage + Offset;
  return pHValue;
}


double aero_ph::avergearray(int* arr, int number) {
  int i;
  int max, min;
  double avg;
  long amount = 0;
  if (number <= 0) {
    return 0;
  }
  if (number < 5) { //less than 5, calculated directly statistics
    for (i = 0; i < number; i++) {
      amount += arr[i];
    }
    avg = amount / number;
    return avg;
  } else {
    if (arr[0] < arr[1]) {
      min = arr[0]; max = arr[1];
    }
    else {
      min = arr[1]; max = arr[0];
    }
    for (i = 2; i < number; i++) {
      if (arr[i] < min) {
        amount += min;      //arr<min
        min = arr[i];
      } else {
        if (arr[i] > max) {
          amount += max;  //arr>max
          max = arr[i];
        } else {
          amount += arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount / (number - 2);
  }//if
  return avg;
}
