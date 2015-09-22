
//-----------------------------------------------------------------
char byteGPS=0;
char linea[300] = "";
char comandoGPR[7] = "$GPRMC";
int inicio=0, conta=0, cont=0, bien=0, indices[13];
//-----------------------------------------------------------------
long latitud=0; 
long longitud=0;
long dlatitud=34239444;
long dlongitud=118450506;
unsigned int cursoDestino =0;
unsigned int distancia =0;
int velocidad =0; 
int cursoReal = 0;
//-----------------------------------------------------------------

void setup() {
  Serial.begin(115200);
  for (int i=0;i<300;i++){ linea[i]=' '; }   
}

void loop() {
	//-----------------------------------------------------------------
	if(Serial.available() <= 0) { delay(10); } 
	if(Serial.available() > 0 ) {
		//-----------------------------------------------------------------
		byteGPS=Serial.read(); //Serial.print(byteGPS);
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
			if(bien==6){ converNMEA(); Navi(); }
			//-----------------------------------------------------------------
			cursoDestino = 0; latitud=0; longitud=0; velocidad=0; cursoReal=0; conta=0;
			for (int i=0;i<300;i++){ linea[i]=' '; }
			//-----------------------------------------------------------------
		}
	}
}




void Navi()
{
	//-----------------------------------------------------------------
	long diflat=0; long diflon=0; int correccion =0; int cuadrante =0;
	//-----------------------------------------------------------------
	diflat=abs(latitud)-abs(dlatitud);
	diflon=abs(longitud)-abs(dlongitud);
	//-----------------------------------------------------------------
	if((diflat <= -1) & (diflon >= 1 )) { cuadrante=1; } // Quadrant =4
	if((diflat >= 1 ) & (diflon >= 1 )) { cuadrante=2; }
	if((diflat >= 1 ) & (diflon <= -1)) { cuadrante=3; }
	if((diflat <= -1) & (diflon <= -1)) { cuadrante=4; }
	//-----------------------------------------------------------------
	// Serial.println(cuadrante);
	cursoDestino=latitud/1000000;
	//-----------------------------------------------------------------
	if(abs(diflat) > abs(diflon)){
		//-----------------------------------------------------------------
		if((cursoDestino >= 1 )&(cursoDestino <= 16)){ correccion=12; } 
		if((cursoDestino >= 17)&(cursoDestino <= 27)){ correccion=11; } 
		if((cursoDestino >= 28)&(cursoDestino <= 37)){ correccion=100;} 
		if((cursoDestino >= 38)&(cursoDestino <= 42)){ correccion=9;  }  
		if((cursoDestino >= 43)&(cursoDestino <= 52)){ correccion=8;  }
		if((cursoDestino >= 53)&(cursoDestino <= 57)){ correccion=7;  }
		if((cursoDestino >= 58)&(cursoDestino <= 62)){ correccion=6;  }
		//-----------------------------------------------------------------
		cursoDestino = abs(diflon)/(abs(diflat)/correccion);
		distancia = ((abs(diflat)/correccion)* sqrt(sq(correccion) + sq(cursoDestino)))/10;
		cursoDestino = (cursoDestino*45)/120;
		//-----------------------------------------------------------------
		switch(cuadrante){
			case 1: cursoDestino= cursoDestino; break;
			case 2: cursoDestino= 180 - cursoDestino; break;
			case 3: cursoDestino= 180 + cursoDestino; break;
			case 4: cursoDestino= 360 - cursoDestino; break;
		}
		//-----------------------------------------------------------------
	}else{
		//-----------------------------------------------------------------
		if((cursoDestino >= 1 )&(cursoDestino <= 16)){ correccion=12; }
		if((cursoDestino >= 17)&(cursoDestino <= 27)){ correccion=13; }
		if((cursoDestino >= 28)&(cursoDestino <= 32)){ correccion=14; }
		if((cursoDestino >= 33)&(cursoDestino <= 37)){ correccion=150;}   
		if((cursoDestino >= 38)&(cursoDestino <= 42)){ correccion=16; }
		if((cursoDestino >= 43)&(cursoDestino <= 47)){ correccion=17; }
		if((cursoDestino >= 48)&(cursoDestino <= 52)){ correccion=19; } 
		if((cursoDestino >= 53)&(cursoDestino <= 57)){ correccion=21; }
		if((cursoDestino >= 58)&(cursoDestino <= 62)){ correccion=24; }
		//-----------------------------------------------------------------
		cursoDestino =abs(diflat)/(abs(diflon)/correccion);
		distancia = ((abs(diflon)/correccion) * sqrt(sq(correccion) + sq(cursoDestino)))/10;
		cursoDestino = (cursoDestino*45)/120; 
		//-----------------------------------------------------------------
		switch(cuadrante)
		{
			case 1: cursoDestino= 90  - cursoDestino; break;
			case 2: cursoDestino= 90  + cursoDestino; break;
			case 3: cursoDestino= 270 - cursoDestino; break;
			case 4: cursoDestino= 270 + cursoDestino; break;
		}
		//-----------------------------------------------------------------
	}




	/*********************************************************************************************
	* This part generate a NMEA string sentence:
	* $JORDI,Course to Destination, Distance, Speed, Latitude,Longitud, Real Course,Dif Lat, Dif Long, Quadrant, Correction
	* This string is use by the ground station (Labview)
	*********************************************************************************************/

	Serial.println("");
	Serial.print("$JORDI,");
	Serial.print(cursoDestino); //Listo impre la cursoDestino, cursoReal lo que sea que nos llevar a nuestro destino, entre 1 a 360 grados. 
	Serial.print(",");
	Serial.print(distancia); //Impreme la distancia en .10 millas
	Serial.print(",");
	Serial.print(velocidad); //Imprime la velocidad
	Serial.print(",");
	Serial.print(latitud);
	Serial.print(","); 
	Serial.print(longitud);
	Serial.print(","); 
	Serial.print(cursoReal);
	Serial.print(",");  
	Serial.print(diflat); //Solo con fines de depuracion
	Serial.print(",");
	Serial.print(diflon); //Solo con fines de depuracion
	Serial.print(",");
	Serial.print(cuadrante); //Solo con fines de depuracion
	Serial.print(",");
	Serial.print(correccion); //Solo con fines de depuracion
}  


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
					case 2: 
						latitud=latitud+((linea[j+1]-48)*(conver/10));
						conver=conver/10;
						break;
					//-----------------------------------------------------------------						
					case 3: 
						if(linea[j+1] == 83) { latitud=(latitud)*-1; }
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
					case 7:                                            // Converts the real Course String in intriger degrees
					cursoReal=cursoReal+((linea[j+1]-48)*(conver/1000000));
					conver=conver/10;
					break;
        }
      }
    }

  }
  latitud = ((latitud/1000000)*1000000)+((latitud % 1000000) / .6);             // Converts degrees,minutes to decimal degrees
  longitud = ((longitud/1000000)*1000000)+((longitud % 1000000) / .6);     // Same


} 



