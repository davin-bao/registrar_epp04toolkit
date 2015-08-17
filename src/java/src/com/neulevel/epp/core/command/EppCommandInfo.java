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
 * This <code>EppCommandInfo</code> class implements EPP Command Info
 * entity.
 *
 * @author Ning Zhang ning.zhang@neustar.com
 * @version $Revision: 1.1 $ $Date: 2005/12/06 20:11:35 $
 */
abstract public class EppCommandInfo extends EppCommand
{
	/**
	 * Converts an XML element into an <code>EppCommandInfo</code> object.
	 * The caller of this method must make sure that the root node is of an
	 * EPP Command Info entity.
	 *
	 * @param root root node for an <code>EppCommandInfo</code> object
	 *             in XML format
	 *
	 * @return an <code>EppCommandInfo</code> object, or null if the node
	 *         is invalid
	 */
	public static EppEntity fromXML( Node root )
	{
		String command = root.getLocalName();
		NodeList list = root.getChildNodes();
		for( int i = 0; i < list.getLength(); i++ )
		{
			Node node = list.item(i);
			String prefix = node.getPrefix();
			String name = node.getLocalName();
			if( (prefix == null) || (name == null) )
			{
				continue;
			}
			if( name.equals(command) )
			{
				if( prefix.equals("contact") )
				{
					return EppCommandInfoContact.fromXML(node);
				}
				else if( prefix.equals("domain") )
				{
					return EppCommandInfoDomain.fromXML(node);
				}
				else if( prefix.equals("host") )
				{
					return EppCommandInfoHost.fromXML(node);
				}
				else if( prefix.equals("svcsub") )
				{
					return EppCommandInfoSvcsub.fromXML(node);
				}
			}
		}

		return null;
	}

	public String toString()
	{
		return toString("info");
	}
}
