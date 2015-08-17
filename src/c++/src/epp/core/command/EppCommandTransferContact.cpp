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
#include "EppCommandTransferContact.hpp"
#include "EppUtil.hpp"

DOM_Element EppCommandTransferContact::toXMLPoll( DOM_Document& doc, const DOMString& tag )
{
	DOM_Element elm;
	DOM_Element body = EppUtil::createElementNS(doc, "contact", tag);

	if( id != null )
	{
		elm = doc.createElement("id");
		elm.appendChild(doc.createTextNode(id));
		body.appendChild(elm);
	}
	if( authInfo != null )
	{
		body.appendChild(authInfo->toXML(doc, "authInfo"));
	}

	return body;
}

DOM_Element EppCommandTransferContact::toXML( DOM_Document& doc, const DOMString& tag )
{
	DOM_Element body = toXMLPoll(doc, tag);

	DOM_Attr attr = doc.createAttribute("op");
	attr.setValue(this->getOperation());
	ValueVectorOf<DOM_Attr> attrList(1);
	attrList.addElement(attr);

	return toXMLCommon(doc, tag, body, &attrList);
}

EppCommandTransferContact * EppCommandTransferContact::fromXML( const DOM_Node& root )
{
	EppCommandTransferContact * cmd = null;
	EppAuthInfo * authInfo = null;
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
		if( name.equals("id") || name.equals("contact:id") )
		{
			DOMString id = EppUtil::getText(node);
			if( cmd == null )
			{
				cmd = new EppCommandTransferContact(id);
			}
		}
//		else if( name.equals("authInfo") )
		else if( name.equals("authInfo") || name.equals("contact:authInfo") )
		{
			if( authInfo == null )
			{
				authInfo = EppAuthInfo::fromXML(node);
			}
		}
	}
	if( cmd != null )
	{
		cmd->authInfo = authInfo;
	}
	else if( authInfo != null )
	{
		delete authInfo;
	}

	return cmd;
}
