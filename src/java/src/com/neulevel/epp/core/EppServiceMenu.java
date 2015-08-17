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

import java.util.*;
import org.w3c.dom.*;

/**
 * This <code>EppServiceMenu</code> class implements EPP svcMenuType entity.
 *
 * @author Ning Zhang ning.zhang@neustar.com
 * @version $Revision: 1.1 $ $Date: 2005/12/06 20:11:35 $
 */
public class EppServiceMenu extends EppEntity
{
	/**
	 * The version list of the EPP Service Menu
	 */
	protected Vector version;
	/**
	 * The language list of the EPP Service Menu
	 */
	protected Vector lang;
	/**
	 * The standard object list of the EPP Service Menu
	 */
	protected Vector svc;
	/**
	 * The <I>unspec</I> object list of the EPP Service Menu. Each entry
	 * contains three tokens: name, url, and schema file name.
	 * For example: "obj1ext http://custom/obj1ext-1.0 obj1ext-1.0.xsd"
	 */
	protected Vector unspec;

	/**
	 * Creates an <code>EppServiceMenu</code> object
	 */
	public EppServiceMenu()
	{
		this.version = new Vector();
		this.lang    = new Vector();
		this.svc     = new Vector();
		this.unspec  = new Vector();
	}

	/**
	 * Returns a <code>Vector</code> containing all version numbers
	 * supported by the EPP server
	 */
	public Vector getVersion()
	{
		return this.version;
	}

	/**
	 * Adds a version number to the list of versions supported by the
	 * EPP server
	 */
	public void addVersion( String version )
	{
		this.version.addElement(version);
	}

	/**
	 * Returns a <code>Vector</code> containing all languages supported
	 * by the Epp server
	 */
	public Vector getLanguage()
	{
		return this.lang;
	}

	/**
	 * Adds a language to the list of languages supported by the
	 * EPP server
	 */
	public void addLanguage( String language )
	{
		this.lang.addElement(language);
	}

	/**
	 * Returns a <code>Vector</code> containing the name space and schema
	 * location of all objects supported by the EPP server
	 */
	public Vector getService()
	{
		return this.svc;
	}

	/**
	 * Adds an object name to the list of all objects supported by
	 * the EPP server
	 */
	public void addService( String service )
	{
		this.svc.addElement(service);
	}

	/**
	 * Returns a <code>Vector</code> containing the name space and schema
	 * location of all <I>unspec</I> objects supported by the EPP server.
	 * Each entry in the vector is a string containing three tokens:
	 * three tokens: name, url, and schema file name. For example:
	 * "obj1ext http://custom/obj1ext-1.0 obj1ext-1.0.xsd"
	 */
	public Vector getUnspec()
	{
		return this.unspec;
	}

	/**
	 * Adds an <I>unspec</I> object to the list of all <I>unspec</I>
	 * objects supported by the EPP server
	 *
	 * @param name the name of the object
	 * @param uri the uri of the object
	 * @param schema the XML schema defining the object
	 *
	 * @note if any of the parameters is null, empty, or containing spaces
	 *       no action will be taken
	 */
	public void addUnspec( String name, String uri, String schema )
	{
		if( (name == null) || (uri == null) || (schema == null) )
		{
			return;
		}
		name   = name.trim();
		uri    = uri.trim();
		schema = schema.trim();
		if( (name.length() == 0) || (uri.length() == 0) || (schema.length() == 0) )
		{
			return;
		}
		if( (name.indexOf(' ') >= 0) || (uri.indexOf(' ') >= 0) || (schema.indexOf(' ') >= 0) )
		{
			return;
		}
		this.unspec.addElement(name + " " + uri + " " + schema);
	}

	/**
	 * Converts the <code>EppServiceMenu</code> object into an XML element
	 *
	 * @param doc the XML <code>Document</code> object
	 * @param tag the tag/element name for the <code>EppServiceMenu</code>
	 *            object
	 *
	 * @return an <code>Element</code> object
	 */
	public Element toXML( Document doc, String tag )
	{
		Element elm;
		Element body = doc.createElement(tag);

		if( version != null )
		{
			for( int i = 0; i < version.size(); i++ )
			{
				Object obj = version.get(i);
				if( (obj != null) && (obj instanceof String) )
				{
					elm = doc.createElement("version");
					elm.appendChild(doc.createTextNode((String) obj));
					body.appendChild(elm);
				}
			}
		}
		if( lang != null )
		{
			for( int i = 0; i < lang.size(); i++ )
			{
				Object obj = lang.get(i);
				if( (obj != null) && (obj instanceof String) )
				{
					elm = doc.createElement("lang");
					elm.appendChild(doc.createTextNode((String) obj));
					body.appendChild(elm);
				}
			}
		}
		if( svc != null )
		{
			for( int i = 0; i < svc.size(); i++ )
			{
				Object obj = svc.get(i);
				if( (obj != null) && (obj instanceof String) )
				{
					elm = EppUtil.createElementNS(doc, (String) obj, "svc", false);
					body.appendChild(elm);
				}
			}
		}
		if( (unspec != null) && (unspec.size() > 0) )
		{
			elm = doc.createElement("unspec");
			for( int i = 0; i < unspec.size(); i++ )
			{
				Object obj = unspec.get(i);
				if( (obj != null) && (obj instanceof String) )
				{
					Element unspec = EppUtil.createElementNSUnspec(doc, (String) obj, "svc", false);
					if( unspec != null )
					{
						elm.appendChild(unspec);
					}
				}
			}

			body.appendChild(elm);
		}

		return body;
	}

	/**
	 * Converts an XML element into an <code>EppServiceMenu</code> object.
	 * The caller of this method must make sure that the root node is of
	 * the EPP addrType.
	 *
	 * @param root root node for an <code>EppServiceMenu</code> object
	 *             in XML format
	 *
	 * @return an <code>EppServiceMenu</code> object, or null if the node
	 *         is invalid
	 */
	public static EppEntity fromXML( Node root )
	{
		EppServiceMenu svcmenu = new EppServiceMenu();
		NodeList list = root.getChildNodes();
		for( int i = 0; i < list.getLength(); i++ )
		{
			Node node = list.item(i);
			String name = node.getLocalName();
			if( name == null )
			{
				continue;
			}
			if( name.equals("version") )
			{
				svcmenu.addVersion(EppUtil.getText(node));
			}
			else if( name.equals("lang") )
			{
				svcmenu.addLanguage(EppUtil.getText(node));
			}
			else if( name.equals("svc") )
			{
				String prefix = node.getPrefix();
				if( prefix != null )
				{
					svcmenu.addService(prefix);
				}
			}
			else if( name.equals("unspec") )
			{
				NodeList ulist = node.getChildNodes();
				for( int j = 0; j < ulist.getLength(); j++ )
				{
					Element unode = (Element) ulist.item(j);
					name = unode.getLocalName();
					if( name.equals("svc") )
					{
						String prefix = unode.getPrefix();
						String uri = unode.getAttribute("xmlns:" + prefix);
						String loc = unode.getAttribute("xsi:schemaLocation");
						// schema location is prefixed
						// with the uri plus a space
						loc = loc.substring(uri.length() + 1);
						svcmenu.addUnspec(prefix, uri, loc);
					}
				}
			}
		}

		return svcmenu;
	}

	public String toString()
	{
		return toString("svcMenu");
	}
}
