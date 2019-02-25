#include "ConnectionException.h"

ConnectionException::ConnectionException(std::string error) : Exception("ConnectionException", error) { }
