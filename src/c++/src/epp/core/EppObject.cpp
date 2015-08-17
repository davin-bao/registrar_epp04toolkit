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
#include "EppObject.hpp"
#include "EppContact.hpp"
#include "EppDomain.hpp"
#include "EppHost.hpp"
#include "EppSvcsub.hpp"
#include "EppUtil.hpp"
#include "EppCommandCreate.hpp"

const int EppObject::CONTACT = 1;
const int EppObject::DOMAIN  = 2;
const int EppObject::HOST    = 3;
const int EppObject::SVCSUB  = 4;

EppObject::EppObject()
{
	this->roid     = null;
	this->status   = new ValueVectorOf<EppStatus>(MAX_NUM_OF_STATUS);
	this->clID     = null;
	this->crID     = null;
	this->crDate   = 0;
	this->upID     = null;
	this->upDate   = 0;
	this->exDate   = 0;
	this->trDate   = 0;
	this->authInfo = null;
}

void EppObject::freeCommon()
{
	if( this->status != null )
	{
		delete this->status;
		this->status = null;
	}
	if( this->authInfo != null )
	{
		delete this->authInfo;
		this->authInfo = null;
	}
}

void EppObject::fromXMLCommon( const DOM_Node& node, const DOMString name )
{
	if( name.equals("roid") )
	{
		roid = EppUtil::getText(node);
	}
	else if( name.equals("clID") )
	{
		clID = EppUtil::getText(node);
	}
	else if( name.equals("crID") )
	{
		crID = EppUtil::getText(node);
	}
	else if( name.equals("crDate") )
	{
		crDate = EppUtil::getDate(node);
	}
	else if( name.equals("upID") )
	{
		upID = EppUtil::getText(node);
	}
	else if( name.equals("upDate") )
	{
		upDate = EppUtil::getDate(node);
	}
	else if( name.equals("exDate") )
	{
		exDate = EppUtil::getDate(node);
	}
	else if( name.equals("trDate") )
	{
		trDate = EppUtil::getDate(node);
	}
	else if( name.equals("authInfo") )
	{
		if( authInfo != null )
		{
			delete authInfo;
		}
		authInfo = EppAuthInfo::fromXML(node);
	}
	else if( name.equals("status") )
	{
		EppStatus * s = EppStatus::fromXML(node);
		if( s != null )
		{
			addStatus(*s);
			delete s;
		}
	}
}

void EppObject::toXMLCommon( DOM_Document& doc, DOM_Element& body )
{
	DOM_Element elm;
	if( clID != null )
	{
		elm = doc.createElement("clID");
		elm.appendChild(doc.createTextNode(clID));
		body.appendChild(elm);
	}
	if( crID != null )
	{
		elm = doc.createElement("crID");
		elm.appendChild(doc.createTextNode(crID));
		body.appendChild(elm);
	}
	if( crDate != 0 )
	{
		elm = doc.createElement("crDate");
		elm.appendChild(EppUtil::createTextNode(doc, crDate));
		body.appendChild(elm);
	}
	if( upID != null )
	{
		elm = doc.createElement("upID");
		elm.appendChild(doc.createTextNode(upID));
		body.appendChild(elm);
	}
	if( upDate != 0 )
	{
		elm = doc.createElement("upDate");
		elm.appendChild(EppUtil::createTextNode(doc, upDate));
		body.appendChild(elm);
	}
	if( exDate != 0 )
	{
		elm = doc.createElement("exDate");
		elm.appendChild(EppUtil::createTextNode(doc, exDate));
		body.appendChild(elm);
	}
	if( trDate != 0 )
	{
		elm = doc.createElement("trDate");
		elm.appendChild(EppUtil::createTextNode(doc, trDate));
		body.appendChild(elm);
	}
	if( authInfo != null )
	{
		body.appendChild(authInfo->toXML(doc, "authInfo"));
	}
}

EppObject * EppObject::fromXML( const DOM_Node& root )
{
	DOMString prefix = root.getPrefix();
	DOMString name = root.getNodeName();
	if( (prefix != null) || (name != null) )
	{
		if(    ((prefix != null) && prefix.equals("contact"))
		    || ((prefix == null) && name.substringData(0, 8).equals("contact:")) )
		{
			return EppContact::fromXML(root);
		}
		else if(    ((prefix != null) && prefix.equals("domain"))
		         || ((prefix == null) && name.substringData(0, 7).equals("domain:")) )
		{
			return EppDomain::fromXML(root);
		}
		else if(    ((prefix != null) && prefix.equals("host"))
		         || ((prefix == null) && name.substringData(0, 5).equals("host:")) )
		{
			return EppHost::fromXML(root);
		}
		else if(    ((prefix != null) && prefix.equals("svcsub"))
		         || ((prefix == null) && name.substringData(0, 7).equals("svcsub:")) )
		{
			return EppSvcsub::fromXML(root);
		}
/*
		if( prefix.equals("contact") )
		{
			return EppContact::fromXML(root);
		}
		else if( prefix.equals("domain") )
		{
			return EppDomain::fromXML(root);
		}
		else if( prefix.equals("host") )
		{
			return EppHost::fromXML(root);
		}
		else if( prefix.equals("svcsub") )
		{
			return EppSvcsub::fromXML(root);
		}
*/
	}

	return null;
}

EppCommandCreate EppObject::create( EppObject * object, DOMString xid )
{
	return EppCommandCreate(object, xid);
}
