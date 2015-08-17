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

#if ! defined(EPPADDRESS_HPP)    /* { */
#define       EPPADDRESS_HPP        1

#include "EppEntity.hpp"

#define	MAX_NUM_OF_STREETS	3

/**
 * This <code>EppAddress</code> class implements EPP Address entity used in
 * the EPP Contact objects.
 *
 * @author Ning Zhang ning.zhang@neustar.com
 * @version $Revision: 1.1 $ $Date: 2005/12/06 20:11:35 $
 */
class EPP_EXPORT EppAddress : public EppEntity
{
private:
	DOMString street[MAX_NUM_OF_STREETS];
	DOMString city;
	DOMString sp;
	DOMString pc;
	DOMString cc;

public:
	/**
	 * Creates an <code>EppAddress</code> object without any contents
	 */
	EppAddress();

	/**
	 * Creates an <code>EppAddress</code> object without street addresses
	 */
	EppAddress( DOMString city, DOMString sp, DOMString pc, DOMString cc );

	/**
	 * Creates an <code>EppAddress</code> object with one street address
	 */
	EppAddress( DOMString street, DOMString city, DOMString sp, DOMString pc, DOMString cc );

	/**
	 * Creates an <code>EppAddress</code> object with full address information
	 */
	EppAddress( DOMString street[], DOMString city, DOMString sp, DOMString pc, DOMString cc );

	/**
	 * Destructor
	 */
	~EppAddress() {};

	/**
	 * Gets the streets lines stored in a DOMString array
	 */
	DOMString * getStreet()
	{
		return this->street;
	};

	/**
	 * Sets the street lines stored in a string array
	 */
	void setStreet( DOMString street[] );

	/**
	 * Sets the street line, given an line index
	 */
	void setStreet( int index, DOMString street );

	/**
	 * Gets the city string
	 */
	DOMString getCity()
	{
		return this->city;
	};

	/**
	 * Sets the city string
	 */
	void setCity( DOMString city )
	{
		this->city = city;
	};

	/**
	 * Gets the province or state string
	 */
	DOMString getState()
	{
		return this->sp;
	};

	/**
	 * Sets the province or state string
	 */
	void setState( DOMString sp )
	{
		this->sp = sp;
	};

	/**
	 * Gets the postal code
	 */
	DOMString getPostalCode()
	{
		return this->pc;
	};

	/**
	 * Sets the postal code
	 */
	void setPostalCode( DOMString pc )
	{
		this->pc = pc;
	};

	/**
	 * Gets the country code
	 */
	DOMString getCountryCode()
	{
		return this->cc;
	};

	/**
	 * Sets the country code
	 */
	void setCountryCode( DOMString cc )
	{
		this->cc = cc;
	};

	/**
	 * Checks if an address is empty
	 */
	bool isNull()
	{
		for( int i = 0; i < MAX_NUM_OF_STREETS; i++ )
		{
			if( this->street[i] != null )
			{
				return false;
			}
		}
		if( this->city != null )
		{
			return false;
		}
		if( this->sp != null )
		{
			return false;
		}
		if( this->pc != null )
		{
			return false;
		}
		if( this->cc != null )
		{
			return false;
		}
		return true;
	};

	/**
	 * Converts an XML element into an <code>EppAddress</code> object.
	 * The caller of this method must make sure that the root node is of
	 * the EPP addrType.
	 *
	 * @param root root node for an <code>EppAddress</code> object in XML format
	 *
	 * @return an <code>EppAddress</code> object, or null if the node is invalid
         */
	static EppAddress * fromXML( const DOM_Node &root );

	/**
	 * Converts the <code>EppAddress</code> object into an XML element
	 *
	 * @param doc the XML <code>DOM_Element</code> object
	 * @param tag the tag/element name for the <code>EppAddress</code> object
	 *
	 * @return an <code>DOM_Element</code> object
	 */
	DOM_Element toXML( DOM_Document& doc, const DOMString& tag );

	/**
	 * Convert an EppAddress into XML an string, with its default tag name
	 */
	DOMString toString()
	{
		return EppEntity::toString(DOMString("address"));
	};
};

#endif     /* EPPADDRESS_HPP */  /* } */
