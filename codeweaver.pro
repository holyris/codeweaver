TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt
QT += widgets

OPENCV_LIB = $${OPENCV_DIR}/x64/vc14/lib
OPENCV_INCLUDE = $${INCLUDEPATH}/opencv2

SOURCES += main.cpp \
    detection.cpp \
    carte.cpp \
    case.cpp \
    gamewindow.cpp \
    personnage.cpp \
    controller.cpp \
    partie.cpp \
    message.cpp \
    cristal.cpp

LIBS += -lopencv_videoio -lopencv_highgui -lopencv_core -lopencv_imgproc -lopencv_aruco
#LIBS += -L/home/alexandre/Téléchargements/aruco-3.1.0/aruco_src/lib -laruco

HEADERS += \
    detection.h \
    carte.h \
    case.h \
    gamewindow.h \
    personnage.h \
    controller.h \
    partie.h \
    message.h \
    cristal.h

DISTFILES +=

FORMS +=
