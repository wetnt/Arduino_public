char *bbk1 = "BOBOKing E_Paper Display";
char bbk2[] = {0xBA, 0xA3, 0xD4, 0xC6, 0xB7, 0xC9, 0xD1, 0xEF, 0};
char *bbk3 = "2017.10.10";
void FrontCover_Show() {
  ePaper_clear();
  ePaper_write(bbk1, 5);
  ePaper_write(bbk2, 15);
  ePaper_write(bbk3, 25);
  ePaper_udpate();
}

