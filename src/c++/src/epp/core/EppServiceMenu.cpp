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
#include "EppServiceMenu.hpp"
#include "EppUtil.hpp"

void EppServiceMenu::addUnspec( DOMString name, DOMString uri, DOMString schema )
{
	unsigned int i;
	if( (name == null) || (uri == null) || (schema == null) )
	{
		return;
	}
	for( i = 0; i < name.length(); i++ )
	{
		if( name.charAt(i) == ' ' )
		{
			return;
		}
	}
	for( i = 0; i < uri.length(); i++ )
	{
		if( uri.charAt(i) == ' ' )
		{
			return;
		}
	}
	for( i = 0; i < schema.length(); i++ )
	{
		if( schema.charAt(i) == ' ' )
		{
			return;
		}
	}
	this->unspec->addElement(name + " " + uri + " " + schema);
}

DOM_Element EppServiceMenu::toXML( DOM_Document& doc, const DOMString& tag )
{
	DOM_Element elm;
	DOM_Element body = doc.createElement(tag);

	if( version != null )
	{
		for( unsigned int i = 0; i < version->size(); i++ )
		{
			DOMString obj = version->elementAt(i);
			if( (obj != null) && (obj.length() > 0) )
			{
				elm = doc.createElement("version");
				elm.appendChild(doc.createTextNode(obj));
				body.appendChild(elm);
			}
		}
	}
	if( lang != null )
	{
		for( unsigned int i = 0; i < lang->size(); i++ )
		{
			DOMString obj = lang->elementAt(i);
			if( (obj != null) && (obj.length() > 0) )
			{
				elm = doc.createElement("lang");
				elm.appendChild(doc.createTextNode(obj));
				body.appendChild(elm);
			}
		}
	}
	if( svc != null )
	{
		for( unsigned int i = 0; i < svc->size(); i++ )
		{
			DOMString obj = svc->elementAt(i);
			if( (obj != null) && (obj.length() > 0) )
			{
				elm = EppUtil::createElementNS(doc, obj, "svc", false);
				body.appendChild(elm);
			}
		}
	}
	if( (unspec != null) && (unspec->size() > 0) )
	{
		elm = doc.createElement("unspec");
		for( unsigned int i = 0; i < unspec->size(); i++ )
		{
			DOMString obj = unspec->elementAt(i);
			if( (obj != null) && (obj.length() > 0) )
			{
				DOM_Element unspec = EppUtil::createElementNSUnspec(doc, obj, "svc", false);
				if( unspec != null )
				{
					elm.appendChild(unspec);
				}
			}
		}
		body.appendChild(elm);
	}
	return body;
}

EppServiceMenu * EppServiceMenu::fromXML( const DOM_Node& root )
{
	// FIXME(nzhang) - need to remove the hack to get around of the
	//                 problem that getLocalName()/getPrefix() may
	//                 return null if setDoNamespaces is set to false

	EppServiceMenu * svcmenu = new EppServiceMenu();
	DOM_NodeList list = root.getChildNodes();
	for( unsigned int i = 0; i < list.getLength(); i++ )
	{
		DOM_Node node = list.item(i);
		DOMString name = node.getLocalName();
		bool local = true;
		if( name == null )
		{
			name = node.getNodeName();
			local = false;
		}
		if( name == null )
		{
			continue;
		}
		if( name.equals("version") )
		{
			svcmenu->addVersion(EppUtil::getText(node));
		}
		else if( name.equals("lang") )
		{
			svcmenu->addLanguage(EppUtil::getText(node));
		}
//		else if( name.equals("svc") )
		else if(    (  local && name.equals("svc"))
			 || (! local && (name.length() > 4)
				     && name.substringData(name.length() - 4, 4).equals(":svc")) )
		{
			DOMString prefix = node.getPrefix();
			if( prefix == null )
			{
				prefix = name.substringData(0, name.length() - 4);
			}
			if( prefix != null )
			{
				svcmenu->addService(prefix);
			}
		}
		else if( name.equals("unspec") )
		{
			DOM_NodeList ulist = node.getChildNodes();
			for( unsigned int j = 0; j < ulist.getLength(); j++ )
			{
				DOM_Node unode = ulist.item(j);
				name = unode.getLocalName();
				local = true;
				if( name == null )
				{
					name = unode.getNodeName();
					local = false;
				}
				if( name == null )
				{
					continue;
				}
//				else if( name.equals("svc") )
				else if(    (  local && name.equals("svc"))
					 || (! local && (name.length() > 4)
						     && name.substringData(name.length() - 4, 4).equals(":svc")) )
				{
					DOMString prefix = unode.getPrefix();
					if( prefix == null )
					{
						prefix = name.substringData(0, name.length() - 4);
					}
					if( prefix == null )
					{
						continue;
					}
					DOMString uri = ((DOM_Element *) &unode)->getAttribute("xmslns:" + prefix);
					DOMString loc = ((DOM_Element *) &unode)->getAttribute("xsi:schemaLocation");
					if( (loc == null) || (uri == null) )
					{
						continue;
					}
					unsigned len = uri.length() + 1;
					unsigned off = loc.length() - len;
					if( off <= 0 )
					{
						continue;
					}
					loc = loc.substringData(len, off);
					if( loc == null )
					{
						continue;
					}
					svcmenu->addUnspec(prefix, uri, loc);
				}
			}
		}
	}

	return svcmenu;
}
