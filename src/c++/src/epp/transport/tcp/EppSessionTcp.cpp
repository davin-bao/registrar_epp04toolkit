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

#if       defined(win32)        /* { */

#include <windows.h>
#include <winsock.h>
#include <io.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>

#ifndef	   EINPROGRESS		/* { */
#define	   EINPROGRESS		WSAEINPROGRESS
#endif	/* EINPROGRESS	*/ 	/* } */
#ifndef	   EALREADY		/* { */
#define	   EALREADY		WSAEALREADY
#endif	/* EALREADY	*/ 	/* } */
#ifndef	   EISCONN		/* { */
#define	   EISCONN		WSAEISCONN
#endif	/* EISCONN	*/ 	/* } */

#define	CLOSESOCKET(_s_)	::closesocket(_s_)

#else  /* defined(win32) */     /* } { */

#define	CLOSESOCKET(_s_)	::close(_s_)

#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>

#endif /* defined(win32) */     /* } */

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/crypto.h>
#include <openssl/x509.h>

#include <dom/DOM.hpp>

#include "EppHello.hpp"
#include "EppGreeting.hpp"
#include "EppParser.hpp"
#include "EppSessionTcp.hpp"
#include "EppChannelTcp.hpp"
#include "EppMessageUtil.hpp"
#include "EppUtil.hpp"

EppSessionTcp::EppSessionTcp()
{
	this->host = null;
	this->port = 0;
	this->channel = null;
	this->useTls = true;
	this->sock = -1;
	this->sslctx = null;
	this->sslssl = null;

	this->privateKeyFileName = null;
	this->privateKeyFileType = SSL_FILETYPE_PEM;
	this->publicKeyFileName = null;
	this->publicKeyFileType = SSL_FILETYPE_PEM;
	this->remoteKeyFileName = null;
};

EppSessionTcp::EppSessionTcp( bool useTLS )
{
	this->host = null;
	this->port = 0;
	this->channel = null;
	this->useTls = useTLS;
	this->sock = -1;
	this->sslctx = null;
	this->sslssl = null;

	this->privateKeyFileName = null;
	this->privateKeyFileType = SSL_FILETYPE_PEM;
	this->publicKeyFileName = null;
	this->publicKeyFileType = SSL_FILETYPE_PEM;
	this->remoteKeyFileName = null;
}

EppSessionTcp::~EppSessionTcp()
{
	this->cleanup();
}

void EppSessionTcp::cleanup()
{
	if( this->host != null )
	{
		delete [] this->host;
		this->host = null;
	}
	this->port = 0;
	if( this->privateKeyFileName != null )
	{
		delete [] this->privateKeyFileName;
		this->privateKeyFileName = null;
	}
	this->privateKeyFileType = SSL_FILETYPE_PEM;
	if( this->publicKeyFileName != null )
	{
		delete [] this->publicKeyFileName;
		this->publicKeyFileName = null;
	}
	this->publicKeyFileType = SSL_FILETYPE_PEM;
	if( this->remoteKeyFileName != null )
	{
		delete [] this->remoteKeyFileName;
		this->remoteKeyFileName = null;
	}
	if( this->channel != null )
	{
		this->channel->terminate();
		delete this->channel;
		this->channel = null;
	}
	if( this->useTls )
	{
		if( this->sslssl != null )
		{
			SSL_shutdown(this->sslssl);
			SSL_free(this->sslssl);
			this->sslssl = null;
		}
		if( this->sslctx != null )
		{
			SSL_CTX_free(this->sslctx);
			this->sslctx = null;
		}
	}
	if( this->sock >= 0 )
	{
		::shutdown(this->sock, 2);
		CLOSESOCKET(this->sock);
		this->sock = -1;
	}
}

void EppSessionTcp::initTLS()
{
	static bool tlsInit = false;
	if( tlsInit == false )
	{
		SSL_load_error_strings();
		SSL_library_init();
		OpenSSL_add_ssl_algorithms();

		tlsInit = true;
	}
	if( this->sock >= 0 )
	{
		::shutdown(this->sock, 2);
		CLOSESOCKET(this->sock);
		this->sock = -1;
	}
	if( this->sslssl != null )
	{
		SSL_shutdown(this->sslssl);
		SSL_free(this->sslssl);
		this->sslssl = null;
	}
	if( this->sslctx != null )
	{
		SSL_CTX_free(this->sslctx);
		this->sslctx = null;
	}
	initSocket();
	if( this->sock < 0 )
	{
		// error
		return;
	}
//	this->sslctx = SSL_CTX_new(TLSv1_client_method());
	this->sslctx = SSL_CTX_new(SSLv23_client_method());
	if( this->sslctx == null )
	{
		this->setException("Cannot initialize OpenSSL: SSL_CTX_new()");
		return;
	}
	if( this->publicKeyFileName != null )
	{
		if( SSL_CTX_use_certificate_chain_file(this->sslctx, this->publicKeyFileName) < 0 )
		{
			this->setException("Cannot load public key file");
			return;
		}
	}
	if( this->privateKeyFileName != null )
	{
		if( SSL_CTX_use_PrivateKey_file(this->sslctx, this->privateKeyFileName, this->privateKeyFileType) < 0 )
		{
			this->setException("Cannot load private key file");
			return;
		}
	}
	if( this->remoteKeyFileName != null )
	{
		if( SSL_CTX_load_verify_locations(this->sslctx, this->remoteKeyFileName, null) < 0 )
		{
			this->setException("Cannot load remote public key file");
			return;
		}
	}
	if( SSL_CTX_set_default_verify_paths(this->sslctx) < 0 )
	{
		this->setException("SSL_CTX_set_default_verify_paths failed");
		return;
	}
	SSL_CTX_set_verify(this->sslctx, SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, null);
	this->sslssl = SSL_new(this->sslctx);
	if( this->sslssl == null )
	{
		this->setException("Cannot initialize OpenSSL: SSL_new()");
		return;
	}

	// set socket to non-blocking
	int ofcmode = fcntl(this->sock, F_GETFL, 0);
	if (fcntl(this->sock, F_SETFL, ofcmode | O_NONBLOCK)) {
		::shutdown(this->sock, 2);
		CLOSESOCKET(this->sock);
		this->sock = -1;
		this->setException("Cannot set socket to non-blocking");
		return;
	}

	SSL_set_fd(this->sslssl, this->sock);
	
	time_t startTime;
	time(&startTime);
	
	while (true) 
	{
		int n = SSL_connect(this->sslssl);
		if (n > 0)
		{
			break; // success
		}

		bool retryConnect = false;
		
		int err = SSL_get_error(this->sslssl, n);
		
		if (err == SSL_ERROR_WANT_READ || 
		    err == SSL_ERROR_WANT_WRITE) 
#if 0
		{
			EppUtil::msSleep(50);
			continue; // retry
		}
#else
		/*
		 * In some cases it was observed that call of SSl_Connect fails and 
		 * SSL error code set to SSL_ERROR_WANT_READ or SSL_ERROR_WANT_WRITE.
		 * SSL documentation suggests that in case of these errors applications should
		 * retry which we have been doing. But sometimes this keeps on happening and 
		 * does not come out of loop of error & retry.
		 * SSL documentation suggests that for non-blocking sockets we can use select
		 * with timeout to control how much time we can stay and retry. 
		 * Following block of code does this.
		 */
		{
			fd_set			  r_fds;
			fd_set			  w_fds;
			int			  flag = 0;
			int			  status;
			struct timeval		  timeout;

			while (true)
			{
				retryConnect = false;

				time_t timeNow;
				time(&timeNow);
				double diff = difftime(timeNow, startTime);

				if (diff > (MAX_NUM_OF_DELAY_SECONDS/2))
				{
					retryConnect = false;
					break;
				}

				timeout.tv_sec  = 1;
				timeout.tv_usec = 0;
				
				FD_ZERO(&r_fds);
				FD_ZERO(&w_fds);
				FD_SET(this->sock, &r_fds);
				FD_SET(this->sock, &w_fds);

				status = ::select(this->sock + 1, 
						  &r_fds, 
						  &w_fds,
						  (fd_set *) NULL, 
						  &timeout);
				
				if( status < 0 )
				{
					// select error.
					retryConnect = false; 
					break;
				}
				else if( status > 0 )
				{
					// Some fd get ready, try connect now.
					retryConnect = true;
					break;
				}		
				else
				{
					// select timeout
					retryConnect = false;
					continue;
				}
			}
		}
		// Error occurred? Retry time lapsed?
		if (retryConnect)
		{
			continue;
		}
#endif
		// error
		SSL_shutdown(this->sslssl);
		SSL_free(this->sslssl);
		this->sslssl = null;
		this->setException("Cannot initialize OpenSSL: SSL_connect()");
		return;
	}
}

void EppSessionTcp::initSocket()
{
	fd_set			  fds;
	struct sockaddr_in	  http_addr;
	struct hostent		* http_host;
	int			  flag = 0;
	int			  secs;
	int			  status;
	struct timeval		  timeout;

	if( this->sock >= 0 )
	{
		::shutdown(this->sock, 2);
		CLOSESOCKET(this->sock);
		this->sock = -1;
	}
	http_host = gethostbyname(this->host);
	if( http_host == null )
	{
		this->setException("Cannot find host: gethostbyname()");
		goto leave;
	}
	this->sock = ::socket(AF_INET, SOCK_STREAM, 0);
	if( this->sock < 0 )
	{
		this->setException("Cannot get socket: socket()");
		goto leave;
	}
	if( this->sotimeout > 0 )
	{
		(void) ::setsockopt(this->sock, SOL_SOCKET, SO_RCVTIMEO,
			(char *) &this->sotimeout, sizeof(this->sotimeout));
		(void) ::setsockopt(this->sock, SOL_SOCKET, SO_SNDTIMEO,
			(char *) &this->sotimeout, sizeof(this->sotimeout));
	}
	flag = 1;
//	if( ioctl(this->sock, FIONBIO, &flag) < 0 )
//	{
//		this->setException("Cannot ioctl socket: ioctl()");
//		flag = 0;
//		goto leave;
//	}

	// set up server address/port

	http_addr.sin_port	= htons(port);
	http_addr.sin_family	= http_host->h_addrtype;
	(void) memcpy((char *) &http_addr.sin_addr,
				http_host->h_addr, http_host->h_length);

	// connect to the http server

	status = ::connect(this->sock, (struct sockaddr *) &http_addr, sizeof(http_addr));
	if( (status < 0) && (errno != EINPROGRESS) )
	{
		// other reason for connection failure
		flag = 0;
		goto leave;
	}
	else if( status >= 0 )
	{
		// already connected, done
		goto leave;
	}

	/*
	 * try to connect until we have a timeout, or the connection is
	 * successful, or the user hits the stop button
	 */
	secs = 0;
	while( (secs + secs) < MAX_NUM_OF_DELAY_SECONDS )
	{
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		FD_ZERO(&fds);
		FD_SET(this->sock, &fds);
		status = ::select(this->sock + 1, (fd_set *) NULL, &fds,
						  (fd_set *) NULL, &timeout);
		secs++;

		// for a non-blocking socket, if the previous connection
		// has not been completed, EALREADY will be set in errno;
		// otherwise, we have a real error

		if( (status < 0) && (errno != EALREADY) )
		{
			flag = 0;
			break;
		}
		else if( status > 0 )
		{
			// the connection is OK, add an extra check here for
			// connection success, if we try to connect again,
			// and get EISCONN, it means that we have a good
			// connection

			status = ::connect(this->sock, (struct sockaddr *) &http_addr, sizeof(http_addr));
			if( (status < 0) && (errno == EISCONN) )
			{
				status = 0;
			}
			// else, we got a real error
			else
			{
				flag = 0;
			}
			break;
		}
		// else, the select() says we are not ready yet. try to
		// connect again and make make sure. if we don't get
		// EALREADY or EISCONN, something is wrong
		status = ::connect(this->sock, (struct sockaddr *) &http_addr, sizeof(http_addr));
		if(    (status < 0)
		    && (errno != EALREADY)
		    && (errno != EISCONN) )
		{
			flag = 0;
			break;
		}
	} 

leave:

	// if flag is 0, there is an error, close the socket if needed

	if( (flag == 0) && (this->sock >= 0) )
	{
		CLOSESOCKET(this->sock);
		this->sock = -1;
		this->setException("Cannot connect to the server: connect()");
	}
}

void EppSessionTcp::init( void * object )
{
	// nothing to do for now
	if( object != null )
	{
		char ** argv = (char **) object;
		setPrivateKeyFile(argv[0], SSL_FILETYPE_PEM);
		setPublicKeyFile(argv[1], SSL_FILETYPE_PEM);
		setRemoteKeyFile(argv[2]);
	}
}


void EppSessionTcp::setPrivateKeyFile( char * name, int type )
{
	this->privateKeyFileType = type;
	if( this->privateKeyFileName != null )
	{
		delete this->privateKeyFileName;
		this->privateKeyFileName = null;
	}
	if( name != null )
	{
		this->privateKeyFileName = new char[strlen(name) + 1];
		if( this->privateKeyFileName != null )
		{
			(void) strcpy(this->privateKeyFileName, name);
		}
	}
}

void EppSessionTcp::setPublicKeyFile( char * name, int type )
{
	this->publicKeyFileType = type;
	if( this->publicKeyFileName != null )
	{
		delete this->publicKeyFileName;
		this->publicKeyFileName = null;
	}
	if( name != null )
	{
		this->publicKeyFileName = new char[strlen(name) + 1];
		if( this->publicKeyFileName != null )
		{
			(void) strcpy(this->publicKeyFileName, name);
		}
	}
}

void EppSessionTcp::setRemoteKeyFile( char * name )
{
	if( this->remoteKeyFileName != null )
	{
		delete this->remoteKeyFileName;
	}
	if( name != null )
	{
		this->remoteKeyFileName = new char[strlen(name) + 1];
		if( this->remoteKeyFileName != null )
		{
			(void) strcpy(this->remoteKeyFileName, name);
		}
	}
}

EppGreeting * EppSessionTcp::connect( const char * host, const int port )
{
	if( this->host != null )
	{
		delete [] this->host;
	}
	this->host = new char[strlen(host) + 1];
	(void) strcpy(this->host, host);
	this->port = port;
	this->setException(null);
	this->setMessage(null);

	char * str = null;
	int    len = 0;

	if( ! this->useTls )
	{
		initSocket();
		if( this->sock < 0 )
		{
			return null;
		}
		str = EppMessageUtil::getEppPayload(this->sock, &len);
		if( len == 0 )
		{
			this->setException(str);
			str = null;
		}
	}
	else
	{
		initTLS();
		if( this->sslssl == null )
		{
			return null;
		}
		str = EppMessageUtil::getEppPayload(this->sslssl, &len);
		if( len == 0 )
		{
			this->setException(str);
			str = null;
		}
	}
	this->setMessage(str);
	if( str == null )
	{
		return null;
	}
	EppParser parser(str, len);
	delete [] str;

	if( parser.hasError() )
	{
		return null;
	}
	return EppGreeting::fromXML(parser.getRootNode());
}

void EppSessionTcp::close()
{
	this->cleanup();
}

EppChannel * EppSessionTcp::getChannel()
{
	if( this->channel == null )
	{
		this->channel = new EppChannelTcp(this);
	}
	return this->channel;
}

EppGreeting * EppSessionTcp::hello()
{
	char * str = null;
	int    len = 0;
	EppHello hello;

	if( this->useTls )
	{
		if( this->sslssl == null )
		{
			return null;
		}
		str = EppMessageUtil::send(this->sslssl, hello.toString(), &len);
	}
	else
	{
		if( this->sock < 0 )
		{
			return null;
		}
		str = EppMessageUtil::send(this->sock, hello.toString(), &len);
	}
	this->setMessage(str);
	if( str == null )
	{
		this->setException("Error in EppSessionTcp::hello()");
		return null;
	}
	EppParser parser(str, len);
	if( parser.hasError() )
	{
		return null;
	}
	return EppGreeting::fromXML(parser.getRootNode());
}
