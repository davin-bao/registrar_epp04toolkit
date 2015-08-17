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
#include "EppCommandUpdateSvcsub.hpp"
#include "EppUtil.hpp"

DOM_Element EppCommandUpdateSvcsub::toXML( DOM_Document& doc, const DOMString& tag )
{
	DOM_Element elm;
	DOM_Element body = EppUtil::createElementNS(doc, "svcsub", tag);

	if( id != null )
	{
		elm = doc.createElement("id");
		elm.appendChild(doc.createTextNode(id));
		body.appendChild(elm);
	}
	if(    (paramAdded->size() > 0)
	    || (contactAdded->size() > 0)
	    || (statusAdded->size() > 0) )
	{
		elm = doc.createElement("add");
		if( paramAdded->size() > 0 )
		{
			paramToXML(doc, elm, paramAdded);
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
	if(    (paramRemoved->size() > 0)
	    || (contactRemoved->size() > 0)
	    || (statusRemoved->size() > 0) )
	{
		elm = doc.createElement("rem");
		if( paramRemoved->size() > 0 )
		{
			paramToXML(doc, elm, paramRemoved);
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
	if( userid != null )
	{
		elm = doc.createElement("userid");
		elm.appendChild(doc.createTextNode(userid));
		body.appendChild(elm);
	}
	if( authInfo != null )
	{
		body.appendChild(authInfo->toXML(doc, "authInfo"));
	}

	return toXMLCommon(doc, tag, body);
}

void EppCommandUpdateSvcsub::paramToXML( DOM_Document& doc, DOM_Element& body, ValueVectorOf<EppSvcsubParam> * list )
{
	DOM_Element elm;
	if( list != null )
	{
		for( unsigned int i = 0; i < list->size(); i++ )
		{
			EppSvcsubParam p = list->elementAt(i);
			elm = p.toXML(doc, "param");
			body.appendChild(elm);
		}
	}
}

void EppCommandUpdateSvcsub::contactToXML( DOM_Document& doc, DOM_Element& body, ValueVectorOf<EppContactType> *list )
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

EppCommandUpdateSvcsub * EppCommandUpdateSvcsub::fromXML( const DOM_Node& root )
{
	EppCommandUpdateSvcsub * cmd = null;
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
//		if( name.equals("id") )
		if( name.equals("id") || name.equals("svcsub:id") )
		{
			if( cmd == null )
			{
				DOMString id = EppUtil::getText(node);
				cmd = new EppCommandUpdateSvcsub(id);
			}
		}
//		else if( name.equals("add") )
		else if( name.equals("add") || name.equals("svcsub:add") )
		{
			if( cmd != null )
			{
				cmd->paramFromXML(node, cmd->paramAdded);
				cmd->contactFromXML(node, cmd->contactAdded);
				cmd->statusFromXML(node, cmd->statusAdded);
			}
		}
//		else if( name.equals("rem") )
		else if( name.equals("rem") || name.equals("svcsub:rem") )
		{
			if( cmd != null )
			{
				cmd->paramFromXML(node, cmd->paramRemoved);
				cmd->contactFromXML(node, cmd->contactRemoved);
				cmd->statusFromXML(node, cmd->statusRemoved);
			}
		}
//		else if( name.equals("chg") )
		else if( name.equals("chg") || name.equals("svcsub:chg") )
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
				if( tname.equals("registrant") || tname.equals("svcsub:registrant") )
				{
					DOMString id = EppUtil::getText(tnode);
					if( cmd != null )
					{
						cmd->setNewRegistrant(id);
					}
				}
//				else if( tname.equals("authInfo") )
				else if( tname.equals("authInfo") || tname.equals("svcsub:authInfo") )
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
//		if( name.equals("userid") )
		if( name.equals("userid") || name.equals("svcsub:userid") )
		{
			DOMString userid = EppUtil::getText(node);
			if( cmd != null )
			{
				cmd->userid = userid;
			}
		}
//		else if( name.equals("authinfo") )
		else if( name.equals("authInfo") || name.equals("svcsub:authInfo") )
		{
			EppAuthInfo * authInfo = EppAuthInfo::fromXML(node);
			if( (cmd != null) && (authInfo != null) )
			{
				cmd->setAuthInfo(*authInfo);
				delete authInfo;
			}
		}
	}
	return cmd;
}

void EppCommandUpdateSvcsub::paramFromXML( const DOM_Node& root, ValueVectorOf<EppSvcsubParam> * paramList )
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
//		if( name.equals("param") )
		if( name.equals("param") || name.equals("svcsub:param") )
		{
			EppSvcsubParam * p = EppSvcsubParam::fromXML(node);
			if( p != null )
			{
				paramList->addElement(*p);
				delete p;
			}
		}
	}
}

void EppCommandUpdateSvcsub::contactFromXML( const DOM_Node& root, ValueVectorOf<EppContactType> * contactList )
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
		if( name.equals("contact") || name.equals("svcsub:contact") )
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
