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


#if ! defined(EPPRESPONSEDATACHECK_HPP)    /* { */
#define       EPPRESPONSEDATACHECK_HPP        1

#include "EppResponseData.hpp"
#include <util/ValueVectorOf.hpp>
#include <util/KeyValuePair.hpp>

#define	MAX_NUM_OF_CHECKS	16

/**
 * This <code>EppResponseDataCheck</code> class implements EPP Response
 * Data entity for EPP Command Check.
 *
 * @author Ning Zhang ning.zhang@neustar.com
 * @version $Revision: 1.1 $ $Date: 2005/12/06 20:11:35 $
 */
class EPP_EXPORT EppResponseDataCheck : public EppResponseData
{
protected:
	/**
	 * A vector for storing key and value pairs
	 */
	ValueVectorOf<KeyValuePair<DOMString, DOMString> > * hashMap;

	/**
	 * Converts shared <code>EppResponseDataCheck</code> component into
	 * XML elements
	 *
	 * @param doc the XML <code>DOM_Element</code> object
	 * @param body the XML <code>DOM_Element</code> to be attached
	 */
	void toXMLCommon( DOM_Document& doc, DOM_Element& body );

	/**
	 * Converts shared <code>EppResponseDataCheck</code> components from
	 * XML format.
	 * 
	 * @param root root node for the list of shared components
	 */
	void fromXMLCommon( const DOM_Node& root );

public:
	/**
	 * Status for checking the existance of an object in the registry
	 */
	static const char * UNKNOWN;
	/**
	 * Status for checking the existance of an object in the registry
	 */
	static const char * FOUND;
	/**
	 * Status for checking the existance of an object in the registry
	 */
	static const char * NOT_FOUND;

	/**
	 * Constructor
	 */
	EppResponseDataCheck()
	{
		this->hashMap = new ValueVectorOf<KeyValuePair<DOMString, DOMString> >(MAX_NUM_OF_CHECKS);
	};

	/**
	 * Destructor
	 */
	virtual ~EppResponseDataCheck()
	{
		if( this->hashMap != null )
		{
			delete this->hashMap;
			this->hashMap = null;
		}
	};

	/**
	 * Returns the run-time type of an EppEntity object
	 */
	virtual int getEntityType()
	{
		return EppEntity::TYPE_EppResponseDataCheck;
	};

	/**
	 * Gets the check result list associated with the result data of
	 * the check command
	 *
	 * @note this method is different from the Java API in which as
	 *       a hash table is returned instead of a vector.
	 */
	ValueVectorOf<KeyValuePair<DOMString, DOMString> > * getHashMap()
	{
		return this->hashMap;
	};

	/**
	 * Adds an entry into the <code>HashMap</code> for indicating if the
	 * object exists in the registry or not
	 *
	 * @param id   The Id associated with an EPP object, ROID for a contact
	 *             object, domain name for a domain object, host name for
	 *             a host object
	 * @param flag one of the <code>FOUND</code>, <code>NOT_FOUND</code>,
	 *             <code>UNKNWON</code>, indicating if the object exists in
	 *             the registry or not, or the existance is unknown
	 */
	void add( DOMString id, DOMString flag )
	{
		KeyValuePair<DOMString, DOMString> v(id, flag);
		this->hashMap->addElement(v);
	};

	/**
	 * Checks if an object id is in the <code>HashMap</code>
	 *
	 * @return one of the <code>FOUND</code>, <code>NOT_FOUND</code>,
	 *         <code>UNKNWON</code>
	 */
	DOMString check( DOMString id );
};

#endif     /* EPPRESPONSEDATACHECK_HPP */  /* } */
