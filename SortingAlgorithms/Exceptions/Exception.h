#ifndef EXCEPTION_H
#define EXCEPTION_H

//includes c++
#include <exception>
#include <string>

class Exception : public std::exception
{
public:
    Exception(std::string name, std::string error);

    virtual std::string getError();
    const char * what() const throw() override final { return name.c_str(); }

private:
    std::string name;
    std::string error;
};

#endif // EXCEPTION_H
