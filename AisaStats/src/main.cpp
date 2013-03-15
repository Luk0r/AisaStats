/*
/1. open envi files for reading
2. parse the header for relevant infos:
interleave = bil
samples = 300
lines   = 6011
bands   = 368
autodarkstartline = 5892
data type = 12
Wavelength = {
 401.88,
 406.14,
 410.40,
 414.65,
 ...
 2494.69,
 2500.93
}
4. save wavelength to vector<float> wavelength

3. read line by line (sequential, BIL mode)

*/


#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>
#include <utility>
#include <fstream>
#include <sstream>
#include <iostream>
#include <functional>

#include <CubeArray.hpp>

int main(int argc, char **argv)
{
	//this is git testing

	// haha now deleted and new this line

	//test1 branch


	envi::CubeArray<int> cube(7, 5, 3);

	std::cout << cube.size() << std::endl;
	std::cout << cube.getPixel(0,0,0) << std::endl;
	std::cout << cube.getPixel(1,0,0) << std::endl;
	std::cout << cube.getPixel(2,0,0) << std::endl;

	int init=0;
	for(auto & x: cube.buffer)
	{
		x=init++;
	}

	std::cout << cube.getPixel(1,0,0) << std::endl;
	std::cout << cube.getPixel(2,0,0) << std::endl;

	char c;
	std::cin >> c;
};

// calc stats for all slices
// care: calc stddev^2 for summing up
// calc stats for data frame and dark current frame
// check for overflow/max saturation values in data frame
// output a) mean SNR for each wavelength
// output b) full stats for each wavelength
