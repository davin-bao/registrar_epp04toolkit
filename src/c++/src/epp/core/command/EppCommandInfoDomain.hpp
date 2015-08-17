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


#if ! defined(EPPCOMMANDINFODOMAIN_HPP)    /* { */
#define       EPPCOMMANDINFODOMAIN_HPP        1

#include "EppCommandInfo.hpp"

/**
 * This <code>EppCommandInfoDomain</code> class implements EPP Command Info
 * entity for EPP Domain objects.
 *
 * @author Ning Zhang ning.zhang@neustar.com
 * @version $Revision: 1.1 $ $Date: 2005/12/06 20:11:35 $
 */
class EPP_EXPORT EppCommandInfoDomain : public EppCommandInfo
{
private:
	DOMString name;

public:
	/**
	 * Creates an <code>EppCommandInfoDomain</code> object for
	 */
	EppCommandInfoDomain()
	{
		this->name = null;
	};

	/**
	 * Creates an <code>EppCommandInfoDomain</code> object for
	 * querying a domain object based on its name
	 */
	EppCommandInfoDomain( DOMString name )
	{
		this->name = name;
	};

	/**
	 * Creates an <code>EppCommandInfoDomain</code> object for
	 * querying a domain object based on its name, given a client
	 * transaction id associated with the operation
	 */
	EppCommandInfoDomain( DOMString name, DOMString xid )
	{
		this->name = name;
		this->clTRID = xid;
	};

	/**
	 * Destructor
	 */
	~EppCommandInfoDomain() {};

	/**
	 * Returns the run-time type of an EppEntity object
	 */
	virtual int getEntityType()
	{
		return EppEntity::TYPE_EppCommandInfoDomain;
	};

	/**
	 * Gets the name of the domain object to be queried
	 */
	DOMString getName()
	{
		return this->name;
	};

	/**
	 * Sets the name of the domain object to be queried
	 */
	void setName( DOMString name )
	{
		this->name = name;
	};

	/**
	 * Converts the <code>EppCommandInfoDomain</code> object into an XML
	 * element
	 *
	 * @param doc the XML <code>DOM_Element</code> object
	 * @param tag the tag/element name for the
	 *            <code>EppCommandInfoDomain</code> object
	 *
	 * @return an <code>DOM_Element</code> object
	 */
	DOM_Element toXML( DOM_Document& doc, const DOMString& tag );

	/**
	 * Converts an XML element into an <code>EppCommandInfoDomain</code>
	 * object. The caller of this method must make sure that the root node
	 * is of an EPP Command Info entity for EPP domain object.
	 *
	 * @param root root node for an <code>EppCommandInfoDomain</code>
	 *             object in XML format
	 *
	 * @return an <code>EppCommandInfoDomain</code> object, or null
	 *         if the node is invalid
	 */
	static EppCommandInfoDomain * fromXML( const DOM_Node& root );
};

#endif     /* EPPCOMMANDINFODOMAIN_HPP */  /* } */
