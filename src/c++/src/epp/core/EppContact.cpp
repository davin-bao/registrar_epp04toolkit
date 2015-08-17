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
#include "EppContact.hpp"
#include "EppUtil.hpp"

const char * EppContact::STATUS_CLIENT_DELETE_PROHIBITED = "clientDeleteProhibited";
const char * EppContact::STATUS_CLIENT_TRANSFER_PROHIBITED = "clientTransferProhibited";
const char * EppContact::STATUS_CLIENT_UPDATE_PROHIBITED = "clientUpdateProhibited";
const char * EppContact::STATUS_LINKED = "linked";
const char * EppContact::STATUS_OK = "ok";
const char * EppContact::STATUS_PENDING_DELETE = "pendingDelete";
const char * EppContact::STATUS_PENDING_TRANSFER = "pendingTransfer";
const char * EppContact::STATUS_SERVER_DELETE_PROHIBITED = "serverDeleteProhibited";
const char * EppContact::STATUS_SERVER_TRANSFER_PROHIBITED = "serverTransferProhibited";
const char * EppContact::STATUS_SERVER_UPDATE_PROHIBITED = "serverUpdateProhibited";

DOM_Element EppContact::toXML( DOM_Document& doc, const DOMString& tag )
{
	DOM_Element elm;
	DOM_Element body = EppUtil::createElementNS(doc, "contact", tag);

	if( id != null )
	{
		elm = doc.createElement("id");
		elm.appendChild(doc.createTextNode(id));
		body.appendChild(elm);
	}
	if( roid != null )
	{
		elm = doc.createElement("roid");
		elm.appendChild(doc.createTextNode(roid));
		body.appendChild(elm);
	}
	if( status != null )
	{
		for( unsigned int i = 0; i < status->size(); i++ )
		{
			EppStatus s = status->elementAt(i);
			body.appendChild(s.toXML(doc, "status"));
		}
	}
	if( ascii != null )
	{
		body.appendChild(ascii->toXML(doc, "ascii"));
	}
	if( i15d != null )
	{
		body.appendChild(i15d->toXML(doc, "i15d"));
	}
	if( voice != null )
	{
		body.appendChild(voice->toXML(doc, "voice"));
	}
	if( fax != null )
	{
		body.appendChild(fax->toXML(doc, "fax"));
	}
	if( email != null )
	{
		elm = doc.createElement("email");
		elm.appendChild(doc.createTextNode(email));
		body.appendChild(elm);
	}

	toXMLCommon(doc, body);

	return body;
}

EppContact * EppContact::fromXML( const DOM_Node& root )
{
	EppContact * contact = new EppContact();
	DOM_NodeList list = root.getChildNodes();
	for( unsigned int i = 0; i < list.getLength(); i++ )
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
		if( name.substringData(0, 8).equals("contact:") )
		{
			name = name.substringData(8, name.length() - 8);
		}
		if( name.equals("id") )
		{
			contact->id = EppUtil::getText(node);
		}
		else if( name.equals("ascii") )
		{
			contact->ascii = EppContactData::fromXML(node);
		}
		else if( name.equals("i15d") )
		{
			contact->i15d = EppContactData::fromXML(node);
		}
		else if( name.equals("voice") )
		{
			contact->voice = EppE164::fromXML(node);
		}
		else if( name.equals("fax") )
		{
			contact->fax = EppE164::fromXML(node);
		}
		else if( name.equals("email") )
		{
			contact->email = EppUtil::getText(node);
		}
		else
		{
			contact->fromXMLCommon(node, name);
		}
	}

	return contact;
}
