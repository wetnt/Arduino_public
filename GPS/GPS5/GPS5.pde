 #include <string.h>
 #include <ctype.h>
 #include <NewSoftSerial.h>
 
 
 char GPSDate[7] = "110412";
 char GPSTime[11] = "163115.000";
 char GPSStatus[2] = "A";
 char GPSLat[10] = "3958.8450"; 
 char GPSLNS[2] = "N";
 char GPSLon[11] = "11621.4676"; 
 char GPSLEW[2] = "E";
 char GPSVel[6] = "0.00";
 char GPSHead[6] = "000";

 //---------------------------------------------------- 
 NewSoftSerial nss(2, 3);
 //----------------------------------------------------
 char linea[300] = "", comandoGPR[7] = "$GPRMC";
 int byteGPS=-1, cont=0, bien=0, conta=0, indices[13];
 //----------------------------------------------------
 

void setup()
{
  Serial.begin(9600);
  nss.begin(9600);
  delay(1000);  
  for (int i=0;i<300;i++){ linea[i]=' '; }   
}

void loop()
{
   // GPSRead();
   /* GPSShow(); */

   while (nss.available())
   {
	GPSRead();
  }   
   
}

 
 
 void GPSRead()
 {
	byteGPS = nss.read();
	if (byteGPS == -1) {
		delay(100); 
	} else {
		//----------------------------------------------------
		linea[conta] = byteGPS; conta++;
		//----------------------------------------------------
		//Serial.print(byteGPS, BYTE); 
		//----------------------------------------------------
		
		if (byteGPS==13){
			//----------------------------------------------------
			cont=0; bien=0;
			for (int i=1;i<7;i++){ if (linea[i]==comandoGPR[i-1]){ bien++; } }
			//----------------------------------------------------
			if(bien==6){
				for (int i=0;i<300;i++){
					if (linea[i]==','){ indices[cont]=i; cont++; }
					if (linea[i]=='*'){ indices[12]=i; cont++; }
				}
				//----------------------------------------------------
				for (int i=0;i<12;i++){
					switch(i){
						case 0 :Serial.print("Time in UTC (HhMmSs): ");break;
						case 1 :Serial.print("Status (A=OK,V=KO): ");break;
						case 2 :Serial.print("Latitude: ");break;
						case 3 :Serial.print("Direction (N/S): ");break;
						case 4 :Serial.print("Longitude: ");break;
						case 5 :Serial.print("Direction (E/W): ");break;
						case 6 :Serial.print("Velocity in knots: ");break;
						case 7 :Serial.print("Heading in degrees: ");break;
						case 8 :Serial.print("Date UTC (DdMmAa): ");break;
						case 9 :Serial.print("Magnetic degrees: ");break;
						case 10 :Serial.print("(E/W): ");break;
						case 11 :Serial.print("Mode: ");break;
						case 12 :Serial.print("Checksum: ");break;
					}
					//----------------------------------------------------
					for (int j=indices[i];j<(indices[i+1]-1);j++){
						Serial.print(linea[j+1]); 
					}
					//----------------------------------------------------
					Serial.println();
					//----------------------------------------------------
				}
				//----------------------------------------------------
				Serial.println("---------------");
				//----------------------------------------------------
			}
			//----------------------------------------------------
			conta=0; for (int i=0;i<300;i++){ linea[i]=' '; }
			//----------------------------------------------------
		}
	}
}
 
 
 
 
 
  void GPSShow()
 {
	Serial.println("----bbbbb-----------");
	Serial.print("Time in UTC (HhMmSs): ");Serial.println(GPSTime);
	Serial.print("Status (A=OK,V=KO): ");Serial.println(GPSStatus);
	Serial.print("Latitude: ");Serial.println(GPSLat);
	Serial.print("Direction (N/S): ");Serial.println(GPSLNS);
	Serial.print("Longitude: ");Serial.println(GPSLon);
	Serial.print("Direction (E/W): ");Serial.println(GPSLEW);
	Serial.print("Velocity in knots: ");Serial.println(GPSVel);
	Serial.print("Heading in degrees: ");Serial.println(GPSHead);
	Serial.print("Date UTC (DdMmAa): ");Serial.println(GPSDate);
	Serial.print("Magnetic degrees: ");Serial.println();
	Serial.print("(E/W): ");Serial.println();
	Serial.print("Mode: ");Serial.println();
	Serial.print("Checksum: ");Serial.println();
	Serial.println("---------------");
 }
