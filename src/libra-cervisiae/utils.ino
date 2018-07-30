void convertUint8ArrayToLong(uint8_t* src, unsigned long* dst, int len) {
  memcpy(dst, src, len);
}

void convertLongToUint8Array(unsigned long* src, uint8_t* dst, int len) {
  memcpy(dst, src, len);
}

