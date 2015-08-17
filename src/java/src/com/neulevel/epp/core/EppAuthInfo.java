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

import org.w3c.dom.*;

/**
 * This <code>EppAuthInfo</code> class implements EPP AuthInfo entity.
 *
 * @author Ning Zhang ning.zhang@neustar.com
 * @version $Revision: 1.1 $ $Date: 2005/12/06 20:11:35 $
 */
public class EppAuthInfo extends EppEntity
{
	/**
	 * Authorization type "pw" for password
	 */
	public static final String TYPE_PW = "pw";

	private String type;
	private String roid;
	private String value;

	/**
	 * Creates an <code>EppAuthInfo</code> object
	 *
	 * @note the only type value is "pw", for password
	 */
	public EppAuthInfo( String type, String value )
	{
		this(type, value, null);
	}

	/**
	 * Creates an <code>EppAuthInfo</code> object with a ROID.
	 *
	 * @note the only type value is "pw", for password
	 */
	public EppAuthInfo( String type, String value, String roid )
	{
		this.type = type;
		this.value = value;
		this.roid = roid;
		if( this.roid == null )
		{
			this.roid = "";
		}
	}

	/**
	 * Gets the value associated with the authorization information
	 */
	public String getValue()
	{
		return this.value;
	}

	/**
	 * Gets the value associated with the authorization information
	 */
	public void setValue( String value )
	{
		this.value = value;
	}

	/**
	 * Gets the ROID of the authorization information
	 */
	public String getRoid()
	{
		return this.roid;
	}

	/**
	 * Sets the ROID of the authorization information
	 */
	public void setRoid( String roid )
	{
		this.roid = roid;
		if( this.roid == null )
		{
			this.roid = "";
		}
	}

	/**
	 * Gets the type of the authorization information
	 */
	public String getType()
	{
		return this.type;
	}

	/**
	 * Sets the type of the authorization information
	 */
	public void setType( String type )
	{
		this.type = type;
	}

	/**
 	 * Converts the <code>EppAuthInfo</code> object into an XML element
	 *
	 * @param doc the XML <code>Document</code> object
	 * @param tag the tag/element name for the <code>EppAuthInfo</code>
	 *            object
	 *
	 * @return an <code>Element</code> object
	 */
	public Element toXML( Document doc, String tag)
	{
		Element body = doc.createElement(tag);
		if( type != null )
		{
			body.setAttribute("type", type);
		}
		if( (roid != null) && (roid.length() > 0) )
		{
			body.setAttribute("roid", roid);
		}
		if( value != null )
		{
			body.appendChild(doc.createTextNode(value));
		}

		return body;
	}

	/**
	 * Converts an XML element into an <code>EppAuthInfo</code> object.
	 * The caller of this method must make sure that the root node is of
	 * the EPP AuthInfo type.
	 *
	 * @param root root node for an <code>EppAuthInfo</code> object
	 *             in XML format
	 *
	 * @return an <code>EppAuthInfo</code> object, or null if the node
	 *         is invalid
	 */
	public static EppEntity fromXML( Node root )
	{
		String type = ((Element) root).getAttribute("type");
		String roid = ((Element) root).getAttribute("roid");
		String value = EppUtil.getText(root);

		return new EppAuthInfo(type, value, roid);
	}

	public String toString()
	{
	   return toString("authInfo");
	}
}
