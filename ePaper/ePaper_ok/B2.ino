
#define    CMD_SIZE                           512
static unsigned char _cmd_buff[CMD_SIZE];
static const unsigned char _cmd_handshake[8] = {0xA5, 0x00, 0x09, CMD_HANDSHAKE, 0xCC, 0x33, 0xC3, 0x3C};        //CMD_HANDSHAKE
static const unsigned char _cmd_read_baud[8] = {0xA5, 0x00, 0x09, CMD_READ_BAUD, 0xCC, 0x33, 0xC3, 0x3C};       //CMD_READ_BAUD
static const unsigned char _cmd_stopmode[8] = {0xA5, 0x00, 0x09, CMD_STOPMODE, 0xCC, 0x33, 0xC3, 0x3C};         //CMD_STOPMODE
static const unsigned char _cmd_update[8] = {0xA5, 0x00, 0x09, CMD_UPDATE, 0xCC, 0x33, 0xC3, 0x3C};           //CMD_UPDATE
static const unsigned char _cmd_load_font[8] = {0xA5, 0x00, 0x09, CMD_LOAD_FONT, 0xCC, 0x33, 0xC3, 0x3C};       //CMD_LOAD_FONT
static const unsigned char _cmd_load_pic[8] = {0xA5, 0x00, 0x09, CMD_LOAD_PIC, 0xCC, 0x33, 0xC3, 0x3C};         //CMD_LOAD_PIC


static void _putchars(const unsigned char * ptr, int n) {
  int i, x;
  for (i = 0; i < n; i++) {
    x = ptr[i];
    Serial2.write(x);
  }
}
void epd_handshake(void) {
  memcpy(_cmd_buff, _cmd_handshake, 8);
  _cmd_buff[8] = _verify(_cmd_buff, 8);
  _putchars(_cmd_buff, 9);
}
void epd_clear(void)
{
  _cmd_buff[0] = FRAME_B;

  _cmd_buff[1] = 0x00;
  _cmd_buff[2] = 0x09;

  _cmd_buff[3] = CMD_CLEAR;

  _cmd_buff[4] = FRAME_E0;
  _cmd_buff[5] = FRAME_E1;
  _cmd_buff[6] = FRAME_E2;
  _cmd_buff[7] = FRAME_E3;
  _cmd_buff[8] = _verify(_cmd_buff, 8);

  _putchars(_cmd_buff, 9);
}
void epd_udpate(void) {
  memcpy(_cmd_buff, _cmd_update, 8);
  _cmd_buff[8] = _verify(_cmd_buff, 8);
  _putchars(_cmd_buff, 9);
}
void epd_disp_string(const void * p, int x0, int y0) {
  int string_size;
  unsigned char * ptr = (unsigned char *)p;

  string_size = strlen((const char *)ptr);
  string_size += 14;

  _cmd_buff[0] = FRAME_B;

  _cmd_buff[1] = (string_size >> 8) & 0xFF;
  _cmd_buff[2] = string_size & 0xFF;

  _cmd_buff[3] = CMD_DRAW_STRING;

  _cmd_buff[4] = (x0 >> 8) & 0xFF;
  _cmd_buff[5] = x0 & 0xFF;
  _cmd_buff[6] = (y0 >> 8) & 0xFF;
  _cmd_buff[7] = y0 & 0xFF;

  strcpy((char *)(&_cmd_buff[8]), (const char *)ptr);

  string_size -= 5;

  _cmd_buff[string_size] = FRAME_E0;
  _cmd_buff[string_size + 1] = FRAME_E1;
  _cmd_buff[string_size + 2] = FRAME_E2;
  _cmd_buff[string_size + 3] = FRAME_E3;
  _cmd_buff[string_size + 4] = _verify(_cmd_buff, string_size + 4);

  _putchars(_cmd_buff, string_size + 5);
}
void epd_set_en_font(unsigned char font) {
  _cmd_buff[0] = FRAME_B;

  _cmd_buff[1] = 0x00;
  _cmd_buff[2] = 0x0A;

  _cmd_buff[3] = CMD_SET_EN_FONT;

  _cmd_buff[4] = font;

  _cmd_buff[5] = FRAME_E0;
  _cmd_buff[6] = FRAME_E1;
  _cmd_buff[7] = FRAME_E2;
  _cmd_buff[8] = FRAME_E3;
  _cmd_buff[9] = _verify(_cmd_buff, 9);

  _putchars(_cmd_buff, 10);
}
void epd_set_ch_font(unsigned char font) {
  _cmd_buff[0] = FRAME_B;

  _cmd_buff[1] = 0x00;
  _cmd_buff[2] = 0x0A;

  _cmd_buff[3] = CMD_SET_CH_FONT;

  _cmd_buff[4] = font;

  _cmd_buff[5] = FRAME_E0;
  _cmd_buff[6] = FRAME_E1;
  _cmd_buff[7] = FRAME_E2;
  _cmd_buff[8] = FRAME_E3;
  _cmd_buff[9] = _verify(_cmd_buff, 9);

  _putchars(_cmd_buff, 10);
}
static unsigned char _verify(const void * ptr, int n) {
  int i;
  unsigned char * p = (unsigned char *)ptr;
  unsigned char result;
  for (i = 0, result = 0; i < n; i++)  {
    result ^= p[i];
  }
  return result;
}
