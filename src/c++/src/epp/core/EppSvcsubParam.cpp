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
#include "EppSvcsubParam.hpp"
#include "EppUtil.hpp"
#include "util/ValueVectorOf.hpp"

DOM_Element EppSvcsubParam::toXML( DOM_Document& doc, const DOMString& tag )
{
	DOM_Element body = doc.createElement(tag);
	if( name != null )
	{
		body.setAttribute("name", name);
	}
	if( value != null )
	{
		body.appendChild(doc.createTextNode(value));
	}
	return body;
}

EppSvcsubParam * EppSvcsubParam::fromXML( const DOM_Node& root )
{
	DOMString name  = ((DOM_Element *) &root)->getAttribute("name");
	DOMString value = EppUtil::getText(root);

	return new EppSvcsubParam(name, value);
}

ValueVectorOf<DOMString> * EppSvcsubParam::getParamValue( ValueVectorOf<EppSvcsubParam> * param, DOMString name )
{
	ValueVectorOf<DOMString> * list = null;
	if( name == null )
	{
		return null;
	}
	if( param == null )
	{
		return null;
	}
	for( unsigned int i = 0; i < param->size(); i++ )
	{
		EppSvcsubParam p = param->elementAt(i);
		if( p.getName().equals(name) )
		{
			if( list == null )
			{
				int size = param->size() / 2;
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
			list->addElement(p.getValue());
		}
	}
	return list;
}
