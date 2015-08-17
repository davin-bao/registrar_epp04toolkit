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
package com.neulevel.epp.core;

import java.io.*;
import java.text.*;
import java.util.*;
import org.w3c.dom.*;
import org.apache.xerces.dom.*;
import org.apache.xml.serialize.*;

/**
 * The <code>EppUtil</code> class implements some utility methods used
 * by various components in the EPP implementation.
 *
 * @author Ning Zhang ning.zhang@neustar.com
 * @version $Revision: 1.1 $ $Date: 2005/12/06 20:11:35 $
 */
public class EppUtil
{
	private static SimpleDateFormat xmlDateFormat;
	private static SimpleDateFormat xmlShortDateFormat;
	private static boolean fullNamespace = false;
	private static String version = "-1.0";

	/**
	 * Property for generating tags with namespace prefixes.
	 *
	 * @note this property is only required to be set with a value for
	 * communicating with EPP servers that expects that all object related
	 * tags, such as 
	 * <pre>
	 *        <contact:id>mycontact-id</contact:id>
	 * </pre>
	 * the contact prefix cannot be omitted as,
	 * <pre>
	 *        <id>mycontact-id</id>
	 * </pre>
 	 * even the default namespace has been specified in the XML message.
	 */
	public static final String xmlFullNamespace = "com.neulevel.epp.core.EppUtil.fullNamespace";

	static
	{
		xmlDateFormat = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss.S'Z'");
		xmlDateFormat.setTimeZone(TimeZone.getTimeZone("GMT"));
		xmlShortDateFormat = new SimpleDateFormat("yyyy-MM-dd");
		xmlShortDateFormat.setTimeZone(TimeZone.getTimeZone("GMT"));

		fullNamespace = System.getProperty(xmlFullNamespace) != null;
	}

	/**
	 * Sets the EPP XSD file version. The default value is "1.0",
	 * for EPP Schema dated on June 29, 2001.
	 */
	public static void setEppVersion( String eppVersion )
	{
		if( eppVersion == null )
		{
			version = "";
		}
		else if( (eppVersion.length() == 0) || (eppVersion.charAt(0) == '-') )
		{
			version = eppVersion;
		}
		else
		{
			version = "-" + eppVersion;
		}
	}

	/**
	 * Gets the EPP XSD file version.
	 */
	public static String getEppVersion()
	{
		if( version.length() == 0 )
		{
			return version;
		}
		return version.substring(1);
	}

	/**
	 * Creates an <code>ElementNSImpl</code> object inside a
	 * <code>Document</code> object. The namespace associated with the
	 * object is specific to EPP.
	 *
	 * @param doc <code>Document</code> object in which the new element
	 *            to be created.
	 * @param ns  The namespace of the new element to be created.
	 * @param tag The tag name of the new element to be created.
	 *
	 * @return an <code>ElementNSImpl</code> object
	 */
	public static ElementNSImpl createElementNS( Document doc, String ns, String tag )
	{
		return createElementNS(doc, ns, tag, true);
	}

	/**
	 * Creates an <code>ElementNSImpl</code> object inside a
	 * <code>Document</code> object. The namespace associated with the
	 * object is specific to EPP.
	 *
	 * @param doc <code>Document</code> object in which the new element to be
	 *            created.
	 * @param ns  The namespace of the new element to be created.
	 * @param tag The tag name of the new element to be created.
	 * @param flag The flag indicating if the default namespace is needed.
	 *
	 * @return an <code>ElementNSImpl</code> object
	 */
	public static ElementNSImpl createElementNS( Document doc, String ns, String tag, boolean flag )
	{
		ElementNSImpl elm;
		if( tag == null )
		{
			elm = (ElementNSImpl) doc.createElementNS("urn:iana:xml:ns:" + ns + version, ns);
			elm.setAttribute("xmlns", "urn:iana:xml:ns:" + ns + version);
			if( version.length() == 0 )
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
			elm = (ElementNSImpl) doc.createElementNS("urn:iana:xml:ns:" + ns + version, tag);
			elm.setPrefix(ns);
			if( flag )
			{
				elm.setAttribute("xmlns", "urn:iana:xml:ns:" + ns + version);
			}
			elm.setAttribute("xmlns:" + ns, "urn:iana:xml:ns:" + ns + version);
		}
		elm.setAttribute("xsi:schemaLocation", "urn:iana:xml:ns:" + ns + version + " " + ns + version + ".xsd");
		return elm;
	}

	/**
	 * Creates an <code>ElementNSImpl</code> object inside a
	 * <code>Document</code> object. The namespace associated with the
	 * object is specific to an <I>unspec</I> object in an
	 * <code>EppServiceMenu</code> object.
	 *
	 * @param doc <code>Document</code> object in which the new element to be
	 *            created.
	 * @param unspec The string containing the information about the
	 *        <I>unspec</I> object with three tokens: name, uri, schema. For
	 *        example: "obj1ext http://custom/obj1ext-1.0 obj1ext-1.0.xsd"
	 * @param tag The tag name of the new element to be created.
	 * @param flag The flag indicating if the default namespace is needed.
	 *
	 * @return an <code>ElementNSImpl</code> object, or null if the
	 *         <code>unspec</code> parameter is not valid.
	 */
	public static ElementNSImpl createElementNSUnspec( Document doc, String unspec, String tag, boolean flag )
	{
		StringTokenizer tok = new StringTokenizer(unspec);
		if( tok.countTokens() != 3 )
		{
			return null;
		}
		String ns  = tok.nextToken();
		String uri = tok.nextToken();
		String loc = uri + " " + tok.nextToken();

		ElementNSImpl elm;
		if( tag == null )
		{
			elm = (ElementNSImpl) doc.createElementNS(uri, ns);
			elm.setAttribute("xmlns", uri);
			if( version.length() == 0 )
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
			elm = (ElementNSImpl) doc.createElementNS(uri, tag);
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

	/**
	 * Creates a <code>Text</code> node for converting a
	 * <code>Calendar</code> object into a string of XML timeInstant type.
	 *
	 * @param doc <code>Document</code> object in which the new element
	 *            to be
	 *            created.
	 * @param cal The <code>Calendar</code> to be converted into a XML
	 *            <code>Text</code> node.
	 */
	public static Text createTextNode( Document doc, Calendar cal )
	{
		return createTextNode(doc, cal, false);
	}

	/**
	 * Creates a <code>Text</code> node for converting a
	 * <code>Calendar</code> object into a string of XML timeInstant
	 * type or XML date type.
	 *
	 * @param doc <code>Document</code> object in which the new element
	 *            to be created.
	 * @param cal The <code>Calendar</code> to be converted into a XML
	 *            <code>Text</code> node.
	 * @param dateOnly true if the format is XML date type, or false
	 *                 if the format is XML timeInstant type
	 */
	public static Text createTextNode( Document doc, Calendar cal, boolean dateOnly )
	{
		if( dateOnly )
		{
			return doc.createTextNode(xmlShortDateFormat.format(cal.getTime()));
		}
		else
		{
			return doc.createTextNode(xmlDateFormat.format(cal.getTime()));
		}
	}

	/**
	 * Gets the text string associated with a node
	 *
	 * @param root <code>Node</code> object from which text to be extracted.
	 *
	 * @return a string associated with the node
	 */
	public static String getText( Node root )
	{
		NodeList list = root.getChildNodes();
		if( (list == null) && (list.getLength() == 0) )
		{
			String str = root.getNodeValue();
			if( str == null )
			{
				str = "";
			}
			return str;
		}
		StringBuffer buf = new StringBuffer();
		for( int i = 0; i < list.getLength(); i++ )
		{
			Node node = list.item(i);
			if( node instanceof TextImpl )
			{
				String val = ((TextImpl) node).getNodeValue();
				if( (val != null) && (val.length() > 0) )
				{
					buf.append(val);
				}
			}
		}
		return buf.toString();
	}

	/**
	 * Converts a text string associated with a node into a
	 * <code>Calendar</code> object
	 *
	 * @param root <code>Node</code> object from which text to be extracted.
	 *
	 * @return a <code>Calendar</code> object, or null if the text string is
	 *         not a valid XML timeInstant string
	 */
	public static Calendar getDate( Node root )
	{
		return getDate(root, false);
	}

	/**
	 * Converts a text string associated with a node into a
	 * <code>Calendar</code> object
	 *
	 * @param root <code>Node</code> object from which text to be extracted.
	 * @param dateOnly true for parsing the string in XML date format, or
	 *                 false for parsing the string in XML timeInstant
	 *                 format
	 *
	 * @return a <code>Calendar</code> object, or null if the text string is
	 *         not a valid XML timeInstant/date string
	 */
	public static Calendar getDate( Node root, boolean dateOnly )
	{
		Calendar cal = null;

		String s = EppUtil.getText(root);
		if( (s != null) && (s.length() > 0) )
		{
			ParsePosition ps = new ParsePosition(0);
			Date date = null;
			if( dateOnly )
			{
				date = xmlShortDateFormat.parse(s, ps);
			}
			else
			{
				date = xmlDateFormat.parse(s, ps);
			}
			if( date != null )
			{
				cal = Calendar.getInstance();
				cal.setTime(date);
			}
		}

		return cal;
	}

	/**
	 * Converts a <code>Document</code> into a formated XML string.
	 *
	 * @param doc <code>Document</code> to be converted into a string.
	 *
	 * @return a string representing the formated XML document
	 */
	public static String toString( Document doc )
	{
		StringWriter str = new StringWriter();

		try
		{
			if( fullNamespace )
			{
				EppWriter out = new EppWriter(new PrintWriter(str));
				out.print(doc);
			}
			else
			{
				OutputFormat out = new OutputFormat(doc);
				out.setIndenting(true);
				out.setIndent(1);
				out.setStandalone(false);
				out.setEncoding("UTF-8");

				XMLSerializer ser = new XMLSerializer(str, out);
				ser.serialize(doc.getDocumentElement());
			}
		}
		catch( Exception e )
		{
			return null;
		}

		return str.toString();
	}
}

/**
 * This <code>EppWriter</code> class is specifically designed to add
 * name space prefix string inside object specific elements for fixing
 * the problem in Tucows' EPP Toolkit that it looks for hard-coded tag
 * names like "contact:roid", which is bad programming practice.
 */
class EppWriter
{
	private boolean     canonical;
	private PrintWriter out;
	private String      encoding = "UTF-8";

	/*
	 * Creates a <code>EppWriter</code> object
	 */
	public EppWriter( PrintWriter out )
	{
		this(out, false);
	}

	/*
	 * Creates a <code>EppWriter</code> object, with a cannonical flag
	 */
	public EppWriter( PrintWriter out, boolean canonical )
	{
		this.out = out;
		this.canonical = canonical;
	}

	/*
	 * Prints the specified node, recursively
	 */
	public void print( Node node )
	{
		print(node, 0, null);
	}

	/*
	 * Prints the specified node, recursively, given an indent level
	 * and a default prefix string.
	 */
	public void print( Node node, int level, String prefix )
	{
		if( node == null )
		{
			return;
		}

		NodeList list = null;
		int type = node.getNodeType();
		switch( type )
		{
		case Node.DOCUMENT_NODE:
			if( ! canonical )
			{
				out.println("<?xml version=\"1.0\" encoding=\"" 
					+ encoding + "\"?>");
			}
			list = node.getChildNodes();
			if( list != null )
			{
				for( int i = 0; i < list.getLength(); i++ )
				{
					print(list.item(i), level, prefix);
				}
			}
			break;

		case Node.ELEMENT_NODE:
			for( int i = 0; i < level; i++ )
			{
				out.print(' ');
			}
			out.print('<');
			String newPrefix = node.getPrefix();
			if( newPrefix != null )
			{
				prefix = newPrefix;
			}
			if( (newPrefix == null) && (prefix != null) )
			{
				out.print(prefix);
				out.print(':');
			}
			out.print(node.getNodeName());
			Attr attrs[] = sortAttributes(node.getAttributes());
			if( attrs != null )
			{
				for ( int i = 0; i < attrs.length; i++ )
				{
					Attr attr = attrs[i];
					out.print(' ');
					out.print(attr.getNodeName());
					out.print("=\"");
					out.print(normalize(attr.getNodeValue()));
					out.print('"');
				}
			}
			list = node.getChildNodes(); 
			if( list == null )
			{
				out.println("/>");
			}
			else
			{
				boolean cr = false;
				out.print('>');
				for( int i = 0; i < list.getLength(); i++ )
				{
					if( i == 0 )
					{
						int c = list.item(0).getNodeType();
						if( c != Node.TEXT_NODE )
						{
							out.println();
							cr = true;
						}
					}
					print(list.item(i), level + 1, prefix);
				}
				if( cr )
				{
					for( int i = 0; i < level; i++ )
					{
						out.print(' ');
					}
				}
				out.print('<');
				out.print('/');
				if( (newPrefix == null) && (prefix != null) )
				{
					out.print(prefix);
					out.print(':');
				}
				out.print(node.getNodeName());
				out.println('>');
			}
			break;

		case Node.ENTITY_REFERENCE_NODE:
			if( canonical )
			{
				list = node.getChildNodes(); 
				if( list != null )
				{
					for( int i = 0; i < list.getLength(); i++ )
					{
						print(list.item(i), level, prefix);
					}
				}
			}
			else
			{
				out.print('&');
				out.print(node.getNodeName());
				out.print(';');
			}
			break;

		case Node.CDATA_SECTION_NODE:
			if( canonical )
			{
				out.print(normalize(node.getNodeValue()));
			}
			else
			{
				out.print("<![CDATA[");
				out.print(node.getNodeValue());
				out.print("]]>");
			}
			break;

		case Node.TEXT_NODE:
			out.print(normalize(node.getNodeValue()));
			break;

		case Node.PROCESSING_INSTRUCTION_NODE:
			out.print("<?");
			out.print(node.getNodeName());
			String data = node.getNodeValue();
			if ( data != null && data.length() > 0 )
			{
				out.print(' ');
				out.print(data);
			}
			out.println("?>");
			break;

		default:
			break;
		}

		out.flush();
	}

	/**
	 * Sorts a list of attributes in alphabetic order
	 * based on the attribute names.
	 */
	protected Attr[] sortAttributes( NamedNodeMap attrs )
	{
		if( attrs == null )
		{
			return null;
		}
		int len = attrs.getLength();
		if( len == 0 )
		{
			return null;
		}
		Attr array[] = new Attr[len];
		for ( int i = 0; i < len; i++ )
		{
			array[i] = (Attr) attrs.item(i);
		}
		for ( int i = 0; i < len - 1; i++ )
		{
			String name = array[i].getNodeName();
			int index = i;
			for ( int j = i + 1; j < len; j++ )
			{
				String curName = array[j].getNodeName();
				if ( curName.compareTo(name) < 0 )
				{
					name = curName;
					index = j;
				}
			}
			if ( index != i )
			{
				Attr temp    = array[i];
				array[i]     = array[index];
				array[index] = temp;
			}
		}

		return array;
	}

	/**
	 * Normalizes a string by escaping special characters such as
	 * ';&lt;', '&gt;', '&amp;', '&quot;', '\r', '\n'
	 */
	protected String normalize( String s )
	{
		StringBuffer str = new StringBuffer();

		int len = (s != null) ? s.length() : 0;
		for ( int i = 0; i < len; i++ )
		{
			char ch = s.charAt(i);
			switch( ch )
			{
			case '<':
				str.append("&lt;");
				break;
			case '>':
				str.append("&gt;");
				break;
			case '&':
				str.append("&amp;");
				break;
			case '"':
				str.append("&quot;");
				break;
			case '\r':
			case '\n':
				if( canonical )
				{
					str.append("&#");
					str.append(Integer.toString(ch));
					str.append(';');
					break;
				}
				// else, default append char
			default:
				str.append(ch);
				break;
			}
		}

		return str.toString();
	}
}
