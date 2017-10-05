import java.io.FileOutputStream;
import java.nio.ByteBuffer;

public class Mandelbrot {

  public static void main(String[] args) {
    int iSize       = 1024;
    int iMaxIters   = 256;
    float fBailout  = 16.0f;
    float fYMin     = -1.25f;
    float fYMax     = 1.25f;
    float fXMax     = 0.75f;
    float fYTot = fYMax - fYMin;
    float fXMin = fXMax - fYTot;
    float fStep = fYTot / iSize;

    byte[] aPixels = ByteBuffer.allocate(iSize * iSize).array();

    //FILE* f;
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
          fNewZY = 2.0f * fZX * fZY + fCY;
          fZY    = fNewZY;
          fZX    = fNewZX;
        } while (i++ < iMaxIters && fTest < fBailout);
        aPixels[iPix++] = (byte)((i * i) & 0xFF);
      }
    }
    try {
      FileOutputStream f = new FileOutputStream("java_out.ppm");
      String header = "P5\n" + iSize + "\n" + iSize + "\n255\n";
      f.write(header.getBytes());
      f.write(aPixels);
      f.close();
    } catch (Exception e) {
      System.out.println("Error writing file");
    }
  }
}
