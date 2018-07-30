void convertUint8ArrayToLong(uint8_t* src, unsigned long* dst) {
  memcpy(dst, src, 8);
}

void convertLongToUint8Array(unsigned long* src, uint8_t* dst) {
  memcpy(dst, src, 8);
}

