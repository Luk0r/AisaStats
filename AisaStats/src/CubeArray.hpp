/*
 * CubeArray.hpp
 *
 *  Created on: 15.03.2013
 *      Author: schmidan
 */

#ifndef CUBEARRAY_HPP_
#define CUBEARRAY_HPP_

#include <memory>
#include <vector>


namespace envi{




template <class T>
class Slice
{
public:
	Slice(uint64_t samples_, uint64_t bands_);

	uint64_t samples;
	uint64_t bands;

	std::vector<T>  buffer;
};

template <class T>
Slice<T>::Slice(uint64_t samples_, uint64_t bands_) :
	samples{samples_},
	bands{bands_},
	buffer(samples * bands, T() )
{

}

template <class T>
class Array
{
public:
	Array(uint64_t samples_, uint64_t lines_);

	uint64_t samples;
	uint64_t lines;

	std::vector<T> buffer;

};

template <class T>
Array<T>::Array(uint64_t samples_, uint64_t lines_):
	samples{samples_},
	lines{lines_},
	buffer(samples * lines, T() )
{

}


template <class T>
class CubeArray
{
public:
	CubeArray(uint64_t  samples_, uint64_t lines_, uint64_t bands_);
	//~CubeArray();


	// access methods
	T getPixel(uint64_t samples_, uint64_t lines_, uint64_t bands_);
	T& at(uint64_t samples_, uint64_t lines_, uint64_t bands_);
	T& linAt(uint64_t);
	size_t size();


	Slice<T> getSlice(uint64_t samples_, uint64_t bands_);
	Array<T> getBand(uint64_t samples_, uint64_t lines_);
	CubeArray<T> subCubeArray(
			uint64_t samples_start_, 	uint64_t samples_end_,
			uint64_t lines_start_, 		uint64_t lines_end_,
			uint64_t bands_start_, 		uint64_t bands_end_);


	// attribs
	uint64_t samples;
	uint64_t lines;
	uint64_t bands;
	std::vector<T> buffer;
};

template <class T>
CubeArray<T>::CubeArray(uint64_t  samples_, uint64_t lines_, uint64_t bands_):
	samples{samples_},
	lines{lines_},
	bands{bands_},
	buffer(samples * lines * bands, T())
{

}

template <class T>
inline T CubeArray<T>::getPixel(uint64_t samples_, uint64_t lines_, uint64_t bands_)
{
	return buffer[bands * (lines_ * samples_) + lines_ * samples + samples_] ;
}

template <class T>
inline T& CubeArray<T>::at(uint64_t samples_, uint64_t lines_, uint64_t bands_)
{
	return buffer[bands * (lines_ * samples_) + lines_ * samples + samples_] ;
}

template <class T>
inline T& CubeArray<T>::linAt(uint64_t length)
{
	return buffer[length];
}

template <class T>
inline size_t CubeArray<T>::size()
{
	return buffer.size();
}

}

#endif /* CUBEARRAY_HPP_ */
