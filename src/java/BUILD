EPP Java Implementation - Build Instructions

Table of Contents

 1. Required Java Packages
 2. Building EPP Java Implementation
 3. Building EPP Java Documentation
 4. Special Instructions
    4.1 Building on Windows Platform
    4.2 Building on UNIX Platform

---------------------------------------------------------------------

1. Required Java Packages

   The EPP Java Implementation requires the following java packages:

   1. JDK 1.2

          http://www.javasoft.com/products/jdk/1.2/

   2. JSSE 1.0.2

          http://www.javasoft.com/products/jsse/

   3. Apache Xerces 1.4.2 or later for Java - xerces.jar

          http://xml.apache.org/dist/xerces-j/
 
   4. GNU Make Version 3.79.1

          ftp://ftp.gnu.org/gnu/make/

   Make sure the above mentioned jar files are included in your CLASSPATH
   environment variable. A sample set up of the CLASSPATH environment
   variable on a UNIX platform would look like:

   CLASSPATH=/lib/xerces.jar:.

   On a Windows machine, it would look like:

   CLASSPATH='d:/lib/xerces.jar;.'

2. Building EPP Java Implementation

   The top level Makefile will build everything, including the
   documentation. If you only want to compile the source code and
   make the JAR files, run the following command from the top of
   the EPP Java tree:
   
     make jars
     
   If you want to build everything, including the documentation,
   read the following instructions before running make.

   If you want to compile class files with optimization, add JAVAOPT=-O
   in the make command line. For example:

     make JAVAOPT=-O
   
   When building, all special instructions must be followed.

3. Building EPP Java Documentation

   From the top of the EPP Java tree, type the following command to
   build the documentation:
   
     make docs apidocs

4. Special Instructions

4.1 Building on Windows Platform

    First, you need a copy of Cygnus's Cygwin. See
    http://sourceware.cygnus.com/cygwin.

    If your JDK is properly installed on your system, all you need to
    do is to set CLASSPATH environment variable properly according to
    the instruction described in Section 1. The environment variable
    must not end with a '\' or it will cause the build to fail.

    Then, if you're not using the Cygwin bash shell, you need to set
    the variable MAKE_MODE in your environment like this:

      set MAKE_MODE=UNIX

    Finally, from the top of the EPP Java tree, run make.

4.2 Building on Unix Platform

    If your JDK is properly installed on your system, all you need to 
    do is to set CLASSPATH environment variable properly according to
    the instruction described in Section 1. Then from the top of the
    directory tree, run make.

-EOF- $Id: BUILD,v 1.1 2005/12/06 20:11:35 wtan Exp $
