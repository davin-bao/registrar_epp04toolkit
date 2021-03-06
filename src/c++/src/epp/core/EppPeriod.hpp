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


#if ! defined(EPPPERIOD_HPP)    /* { */
#define       EPPPERIOD_HPP        1

#include "EppEntity.hpp"

/**
 * This <code>EppPeriod</code> class implements EPP Domain periodType entity.
 *
 * @author Ning Zhang ning.zhang@neustar.com
 * @version $Revision: 1.1 $ $Date: 2005/12/06 20:11:35 $
 */
class EPP_EXPORT EppPeriod : public EppEntity
{
private:
	int  value;
	char unit;

public:
	/**
	 * Period unit for year ('y')
	 */
	static const char UNIT_YEAR;
	/**
	 * Period unit for month ('m')
	 */
	static const char UNIT_MONTH;

	/**
	 * Creates an <code>EppPeriod</code> object, with default value
	 * 1 and unit of 'm'
	 */
	EppPeriod()
	{
		this->value = 1;
		this->unit  = UNIT_YEAR;
	};

	/**
	 * Creates an <code>EppPeriod</code> object
	 */
	EppPeriod( int value, char unit )
	{
		this->value = value;
		this->unit  = unit;
	};

	/**
	 * Destructor
	 */
	~EppPeriod() {};

	/**
	 * Gets the value of the period
	 */
	int getValue()
	{
		return this->value;
	};

	/**
	 * Sets the value of the period
	 */
	void setValue( int value )
	{
		this->value = value;
	};

	/**
	 * Gets the unit of the period
	 */
	char getUnit()
	{
		return this->unit;
	};

	/**
	 * Sets the unit of the period, either 'y' for year or 'm' for month
	 */
	void setUnit( char unit )
	{
		this->unit = unit;
	};

	/**
	 * Converts the <code>EppPeriod</code> object into an XML element
	 *
	 * @param doc the XML <code>DOM_Element</code> object
	 * @param tag the tag/element name for the <code>EppPeriod</code> object
	 *
	 * @return an <code>DOM_Element</code> object
	 */
	DOM_Element toXML( DOM_Document& doc, const DOMString& tag );

	/**
	 * Converts an XML element into an <code>EppPeriod</code> object.
	 * The caller of this method must make sure that the root node is of
	 * the EPP Period type.
	 *
	 * @param root root node for an <code>EppPeriod</code> object
	 *             in XML format
	 *
	 * @return an <code>EppPeriod</code> object, or null if the node
	 *         is invalid
	 */
	static EppPeriod * fromXML( const DOM_Node& root );

	DOMString toString()
	{
		return EppEntity::toString(DOMString("period"));
	};
};

#endif     /* EPPPERIOD_HPP */  /* } */
