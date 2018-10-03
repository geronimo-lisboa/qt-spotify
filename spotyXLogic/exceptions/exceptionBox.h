#ifndef exceptionBox_h
#define exceptionBox_h
#include <QMessageBox>
#include <stdexcept>
////Serve pra mostrar uma caixa de erro.
static inline void showExceptionBox(std::runtime_error& err){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::critical(nullptr,
                                  "exception",
                                  QString::fromLocal8Bit(err.what()),
                                  QMessageBox::Ok);
}
#endif
