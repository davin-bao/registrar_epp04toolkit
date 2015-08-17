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
#include "EppCommand.hpp"
#include "EppCommandLogin.hpp"
#include "EppCommandLogout.hpp"
#include "EppCommandPoll.hpp"
#include "EppCommandCreate.hpp"
#include "EppCommandDelete.hpp"
#include "EppCommandDeleteContact.hpp"
#include "EppCommandDeleteDomain.hpp"
#include "EppCommandDeleteHost.hpp"
#include "EppCommandDeleteSvcsub.hpp"
#include "EppCommandInfo.hpp"
#include "EppCommandInfoContact.hpp"
#include "EppCommandInfoDomain.hpp"
#include "EppCommandInfoHost.hpp"
#include "EppCommandInfoSvcsub.hpp"
#include "EppCommandCheck.hpp"
#include "EppCommandCheckContact.hpp"
#include "EppCommandCheckDomain.hpp"
#include "EppCommandCheckHost.hpp"
#include "EppCommandCheckSvcsub.hpp"
#include "EppCommandRenew.hpp"
#include "EppCommandRenewDomain.hpp"
#include "EppCommandRenewSvcsub.hpp"
#include "EppCommandTransfer.hpp"
#include "EppCommandTransferContact.hpp"
#include "EppCommandTransferDomain.hpp"
#include "EppCommandTransferSvcsub.hpp"
#include "EppCommandUpdate.hpp"
#include "EppCommandUpdateContact.hpp"
#include "EppCommandUpdateDomain.hpp"
#include "EppCommandUpdateHost.hpp"
#include "EppCommandUpdateSvcsub.hpp"
#include "EppUtil.hpp"

EppCommand::~EppCommand()
{
	if( this->creds != null )
	{
		delete this->creds;
		this->creds = null;
	}
	if( this->unspec != null )
	{
		delete this->unspec;
		this->unspec = null;
	}
}

void EppCommand::setCreds( EppCreds& creds )
{
	if( this->creds != null )
	{
		delete this->creds;
	}
	this->creds = new EppCreds(creds.getClientId(),
				   creds.getPassword(),
				   creds.getNewPassword());
	EppCredsOptions * opt = creds.getOptions();
	if( opt != null )
	{
		this->creds->setOptions(*opt);
	}
}

DOM_Element EppCommand::toXMLCommon( DOM_Document& doc, const DOMString command, DOM_Element& element )
{
	return toXMLCommon(doc, command, element, (EppEntity *) null, command, (ValueVectorOf<DOM_Attr> *) null);
}

DOM_Element EppCommand::toXMLCommon( DOM_Document& doc, const DOMString command, DOM_Element& element, ValueVectorOf<DOM_Attr> * attrList )
{
	return toXMLCommon(doc, command, element, null, command, attrList);
}

DOM_Element EppCommand::toXMLCommon( DOM_Document& doc, const DOMString command, EppEntity * object )
{
	DOM_Element element;
	return toXMLCommon(doc, command, element, object, command, (ValueVectorOf<DOM_Attr> *) null);
}

DOM_Element EppCommand::toXMLCommon( DOM_Document& doc, const DOMString command, DOM_Element& element, EppEntity * object, const DOMString tag, ValueVectorOf<DOM_Attr> * attrList )
{
	DOM_Element elm;
	DOM_Element epp = EppUtil::createElementNS(doc, "epp", null);
	DOM_Element body = doc.createElement("command");
	epp.appendChild(body);

	if( creds != null )
	{
		body.appendChild(creds->toXML(doc, "creds"));
	}

	elm = doc.createElement(command);
	if( attrList != null )
	{
		for( unsigned int i = 0; i < attrList->size(); i++ )
		{
			DOM_Attr obj = attrList->elementAt(i);
			elm.setAttributeNode(obj);
		}
	}
	if( object != null )
	{
		elm.appendChild(object->toXML(doc, tag));
	}
	else if( element != null )
	{
		elm.appendChild(element);
	}
	body.appendChild(elm);

	if( unspec != null )
	{
		elm = unspec->toXML(doc, "unspec");
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

EppCommand * EppCommand::fromXML( const DOM_Node& root )
{
	unsigned int i;
	EppCommand * cmd = null;
	DOM_Node command;
	bool found = false;

	DOM_NodeList list = root.getChildNodes();
	for( i = 0; i < list.getLength(); i++ )
	{
		DOM_Node node = list.item(i);
		DOMString name = node.getLocalName();
		if( name == null )
		{
			name = node.getNodeName();
		}
		if( name == null )
		{
			continue;
		}
		if( name.equals("command") )
		{
			command = node;
			found = true;
			break;
		}
	}

	if( found == false )
	{
		return null;
	}

	list = command.getChildNodes();
	for( i = 0; i < list.getLength(); i++ )
	{
		DOM_Node node = list.item(i);
		DOMString name = node.getLocalName();
		if( name == null )
		{
			name = node.getNodeName();
		}
		if( name == null )
		{
			continue;
		}
		if( name.equals("login") )
		{
			cmd = EppCommandLogin::fromXML(node);
		}
		else if( name.equals("logout") )
		{
			cmd = EppCommandLogout::fromXML(node);
		}
		else if( name.equals("poll") )
		{
			cmd = EppCommandPoll::fromXML(node);
		}
		else if( name.equals("create") )
		{
			cmd = EppCommandCreate::fromXML(node);
		}
		else if( name.equals("delete") )
		{
			cmd = EppCommandDelete::fromXML(node);
		}
		else if( name.equals("info") )
		{
			cmd = EppCommandInfo::fromXML(node);
		}
		else if( name.equals("check") )
		{
			cmd = EppCommandCheck::fromXML(node);
		}
		else if( name.equals("renew") )
		{
			cmd = EppCommandRenew::fromXML(node);
		}
		else if( name.equals("transfer") )
		{
			cmd = EppCommandTransfer::fromXML(node);
		}
		else if( name.equals("update") )
		{
			cmd = EppCommandUpdate::fromXML(node);
		}
		/*
		 * other commands
		 */
		if( cmd != null )
		{
			break;
		}
	}
	if( cmd == null )
	{
		return null;
	}
	for( i = 0; i < list.getLength(); i++ )
	{
		DOM_Node node = list.item(i);
		DOMString name = node.getLocalName();
		if( name == null )
		{
			name = node.getNodeName();
		}
		if( name == null )
		{
			continue;
		}
		if( name.equals("creds") )
		{
			if( cmd->creds == null )
			{
				cmd->creds = EppCreds::fromXML(node);
			}
		}
		else if( name.equals("unspec") )
		{
			if( cmd->unspec == null )
			{
				cmd->unspec = EppUnspec::fromXML(node);
			}
		}
		else if( name.equals("clTRID") )
		{
			cmd->clTRID = EppUtil::getText(node);
		}
	}

	return cmd;
}

EppCommandCreate EppCommand::create( EppObject * object, DOMString xid )
{
	return EppCommandCreate(object, xid);
}

EppCommandCheck * EppCommand::check( int objectType, DOMString xid )
{
	EppCommandCheck * cmd = null;

	if( objectType == EppObject::CONTACT )
	{
		cmd = new EppCommandCheckContact(xid);
	}
	else if( objectType == EppObject::DOMAIN )
	{
		cmd = new EppCommandCheckDomain(xid);
	}
	else if( objectType == EppObject::HOST )
	{
		cmd = new EppCommandCheckHost(xid);
	}
	else if( objectType == EppObject::SVCSUB )
	{
		cmd = new EppCommandCheckSvcsub(xid);
	}
	return cmd;
}

EppCommandDelete * EppCommand::remove( int objectType, DOMString objectId, DOMString xid )
{
	EppCommandDelete * cmd = null;

	if( objectType == EppObject::CONTACT )
	{
		cmd = new EppCommandDeleteContact(objectId, xid);
	}
	else if( objectType == EppObject::DOMAIN )
	{
		cmd = new EppCommandDeleteDomain(objectId, xid);
	}
	else if( objectType == EppObject::HOST )
	{
		cmd = new EppCommandDeleteHost(objectId, xid);
	}
	else if( objectType == EppObject::SVCSUB )
	{
		cmd = new EppCommandDeleteSvcsub(objectId, xid);
	}
	return cmd;
}

EppCommandInfo * EppCommand::info( int objectType, DOMString objectId, DOMString xid )
{
	EppCommandInfo * cmd = null;

	if( objectType == EppObject::CONTACT )
	{
		cmd = new EppCommandInfoContact(objectId, xid);
	}
	else if( objectType == EppObject::DOMAIN )
	{
		cmd = new EppCommandInfoDomain(objectId, xid);
	}
	else if( objectType == EppObject::HOST )
	{
		cmd = new EppCommandInfoHost(objectId, xid);
	}
	else if( objectType == EppObject::SVCSUB )
	{
		cmd = new EppCommandInfoSvcsub(objectId, xid);
	}
	return cmd;
}

EppCommandUpdate * EppCommand::update( int objectType, DOMString objectId, DOMString xid )
{
	EppCommandUpdate * cmd = null;

	if( objectType == EppObject::CONTACT )
	{
		cmd = new EppCommandUpdateContact(objectId, xid);
	}
	else if( objectType == EppObject::DOMAIN )
	{
		cmd = new EppCommandUpdateDomain(objectId, xid);
	}
	else if( objectType == EppObject::HOST )
	{
		cmd = new EppCommandUpdateHost(objectId, xid);
	}
	else if( objectType == EppObject::SVCSUB )
	{
		cmd = new EppCommandUpdateSvcsub(objectId, xid);
	}
	return cmd;
}

EppCommandTransfer * EppCommand::transfer( int objectType, DOMString objectId, DOMString xid )
{
	EppCommandTransfer * cmd = null;

	if( objectType == EppObject::CONTACT )
	{
		cmd = new EppCommandTransferContact(objectId, xid);
	}
	else if( objectType == EppObject::DOMAIN )
	{
		cmd = new EppCommandTransferDomain(objectId, xid);
	}
	else if( objectType == EppObject::SVCSUB )
	{
		cmd = new EppCommandTransferSvcsub(objectId, xid);
	}
	return cmd;
}

EppCommandRenew * EppCommand::renew( int objectType, DOMString objectId, DOMString xid )
{
	EppCommandRenew * cmd = null;

	if( objectType == EppObject::DOMAIN )
	{
		cmd = new EppCommandRenewDomain(objectId, xid);
	}
	else if( objectType == EppObject::SVCSUB )
	{
		cmd = new EppCommandRenewSvcsub(objectId, xid);
	}
	return cmd;
}
