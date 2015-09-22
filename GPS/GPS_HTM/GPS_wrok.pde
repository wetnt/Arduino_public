//-----------------------------------------------------------------
char byteGPS=0;
char linea[300] = "";
char comandoGPR[7] = "$GPRMC";
int inicio=0;
int conta=0;
int cont=0;
int bien=0;
int indices[13];
//-----------------------------------------------------------------
long latitud=0;                  // Latitude read by GPS device
long void st=0;                  // lngitude read by GPS device
long dlatitud=39.977;            // Lat destination (Change it)
long dlngitud=116.332;           // Long destination (Change it)
unsigned int cursoDestino =0;    // Course of target destination
unsigned int distancia =0;       // Distance in meter to our objective
int velocidad =0;                // Speed (knots)
int cursoReal = 0;               // Real course of the "airplane", read by GPS
//-----------------------------------------------------------------
void setup() {
	Serial.begin(115200);
	for (int i=0;i<300;i++){ linea[i]=' '; }   
}

void loop() {
	if(Serial.available() <= 0) { delay(10); } 
	if(Serial.available() > 0 ) {
		//-----------------------------------------------------------------
		byteGPS=Serial.read(); //Serial.print(byteGPS);
		linea[conta]=byteGPS; conta++; 
		//-----------------------------------------------------------------
		if(byteGPS==13){
			//-----------------------------------------------------------------
			cont=0; bien=0;
			for(int i=1;i<7;i++){
				if(linea[i]==comandoGPR[i-1]){ bien++; }
				if(bien==6){ inicio=i-6; }
			}
			if(bien==6){ converNMEA(); Navi(); }
			//-----------------------------------------------------------------			
			cursoDestino = 0;
			latitud=0; lngitud=0;
			velocidad=0; cursoReal=0;
			conta=0;                        // Reset buffer
			for (int i=0;i<300;i++){
				linea[i]=' ';             
			}                 
		}
	}
}

void Navi()
{
	long diflat=0; // Latitudes difference
	long diflon=0; // lngitude difference
	int correccion =0; //Correction dûe à l'ovalité de la terrre
	int cuadrante =0; // Quadrant
	
	diflat=abs(latitud)-abs(dlatitud);       // Différence entre la latitude d'origine et celle de destination
	diflon=abs(lngitud)-abs(dlngitud); // Idem pour la lngitude
	
	if((diflat <= -1) & (diflon >= 1))         //Si la diferencia de latitud es negativa y la diferencia de lngitud es positiva..../ - Latitude/+lngitude
	{
		cuadrante=1;                               // Quadrant = 1
	}
	if((diflat >= 1) & (diflon >= 1))          //Si la diferencia de latitud es positiva y la diferencia de lngitud es positiva..../ + Latitude/+lngitude
	{
		cuadrante=2;                              // Quadrant = 2
	}      
	if((diflat >= 1) & (diflon <= -1))        //Si la diferencia de latitud es positiva y la diferencia de lngitud es negativa..../ + Latitude/-lngitude
	{
		cuadrante=3;                              // Quadrant = 3
	}
	if((diflat <= -1) & (diflon <= -1))       //Si la différence de latitude est négative et la différence de lngitude est négative alors - Latitude / - lngitude
	{
		cuadrante=4;                              // Quadrant =4
	}
	
	// Serial.println(cuadrante);                                             //Imprimee el cuadrante Just for debugging
	
	cursoDestino=latitud/1000000;                                       // Filter the decimal degrees to obtain integer
	
	
	if(abs(diflat) > abs(diflon))                                               // Compare latitude and lngitude and choose the correct equation
	{
        if((cursoDestino >= 1)&(cursoDestino <= 16)){           // If the airplane position is in the degrees 1 to 16 then correction = 12
			correccion=12;
		}                                                                                // If not continues
		if((cursoDestino >= 17)&(cursoDestino <= 27)){
			correccion=11;
		} 
		if((cursoDestino >= 28)&(cursoDestino <= 37)){
			correccion=100;
		} 
		if((cursoDestino >= 38)&(cursoDestino <= 42)){
			correccion=9;
		}  
		if((cursoDestino >= 43)&(cursoDestino <= 52)){
			correccion=8;
		}
		if((cursoDestino >= 53)&(cursoDestino <= 57)){
			correccion=7;
		}
		if((cursoDestino >= 58)&(cursoDestino <= 62)){
			correccion=6;
		}
		
		cursoDestino =abs(diflon)/(abs(diflat)/correccion);
		distancia= ((abs(diflat)/correccion)* sqrt(sq(correccion) + sq(cursoDestino)))/10;      // Calcule la distance
		cursoDestino = (cursoDestino*45)/120;
		switch(cuadrante)
		{
			case 1: 
			cursoDestino= cursoDestino;
			break;
			case 2: 
			cursoDestino= 180 - cursoDestino;
			break;
			case 3: 
			cursoDestino= 180 + cursoDestino;
			break;
			case 4: 
			cursoDestino= 360 - cursoDestino;
			break;
		}         
	}
	else                                         // If not for logic latitude < lngitude
	{
		if((cursoDestino >= 1)&(cursoDestino <= 16)){
			correccion=12;
		}
		if((cursoDestino >= 17)&(cursoDestino <= 27)){
			correccion=13;
		}
		if((cursoDestino >= 28)&(cursoDestino <= 32)){
			correccion=14;
		}
		if((cursoDestino >= 33)&(cursoDestino <= 37)){
			correccion=150;
		}   
		if((cursoDestino >= 38)&(cursoDestino <= 42)){
			correccion=16;
		}
		if((cursoDestino >= 43)&(cursoDestino <= 47)){
			correccion=17;
		}
		if((cursoDestino >= 48)&(cursoDestino <= 52)){
			correccion=19;
		} 
		if((cursoDestino >= 53)&(cursoDestino <= 57)){
			correccion=21;
		}
		if((cursoDestino >= 58)&(cursoDestino <= 62)){
			correccion=24;
		}
		
		cursoDestino =abs(diflat)/(abs(diflon)/correccion);
		distancia= ((abs(diflon)/correccion)* sqrt(sq(correccion) + sq(cursoDestino)))/10; //Calcula la distancia
		cursoDestino = (cursoDestino*45)/120; // Ecuacion para obtener los grados que nos llevara a nuestro destino WUJU, pero aun falta mas!!
		
		switch(cuadrante)
		{
			case 1: 
			cursoDestino= 90 - cursoDestino;
			break;
			case 2: 
			cursoDestino= 90 + cursoDestino;
			break;
			case 3: 
			cursoDestino= 270 - cursoDestino;
			break;
			case 4: 
			cursoDestino= 270 + cursoDestino;
			break;
		}  
	}
	
	/*********************************************************************************************
		This part generate a NMEA string sentence:
		$JORDI,Course to Destination, Distance, Speed, Latitude,lngitud, Real Course,Dif Lat, Dif Long, Quadrant, Correction
		This string is use by the ground station (Labview)
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
	Serial.print(lngitud);
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
	
	for (int i=inicio;i<300;i++){
		if (linea[i]==','){                                        // Check for the position of the  "," separator
            indices[cont]=i;
            cont++;
		}
	}
	for (int i=0;i<11;i++){
        long conver = 100000000;                          // Convert many variables, multipurpose
		for (int j=indices[i];j<(indices[i+1]-1);j++)   // Read values
		{
            if(linea[j+1] != 46)                                  // If different to "." dot, continue
            {
				switch(i)
				{
					case 2:                                              // Converts the latitude string
					latitud=latitud+((linea[j+1]-48)*(conver/10));
					conver=conver/10;           
					break;
					
					case 3:                                             // If north = Positive, if south = negative
					if(linea[j+1] == 83)// Multiply latitude for -1
					{
						latitud=(latitud)*-1; 
					}
					break;
					
					case 4:                                            // Converts the lngitude string
					lngitud=lngitud+((linea[j+1]-48)*conver); 
					conver=conver/10;
					break;
					
					case 5:                                            // If east = stays positive, if is west = negative
					
					if(linea[j+1] == 87)
					{
						lngitud=(lngitud)*-1;                   // Change the value to negative (West)
					}
					break;
					case 6: // Convert Speed 
					velocidad=velocidad+((linea[j+1]-48)*(conver/1000000));
					conver=conver/10;
					break;
					
					case 7:                                            // Converts the real Course String in intriger degrees
					cursoReal=cursoReal+((linea[j+1]-48)*(conver/1000000));
					conver=conver/10;
					break;
				}
			}
		}
		
	}
	latitud = ((latitud/1000000)*1000000)+((latitud % 1000000) / .6);             // Converts degrees,minutes to decimal degrees
	lngitud = ((lngitud/1000000)*1000000)+((lngitud % 1000000) / .6);     // Same
	
	
} 


