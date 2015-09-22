//-----------------------------------------------------------------
char byteGPS=0;
char linea[300] = "";
char comandoGPR[7] = "$GPRMC";
int inicio=0, conta=0, cont=0, bien=0, indices[13];
//-----------------------------------------------------------------
int TimeCharN = -1;int DateCharN = -1;
//-----------------------------------------------------------------
//$GPRMC,160546.000,A,3958.8450,N,11621.4676,E,0.00,,110412,,*12
char csYY[3]="00";char csMT[3]="00";char csDD[3]="00";
char csHH[3]="00";char csMM[3]="00";char csSS[3]="00";char csMS[4]="000";
long latitude=0; 
long longitud=0;
//-----------------------------------------------------------------
void GpsInt()
{
    for (int i=0;i<300;i++){ linea[i]=' '; }  
}

void GpsRead()
{
	//-----------------------------------------------------------------
	if(nss.available() <= 0) { delay(10); } 
	if(nss.available() > 0 ) {
		//-----------------------------------------------------------------
		byteGPS=nss.read(); 
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
			if(bien==6){ converNMEA(); GpsShow();}
			//-----------------------------------------------------------------
			latitude=0; longitud=0; velocidad=0; cursoReal=0; conta=0;
			TimeCharN = -1;
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
							case 0: csHH[0] = linea[j+1];break;
							case 1: csHH[1] = linea[j+1];break;
							case 2: csMM[0] = linea[j+1];break;
							case 3: csMM[1] = linea[j+1];break;
							case 4: csSS[0] = linea[j+1];break;
							case 5: csSS[1] = linea[j+1];break;
							case 7: csMS[0] = linea[j+1];break;
							case 8: csMS[1] = linea[j+1];break;
							case 9: csMS[2] = linea[j+1];break;
						}
						break;
					//-----------------------------------------------------------------
					case 1: 
						GpsKey = linea[j+1];
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
							case 0: csDD[0] = linea[j+1];break;
							case 1: csDD[1] = linea[j+1];break;
							case 2: csMT[0] = linea[j+1];break;
							case 3: csMT[1] = linea[j+1];break;
							case 4: csYY[0] = linea[j+1];break;
							case 5: csYY[1] = linea[j+1];break;
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
  flatitude = (float)latitude/1000000;
  flongitud = (float)longitud/1000000;
  //-----------------------------------------------------------------  
  YY = (csYY[0]-48)*10+(csYY[1]-48);
  MT = (csMT[0]-48)*10+(csMT[1]-48);
  DD = (csDD[0]-48)*10+(csDD[1]-48);  
  HH = (csHH[0]-48)*10+(csHH[1]-48) + TimeZone;
  MM = (csMM[0]-48)*10+(csMM[1]-48);
  SS = (csSS[0]-48)*10+(csSS[1]-48);
  MS = (csMS[0]-48)*10+(csMS[1]-48);
  if(HH>=24){ HH = HH-24; DD = DD + 1; }
  //-----------------------------------------------------------------
} 

