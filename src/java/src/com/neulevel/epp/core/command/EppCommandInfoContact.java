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
package com.neulevel.epp.core.command;

import org.w3c.dom.*;
import com.neulevel.epp.core.*;

/**
 * This <code>EppCommandInfoContact</code> class implements EPP Command Info
 * entity for EPP Contact objects.
 *
 * @author Ning Zhang ning.zhang@neustar.com
 * @version $Revision: 1.1 $ $Date: 2005/12/06 20:11:35 $
 */
public class EppCommandInfoContact extends EppCommandInfo
{
	private String id;

	/**
	 * Creates an <code>EppCommandInfoContact</code> object for
	 * querying a contact object based on its id
	 */
	public EppCommandInfoContact( String id )
	{
		this.id = id;
	}

	/**
	 * Creates an <code>EppCommandInfoContact</code> object for
	 * querying a contact object based on its id, given a client
	 * transaction id assoicated with the operation
	 */
	public EppCommandInfoContact( String id, String xid )
	{
		this.id = id;
		this.clTRID = xid;
	}

	/**
	 * Gets the id of the contact object to be queried
	 */
	public String getId()
	{
		return this.id;
	}

	/**
	 * Sets the id of the contact object to be queried
	 */
	public void setId( String id )
	{
		this.id = id;
	}

	/**
	 * Converts the <code>EppCommandInfoContact</code> object into an XML
	 * element
	 *
	 * @param doc the XML <code>Document</code> object
	 * @param tag the tag/element name for the
	 *            <code>EppCommandInfoContact</code> object
	 *
	 * @return an <code>Element</code> object
	 */
	public Element toXML( Document doc, String tag )
	{
		Element elm;
		Element body = EppUtil.createElementNS(doc, "contact", tag);

		if( id != null )
		{
			elm = doc.createElement("id");
			elm.appendChild(doc.createTextNode(id));
			body.appendChild(elm);
		}

		return toXMLCommon(doc, tag, body);
	}

	/**
	 * Converts an XML element into an <code>EppCommandInfoContact</code>
	 * object. The caller of this method must make sure that the root node
	 * is of an EPP Command Info entity for EPP contact object.
	 *
	 * @param root root node for an <code>EppCommandInfoContact</code>
	 *             object in XML format
	 *
	 * @return an <code>EppCommandInfoContact</code> object, or null
	 *         if the node is invalid
	 */
	public static EppEntity fromXML( Node root )
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
			if( name.equals("id") )
			{
				String id = EppUtil.getText(node);
				return new EppCommandInfoContact(id);
			}
		}

		return null;
	}
}
