# C++ Static Library Makefile autogenerated by premake
# Don't edit this file! Instead edit `premake.lua` then rerun `make`

ifndef CONFIG
  CONFIG=DebugSingleDLL
endif

ifeq ($(CONFIG),DebugSingleDLL)
  BINDIR := ../../lib/DebugSingleDLL
  LIBDIR := ../../lib/DebugSingleDLL
  OBJDIR := obj/tests/DebugSingleDLL
  OUTDIR := ../../lib/DebugSingleDLL
  CPPFLAGS := -MMD -D "_CRT_SECURE_NO_DEPRECATE" -I "../../include" -I "../../tests/UnitTest++/src"
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g
  CXXFLAGS := $(CFLAGS)
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -lode_singled
  LDDEPS := ../../lib/DebugSingleDLL/ode_singled.dll
  RESFLAGS := -D "_CRT_SECURE_NO_DEPRECATE" -I "../../include" -I "../../tests/UnitTest++/src"
  TARGET := tests.exe
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

ifeq ($(CONFIG),ReleaseSingleDLL)
  BINDIR := ../../lib/ReleaseSingleDLL
  LIBDIR := ../../lib/ReleaseSingleDLL
  OBJDIR := obj/tests/ReleaseSingleDLL
  OUTDIR := ../../lib/ReleaseSingleDLL
  CPPFLAGS := -MMD -D "_CRT_SECURE_NO_DEPRECATE" -I "../../include" -I "../../tests/UnitTest++/src"
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g
  CXXFLAGS := $(CFLAGS)
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -lode_single
  LDDEPS := ../../lib/ReleaseSingleDLL/ode_single.dll
  RESFLAGS := -D "_CRT_SECURE_NO_DEPRECATE" -I "../../include" -I "../../tests/UnitTest++/src"
  TARGET := tests.exe
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

ifeq ($(CONFIG),DebugSingleLib)
  BINDIR := ../../lib/DebugSingleLib
  LIBDIR := ../../lib/DebugSingleLib
  OBJDIR := obj/tests/DebugSingleLib
  OUTDIR := ../../lib/DebugSingleLib
  CPPFLAGS := -MMD -D "_CRT_SECURE_NO_DEPRECATE" -I "../../include" -I "../../tests/UnitTest++/src"
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g
  CXXFLAGS := $(CFLAGS)
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -lode_singled
  LDDEPS := ../../lib/DebugSingleLib/libode_singled.a
  RESFLAGS := -D "_CRT_SECURE_NO_DEPRECATE" -I "../../include" -I "../../tests/UnitTest++/src"
  TARGET := tests.exe
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

ifeq ($(CONFIG),ReleaseSingleLib)
  BINDIR := ../../lib/ReleaseSingleLib
  LIBDIR := ../../lib/ReleaseSingleLib
  OBJDIR := obj/tests/ReleaseSingleLib
  OUTDIR := ../../lib/ReleaseSingleLib
  CPPFLAGS := -MMD -D "_CRT_SECURE_NO_DEPRECATE" -I "../../include" -I "../../tests/UnitTest++/src"
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g
  CXXFLAGS := $(CFLAGS)
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -lode_single
  LDDEPS := ../../lib/ReleaseSingleLib/libode_single.a
  RESFLAGS := -D "_CRT_SECURE_NO_DEPRECATE" -I "../../include" -I "../../tests/UnitTest++/src"
  TARGET := tests.exe
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

ifeq ($(CONFIG),DebugDoubleDLL)
  BINDIR := ../../lib/DebugDoubleDLL
  LIBDIR := ../../lib/DebugDoubleDLL
  OBJDIR := obj/tests/DebugDoubleDLL
  OUTDIR := ../../lib/DebugDoubleDLL
  CPPFLAGS := -MMD -D "_CRT_SECURE_NO_DEPRECATE" -D "dDOUBLE" -I "../../include" -I "../../tests/UnitTest++/src"
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g
  CXXFLAGS := $(CFLAGS)
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -lode_doubled
  LDDEPS := ../../lib/DebugDoubleDLL/ode_doubled.dll
  RESFLAGS := -D "_CRT_SECURE_NO_DEPRECATE" -D "dDOUBLE" -I "../../include" -I "../../tests/UnitTest++/src"
  TARGET := tests.exe
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

ifeq ($(CONFIG),ReleaseDoubleDLL)
  BINDIR := ../../lib/ReleaseDoubleDLL
  LIBDIR := ../../lib/ReleaseDoubleDLL
  OBJDIR := obj/tests/ReleaseDoubleDLL
  OUTDIR := ../../lib/ReleaseDoubleDLL
  CPPFLAGS := -MMD -D "_CRT_SECURE_NO_DEPRECATE" -D "dDOUBLE" -I "../../include" -I "../../tests/UnitTest++/src"
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g
  CXXFLAGS := $(CFLAGS)
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -lode_double
  LDDEPS := ../../lib/ReleaseDoubleDLL/ode_double.dll
  RESFLAGS := -D "_CRT_SECURE_NO_DEPRECATE" -D "dDOUBLE" -I "../../include" -I "../../tests/UnitTest++/src"
  TARGET := tests.exe
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

ifeq ($(CONFIG),DebugDoubleLib)
  BINDIR := ../../lib/DebugDoubleLib
  LIBDIR := ../../lib/DebugDoubleLib
  OBJDIR := obj/tests/DebugDoubleLib
  OUTDIR := ../../lib/DebugDoubleLib
  CPPFLAGS := -MMD -D "_CRT_SECURE_NO_DEPRECATE" -D "dDOUBLE" -I "../../include" -I "../../tests/UnitTest++/src"
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g
  CXXFLAGS := $(CFLAGS)
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -lode_doubled
  LDDEPS := ../../lib/DebugDoubleLib/libode_doubled.a
  RESFLAGS := -D "_CRT_SECURE_NO_DEPRECATE" -D "dDOUBLE" -I "../../include" -I "../../tests/UnitTest++/src"
  TARGET := tests.exe
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

ifeq ($(CONFIG),ReleaseDoubleLib)
  BINDIR := ../../lib/ReleaseDoubleLib
  LIBDIR := ../../lib/ReleaseDoubleLib
  OBJDIR := obj/tests/ReleaseDoubleLib
  OUTDIR := ../../lib/ReleaseDoubleLib
  CPPFLAGS := -MMD -D "_CRT_SECURE_NO_DEPRECATE" -D "dDOUBLE" -I "../../include" -I "../../tests/UnitTest++/src"
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g
  CXXFLAGS := $(CFLAGS)
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -lode_double
  LDDEPS := ../../lib/ReleaseDoubleLib/libode_double.a
  RESFLAGS := -D "_CRT_SECURE_NO_DEPRECATE" -D "dDOUBLE" -I "../../include" -I "../../tests/UnitTest++/src"
  TARGET := tests.exe
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

OBJECTS := \
	$(OBJDIR)/joint.o \
	$(OBJDIR)/main.o \
	$(OBJDIR)/odemath.o \
	$(OBJDIR)/AssertException.o \
	$(OBJDIR)/Checks.o \
	$(OBJDIR)/DeferredTestReporter.o \
	$(OBJDIR)/DeferredTestResult.o \
	$(OBJDIR)/MemoryOutStream.o \
	$(OBJDIR)/ReportAssert.o \
	$(OBJDIR)/Test.o \
	$(OBJDIR)/TestDetails.o \
	$(OBJDIR)/TestList.o \
	$(OBJDIR)/TestReporter.o \
	$(OBJDIR)/TestReporterStdout.o \
	$(OBJDIR)/TestResults.o \
	$(OBJDIR)/TestRunner.o \
	$(OBJDIR)/TimeConstraint.o \
	$(OBJDIR)/XmlTestReporter.o \
	$(OBJDIR)/TimeHelpers.o \

RESOURCES := \

MKDIR_TYPE := msdos
CMD := $(subst \,\\,$(ComSpec)$(COMSPEC))
ifeq (,$(CMD))
  MKDIR_TYPE := posix
endif
ifeq (/bin/sh.exe,$(SHELL))
  MKDIR_TYPE := posix
endif
ifeq ($(MKDIR_TYPE),posix)
  CMD_MKBINDIR := mkdir -p $(BINDIR)
  CMD_MKLIBDIR := mkdir -p $(LIBDIR)
  CMD_MKOUTDIR := mkdir -p $(OUTDIR)
  CMD_MKOBJDIR := mkdir -p $(OBJDIR)
else
  CMD_MKBINDIR := $(CMD) /c if not exist $(subst /,\\,$(BINDIR)) mkdir $(subst /,\\,$(BINDIR))
  CMD_MKLIBDIR := $(CMD) /c if not exist $(subst /,\\,$(LIBDIR)) mkdir $(subst /,\\,$(LIBDIR))
  CMD_MKOUTDIR := $(CMD) /c if not exist $(subst /,\\,$(OUTDIR)) mkdir $(subst /,\\,$(OUTDIR))
  CMD_MKOBJDIR := $(CMD) /c if not exist $(subst /,\\,$(OBJDIR)) mkdir $(subst /,\\,$(OBJDIR))
endif

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking tests
	-@$(CMD_MKBINDIR)
	-@$(CMD_MKLIBDIR)
	-@$(CMD_MKOUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning tests
ifeq ($(MKDIR_TYPE),posix)
	-@rm -f $(OUTDIR)/$(TARGET)
	-@rm -rf $(OBJDIR)
else
	-@if exist $(subst /,\,$(OUTDIR)/$(TARGET)) del /q $(subst /,\,$(OUTDIR)/$(TARGET))
	-@if exist $(subst /,\,$(OBJDIR)) del /q $(subst /,\,$(OBJDIR))
	-@if exist $(subst /,\,$(OBJDIR)) rmdir /s /q $(subst /,\,$(OBJDIR))
endif

$(OBJDIR)/joint.o: ../../tests/joint.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/main.o: ../../tests/main.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/odemath.o: ../../tests/odemath.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/AssertException.o: ../../tests/UnitTest++/src/AssertException.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/Checks.o: ../../tests/UnitTest++/src/Checks.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/DeferredTestReporter.o: ../../tests/UnitTest++/src/DeferredTestReporter.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/DeferredTestResult.o: ../../tests/UnitTest++/src/DeferredTestResult.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/MemoryOutStream.o: ../../tests/UnitTest++/src/MemoryOutStream.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/ReportAssert.o: ../../tests/UnitTest++/src/ReportAssert.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/Test.o: ../../tests/UnitTest++/src/Test.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/TestDetails.o: ../../tests/UnitTest++/src/TestDetails.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/TestList.o: ../../tests/UnitTest++/src/TestList.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/TestReporter.o: ../../tests/UnitTest++/src/TestReporter.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/TestReporterStdout.o: ../../tests/UnitTest++/src/TestReporterStdout.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/TestResults.o: ../../tests/UnitTest++/src/TestResults.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/TestRunner.o: ../../tests/UnitTest++/src/TestRunner.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/TimeConstraint.o: ../../tests/UnitTest++/src/TimeConstraint.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/XmlTestReporter.o: ../../tests/UnitTest++/src/XmlTestReporter.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/TimeHelpers.o: ../../tests/UnitTest++/src/Win32/TimeHelpers.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

-include $(OBJECTS:%.o=%.d)

