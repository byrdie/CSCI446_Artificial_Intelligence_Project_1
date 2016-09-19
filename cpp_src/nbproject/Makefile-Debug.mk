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
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/cairo_int.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/map_data_types.o \
	${OBJECTDIR}/map_problem_gen.o \
	${OBJECTDIR}/newfile.o


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
LDLIBSOPTIONS=`pkg-config --libs cairo` `pkg-config --libs cairo-fc` `pkg-config --libs cairo-ft` `pkg-config --libs cairo-gobject` `pkg-config --libs cairo-pdf` `pkg-config --libs cairo-png` `pkg-config --libs cairo-ps` `pkg-config --libs cairo-script` `pkg-config --libs cairo-svg` `pkg-config --libs cairo-tee` `pkg-config --libs cairo-xcb` `pkg-config --libs cairo-xcb-shm` `pkg-config --libs cairo-xlib` `pkg-config --libs cairo-xlib-xrender`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cpp_src

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cpp_src: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cpp_src ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/cairo_int.o: cairo_int.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags cairo` `pkg-config --cflags cairo-fc` `pkg-config --cflags cairo-ft` `pkg-config --cflags cairo-gobject` `pkg-config --cflags cairo-pdf` `pkg-config --cflags cairo-png` `pkg-config --cflags cairo-ps` `pkg-config --cflags cairo-script` `pkg-config --cflags cairo-svg` `pkg-config --cflags cairo-tee` `pkg-config --cflags cairo-xcb` `pkg-config --cflags cairo-xcb-shm` `pkg-config --cflags cairo-xlib` `pkg-config --cflags cairo-xlib-xrender` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cairo_int.o cairo_int.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags cairo` `pkg-config --cflags cairo-fc` `pkg-config --cflags cairo-ft` `pkg-config --cflags cairo-gobject` `pkg-config --cflags cairo-pdf` `pkg-config --cflags cairo-png` `pkg-config --cflags cairo-ps` `pkg-config --cflags cairo-script` `pkg-config --cflags cairo-svg` `pkg-config --cflags cairo-tee` `pkg-config --cflags cairo-xcb` `pkg-config --cflags cairo-xcb-shm` `pkg-config --cflags cairo-xlib` `pkg-config --cflags cairo-xlib-xrender` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/map_data_types.o: map_data_types.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags cairo` `pkg-config --cflags cairo-fc` `pkg-config --cflags cairo-ft` `pkg-config --cflags cairo-gobject` `pkg-config --cflags cairo-pdf` `pkg-config --cflags cairo-png` `pkg-config --cflags cairo-ps` `pkg-config --cflags cairo-script` `pkg-config --cflags cairo-svg` `pkg-config --cflags cairo-tee` `pkg-config --cflags cairo-xcb` `pkg-config --cflags cairo-xcb-shm` `pkg-config --cflags cairo-xlib` `pkg-config --cflags cairo-xlib-xrender` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/map_data_types.o map_data_types.cpp

${OBJECTDIR}/map_problem_gen.o: map_problem_gen.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags cairo` `pkg-config --cflags cairo-fc` `pkg-config --cflags cairo-ft` `pkg-config --cflags cairo-gobject` `pkg-config --cflags cairo-pdf` `pkg-config --cflags cairo-png` `pkg-config --cflags cairo-ps` `pkg-config --cflags cairo-script` `pkg-config --cflags cairo-svg` `pkg-config --cflags cairo-tee` `pkg-config --cflags cairo-xcb` `pkg-config --cflags cairo-xcb-shm` `pkg-config --cflags cairo-xlib` `pkg-config --cflags cairo-xlib-xrender` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/map_problem_gen.o map_problem_gen.cpp

${OBJECTDIR}/newfile.o: newfile.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g `pkg-config --cflags cairo` `pkg-config --cflags cairo-fc` `pkg-config --cflags cairo-ft` `pkg-config --cflags cairo-gobject` `pkg-config --cflags cairo-pdf` `pkg-config --cflags cairo-png` `pkg-config --cflags cairo-ps` `pkg-config --cflags cairo-script` `pkg-config --cflags cairo-svg` `pkg-config --cflags cairo-tee` `pkg-config --cflags cairo-xcb` `pkg-config --cflags cairo-xcb-shm` `pkg-config --cflags cairo-xlib` `pkg-config --cflags cairo-xlib-xrender`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/newfile.o newfile.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cpp_src

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
