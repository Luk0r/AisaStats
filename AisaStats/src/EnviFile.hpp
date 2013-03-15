/*
 * EnviFile.hpp
 *
 *  Created on: 15.03.2013
 *      Author: schmidan
 */

#ifndef ENVIFILE_HPP_
#define ENVIFILE_HPP_

#include <cstdint> // uint32_t  ...
#include <vector>
#include <utility> // pair
#include <string>
#include <memory>

namespace envi {

class BasicHeader
{
public:
	BasicHeader(std::string);

	std::shared_ptr< std::vector< std::pair<std::string, std::string>> > getHeaderItemsPairs()
			{
				return pvHheaderItemPairs;
			}



private:
	enum Interleave{BIP, BIL, BSQ} interleave;
	uint32_t samples;
	uint32_t lines;
	uint32_t bands;

	uint8_t datatype;
	uint8_t byte_order;

	std::string headerFileName;

	std::shared_ptr< std::vector< std::pair<std::string, std::string>> > pvHheaderItemPairs;

	void readEnviHeader();

};

class EnviFile : public BasicHeader  {
public:
	EnviFile();
	~EnviFile();

private:
	std::string fileName;


	void read_bil(); // can return 1 line or 1 slice
	void read_bip(); // can 1 spectrum or 1 line
	void read_bsq(); // can return 1 band


};








} /* namespace envi */


#endif /* ENVIFILE_HPP_ */
