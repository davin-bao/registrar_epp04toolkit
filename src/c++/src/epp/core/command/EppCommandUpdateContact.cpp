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
#include "EppCommandUpdateContact.hpp"
#include "EppUtil.hpp"

DOM_Element EppCommandUpdateContact::toXML( DOM_Document& doc, const DOMString& tag )
{
	DOM_Element elm;
	DOM_Element body = EppUtil::createElementNS(doc, "contact", tag);

	if( id != null )
	{
		elm = doc.createElement("id");
		elm.appendChild(doc.createTextNode(id));
		body.appendChild(elm);
	}
	if( statusAdded->size() > 0 )
	{
		elm = doc.createElement("add");
		statusToXML(doc, elm, statusAdded);
		body.appendChild(elm);
	}
	if( statusRemoved->size() > 0 )
	{
		elm = doc.createElement("rem");
		statusToXML(doc, elm, statusRemoved);
		body.appendChild(elm);
	}
	if(    (newAscii != null) || (newI15d != null)
	    || (newVoice != null) || (newFax != null)
	    || (newEmail != null) || (newAuthInfo != null) )
	{
		elm = doc.createElement("chg");
		if( newAscii != null )
		{
			elm.appendChild(newAscii->toXML(doc, "ascii"));
		}
		if( newI15d != null )
		{
			elm.appendChild(newI15d->toXML(doc, "i15d"));
		}
		if( newVoice != null )
		{
			elm.appendChild(newVoice->toXML(doc, "voice"));
		}
		if( newFax != null )
		{
			elm.appendChild(newFax->toXML(doc, "fax"));
		}
		if( newEmail != null )
		{
			DOM_Element email = doc.createElement("email");
			email.appendChild(doc.createTextNode(newEmail));
			elm.appendChild(email);
		}
		if( newAuthInfo != null )
		{
			elm.appendChild(newAuthInfo->toXML(doc, "authInfo"));
		}
		body.appendChild(elm);
	}

	return toXMLCommon(doc, tag, body);
}

EppCommandUpdateContact * EppCommandUpdateContact::fromXML( const DOM_Node& root )
{
	EppCommandUpdateContact * cmd = null;
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
			if( cmd == null )
			{
				DOMString id = EppUtil::getText(node);
				cmd = new EppCommandUpdateContact(id);
			}
		}
//		else if( name.equals("add") )
		else if( name.equals("add") || name.equals("contact:add") )
		{
			if( cmd != null )
			{
				cmd->statusFromXML(node, cmd->statusAdded);
			}
		}
//		else if( name.equals("rem") )
		else if( name.equals("rem") || name.equals("contact:rem") )
		{
			if( cmd != null )
			{
				cmd->statusFromXML(node, cmd->statusRemoved);
			}
		}
//		else if( name.equals("chg") )
		else if( name.equals("chg") || name.equals("contact:chg") )
		{
			if( cmd != null )
			{
				cmd->addNewStuff(node);
			}
		}
	}

	return cmd;
}

void EppCommandUpdateContact::addNewStuff( const DOM_Node& root )
{
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
//		if( name.equals("ascii") )
		if( name.equals("ascii") || name.equals("contact:ascii") )
		{
			EppContactData * ascii = EppContactData::fromXML(node);
			if( ascii != null )
			{
				setNewAscii(*ascii);
				delete ascii;
			}
		}
//		else if( name.equals("i15d") )
		else if( name.equals("i15d") || name.equals("contact:i15d") )
		{
			EppContactData * i15d = EppContactData::fromXML(node);
			if( i15d != null )
			{
				setNewI15d(*i15d);
				delete i15d;
			}
		}
//		else if( name.equals("voice") )
		else if( name.equals("voice") || name.equals("contact:voice") )
		{
			EppE164 * voice = EppE164::fromXML(node);
			if( voice != null )
			{
				setNewVoice(*voice);
				delete voice;
			}
		}
//		else if( name.equals("fax") )
		else if( name.equals("fax") || name.equals("contact:fax") )
		{
			EppE164 * fax = EppE164::fromXML(node);
			if( fax != null )
			{
				setNewFax(*fax);
				delete fax;
			}
		}
//		else if( name.equals("email") )
		else if( name.equals("email") || name.equals("contact:email") )
		{
			DOMString email = EppUtil::getText(node);
			setNewEmail(email);
		}
//		else if( name.equals("authInfo") )
		else if( name.equals("authInfo") || name.equals("contact:authInfo") )
		{
			EppAuthInfo * authInfo = EppAuthInfo::fromXML(node);
			if( authInfo != null )
			{
				setNewAuthInfo(*authInfo);
				delete authInfo;
			}
		}
	}
}
