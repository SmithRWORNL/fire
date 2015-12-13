/**----------------------------------------------------------------------------
 Copyright (c) 2015-, Jay Jay Billings
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.

 * Neither the name of fern nor the names of its
 contributors may be used to endorse or promote products derived from
 this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 Author(s): Jay Jay Billings (jayjaybillings <at> gmail <dot> com)
 -----------------------------------------------------------------------------*/
#ifndef PARSERS_BASICDELIMITEDTEXTPARSER_H_
#define PARSERS_BASICDELIMITEDTEXTPARSER_H_

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "IDelimitedTextParser.h"

namespace fire {

/**
 * Default template for casting strings properly.
 */
template<typename T>
struct StringCaster{
	static T cast(const std::string & value) {return static_cast<T>(value);};
};

/**
 * Implementation of StringCaster for doubles
 */
template<>
struct StringCaster<double>{
	static double cast(const std::string & value) {
		return strtod(value.c_str(),NULL);};
};

/**
 * Implementation of StringCaster for floats
 */
template<>
struct StringCaster<float>{
	static double cast(const std::string & value) {
		return strtof(value.c_str(),NULL);};
};

/**
 * Implementation of StringCaster for ints
 */
template<>
struct StringCaster<int>{
	static double cast(const std::string & value) {
		return atoi(value.c_str());};
};


/**
 * This class implements IDelimitedTextParser to provide a local, file-based,
 * serially executed delimited text parser.
 *
 * isFile() will return true if setSource(std::string) is used
 * isStream() will return true if setSource(std::istream) is used
 * isLocal() always returns true.
 * isParallel() always returns false.
 *
 * The source may either be a file on the local filesystem or an input stream.
 *
 */
template<class T>
class BasicDelimitedTextParser: public IDelimitedTextParser<T> {

protected:

	/**
	 * The source file name used if setSource(string) is called.
	 */
	std::string sourceFile;

	/**
	 * The source stream used if setSource(stream) is called.
	 */
	std::istream sourceStream;

	/**
	 * The delimiter used when parsing the file.
	 */
	std::string delimiter;

	/**
	 * The character that represents a comment and should be skipped.
	 */
	std::string commentChar;

	/**
	 * The vector of data parsed from the file.
	 */
	std::vector<std::vector<T>> data;

public:
	BasicDelimitedTextParser(std::string delim, std::string comment)
		 : delimiter(delim), commentChar(comment), sourceStream(NULL) {};

	virtual ~BasicDelimitedTextParser() {};

	virtual void setSource(const std::string & source) {
		sourceFile = source;
	};

	virtual void setSource(const std::istream & source) {
		throw "Method not yet implemented.";
	};

	virtual const std::string & getSource() {return sourceFile;};

	virtual const std::istream & getSourceStream() {return sourceStream;};

	virtual void parse() {
		// Load the contents of the file
		std::string value, line;
		std::ifstream fileStream(sourceFile);
		if (fileStream.is_open()) {
			while (getline(fileStream,line)) {
				if (!line.empty() && !line.find("#") == 0) {
				   std::stringstream ss(line);
				   std::vector<T> lineVec;
				   while (getline(ss,value,*delimiter.c_str())) {
				       lineVec.push_back(StringCaster<double>::cast(value));
				   }
				   data.push_back(lineVec);
				}
			}
			fileStream.close();
		}
	};

	virtual std::vector<std::vector<T>> & getData() {
		return data;
	};

};

} /* namespace fire */

#endif /* PARSERS_BASICDELIMITEDTEXTPARSER_H_ */
