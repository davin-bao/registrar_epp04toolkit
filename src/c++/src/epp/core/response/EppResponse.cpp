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
#include "EppResponse.hpp"
#include "EppUtil.hpp"

EppResponse::~EppResponse()
{
	if( this->result != null )
	{
		for( unsigned int i = 0; i < this->result->size(); i++ )
		{
			EppResult * p = this->result->elementAt(i);
			if( p != null )
			{
				delete p;
			}
		}
		delete this->result;
		this->result = null;
	}
	if( this->resData != null )
	{
		if( this->freeable )
		{
			delete this->resData;
		}
		this->resData = null;
	}
	if( this->unspec != null )
	{
		delete this->unspec;
		this->unspec = null;
	}
	if( this->trID != null )
	{
		delete this->trID;
		this->trID = null;
	}
}

bool EppResponse::success()
{
	if( result == null )
	{
		return false;
	}

	if( result->size() != 1 )
	{
		return false;
	}

	EppResult * r = result->elementAt(0);

	if( (r != null) && EppError::isError(r->getCode()) )
	{
		return false;
	}

	return true;
}

DOM_Element EppResponse::toXML( DOM_Document& doc, const DOMString& tag )
{
	DOM_Element elm;
	DOM_Element epp = EppUtil::createElementNS(doc, "epp", null);
	DOM_Element body = doc.createElement(tag);
	epp.appendChild(body);

	if( result != null )
	{
		for( unsigned int i = 0; i < result->size(); i++ )
		{
			EppResult * obj = result->elementAt(i);
			if( obj != null )
			{
				body.appendChild(obj->toXML(doc, "result"));
			}
		}
	}

	if( (msgQCount > 0) || (msgQDate != 0) )
	{
		elm = doc.createElement("msgQ");
		if( msgQCount > 0 )
		{
			char buf[16];

			(void) sprintf(buf, "%d", msgQCount);

			elm.setAttribute("count", buf);
		}
		if( msgQDate != 0 )
		{
			DOM_Element d = doc.createElement("qDate");
			d.appendChild(EppUtil::createTextNode(doc, msgQDate));
			elm.appendChild(d);
		}
		body.appendChild(elm);
	}

	if( resData != null )
	{
		body.appendChild(resData->toXML(doc, "resData"));
	}

	if( unspec != null )
	{
		elm = unspec->toXML(doc, "unspec");
		body.appendChild(elm);
	}

	if( trID != null )
	{
		body.appendChild(trID->toXML(doc, "trID"));
	}

	return epp;
}

EppResponse * EppResponse::fromXML( const DOM_Node& root )
{
	unsigned int i;
	EppResponse * rsp = null;
	DOM_Node response;
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
		if( name.equals("response") )
		{
			response = node;
			found = true;
			break;
		}
	}

	if( found == false )
	{
		return null;
	}

	rsp = new EppResponse();
	list = response.getChildNodes();
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
		if( name.equals("result") )
		{
			EppResult * r = EppResult::fromXML(node);
			if( r != null )
			{
				rsp->result->addElement(r);
			}
		}
		else if( name.equals("msgQ") )
		{
			DOM_Element * elm = (DOM_Element *) &node;
			DOMString str = elm->getAttribute("count");
			if( (str != null) && (str.length() > 0) )
			{
				char * p = str.transcode();
				if( p != null )
				{
					rsp->msgQCount = atoi(p);
					delete p;
				}
			}
			DOM_NodeList qlist = node.getChildNodes();
			for( unsigned int j = 0; j < qlist.getLength(); j++ )
			{
				node = qlist.item(j);
				name = node.getLocalName();
				if( name == null )
				{
					name = node.getNodeName();
				}
				if( name == null )
				{
					continue;
				}
				if( name.equals("qDate") )
				{
					rsp->msgQDate = EppUtil::getDate(node);
				}
			}
		}
		else if( name.equals("resData") )
		{
			if( rsp->resData == null )
			{
				rsp->resData = EppResponseData::fromXML(node);
				rsp->freeable = true;
			}
		}
		else if( name.equals("unspec") )
		{
			if( rsp->unspec == null )
			{
				rsp->unspec = EppUnspec::fromXML(node);
			}
		}
		else if( name.equals("trID") )
		{
			if( rsp->trID == null )
			{
				rsp->trID = EppTransactionId::fromXML(node);
			}
		}
	}

	return rsp;
}
