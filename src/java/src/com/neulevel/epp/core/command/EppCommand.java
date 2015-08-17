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
 * This <code>EppCommand</code> class implements EPP Command entity.
 *
 * @author Ning Zhang ning.zhang@neustar.com
 * @version $Revision: 1.1 $ $Date: 2005/12/06 20:11:35 $
 */
abstract public class EppCommand extends EppEntity
{
	/**
	 * The EPP Credentials associated with the EPP Command (optional)
	 */
	protected EppCreds  creds;	// optional
	/**
	 * Any extension data associated with the EPP Command (optional)
	 */
	protected EppUnspec unspec;	// optional
	/**
	 * The client transaction id associated with the EPP Command
	 */
	protected String    clTRID;

	/**
	 * Gets command credentials
	 */
	public EppCreds getCreds()
	{
		return this.creds;
	}

	/**
	 * Sets command credentials
	 */
	public void setCreds( EppCreds creds )
	{
		this.creds = creds;
	}

	/**
	 * Gets optional unspecified object
	 */
	public EppUnspec getUnspec()
	{
		return this.unspec;
	}

	/**
	 * Sets optional unspecified object
	 */
	public void setUnspec( EppUnspec unspec )
	{
		this.unspec = unspec;
	}

	/**
	 * Gets transaction id from the registrar client
	 */
	public String getClientTransactionId()
	{
		return this.clTRID;
	}

	/**
	 * Sets transaction id from the registrar client
	 */
	public void setClientTransactionId( String xid )
	{
		this.clTRID = xid;
	}

	/**
	 * Converts the shared <code>EppCommand</code> components into an XML
	 * element. The command must be object specific commands such as
	 * create/delete/query, etc.
	 *
	 * @param doc the XML <code>Document</code> object
	 * @param command the tag/element name for the <code>EppCommand</code>
	 *                object
	 * @param element the <code>Element</code> associated with the command
	 *
	 * @return an <code>Element</code> object
	 */
	protected Element toXMLCommon( Document doc, String command, Element element )
	{
		return toXMLCommon(doc, command, element, command, null);
	}

	/**
	 * Converts the shared <code>EppCommand</code> components into an XML
	 * element. The command must be object specific commands such as
	 * create/delete/query, etc.
	 *
	 * @param doc the XML <code>Document</code> object
	 * @param command  the tag/element name for the <code>EppCommand</code>
	 *                 object
	 * @param element  the <code>Element</code> associated with the command
	 * @param attrList the <code>Attr</code> list associated with the
	 *		   command
	 *
	 * @return an <code>Element</code> object
	 */
	protected Element toXMLCommon( Document doc, String command, Element element, Vector attrList )
	{
		return toXMLCommon(doc, command, element, command, attrList);
	}

	/**
	 * Converts the shared <code>EppCommand</code> components into an XML
	 * element. The command must be object specific commands such as
	 * create/delete/query, etc.
	 *
	 * @param doc the XML <code>Document</code> object
	 * @param command the tag/element name for the <code>EppCommand</code>
	 *                object
	 * @param object the <code>EppObject</code> associated with the command.
	 *		 the type of the object should be either
	 *		 <code>EppEntity</code> or <code>Element</code>
	 *
	 * @return an <code>Element</code> object
	 */
	protected Element toXMLCommon( Document doc, String command, EppEntity object )
	{
		return toXMLCommon(doc, command, object, command, null);
	}

	/**
	 * Converts the shared <code>EppCommand</code> components into an XML
	 * element
	 *
	 * @param doc the XML <code>Document</code> object
	 * @param command the tag/element name for the <code>EppCommand</code>
	 *                object
	 * @param object   the <code>Object</code> associated with the command.
	 *		   the type of the object should be either
	 *		   <code>EppEntity</code> or <code>Element</code>
	 * @param tag      the tag indicating if the command is generic, such
	 *                 as login/logout
	 * @param attrList the <code>Attr</code> list associated with the
	 *		   command
	 *
	 * @return an <code>Element</code> object
	 */
	protected Element toXMLCommon( Document doc, String command, Object object, String tag, Vector attrList )
	{
		Element elm;
		Element epp = EppUtil.createElementNS(doc, "epp", null);
		Element body = doc.createElement("command");
		epp.appendChild(body);

		if( creds != null )
		{
			body.appendChild(creds.toXML(doc, "creds"));
		}

		elm = doc.createElement(command);
		if( attrList != null )
		{
			for( int i = 0; i < attrList.size(); i++ )
			{
				Object obj = attrList.get(i);
				if( obj instanceof Attr )
				{
					elm.setAttributeNode((Attr) obj);
				}
			}
		}
		if( object != null )
		{
			if( object instanceof EppEntity )
			{
				elm.appendChild(((EppEntity) object).toXML(doc, tag));
			}
			else if( object instanceof Element )
			{
				elm.appendChild((Element) object);
			}
		}
		body.appendChild(elm);

		if( unspec != null )
		{
			elm = unspec.toXML(doc, "unspec");
			body.appendChild(elm);
		}

		if( clTRID != null )
		{
			elm = doc.createElement("clTRID");
			elm.appendChild(doc.createTextNode(clTRID));
			body.appendChild(elm);
		}

		return epp;
	}

	/**
	 * Converts an XML element into an <code>EppCommand</code> object.
	 * The caller of this method must make sure that the root node is of
	 * an EPP Command entity.
	 *
	 * @param root root node for an <code>EppCommand</code> object in XML
	 *             format
	 *
	 * @return an <code>EppEntity</code> object, or null if the node
	 *         is invalid
	 */
	public static EppEntity fromXML( Node root )
	{
		EppCommand cmd = null;
		Node command = null;

		NodeList list = root.getChildNodes();
		for( int i = 0; i < list.getLength(); i++ )
		{
			Node node = list.item(i);
			String name = node.getLocalName();
			if( name == null )
			{
				continue;
			}
			if( name.equals("command") )
			{
				command = node;
				break;
			}
		}

		if( command == null )
		{
			return null;
		}

		list = command.getChildNodes();
		for( int i = 0; i < list.getLength(); i++ )
		{
			Node node = list.item(i);
			String name = node.getLocalName();
			if( name == null )
			{
				continue;
			}
			if( name.equals("login") )
			{
				cmd = (EppCommand) EppCommandLogin.fromXML(node);
			}
			else if( name.equals("logout") )
			{
				cmd = (EppCommand) EppCommandLogout.fromXML(node);
			}
			else if( name.equals("poll") )
			{
				cmd = (EppCommand) EppCommandPoll.fromXML(node);
			}
			else if( name.equals("create") )
			{
				cmd = (EppCommand) EppCommandCreate.fromXML(node);
			}
			else if( name.equals("delete") )
			{
				cmd = (EppCommand) EppCommandDelete.fromXML(node);
			}
			else if( name.equals("info") )
			{
				cmd = (EppCommand) EppCommandInfo.fromXML(node);
			}
			else if( name.equals("check") )
			{
				cmd = (EppCommand) EppCommandCheck.fromXML(node);
			}
			else if( name.equals("renew") )
			{
				cmd = (EppCommand) EppCommandRenew.fromXML(node);
			}
			else if( name.equals("transfer") )
			{
				cmd = (EppCommand) EppCommandTransfer.fromXML(node);
			}
			else if( name.equals("update") )
			{
				cmd = (EppCommand) EppCommandUpdate.fromXML(node);
			}
			/*
			 * other commands
			 */
		}
		if( cmd == null )
		{
			return null;
		}
		for( int i = 0; i < list.getLength(); i++ )
		{
			Node node = list.item(i);
			String name = node.getLocalName();
			if( name == null )
			{
				continue;
			}
			if( name.equals("creds") )
			{
				cmd.creds = (EppCreds) EppCreds.fromXML(node);
			}
			else if( name.equals("unspec") )
			{
				cmd.unspec = (EppUnspec) EppUnspec.fromXML(node);
			}
			else if( name.equals("clTRID") )
			{
				cmd.clTRID = EppUtil.getText(node);
			}
		}
		return cmd;
	}

	/**
	 * Creates an <code>EppCommandCreate</code> object. This is a
	 * convience method for creating an EPP Object in the registry.
	 *
	 * @param object object to be created in the registry
	 * @param xid    client transaction id associated with the operation
	 *
	 * @return an <code>EppCommandCreate</code> object, which could
	 *         be one of the subclass of <code>EppCommandCreate</code>
	 */
	public static EppCommandCreate create( EppObject object, String xid )
	{
		return new EppCommandCreate(object, xid);
	}

	/**
	 * Creates an <code>EppCommandCheck</code> object based on the
	 * object type.
	 *
	 * @param objectType the type of objects to be checked. The value
	 *                   must be defined in <code>EppObject</code>, as
	 *                   one of the followings:
	 *                   <UL><LI>EppObject.CONTACT</LI>
	 *                       <LI>EppObject.DOMAIN</LI>
	 *                       <LI>EppObject.HOST</LI>
	 *                       <LI>EppObject.SVCSUB</LI>
	 *                   </UL>
	 * @param xid client transaction id associated with the operation
	 *
	 * @return an <code>EppCommandCheck</code> object, which could
	 *         be one of the subclass of <code>EppCommandCheck</code>;
	 *         or null if the object type is invalid.
	 */
	public static EppCommandCheck check( int objectType, String xid )
	{
		EppCommandCheck cmd = null;

		switch( objectType )
		{
		case EppObject.CONTACT:
			cmd = new EppCommandCheckContact(xid);
			break;
		case EppObject.DOMAIN:
			cmd = new EppCommandCheckDomain(xid);
			break;
		case EppObject.HOST:
			cmd = new EppCommandCheckHost(xid);
			break;
		case EppObject.SVCSUB:
			cmd = new EppCommandCheckSvcsub(xid);
			break;
		default:
			break;
		}
		return cmd;
	}

	/**
	 * Creates an <code>EppCommandDelete</code> object based on the
	 * object type.
	 *
	 * @param objectType the type of object to be deleted. The value
	 *                   must be defined in <code>EppObject</code>, as
	 *                   one of the followings:
	 *                   <UL><LI>EppObject.CONTACT</LI>
	 *                       <LI>EppObject.DOMAIN</LI>
	 *                       <LI>EppObject.HOST</LI>
	 *                       <LI>EppObject.SVCSUB</LI>
	 *                   </UL>
	 * @param objectId the id associated with object to be deleted.
	 *                 The value is id for an EPP Contact object,
	 *                 domain name for an EPP Domain object, or host
	 *                 name for an EPP Host object, or service
	 *                 subscription id for an EPP Svcsub object
	 * @param xid client transaction id associated with the operation
	 *
	 * @return an <code>EppCommandDelete</code> object, which could
	 *         be one of the subclass of <code>EppCommandDelete</code>;
	 *         or null if the object type is invalid.
	 */
	public static EppCommandDelete delete( int objectType, String objectId, String xid )
	{
		EppCommandDelete cmd = null;

		switch( objectType )
		{
		case EppObject.CONTACT:
			cmd = new EppCommandDeleteContact(objectId, xid);
			break;
		case EppObject.DOMAIN:
			cmd = new EppCommandDeleteDomain(objectId, xid);
			break;
		case EppObject.HOST:
			cmd = new EppCommandDeleteHost(objectId, xid);
			break;
		case EppObject.SVCSUB:
			cmd = new EppCommandDeleteSvcsub(objectId, xid);
			break;
		default:
			break;
		}
		return cmd;
	}

	/**
	 * Creates an <code>EppCommandInfo</code> object based on the
	 * object type.
	 *
	 * @param objectType the type of object to be queried. The value
	 *                   must be defined in <code>EppObject</code>, as
	 *                   one of the followings:
	 *                   <UL><LI>EppObject.CONTACT</LI>
	 *                       <LI>EppObject.DOMAIN</LI>
	 *                       <LI>EppObject.HOST</LI>
	 *                       <LI>EppObject.SVCSUB</LI>
	 *                   </UL>
	 * @param objectId the id associated with object to be queried.
	 *                 The value is id for an EPP Contact object,
	 *                 domain name for an EPP Domain object, or host
	 *                 name for an EPP Host object, or service
	 *                 subscription id for an EPP Svcsub object
	 * @param xid client transaction id associated with the operation
	 *
	 * @return an <code>EppCommandInfo</code> object, which could
	 *         be one of the subclass of <code>EppCommandInfo</code>;
	 *         or null if the object type is invalid.
	 */
	public static EppCommandInfo info( int objectType, String objectId, String xid )
	{
		EppCommandInfo cmd = null;

		switch( objectType )
		{
		case EppObject.CONTACT:
			cmd = new EppCommandInfoContact(objectId, xid);
			break;
		case EppObject.DOMAIN:
			cmd = new EppCommandInfoDomain(objectId, xid);
			break;
		case EppObject.HOST:
			cmd = new EppCommandInfoHost(objectId, xid);
			break;
		case EppObject.SVCSUB:
			cmd = new EppCommandInfoSvcsub(objectId, xid);
			break;
		default:
			break;
		}
		return cmd;
	}

	/**
	 * Creates an <code>EppCommandUpdate</code> object based on the
	 * object type.
	 *
	 * @param objectType the type of object to be updated. The value
	 *                   must be defined in <code>EppObject</code>, as
	 *                   one of the followings:
	 *                   <UL><LI>EppObject.CONTACT</LI>
	 *                       <LI>EppObject.DOMAIN</LI>
	 *                       <LI>EppObject.HOST</LI>
	 *                       <LI>EppObject.SVCSUB</LI>
	 *                   </UL>
	 * @param objectId the id associated with object to be updated.
	 *                 The value is id for an EPP Contact object,
	 *                 domain name for an EPP Domain object, or host
	 *                 name for an EPP Host object, or service subscription
	 *		   id for an EPP Svcsub object
	 * @param xid client transaction id associated with the operation
	 *
	 * @return an <code>EppCommandUpdate</code> object, which could
	 *         be one of the subclass of <code>EppCommandUpdate</code>;
	 *         or null if the object type is invalid.
	 */
	public static EppCommandUpdate update( int objectType, String objectId, String xid )
	{
		EppCommandUpdate cmd = null;

		switch( objectType )
		{
		case EppObject.CONTACT:
			cmd = new EppCommandUpdateContact(objectId, xid);
			break;
		case EppObject.DOMAIN:
			cmd = new EppCommandUpdateDomain(objectId, xid);
			break;
		case EppObject.HOST:
			cmd = new EppCommandUpdateHost(objectId, xid);
			break;
		case EppObject.SVCSUB:
			cmd = new EppCommandUpdateSvcsub(objectId, xid);
			break;
		default:
			break;
		}
		return cmd;
	}

	/**
	 * Creates an <code>EppCommandTransfer</code> object based on the
	 * object type.
	 *
	 * @param objectType the type of object to be transferred. The value
	 *                   must be defined in <code>EppObject</code>, as
	 *                   one of the followings:
	 *                   <UL><LI>EppObject.CONTACT</LI>
	 *                       <LI>EppObject.DOMAIN</LI>
	 *                       <LI>EppObject.SVCSUB</LI>
	 *                   </UL>
	 * @param objectId the id associated with object to be transferred.
	 *                 The value is id for an EPP Contact object,
	 *                 domain name for an EPP Domain object, or service
	 *                 subscription id for an EPP Svcsub object
	 * @param xid client transaction id associated with the operation
	 *
	 * @return an <code>EppCommandTransfer</code> object, which could
	 *         be one of the subclass of <code>EppCommandTransfer</code>;
	 *         or null if the object type is invalid.
	 */
	public static EppCommandTransfer transfer( int objectType, String objectId, String xid )
	{
		EppCommandTransfer cmd = null;

		switch( objectType )
		{
		case EppObject.CONTACT:
			cmd = new EppCommandTransferContact(objectId, xid);
			break;
		case EppObject.DOMAIN:
			cmd = new EppCommandTransferDomain(objectId, xid);
			break;
		case EppObject.SVCSUB:
			cmd = new EppCommandTransferSvcsub(objectId, xid);
			break;
		default:
			break;
		}
		return cmd;
	}

	/**
	 * Creates an <code>EppCommandRenew</code> object based on the
	 * object type.
	 *
	 * @param objectType the type of object to be renewed. The value
	 *                   must be defined in <code>EppObject</code>, as
	 *                   one of the followings:
	 *                   <UL><LI>EppObject.DOMAIN</LI>
	 *                   <UL><LI>EppObject.SVCSUB</LI>
	 *                   </UL>
	 * @param objectId the id associated with object to be renewed.
	 *                 The value is the domain name for an EPP Domain
	 *                 object, or service subscription id for an EPP
	 *                 Svcsub object
	 * @param xid client transaction id associated with the operation
	 *
	 * @return an <code>EppCommandRenew</code> object, which could
	 *         be one of the subclass of <code>EppCommandRenew</code>;
	 *         or null if the object type is invalid.
	 *
	 * @note   As the current expiration date of the object is default
	 *         to the current date, and the default value of the new
	 *         registration period is specified by the registry, the
	 *         the caller to this method may have to use
	 *         <code>setCurrentExpiratin</code> and <code>setPeriod</code>
	 *         to change these default values.
	 */
	public static EppCommandRenew renew( int objectType, String objectId, String xid )
	{
		EppCommandRenew cmd = null;

		switch( objectType )
		{
		case EppObject.DOMAIN:
			cmd = new EppCommandRenewDomain(objectId, xid);
			break;
		case EppObject.SVCSUB:
			cmd = new EppCommandRenewSvcsub(objectId, xid);
			break;
		default:
			break;
		}
		return cmd;
	}
}
