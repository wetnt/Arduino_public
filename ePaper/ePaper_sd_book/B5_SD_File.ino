File myFile;
void sd_file_init() {
  if (!SD.begin(chipSelect)) {
    Serial.println("SD OPEN Failed!"); return;
  } else {
    Serial.println("SD OPEN OK");
  }
}
void sd_file_create() {
  lg("Creating ..."); lg(filename); lg();
  myFile = SD.open(filename, FILE_WRITE);
  myFile.close();
  if (SD.exists(filename)) {
    lg("Exist ..."); lg(filename); lg();
  } else {
    lg("NO Exist ..."); lg(filename); lg();
  }
}
void sd_file_save() {
  myFile = SD.open(filename, FILE_WRITE);
  if (myFile) {
    myFile.write(buff); myFile.close();
    lg("Save ..."); lg(filename); lg();
    lg(buff); lg();
  } else {
    lg("error write ..."); lg(filename); lg();
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


char buff2[200];
int n, f = 0;
void sd_file_read() {
  lg("read ..."); lg(filename); lg();
  //myFile = SD.open(filename, FILE_WRITE);
  myFile = SD.open(filename, FILE_READ);

  if (myFile) {

    ePaper_clear();

    myFile.seek(480);

    while (myFile.available()  && f <= 18) {
      char b = myFile.read();
      Serial.write(b);
      if (chechB(b))buff2[n++] = b;
      if (n == 50) {
        ePaper_write(buff2, f);
        lg(); lg("n="); lg(n); lg(" "); lg("f="); lg(f); lg();
        resetBuffer(buff2); n = 0; f++;
      }
    }
    ePaper_write(buff2, f + 1);
    ePaper_udpate();
    myFile.close();
    lg();
  } else {
    lg("error read ..."); lg(filename); lg();
  }
}
boolean chechB(char b) {
  if (b == '\r')return false;
  if (b == '\n')return false;
  if (b == 0x00)return false;
  if (b == 0xA5)return false;
  return true;
}

