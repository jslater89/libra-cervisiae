void convertUint8ToChar(uint8_t* src, char* dst, int len) {
  uint8_t* pin = src;
  const char* hex = "0123456789ABCDEF";
  char* pout = dst;
  for(int i = 0; i < len-1; ++i){
      *pout++ = hex[(*pin>>4)&0xF];
      *pout++ = hex[(*pin++)&0xF];
  }
  *pout++ = hex[(*pin>>4)&0xF];
  *pout++ = hex[(*pin)&0xF];
  *pout = 0;
}

void convertCharToUint8(char* src, uint8_t* dst, int len) {
  if(src == NULL) {
    memset(dst, 0, len);
    return;
  }

  if((len % 2) != 0) {
    memset(dst, 0, len);
    return;
  }

  size_t index = 0;
  while (index < len * 2) {
      char c = src[index];
      int value = 0;
      if(c >= '0' && c <= '9') {
          value = (c - '0');
      }
      else if (c >= 'A' && c <= 'F') {  
          value = (10 + (c - 'A'));
      }
      else if (c >= 'a' && c <= 'f') {
           value = (10 + (c - 'a'));
      }
      else {
        memset(dst, 0, len);
        return;
      }

      dst[(index/2)] += value << (((index + 1) % 2) * 4);

      index++;
  }
}

