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
#include "EppGreeting.hpp"
#include "EppUtil.hpp"

void EppGreeting::cloneServiceMenu( EppServiceMenu& menu )
{
	unsigned int i;
	ValueVectorOf<DOMString> * version = menu.getVersion();
	ValueVectorOf<DOMString> * lang    = menu.getLanguage();
	ValueVectorOf<DOMString> * svc     = menu.getService();

	if( this->svcMenu == null )
	{
		this->svcMenu = new EppServiceMenu();
	}

	ValueVectorOf<DOMString> * myVersion = this->svcMenu->getVersion();
	ValueVectorOf<DOMString> * myLang    = this->svcMenu->getLanguage();
	ValueVectorOf<DOMString> * mySvc     = this->svcMenu->getService();

	myVersion->removeAllElements();
	myLang->removeAllElements();
	mySvc->removeAllElements();

	for( i = 0; i < version->size(); i++ )
	{
		myVersion->addElement(version->elementAt(i));
	}
	for( i = 0; i < lang->size(); i++ )
	{
		myLang->addElement(lang->elementAt(i));
	}
	for( i = 0; i < svc->size(); i++ )
	{
		mySvc->addElement(svc->elementAt(i));
	}
}

DOM_Element EppGreeting::toXML( DOM_Document& doc, const DOMString& tag )
{
	DOM_Element elm;
	DOM_Element epp = EppUtil::createElementNS(doc, "epp", null);
	DOM_Element body = doc.createElement(tag);
	epp.appendChild(body);

	if( svID != null )
	{
		elm = doc.createElement("svID");
		elm.appendChild(doc.createTextNode(svID));
		body.appendChild(elm);
	}
	elm = doc.createElement("svDate");
	elm.appendChild(EppUtil::createTextNode(doc, svDate));
	body.appendChild(elm);

	if( svcMenu != null )
	{
		body.appendChild(svcMenu->toXML(doc, "svcMenu"));
	}
	return epp;
}

EppGreeting * EppGreeting::fromXML( const DOM_Node &root )
{
	unsigned int i;
	EppGreeting * greeting = null;
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
		if( name.equals("greeting") )
		{
			greeting = new EppGreeting();
			list = node.getChildNodes();
			break;
		}
	}

	if( greeting == null )
	{
		return null;
	}

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
		if( name.equals("svID") )
		{
			greeting->svID = EppUtil::getText(node);
		}
		else if( name.equals("svDate") )
		{
			greeting->svDate = EppUtil::getDate(node);
		}
		else if( name.equals("svcMenu") )
		{
			if( greeting->svcMenu != null )
			{
				delete greeting->svcMenu;
			}
			greeting->svcMenu = EppServiceMenu::fromXML(node);
		}
	}

	return greeting;
}
