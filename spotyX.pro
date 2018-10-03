TEMPLATE = subdirs

SUBDIRS += \
    spotyXLogic \
    spotyXTest\
    spotyXGUI



spotyXLogic.subdir = D:/programacao/estudos-qt/projetoProva/spotyX/spotyXLogic
spotyXGUI.subdir =D:/programacao/estudos-qt/projetoProva/spotyX/spotyXGUI
spotyXTest.subdir =D:/programacao/estudos-qt/projetoProva/spotyX/spotyXTest

spotyXGUI.depends = spotyXLogic
spotyXTest.depends = spotyXLogic

CONFIG += ordered
