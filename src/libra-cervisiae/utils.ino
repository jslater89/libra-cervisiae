void convertUint8ArrayToLong(uint8_t* src, long* dst) {
  memcpy(dst, src, sizeof(long));
}

void convertLongToUint8Array(long* src, uint8_t* dst) {
  memcpy(dst, src, sizeof(long));
}

