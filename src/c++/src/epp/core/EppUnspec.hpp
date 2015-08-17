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


#if ! defined(EPPUNSPEC_HPP)    /* { */
#define       EPPUNSPEC_HPP        1

#include "EppEntity.hpp"

/**
 * The <code>EppUnspec</code> class implement EPP unspecType objects.
 *
 * @author Ning Zhang ning.zhang@neustar.com
 * @version $Revision: 1.1 $ $Date: 2005/12/06 20:11:35 $
 */
class EPP_EXPORT EppUnspec : public EppEntity
{
private:
	DOMString value;

public:
	/**
	 * Creates an <code>EppUnspec</code> object
	 */
	EppUnspec()
	{
		value = null;
	};

	/**
	 * Creates an <code>EppUnspec</code> object with a value
	 */
	EppUnspec( DOMString value )
	{
		this->value = value;
	};

	/**
	 * Destructor
	 */
	~EppUnspec() {};

	/**
	 * Gets the value associated with <code>EppUnspec</code> object
	 */
	DOMString getValue()
	{
		return this->value;
	};

	/**
	 * Sets the value associated with <code>EppUnspec</code> object
	 */
	void setValue( const DOMString& value )
	{
		this->value = value;
	};

	/**
	 * Converts the <code>EppUnspec</code> object into an XML element
	 *
	 * @param doc the XML <code>DOM_Element</code> object
	 * @param tag the tag/element name for the <code>EppUnspec</code> object
	 *
	 * @return an <code>DOM_Element</code> object
	 */
	DOM_Element toXML( DOM_Document &doc, const DOMString &tag );

	/**
	 * Converts an XML element into an <code>EppUnspec</code> object.
	 * The caller of this method must make sure that the root node is of
	 * EPP unspecType
	 *
	 * @param root root node for an <code>EppUnspec</code> object in XML format
	 *
	 * @return an <code>EppUnspec</code> object, or null if the node is invalid
	 */
	static EppUnspec * fromXML( const DOM_Node &root );

	DOMString toString()
	{
		return EppEntity::toString(DOMString("unspec"));
	};
};

#endif     /* EPPUNSPEC_HPP */  /* } */
