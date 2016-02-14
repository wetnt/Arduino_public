/* Modbus para */
//#define TIMEOUT 1000          /* 1 second */
#define TIMEOUT 10000          /* 10 second */
#define MAX_READ_REGS 125
#define MAX_WRITE_REGS 125
#define MAX_RESPONSE_LENGTH 256
#define PRESET_QUERY_SIZE 256
#define PORT_ERROR -5

unsigned int crc(unsigned char *buf, int start, int cnt) {
  int i, j;
  unsigned temp, temp2, flag;
  temp = 0xFFFF;
  for (i = start; i < cnt; i++) {
    temp = temp ^ buf[i];
    for (j = 1; j <= 8; j++) {
      flag = temp & 0x0001;
      temp = temp >> 1;
      if (flag) temp = temp ^ 0xA001;
    }
  }
  temp2 = temp >> 8;
  temp = (temp << 8) | temp2;
  temp &= 0xFFFF;
  return (temp);
}
#define REQUEST_QUERY_SIZE 6     /* the following packets require          */
#define CHECKSUM_SIZE 2          /* 6 unsigned chars for the packet plus   */
void build_request_packet(int slave, int function, int start_addr, int count, unsigned char *packet) {
  packet[0] = slave;
  packet[1] = function;
  start_addr -= 1;
  packet[2] = start_addr >> 8;
  packet[3] = start_addr & 0x00ff;
  packet[4] = count >> 8;
  packet[5] = count & 0x00ff;
}
void modbus_query(unsigned char *packet, size_t string_length) {
  int temp_crc;
  temp_crc = crc(packet, 0, string_length);
  packet[string_length++] = temp_crc >> 8;
  packet[string_length++] = temp_crc & 0x00FF;
  packet[string_length] = 0;
}
int send_query(unsigned char *query, size_t string_length) {
  int i;  
  modbus_query(query, string_length);
  string_length += 2;
 // String s = "";
  lg("====");
  for (i = 0; i < string_length; i++) {
   // s.concat((char)query[i]);
    //lg(query[i]);
    Serial.print(query[i], HEX); //Orginal
    lg(' ');
    myAvw.write(query[i]);
  }  
  lg("====");
  //lg(s);
  lg("====");
  lg();
  smartDelay(200);
  return i;
}
int receive_response(unsigned char *received_string) {
  int bytes_received = 0;
  int i = 0;
  //myAvw.listen();
  while (myAvw.available() == 0) {
    smartDelay(1);
    if (i++ > TIMEOUT)
      return bytes_received;
  }
  smartDelay(200);
  //lg("====");
  myAvw.listen();
  while (myAvw.available()) {
    //received_string[bytes_received] = myAvw.read();
    char c = myAvw.read(); //lg(c);
    received_string[bytes_received] = c;

    bytes_received++;
    if (bytes_received >= MAX_RESPONSE_LENGTH)
      return PORT_ERROR;
  }
  //lg("====");
  return (bytes_received);
}
int modbus_response(unsigned char *data, unsigned char *query) {
  int response_length;
  int i;
  unsigned int crc_calc = 0;
  unsigned int crc_received = 0;
  unsigned char recv_crc_hi;
  unsigned char recv_crc_lo;

  do {
    response_length = receive_response(data);
  } while ((response_length > 0) && (data[0] != query[0]));

  if (response_length) {
    crc_calc = crc(data, 0, response_length - 2);
    recv_crc_hi = (unsigned) data[response_length - 2];
    recv_crc_lo = (unsigned) data[response_length - 1];
    crc_received = data[response_length - 2];
    crc_received = (unsigned) crc_received << 8;
    crc_received = crc_received | (unsigned) data[response_length - 1];
    if (crc_calc != crc_received) response_length = 0;
    if (response_length && data[1] != query[1]) {
      response_length = 0 - data[2];
    }
  }
  return (response_length);
}
int read_reg_response(int *dest, int dest_size, unsigned char *query) {
  unsigned char data[MAX_RESPONSE_LENGTH];
  int raw_response_length;
  int temp, i;
  raw_response_length = modbus_response(data, query);
  if (raw_response_length > 0) raw_response_length -= 2;
  if (raw_response_length > 0) {
    for (i = 0; i < (data[2] * 2) && i < (raw_response_length / 2); i++) {
      temp = data[3 + i * 2] << 8;
      temp = temp | data[4 + i * 2];
      dest[i] = temp;
    }
  }
  return (raw_response_length);
}
int preset_response(unsigned char *query) {
  unsigned char data[MAX_RESPONSE_LENGTH];
  int raw_response_length;
  raw_response_length = modbus_response(data, query);
  return (raw_response_length);
}
int read_holding_registers(int slave, int start_addr, int count, int *dest, int dest_size) {
  int function = 0x03;
  int ret;
  unsigned char packet[REQUEST_QUERY_SIZE + CHECKSUM_SIZE];
  if (count > MAX_READ_REGS) count = MAX_READ_REGS;
  build_request_packet(slave, function, start_addr, count, packet);
  if (send_query(packet, REQUEST_QUERY_SIZE) > -1) {
    ret = read_reg_response(dest, dest_size, packet);
  } else {
    ret = -1;
  }
  return (ret);
}
int preset_multiple_registers(int slave, int start_addr, int reg_count, int *data) {
  int function = 0x10;
  int byte_count, i, packet_size = 6;
  int ret;
  unsigned char packet[PRESET_QUERY_SIZE];
  if (reg_count > MAX_WRITE_REGS) {
    reg_count = MAX_WRITE_REGS;
  }
  build_request_packet(slave, function, start_addr, reg_count, packet);
  byte_count = reg_count * 2;
  packet[6] = (unsigned char)byte_count;
  for (i = 0; i < reg_count; i++) {
    packet_size++;
    packet[packet_size] = data[i] >> 8;
    packet_size++;
    packet[packet_size] = data[i] & 0x00FF;
  }
  packet_size++;
  if (send_query(packet, packet_size) > -1) {
    ret = preset_response(packet);
  } else {
    ret = -1;
  }
  return (ret);
}
