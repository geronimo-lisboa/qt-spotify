#ifndef TwoRecordsWithSameIdException_h
#define TwoRecordsWithSameIdException_h
#include <stdexcept>
using namespace std;
class TwoRecordsWithSameIdException:public runtime_error
{
public:
    TwoRecordsWithSameIdException():
        runtime_error("duas entidades com mesmo id na mesma tabela, o banco está louco"){

    }

};

#endif
