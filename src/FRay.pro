TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp \
    geometry/sphere.cpp \
    rendering/scene.cpp \
    rendering/camera.cpp \
    math/math.cpp \
    rendering/raytracer.cpp \
    rendering/sampler.cpp

HEADERS += \
    math/math.h \
    math/matrix.h \
    math/vector.h \
    geometry/geometry.h \
    geometry/sphere.h \
    utils/utils.h \
    rendering/scene.h \
    rendering/ray.h \
    rendering/camera.h \
    rendering/shading/material.h \
    rendering/raytracer.h \
    rendering/sampler.h

QMAKE_CXXFLAGS += -std=c++11 -DNO_FREETYPE -Wunused-parameter

