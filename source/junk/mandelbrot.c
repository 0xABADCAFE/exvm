#include <stdio.h>
#include <stdlib.h>

int iSize       = 1024;
int iMaxIters   = 256;
float fBailout  = 16.0;
float fYMin     = -1.25;
float fYMax     = 1.25;
float fXMax     = 0.75;

int main() {
  float fYTot = fYMax - fYMin;
  float fXMin = fXMax - fYTot;
  float fStep = fYTot / iSize;
  unsigned char* aPixels = (unsigned char*) malloc(iSize * iSize);

  if (aPixels) {
    FILE* f;
    int iPix = 0;
    float fCY   = fYMax;
    for (int y = 0; y<iSize; y++, fCY -= fStep) {
      float fCX = fXMin;
      for (int x = 0; x<iSize; x++, fCX += fStep) {
        int i   = 0;
        float fZX = fCX;
        float fZY = fCY;
        float fTest, fZX2, fZY2, fNewZX, fNewZY;
        do {
          fZX2   = fZX * fZX;
          fZY2   = fZY * fZY;
          fTest  = fZX2 + fZY2;
          fNewZX = fZX2 - fZY2 + fCX;
          fNewZY = 2.0 * fZX * fZY + fCY;
//           if (fNewZX == fZX && fNewZY == fZY) {
//             i = iMaxIters;
//             break;
//           }
          fZY    = fNewZY;
          fZX    = fNewZX;
        } while (i++ < iMaxIters && fTest < fBailout);
        aPixels[iPix++] = (i * i) & 0xFF;
      }
    }

    f = fopen("c_out.ppm", "wb");
    fprintf(f, "P5\n%d\n%d\n255\n", iSize, iSize);
    fwrite(aPixels, 1, iSize * iSize, f);
    fclose(f);
    free(aPixels);
  }
  return 0;
}
