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


#if ! defined(EPPSTATUS_HPP)    /* { */
#define       EPPSTATUS_HPP        1

#include "EppEntity.hpp"

/**
 * This <code>EppStatus</code> class implements EPP Status entity. Different EPP
 * objects have different status values:
 *
 * <UL>
 * <LI><B>EPP Contact Object</B><UL>
 *     <LI>clientDeleteProhibited</LI>
 *     <LI>clientTransferProhibited</LI>
 *     <LI>clientUpdateProhibited</LI>
 *     <LI>linked</LI>
 *     <LI>ok</LI>
 *     <LI>pendingDelete</LI>
 *     <LI>pendingTransfer</LI>
 *     <LI>serverDeleteProhibited</LI>
 *     <LI>serverTransferProhibited</LI>
 *     <LI>serverUpdateProhibited</LI>
 *     </UL></LI>
 * <LI><B>EPP Domain Object</B><UL>
 *     <LI>clientDeleteProhibited</LI>
 *     <LI>clientHold</LI>
 *     <LI>clientRenewProhibited</LI>
 *     <LI>clientTransferProhibited</LI>
 *     <LI>clientUpdateProhibited</LI>
 *     <LI>inactive</LI>
 *     <LI>ok</LI>
 *     <LI>pendingDelete</LI>
 *     <LI>pendingTransfer</LI>
 *     <LI>pendingVerification</LI>
 *     <LI>serverDeleteProhibited</LI>
 *     <LI>serverHold</LI>
 *     <LI>serverRenewProhibited</LI>
 *     <LI>serverTransferProhibited</LI>
 *     <LI>serverUpdateProhibited</LI>
 *     </UL></LI>
 * <LI><B>EPP Host Object</B><UL>
 *     <LI>clientDeleteProhibited</LI>
 *     <LI>clientUpdateProhibited</LI>
 *     <LI>linked</LI>
 *     <LI>ok</LI>
 *     <LI>pendingDelete</LI>
 *     <LI>pendingTransfer</LI>
 *     <LI>serverDeleteProhibited</LI>
 *     <LI>serverUpdateProhibited</LI>
 *     </UL></LI>
 * </UL>
 *
 * @author Ning Zhang ning.zhang@neustar.com
 * @version $Revision: 1.1 $ $Date: 2005/12/06 20:11:35 $
 */
class EPP_EXPORT EppStatus : public EppEntity
{
private:
	DOMString message;
	DOMString s;
	DOMString lang;

public:
	/**
	 * Creates an <code>EppStatus</code> object, with default status
	 * as "ok" and language as "en"
	 */
	EppStatus()
	{
		this->s = DOMString("ok");
		this->lang = null;
		this->message = null;
	};

	/**
	 * Creates an <code>EppStatus</code> object with a status code
	 */
	EppStatus( DOMString status )
	{
		this->s = status;
		this->lang = null;
		this->message = null;
	};

	/**
	 * Creates an <code>EppStatus</code> object with a status code,
	 * and a descriptive message
	 */
	EppStatus( DOMString status, DOMString lang, DOMString message )
	{
		this->s = status;
		this->lang = lang;
		this->message = message;
	};

	/**
	 * Destructor
	 */
	~EppStatus() {};

	/**
	 * Gets the description message associated with the
	 * <code>EppStatus</code> object
	 */
	DOMString getMessage()
	{
		return this->message;
	};

	/**
	 * Sets the description message associated with the
	 * <code>EppStatus</code> object
	 */
	void setMessage( DOMString message )
	{
		this->message = message;
	};

	/**
	 * Gets the status code string
	 */
	DOMString getStatus()
	{
		return this->s;
	};

	/**
	 * Sets the status code string
	 */
	void setStatus( DOMString status )
	{
		this->s = status;
	};

	/**
	 * Gets the language for encoding the description message
	 */
	DOMString getLanguage()
	{
		return this->lang;
	};

	/**
	 * Sets the language for encoding the description message
	 */
	void setLanguage( DOMString language )
	{
		this->lang = language;
	};

	/**
	 * Converts the <code>EppStatus</code> object into an XML element
	 *
	 * @param doc the XML <code>DOM_Element</code> object
	 * @param tag the tag/element name for the <code>EppStatus</code> object
	 *
	 * @return an <code>DOM_Element</code> object
	 */
	DOM_Element toXML( DOM_Document& doc, const DOMString& tag );

	/**
	 * Converts an XML element into an <code>EppStatus</code> object.
	 * The caller of this method must make sure that the root node is of
	 * the EPP Status type.
	 *
	 * @param root root node for an <code>EppStatus</code> object
	 *             in XML format
	 *
	 * @return an <code>EppStatus</code> object, or null if the node
	 *         is invalid
	 */
	static EppStatus * fromXML( const DOM_Node& root );

	DOMString toString()
	{
	   return EppEntity::toString(DOMString("status"));
	};
};

#endif     /* EPPSTATUS_HPP */  /* } */
