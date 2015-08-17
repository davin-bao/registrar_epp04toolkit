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


#if ! defined(EPPCOMMANDLOGIN_HPP)    /* { */
#define       EPPCOMMANDLOGIN_HPP        1

#include "EppCommand.hpp"
#include "EppServiceMenu.hpp"

/**
 * This <code>EppCommandLogin</code> class implements EPP Command Login
 * entity.
 *
 * @author Ning Zhang ning.zhang@neustar.com
 * @version $Revision: 1.1 $ $Date: 2005/12/06 20:11:35 $
 */
class EPP_EXPORT EppCommandLogin : public EppCommand
{
private:
	EppServiceMenu * svcs;

public:
	/**
	 * Creates an <code>EppCommandLogin</code> object
	 */
	EppCommandLogin()
	{
		this->svcs = null;
	};

	/**
	 * Creates an <code>EppCommandLogin</code> object
	 *
	 * @param serviceMenu the menu of services to be supported
	 */
	EppCommandLogin( EppServiceMenu& serviceMenu )
	{
		this->svcs = null;
		setServiceMenu(serviceMenu);
	};

	/**
	 * Destructor
	 */
	~EppCommandLogin()
	{
		if( this->svcs != null )
		{
			delete this->svcs;
			this->svcs = null;
		}
	};

	/**
	 * Returns the run-time type of an EppEntity object
	 */
	virtual int getEntityType()
	{
		return EppEntity::TYPE_EppCommandLogin;
	};

	/**
	 * Gets the menu of services to be supported
	 */
	EppServiceMenu * getServiceMenu()
	{
		return this->svcs;
	};

	/**
	 * Sets the menu of services to be supported
	 */
	void setServiceMenu( EppServiceMenu& serviceMenu );

	/**
	 * Converts the <code>EppCommandLogin</code> object into an XML element
	 *
	 * @param doc the XML <code>DOM_Element</code> object
	 * @param tag the tag/element name for the <code>EppCommandLogin</code>
	 *            object
	 *
	 * @return an <code>DOM_Element</code> object
	 */
	DOM_Element toXML( DOM_Document& doc, const DOMString& tag );

	/**
	 * Converts an XML element into an <code>EppCommandLogin</code> object.
	 * The caller of this method must make sure that the root node is of an
	 * EPP Command Create entity.
	 *
	 * @param root root node for an <code>EppCommandLogin</code> object
	 *             in XML format
	 *
	 * @return an <code>EppCommandLogin</code> object, or null if the node
	 *         is invalid
	 */
	static EppCommandLogin * fromXML( const DOM_Node& root );

	DOMString toString()
	{
		return EppEntity::toString(DOMString("login"));
	};
};

#endif     /* EPPCOMMANDLOGIN_HPP */  /* } */
