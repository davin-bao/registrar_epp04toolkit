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

# $Id: Makefile,v 1.1 2005/12/06 20:11:35 wtan Exp $
#
# This is the Makefile for building EPP C++ Implementation
#
# Makefile for directory . (src)

TOP=..
DIRS=epp biz us
include $(TOP)/src/Makefile.plat
TARGETS=prepare include
include $(TOP)/src/Makefile.incl

LIBNAME=libepp-c
THISLIB=${EPP_LIB_DIR}/${LIBNAME}${PRODUCTVERSION}${SHLIBSUFFIX}

lib:: ${THISLIB}

prepare::
	@echo Preparing the directory structure for a build ...
	-${MKDIR} ${EPP_OBJ_DIR}
	-${MKDIR} ${EPP_LIB_DIR}
	-${MKDIR} ${EPP_INC_DIR}

${THISLIB}::
	@echo Building ${THISLIB}
	${MAKE} -C ${EPP_OBJ}

apiDocs: include
	-${MKDIR} $(TOP)/docs/apiDocs
	-${RM} -r $(TOP)/docs/apiDocs/*
	sed -e 's/PRODUCTVERSION_DOT/$(PRODUCTVERSION_DOT)/g' doc/header.html > header.html
	sed -e 's/PRODUCTVERSION_DOT/$(PRODUCTVERSION_DOT)/g' doc/footer.html > footer.html
	cat ${EPP_INC_DIR}/*.hpp | sed -e 's/\@note/<BR><B>Note:<\/B>/g' | \
	sed -e 's/EPP_EXPORT //g' > epp.hpp
	doc++ --html --full-toc \
		--header header.html \
		--footer footer.html \
		--dir $(TOP)/docs/apiDocs epp.hpp
	${RM} epp.hpp
	$(CP) header.html                         allclasses-frame.html
	echo '<BODY BGCOLOR="white">'          >> allclasses-frame.html
	echo '<B>All Classes</B><BR>'          >> allclasses-frame.html
	echo '<TABLE BORDER="0" WIDTH="100%">' >> allclasses-frame.html
	echo '<TR><TD NOWARP>'                 >> allclasses-frame.html
	for i in $(TOP)/docs/apiDocs/Epp*.html ; do \
		echo '<A HREF="'`basename $$i`'" TARGET="classFrame">'`basename $$i .html`'</A><BR>' \
 	                                       >> allclasses-frame.html ; \
	done
	for i in $(TOP)/docs/apiDocs/Biz*.html ; do \
		echo '<A HREF="'`basename $$i`'" TARGET="classFrame">'`basename $$i .html`'</A><BR>' \
 	                                       >> allclasses-frame.html ; \
	done
	for i in $(TOP)/docs/apiDocs/Us*.html ; do \
		echo '<A HREF="'`basename $$i`'" TARGET="classFrame">'`basename $$i .html`'</A><BR>' \
 	                                       >> allclasses-frame.html ; \
	done
	echo '</TD></TR></TABLE></BODY></HTML>'>> allclasses-frame.html
	$(CP) header.html                         allclasses-core.html
	echo '<BODY BGCOLOR="white">'          >> allclasses-core.html
	echo '<B>Core</B><BR>'                 >> allclasses-core.html
	echo '<TABLE BORDER="0" WIDTH="100%">' >> allclasses-core.html
	echo '<TR><TD NOWRAP>'                >> allclasses-core.html
	for i in $(TOP)/src/epp/core/Epp*.hpp ; do \
		echo '<A HREF="'`basename $$i .hpp`'.html" TARGET="classFrame">'`basename $$i .hpp`'</A><BR>' \
	                                       >> allclasses-core.html ; \
	done
	echo '</TD></TR></TABLE></BODY></HTML>'>> allclasses-core.html
	$(CP) header.html                         allclasses-command.html
	echo '<BODY BGCOLOR="white">'          >> allclasses-command.html
	echo '<B>Core/Command</B><BR>'         >> allclasses-command.html
	echo '<TABLE BORDER="0" WIDTH="100%">' >> allclasses-command.html
	echo '<TR><TD NOWRAP>'                 >> allclasses-command.html
	for i in $(TOP)/src/epp/core/command/Epp*.hpp ; do \
		echo '<A HREF="'`basename $$i .hpp`'.html" TARGET="classFrame">'`basename $$i .hpp`'</A><BR>' \
	                                       >> allclasses-command.html ; \
	done
	echo '</TD></TR></TABLE></BODY></HTML>'>> allclasses-command.html
	$(CP) header.html                         allclasses-response.html
	echo '<BODY BGCOLOR="white">'          >> allclasses-response.html
	echo '<B>Core/Response</B><BR>'        >> allclasses-response.html
	echo '<TABLE BORDER="0" WIDTH="100%">' >> allclasses-response.html
	echo '<TR><TD NOWRAP>'                 >> allclasses-response.html
	for i in $(TOP)/src/epp/core/response/Epp*.hpp ; do \
		echo '<A HREF="'`basename $$i .hpp`'.html" TARGET="classFrame">'`basename $$i .hpp`'</A><BR>' \
	                                       >> allclasses-response.html ; \
	done
	echo '</TD></TR></TABLE></BODY></HTML>'>> allclasses-response.html
	$(CP) header.html                         allclasses-transport.html
	echo '<BODY BGCOLOR="white">'          >> allclasses-transport.html
	echo '<B>Transport</B><BR>'            >> allclasses-transport.html
	echo '<TABLE BORDER="0" WIDTH="100%">' >> allclasses-transport.html
	echo '<TR><TD NOWRAP>'                 >> allclasses-transport.html
	for i in $(TOP)/src/epp/transport/Epp*.hpp ; do \
		echo '<A HREF="'`basename $$i .hpp`'.html" TARGET="classFrame">'`basename $$i .hpp`'</A><BR>' \
	                                       >> allclasses-transport.html ; \
	done
	echo '</TD></TR></TABLE></BODY></HTML>'>> allclasses-transport.html
	$(CP) header.html                         allclasses-transport-tcp.html
	echo '<BODY BGCOLOR="white">'          >> allclasses-transport-tcp.html
	echo '<B>Transport/Tcp</B><BR>'        >> allclasses-transport-tcp.html
	echo '<TABLE BORDER="0" WIDTH="100%">' >> allclasses-transport-tcp.html
	echo '<TR><TD NOWRAP>'                 >> allclasses-transport-tcp.html
	for i in $(TOP)/src/epp/transport/tcp/Epp*.hpp ; do \
		echo '<A HREF="'`basename $$i .hpp`'.html" TARGET="classFrame">'`basename $$i .hpp`'</A><BR>' \
	                                       >> allclasses-transport-tcp.html ; \
	done
	echo '</TD></TR></TABLE></BODY></HTML>'>> allclasses-transport-tcp.html
	$(CP) header.html                         allclasses-biz.html
	echo '<BODY BGCOLOR="white">'          >> allclasses-biz.html
	echo '<B>Biz</B><BR>'                  >> allclasses-biz.html
	echo '<TABLE BORDER="0" WIDTH="100%">' >> allclasses-biz.html
	echo '<TR><TD NOWRAP>'                 >> allclasses-biz.html
	for i in $(TOP)/src/biz/Biz*.hpp ; do \
		echo '<A HREF="'`basename $$i .hpp`'.html" TARGET="classFrame">'`basename $$i .hpp`'</A><BR>' \
	                                       >> allclasses-biz.html ; \
	done
	echo '</TD></TR></TABLE></BODY></HTML>'>> allclasses-biz.html
	$(CP) header.html                         allclasses-us.html
	echo '<BODY BGCOLOR="white">'          >> allclasses-us.html
	echo '<B>Us</B><BR>'                  >> allclasses-us.html
	echo '<TABLE BORDER="0" WIDTH="100%">' >> allclasses-us.html
	echo '<TR><TD NOWRAP>'                 >> allclasses-us.html
	for i in $(TOP)/src/us/Us*.hpp ; do \
		echo '<A HREF="'`basename $$i .hpp`'.html" TARGET="classFrame">'`basename $$i .hpp`'</A><BR>' \
	                                       >> allclasses-us.html ; \
	done
	echo '</TD></TR></TABLE></BODY></HTML>'>> allclasses-us.html
	$(CP) header.html                $(TOP)/docs/apiDocs/apiIndex.html
	sed -e 's/PRODUCTVERSION_DOT/$(PRODUCTVERSION_DOT)/g' doc/apiIndex.html \
	                              >> $(TOP)/docs/apiDocs/apiIndex.html
	$(CP) header.html                $(TOP)/docs/apiDocs/overview-frame.html
	sed -e 's/PRODUCTVERSION_DOT/$(PRODUCTVERSION_DOT)/g' doc/overview-frame.html \
	                              >> $(TOP)/docs/apiDocs/overview-frame.html
	$(CP) header.html                $(TOP)/docs/apiDocs/overview-summary.html
	sed -e 's/PRODUCTVERSION_DOT/$(PRODUCTVERSION_DOT)/g' doc/overview-summary.html \
	                              >> $(TOP)/docs/apiDocs/overview-summary.html
	
	cat   footer.html             >> $(TOP)/docs/apiDocs/overview-summary.html
	$(MV) allclasses-frame.html         $(TOP)/docs/apiDocs/
	$(MV) allclasses-core.html          $(TOP)/docs/apiDocs/
	$(MV) allclasses-command.html       $(TOP)/docs/apiDocs/
	$(MV) allclasses-response.html      $(TOP)/docs/apiDocs/
	$(MV) allclasses-transport.html     $(TOP)/docs/apiDocs/
	$(MV) allclasses-transport-tcp.html $(TOP)/docs/apiDocs/
	$(MV) allclasses-biz.html           $(TOP)/docs/apiDocs/
	$(MV) allclasses-us.html           $(TOP)/docs/apiDocs/
	$(RM) header.html footer.html

copy:: lib
	@echo Make the target directory and its main subdirectories
	-${MKDIR} ${BINTARGETDIR}
	-${MKDIR} ${BINTARGETDIR}/lib
	-${MKDIR} ${BINTARGETDIR}/include
	-${MKDIR} ${BINTARGETDIR}/docs
	-${MKDIR} ${BINTARGETDIR}/xsd
	-${MKDIR} ${BINTARGETDIR}/test
	@echo Copying License/ChangeLog files
	-${CP) ../LICENSE ../CHANGELOG ${BINTARGETDIR}/
	@echo Copying header files ...
	-${CP} -pr ${EPP_INC_DIR}/*.hpp ${BINTARGETDIR}/include/
	@echo Copying binary files ...
	-${CP} -pr ${EPP_LIB_DIR}/* ${BINTARGETDIR}/lib/
	@echo Copying document files ...
	-${CP} -pr ${TOP}/docs/* ${BINTARGETDIR}/docs/
	@echo Copying XML schema files ...
	-${CP} -pr ${TOP}/xsd/* ${BINTARGETDIR}/xsd/
	@echo Copying Testing files ...
	-${CP} -pr ${TOP}/test/EppTestSSL.cpp       ${BINTARGETDIR}/test/
	-${CP} -pr ${TOP}/test/EppTestServerTcp.cpp ${BINTARGETDIR}/test/
	-${CP} -pr ${TOP}/test/testkeys.*           ${BINTARGETDIR}/test/
	-${CP} -pr ${TOP}/test/RunTestTcp           ${BINTARGETDIR}/test/

tgz:: copy
	@echo Tar/Gzip all ...
	cd ${BINTARGETDIR}/..
	-${RM} -f ${BINTARGETDIR}.tar
	-${RM} -f ${BINTARGETDIR}.tar.gz
	tar cvf ${BINTARGETDIR}.tar ${BINTARGETDIR}
	gzip ${BINTARGETDIR}.tar

zip:: copy
	@echo Zip all ...
	cd ${BINTARGETDIR}/..
	-${RM} -f ${BINTARGETDIR}.zip
	zip -r ${BINTARGETDIR}.zip ${BINTARGETDIR}

package_bin:: zip tgz

package_src::
