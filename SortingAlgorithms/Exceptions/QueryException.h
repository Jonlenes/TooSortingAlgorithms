#ifndef QUERYEXCEPTION_H
#define QUERYEXCEPTION_H

#include "Exception.h"

class QueryException : public Exception
{
public:
    QueryException(std::string error = "");
};

#endif // QUERYEXCEPTION_H
