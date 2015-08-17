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

import java.util.*;
import org.w3c.dom.*;
import com.neulevel.epp.core.*;

/**
 * This <code>EppCommandUpdate</code> class implements EPP Command Update
 * entity.
 *
 * @author Ning Zhang ning.zhang@neustar.com
 * @version $Revision: 1.1 $ $Date: 2005/12/06 20:11:35 $
 */
abstract public class EppCommandUpdate extends EppCommand
{
	protected Vector statusAdded   = new Vector();
	protected Vector statusRemoved = new Vector();

	/**
	 * Gets the list of new status to be added for the EPP object
	 */
	public Vector getAddedStatus()
	{
		return this.statusAdded;
	}

	/**
	 * Adds a new status for the EPP object
	 */
	public void addStatus( String status )
	{
		this.statusAdded.addElement(new EppStatus(status));
	}

	/*
	 * Adds a new status for the EPP object
	 */
	public void addStatus( EppStatus status )
	{
		this.statusAdded.addElement(status);
	}

	/**
	 * Gets the list of old status to be removed for the EPP object
	 */
	public Vector getRemovedStatus()
	{
		return this.statusRemoved;
	}

	/*
	 * Removes an old status for the EPP object
	 */
	public void removeStatus( String status )
	{
		this.statusRemoved.addElement(new EppStatus(status));
	}

	/*
	 * Removes an old status for the EPP object
	 */
	public void removeStatus( EppStatus status )
	{
		this.statusRemoved.addElement(status);
	}

	/**
	 * Converts an XML element into an <code>EppCommandUpdate</code>
	 * object. The caller of this method must make sure that the root
	 * node is of an EPP Command Update entity.
	 *
	 * @param root root node for an <code>EppCommandUpdate</code> object
	 *             in XML format
	 *
	 * @return an <code>EppCommandUpdate</code> object, or null if the
	 *         node is invalid
	 */
	public static EppEntity fromXML( Node root )
	{
		String command = root.getLocalName();
		EppCommandUpdate cmd = null;

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
					return EppCommandUpdateContact.fromXML(node);
				}
				else if( prefix.equals("domain") )
				{
					return EppCommandUpdateDomain.fromXML(node);
				}
				else if( prefix.equals("host") )
				{
					return EppCommandUpdateHost.fromXML(node);
				}
				else if( prefix.equals("svcsub") )
				{
					return EppCommandUpdateSvcsub.fromXML(node);
				}
				break;
			}
		}
			
		return null;
	}

	/**
	 * Converts a list of EPP Status objects into XML
	 *
	 * @param doc  the XML <code>Document</code> object
	 * @param body the XML <code>Element</code> object to which the list
	 *             of EPP Status objects is appended
	 * @param list the list of EPP Status objects to be converted
	 */
	protected void statusToXML( Document doc, Element body, Vector list )
	{
		Element elm;
		if( list != null )
		{
			for( int i = 0; i < list.size(); i++ )
			{
				Object obj = list.elementAt(i);
				if( obj instanceof EppStatus )
				{
					EppStatus status = (EppStatus) obj;
					elm = status.toXML(doc, "status");
					body.appendChild(elm);
				}
			}
		}
	}

	/**
	 * Converts a list of EPP Status objects from XML
	 *
	 * @param root the XML <code>Node</code> object containing the list
	 *             of EPP Status objects
	 * @param statusList the list of EPP Status objects to be stored
	 */
	protected void statusFromXML( Node root, Vector statusList )
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
			if( name.equals("status") )
			{
				EppStatus status = (EppStatus) EppStatus.fromXML(node);
				statusList.addElement(status);
			}
		}
	}

	public String toString()
	{
		return toString("update");
	}
}
