#include "QueryException.h"

QueryException::QueryException(std::string error) : Exception("QueryException", error) { }
