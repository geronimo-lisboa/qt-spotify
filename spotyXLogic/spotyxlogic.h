#ifndef SPOTYXLOGIC_H
#define SPOTYXLOGIC_H
#include <QObject>

namespace teste
{
class Spotylibrary : public QObject
{
    Q_OBJECT
public:
    Spotylibrary(QObject* parent=nullptr);
    void foo();
signals:
    void testSignal(QString str);
};
}
#endif // SPOTYXLOGIC_H
