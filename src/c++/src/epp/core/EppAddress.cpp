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
#include "EppAddress.hpp"
#include "EppUtil.hpp"

EppAddress::EppAddress()
{
	for( int i = 0; i < MAX_NUM_OF_STREETS; i++ )
	{
		this->street[i] = null;
	}

	this->city = null;
	this->sp = null;
	this->pc = null;
	this->cc = null;
}

EppAddress::EppAddress( DOMString city, DOMString sp, DOMString pc, DOMString cc )
{
	for( int i = 0; i < MAX_NUM_OF_STREETS; i++ )
	{
		this->street[i] = null;
	}

	this->city = city;
	this->sp = sp;
	this->pc = pc;
	this->cc = cc;
}

EppAddress::EppAddress( DOMString street, DOMString city, DOMString sp, DOMString pc, DOMString cc )
{
	for( int i = 0; i < MAX_NUM_OF_STREETS; i++ )
	{
		this->street[i] = null;
	}
	this->street[0] = street;
	this->city = city;
	this->sp = sp;
	this->pc = pc;
	this->cc = cc;
}

EppAddress::EppAddress( DOMString street[], DOMString city, DOMString sp, DOMString pc, DOMString cc )
{
	for( int i = 0; i < MAX_NUM_OF_STREETS; i++ )
	{
		this->street[i] = street[i];
	}
	this->city = city;
	this->sp = sp;
	this->pc = pc;
	this->cc = cc;
}

void EppAddress::setStreet( DOMString street[] )
{
	for( int i = 0; i < MAX_NUM_OF_STREETS; i++ )
	{
		this->street[i] = street[i];
	}
}

void EppAddress::setStreet( int index, DOMString street )
{
	if( (index >= 0) && (index < MAX_NUM_OF_STREETS) )
	{
		this->street[index] = street;
	}
}

EppAddress * EppAddress::fromXML( const DOM_Node& root )
{
	DOMString street[MAX_NUM_OF_STREETS];
	DOMString city = null;
	DOMString sp = null;
	DOMString pc = null;
	DOMString cc = null;
	unsigned int i;

	for( i = 0; i < MAX_NUM_OF_STREETS; i++ )
	{
		street[i] = null;
	}

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
		if( name.substringData(0, 8).equals("contact:") )
		{
			name = name.substringData(8, name.length() - 8);
		}
		if( name.equals("street") )
		{
			for( int j = 0; j < MAX_NUM_OF_STREETS; j++ )
			{
				if( street[j] == null )
				{
					street[j] = EppUtil::getText(node);
					break;
				}
			}
		}
		else if( name.equals("city") )
		{
			city = EppUtil::getText(node);
		}
		else if( name.equals("sp") )
		{
			sp = EppUtil::getText(node);
		}
		else if( name.equals("pc") )
		{
			pc = EppUtil::getText(node);
		}
		else if( name.equals("cc") )
		{
			cc = EppUtil::getText(node);
		}
	}

	return new EppAddress(street, city, sp, pc, cc);
}

DOM_Element EppAddress::toXML( DOM_Document& doc, const DOMString& tag )
{
	DOM_Element body = doc.createElement(tag);
	DOM_Element elm;

	for( int i = 0; i < MAX_NUM_OF_STREETS; i++ )
	{
		if( street[i] != null )
		{
			elm = doc.createElement("street");
			elm.appendChild(doc.createTextNode(street[i]));
			body.appendChild(elm);
		}
	}
	if( city != null )
	{
		elm = doc.createElement("city");
		elm.appendChild(doc.createTextNode(city));
		body.appendChild(elm);
	}
	if( sp != null )
	{
		elm = doc.createElement("sp");
		elm.appendChild(doc.createTextNode(sp));
		body.appendChild(elm);
	}
	if( pc != null )
	{
		elm = doc.createElement("pc");
		elm.appendChild(doc.createTextNode(pc));
		body.appendChild(elm);
	}
	if( cc != null )
	{
		elm = doc.createElement("cc");
		elm.appendChild(doc.createTextNode(cc));
		body.appendChild(elm);
	}
	return body;
}
