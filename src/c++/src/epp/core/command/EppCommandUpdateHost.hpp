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


#if ! defined(EPPCOMMANDUPDATEHOST_HPP)    /* { */
#define       EPPCOMMANDUPDATEHOST_HPP        1

#include "EppCommandUpdate.hpp"
#include "EppIpAddress.hpp"

#define	MAX_NUM_OF_UPDATE_ADDRESSES	16

/**
 * This <code>EppCommandUpdateHost</code> class implements EPP Command Update
 * entity for EPP Host objects.
 *
 * @author Ning Zhang ning.zhang@neustar.com
 * @version $Revision: 1.1 $ $Date: 2005/12/06 20:11:35 $
 */
class EPP_EXPORT EppCommandUpdateHost : public EppCommandUpdate
{
private:
	DOMString                     name;
	ValueVectorOf<EppIpAddress> * addrAdded;
	ValueVectorOf<EppIpAddress> * addrRemoved;
	DOMString                     newName;

	/**
	 * Converts a list of IP addresses into XML
	 *
	 * @param doc  the XML <code>DOM_Element</code> object
	 * @param body the XML <code>DOM_Element</code> object to which the list
	 *             of IP addresses is appended
	 * @param list the list of IP addresses to be converted
	 */
	void addressToXML( DOM_Document& doc, DOM_Element& body, ValueVectorOf<EppIpAddress> * list );

	/**
	 * Converts a list of IP addresses from XML format
	 *
	 * @param root the XML <code>Node</code> object containing the list
	 *             of IP addresses 
	 * @param addressList the list of IP addresses to be stored
	 */
	void addressFromXML( const DOM_Node& root, ValueVectorOf<EppIpAddress> * addressList );

public:
	/**
	 * Creates an <code>EppCommandUpdateHost</code>
	 */
	EppCommandUpdateHost()
	{
		this->name        = null;
		this->addrAdded   = new ValueVectorOf<EppIpAddress>(MAX_NUM_OF_UPDATE_ADDRESSES);
		this->addrRemoved = new ValueVectorOf<EppIpAddress>(MAX_NUM_OF_UPDATE_ADDRESSES);
		this->newName     = null;
	};

	/**
	 * Creates an <code>EppCommandUpdateHost</code> given the name of the
	 * host
	 */
	EppCommandUpdateHost( DOMString name )
	{
		this->name        = name;
		this->addrAdded   = new ValueVectorOf<EppIpAddress>(MAX_NUM_OF_UPDATE_ADDRESSES);
		this->addrRemoved = new ValueVectorOf<EppIpAddress>(MAX_NUM_OF_UPDATE_ADDRESSES);
		this->newName     = null;
	};

	/**
	 * Creates an <code>EppCommandUpdateHost</code> given the name of the
	 * host with a client transaction id associated with operation
	 */
	EppCommandUpdateHost( DOMString name, DOMString xid )
	{
		this->name        = name;
		this->addrAdded   = new ValueVectorOf<EppIpAddress>(MAX_NUM_OF_UPDATE_ADDRESSES);
		this->addrRemoved = new ValueVectorOf<EppIpAddress>(MAX_NUM_OF_UPDATE_ADDRESSES);
		this->newName     = null;
		this->clTRID      = xid;
	};

	/**
	 * Destructor
	 */
	~EppCommandUpdateHost()
	{
		if( this->addrAdded != null )
		{
			delete this->addrAdded;
			this->addrAdded = null;
		}
		if( this->addrRemoved != null )
		{
			delete this->addrRemoved;
			this->addrRemoved = null;
		}
	};

	/**
	 * Returns the run-time type of an EppEntity object
	 */
	virtual int getEntityType()
	{
		return EppEntity::TYPE_EppCommandUpdateHost;
	};

	/**
	 * Gets the name of the host to be updated
	 */
	DOMString getName()
	{
		return this->name;
	};

	/**
	 * Sets the name of the host to be updated
	 */
	void setName( DOMString name )
	{
		this->name= name;
	};

	/**
	 * Gets the list of new IP addresses to be added to the host
	 */
	ValueVectorOf<EppIpAddress> * getAddressAdded()
	{
		return this->addrAdded;
	};

	/**
	 * Adds a new IP address to be associated with the host
	 */
	void addAddress( EppIpAddress& address )
	{
		this->addrAdded->addElement(address);
	};

	/**
	 * Gets the list of old IP addresses to be removed from the host
	 */
	ValueVectorOf<EppIpAddress> * getAddressRemoved()
	{
		return this->addrRemoved;
	};

	/*
	 * Removes an old IP address associated with the host
	 */
	void removeAddress( EppIpAddress& address )
	{
		this->addrRemoved->addElement(address);
	};

	/**
	 * Gets the new name for the host, or null if the name of the
	 * the host is not to be changed
	 */
	DOMString getNewName()
	{
		return this->newName;
	};

	/**
	 * Sets the new name for the host if the name of the
	 * the host needs to be changed
	 */
	void setNewName( DOMString name )
	{
		this->newName = name;
	};

	/**
	 * Converts the <code>EppCommandUpdateHost</code> object into 
	 * an XML element
	 *
	 * @param doc the XML <code>DOM_Element</code> object
	 * @param tag the tag/element name for the 
	 *            <code>EppCommandUpdateHost</code> object
	 *
	 * @return an <code>DOM_Element</code> object 
	 */
	DOM_Element toXML( DOM_Document& doc, const DOMString& tag );

	/**
	 * Converts an XML element into an <code>EppCommandUpdateHost</code>
	 * object. The caller of this method must make sure that the root node
	 * is of an EPP Command Update entity for an EPP Host object.
	 *
	 * @param root root node for an <code>EppCommandUpdate</code> object
	 *	     in XML format
	 *
	 * @return an <code>EppCommandUpdate</code> object, or null if the node
	 *	 is invalid
	 */
	static EppCommandUpdateHost * fromXML( const DOM_Node& root );
};

#endif     /* EPPCOMMANDUPDATEHOST_HPP */  /* } */
