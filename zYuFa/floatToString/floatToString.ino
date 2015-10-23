#include "floatToString.h"  //set to whatever is the location of floatToStrig

 void setup() {

 Serial.begin(9600);

 char buffer[25]; // just give it plenty to write out any values you want to test
 // ==========================================
 // now run a series on the floatToString function

 // looking at the precision of the float

 Serial.println("floatToString(buffer, 1000000.321 , 5);");
 Serial.println(floatToString(buffer, 1000000.321, 5)); 
 Serial.println();
 Serial.println("floatToString(buffer, 100000.321 , 5);");
 Serial.println(floatToString(buffer, 100000.321, 5)); 
 Serial.println();
 Serial.println("floatToString(buffer, 10000.321 , 5);");
 Serial.println(floatToString(buffer, 10000.321, 5)); 
 Serial.println();  
 Serial.println("floatToString(buffer, 1000.321 , 5);");
 Serial.println(floatToString(buffer, 1000.321, 5)); 
 Serial.println();
 Serial.println("floatToString(buffer, 100.321 , 5);");
 Serial.println(floatToString(buffer, 100.321, 5)); 
 Serial.println();

 // ==========================================
 // looking at effect of changing precision
 Serial.println("floatToString(buffer, 100000.321 , 6);");
 Serial.println(floatToString(buffer, 100000.321, 6));
 Serial.println();
 Serial.println("floatToString(buffer, 100000.321 , 7);");
 Serial.println(floatToString(buffer, 100000.321, 7));
 Serial.println();
 Serial.println("floatToString(buffer, 100000.321 , 8);");
 Serial.println(floatToString(buffer, 100000.321, 8));
 Serial.println();
 Serial.println("floatToString(buffer, 100000.321 , 9);");
 Serial.println(floatToString(buffer, 100000.321, 9));
 Serial.println();


 // ==========================================

 // check negatives and rounding, and some edge cases
 Serial.println("floatToString(buffer, -5004.321 , 5);");
 Serial.println(floatToString(buffer, -5004.321 , 5)); 
 Serial.println();

 Serial.println("floatToString(buffer, 99.999 , 3); ");
 Serial.println(floatToString(buffer, 99.999 , 3)); 
 Serial.println();

 Serial.println("floatToString(buffer, 100, 1);");
 Serial.println(floatToString(buffer, 100, 1)); 
 Serial.println();

 Serial.println("floatToString(buffer, -100.999 , 1);");
 Serial.println(floatToString(buffer, -100.999 , 1)); 
 Serial.println();

 Serial.println("floatToString(buffer, -54.321 , 0);");
 Serial.println(floatToString(buffer, -54.321 , 0)); 
 Serial.println();

 Serial.println("floatToString(buffer, 0.321 , 5);");
 Serial.println(floatToString(buffer, 0.321 , 5));    
 Serial.println();

 Serial.println("floatToString(buffer, -1.0001 , 5);");
 Serial.println(floatToString(buffer, -1.0001 , 5));   
 Serial.println();

 Serial.println("floatToString(buffer, -0.000001 , 5);");
 Serial.println(floatToString(buffer, -0.000001 , 5)); 
 Serial.println();

 Serial.println("floatToString(buffer, 0.000001 , 5);");
 Serial.println(floatToString(buffer, 0.000001 , 5)); 
 Serial.println();

 Serial.println("floatToString(buffer, -0.00001 , 5);");
 Serial.println(floatToString(buffer, -0.00001 , 5)); 
 Serial.println();

 Serial.println("floatToString(buffer, 0.000099 , 5);");
 Serial.println(floatToString(buffer, 0.000099 , 5)); 
 Serial.println();

 // alternative technique that depends on <stdio.h>
 //Serial.println("Serial.println(dtostrf(-1.0001, 2, 5, s));");
 //char s[32];
 // Serial.println(dtostrf(-1.0001, 2, 5, s)));

 delay(1000);
 Serial.println();

 }

 void loop() {
 }
