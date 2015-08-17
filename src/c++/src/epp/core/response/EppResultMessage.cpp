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
#include "EppResultMessage.hpp"
#include "EppUtil.hpp"

DOM_Element EppResultMessage::toXML( DOM_Document& doc, const DOMString& tag )
{
	DOM_Element body = doc.createElement(tag);
	DOM_Element elm;

	if( (id != null) && (id.length() > 0) )
	{
		body.setAttribute("id", id);
	}
	if( (lang != null) && (lang.length() > 0) )
	{
		body.setAttribute("lang", lang);
	}
	if( (msg != null) && (msg.length() > 0) )
	{
		body.appendChild(doc.createTextNode(msg));
	}

	return body;
}

EppResultMessage * EppResultMessage::fromXML( const DOM_Node& root )
{
	DOMString id   = null;
	DOMString lang = null;
	DOMString msg  = null;

	DOM_Element * elm = (DOM_Element *) & root;
	id   = elm->getAttribute("id");
	lang = elm->getAttribute("lang");
	msg  = EppUtil::getText(root);

	return new EppResultMessage(id, lang, msg);
}
