
// Note to self: M rows, N columns; row-major is array[m][n]

// Takes an array of tilts (y), an array of observed gravities (x), and an
// array with room for 3 coefficients.
int regressGravities(float gravities[], float tilts[], float coefficients[3]) {
  return regress(gravities, tilts, coefficients);
}

// Takes an array of temperatures(y), an array of differences from predicted gravities(x),
// and an array with room for 3 coefficients.
int regressTemps(float gravityOffsets[], float temps[], float coefficients[3]) {
  return regress(gravityOffsets, temps, coefficients);
}

// Takes two arrays containing dependent variable data and independent variable
// data, and one size-3 array containing polynomial coefficients:
// y = c[0]x^2 + c[1]x + c[2]
//
// returns:
// 0: success
// -1: matrix not invertible
// -2: mismatch in x, y observations
int regress(float y[], float x[], float coefficients[3]) {  
  coefficients[0] = 0;
  coefficients[1] = 0;
  coefficients[2] = -1;
  
  int sizeofx = (sizeof(x) / sizeof(float));
  int sizeofy = (sizeof(y) / sizeof(float));

  if(sizeofx != sizeofy) {
    return -2;
  }

  int s = sizeofx;
  
  float X[s][3]; // independent variable
  float XT[3][s]; // transposed X
  float Y[s][1]; // dependent variable
  float XProd[3][3]; // XT * X
  float XYProd[3][1]; // XT * Y
  float FinalResult[3][1]; // XProd(inverted) * XYProd

  float* pX = &X[0][0];
  float* pXT = &XT[0][0];
  float* pY = &Y[0][0];
  float* pXProd = &XProd[0][0];
  float* pXYProd = &XYProd[0][0];
  float* pFR = &FinalResult[0][0];

  for(int i = 0; i < s; i++) {
    X[i][0] = 1;
    X[i][1] = x[i];
    X[i][2] = x[i] * x[i];
  }

  Matrix.Transpose(pX, s, 3, pXT);
  Matrix.Multiply(pXT, pX, 3, s, 3, pXProd);
  int result = Matrix.Invert(pXProd, 3);

  if(result == 0) {
    return -1;
  }

  Matrix.Multiply(pXT, pY, 3, s, 1, pXYProd);
  Matrix.Multiply(pXProd, pXYProd, 3, 3, 1, pFR);

  coefficients[2] = FinalResult[0][0];
  coefficients[1] = FinalResult[1][0];
  coefficients[0] = FinalResult[2][0];

  return 0;
}

