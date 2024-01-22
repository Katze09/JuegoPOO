#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/AudioPlayer.o \
	${OBJECTDIR}/Background.o \
	${OBJECTDIR}/Bullets.o \
	${OBJECTDIR}/Enemies.o \
	${OBJECTDIR}/Level.o \
	${OBJECTDIR}/Loader.o \
	${OBJECTDIR}/Menu.o \
	${OBJECTDIR}/Object.o \
	${OBJECTDIR}/Obstacle.o \
	${OBJECTDIR}/Player.o \
	${OBJECTDIR}/States.o \
	${OBJECTDIR}/Texts.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/tinyxml2.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-mwindows -lwinmm
CXXFLAGS=-mwindows -lwinmm

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../../../../../SDL2/lib -L../../../../../SDL2_Image/lib -L../../../../../SDL2_MIXER/lib -L../../../../../SDL2_TTF/lib

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/juegopoo.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/juegopoo.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/juegopoo ${OBJECTFILES} ${LDLIBSOPTIONS} -lmingw32 -lsdl2main -lsdl2 -lstdc++ -lSDL2_ttf -lSDL2_mixer -lSDL2_image

${OBJECTDIR}/AudioPlayer.o: AudioPlayer.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_Image/include -I../../../../../SDL2_MIXER/include -I../../../../../SDL2_TTF/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AudioPlayer.o AudioPlayer.cpp

${OBJECTDIR}/Background.o: Background.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_Image/include -I../../../../../SDL2_MIXER/include -I../../../../../SDL2_TTF/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Background.o Background.cpp

${OBJECTDIR}/Bullets.o: Bullets.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_Image/include -I../../../../../SDL2_MIXER/include -I../../../../../SDL2_TTF/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Bullets.o Bullets.cpp

${OBJECTDIR}/Enemies.o: Enemies.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_Image/include -I../../../../../SDL2_MIXER/include -I../../../../../SDL2_TTF/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Enemies.o Enemies.cpp

${OBJECTDIR}/Level.o: Level.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_Image/include -I../../../../../SDL2_MIXER/include -I../../../../../SDL2_TTF/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Level.o Level.cpp

${OBJECTDIR}/Loader.o: Loader.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_Image/include -I../../../../../SDL2_MIXER/include -I../../../../../SDL2_TTF/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Loader.o Loader.cpp

${OBJECTDIR}/Menu.o: Menu.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_Image/include -I../../../../../SDL2_MIXER/include -I../../../../../SDL2_TTF/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Menu.o Menu.cpp

${OBJECTDIR}/Object.o: Object.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_Image/include -I../../../../../SDL2_MIXER/include -I../../../../../SDL2_TTF/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Object.o Object.cpp

${OBJECTDIR}/Obstacle.o: Obstacle.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_Image/include -I../../../../../SDL2_MIXER/include -I../../../../../SDL2_TTF/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Obstacle.o Obstacle.cpp

${OBJECTDIR}/Player.o: Player.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_Image/include -I../../../../../SDL2_MIXER/include -I../../../../../SDL2_TTF/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Player.o Player.cpp

${OBJECTDIR}/States.o: States.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_Image/include -I../../../../../SDL2_MIXER/include -I../../../../../SDL2_TTF/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/States.o States.cpp

${OBJECTDIR}/Texts.o: Texts.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_Image/include -I../../../../../SDL2_MIXER/include -I../../../../../SDL2_TTF/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Texts.o Texts.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_Image/include -I../../../../../SDL2_MIXER/include -I../../../../../SDL2_TTF/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/tinyxml2.o: tinyxml2.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_Image/include -I../../../../../SDL2_MIXER/include -I../../../../../SDL2_TTF/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tinyxml2.o tinyxml2.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
