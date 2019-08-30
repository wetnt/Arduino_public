//低功耗、低噪声 3 轴数字地磁传感器,可用于罗盘应用
//https://www.geek-workshop.com/forum.php?mod=viewthread&tid=12694&page=1

#include <Wire.h>
#include "bmm150.h"
#include "bmm150_defs.h"

//#define MagnetcDeclination 4.43 //Shanghai
#define MagnetcDeclination 6.8666667 //Beijing
#define CalThreshold 0

BMM150 bmm = BMM150();
bmm150_mag_data value_offset;
int16_t offsetX, offsetY, offsetZ;
int heading;
int rrr = 15;
int rx1, rx0 = 142;
int ry1, ry0 = 36;
float sx, sy;

void BMM150_setup() {
  lcd_show("BMM150_setup!");
  Wire.begin(0, 26);

  if (bmm.initialize() == BMM150_E_ID_NOT_CONFORM) {
    Serial.println("Chip ID can not read!");
    while (1);
  } else {
    Serial.println("Initialize done!");
  }

  calibrateMag();
}

void BMM150_North_Line() {
  //--------------------------------------------------
  //M5.Lcd.setCursor(0,0,2); M5.Lcd.printf("%03d  \n", heading);
  //--------------------------------------------------
  M5.Lcd.drawLine(rx0, ry0, rx1, ry1, TFT_BLACK);
  M5.Lcd.drawCircle(rx0, ry0, rrr, RED);
  sx = cos(-heading * 0.0174532925); rx1 = sx * rrr + rx0;
  sy = sin(-heading * 0.0174532925); ry1 = sy * rrr + ry0;
  M5.Lcd.drawLine(rx0, ry0, rx1, ry1, TFT_GREEN);
  //--------------------------------------------------
}

void BMM150_loop() {
  int16_t x, y, z; //triple axis data
  getRawData(&x, &y, &z);
  heading = calculateHeading(&x, &y, &z);

  //Print out values of each axis
  //  Serial.print("  x: ");  Serial.print(x);
  //  Serial.print("  y: ");  Serial.print(y);
  //  Serial.print("  z: ");  Serial.print(z);
  //  Serial.print(" headingDegrees: ");
  //  Serial.println( heading );
}

void getRawData(int16_t* x , int16_t* y, int16_t* z)
{
  bmm.read_mag_data();
  *x = bmm.raw_mag_data.raw_datax;
  *y = bmm.raw_mag_data.raw_datay;
  *z = bmm.raw_mag_data.raw_dataz;
}

int calculateHeading(int16_t* x , int16_t* y, int16_t* z)
{
  float headingRadians = atan2((double)((*y) - offsetY), (double)((*x) - offsetX));
  // Correct for when signs are reversed.
  if (headingRadians < 0)
    headingRadians += 2 * PI;

  int headingDegrees = headingRadians * 180 / M_PI;
  headingDegrees += MagnetcDeclination; //the magnetc-declination angle

  headingDegrees -= 90;

  // Check for wrap due to addition of declination.
  if (headingDegrees > 360) headingDegrees -= 360;
  if (headingDegrees < 0)   headingDegrees += 360;

  return headingDegrees;
}

void calibrateMag()
{
  int16_t x, y, z; //triple axis data
  int16_t xMax, xMin, yMax, yMin, zMax, zMin;
  //initialize the variables
  getRawData(&x, &y, &z);
  xMax = xMin = x;
  yMax = yMin = y;
  zMax = zMin = z;
  offsetX = offsetY = offsetZ = 0;

  Serial.println("Starting Calibration......");
  Serial.println("Please turn your device around in 20 seconds");

  //return;

  for (int i = 0; i < 200; i++)
  {
    getRawData(&x, &y, &z);
    //get Max and Min
    // this routine will capture the max and min values of the mag X, Y, and Z data while the
    // compass is being rotated 360 degrees through the level plane and the upright plane.
    // i.e. horizontal and vertical circles.
    // This function should be invoked while making continuous measurements on the magnetometers
    if (x > xMax) xMax = x;
    if (x < xMin) xMin = x;
    if (y > yMax) yMax = y;
    if (y < yMin) yMin = y;
    if (z > zMax) zMax = z;
    if (z < zMin) zMin = z;

    delay(100);

    if (i % 10 == 0) {
      Serial.print(xMax);Serial.print(" ");Serial.println(xMin);
      M5.Lcd.setCursor(20, 24, 4);  M5.Lcd.printf("M:  %03d  %03d      \n", xMax, xMin);
    }
  }
  //compute offsets
  if (abs(xMax - xMin) > CalThreshold ) offsetX = (xMax + xMin) / 2;
  if (abs(yMax - yMin) > CalThreshold ) offsetY = (yMax + yMin) / 2;
  if (abs(zMax - zMin) > CalThreshold ) offsetZ = (zMax + zMin) / 2;

  Serial.print(" offsetX:");  Serial.print("");  Serial.print(offsetX);
  Serial.print(" offsetY:");  Serial.print("");  Serial.print(offsetY);
  Serial.print(" offsetZ:");  Serial.print("");  Serial.println(offsetZ);

  delay(3000);
}
