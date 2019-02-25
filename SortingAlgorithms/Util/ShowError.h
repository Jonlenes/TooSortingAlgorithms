#ifndef SHOWERR_H
#define SHOWERR_H

//includes Qt
#include <QWidget>

//includes c++
#include <iostream>

using namespace std;

class ShowError
{
public:
    static void error(const string &e, bool aviso = false);
};

#endif // SHOWERR_H
