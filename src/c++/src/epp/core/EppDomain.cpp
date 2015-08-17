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
#include "EppDomain.hpp"
#include "EppUtil.hpp"

const char * EppDomain::CONTACT_TYPE_ADMIN = "admin";
const char * EppDomain::CONTACT_TYPE_BILLING = "billing";
const char * EppDomain::CONTACT_TYPE_TECH = "tech";

const char * EppDomain::STATUS_CLIENT_DELETE_PROHIBITED = "clientDeleteProhibited";
const char * EppDomain::STATUS_CLIENT_HOLD = "clientHold";
const char * EppDomain::STATUS_CLIENT_RENEW_PROHIBITED = "clientRenewProhibited";
const char * EppDomain::STATUS_CLIENT_TRANSFER_PROHIBITED = "clientTransferProhibited";
const char * EppDomain::STATUS_CLIENT_UPDATE_PROHIBITED = "clientUpdateProhibited";
const char * EppDomain::STATUS_INACTIVE = "inactive";
const char * EppDomain::STATUS_OK = "ok";
const char * EppDomain::STATUS_PENDING_DELETE = "pendingDelete";
const char * EppDomain::STATUS_PENDING_TRANSFER = "pendingTransfer";
const char * EppDomain::STATUS_PENDING_VERIFICATION = "pendingVerification";
const char * EppDomain::STATUS_SERVER_DELETE_PROHIBITED = "serverDeleteProhibited";
const char * EppDomain::STATUS_SERVER_HOLD = "serverHold";
const char * EppDomain::STATUS_SERVER_RENEW_PROHIBITED = "serverRenewProhibited";
const char * EppDomain::STATUS_SERVER_TRANSFER_PROHIBITED = "serverTransferProhibited";
const char * EppDomain::STATUS_SERVER_UPDATE_PROHIBITED = "serverUpdateProhibited";

DOM_Element EppDomain::toXML( DOM_Document& doc, const DOMString& tag )
{
	DOM_Element elm;
	DOM_Element body = EppUtil::createElementNS(doc, "domain", tag);
	bool isCreate = tag.equals("create");

	// the order of the tags for create is:
	//
	// name/period/ns/registrant/contact/authInfo
	//
	// the order of the tags for info is
	//
	// name/roid/status/registrant/contact/ns/host/clID/crID/crDate
	// upDate/exDate/trDate/authInfo
	//
	// so the tricky part is to put ns ahead of registrant for
	// a create tag, and ns after contact for an info tag

	if( name != null )
	{
		elm = doc.createElement("name");
		elm.appendChild(doc.createTextNode(name));
		body.appendChild(elm);
	}
	if( period != null )
	{
		body.appendChild(period->toXML(doc, "period"));
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

	// ns for a create tag

	if( isCreate && (ns != null) )
	{
		for( unsigned int i = 0; i < ns->size(); i++ )
		{
			DOMString s = ns->elementAt(i);
			elm = doc.createElement("ns");
			elm.appendChild(doc.createTextNode(s));
			body.appendChild(elm);
		}
	}
	if( registrant != null )
	{
		elm = doc.createElement("registrant");
		elm.appendChild(doc.createTextNode(registrant));
		body.appendChild(elm);
	}
	if( contact != null )
	{
		for( unsigned int i = 0; i < contact->size(); i++ )
		{
			EppContactType c = contact->elementAt(i);
			body.appendChild(c.toXML(doc, "contact"));
		}
	}

	// ns for an info tag

	if( ! isCreate && (ns != null) )
	{
		for( unsigned int i = 0; i < ns->size(); i++ )
		{
			DOMString s = ns->elementAt(i);
			elm = doc.createElement("ns");
			elm.appendChild(doc.createTextNode(s));
			body.appendChild(elm);
		}
	}
	if( host != null )
	{
		for( unsigned int i = 0; i < host->size(); i++ )
		{
			DOMString s = host->elementAt(i);
			elm = doc.createElement("host");
			elm.appendChild(doc.createTextNode(s));
			body.appendChild(elm);
		}
	}

	toXMLCommon(doc, body);

	return body;
}

EppDomain * EppDomain::fromXML( const DOM_Node& root )
{
	EppDomain * domain = new EppDomain();
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
		if( name.substringData(0, 7).equals("domain:") )
		{
			name = name.substringData(7, name.length() - 7);
		}
		if( name.equals("name") )
		{
			domain->setName(EppUtil::getText(node));
		}
		else if( name.equals("host") )
		{
			domain->addHost(EppUtil::getText(node));
		}
		else if( name.equals("ns") )
		{
			domain->addNameServer(EppUtil::getText(node));
		}
		else if( name.equals("contact") )
		{
			EppContactType * c = EppContactType::fromXML(node);
			if( c != null )
			{
				domain->addContact(*c);
				delete c;
			}
		}
		else if( name.equals("period") )
		{
			EppPeriod * p = EppPeriod::fromXML(node);
			if( p != null )
			{
				domain->setPeriod(*p);
				delete p;
			}
		}
		else if( name.equals("registrant") )
		{
			domain->setRegistrant(EppUtil::getText(node));
		}
		else if( name.equals("authInfo") )
		{
			EppAuthInfo * authInfo = EppAuthInfo::fromXML(node);
			if( authInfo != null )
			{
				domain->setAuthInfo(*authInfo);
				delete authInfo;
			}
		}
		else
		{
			domain->fromXMLCommon(node, name);
		}
	}

	return domain;
}
