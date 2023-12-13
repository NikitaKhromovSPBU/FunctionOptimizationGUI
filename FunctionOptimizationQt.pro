QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++23

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    AbsoluteValueDifferenceSC.cpp \
    ExpModulatedSin.cpp \
    FletcherReevesOptimizer.cpp \
    GeneralFunction.cpp \
    GeneralOptimizer.cpp \
    GeneralStopCriterion.cpp \
    HimmelblauFunction.cpp \
    IterationsNumberSC.cpp \
    LeviFunction.cpp \
    RectangularArea.cpp \
    RelativeDifferenceSC.cpp \
    RosenbrockFunction.cpp \
    StohasticOptimizer.cpp \
    plotscene.cpp \
    settings.cpp

HEADERS += \
    mainwindow.h \
    AbsoluteValueDifferenceSC.h \
    ExpModulatedSin.h \
    FletcherReevesOptimizer.h \
    GeneralFunction.h \
    GeneralOptimizer.h \
    GeneralStopCriterion.h \
    HimmelblauFunction.h \
    IterationsNumberSC.h \
    LeviFunction.h \
    RectangularArea.h \
    RelativeDifferenceSC.h \
    RosenbrockFunction.h \
    StohasticOptimizer.h \
    plotscene.h \
    settings.h

FORMS += \
    mainwindow.ui \
    settings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
