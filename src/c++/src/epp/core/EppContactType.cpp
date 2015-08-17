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
#include "EppContactType.hpp"
#include "EppUtil.hpp"

DOM_Element EppContactType::toXML( DOM_Document& doc, const DOMString& tag )
{
	DOM_Element body = doc.createElement(tag);
	if( type != null )
	{
		body.setAttribute("type", type);
	}
	if( id != null )
	{
		body.appendChild(doc.createTextNode(id));
	}
	return body;
}

EppContactType * EppContactType::fromXML( const DOM_Node& root )
{
	DOMString id = EppUtil::getText(root);
	DOMString type = ((DOM_Element *) &root)->getAttribute("type");

	return new EppContactType(id, type);
}

ValueVectorOf<DOMString> * EppContactType::getContactId( ValueVectorOf<EppContactType> * contact, DOMString type )
{
	ValueVectorOf<DOMString> * list = null;
	if( type == null )
	{
		return null;
	}
	if( contact == null )
	{
		return null;
	}
	for( unsigned int i = 0; i < contact->size(); i++ )
	{
		EppContactType p = contact->elementAt(i);
		if( p.getType().equals(type) )
		{
			if( list == null )
			{
				int size = contact->size() / 2;
				if( size <= 0 )
				{
					size = 1;
				}
				list = new ValueVectorOf<DOMString>(size);
				if( list == null )
				{
					return null;
				}
			}
			list->addElement(p.getId());
		}
	}
	return list;
}
