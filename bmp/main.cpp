#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "bitmap_image.hpp"

using namespace std;

//vector<int> read_bmp(string filename){
std::vector<int> read_bmp(string filename){
    bitmap_image image(filename);
    vector<int> data(11 * 11);

    if (!image)
    {
      printf("Error - Failed to open: input.bmp\n");
      //return 1;
    }

   unsigned char red;
   unsigned char green;
   unsigned char blue;

   const unsigned int height = image.height();
   const unsigned int width  = image.width();


   for (std::size_t y = 0; y < height; ++y) {
      for (std::size_t x = 0; x < width; ++x) {
          image.get_pixel(x,y, red, green, blue);
          data[width*y + x] = ((red+green+blue)/3) < 1;
      }
   }

   return data;
}

int main()
{
    std::vector<int> data = read_bmp("0.bmp");

    for (size_t y = 0; y < 11; ++y) {
          for (size_t x = 0; x < 11; ++x) {
              cout << data[11*y + x] << " ";
          }
          cout << endl;
       }
    return 0;
}

