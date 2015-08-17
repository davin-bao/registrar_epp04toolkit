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
#include "EppCommandUpdate.hpp"
#include "EppCommandUpdateContact.hpp"
#include "EppCommandUpdateDomain.hpp"
#include "EppCommandUpdateHost.hpp"
#include "EppCommandUpdateSvcsub.hpp"

EppCommandUpdate * EppCommandUpdate::fromXML( const DOM_Node& root )
{
	DOMString command = root.getLocalName();

	DOM_NodeList list = root.getChildNodes();
	for( unsigned int i = 0; i < list.getLength(); i++ )
	{
		DOM_Node node = list.item(i);
		DOMString prefix = node.getPrefix();
		DOMString name = node.getLocalName();
/*
		if( (prefix == null) || (name == null) )
		{
			continue;
		}
		if( name.equals(command) )
		{
			if( prefix.equals("contact") )
			{
				return EppCommandUpdateContact.fromXML(node);
			}
			else if( prefix.equals("domain") )
			{
				return EppCommandUpdateDomain.fromXML(node);
			}
			else if( prefix.equals("host") )
			{
				return EppCommandUpdateHost.fromXML(node);
			}
			break;
		}
*/
		if( prefix == null )
		{
			prefix = node.getNodeName();
		}
		if( prefix == null )
		{
			continue;
		}
		if( prefix.equals("contact") || prefix.equals("contact:update") )
		{
			return EppCommandUpdateContact::fromXML(node);
		}
		else if( prefix.equals("domain") || prefix.equals("domain:update") )
		{
			return EppCommandUpdateDomain::fromXML(node);
		}
		else if( prefix.equals("host") || prefix.equals("host:update") )
		{
			return EppCommandUpdateHost::fromXML(node);
		}
		else if( prefix.equals("svcsub") || prefix.equals("svcsub:update") )
		{
			return EppCommandUpdateSvcsub::fromXML(node);
		}
	}

	return null;
}

void EppCommandUpdate::statusToXML( DOM_Document& doc, DOM_Element& body, ValueVectorOf<EppStatus> * list )
{
	DOM_Element elm;
	if( list != null )
	{
		for( unsigned int i = 0; i < list->size(); i++ )
		{
			EppStatus status  = list->elementAt(i);
			elm = status.toXML(doc, "status");
			body.appendChild(elm);
		}
	}
}

void EppCommandUpdate::statusFromXML( const DOM_Node& root, ValueVectorOf<EppStatus> * statusList )
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
//		if( name.equals("status") )
		if(    name.equals("status") 
		    || name.equals("contact:status")
		    || name.equals("domain:status")
		    || name.equals("host:status")
		    || name.equals("svcsub:status") )
		{
			EppStatus * status = EppStatus::fromXML(node);
			if( status != null )
			{
				statusList->addElement(*status);
				delete status;
			}
		}
	}
}
