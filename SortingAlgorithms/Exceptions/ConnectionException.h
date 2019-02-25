#ifndef CONNECTIONEXCEPTION_H
#define CONNECTIONEXCEPTION_H

#include "Exception.h"

class ConnectionException : public Exception
{
public:
    ConnectionException(std::string error = "");
};

#endif // CONNECTIONEXCEPTION_H
