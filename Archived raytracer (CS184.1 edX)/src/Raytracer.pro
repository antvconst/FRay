TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    fmath.cpp \
    fray.cpp \
    frenderer.cpp \
    pngwriter.cc

HEADERS += \
    fmath.h \
    fray.h \
    frenderer.h \
    pngwriter.h

LIBS += -L'C:\Users\Anton Konstantinov\Desktop\Raytracer\lib' -llibpng

QMAKE_CXXFLAGS += -std=c++11 -DNO_FREETYPE -Wunused-parameter
