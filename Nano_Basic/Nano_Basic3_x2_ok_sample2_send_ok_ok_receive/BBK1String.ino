//ALib Begin//
char ** cSplit(char * string, char spliter, int * arrayCount) {
  //分割后字符串数量
  int num = 0;
  //计算数量
  int i = 0;
  int size = strlen(string);
  for (; i < size; i++) {
    if ((string[i] != spliter) && (string[i + 1] == spliter || string[i + 1] == '\0'))
      num++;
  }
  * arrayCount = num;
  //分配空间
  char ** cStrings = (char ** )malloc(sizeof(char * ) * (num + 1));
  int j = 0;
  for (; j <= num; j++) {
    //初始化指针数组
    cStrings[j] = 0;
  }
  //保存分割后字符串
  char * buffer = (char * )malloc(sizeof(char) * (size + 1));
  int l = 0;
  for (; l < size + 1; l++) {
    buffer[l] = 0;
  }
  int counter = 0;
  int k = 0;
  for (; k < size; k++) {
    if (string[k] != spliter) {
      int i = 0;
      int j = k;
      while (string[j] != spliter && string[j] != '\0')
        buffer[i++] = string[j++];
      buffer[i] = '\0';
      cStrings[counter] = (char * )malloc(sizeof(char) * i);
      strcpy(cStrings[counter++], buffer);
      k = k + i;
    }
  }
  free(buffer);
  return cStrings;
}
/**
 *调用此方法释放cSplit分配的内存空间
 */
void freeStringsMemory(char ** strings) {
  int k = 0;
  for (; ; k++) {
    if (strings[k] != 0)
      free(strings[k]);
    else
      break;
  }
  free(strings);
}
//ALib End//

