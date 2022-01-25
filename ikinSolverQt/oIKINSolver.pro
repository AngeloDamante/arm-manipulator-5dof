TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        CArm5Dof.cpp \
        main.cpp

HEADERS += \
    CArm5Dof.h \
    CJoint.h \
    CLink.h
