#pragma once

#include <string>
#include <fstream>
#include <cstring>
#include <ostream>
#include "utils.hpp"
#include <string>
#include <sstream>

template<class E, class T, int N>
std::basic_istream<E,T>& operator>>(std::basic_istream<E,T>& in, const E(&sliteral)[N]) {
        E buffer[N-1] = {}; //get buffer
        in >> buffer[0]; //skips whitespace
        if (N>2)
                in.read(buffer+1, N-2); //read the rest
        if (std::strncmp(buffer, sliteral, N-1)) //if it failed
                in.setstate(std::ios::failbit); //set the state
        return in;
}

Data txt_loader(const std::string& file)
{
    Data data;
    std::ifstream fin(file);
    std::cout << "loading [" << file << "]..." << std::endl;

    Model model(9, 3);
    std::string line;
    while (std::getline(fin, line)) {
        std::istringstream iss(line);

        for (uint i = 0; i < 9; ++i)
            iss >> model.x.at(i);
        iss >> ",";
        for (uint i = 0; i < 3; ++i)
            iss >> model.y.at(i);

        data.emplace_back(model);
    }

    std::cout << "loading of " << data.size() << " models completed" << std::endl;
    return data;
}

#include "bitmap_image.hpp"

Vector read_bmp(const std::string& filename){
    bitmap_image image(filename);
    if (!image)
        std::cout << "Error - Failed to open: input.bmp" << std::endl;

   unsigned char r, g ,b;
   const uint height = image.height();
   const uint width  = image.width();

   Vector data(height * width);
   for (uint y = 0; y < height; ++y) {
      for (uint x = 0; x < width; ++x) {
          image.get_pixel(x, y, r, g, b);
          data.at(width * y + x) = float(r + g + b) / (255 * 3);
      }
   }
   return data;
}

Data bmp_loader(const std::string& folder)
{
    auto data = txt_loader(folder + "/data.txt");

    for (uint i = 0; i < data.size(); ++i) {
        std::ostringstream oss;
        oss << folder << "/" << i << ".bmp";
        data[i].x = read_bmp(oss.str());
    }
    return data;
}
