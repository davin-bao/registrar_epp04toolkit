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


#if ! defined(EPPCOMMANDUPDATEDOMAIN_HPP)    /* { */
#define       EPPCOMMANDUPDATEDOMAIN_HPP        1

#include "EppCommandUpdate.hpp"
#include "EppContactType.hpp"
#include "EppAuthInfo.hpp"

#define	MAX_NUM_OF_UPDATE_NAMESERVERS	16
#define	MAX_NUM_OF_UPDATE_CONTACTS	16
	
/**
 * This <code>EppCommandUpdateDomain</code> class implements EPP Command Update
 * entity for EPP Domain objects.
 *
 * @author Ning Zhang ning.zhang@neustar.com
 * @version $Revision: 1.1 $ $Date: 2005/12/06 20:11:35 $
 */
class EPP_EXPORT EppCommandUpdateDomain : public EppCommandUpdate
{
private:
	DOMString                       name;
	ValueVectorOf<DOMString>      * nsAdded;
	ValueVectorOf<DOMString>      * nsRemoved;
	ValueVectorOf<EppContactType> * contactAdded;
	ValueVectorOf<EppContactType> * contactRemoved;
	DOMString                       newRegistrant;
	EppAuthInfo                   * newAuthInfo;

	/**
	 * Converts a list of name servers into XML
	 *
	 * @param doc  the XML <code>DOM_Element</code> object
	 * @param body the XML <code>DOM_Element</code> object to which the list
	 *             of name servers is appended
	 * @param list the list of name servers to be converted
	 */
	void nameServerToXML( DOM_Document& doc, DOM_Element& body, ValueVectorOf<DOMString> * list );

	/**
	 * Converts a list of contacts into XML
	 *
	 * @param doc  the XML <code>DOM_Element</code> object
	 * @param body the XML <code>DOM_Element</code> object to which the list
	 *             of contacts is appended
	 * @param list the list of contacts to be converted
	 */
	void contactToXML( DOM_Document& doc, DOM_Element& body, ValueVectorOf<EppContactType> * list );

	/**
	 * Converts a list of name servers from XML format
	 *
	 * @param root the XML <code>Node</code> object containing the list
	 *             of name servers
	 * @param addressList the list of name servers to be stored
	 */
	void nameServerFromXML( const DOM_Node& root, ValueVectorOf<DOMString> * nameServerList );

	/**
	 * Converts a list of contacts from XML format
	 *
	 * @param root the XML <code>Node</code> object containing the list
	 *             of IP addresses 
	 * @param contactList the list of contacts to be stored
	 */
	void contactFromXML( const DOM_Node& root, ValueVectorOf<EppContactType> * contactList );

public:
	/**
	 * Creates an <code>EppCommandUpdateDomain</code>
	 */
	EppCommandUpdateDomain()
	{
		this->name           = null;
		this->nsAdded        = new ValueVectorOf<DOMString>(MAX_NUM_OF_UPDATE_NAMESERVERS);
		this->nsRemoved      = new ValueVectorOf<DOMString>(MAX_NUM_OF_UPDATE_NAMESERVERS);
		this->contactAdded   = new ValueVectorOf<EppContactType>(MAX_NUM_OF_UPDATE_CONTACTS);
		this->contactRemoved = new ValueVectorOf<EppContactType>(MAX_NUM_OF_UPDATE_CONTACTS);
		this->newRegistrant  = null;
		this->newAuthInfo    = null;
	};

	/**
	 * Creates an <code>EppCommandUpdateDomain</code> given the name of the
	 * domain
	 */
	EppCommandUpdateDomain( DOMString name )
	{
		this->name           = name;
		this->nsAdded        = new ValueVectorOf<DOMString>(MAX_NUM_OF_UPDATE_NAMESERVERS);
		this->nsRemoved      = new ValueVectorOf<DOMString>(MAX_NUM_OF_UPDATE_NAMESERVERS);
		this->contactAdded   = new ValueVectorOf<EppContactType>(MAX_NUM_OF_UPDATE_CONTACTS);
		this->contactRemoved = new ValueVectorOf<EppContactType>(MAX_NUM_OF_UPDATE_CONTACTS);
		this->newRegistrant  = null;
		this->newAuthInfo    = null;
	};

	/**
	 * Creates an <code>EppCommandUpdateDomain</code> given the name of the
	 * domain
	 */
	EppCommandUpdateDomain( DOMString name, DOMString xid )
	{
		this->name           = name;
		this->nsAdded        = new ValueVectorOf<DOMString>(MAX_NUM_OF_UPDATE_NAMESERVERS);
		this->nsRemoved      = new ValueVectorOf<DOMString>(MAX_NUM_OF_UPDATE_NAMESERVERS);
		this->contactAdded   = new ValueVectorOf<EppContactType>(MAX_NUM_OF_UPDATE_CONTACTS);
		this->contactRemoved = new ValueVectorOf<EppContactType>(MAX_NUM_OF_UPDATE_CONTACTS);
		this->newRegistrant  = null;
		this->newAuthInfo    = null;
		this->clTRID         = xid;
	};

	/**
	 * Destructor
	 */
	~EppCommandUpdateDomain()
	{
		if( this->nsAdded != null )
		{
			delete this->nsAdded;
			this->nsAdded = null;
		}
		if( this->nsRemoved != null )
		{
			delete this->nsRemoved;
			this->nsRemoved = null;
		}
		if( this->contactAdded != null )
		{
			delete this->contactAdded;
			this->contactAdded = null;
		}
		if( this->contactRemoved != null )
		{
			delete this->contactRemoved;
			this->contactRemoved = null;
		}
		if( this->newAuthInfo != null )
		{
			delete this->newAuthInfo;
			this->newAuthInfo = null;
		}
	};

	/**
	 * Returns the run-time type of an EppEntity object
	 */
	virtual int getEntityType()
	{
		return EppEntity::TYPE_EppCommandUpdateDomain;
	};

	/**
	 * Gets the name of the domain to be updated
	 */
	DOMString getName()
	{
		return this->name;
	};

	/**
	 * Sets the name of the domain to be updated
	 */
	void setName( DOMString& name )
	{
		this->name = name;
	};

	/**
	 * Gets the list of new name servers to be added to the domain
	 */
	ValueVectorOf<DOMString> * getNameServerAdded()
	{
		return this->nsAdded;
	};

	/**
	 * Adds a new name server to be associated with the domain
	 */
	void addNameServer( DOMString nameServer )
	{
		this->nsAdded->addElement(nameServer);
	};

	/**
	 * Gets the list of old name servers to be removed from the domain
	 */
	ValueVectorOf<DOMString> * getNameServerRemoved()
	{
		return this->nsRemoved;
	};

	/*
	 * Removes an old name server associated with the domain
	 */
	void removeNameServer( DOMString nameServer )
	{
		this->nsRemoved->addElement(nameServer);
	};

	/**
	 * Gets the list of new contacts to be added to the domain
	 */
	ValueVectorOf<EppContactType> * getContactAdded()
	{
		return this->contactAdded;
	};

	/**
	 * Adds a new contact to be associated with the domain
	 */
	void addContact( EppContactType& contact )
	{
		this->contactAdded->addElement(contact);
	};

	/**
	 * Gets the list of old contacts to be removed from the domain
	 */
	ValueVectorOf<EppContactType> * getContactRemoved()
	{
		return this->contactRemoved;
	};

	/*
	 * Removes an old contact associated with the domain
	 */
	void removeContact( EppContactType& contact )
	{
		this->contactRemoved->addElement(contact);
	};

	/**
	 * Gets the new registrant's contact id for the domain, or null if the
	 * registrant of the domain is not to be changed
	 */
	DOMString getNewRegistrant()
	{
		return this->newRegistrant;
	};

	/**
	 * Sets the new registrant's contact id for the domain if a new registrant
	 * claims the ownership of the domain
	 */
	void setNewRegistrant( DOMString registrant )
	{
		this->newRegistrant = registrant;
	};

	/**
	 * Gets the new authorization information for the domain, or null if
	 * the authorization information of the domain is not to be changed
	 */
	EppAuthInfo * getNewAuthInfo()
	{
		return this->newAuthInfo;
	};

	/**
	 * Sets the new authorization information for the domain if it needs
	 * to be changed
	 */
	void setNewAuthInfo( EppAuthInfo& authInfo )
	{
		if( this->newAuthInfo == null )
		{
			this->newAuthInfo = new EppAuthInfo();
		}
		*(this->newAuthInfo) = authInfo;
	};

	/**
	 * Converts the <code>EppCommandUpdateDomain</code> object into 
	 * an XML element
	 *
	 * @param doc the XML <code>DOM_Element</code> object
	 * @param tag the tag/element name for the 
	 *            <code>EppCommandUpdateDomain</code> object
	 *
	 * @return an <code>DOM_Element</code> object 
	 */
	DOM_Element toXML( DOM_Document& doc, const DOMString& tag );

	/**
	 * Converts an XML element into an <code>EppCommandUpdateDomain</code>
	 * object. The caller of this method must make sure that the root node
	 * is of an EPP Command Update entity for an EPP Domain object.
	 *
	 * @param root root node for an <code>EppCommandUpdate</code> object
	 *	     in XML format
	 *
	 * @return an <code>EppCommandUpdateDomain</code> object, or null
	 *         if the node is invalid
	 */
	static EppCommandUpdateDomain * fromXML( const DOM_Node& root );
};

#endif     /* EPPCOMMANDUPDATEDOMAIN_HPP */  /* } */
