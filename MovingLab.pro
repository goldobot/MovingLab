#-------------------------------------------------
#
# Project created by QtCreator 2018-05-07T21:58:37
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport

TARGET = MovingLab
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
#DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

*msvc* { # visual studio spec filter
    QMAKE_CXXFLAGS += -MP

    # add the desired -O3 if not present
    #QMAKE_CXXFLAGS += /fp:fast
    #QMAKE_CXXFLAGS += /fp:strict
}

#add additional compiler for asm source using MS 2017 macro assembler 64 bit
#ml64.name = ML64 ${QMAKE_FILE_IN}
#ml64.input = ASM_FILES
#ml64.variable_out = OBJECTS
#ml64.commands = ML64 /c ${QMAKE_FILE_NAME} /Fo ${QMAKE_FILE_OUT}
#ml64.output = ${QMAKE_VAR_OBJECTS_DIR}${QMAKE_FILE_IN_BASE}$${first(QMAKE_EXT_OBJ)}
#ml64.CONFIG += target_predeps
#QMAKE_EXTRA_COMPILERS  += ml64



# Optimize compilation time
PRECOMPILED_HEADER = Pch/my_precompiled_header.h
CONFIG += precompile_header


## List of all modules used by the project
listOfModulesFolders = . \
    ./Algo/CoreSlam \
    ./Algo/CoreSlamParticlesFilter \
    ./Algo/BreezySlam \
    ./Algo/BreezySlam/coreslam \
    ./Algo/PathFinder \
    ./Drivers/Basic/ScanseLidar \
    ./Drivers/Basic/SerialCom \
    ./Drivers/Basic/Slamware \
    ./Drivers/Basic/Socket \
    ./Drivers/Basic/Vesc \
    ./Drivers/Platform/TwoWheelsBase \
    ./Params \
    ./Tools

## Import all used modules
for(moduleFolder, listOfModulesFolders): \
{
    INCLUDEPATH += $${moduleFolder}
    HEADERS += $$files($${moduleFolder}/*.h, false)
    SOURCES += $$files($${moduleFolder}/*.cpp, false)
    FORMS += $$files($${moduleFolder}/*.ui, false)
    RESOURCES += $$files($${moduleFolder}/*.qrc, false)
    # ASM_FILES += $$files($${moduleFolder}/*.asm, false)
}

