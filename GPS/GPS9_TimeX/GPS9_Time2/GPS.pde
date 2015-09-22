//-----------------------------------------------------------------
//$GPRMC,160546.000,A,3958.8450,N,11621.4676,E,0.00,,110412,,*12
//-----------------------------------------------------------------
char byteGPS=0;
char linea[300] = "";
char comandoGPR[7] = "$GPRMC";
int inicio=0, conta=0, cont=0, bien=0, indices[13];
int TimeCharN = -1, DateCharN = -1;
//-----------------------------------------------------------------
long latitude=0, longitud=0, velocidad=0, cursoReal=0;
int YY,MT,DD,HH,MM,SS,MS;
//-----------------------------------------------------------------
void GpsInt(int TimeZone)
{
    myGps.TimeZone = TimeZone;
    for (int i=0;i<300;i++){ linea[i]=' '; }  
}

void GpsRead()
{
	//-----------------------------------------------------------------
	if(Serial.available() <= 0) { delay(0); } 
	if(Serial.available() > 0 ) {
		//-----------------------------------------------------------------
		byteGPS=Serial.read(); 
//Serial.print(byteGPS);
		linea[conta]=byteGPS; conta++; 
		//-----------------------------------------------------------------
		if(byteGPS==13){
			//-----------------------------------------------------------------
			cont=0; bien=0;
			for (int i=1;i<7;i++){
				if(linea[i]==comandoGPR[i-1]){ bien++; }
				if(bien==6){ inicio=i-6; }
			}
			//-----------------------------------------------------------------
			if(bien==6){ converNMEA(); }
			//-----------------------------------------------------------------
			latitude=0; longitud=0; velocidad=0; cursoReal=0; conta=0;
			TimeCharN = -1; DateCharN = -1;
			YY=0;MT=0;DD=0;HH=0;MM=0;SS=0;MS=0;
			for (int i=0;i<300;i++){ linea[i]=' '; }
			//-----------------------------------------------------------------
		}
	}
	//-----------------------------------------------------------------	
}

//$GPRMC,160546.000,A,3958.8450,N,11621.4676,E,0.00,,110412,,*12
void converNMEA()
{
	//-----------------------------------------------------------------
	for (int i=inicio;i<300;i++){
		if (linea[i]==','){ indices[cont]=i; cont++; }
	}
	//-----------------------------------------------------------------
	for (int i=0;i<11;i++){
		long conver = 100000000;
		for (int j=indices[i];j<(indices[i+1]-1);j++) {
			if(linea[j+1] != 46){
				switch(i){
					//-----------------------------------------------------------------
					case 0: 
						//-----------------------------------------------------------------
						TimeCharN++;
						switch(TimeCharN){
							case 0: HH = (linea[j+1]-48)*10;break;
							case 1: HH = HH+(linea[j+1]-48);break;
							case 2: MM = (linea[j+1]-48)*10;break;
							case 3: MM = MM+(linea[j+1]-48);break;
							case 4: SS = (linea[j+1]-48)*10;break;
							case 5: SS = SS+(linea[j+1]-48);break;
							case 7: MS = MS+(linea[j+1]-48)*100;break;
							case 8: MS = MS+(linea[j+1]-48)*10; break;
							case 9: MS = MS+(linea[j+1]-48);    break;
						}
						break;
					//-----------------------------------------------------------------
					case 1: 
						myGps.key = linea[j+1];
						break;
					//-----------------------------------------------------------------
					case 2: 
						latitude=latitude+((linea[j+1]-48)*(conver/10));
						conver=conver/10;
						break;
					//-----------------------------------------------------------------						
					case 3: 
						if(linea[j+1] == 83) { latitude=(latitude)*-1; }
						break;
					//-----------------------------------------------------------------
					case 4:
						longitud=longitud+((linea[j+1]-48)*conver); 
						conver=conver/10;
						break;
					//-----------------------------------------------------------------
					case 5:
						if(linea[j+1] == 87){ longitud=(longitud)*-1; } 
						break;
					//-----------------------------------------------------------------
					case 6:
						velocidad=velocidad+((linea[j+1]-48)*(conver/1000000));
						conver=conver/10;
						break;
					//-----------------------------------------------------------------
					case 7:
						cursoReal=cursoReal+((linea[j+1]-48)*(conver/1000000));
						conver=conver/10;
						break;
					//-----------------------------------------------------------------
					case 8: 
						DateCharN++;
						switch(DateCharN){
							case 0: DD = (linea[j+1]-48)*10;break;
							case 1: DD = DD+(linea[j+1]-48);break;
							case 2: MT = (linea[j+1]-48)*10;break;
							case 3: MT = MT+(linea[j+1]-48);break;
							case 4: YY = (linea[j+1]-48)*10;break;
							case 5: YY = YY+(linea[j+1]-48);break;
						}
						break;
					//-----------------------------------------------------------------
        }
      }
    }

  }
  //-----------------------------------------------------------------
  latitude = ((latitude/1000000)*1000000)+((latitude % 1000000) / .6);
  longitud = ((longitud/1000000)*1000000)+((longitud % 1000000) / .6);
  myGps.lat = (float)latitude/1000000;
  myGps.lon = (float)longitud/1000000;
  //-----------------------------------------------------------------  
  myGps.YY = YY;  myGps.MT = MT;  myGps.DD = DD;  
  myGps.MM = MM;  myGps.SS = SS;  myGps.MS = MS;  
  myGps.HH = (int)HH + myGps.TimeZone;
  if(myGps.HH>=24){ myGps.HH = myGps.HH-24; myGps.DD = myGps.DD + 1; }
  //-----------------------------------------------------------------
  myGps.vel = velocidad; myGps.age = cursoReal;
  //-----------------------------------------------------------------
} 

