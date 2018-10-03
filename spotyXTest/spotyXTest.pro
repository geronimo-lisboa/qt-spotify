QT -= gui
QT += core network sql webenginewidgets

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../spotyXLogic/release/ -lspotyXLogic
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../spotyXLogic/debug/ -lspotyXLogic

INCLUDEPATH += $$PWD/../spotyXLogic
DEPENDPATH += $$PWD/../spotyXLogic

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../spotyXLogic/release/libspotyXLogic.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../spotyXLogic/debug/libspotyXLogic.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../spotyXLogic/release/spotyXLogic.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../spotyXLogic/debug/spotyXLogic.lib

DISTFILES += \
    gmock/internal/custom/README.md \
    gtest/internal/custom/README.md \
    gmock/gmock-generated-nice-strict.h.pump \
    gtest/internal/gtest-param-util-generated.h.pump \
    gtest/internal/gtest-type-util.h.pump

HEADERS += \
    gmock/internal/custom/gmock-generated-actions.h \
    gmock/internal/custom/gmock-generated-actions.h.pump \
    gmock/internal/custom/gmock-matchers.h \
    gmock/internal/custom/gmock-port.h \
    gmock/internal/gmock-generated-internal-utils.h \
    gmock/internal/gmock-generated-internal-utils.h.pump \
    gmock/internal/gmock-internal-utils.h \
    gmock/internal/gmock-port.h \
    gmock/gmock-actions.h \
    gmock/gmock-cardinalities.h \
    gmock/gmock-generated-actions.h \
    gmock/gmock-generated-actions.h.pump \
    gmock/gmock-generated-function-mockers.h \
    gmock/gmock-generated-function-mockers.h.pump \
    gmock/gmock-generated-matchers.h \
    gmock/gmock-generated-matchers.h.pump \
    gmock/gmock-generated-nice-strict.h \
    gmock/gmock-matchers.h \
    gmock/gmock-more-actions.h \
    gmock/gmock-more-matchers.h \
    gmock/gmock-spec-builders.h \
    gmock/gmock.h \
    gtest/internal/custom/gtest-port.h \
    gtest/internal/custom/gtest-printers.h \
    gtest/internal/custom/gtest.h \
    gtest/internal/gtest-death-test-internal.h \
    gtest/internal/gtest-filepath.h \
    gtest/internal/gtest-internal.h \
    gtest/internal/gtest-linked_ptr.h \
    gtest/internal/gtest-param-util-generated.h \
    gtest/internal/gtest-param-util.h \
    gtest/internal/gtest-port-arch.h \
    gtest/internal/gtest-port.h \
    gtest/internal/gtest-string.h \
    gtest/internal/gtest-tuple.h \
    gtest/internal/gtest-tuple.h.pump \
    gtest/internal/gtest-type-util.h \
    gtest/gtest-death-test.h \
    gtest/gtest-message.h \
    gtest/gtest-param-test.h \
    gtest/gtest-param-test.h.pump \
    gtest/gtest-printers.h \
    gtest/gtest-spi.h \
    gtest/gtest-test-part.h \
    gtest/gtest-typed-test.h \
    gtest/gtest.h \
    gtest/gtest_pred_impl.h \
    gtest/gtest_prod.h

LIBS += D:/programacao/estudos-qt/projetoProva/spotyX/spotyXTest/lib/gtestd.lib
LIBS += D:/programacao/estudos-qt/projetoProva/spotyX/spotyXTest/lib/gmockd.lib
