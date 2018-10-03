#ifndef IniFileNotPresentException_h
#define IniFileNotPresentException_h
#include <stdexcept>
using namespace std;
class IniFileNotPresentException:public runtime_error
{
public:
    IniFileNotPresentException():
        runtime_error("ini não encontrado"){

    }

};

#endif
