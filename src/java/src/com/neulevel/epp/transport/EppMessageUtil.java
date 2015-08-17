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
package com.neulevel.epp.transport;

import java.io.*;
import java.net.*;

/**
 * This <code>EppSessionUtil</code> class contains some utility methods for
 * handling message exchanges between an EPP Server and an EPP Client.
 *
 * @author Ning Zhang ning.zhang@neustar.com
 * @version $Revision: 1.2 $ $Date: 2008/11/13 17:03:08 $
 */
public class EppMessageUtil
{
	private static final int BUFSIZ = 8192;

	/**
	 * Timeout value in 1/10 seconds
	 */
	private static int   timeout = 0;

	/**
	 * Sets the timeout values in seconds. The default value is 0, which
	 * means there will be no timeout.
	 */
	public static void setTimeout( int seconds )
	{
		if( seconds > 0 )
		{
			EppMessageUtil.timeout = seconds * 10;
		}
	}

	/**
	 * Gets the timeout values in seconds. The default value is 0, which
	 * means there will be no timeout.
	 */
	public static int getTimeout()
	{
		return EppMessageUtil.timeout / 10;
	}

	/**
	 * Sends a string over a socket and reads a string back from
	 * the socket
	 *
	 * @param socket the socket used for sending the string
	 * @param str    the string to be sent over the socket
	 *
	 * @return a string containing the EPP message payload, or null
	 *         if there is any error associated with the connection to
	 *         the server
	 */
	public static String send( Socket socket, String str ) throws IOException
	{
		socket.setSoTimeout(EppMessageUtil.timeout*1000);
		OutputStream out = socket.getOutputStream();
		out.write(str.getBytes());
		out.flush();
		return EppMessageUtil.getEppPayload(socket.getInputStream());
	}

	/**
	 * Gets the EPP message payload from an input stream
	 *
	 * @param in the <code>InputStream</code> object from which the EPP
	 *           message payload is retrieved
	 *
	 * @return a string containing the EPP message payload, or null
	 *         if there is any error associated with the connection to
	 *         the server
	 */
	public static String getEppPayload( InputStream in ) throws IOException
	{
		StringBuffer rtn = new StringBuffer();
		byte[] buf = new byte[BUFSIZ];
		int i = 0;
		int n;
		boolean endFound = false;
		boolean eppFound = false;

		while( ! endFound )
		{
			int loop = 0;
			n = in.read();
			if (n == -1)//end of stream is reached from JDK1.6 documentaion
			{
				throw new IOException("Connection with server lost.Throwing Exception.");
			}

			// EPP payload rarely exceeds 8KB, so this
			// doubling-up should not occur very often

			if( i == buf.length )
			{
				byte[] newbuf = new byte[buf.length + BUFSIZ];
				for( i = 0; i < buf.length; i++ )
				{
					newbuf[i] = buf[i];
				}
				buf = newbuf;
			}
			buf[i++] = (byte) n;

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

		return new String(buf, 0, i).trim();
	}
}
