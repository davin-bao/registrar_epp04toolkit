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
 * This <code>EppCommandUpdateContact</code> class implements EPP Command Update
 * entity for EPP Contact objects.
 *
 * @author Ning Zhang ning.zhang@neustar.com
 * @version $Revision: 1.1 $ $Date: 2005/12/06 20:11:35 $
 */
public class EppCommandUpdateContact extends EppCommandUpdate
{
	private String         id;
	private EppContactData newAscii;
	private EppContactData newI15d;
	private EppE164        newVoice;
	private EppE164        newFax;
	private String         newEmail;
	private EppAuthInfo    newAuthInfo;

	/**
	 * Creates an <code>EppCommandUpdateContact</code> given the id
	 * of the contact
	 */
	public EppCommandUpdateContact( String id )
	{
		this(id, null);
	}

	/**
	 * Creates an <code>EppCommandUpdateContact</code> given the id
	 * of the contact and a client transaction id
	 */
	public EppCommandUpdateContact( String id, String xid )
	{
		this.id = id;
		this.clTRID = xid;
	}

	/**
	 * Gets the id of the contact to be updated
	 */
	public String getId()
	{
		return this.id;
	}

	/**
	 * Sets the id of the contact to be updated
	 */
	public void setId( String id )
	{
		this.id= id;
	}

	/**
	 * Gets the new contact data in ascii encoding, or null if not changed
	 */
	public EppContactData getNewAscii()
	{
		return this.newAscii;
	}

	/**
	 * Sets the new contact data in ascii encoding, or null if not changed
	 */
	public void setNewAscii( EppContactData ascii )
	{
		this.newAscii = ascii;
	}

	/**
	 * Gets the new contact data in native encoding, or null if not changed
	 */
	public EppContactData getNewI15d()
	{
		return this.newI15d;
	}

	/**
	 * Sets the new contact data in ascii encoding, or null if not changed
	 */
	public void setNewI15d( EppContactData i15d )
	{
		this.newI15d = i15d;
	}

	/**
	 * Gets the new voice phone number
	 */
	public EppE164 getNewVoice()
	{
		return this.newVoice;
	}

	/**
	 * Sets the new voice phone number
	 */
	public void setNewVoice( String voice )
	{
		this.newVoice = new EppE164(voice);
	}

	/**
	 * Sets the new voice phone number
	 */
	public void setNewVoice( String voice, String ext )
	{
		this.newVoice = new EppE164(voice, ext);
	}

	/**
	 * Sets the new voice phone number
	 */
	public void setNewVoice( EppE164 voice )
	{
		this.newVoice = voice;
	}

	/**
	 * Gets the new fax number
	 */
	public EppE164 getNewFax()
	{
		return this.newFax;
	}

	/**
	 * Sets the new fax number
	 */
	public void setNewFax( String fax )
	{
		this.newFax = new EppE164(fax);
	}

	/**
	 * Sets the new fax number
	 */
	public void setNewFax( String fax, String ext )
	{
		this.newFax = new EppE164(fax, ext);
	}

	/**
	 * Sets the new fax number
	 */
	public void setNewFax( EppE164 fax )
	{
		this.newFax = fax;
	}

	/**
	 * Gets the new email address of the contact, or null if not changed
	 */
	public String getNewEmail()
	{
		return this.newEmail;
	}

	/**
	 * Sets the new email address of the contact, or null if not changed
	 */
	public void setNewEmail( String email )
	{
		this.newEmail = email;
	}

	/*
	 * Gets the new authorization information for the contact, or null if
	 * the authorization information of the domain is not to be changed
	 */
	public EppAuthInfo getNewAuthInfo()
	{
		return this.newAuthInfo;
	}

	/**
	 * Sets the new authorization information for the contact if it needs
	 * to be changed
	 */
	public void setNewAuthInfo( EppAuthInfo authInfo )
	{
		this.newAuthInfo = authInfo;
	}

	/**
	 * Converts the <code>EppCommandUpdateContact</code> object into 
	 * an XML element
	 *
	 * @param doc the XML <code>Document</code> object
	 * @param tag the tag/element name for the 
	 *            <code>EppCommandUpdateContact</code> object
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
		if( statusAdded.size() > 0 )
		{
			elm = doc.createElement("add");
			statusToXML(doc, elm, statusAdded);
			body.appendChild(elm);
		}
		if( statusRemoved.size() > 0 )
		{
			elm = doc.createElement("rem");
			statusToXML(doc, elm, statusRemoved);
			body.appendChild(elm);
		}
		if(    (newAscii != null) || (newI15d != null)
		    || (newVoice != null) || (newFax != null)
		    || (newEmail != null) || (newAuthInfo != null) )
		{
			elm = doc.createElement("chg");
			if( newAscii != null )
			{
				elm.appendChild(newAscii.toXML(doc, "ascii"));
			}
			if( newI15d != null )
			{
				elm.appendChild(newI15d.toXML(doc, "i15d"));
			}
			if( newVoice != null )
			{
				elm.appendChild(newVoice.toXML(doc, "voice"));
			}
			if( newFax != null )
			{
				elm.appendChild(newFax.toXML(doc, "fax"));
			}
			if( newEmail != null )
			{
				Element email = doc.createElement("email");
				email.appendChild(doc.createTextNode(newEmail));
				elm.appendChild(email);
			}
			if( newAuthInfo != null )
			{
				elm.appendChild(newAuthInfo.toXML(doc, "authInfo"));
			}
			body.appendChild(elm);
		}

		return toXMLCommon(doc, tag, body);
	}

	/**
	 * Converts an XML element into an <code>EppCommandUpdateDomain</code>
	 * object. The caller of this method must make sure that the root node
	 * is of an EPP Command Update entity for an EPP Contact object.
	 *
	 * @param root root node for an <code>EppCommandUpdateDomain</code>
	 *             object in XML format
	 *
	 * @return an <code>EppCommandUpdateDomain</code> object, or null
	 *         if the node is invalid
	 */
	public static EppEntity fromXML( Node root )
	{
		EppCommandUpdateContact cmd = null;
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
				cmd = new EppCommandUpdateContact(id);
			}
			else if( name.equals("add") )
			{
				if( cmd != null )
				{
					cmd.statusFromXML(node, cmd.statusAdded);
				}
			}
			else if( name.equals("rem") )
			{
				if( cmd != null )
				{
					cmd.statusFromXML(node, cmd.statusRemoved);
				}
			}
			else if( name.equals("chg") )
			{
				if( cmd != null )
				{
					cmd.addNewStuff(node);
				}
			}
		}

		return cmd;
	}

	/**
	 * Adds elements included in the &lt;chg&gt tag of the update command
	 * for a contact object
	 *
	 * @param root the root <code>Node</code> of the &lt;chg&gt; tag
	 */
	private void addNewStuff( Node root )
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
			if( name.equals("ascii") )
			{
				EppContactData ascii = (EppContactData) EppContactData.fromXML(node);
				setNewAscii(ascii);
			}
			else if( name.equals("i15d") )
			{
				EppContactData i15d = (EppContactData) EppContactData.fromXML(node);
				setNewI15d(i15d);
			}
			else if( name.equals("voice") )
			{
				EppE164 voice = (EppE164) EppE164.fromXML(node);
				setNewVoice(voice);
			}
			else if( name.equals("fax") )
			{
				EppE164 fax = (EppE164) EppE164.fromXML(node);
				setNewFax(fax);
			}
			else if( name.equals("email") )
			{
				String email = EppUtil.getText(node);
				setNewEmail(email);
			}
			else if( name.equals("authInfo") )
			{
				EppAuthInfo authInfo = (EppAuthInfo) EppAuthInfo.fromXML(node);
				setNewAuthInfo(authInfo);
			}
		}
	}
}
