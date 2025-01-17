QT       += core gui
QMAKE_CXXFLAGS += -Wa,-mbig-obj
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Info_II/clases/Plotter_Casero/build/Desktop_Qt_6_7_2_MinGW_64_bit-Debug/release/ -lPlotter_Casero
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Info_II/clases/Plotter_Casero/build/Desktop_Qt_6_7_2_MinGW_64_bit-Debug/debug/ -lPlotter_Casero

INCLUDEPATH += $$PWD/../Info_II/clases/Plotter_Casero
DEPENDPATH += $$PWD/../Info_II/clases/Plotter_Casero

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../Info_II/clases/Plotter_Casero/build/Desktop_Qt_6_7_2_MinGW_64_bit-Debug/release/libPlotter_Casero.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../Info_II/clases/Plotter_Casero/build/Desktop_Qt_6_7_2_MinGW_64_bit-Debug/debug/libPlotter_Casero.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../Info_II/clases/Plotter_Casero/build/Desktop_Qt_6_7_2_MinGW_64_bit-Debug/release/Plotter_Casero.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../Info_II/clases/Plotter_Casero/build/Desktop_Qt_6_7_2_MinGW_64_bit-Debug/debug/Plotter_Casero.lib

LIBS += -L"C:\DLLS\QcustomPlot"
LIBS += -L"C:\DLLS\MuParser"
INCLUDEPATH +="C:\DLLS\QcustomPlot"
INCLUDEPATH +="C:\DLLS\MuParser"
LIBS += -lqcustomplotd2
LIBS += -lMuParserDLL_Make
