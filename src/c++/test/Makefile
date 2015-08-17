#******************************************************************************
# The MIT License (MIT)
#  
# Copyright (c) 2015 Neustar Inc.
#  
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#  
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#  
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#******************************************************************************

# $Id: Makefile,v 1.2 2007/08/30 21:58:25 wtan Exp $
#
# This is the Makefile for building EPP C++ Implementation
#
# Makefile for directory . (test)

TOP=..
DIRS=
include $(TOP)/src/Makefile.plat

HDRS=\

SRCS=\
	EppTestCore.cpp		\
	EppTestCommand.cpp	\
	EppTestResponse.cpp	\
	EppTestSSL.cpp	\
	EppTestServer.cpp	\

OBJS=\
	EppTestCore.$(O)	\
	EppTestCommand.$(O)	\
	EppTestResponse.$(O)	\
	EppTestSSL.$(O)	\
	EppTestServer.$(O)	\

BINS=\
	EppTestCore$(EXE)	\
	EppTestCommand$(EXE)	\
	EppTestResponse$(EXE)	\
	EppTestSSL$(EXE)	\
	EppTestServerTcp$(EXE)	\

TESTS=\
	EppTestCore	\
	EppTestCommand	\
	EppTestResponse	\
	EppTestSSL	\

LIBNAME=libepp-c
THISLIB=${EPP_LIB_DIR}/${LIBNAME}${PRODUCTVERSION}${SHLIBSUFFIX}

LIBS=\
	${THISLIB} ${XERCES_LIB} ${OPENSSL_LIB} -ldl

TARGETS=$(BINS)

include $(TOP)/src/Makefile.incl

ifeq (${PLATFORM}, win32)
ifeq (${WIN32_DEBUG}, _DEBUG)
DEBUG_OPT = /MDd /Zi /Od
else
DEBUG_OPT = /MD /Od
endif
DDLS=$(XERCES_C_DLL) $(OPENSSL_DDL)
else
DEBUG_OPT = -g
DDLS=
endif

XSDS = epp.xsd eppcom.xsd contact.xsd domain.xsd host.xsd

#
# Common rules (test only)
#

ifeq (${PLATFORM}, solaris)
#CC2 =	$(CC1) $(DEBUG_OPT) -lpthread
CC2 =	purify -chain-length=20 -windows=no -cache-dir=/usr/home/nzhang/cache $(CC1) $(DEBUG_OPT) -lpthread
else
CC2 =	$(CC1) $(DEBUG_OPT)
endif

clean::
	${RM} -rf *.$(O) *.xsd xml ${BINS} *.pdb *.ilk

EppTestCore$(EXE): EppTestCore.$(O) ${LIBS}
	$(CC2) -o $(@) $(<) ${ALLLIBS}

EppTestCommand$(EXE): EppTestCommand.$(O) ${LIBS}
	$(CC2) -o $(@) $(<) ${ALLLIBS}

EppTestResponse$(EXE): EppTestResponse.$(O) ${LIBS}
	$(CC2) -o $(@) $(<) ${ALLLIBS}

EppTestSSL$(EXE): EppTestSSL.$(O) ${LIBS}
	$(CC2) -o $(@) $(<) ${ALLLIBS}

EppTestServerTcp$(EXE): EppTestServerTcp.$(O) ${LIBS}
	$(CC2) -o $(@) $(<) ${ALLLIBS}

#
# Copy EPP Schema files from ../xsd
#
epp.xsd:: ../xsd/epp.xsd
	${CP} -p $< $@

eppcom.xsd:: ../xsd/eppcom.xsd
	${CP} -p $< $@

contact.xsd:: ../xsd/contact.xsd
	${CP} -p $< $@

domain.xsd:: ../xsd/domain.xsd
	${CP} -p $< $@

host.xsd:: ../xsd/host.xsd
	${CP} -p $< $@

epp.xml::
	${RM} -rf xml
	${CP} -pr ../xsd/xml .
#
# Test all
#
testall:	$(TARGETS) $(XSDS)
	echo "Test all..."
	@for i in $(TESTS) ; do \
		echo "Performing $$i ..." ; \
		./$$i ; \
	done
