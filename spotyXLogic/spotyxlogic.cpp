#include "spotyxlogic.h"


teste::Spotylibrary::Spotylibrary(QObject *parent):
    QObject (parent)
{

}

void teste::Spotylibrary::foo()
{
    emit testSignal("hello lib");
}
