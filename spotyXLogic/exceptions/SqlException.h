#ifndef SqlException_h
#define SqlException_h
#include <stdexcept>
using namespace std;
class SqlException:public runtime_error
{
public:
    SqlException():
        runtime_error("SQL EXCEPTION"){

    }

};

#endif
