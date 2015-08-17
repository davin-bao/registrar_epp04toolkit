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
#if ! defined(_XOPEN_SOURCE)    /* { */
/*
 * for strptime() only
 */
#define       _XOPEN_SOURCE        1
#endif     /* _XOPEN_SOURCE */  /* } */

#include <stdio.h>
#include <string.h>

#if	   ! defined(WIN32)  	/* { */
//#include <stream.h>
#endif	/* ! defined(WIN32) */	/* } */

#include <iostream>
#include <time.h>
#include "EppEntity.hpp"
#include "EppUtil.hpp"

#if        defined(solaris)     /* { */
extern "C" {
extern char *strptime(const char *, const char *, struct tm *);
};
#endif	/* defined(solaris) */  /* } */

static char * estr [6] = { "&lt;", "&gt;", "&quot;", "&amp;", "&#13;", "&#10" };

#define	   EPP_SUPPORT_UNSIGNED_TIME_T		   1
#if	   EPP_SUPPORT_UNSIGNED_TIME_T		/* { */
#include   "EppUtilTime.cpp"
#endif	/* EPP_SUPPORT_UNSIGNED_TIME_T	*/	/* } */

/**
 * This <code>EppWriter</code> class is specifically designed to add
 * name space prefix string inside object specific elements for fixing
 * the problem in Tucows' EPP Toolkit that it looks for hard-coded tag
 * names like "contact:roid", which is bad programming practice.
 */
class EppWriter
{
private:
	bool canonical;
	DOMString out;
	DOMString encoding;

public:
	EppWriter()
	{
		canonical = false;
		out = DOMString("");
		encoding = DOMString("UTF-8");
	};
	~EppWriter()
	{
	};

	DOMString getOutput()
	{
		return out;
	}

	void print( const DOM_Node &node )
	{
		this->print(node, 0, null);
	};

	void print( const DOM_Node &node, int level, DOMString prefix );

	/**
	 * Normalizes a string by escaping special characters such as
	 * ';&lt;', '&gt;', '&amp;', '&quot;', '\r', '\n'
	 */
	void normalize( DOMString& out, DOMString& s )
	{

		int len = (s != null) ? s.length() : 0;
		if( len == 0 )
		{
			return;
		}

		for ( int i = 0; i < len; i++ )
		{
			XMLCh ch = s.charAt(i);
			if( ch == '<' )
			{
				out += estr[0];
			}
			else if( ch == '>' )
			{
				out += estr[1];
			}
			else if( ch == '"' )
			{
				out += estr[2];
			}
			else if( ch == '&' )
			{

				out += estr[3];
			}
			else if( canonical && (ch == '\r') )
			{
				out += estr[4];
			}
			else if( canonical && (ch == '\n') )
			{
				out += estr[5];
			}
			else
			{
				out += ch;
			}
		}
	};
};

void EppWriter::print( const DOM_Node &node, int level, DOMString prefix )
{
	unsigned int i = 0;
	int j = 0;
	if( node == null )
	{
		return;
	}

	DOM_NodeList list;
	DOM_NamedNodeMap attrs;
	DOMString newPrefix;
	int type = node.getNodeType();
	switch( type )
	{
	case DOM_Node::DOCUMENT_NODE:
		if( ! canonical )
		{
			out += "<?xml version=\"1.0\" encoding=\""
				+ encoding + "\"?>";
			out += "\n";
		}
		list = node.getChildNodes();
		if( list != null )
		{
			for( i = 0; i < list.getLength(); i++ )
			{
				print(list.item(i), level, prefix);
			}
		}
		break;

	case DOM_Node::ELEMENT_NODE:
		for( j = 0; j < level; j++ )
		{
			out += " ";
		}
		out += "<";
		newPrefix = node.getPrefix();
		if( newPrefix != null )
		{
			prefix = newPrefix;
		}
		if( (newPrefix == null) && (prefix != null) )
		{
			out += prefix;
			out += ":";
		}
		out += node.getNodeName();
		attrs = node.getAttributes();
		if( attrs != null )
		{
			for( i = 0; i < attrs.getLength(); i++ )
			{
				DOM_Node attr = attrs.item(i);
				out += " ";
				out += attr.getNodeName();
				out += "=\"";
				out += attr.getNodeValue();
				out += "\"";
			}
		}	
		list = node.getChildNodes();
		if( (list == null) || (list.getLength() == 0) )
		{
			out += "/>\n";
		}
		else
		{
			bool cr = false;
			out += ">";
			for( i = 0; i < list.getLength(); i++ )
			{
				if( i == 0 )
				{
					if( list.item(0).getNodeType() != DOM_Node::TEXT_NODE )
					{
						out += "\n";
						cr = true;
					}
				}
				print(list.item(i), level + 1, prefix);
			}
			if( cr )
			{
				for( j = 0; j < level; j++ )
				{
					out += " ";
				}
			}
			out += "</";
			if( (newPrefix == null) && (prefix != null) )
			{
				out += prefix;
				out += ":";
			}
			out += node.getNodeName();
			out += ">\n";
		}
		break;

	case DOM_Node::TEXT_NODE:
		{
			DOMString p = node.getNodeValue();
			this->normalize(out, p);
//			out += node.getNodeValue();
		}
		break;

	default:
		break;
	}
}

char EppUtil::version[MAX_VERSION_LENGTH] = { '-', '1', '.', '0', 0};

void EppUtil::setEppVersion( const char * eppVersion )
{
	if( eppVersion == null )
	{
		version[0] = 0;
	}
	else if( ::strlen(eppVersion) == 0 )
	{
		version[0] = 0;
	}
	else if( eppVersion[0] == '-' )
	{
		(void) ::strncpy(version, eppVersion, MAX_VERSION_LENGTH - 1);
		EppUtil::version[MAX_VERSION_LENGTH - 1] = 0;
	}
	else
	{
		version[0] = '-';
		(void) ::strncpy(&version[1], eppVersion, MAX_VERSION_LENGTH - 2);
		EppUtil::version[MAX_VERSION_LENGTH - 1] = 0;
	}
}

const char * EppUtil::getEppVersion()
{
	if( version[0] == 0 )
	{
		return (const char *) &version[0];
	}
	else
	{
		return (const char *) &version[1];
	}
}

DOM_Element EppUtil::createElementNS( DOM_Document& doc, const DOMString ns, const DOMString tag )
{
	return EppUtil::createElementNS(doc, ns, tag, true);
}

DOM_Element EppUtil::createElementNS( DOM_Document& doc, const DOMString ns, const DOMString tag, bool flag )
{
	DOM_Element elm;
	DOMString prefix("urn:iana:xml:ns:");
	if( tag == null )
	{
		elm = doc.createElementNS(prefix + ns + version, ns);
		elm.setAttribute("xmlns", "urn:iana:xml:ns:" + ns + version);
		if( version[0] == 0 )
		{
			// old EPP-02 schema
			elm.setAttribute("xmlns:xsi", "http://www.w3.org/2000/10/XMLSchema-instance");
		}
		else
		{
			elm.setAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
		}
	}
	else
	{
		elm = doc.createElementNS(prefix + ns + version, tag);
		elm.setPrefix(ns);
		if( flag )
		{
			elm.setAttribute("xmlns", prefix + ns + version);
		}
		elm.setAttribute("xmlns:" + ns, prefix + ns + version);
	}
	elm.setAttribute("xsi:schemaLocation", prefix + ns + version + " " + ns + version + ".xsd");

	return elm;
}

DOM_Element EppUtil::createElementNSUnspec( DOM_Document& doc, const DOMString unspec, const DOMString tag, bool flag )
{
	unsigned int len = unspec.length();
	unsigned int index_ns;
	unsigned int index_uri;
	unsigned int index;

	DOMString ns  = null;
	DOMString uri = null;
	DOMString loc = null;

	for( index = 0; index < len; index++ )
	{
		if( unspec.charAt(index) == ' ' )
		{
			ns = unspec.substringData(0, index);
			index_ns = index;
			break;
		}
	}
	for( index = index_ns + 1; index < len; index++ )
	{
		if( unspec.charAt(index) == ' ' )
		{
			uri = unspec.substringData(index_ns + 1, index - index_ns - 1);
			index_uri = index;
			break;
		}
	}
	if( index < len )
	{
		loc = unspec.substringData(index_uri + 1, len - index_uri - 1);
	}
	if( (ns == null) || (uri == null) || (loc == null) )
	{
		return DOM_Element();
	}

	loc = uri + " " + loc;

	DOM_Element elm;
	if( tag == null )
	{
		elm = doc.createElementNS(uri, ns);
		elm.setAttribute("xmlns", uri);
		if( version[0] == 0 )
		{
			// old EPP-02 schema
			elm.setAttribute("xmlns:xsi", "http://www.w3.org/2000/10/XMLSchema-instance");
		}
		else
		{
			elm.setAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
		}
	}
	else
	{
		elm = doc.createElementNS(uri, tag);
		elm.setPrefix(ns);
		if( flag )
		{
			elm.setAttribute("xmlns", uri);
		}
		elm.setAttribute("xmlns:" + ns, uri);
	}
	elm.setAttribute("xsi:schemaLocation", loc);

	return elm;
}

DOM_Text EppUtil::createTextNode( DOM_Document& doc, const time_t cal )
{
	return EppUtil::createTextNode(doc, cal, false);
}

DOM_Text EppUtil::createTextNode( DOM_Document& doc, const time_t cal, bool dateOnly )
{
	char buf[128];
	struct tm tmp;

#if	   EPP_SUPPORT_UNSIGNED_TIME_T		/* { */

	long long t = (long long) ((unsigned int) cal);
	(void) gmtime64_r(&t, &tmp);

#else	/* EPP_SUPPORT_UNSIGNED_TIME_T	*/	/* } */

#if       defined(win32)      /* { */
	struct tm * p = gmtime(&cal);
	tmp = *p;
#else  /* defined(win32) */   /* } { */
	(void) gmtime_r(&cal, &tmp);
#endif /* defined(win32) */   /* } */

#endif	/* EPP_SUPPORT_UNSIGNED_TIME_T	*/	/* } */

	const char * fmt = dateOnly ? "%Y-%m-%d" : "%Y-%m-%dT%H:%M:%S.0Z";
	buf[0] = '\0';
	(void) strftime(buf, sizeof(buf), fmt, &tmp);

	return doc.createTextNode(buf);
}

DOMString EppUtil::getText( const DOM_Node &root )
{
	DOM_NodeList list = root.getChildNodes();
	if( list.getLength() == 0 )
	{
		return root.getNodeValue();
	}

	DOMString str = DOMString("");
	for( unsigned int i = 0; i < list.getLength(); i++ )
	{
		DOM_Node node = list.item(i);
		if( node.getNodeType() == DOM_Node::TEXT_NODE )
		{
			DOMString val = node.getNodeValue();
			str += val;
		}
	}
	return str;
}

bool EppUtil::getTextAsBool( const DOM_Node &root )
{
	DOMString str = getText(root);
	
	unsigned int length = str.length();
	if (length == 1 && (str.charAt(0) == (XMLCh)'1'))
	{
		return true;
	}
	else if (length == 4)
	{
		XMLCh c;

		c = str.charAt(0);
		if ( c != (XMLCh)'t' && c != (XMLCh)'T' )
			return false;

		c = str.charAt(1);
		if ( c != (XMLCh)'r' && c != (XMLCh)'R' )
			return false;

		c = str.charAt(2);
		if ( c != (XMLCh)'u' && c != (XMLCh)'U' )
			return false;

		c = str.charAt(3);
		if ( c != (XMLCh)'e' && c != (XMLCh)'E' )
			return false;

		return true;
	}
	return false;
}

time_t EppUtil::getDate( const DOM_Node& root )
{
	return EppUtil::getDate(root, false);
}


time_t EppUtil::getDate( const DOM_Node& root, bool dateOnly )
{
	time_t cal = 0;

	DOMString s = EppUtil::getText(root);
	if( (s != null) && (s.length() > 0) )
	{
		char * buf = s.transcode();
		if( buf != null )
		{
			cal = EppUtil::getDate(buf, dateOnly);
			delete [] buf;
		}
	}

	return cal;
}


time_t EppUtil::getDate( const char * s, bool dateOnly )
{
	time_t cal = 0;
	struct tm tmp;
#if       defined(win32)      /* { */
	const char * fmt = dateOnly ? "%4d-%2d-%2d" : "%4d-%2d-%2dT%2d:%2d:%2d.0Z";
#else  /* defined(win32) */   /* } { */
#if       defined(hpux)       /* { */
	const char * fmt = dateOnly ? "%Y-%m-%d" : "%Y-%m-%d %H:%M:%S.0Z";
#else  /* defined(hpux) */    /* } { */
	const char * fmt = dateOnly ? "%Y-%m-%d" : "%Y-%m-%dT%H:%M:%S.0Z";
#endif /* defined(hpux) */    /* } */
#endif /* defined(win32) */   /* } */

	if( (s != null) && (*s != '\0') )
	{
		char * buf = ::strdup(s);
		if( buf != null )
		{
#if       defined(hpux)       /* { */
			char * cp = buf;
			while( *cp != '\0' )
			{
				if( *cp == 'T' )
				{
					*cp = ' ';
					break;
				}
				cp++;
			}
#endif /* defined(hpux) */    /* } */

			(void) memset((char *) &tmp, '\0', sizeof(tmp));

#if       defined(win32)      /* { */

			char * c = "";
			if( dateOnly )
			{
				if( sscanf(buf, fmt, &tmp.tm_year, &tmp.tm_mon,
					&tmp.tm_mday) != 3 )
				{
					c = null;
				}
			}
			else
			{
				if( sscanf(buf, fmt, &tmp.tm_year, &tmp.tm_mon,
					&tmp.tm_mday, &tmp.tm_hour, &tmp.tm_min,
					&tmp.tm_sec) != 6 )
				{
					c = null;
				}
			}
			if( c != null )
			{
				tmp.tm_year -= 1900;
				tmp.tm_mon--;
			}

#else  /* defined(win32) */   /* } { */
			char * c = (char *) strptime(buf, fmt, &tmp);
			if( c == null )
			{
				// error
			}
#endif /* defined(win32) */   /* } */

#if	   EPP_SUPPORT_UNSIGNED_TIME_T		/* { */

			long long t = mktime64(&tmp) - timezone + daylight * 3600;
			cal = t & 0xFFFFFFFF;

#else	/* EPP_SUPPORT_UNSIGNED_TIME_T	*/	/* } */

//			if( strptime(buf, fmt, &tmp) == null )
//			if( (c == null) || (*c == '\0') )
			{
				cal = mktime(&tmp) - timezone + daylight * 3600;
			}

#endif	/* EPP_SUPPORT_UNSIGNED_TIME_T	*/	/* } */

			(void) ::free(buf);
		}
	}

	return cal;
}


DOMString EppUtil::toString( const DOM_Document &doc )
{
	EppWriter out = EppWriter();
	out.print(doc);
	return out.getOutput();
}


void EppUtil::msSleep(unsigned int milliseconds)
{
#if       defined(WIN32)       /* { */

        ::Sleep(milliseconds);

#else  /* defined(WIN32) */    /* } { */

        struct timespec req, rem;

        int seconds = milliseconds / 1000;
        milliseconds -= seconds * 1000;

        req.tv_sec = seconds;
        req.tv_nsec = milliseconds * 1000;

        ::nanosleep(&req, &rem);
#endif /* defined(WIN32) */    /* } */
}

