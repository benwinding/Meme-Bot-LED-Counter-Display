
void DrawSentence(const char* sentence) {
  unsigned lenC = strlen(sentence);
  int len = lenC * 8;
  int window = 64;

  static int shift = -len;
  if (shift < window + len - 8)
    shift = shift + 1;
  else
    shift = -len + 8;
  for (int i = 0; i < window; i += 8) {
    for (int j = 0; j < lenC; j++) {
      int x = lenC - 1 - j;
      drawLetter(i, 0, sentence[x], shift - i - j * 8);
    }
  }
}

void ShowMatrix(int delayTime) {
  matrix.reverse();
  uint32_t lastCountTime = millis();
  while ((millis() - lastCountTime) < delayTime) {
    matrix.scan();
  }
  matrix.reverse();
  matrix.clear();
}

void drawLetter(uint16_t x, uint16_t y, uint8_t n, int shift) {
  // (x, y) top-left position, x should be multiple of 8
  n = n - 32 - 16; // Sync to array above
  uint8_t *pDst = displaybuf + y * (WIDTH / 8) + x / 8;
  const uint8_t *pSrc = digitals + n * 16;
  
  for (uint8_t i = 0; i < 16; i++) {
    int temp;
    if (shift < 0)
      temp = *pSrc << -shift;
    else
      temp = *pSrc >> shift;
    *pDst = *pDst ^ temp;
    pDst += WIDTH / 8;
    pSrc++;
  }
}

