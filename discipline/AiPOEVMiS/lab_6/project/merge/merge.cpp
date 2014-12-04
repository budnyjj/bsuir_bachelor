#include <Magick++.h> 
#include <iostream>
#include <algorithm>

using namespace std; 
using namespace Magick;

Color merge(Color pixel_a, Color pixel_b) {
  Quantum redQuantum = max(pixel_a.redQuantum(), pixel_b.redQuantum());
  Quantum greenQuantum = max(pixel_a.greenQuantum(), pixel_b.greenQuantum());
  Quantum blueQuantum = max(pixel_a.blueQuantum(), pixel_b.blueQuantum());
  return Color(redQuantum, greenQuantum, blueQuantum);
}

int main(int argc, char **argv) 
{ 
  InitializeMagick(*argv);

  // Construct the image object. Seperating image construction from the 
  // the read operation ensures that a failure to read the image file 
  // doesn't render the image object useless. 
  Image image_a,
        image_b;
  
  try { 
    // Read a file into image object 
    image_a.read( "input/input_a.jpg" );
    image_b.read( "input/input_b.jpg" );
    
    size_t rows = min(image_a.rows(), image_b.rows());
    size_t columns = min(image_a.columns(), image_b.columns());
    
    image_a.type(TrueColorType);
    image_b.type(TrueColorType);
    
    image_a.modifyImage();

    Pixels view_a(image_a);
    PixelPacket *pixels_a = view_a.get(0, 0, columns, rows);

    Pixels view_b(image_b);
    PixelPacket *pixels_b = view_b.get(0, 0, columns, rows);
    
    for (ssize_t row = 0; row < rows; ++row) {
      for (ssize_t column = 0; column < columns; ++column) {
        *pixels_a = merge(*pixels_a, *pixels_b);
        pixels_a++;
        pixels_b++;
      }
    }
    
    view_a.sync();
    
    // Write the image to a file 
    image_a.write( "output/output.png" ); 
  } 
  catch( Exception &error_ ) 
    { 
      cout << "Caught exception: " << error_.what() << endl; 
      return 1; 
    } 
  return 0; 
}
