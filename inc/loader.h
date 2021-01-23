#ifndef LOADER_H
#define LOADER_H


#include <stdint.h>
#include <string>
#include <vector>

class Binary;
class Section;
class Symbol;

class Symbol {
public:
	enum SymbolType {
		SYM_TYPE_UKN = 0,
		SYM_TYPE_FUNC = 1
	};

	Symbol() : type(SYM_TYPE_FUNC), name(), addr(0) {}

	SymbolType type;
	std::string name;
	uint64_t addr;
};


