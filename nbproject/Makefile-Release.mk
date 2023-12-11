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
CC=clang
CCC=clang++
CXX=clang++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=CLang-Windows
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
	${OBJECTDIR}/Object.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../../../../../Program\ Files/LLVM/lib -lsfml-graphics -lFLAC -lfreetype -logg -lopenal32 -lsfml-audio-d -lsfml-audio-s-d -lsfml-audio-s -lsfml-audio -lsfml-graphics-d -lsfml-graphics-s-d -lsfml-graphics-s -lsfml-main-d -lsfml-main -lsfml-network-d -lsfml-network-s-d -lsfml-network-s -lsfml-network -lsfml-system-d -lsfml-system-s-d -lsfml-system-s -lsfml-system -lsfml-window-d -lsfml-window-s-d -lsfml-window-s -lsfml-window -lvorbis -lvorbisenc -lvorbisfile

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/juegopoo.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/juegopoo.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/juegopoo ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Object.o: Object.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -I../../../../../Program\ Files/LLVM/include -include ../../../../../Program\ Files/LLVM/include/clang-c/BuildSystem.h -include ../../../../../Program\ Files/LLVM/include/clang-c/CXCompilationDatabase.h -include ../../../../../Program\ Files/LLVM/include/clang-c/CXDiagnostic.h -include ../../../../../Program\ Files/LLVM/include/clang-c/CXErrorCode.h -include ../../../../../Program\ Files/LLVM/include/clang-c/CXFile.h -include ../../../../../Program\ Files/LLVM/include/clang-c/CXSourceLocation.h -include ../../../../../Program\ Files/LLVM/include/clang-c/CXString.h -include ../../../../../Program\ Files/LLVM/include/clang-c/Documentation.h -include ../../../../../Program\ Files/LLVM/include/clang-c/ExternC.h -include ../../../../../Program\ Files/LLVM/include/clang-c/FatalErrorHandler.h -include ../../../../../Program\ Files/LLVM/include/clang-c/Index.h -include ../../../../../Program\ Files/LLVM/include/clang-c/Platform.h -include ../../../../../Program\ Files/LLVM/include/clang-c/Rewrite.h -include ../../../../../Program\ Files/LLVM/include/llvm-c -include ../../../../../Program\ Files/LLVM/include/llvm-c/Remarks.h -include ../../../../../Program\ Files/LLVM/include/llvm-c/lto.h -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Object.o Object.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -I../../../../../Program\ Files/LLVM/include -include ../../../../../Program\ Files/LLVM/include/clang-c/BuildSystem.h -include ../../../../../Program\ Files/LLVM/include/clang-c/CXCompilationDatabase.h -include ../../../../../Program\ Files/LLVM/include/clang-c/CXDiagnostic.h -include ../../../../../Program\ Files/LLVM/include/clang-c/CXErrorCode.h -include ../../../../../Program\ Files/LLVM/include/clang-c/CXFile.h -include ../../../../../Program\ Files/LLVM/include/clang-c/CXSourceLocation.h -include ../../../../../Program\ Files/LLVM/include/clang-c/CXString.h -include ../../../../../Program\ Files/LLVM/include/clang-c/Documentation.h -include ../../../../../Program\ Files/LLVM/include/clang-c/ExternC.h -include ../../../../../Program\ Files/LLVM/include/clang-c/FatalErrorHandler.h -include ../../../../../Program\ Files/LLVM/include/clang-c/Index.h -include ../../../../../Program\ Files/LLVM/include/clang-c/Platform.h -include ../../../../../Program\ Files/LLVM/include/clang-c/Rewrite.h -include ../../../../../Program\ Files/LLVM/include/llvm-c -include ../../../../../Program\ Files/LLVM/include/llvm-c/Remarks.h -include ../../../../../Program\ Files/LLVM/include/llvm-c/lto.h -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

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
