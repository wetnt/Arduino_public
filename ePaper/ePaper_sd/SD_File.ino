File myFile;

String filename = "santi.txt";
void sd_file_init() {
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  } else {
    Serial.println("SD OPEN CALL");
  }
}

void sd_file_Create() {
  lg("Creating ..."); lg(filename); lg();
  myFile = SD.open(filename, FILE_WRITE);
  myFile.close();

  // Check to see if the file exists:
  if (SD.exists(filename)) {
    lg("exists ..."); lg(filename); lg();
  } else {
    lg("doesn't exist ..."); lg(filename); lg();
  }
}
//char * txt = "CED2C3C7CAC7CEB0B4F3B5C4B9A4B3CCA3A1";

void sd_file_save() {
  myFile = SD.open(filename, FILE_WRITE);

  if (myFile) {
    myFile.write(buff);
    myFile.close();

    lg("save ..."); lg(filename); lg();
    lg(buff); lg();
  }
  else {
    lg("error write ..."); lg(filename); lg();
  }

}


char buff2[200];
int n, f = 0;
void sd_file_read() {
  lg("read ..."); lg(filename); lg();
  //myFile = SD.open(filename, FILE_WRITE);
  myFile = SD.open(filename, FILE_READ);

  if (myFile) {

    sss_int();
    
    myFile.seek(480);

    while (myFile.available()  && f <= 18) {
      char b = myFile.read();
      Serial.write(b);
      //if (b != '\r' && b != '\n')buff2[n++] = b;
      if (b != '\n')buff2[n++] = b;
      if (n == 50) {
        sss_write(buff2, f);
        lg(); lg("n="); lg(n); lg(" "); lg("f="); lg(f); lg();
        resetBuffer(buff2); n = 0; f++;
      }
    }
    sss_write(buff2, f+1);
    sss_show();
    myFile.close();
    lg();
  } else {
    lg("error read ..."); lg(filename); lg();
  }

}

void sd_file_Remove() {
  lg("Remove ..."); lg(filename); lg();
  SD.remove("example.txt");
  if (SD.exists("example.txt")) {
    lg("exists ..."); lg(filename); lg();
  } else {
    lg("doesn't exist ..."); lg(filename); lg();
  }
}

void s1() {
  sss(buff2, 0);
}
void s2() {
  //sss(txt);
}

void resetBuffer(char * buf) {
  memset(buf, 0, sizeof(buf));
}
