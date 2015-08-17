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
 * This <code>EppCommandLogin</code> class implements EPP Command Login
 * entity.
 *
 * @author Ning Zhang ning.zhang@neustar.com
 * @version $Revision: 1.1 $ $Date: 2005/12/06 20:11:35 $
 */
public class EppCommandLogin extends EppCommand
{
	class EppLoginMenu extends EppServiceMenu
	{
		public EppLoginMenu( EppServiceMenu serviceMenu )
		{
			this.version = null;
			this.lang = null;
			this.svc = serviceMenu.getService();
			this.unspec = serviceMenu.getUnspec();
		}
	}

	private EppLoginMenu svcs;

	/**
	 * Creates an <code>EppCommandLogin</code> object
	 *
	 * @param serviceMenu the menu of services to be supported
	 */
	public EppCommandLogin( EppServiceMenu serviceMenu )
	{
		this.svcs = new EppLoginMenu(serviceMenu);
	}

	/**
	 * Gets the menu of services to be supported
	 */
	public EppServiceMenu getServiceMenu()
	{
		return this.svcs;
	}

	/**
	 * Sets the menu of services to be supported
	 */
	public void setServiceMenu( EppServiceMenu serviceMenu )
	{
		this.svcs = new EppLoginMenu(serviceMenu);
	}

	/**
	 * Converts the <code>EppCommandLogin</code> object into an XML element
	 *
	 * @param doc the XML <code>Document</code> object
	 * @param tag the tag/element name for the <code>EppCommandLogin</code>
	 *            object
	 *
	 * @return an <code>Element</code> object
	 */
	public Element toXML( Document doc, String tag )
	{
		return toXMLCommon(doc, tag, svcs, "svcs", null);
	}

	/**
	 * Converts an XML element into an <code>EppCommandLogin</code> object.
	 * The caller of this method must make sure that the root node is of an
	 * EPP Command Create entity.
	 *
	 * @param root root node for an <code>EppCommandLogin</code> object
	 *             in XML format
	 *
	 * @return an <code>EppCommandLogin</code> object, or null if the node
	 *         is invalid
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
			if( name.equals("svcs") )
			{
				EppServiceMenu menu = (EppServiceMenu)
						EppServiceMenu.fromXML(node);
				if( menu != null )
				{
					return new EppCommandLogin(menu);
				}
			}
		}

		return null;
	}

	public String toString()
	{
		return toString("login");
	}
}
