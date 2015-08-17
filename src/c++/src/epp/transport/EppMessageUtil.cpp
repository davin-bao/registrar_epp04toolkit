/*******************************************************************************
 * The MIT License (MIT)
 *  
 * Copyright (c) 2015 Neustar Inc.
 *  
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *  
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *  
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *******************************************************************************/
#include <string.h>
#include <memory.h>
#if       ! defined(win32)      /* { */
#include <sys/time.h>
#endif /* ! defined(win32) */   /* } */
#include "EppMessageUtil.hpp"
#include "EppUtil.hpp"

#ifndef	BUFSIZ
#define	BUFSIZ	4096
#endif


char * EppMessageUtil::send( int socket, const DOMString& str, int * length )
{
	*length = 0;
	char * p = str.transcode();
	if( p == null )
	{
		return "Error in EppMessageUtil::send() no memory";
	}

	int l = ::strlen(p);
#if       defined(win32)        /* { */
	int n = ::send(socket, p, l, 0);
#else /* defined(win32) */     /* } */
	int n = ::write(socket, p, l);
#endif /* defined(win32) */     /* } */
	delete [] p;
	if( n != l )
	{
		return "Error in EppMessageUtil::send() write error";
	}
	return EppMessageUtil::getEppPayload(socket, length);
}

char * EppMessageUtil::getEppPayload( int socket, int * length )
{
	bool quit = false;
	return EppMessageUtil::getEppPayload(socket, length, &quit, 0);
}

char * EppMessageUtil::getEppPayload( int socket, int * length, bool * quit, int maxsize )
{
	*length = 0;
	int    i = 0;
	int    len = BUFSIZ;
	char * buf = new char[BUFSIZ];

	if( buf == null )
		return null; // no mem

	bool endFound = false;
	bool eppFound = false;
	bool eppStart = false;

	while( ! endFound )
	{
		char c;
		int n;

#if       defined(win32)        /* { */
		while( (n = ::recv(socket, &c, 1, 0)) == 0 )
#else /* defined(win32) */     /* } */
		while( (n = ::read(socket, &c, 1)) == 0 )
#endif /* defined(win32) */     /* } */
		{
			EppUtil::msSleep(1000);
			if( *quit == true )
			{
				strncpy(buf, "Error in EppMessageUtil::getEppPayload() timeout/quit", BUFSIZ);
				buf[BUFSIZ-1] = '\0';
				return buf;
			}
		}
		if( n < 0 )
		{
			// error
			strncpy(buf, "Error in EppMessageUtil::getEppPayload() read()", BUFSIZ);
			buf[BUFSIZ-1] = '\0';
			return buf;
		}
//		cout << c;
		if( eppStart == false )
		{
			if( c != '<' )
			{
				continue;
			}
			eppStart = true;
		}

		// EPP payload rarely exceeds 8KB, so this
		// doubling-up should not occur very often

		if( i == (len - 1) )
		{
			// check if the maxsize is reached

			if( (maxsize > 0) && (len >= maxsize) )
			{
				*length = -len;
				strncpy(buf, "EPP message payload size exceeds the maximum limit", BUFSIZ);
				buf[BUFSIZ-1] = '\0';
				return buf;
			}

			char * newbuf = new char[len + BUFSIZ];
			if( newbuf == null )
			{
				strncpy(buf, "Error in EppMessageUtil::getEppPayload() no memory", BUFSIZ);
				buf[BUFSIZ-1] = '\0';
				return buf;
			}
			(void) memcpy(newbuf, buf, len);
			delete [] buf;
			buf = newbuf;
			len = len + BUFSIZ;
		}
		buf[i++] = c;

		// check if we have got the "</epp" tag

		if(    ! eppFound
		    && (i >= 5)
		    && (buf[i - 5] == '<')
		    && (buf[i - 4] == '/')
		    && (buf[i - 3] == 'e')
		    && (buf[i - 2] == 'p')
		    && (buf[i - 1] == 'p') )
		{
			eppFound = true;
		} 
		if( eppFound && (buf[i - 1] == '>') )
		{
			endFound = true;
		}
	}

	// ok, we have got a buffer, either with a full EPP payload, or
	// end of the input stream

	buf[i] = 0;
	*length = i;

	// trim the buffer

	return buf;
}

char * EppMessageUtil::send( SSL * ssl, const DOMString& str, int * length )
{
	*length = 0;
	char * p = str.transcode();
	if( p == null )
	{
		return "Error in EppMessageUtil::send() no memory";
	}

	int l = strlen(p);
	int n;
	while (true) {
		ERR_clear_error();
		n = SSL_write(ssl, p, l);
		if (n < 0) {
			int err = SSL_get_error(ssl, n);
			if (err == SSL_ERROR_WANT_READ || err == SSL_ERROR_WANT_WRITE) {
				EppUtil::msSleep(100);
				continue; // retry
			}
		}
		break; // either success, or connection closed, or error
	}

	delete [] p;
	if( n != l )
	{
		if (n == 0)
			return "Error in EppMessageUtil::send() connection closed";
		else
			return "Error in EppMessageUtil::send() write error";
	}
	return EppMessageUtil::getEppPayload(ssl, length);
}

char * EppMessageUtil::getEppPayload( SSL * ssl, int * length )
{
	bool quit = false;
	return EppMessageUtil::getEppPayload(ssl, length, &quit, 0);
}

char * EppMessageUtil::getEppPayload( SSL * ssl, int * length, bool * quit, int maxsize )
{
	*length = 0;
	int    i = 0;
	int    len = BUFSIZ;
	char * buf = new char[BUFSIZ];

	if( buf == null )
		return null; // no mem

	bool endFound = false;
	bool eppFound = false;
	bool eppStart = false;

	while( ! endFound )
	{
		char c;
		int n;

		while (true)
		{
			if (*quit == true) {
				strncpy(buf, "Error in EppMessageUtil::getEppPayload() timeout/quit", BUFSIZ);
				buf[BUFSIZ-1] = '\0';
				return buf;
			}

			ERR_clear_error();
			n = SSL_read(ssl, (char *)&c, 1);

			if (n > 0) // read successful
				break;

			if (n < 0) {
				int err = SSL_get_error(ssl, n);
				if (err == SSL_ERROR_WANT_READ || err == SSL_ERROR_WANT_WRITE) {
					EppUtil::msSleep(100);
					continue;
				}

				snprintf(buf, BUFSIZ, "Error in EppMessageUtil::getEppPayload() SSL_read error [rv=%d, ssl_error=%d, errno=%d]", n, err, errno);
			}
			else {
				strncpy(buf, "Error in EppMessageUtil::getEppPayload() connection closed", BUFSIZ);
			}

			buf[BUFSIZ-1] = '\0';
			*quit = true;
			return buf;
		}

//		cout << c;
		if( eppStart == false )
		{
			if( c != '<' )
			{
				continue;
			}
			eppStart = true;
		}

		// EPP payload rarely exceeds 8KB, so this
		// doubling-up should not occur very often

		if( i == (len - 1) )
		{
			// check if the maxsize is reached

			if( (maxsize > 0) && (len >= maxsize) )
			{
				*length = -len;
				strncpy(buf, "EPP message payload size exceeds the maximum limit", BUFSIZ);
				buf[BUFSIZ-1] = '\0';
				return buf;
			}

			char * newbuf = new char[len + BUFSIZ];
			if( newbuf == null )
			{
				strncpy(buf, "Error in EppMessageUtil::getEppPayload() no memory", BUFSIZ);
				buf[BUFSIZ-1] = '\0';
				return buf;
			}
			(void) memcpy(newbuf, buf, len);
			buf = newbuf;
			len = len + BUFSIZ;
		}
		buf[i++] = c;

		// check if we have got the "</epp" tag

		if(    ! eppFound
		    && (i >= 5)
		    && (buf[i - 5] == '<')
		    && (buf[i - 4] == '/')
		    && (buf[i - 3] == 'e')
		    && (buf[i - 2] == 'p')
		    && (buf[i - 1] == 'p') )
		{
			eppFound = true;
		} 
		if( eppFound && (buf[i - 1] == '>') )
		{
			endFound = true;
		}
	}

	// ok, we have got a buffer, either with a full EPP payload, or
	// end of the input stream

	buf[i] = 0;
	*length = i;

	// trim the buffer

	return buf;
}

int EppMessageUtil::checkSocket( int sock, int timeout )
{
	int rtn;
	fd_set fi;
	fd_set fo;
	fd_set fe;
	struct timeval tp;

	FD_ZERO(&fi);
	FD_ZERO(&fo);
	FD_ZERO(&fe);

	FD_SET(sock, &fi);
//	FD_SET(sock, &fo);
	FD_SET(sock, &fe);

	tp.tv_sec = timeout;
	tp.tv_usec = 0;

	rtn = ::select( sock + 1, &fi, &fo, &fe, &tp);
	if( rtn < 0 )
	{
		return -1;
	}
	if( rtn == 0 )
	{
		return 0;
	}
	if( FD_ISSET(sock, &fi) )
	{
		return +1;
	}
	if( FD_ISSET(sock, &fe) )
	{
		return -1;
	}
	return 0;
}
