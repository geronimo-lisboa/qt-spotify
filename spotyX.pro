TEMPLATE = subdirs

SUBDIRS += \
    spotyXLogic \
    spotyXGUI


spotyXLogic.subdir = D:/programacao/estudos-qt/projetoProva/spotyX/spotyXLogic
spotyXGUI.subdir =D:/programacao/estudos-qt/projetoProva/spotyX/spotyXGUI

spotyXGUI.depends = spotyXLogic

CONFIG += ordered
