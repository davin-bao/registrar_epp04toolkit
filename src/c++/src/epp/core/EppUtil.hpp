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


#if ! defined(EPPUTIL_HPP)    /* { */
#define       EPPUTIL_HPP        1

#include <time.h>
#include <dom/DOM.hpp>

#define MAX_VERSION_LENGTH	20

class EPP_EXPORT EppUtil
{
private:
	static char version[MAX_VERSION_LENGTH];

public:
	/**
	 * Sets the EPP XSD file version. The default value is "1.0",
	 * for EPPSchema datedon June 29, 2001.
	 */
	static void setEppVersion( const char * eppVersion );

	/**
	 * Gets the EPP XSD file version.
	 *
	 * @note value returned from this method is pointing to an internal
	 *       buffer, so there is no need to free it
	 */
	static const char * getEppVersion();

	/**
	 * Creates an <code>DOM_ElementNSImpl</code> object inside a
	 * <code>DOM_Element</code> object. The namespace associated with the
	 * object is specific to EPP.
	 *
	 * @param doc <code>DOM_Element</code> object in which the new element
	 *            to be created.
	 * @param ns  The namespace of the new element to be created.
	 * @param tag The tag name of the new element to be created.
	 *
	 * @return an <code>DOM_ElementNSImpl</code> object
	 */
	static DOM_Element createElementNS( DOM_Document& doc, const DOMString ns, const DOMString tag );

	/**
	 * Creates an <code>DOM_ElementNSImpl</code> object inside a
	 * <code>DOM_Element</code> object. The namespace associated with the
	 * object is specific to EPP.
	 *
	 * @param doc <code>DOM_Document</code> object in which the new element to be
	 *            created.
	 * @param ns  The namespace of the new element to be created.
	 * @param tag The tag name of the new element to be created.
	 * @param flag The flag indicating if the default namespace is needed.
	 *
	 * @return an <code>DOM_ElementNSImpl</code> object
	 */
	static DOM_Element createElementNS( DOM_Document& doc, const DOMString ns, const DOMString tag, bool flag );

	/**
	 * Creates an <code>DOM_ElementNSImpl</code> object inside a
	 * <code>Document</code> object. The namespace associated with the
	 * object is specific to an <I>unspec</I> object in an
	 * <code>EppServiceMenu</code> object.
	 *
	 * @param doc <code>DOM_Document</code> object in which the new element to be
	 *            created.
	 * @param unspec The string containing the information about the
	 *        <I>unspec</I> object with three tokens: name, uri, schema. For
	 *        example: "obj1ext http://custom/obj1ext-1.0 obj1ext-1.0.xsd"
	 * @param tag The tag name of the new element to be created.
	 * @param flag The flag indicating if the default namespace is needed.
	 *
	 * @return an <code>DOM_Element</code> object, or null if the
	 *         <code>unspec</code> parameter is not valid.
	 */
	static DOM_Element createElementNSUnspec( DOM_Document& doc, const DOMString unspec, const DOMString tag, bool flag );

	/**
	 * Creates a <code>DOM_Text</code> node for converting a
	 * <code>time_t</code> value into a string of XML timeInstant type.
	 *
	 * @param doc <code>DOM_Element</code> object in which the new element
	 *            to be created.
	 * @param cal The <code>time_t</code> to be converted into a XML
	 *            <code>DOM_Text</code> node.
	 *
	 * @note  the <code>time_t</code> value should be GMT.
	 */
	static DOM_Text createTextNode( DOM_Document& doc, const time_t cal );

	/**
	 * Creates a <code>DOM_Text</code> node for converting a
	 * <code>time_t</code> value into a string of XML timeInstant
	 * type or XML date type.
	 *
	 * @param doc <code>DOM_Element</code> object in which the new element
	 *            to be created.
	 * @param cal The <code>time_t</code> value to be converted into a XML
	 *            <code>Text</code> node.
	 * @param dateOnly true if the format is XML date type, or false
	 *                 if the format is XML timeInstant type
	 *
	 * @note  the <code>time_t</code> value should be GMT.
	 */
	static DOM_Text createTextNode( DOM_Document& doc, const time_t cal, bool dateOnly );

	/**
	 * Gets the text string associated with a node
	 *
	 * @param root <code>Node</code> object from which text to be extracted.
	 *
	 * @return a string associated with the node
	 */
	static DOMString getText( const DOM_Node &root );

	/**
	 * Gets the text string associated with a node as a <code>bool</code> value
	 *
	 * @param root <code>Node</code> object from which text to be extracted.
	 *
	 * @return a string associated with the node
	 */
	static bool getTextAsBool( const DOM_Node &root );

	/**
	 * Converts a text string associated with a node into a
	 * <code>time_t</code> value in GMT
	 *
	 * @param root <code>Node</code> object from which text to be extracted.
	 *
	 * @return a <code>time_t</code> value, or 0 if the text string is
	 *         not a valid XML timeInstant string
	 */
	static time_t getDate( const DOM_Node& root );

	/**
	 * Converts a text string associated with a node into a
	 * <code>time_t</code> value in GMT
	 *
	 * @param root <code>Node</code> object from which text to be extracted.
	 * @param dateOnly true for parsing the string in XML date format, or
	 *                 false for parsing the string in XML timeInstant
	 *                 format
	 *
	 * @return a <code>time_t</code> value, or 0 if the text string is
	 *         not a valid XML timeInstant/date string
	 */
	static time_t getDate( const DOM_Node& root, bool dateOnly );

	/**
	 * Converts a string into a <code>time_t</code> value in GMT
	 *
	 * @param buf C string containing the date representation
	 * @param dateOnly true for parsing the string in XML date format, or
	 *                 false for parsing the string in XML timeInstant
	 *                 format
	 *
	 * @return a <code>time_t</code> value, or 0 if the string is
	 *         not a valid XML timeInstant/date string
	 */
	static time_t getDate( const char *buf, bool dateOnly );

	/**
	 * Converts a <code>DOM_Element</code> into a formated XML string.
	 *
	 * @param doc <code>DOM_Element</code> to be converted into a string.
	 *
	 * @return a string representing the formated XML document
	 */
	static DOMString toString( const DOM_Document &doc );

	/**
	 * Sleeps for the specified time period in milliseconds.
	 *
	 * @param milliseconds number of milliseconds to sleep for.
	 */
	static void msSleep(unsigned int milliseconds);
};

#endif     /* EPPUTIL_HPP */  /* } */
