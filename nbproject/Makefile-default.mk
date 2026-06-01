#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f
MV=mv
CP=cp

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/StickmanGame.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/StickmanGame.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=main.c src/audio.c src/board_init.c src/display_assets.c src/game_state.c src/keypad.c src/lcd_driver.c src/timing.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.o ${OBJECTDIR}/src/audio.o ${OBJECTDIR}/src/board_init.o ${OBJECTDIR}/src/display_assets.o ${OBJECTDIR}/src/game_state.o ${OBJECTDIR}/src/keypad.o ${OBJECTDIR}/src/lcd_driver.o ${OBJECTDIR}/src/timing.o
POSSIBLE_DEPFILES=${OBJECTDIR}/main.o.d ${OBJECTDIR}/src/audio.o.d ${OBJECTDIR}/src/board_init.o.d ${OBJECTDIR}/src/display_assets.o.d ${OBJECTDIR}/src/game_state.o.d ${OBJECTDIR}/src/keypad.o.d ${OBJECTDIR}/src/lcd_driver.o.d ${OBJECTDIR}/src/timing.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.o ${OBJECTDIR}/src/audio.o ${OBJECTDIR}/src/board_init.o ${OBJECTDIR}/src/display_assets.o ${OBJECTDIR}/src/game_state.o ${OBJECTDIR}/src/keypad.o ${OBJECTDIR}/src/lcd_driver.o ${OBJECTDIR}/src/timing.o

# Source Files
SOURCEFILES=main.c src/audio.c src/board_init.c src/display_assets.c src/game_state.c src/keypad.c src/lcd_driver.c src/timing.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/StickmanGame.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX370F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/71e596147c2e3160ca9563911b6763c53defc02e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}"
	@${RM} ${OBJECTDIR}/main.o.d
	@${RM} ${OBJECTDIR}/main.o
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF) -Iinclude    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"

${OBJECTDIR}/src/audio.o: src/audio.c  .generated_files/flags/default/71e596147c2e3160ca9563911b6763c53defc02e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src"
	@${RM} ${OBJECTDIR}/src/audio.o.d
	@${RM} ${OBJECTDIR}/src/audio.o
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/audio.o.d" -o ${OBJECTDIR}/src/audio.o src/audio.c    -DXPRJ_default=$(CND_CONF) -Iinclude    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"

${OBJECTDIR}/src/board_init.o: src/board_init.c  .generated_files/flags/default/71e596147c2e3160ca9563911b6763c53defc02e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src"
	@${RM} ${OBJECTDIR}/src/board_init.o.d
	@${RM} ${OBJECTDIR}/src/board_init.o
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/board_init.o.d" -o ${OBJECTDIR}/src/board_init.o src/board_init.c    -DXPRJ_default=$(CND_CONF) -Iinclude    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"

${OBJECTDIR}/src/display_assets.o: src/display_assets.c  .generated_files/flags/default/71e596147c2e3160ca9563911b6763c53defc02e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src"
	@${RM} ${OBJECTDIR}/src/display_assets.o.d
	@${RM} ${OBJECTDIR}/src/display_assets.o
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/display_assets.o.d" -o ${OBJECTDIR}/src/display_assets.o src/display_assets.c    -DXPRJ_default=$(CND_CONF) -Iinclude    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"

${OBJECTDIR}/src/game_state.o: src/game_state.c  .generated_files/flags/default/71e596147c2e3160ca9563911b6763c53defc02e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src"
	@${RM} ${OBJECTDIR}/src/game_state.o.d
	@${RM} ${OBJECTDIR}/src/game_state.o
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/game_state.o.d" -o ${OBJECTDIR}/src/game_state.o src/game_state.c    -DXPRJ_default=$(CND_CONF) -Iinclude    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"

${OBJECTDIR}/src/keypad.o: src/keypad.c  .generated_files/flags/default/71e596147c2e3160ca9563911b6763c53defc02e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src"
	@${RM} ${OBJECTDIR}/src/keypad.o.d
	@${RM} ${OBJECTDIR}/src/keypad.o
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/keypad.o.d" -o ${OBJECTDIR}/src/keypad.o src/keypad.c    -DXPRJ_default=$(CND_CONF) -Iinclude    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"

${OBJECTDIR}/src/lcd_driver.o: src/lcd_driver.c  .generated_files/flags/default/71e596147c2e3160ca9563911b6763c53defc02e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src"
	@${RM} ${OBJECTDIR}/src/lcd_driver.o.d
	@${RM} ${OBJECTDIR}/src/lcd_driver.o
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/lcd_driver.o.d" -o ${OBJECTDIR}/src/lcd_driver.o src/lcd_driver.c    -DXPRJ_default=$(CND_CONF) -Iinclude    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"

${OBJECTDIR}/src/timing.o: src/timing.c  .generated_files/flags/default/71e596147c2e3160ca9563911b6763c53defc02e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src"
	@${RM} ${OBJECTDIR}/src/timing.o.d
	@${RM} ${OBJECTDIR}/src/timing.o
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/timing.o.d" -o ${OBJECTDIR}/src/timing.o src/timing.c    -DXPRJ_default=$(CND_CONF) -Iinclude    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"

else
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/8147211a04ee442157d809d528b8299f183fe1a0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}"
	@${RM} ${OBJECTDIR}/main.o.d
	@${RM} ${OBJECTDIR}/main.o
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF) -Iinclude    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"

${OBJECTDIR}/src/audio.o: src/audio.c  .generated_files/flags/default/8147211a04ee442157d809d528b8299f183fe1a0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src"
	@${RM} ${OBJECTDIR}/src/audio.o.d
	@${RM} ${OBJECTDIR}/src/audio.o
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/audio.o.d" -o ${OBJECTDIR}/src/audio.o src/audio.c    -DXPRJ_default=$(CND_CONF) -Iinclude    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"

${OBJECTDIR}/src/board_init.o: src/board_init.c  .generated_files/flags/default/8147211a04ee442157d809d528b8299f183fe1a0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src"
	@${RM} ${OBJECTDIR}/src/board_init.o.d
	@${RM} ${OBJECTDIR}/src/board_init.o
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/board_init.o.d" -o ${OBJECTDIR}/src/board_init.o src/board_init.c    -DXPRJ_default=$(CND_CONF) -Iinclude    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"

${OBJECTDIR}/src/display_assets.o: src/display_assets.c  .generated_files/flags/default/8147211a04ee442157d809d528b8299f183fe1a0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src"
	@${RM} ${OBJECTDIR}/src/display_assets.o.d
	@${RM} ${OBJECTDIR}/src/display_assets.o
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/display_assets.o.d" -o ${OBJECTDIR}/src/display_assets.o src/display_assets.c    -DXPRJ_default=$(CND_CONF) -Iinclude    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"

${OBJECTDIR}/src/game_state.o: src/game_state.c  .generated_files/flags/default/8147211a04ee442157d809d528b8299f183fe1a0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src"
	@${RM} ${OBJECTDIR}/src/game_state.o.d
	@${RM} ${OBJECTDIR}/src/game_state.o
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/game_state.o.d" -o ${OBJECTDIR}/src/game_state.o src/game_state.c    -DXPRJ_default=$(CND_CONF) -Iinclude    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"

${OBJECTDIR}/src/keypad.o: src/keypad.c  .generated_files/flags/default/8147211a04ee442157d809d528b8299f183fe1a0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src"
	@${RM} ${OBJECTDIR}/src/keypad.o.d
	@${RM} ${OBJECTDIR}/src/keypad.o
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/keypad.o.d" -o ${OBJECTDIR}/src/keypad.o src/keypad.c    -DXPRJ_default=$(CND_CONF) -Iinclude    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"

${OBJECTDIR}/src/lcd_driver.o: src/lcd_driver.c  .generated_files/flags/default/8147211a04ee442157d809d528b8299f183fe1a0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src"
	@${RM} ${OBJECTDIR}/src/lcd_driver.o.d
	@${RM} ${OBJECTDIR}/src/lcd_driver.o
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/lcd_driver.o.d" -o ${OBJECTDIR}/src/lcd_driver.o src/lcd_driver.c    -DXPRJ_default=$(CND_CONF) -Iinclude    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"

${OBJECTDIR}/src/timing.o: src/timing.c  .generated_files/flags/default/8147211a04ee442157d809d528b8299f183fe1a0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src"
	@${RM} ${OBJECTDIR}/src/timing.o.d
	@${RM} ${OBJECTDIR}/src/timing.o
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/timing.o.d" -o ${OBJECTDIR}/src/timing.o src/timing.c    -DXPRJ_default=$(CND_CONF) -Iinclude    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"

endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/StickmanGame.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${DISTDIR}
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/StickmanGame.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC0275F  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"

else
${DISTDIR}/StickmanGame.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${DISTDIR}
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/StickmanGame.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/StickmanGame.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
