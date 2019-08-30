//utf-8和unicode编码规则
unsigned short * translate(unsigned char* sbuf)
{
  int i = 0, j = 0;
  int nsize = strlen(sbuf);
  unsigned char * strbuf = (unsigned char*)calloc(2, nsize + 1);
  while (*(sbuf + i))
  {
    if (*(sbuf + i) < 0x80)
    {
      *(strbuf + j) = *(sbuf + i);
      *(strbuf + j + 1) = 0;
      i++;
      j += 2; //一个单元两个字节，高位补零
    }
    else if ((*(sbuf + i) & 0xe0) == 0xc0)  //不太清楚表示什么
    {
      *(strbuf + j) = (*(sbuf + i) << 6) | (*(sbuf + i + 1) | 0x00);
      *(strbuf + j + 1) = (*(sbuf + i) >> 2) & 0x07;
      i += 2;
      j += 2;
    }
    else if ((*(sbuf + i) & 0xf0) == 0xe0) //表示汉字的字节的检验
    {
      *(strbuf + j) = (*(sbuf + i + 1) << 6) | (*(sbuf + i + 2) & 0x3f);
      *(strbuf + j + 1) = (*(sbuf + i) << 4) | ((*(sbuf + i + 1) >> 2) & 0x0f);
      i += 3;
      j += 2;
    }
  }
  //为宽字符集增加结尾标志
  *(strbuf + j) = 0;
  *(strbuf + j + 1) = 0;
  return (unsigned short *)strbuf;
}
