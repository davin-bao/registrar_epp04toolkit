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
#include "EppCreds.hpp"
#include "EppUtil.hpp"

DOM_Element EppCreds::toXML( DOM_Document& doc, const DOMString& tag )
{
	DOM_Element body = doc.createElement(tag);
	DOM_Element elm;

	if( clID != null )
	{
		elm = doc.createElement("clID");
		elm.appendChild(doc.createTextNode(clID));
		body.appendChild(elm);
	}
	if( pw != null )
	{
		elm = doc.createElement("pw");
		elm.appendChild(doc.createTextNode(pw));
		body.appendChild(elm);
	}
	if( newPW != null )
	{
		elm = doc.createElement("newPW");
		elm.appendChild(doc.createTextNode(newPW));
		body.appendChild(elm);
	}
	if( options != null )
	{
		body.appendChild(options->toXML(doc, "options"));
	}

	return body;
}

EppCreds * EppCreds::fromXML( const DOM_Node& root )
{
	DOMString clID = null;
	DOMString pw = null;
	DOMString newPW = null;
	EppCredsOptions * opt = null;
	EppCreds * creds = null;

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
		if( name.equals("clID") )
		{
			clID = EppUtil::getText(node);
		}
		else if( name.equals("pw") )
		{
			pw = EppUtil::getText(node);
		}
		else if( name.equals("newPW") )
		{
			newPW = EppUtil::getText(node);
		}
		else if( name.equals("options") )
		{
			if( opt != null )
			{
				delete opt;
			}
			opt = EppCredsOptions::fromXML(node);
		}
	}

	if( (clID != null) && (pw != null) )
	{
		creds = new EppCreds(clID, pw, newPW);
		if( opt != null )
		{
			creds->setOptions(*opt);
		}
	}

	if( opt != null )
	{
		delete opt;
	}

	return creds;
}
