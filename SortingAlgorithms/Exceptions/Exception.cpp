#include "Exception.h"

Exception::Exception(std::string name, std::string error) : name(name), error(error) { }

std::string Exception::getError()
{
   return error;
}
