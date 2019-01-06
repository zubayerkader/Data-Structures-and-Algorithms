#ifndef STACKEXCEPTIONS_H
#define STACKEXCEPTIONS_H

#include <string>
#include "RuntimeException.h"


class StackEmpty : public RuntimeException {
public:
StackEmpty(const std::string& err) : RuntimeException(err) {}
};

class StackFull : public RuntimeException {
public:
	StackFull(const std::string& err) : RuntimeException(err) {}
};

#endif
