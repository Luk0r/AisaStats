/*
 * array2d.hpp
 *
 *  Created on: 14.09.2010
 *      Author: schmidta
 */

#ifndef ARRAY2D_HPP_
#define ARRAY2D_HPP_
#include <memory>

//BEGIN partitial template specialisation for pointer type
// see: http://www.c-plusplus.de/forum/257864
// USE LIKE:

/*
template <class T>
class MyClass
{
// ...
  const static bool tIsPointer = IsPointer<T>::value;
// ...
};
*/

/**
 *
 */
template <class T>
class Array2D
{
public:
	Array2D(unsigned int  height_, unsigned int  width_);
	~Array2D();
	Array2D(const Array2D& ); // copy constructor

	//2dimensional access
	//T * operator[](unsigned int );

	//2dimensional eccess with operator()
	 T& operator()(unsigned int height, unsigned int width) ;

	//1dimensional access
	 T& at(unsigned long long int i) ;


	//size
	const unsigned long long int size() const;

private:
	std::unique_ptr<T> pLine;
	//T *pLine; //2D Array
	unsigned int height;
	unsigned int width;
	unsigned long long int length;
};


/**
 * default constructor
 * @param height_
 * @param width_
 */
template <class T>
inline Array2D<T>::Array2D(unsigned int  height_, unsigned int  width_)
{
	height =  height_; // height
	width =  width_; // width
	length = height * width;
	//2dim array to 1 dim array
	pLine.reset( new T[height * width]);
}

template <class T>
inline Array2D<T>::~Array2D()
{
	//delete [] pLine;
}

/**
 * copy constructor
 * @param rhs
 */
template <class T>
Array2D<T>::Array2D(const Array2D& rhs)
{
	height = rhs.height;
	width = rhs.width;
	length = rhs.length;

	pLine( new T[height * width]);

	for(unsigned long long int i=0; i<length; ++i)
	{
		(*pLine)[i] = (*rhs.pLine)[i];
	}
}

/**
 * ERRORCHECK !!! need to be done by calling routine for parameters
 * parameters need to be smaller than corresponding @param nx and @param ny
 */
/*
template <class T>
inline T * Array2D<T>::operator[](unsigned int x)
{
	//ERRORCHECK !!! need to be done by calling routine for parameters
	//parameters need to be smaller than corresponding nx and ny
	return & pLine[x * ny];
}
*/ // internet says: dont do this, use operator(x,y)

/**
 * care: ERRORCHECK is missing for dimensions
 */
template <class T>
inline  T& Array2D<T>::operator()(unsigned int row, unsigned int col)
{
	return pLine.get()[row * width + col];
}

/**
 * with error checking (array bounds)
 * @param i
 * @return
 */
template <class T>
inline  T& Array2D<T>::at(unsigned long long int i)
{
	if(i < length)
		return pLine.get()[i];
	else
	{
		std::cout << "ERROR: index out of array dimension, last element returned" << std::endl;
		std::cout << "Index i was " <<i << std::endl;
		std::cout << "last array index is " << length-1 << std::endl;

		return pLine.get()[length-1];
	}
}

template <class T>
inline const unsigned long long int  Array2D<T>::size() const
{
	return length;
}


#endif /* ARRAY2D_HPP_ */
