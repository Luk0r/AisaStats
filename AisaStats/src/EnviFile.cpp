/*
 * EnviFile.cpp
 *
 *  Created on: 15.03.2013
 *      Author: schmidan
 */

#include "EnviFile.hpp"


#include <memory>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iostream>
#include <functional>

namespace envi {


BasicHeader::BasicHeader(std::string inFileName):
		headerFileName{inFileName}
{
	readEnviHeader();

	// fill basic header infos
	for(auto x: pvHheaderItemPairs)
	{
		if(x.first == "samples")
			samples = std::stoi(x.second);
		else if(x.first == "lines")
			lines = std::stoi(x.second);
		else if(x.first == "bands")
			bands = std::stoi(x.second);
		else if(x.first == "byte_order")
			byte_order = std::stoi(x.second);
		else if(x.first == "interleave")
		{
			if(x.second == "bil")
				interleave = Interleave::BIL;
			if(x.second == "bip")
				interleave = Interleave::BIP;
			if(x.second == "bsq")
				interleave = Interleave::BSQ;
		}
		else if(x.first == "datatype")
			datatype = std::stoi(x.second);

	}
}

void BasicHeader::readEnviHeader()
{
	std::ifstream inFile(headerFileName.c_str());

	if(inFile.good())
	{
		std::stringstream strStream;
		std::string line;

		inFile.seekg( std::ios::beg);
		while(std::getline(inFile, line))
		{
			strStream.str(line);
			std::string checkString, buffer;

			//if line containes "=", then put everything before to "first" and rest to "second"
			std::size_t pos = line.find("=");
			if(pos != std::string::npos)
			{
				std::string first {line.substr(0, pos)};
				std::string second {line.substr(pos+1, line.size())};
				pvHheaderItemPairs->push_back(
						std::pair<std::string, std::string>(std::move(first), std::move(second) ) );
			}
			else
			{
				if( !pvHheaderItemPairs->empty() )
					pvHheaderItemPairs->back().second.append(line);
			}
		}


#if DEBUG
		for( auto const & x: pvHheaderItemPairs)
		{
			std::cout << "|" << x.first << "|" << std::endl <<
					"   " << "|" << x.second << "|" << std::endl << std::endl;
		}
#endif


		for( auto& x: pvHheaderItemPairs) // removes all spaces and "{" and "}"
		{
			x.first.erase(std::remove(x.first.begin(), x.first.end(), ' ' ),
		    	x.first.end());

			/*
			 * THIS IS NOT WORKING, 17 seconds template errors in console, compiler bug ? gcc 4.7.2
			 * doing workaround
			 *
			 *  x.second.erase(std::remove( x.second.begin(), x.second.end(), [](const char & element) {
			 *	return (element == ' ');}),
			 *	x.second.end());
			 */
		 	x.second.erase(std::remove(x.second.begin(), x.second.end(), ' ' ),
		    		x.second.end());
		 	x.second.erase(std::remove(x.second.begin(), x.second.end(), '{' ),
		    		x.second.end());
		 	x.second.erase(std::remove(x.second.begin(), x.second.end(), '}' ),
		    		x.second.end());
		}

//#if DEBUG
		for( auto const & x: pvHheaderItemPairs)
		{
			std::cout << "|" << x.first << "|" << std::endl <<
					"   " << "|" << x.second << "|" << std::endl << std::endl;
		}
//#endif
	}

}
} /* namespace envi */
