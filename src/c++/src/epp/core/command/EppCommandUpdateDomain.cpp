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
#include "EppCommandUpdateDomain.hpp"
#include "EppUtil.hpp"

DOM_Element EppCommandUpdateDomain::toXML( DOM_Document& doc, const DOMString& tag )
{
	DOM_Element elm;
	DOM_Element body = EppUtil::createElementNS(doc, "domain", tag);

	if( name != null )
	{
		elm = doc.createElement("name");
		elm.appendChild(doc.createTextNode(name));
		body.appendChild(elm);
	}
	if(    (nsAdded->size() > 0)
	    || (contactAdded->size() > 0)
	    || (statusAdded->size() > 0) )
	{
		elm = doc.createElement("add");
		if( nsAdded->size() > 0 )
		{
			nameServerToXML(doc, elm, nsAdded);
		}
		if( contactAdded->size() > 0 )
		{
			contactToXML(doc, elm, contactAdded);
		}
		if( statusAdded->size() > 0 )
		{
			statusToXML(doc, elm, statusAdded);
		}
		body.appendChild(elm);
	}
	if(    (nsRemoved->size() > 0)
	    || (contactRemoved->size() > 0)
	    || (statusRemoved->size() > 0) )
	{
		elm = doc.createElement("rem");
		if( nsRemoved->size() > 0 )
		{
			nameServerToXML(doc, elm, nsRemoved);
		}
		if( contactRemoved->size() > 0 )
		{
			contactToXML(doc, elm, contactRemoved);
		}
		if( statusRemoved->size() > 0 )
		{
			statusToXML(doc, elm, statusRemoved);
		}
		body.appendChild(elm);
	}
	if( (newRegistrant != null) || (newAuthInfo != null) )
	{
		elm = doc.createElement("chg");
		if( newRegistrant != null )
		{
			DOM_Element name = doc.createElement("registrant");
			name.appendChild(doc.createTextNode(newRegistrant));
			elm.appendChild(name);
		}
		if( newAuthInfo != null )
		{
			elm.appendChild(newAuthInfo->toXML(doc, "authInfo"));
		}
		body.appendChild(elm);
	}

	return toXMLCommon(doc, tag, body);
}

void EppCommandUpdateDomain::nameServerToXML( DOM_Document& doc, DOM_Element& body, ValueVectorOf<DOMString> * list )
{
	DOM_Element elm;
	if( list != null )
	{
		for( unsigned int i = 0; i < list->size(); i++ )
		{
			DOMString ns = list->elementAt(i);
			elm = doc.createElement("ns");
			elm.appendChild(doc.createTextNode(ns));
			body.appendChild(elm);
		}
	}
}

void EppCommandUpdateDomain::contactToXML( DOM_Document& doc, DOM_Element& body, ValueVectorOf<EppContactType> *list )
{
	DOM_Element elm;
	if( list != null )
	{
		for( unsigned int i = 0; i < list->size(); i++ )
		{
			EppContactType ct  = list->elementAt(i);
			elm = ct.toXML(doc, "contact");
			body.appendChild(elm);
		}
	}
}

EppCommandUpdateDomain * EppCommandUpdateDomain::fromXML( const DOM_Node& root )
{
	EppCommandUpdateDomain * cmd = null;
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
//		if( name.equals("name") )
		if( name.equals("name") || name.equals("domain:name") )
		{
			if( cmd == null )
			{
				DOMString host = EppUtil::getText(node);
				cmd = new EppCommandUpdateDomain(host);
			}
		}
//		else if( name.equals("add") )
		else if( name.equals("add") || name.equals("domain:add") )
		{
			if( cmd != null )
			{
				cmd->nameServerFromXML(node, cmd->nsAdded);
				cmd->contactFromXML(node, cmd->contactAdded);
				cmd->statusFromXML(node, cmd->statusAdded);
			}
		}
//		else if( name.equals("rem") )
		else if( name.equals("rem") || name.equals("domain:rem") )
		{
			if( cmd != null )
			{
				cmd->nameServerFromXML(node, cmd->nsRemoved);
				cmd->contactFromXML(node, cmd->contactRemoved);
				cmd->statusFromXML(node, cmd->statusRemoved);
			}
		}
//		else if( name.equals("chg") )
		else if( name.equals("chg") || name.equals("domain:chg") )
		{
			DOM_NodeList tlist = node.getChildNodes();
			for( unsigned int j = 0; j < tlist.getLength(); j++ )
			{
				DOM_Node tnode = tlist.item(j);
				DOMString tname = tnode.getLocalName();
				if( tname == null )
				{
					tname = tnode.getNodeName();
				}
				if( tname == null )
				{
					continue;
				}
//				if( tname.equals("registrant") )
				if( tname.equals("registrant") || tname.equals("domain:registrant") )
				{
					DOMString id = EppUtil::getText(tnode);
					if( cmd != null )
					{
						cmd->setNewRegistrant(id);
					}
				}
//				else if( tname.equals("authInfo") )
				else if( tname.equals("authInfo") || tname.equals("domain:authInfo") )
				{
					EppAuthInfo * authInfo = EppAuthInfo::fromXML(tnode);
					if( (cmd != null) && (authInfo != null) )
					{
						cmd->setNewAuthInfo(*authInfo);
						delete authInfo;
					}
				}
			}
		}
	}
	return cmd;
}

void EppCommandUpdateDomain::nameServerFromXML( const DOM_Node& root, ValueVectorOf<DOMString> * nameServerList )
{
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
//		if( name.equals("ns") )
		if( name.equals("ns") || name.equals("domain:ns") )
		{
			DOMString ns = EppUtil::getText(node);
			nameServerList->addElement(ns);
		}
	}
}

void EppCommandUpdateDomain::contactFromXML( const DOM_Node& root, ValueVectorOf<EppContactType> * contactList )
{
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
//		if( name.equals("contact") )
		if( name.equals("contact") || name.equals("domain:contact") )
		{
			EppContactType * ct = EppContactType::fromXML(node);
			if( ct != null )
			{
				contactList->addElement(*ct);
				delete ct;
			}
		}
	}
}
