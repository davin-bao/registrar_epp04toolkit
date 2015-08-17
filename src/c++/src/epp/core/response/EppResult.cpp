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
#include <stdio.h>
#include <stdlib.h>
#include "EppResult.hpp"
#include "EppUtil.hpp"

DOM_Element EppResult::toXML( DOM_Document& doc, const DOMString& tag )
{
	DOM_Element body = doc.createElement(tag);
	DOM_Element elm;
	char buf[16];

	(void) sprintf(buf, "%d", code);

	body.setAttribute("code", buf);

	if( msg != null )
	{
		body.appendChild(msg->toXML(doc, "msg"));
	}

	if( (value != null) && (value->size() > 0) )
	{
		for( unsigned int i = 0; i < value->size(); i++ )
		{
			DOMString obj = value->elementAt(i);
			elm = doc.createElement("value");
			elm.appendChild(doc.createTextNode(obj));
			body.appendChild(elm);
		}
	}

	return body;
}

EppResult * EppResult::fromXML( const DOM_Node& root )
{
	EppResult * result = new EppResult();
	DOM_Element * elm = (DOM_Element *) &root;

	DOMString code = elm->getAttribute("code");
	if( code != null )
	{
		char * p = code.transcode();
		if( p != null )
		{
			result->code = atoi(p);
			delete [] p;
		}
	}

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
		if( name.equals("msg") )
		{
			result->msg = EppResultMessage::fromXML(node);
		}
		else if( name.equals("value") )
		{
			result->addValue(EppUtil::getText(node));
		}
	}
	return result;
}

EppResult * EppResult::clone()
{
	EppResult * p = new EppResult();
	if( p == null )
	{
		return null;
	}
	p->code = this->code;
	if( this->msg != null )
	{
		p->setMessage(this->msg);
	}
	if( this->value != null )
	{
		for( unsigned int i = 0; i < this->value->size(); i++ )
		{
			DOMString s = this->value->elementAt(i);
			p->addValue(s);
		}
	}

	return p;
}

void EppResult::setMessage( EppResultMessage * message )
{
	if( message == null )
	{
		return;
	}
	if( this->msg == null )
	{
		this->msg = new EppResultMessage();
	}
	if( this->msg != null )
	{
		this->msg->setId(message->getId());
		this->msg->setLanguage(message->getLanguage());
		this->msg->setMessage(message->getMessage());
	}
}
