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


#if ! defined(EPPGREETING_HPP)    /* { */
#define       EPPGREETING_HPP        1

#include <time.h>
#include "EppEntity.hpp"
#include "EppServiceMenu.hpp"

/**
 * This <code>EppGreeting</code> class implements EPP Greeting entity used
 * in the EPP Protocol initialization.
 *
 * @author Ning Zhang ning.zhang@neustar.com
 * @version $Revision: 1.1 $ $Date: 2005/12/06 20:11:35 $
 */
class EPP_EXPORT EppGreeting : public EppEntity
{
private:
	DOMString        svID;
	time_t           svDate;
	EppServiceMenu * svcMenu;

	/**
	 * Clones the service menu
	 */
	void cloneServiceMenu( EppServiceMenu& menu );

public:
	/**
	 * Creates an <code>EppGreeting</code> object with default setting
	 */
	EppGreeting()
	{
		this->svID = "Neustar EPP Server";
		this->svDate = time(0);
		this->svcMenu = new EppServiceMenu();
		this->svcMenu->addVersion("1.0");
		this->svcMenu->addLanguage("en-US");
		this->svcMenu->addService("contact");
		this->svcMenu->addService("host");
		this->svcMenu->addService("domain");
		this->svcMenu->addService("svcsub");
	};

	/**
	 * Creates an <code>EppGreeting</code> object, given a service
	 * identifier and service menu
	 *
	 * @param serviceId the identifier of the service provided
	 * @param serviceMenu the menu of the service provided
	 */
	EppGreeting( DOMString serviceId, EppServiceMenu& serviceMenu )
	{
		this->svID = serviceId;
		this->svDate = time(0);
		this->svcMenu = new EppServiceMenu();
		cloneServiceMenu(serviceMenu);
	};

	/**
	 * Destructor
	 */
	~EppGreeting()
	{
		if( this->svcMenu != null )
		{
			delete this->svcMenu;
			this->svcMenu = null;
		}
	};

	/**
	 * Gets the identifier of the service
	 */
	DOMString getServiceId()
	{
		return this->svID;
	};

	/**
	 * Sets the identifier of the service
	 */
	void setServiceId( DOMString serviceId )
	{
		this->svID = serviceId;
	};

	/**
	 * Gets the date associated with the service. The default value is the
	 * <code>time_t</code> value when the <code>EppGreeting</code> is
	 * created.
	 */
	time_t getServiceDate()
	{
		return this->svDate;
	};

	/**
	 * Sets the date associated with the service
	 */
	void setServiceDate( time_t serviceDate )
	{
		this->svDate = serviceDate;
	};

	/**
	 * Gets the menu of the service provided
	 */
	EppServiceMenu * getServiceMenu()
	{
		return this->svcMenu;
	};

	/**
	 * Sets the menu of the service provided
	 */
	void setServiceMenu( EppServiceMenu& serviceMenu )
	{
		cloneServiceMenu(serviceMenu);
	};

	/**
	 * Converts the <code>EppGreeting</code> object into an XML element
	 *
	 * @param doc the XML <code>DOM_Element</code> object
	 * @param tag the tag/element name for the <code>EppGreeting</code>
	 *            object
	 *
	 * @return an <code>DOM_Element</code> object
	 */
	DOM_Element toXML( DOM_Document& doc, const DOMString& tag );

	/**
	 * Converts an XML element into an <code>EppGreeting</code> object.
	 * The caller of this method must make sure that the root node is of
	 * the EPP addrType.
	 *
	 * @param root root node for an <code>EppGreeting</code> object
	 *             in XML format
	 *
	 * @return an <code>EppGreeting</code> object, or null if the node
	 *         is invalid
	 */
	static EppGreeting * fromXML( const DOM_Node& root );

	DOMString toString()
	{
		return EppEntity::toString(DOMString("greeting"));
	};
};

#endif     /* EPPGREETING_HPP */  /* } */
