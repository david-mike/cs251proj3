#ifndef _SYMBOL_HPP_
#define _SYMBOL_HPP_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "key.hpp"

class Symbol {

private:
	std::vector<Key> T;
	
	std::map<Key, std::vector<Key>> M;
public:
	Symbol(const std::string&);
	void decrypt(const std::string&);
};

#endif
