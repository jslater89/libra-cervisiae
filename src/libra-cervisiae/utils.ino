void convertUnsignedCharToLong(unsigned char *src, long *dst) {
  memcpy(dst, src, sizeof(long));
}

void convertLongToUnsignedChar(long *src, unsigned char *dst) {
  memcpy(dst, src, sizeof(long));
}

