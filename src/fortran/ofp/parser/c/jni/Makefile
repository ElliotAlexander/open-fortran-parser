# Copyright (c) 2005, 2006 Los Alamos National Security, LLC.  This
# material was produced under U.S. Government contract DE-
# AC52-06NA25396 for Los Alamos National Laboratory (LANL), which is
# operated by the Los Alamos National Security, LLC (LANS) for the
# U.S. Department of Energy. The U.S. Government has rights to use,
# reproduce, and distribute this software. NEITHER THE GOVERNMENT NOR
# LANS MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY
# LIABILITY FOR THE USE OF THIS SOFTWARE. If software is modified to
# produce derivative works, such modified software should be clearly
# marked, so as not to confuse it with the version available from
# LANL.

# Additionally, this program and the accompanying materials are made
# available under the terms of the Eclipse Public License v1.0 which
# accompanies this distribution, and is available at
# http://www.eclipse.org/legal/epl-v10.html

include ../../../../../../make.inc

JAVAC=$(OFP_JAVAC) 
JAVA=$(OFP_JAVA) 
JAR=$(OFP_JAR) 
CC=$(OFP_CC) 

JARFILE=$(OFP_JARFILE)

BUILDDIR = $(OFP_BUILD_DIR)
CLASSDIR = $(BUILDDIR)/fortran/ofp/parser/c/jni
JFLAGS = -d $(BUILDDIR) @sourcefiles $(OFP_JFLAGS)

INSTALLDIR = $(CLASSDIR)

#CFLAGS=$(OFP_CFLAGS) -I$(OFP_C_DIR)
#LDFLAGS=$(OFP_LDFLAGS)
OFP_CFLAGS := $(OFP_CFLAGS) -I$(OFP_C_DIR)

CLASS_FILES=$(CLASSDIR)/FortranParserActionJNI.class
C_ACTION_SO=$(OFP_C_ACTION_SO)
C_TOKEN=../token.c
C_ACTIONS_GEN_JNI=c_actions_jni.c
C_ACTIONS_JNI=jni_token_funcs.c
C_ACTION_NULL=../FortranParserActionNull.c
C_ACTION_PRINT=../FortranParserActionPrint.c
JAVA_JNI_ACTIONS_CLASS=FortranParserActionJNI.java

ALL_TARGETS=
ifeq ($(OFP_ENABLE_C_ACTIONS), "yes")
   ALL_TARGETS := jni_code $(CLASS_FILES) $(BUILDDIR)/$(C_ACTION_SO)
endif
ifeq ($(OFP_ENABLE_C_MAIN), "yes")
   ALL_TARGETS := $(ALL_TARGETS) c_main_ex
endif

############################# generic rules ########################
.SUFFIXES: .c .C .o

.c.o:
	$(CC) $(CINCS) $(CFLAGS) $(OFP_CFLAGS) -fPIC -c $< -o $@ 
.C.o:
	$(CXX) $(CXXINCS) $(CXXFLAGS) -fPIC -c $< -o $@ 

############################# targets ##############################

all: $(ALL_TARGETS)
	cp jni_token_funcs.h $(INSTALLDIR)/.
	cp jni_token_funcs.c $(INSTALLDIR)/.

$(BUILDDIR)/$(C_ACTION_SO): $(C_TOKEN) $(C_ACTIONS_JNI) $(C_ACTIONS_GEN_JNI) $(C_ACTION_PRINT)
	$(CC) $(OFP_DY_CFLAGS) $(CINCS) $(CFLAGS) $(OFP_CFLAGS) -fPIC $(C_TOKEN) \
              $(C_ACTIONS_JNI) \
              $(C_ACTIONS_GEN_JNI) $(C_ACTION_PRINT) -o $@

$(CLASSDIR)/FortranParserActionJNI.class: FortranParserActionJNI.java
	$(JAVAC) $(JFLAGS) $<

jarfile: $(BUILDDIR)/$(JARFILE)

$(BUILDDIR)/$(JARFILE): $(CLASS_FILES)
	cd $(BUILDDIR) ; $(JAR) cf $(JARFILE) fortran/

jni_code: c_actions_jni.c

c_actions_jni.c: ../../java/IFortranParserAction.java
	$(JAVA) $(OFP_JFLAGS) fortran.tools.ToC
	cp c_actions_jni.c $(INSTALLDIR)/.

c_main_ex: c_main_ex.o
	$(CC) -o $@ $< -fPIC $(LDFLAGS) $(OFP_LDFLAGS)

# this should not be called (nor should allclean) if neither the 
# c actions nor c main were enabled.
clean: 
ifeq ($(OFP_ENABLE_C_ACTIONS), "yes")
	rm -f $(CLASS_FILES)
	rm -f $(BUILDDIR)/$(C_ACTION_SO)
	rm -f $(C_ACTIONS_GEN_JNI)
	rm -f $(JAVA_JNI_ACTIONS_CLASS)
endif
ifeq ($(OFP_ENABLE_C_MAIN), "yes")
	rm -f c_main_ex c_main_ex.o 
endif

allclean:
	$(MAKE) clean

