

// Note to self: M rows, N columns; row-major is array[m][n]

// Takes an array of tilts (y), an array of observed gravities (x), and an
// array with room for 3 coefficients.
int regressGravities(float gravities[], float tilts[], int elements, float coefficients[3]) {
  return regress(gravities, tilts, elements, coefficients);
}

// Takes an array of temperatures(y), an array of differences from predicted gravities(x),
// and an array with room for 3 coefficients.
int regressTemps(float gravityOffsets[], float temps[], int elements, float coefficients[3]) {
  return regress(gravityOffsets, temps, elements, coefficients);
}

// Takes two arrays containing dependent variable data and independent variable
// data, and one size-3 array containing polynomial coefficients:
// y = c[0]x^2 + c[1]x + c[2]
//
// returns:
// 0: success
// -1: matrix not invertible
// -2: mismatch in x, y observations
int regress(float y[], float x[], int elements, float coefficients[3]) {  
  coefficients[0] = 0;
  coefficients[1] = 0;
  coefficients[2] = -1;

  int s = elements;
  //Serial.println("S: " + s);

  float* pX = (float*) malloc(sizeof(float) * s * 3); // independent variable (s rows, 3 cols)
  float* pXT = (float*) malloc(sizeof(float) * 3 * s); // transposed X (3 rows, s cols)
  float* pY = (float*) malloc(sizeof(float) * s * 1); // dependent variable (s rows, 1 col)
  float* pXProd = (float*) malloc(sizeof(float) * 3 * 3); // (XT * X)^-1 (3 rows, cols)
  float* pXYProd = (float*) malloc(sizeof(float) * 3 * 1); // XT * Y (3 rows, 1 col)
  float* pFR = (float*) malloc(sizeof(float) * 3 * 1); // Result (3 rows, 1 col)

  for(int i = 0; i < s; i++) {
    int xrow = i * 3;
    pX[xrow + 0] = 1;
    pX[xrow + 1] = x[i];
    pX[xrow + 2] = x[i] * x[i];

    //yrow = i
    pY[i + 0] = y[i];
  }

  //Matrix.Print(pX, s, 3, (String) "x");
  //pMatrix.Print(pY, s, 1, (String) "y");

  Matrix.Transpose(pX, s, 3, pXT);
  Matrix.Multiply(pXT, pX, 3, s, 3, pXProd);
  int result = Matrix.Invert(pXProd, 3);

  if(result == 0) {
    free(pX);
    free(pXT);
    free(pY);
    free(pXProd);
    free(pXYProd);
    free(pFR);
    return -1;
  }

  Matrix.Multiply(pXT, pY, 3, s, 1, pXYProd);
  Matrix.Multiply(pXProd, pXYProd, 3, 3, 1, pFR);

  coefficients[2] = pFR[0];
  coefficients[1] = pFR[1];
  coefficients[0] = pFR[2];

  free(pX);
  free(pXT);
  free(pY);
  free(pXProd);
  free(pXYProd);
  free(pFR);
  return 0;
}


