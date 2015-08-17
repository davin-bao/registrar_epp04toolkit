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
package com.neulevel.epp.core.response;

import java.util.*;
import org.w3c.dom.*;
import com.neulevel.epp.core.*;

/**
 * This <code>EppResponseDataCheck</code> class implements EPP Response
 * Data entity for EPP Command Check.
 *
 * @author Ning Zhang ning.zhang@neustar.com
 * @version $Revision: 1.1 $ $Date: 2005/12/06 20:11:35 $
 */
abstract public class EppResponseDataCheck extends EppResponseData
{
	/**
	 * Status for checking the existance of an object in the registry
	 */
	public static final String UNKNOWN   = " ";
	/**
	 * Status for checking the existance of an object in the registry
	 */
	public static final String FOUND     = "+";
	/**
	 * Status for checking the existance of an object in the registry
	 */
	public static final String NOT_FOUND = "-";

	/**
	 * A <code>HashMap</code> storing key and value pairs
	 */
	protected HashMap hashMap = new HashMap();

	/**
	 * Gets the <code>HashMap</code> associated with the result data of
	 * the check command
	 */
	public HashMap getHashMap()
	{
		return this.hashMap;
	}

	/**
	 * Adds an entry into the <code>HashMap</code> for indicating if the
	 * object exists in the registry or not
	 *
	 * @param id   The Id associated with an EPP object, ROID for a contact
	 *             object, domain name for a domain object, host name for
	 *             a host object
	 * @param flag one of the <code>FOUND</code>, <code>NOT_FOUND</code>,
	 *             <code>UNKNWON</code>, indicating if the object exists in
	 *             the registry or not, or the existance is unknown
	 */
	public void add( String id, String flag )
	{
		this.hashMap.put(id, flag);
	}

	/**
	 * Checks if an object id is in the <code>HashMap</code>
	 *
	 * @return one of the <code>FOUND</code>, <code>NOT_FOUND</code>,
	 *         <code>UNKNWON</code>
	 */
	public String check( String id )
	{
		Object obj = this.hashMap.get(id);
		if( (obj != null) && (obj instanceof String) )
		{
			return (String) obj;
		}
		return UNKNOWN;
	}

	/**
	 * Converts shared <code>EppResponseDataCheck</code> component into
	 * XML elements
	 *
	 * @param doc the XML <code>Document</code> object
	 * @param body the XML <code>Element</code> to be attached
	 */
	protected void toXMLCommon( Document doc, Element body )
	{
		Set keyset = this.hashMap.keySet();
		if( keyset == null )
		{
			return;
		}
		Iterator list = keyset.iterator();
		if( list == null )
		{
			return;
		}
		Element elm;
		while( list.hasNext() )
		{
			Object o = list.next();
			Object x = this.hashMap.get(o);
			if(    (o != null) && (o instanceof String)
			    && (x != null) && (x instanceof String) )
			{
				elm = doc.createElement("cd");
				elm.setAttribute("x", (String) x);
				elm.appendChild(doc.createTextNode((String) o));
				body.appendChild(elm);
			}
		}

		return;
	}

	/**
	 * Converts shared <code>EppResponseDataCheck</code> components from
	 * XML format.
	 * 
	 * @param root root node for the list of shared components
	 */
	protected void fromXMLCommon( Node root )
	{
		NodeList list = root.getChildNodes();
		for( int i = 0; i < list.getLength(); i++ )
		{
			Node node = list.item(i);
			String name = node.getLocalName();
			if( name == null )
			{
				continue;
			}
			if( name.equals("cd") )
			{
				String id = EppUtil.getText(node);
				String cd = ((Element) node).getAttribute("x");
				if( (cd != null) && cd.equals(FOUND) )
				{
					this.add(id, FOUND);
				}
				else if( (cd != null) && cd.equals(NOT_FOUND) )
				{
					this.add(id, NOT_FOUND);
				}
				else
				{
					this.add(id, UNKNOWN);
				}
			}
		}
	}
}
