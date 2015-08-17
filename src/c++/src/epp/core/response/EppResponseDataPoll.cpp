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
#include "EppResponseDataPoll.hpp"
#include "EppCommandTransfer.hpp"
#include "EppUtil.hpp"

DOM_Element EppResponseDataPoll::toXML( DOM_Document& doc, const DOMString& tag )
{
	DOM_Element elm;
	DOM_Element body = doc.createElement(tag);
	if( object != null )
	{
		// FIXME(zhang) - check for run-time type
//		if( object instanceof EppCommandTransfer )
		{
			elm = object->toXMLPoll(doc, "transfer"); 
			body.appendChild(elm);
		}
	}
	return body;
}

EppResponseDataPoll * EppResponseDataPoll::fromXML( const DOM_Node& root )
{
	DOMString name = root.getLocalName();
	EppPollable * object = null;
	if( name == null )
	{
		name = root.getNodeName();
	}
	if( name == null )
	{
		return null;
	}
//	if( name.equals("transfer") )
	if(    name.equals("transfer")
	    || name.equals("contact:transfer")
	    || name.equals("domain:transfer")
	    || name.equals("svcsub:transfer") )
	{
		object = EppCommandTransfer::fromXMLPoll(root);
	}
	if( object == null )
	{
		return null;
	}

	EppResponseDataPoll * rsp = new EppResponseDataPoll();
	rsp->object = object;
	rsp->freeable = true;

	return rsp;
}
