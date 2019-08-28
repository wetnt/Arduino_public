char book_buff[200];
int book_pos = 0, book_line = 0, book_page = 0;
int book_char_max = 48;
int book_line_max = 17;

void sd_book_read_show(String fileName, int pos) {
  //----------------------------------------------------------
  lg("sd_book_read_show("); lg(fileName); lg(","); lg(pos); lg(")"); lg();
  //----------------------------------------------------------
  //myFile = SD.open(fileName, FILE_WRITE);
  myFile = SD.open(fileName, FILE_READ);
  if (myFile) {
    lg("read ..."); lg(fileName); lg("... ok!"); lg();
  } else {
    lg("read ..."); lg(fileName); lg("... error!"); lg(); return;
  }
  //----------------------------------------------------------
  ePaper_clear();
  //myFile.peek();
  myFile.seek(pos);
  //----------------------------------------------------------
  while (myFile.available()  && book_line <= book_line_max) {
    char b = myFile.read(); Serial.write(b);
    if (b != '\n' || b != '\r')book_buff[book_pos++] = b;
    if (book_pos == book_char_max) {
      //---------------------------------------------------
      lg(); lg("book_pos="); lg(book_pos); lg(" ");
      lg("book_line="); lg(book_line); lg();
      //---------------------------------------------------
      ePaper_write(book_buff, book_line);
      resetBuffer(book_buff); book_pos = 0; book_line++;
      //---------------------------------------------------
    }
  }
  //----------------------------------------------------------
  myFile.close(); ePaper_udpate(); book_line = 0; lg();
  //----------------------------------------------------------
}
