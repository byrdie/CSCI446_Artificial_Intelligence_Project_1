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
	${OBJECTDIR}/backtracking.o \
	${OBJECTDIR}/cairo_int.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/map_data_types.o \
	${OBJECTDIR}/map_problem_gen.o \
	${OBJECTDIR}/min-conflicts.o \
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
LDLIBSOPTIONS=`pkg-config --libs cairo` `pkg-config --libs cairo-fc` `pkg-config --libs cairo-ft` `pkg-config --libs cairo-gobject` `pkg-config --libs cairo-pdf` `pkg-config --libs cairo-png` `pkg-config --libs cairo-ps` `pkg-config --libs cairo-script` `pkg-config --libs cairo-svg` `pkg-config --libs cairo-tee` `pkg-config --libs cairo-xcb` `pkg-config --libs cairo-xcb-shm` `pkg-config --libs cairo-xlib` `pkg-config --libs cairo-xlib-xrender` -lboost_atomic -lboost_atomic -lboost_chrono -lboost_chrono -lboost_context -lboost_context -lboost_coroutine -lboost_date_time -lboost_date_time -lboost_exception -lboost_filesystem -lboost_filesystem -lboost_graph -lboost_graph -lboost_graph_parallel -lboost_graph_parallel -lboost_iostreams -lboost_iostreams -lboost_locale -lboost_locale -lboost_log -lboost_log -lboost_log_setup -lboost_log_setup -lboost_math_c99 -lboost_math_c99 -lboost_math_c99f -lboost_math_c99f -lboost_math_c99l -lboost_math_c99l -lboost_math_tr1 -lboost_math_tr1 -lboost_math_tr1f -lboost_math_tr1f -lboost_math_tr1l -lboost_math_tr1l -lboost_mpi -lboost_mpi -lboost_mpi_python-py27 -lboost_mpi_python-py27 -lboost_mpi_python-py34 -lboost_mpi_python-py34 -lboost_mpi_python -lboost_mpi_python -lboost_prg_exec_monitor -lboost_prg_exec_monitor -lboost_program_options -lboost_program_options -lboost_python-py27 -lboost_python-py27 -lboost_python-py34 -lboost_python-py34 -lboost_python -lboost_python -lboost_random -lboost_random -lboost_regex -lboost_regex -lboost_serialization -lboost_serialization -lboost_signals -lboost_signals -lboost_system -lboost_system -lboost_test_exec_monitor -lboost_thread -lboost_thread -lboost_timer -lboost_timer -lboost_unit_test_framework -lboost_unit_test_framework -lboost_wave -lboost_wave -lboost_wserialization -lboost_wserialization  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cpp_src

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cpp_src: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cpp_src ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/backtracking.o: backtracking.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags cairo` `pkg-config --cflags cairo-fc` `pkg-config --cflags cairo-ft` `pkg-config --cflags cairo-gobject` `pkg-config --cflags cairo-pdf` `pkg-config --cflags cairo-png` `pkg-config --cflags cairo-ps` `pkg-config --cflags cairo-script` `pkg-config --cflags cairo-svg` `pkg-config --cflags cairo-tee` `pkg-config --cflags cairo-xcb` `pkg-config --cflags cairo-xcb-shm` `pkg-config --cflags cairo-xlib` `pkg-config --cflags cairo-xlib-xrender` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/backtracking.o backtracking.cpp

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

${OBJECTDIR}/min-conflicts.o: min-conflicts.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags cairo` `pkg-config --cflags cairo-fc` `pkg-config --cflags cairo-ft` `pkg-config --cflags cairo-gobject` `pkg-config --cflags cairo-pdf` `pkg-config --cflags cairo-png` `pkg-config --cflags cairo-ps` `pkg-config --cflags cairo-script` `pkg-config --cflags cairo-svg` `pkg-config --cflags cairo-tee` `pkg-config --cflags cairo-xcb` `pkg-config --cflags cairo-xcb-shm` `pkg-config --cflags cairo-xlib` `pkg-config --cflags cairo-xlib-xrender` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/min-conflicts.o min-conflicts.cpp

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
