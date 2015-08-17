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
#include <stdio.h>
#include <stdlib.h>
#include "EppPeriod.hpp"
#include "EppUtil.hpp"

const char EppPeriod::UNIT_YEAR  = 'y';
const char EppPeriod::UNIT_MONTH = 'm';

DOM_Element EppPeriod::toXML( DOM_Document& doc, const DOMString& tag )
{
	char buf[32];
	buf[0] = unit;
	buf[1] = '\0';
	DOM_Element body = doc.createElement(tag);
	body.setAttribute("unit", buf);
	(void) sprintf(buf, "%d", value);
	body.appendChild(doc.createTextNode(buf));

	return body;
}

EppPeriod * EppPeriod::fromXML( const DOM_Node& root )
{
	DOM_Element * elm = (DOM_Element *) &root;
	DOMString value = EppUtil::getText(root);
	DOMString unit = elm->getAttribute("unit");

	if(    (value != null) && (value.length() > 0)
	    && (unit  != null) && (unit.length()  > 0) )
	{
		char * p = value.transcode();
		int val = atoi(p);
		delete [] p;
		return new EppPeriod(val, unit.charAt(0));
	}

	return null;
}
