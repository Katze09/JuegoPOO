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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Background.o \
	${OBJECTDIR}/Bullets.o \
	${OBJECTDIR}/Enemies.o \
	${OBJECTDIR}/Level.o \
	${OBJECTDIR}/Loader.o \
	${OBJECTDIR}/Object.o \
	${OBJECTDIR}/Obstacle.o \
	${OBJECTDIR}/Player.o \
	${OBJECTDIR}/States.o \
	${OBJECTDIR}/Texts.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/tinyxml2.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/tests/newsimpletest.o

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
LDLIBSOPTIONS=-L../../../../../SDL2/lib -L../../../../../SDL2_TTF/lib

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/juegopoo.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/juegopoo.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/juegopoo ${OBJECTFILES} ${LDLIBSOPTIONS} -lmingw32 -lsdl2main -lsdl2 -lstdc++ -lSDL2_ttf

${OBJECTDIR}/Background.o: Background.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_TTF/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Background.o Background.cpp

${OBJECTDIR}/Bullets.o: Bullets.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_TTF/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Bullets.o Bullets.cpp

${OBJECTDIR}/Enemies.o: Enemies.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_TTF/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Enemies.o Enemies.cpp

${OBJECTDIR}/Level.o: Level.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_TTF/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Level.o Level.cpp

${OBJECTDIR}/Loader.o: Loader.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_TTF/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Loader.o Loader.cpp

${OBJECTDIR}/Object.o: Object.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_TTF/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Object.o Object.cpp

${OBJECTDIR}/Obstacle.o: Obstacle.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_TTF/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Obstacle.o Obstacle.cpp

${OBJECTDIR}/Player.o: Player.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_TTF/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Player.o Player.cpp

${OBJECTDIR}/States.o: States.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_TTF/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/States.o States.cpp

${OBJECTDIR}/Texts.o: Texts.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_TTF/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Texts.o Texts.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_TTF/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/tinyxml2.o: tinyxml2.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_TTF/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tinyxml2.o tinyxml2.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/newsimpletest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}   


${TESTDIR}/tests/newsimpletest.o: tests/newsimpletest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_TTF/include -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/newsimpletest.o tests/newsimpletest.cpp


${OBJECTDIR}/Background_nomain.o: ${OBJECTDIR}/Background.o Background.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Background.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_TTF/include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Background_nomain.o Background.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Background.o ${OBJECTDIR}/Background_nomain.o;\
	fi

${OBJECTDIR}/Bullets_nomain.o: ${OBJECTDIR}/Bullets.o Bullets.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Bullets.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_TTF/include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Bullets_nomain.o Bullets.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Bullets.o ${OBJECTDIR}/Bullets_nomain.o;\
	fi

${OBJECTDIR}/Enemies_nomain.o: ${OBJECTDIR}/Enemies.o Enemies.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Enemies.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_TTF/include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Enemies_nomain.o Enemies.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Enemies.o ${OBJECTDIR}/Enemies_nomain.o;\
	fi

${OBJECTDIR}/Level_nomain.o: ${OBJECTDIR}/Level.o Level.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Level.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_TTF/include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Level_nomain.o Level.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Level.o ${OBJECTDIR}/Level_nomain.o;\
	fi

${OBJECTDIR}/Loader_nomain.o: ${OBJECTDIR}/Loader.o Loader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Loader.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_TTF/include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Loader_nomain.o Loader.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Loader.o ${OBJECTDIR}/Loader_nomain.o;\
	fi

${OBJECTDIR}/Object_nomain.o: ${OBJECTDIR}/Object.o Object.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Object.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_TTF/include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Object_nomain.o Object.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Object.o ${OBJECTDIR}/Object_nomain.o;\
	fi

${OBJECTDIR}/Obstacle_nomain.o: ${OBJECTDIR}/Obstacle.o Obstacle.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Obstacle.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_TTF/include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Obstacle_nomain.o Obstacle.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Obstacle.o ${OBJECTDIR}/Obstacle_nomain.o;\
	fi

${OBJECTDIR}/Player_nomain.o: ${OBJECTDIR}/Player.o Player.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Player.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_TTF/include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Player_nomain.o Player.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Player.o ${OBJECTDIR}/Player_nomain.o;\
	fi

${OBJECTDIR}/States_nomain.o: ${OBJECTDIR}/States.o States.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/States.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_TTF/include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/States_nomain.o States.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/States.o ${OBJECTDIR}/States_nomain.o;\
	fi

${OBJECTDIR}/Texts_nomain.o: ${OBJECTDIR}/Texts.o Texts.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Texts.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_TTF/include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Texts_nomain.o Texts.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Texts.o ${OBJECTDIR}/Texts_nomain.o;\
	fi

${OBJECTDIR}/main_nomain.o: ${OBJECTDIR}/main.o main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_TTF/include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main_nomain.o main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
	fi

${OBJECTDIR}/tinyxml2_nomain.o: ${OBJECTDIR}/tinyxml2.o tinyxml2.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tinyxml2.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -I../../../../../SDL2/include -I../../../../../SDL2_TTF/include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tinyxml2_nomain.o tinyxml2.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/tinyxml2.o ${OBJECTDIR}/tinyxml2_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
