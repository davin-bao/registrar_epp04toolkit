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


#if ! defined(EPPCOMMANDUPDATECONTACT_HPP)    /* { */
#define       EPPCOMMANDUPDATECONTACT_HPP        1

#include "EppCommandUpdate.hpp"
#include "EppContactData.hpp"
#include "EppE164.hpp"
#include "EppAuthInfo.hpp"

/**
 * This <code>EppCommandUpdateContact</code> class implements EPP Command Update
 * entity for EPP Contact objects.
 *
 * @author Ning Zhang ning.zhang@neustar.com
 * @version $Revision: 1.1 $ $Date: 2005/12/06 20:11:35 $
 */
class EPP_EXPORT EppCommandUpdateContact : public EppCommandUpdate
{
private:
	DOMString        id;
	EppContactData * newAscii;
	EppContactData * newI15d;
	EppE164        * newVoice;
	EppE164        * newFax;
	DOMString        newEmail;
	EppAuthInfo    * newAuthInfo;

	/**
	 * Adds elements included in the &lt;chg&gt tag of the update command
	 * for a contact object
	 *
	 * @param root the root <code>Node</code> of the &lt;chg&gt; tag
	 */
	void addNewStuff( const DOM_Node& root );

public:
	/**
	 * Creates an <code>EppCommandUpdateContact</code>
	 */
	EppCommandUpdateContact()
	{
		this->id        = null;
		this->newAscii    = null;
		this->newI15d     = null;
		this->newVoice    = null;
		this->newFax      = null;
		this->newEmail    = null;
		this->newAuthInfo = null;
	};

	/**
	 * Creates an <code>EppCommandUpdateContact</code> given the id
	 * of the contact
	 */
	EppCommandUpdateContact( DOMString id )
	{
		this->id          = id;
		this->newAscii    = null;
		this->newI15d     = null;
		this->newVoice    = null;
		this->newFax      = null;
		this->newEmail    = null;
		this->newAuthInfo = null;
	};

	/**
	 * Creates an <code>EppCommandUpdateContact</code> given the id
	 * of the contact
	 */
	EppCommandUpdateContact( DOMString id, DOMString xid )
	{
		this->id          = id;
		this->newAscii    = null;
		this->newI15d     = null;
		this->newVoice    = null;
		this->newFax      = null;
		this->newEmail    = null;
		this->newAuthInfo = null;
		this->clTRID      = xid;
	};

	/**
	 * Destructor
	 */
	~EppCommandUpdateContact()
	{
		if( this->newAscii != null )
		{
			delete this->newAscii;
			this->newAscii = null;
		}
		if( this->newI15d != null )
		{
			delete this->newI15d;
			this->newI15d = null;
		}
		if( this->newVoice != null )
		{
			delete this->newVoice;
			this->newVoice = null;
		}
		if( this->newFax != null )
		{
			delete this->newFax;
			this->newFax = null;
		}
		if( this->newAuthInfo != null )
		{
			delete this->newAuthInfo;
			this->newAuthInfo = null;
		}
	};

	/**
	 * Returns the run-time type of an EppEntity object
	 */
	virtual int getEntityType()
	{
		return EppEntity::TYPE_EppCommandUpdateContact;
	};

	/**
	 * Gets the id of the contact to be updated
	 */
	DOMString getId()
	{
		return this->id;
	};

	/**
	 * Sets the id of the contact to be updated
	 */
	void setId( DOMString id )
	{
		this->id= id;
	};

	/**
	 * Gets the new contact data in ascii encoding, or null if not changed
	 */
	EppContactData * getNewAscii()
	{
		return this->newAscii;
	};

	/**
	 * Sets the new contact data in ascii encoding, or null if not changed
	 */
	void setNewAscii( EppContactData& ascii )
	{
		if( this->newAscii == null )
		{
			this->newAscii = new EppContactData();
		}
		*(this->newAscii) = ascii;
	};

	/**
	 * Gets the new contact data in native encoding, or null if not changed
	 */
	EppContactData * getNewI15d()
	{
		return this->newI15d;
	};

	/**
	 * Sets the new contact data in ascii encoding, or null if not changed
	 */
	void setNewI15d( EppContactData& i15d )
	{
		if( this->newI15d == null )
		{
			this->newI15d = new EppContactData();
		}
		*(this->newI15d) = i15d;
	};

	/**
	 * Gets the new voice phone number
	 */
	EppE164 * getNewVoice()
	{
		return this->newVoice;
	};

	/**
	 * Sets the new voice phone number
	 */
	void setNewVoice( DOMString voice )
	{
		EppE164 v(voice);
		this->setNewVoice(v);
	};

	/**
	 * Sets the new voice phone number
	 */
	void setNewVoice( DOMString voice, DOMString ext )
	{
		EppE164 v(voice, ext);
		this->setNewVoice(v);
	};

	/**
	 * Sets the new voice phone number
	 */
	void setNewVoice( EppE164& voice )
	{
		if( this->newVoice == null )
		{
			this->newVoice = new EppE164();
		}
		*(this->newVoice) = voice;
	};

	/**
	 * Gets the new fax number
	 */
	EppE164 * getNewFax()
	{
		return this->newFax;
	};

	/**
	 * Sets the new fax number
	 */
	void setNewFax( DOMString fax )
	{
		EppE164 f(fax);
		this->setNewFax(f);
	};

	/**
	 * Sets the new fax number
	 */
	void setNewFax( DOMString fax, DOMString ext )
	{
		EppE164 f(fax, ext);
		this->setNewFax(f);
	};

	/**
	 * Sets the new fax number
	 */
	void setNewFax( EppE164& fax )
	{
		if( this->newFax == null )
		{
			this->newFax = new EppE164();
		}
		*(this->newFax) = fax;
	};

	/**
	 * Gets the new email address of the contact, or null if not changed
	 */
	DOMString getNewEmail()
	{
		return this->newEmail;
	};

	/**
	 * Sets the new email address of the contact, or null if not changed
	 */
	void setNewEmail( DOMString email )
	{
		this->newEmail = email;
	};

	/*
	 * Gets the new authorization information for the contact, or null if
	 * the authorization information of the domain is not to be changed
	 */
	EppAuthInfo * getNewAuthInfo()
	{
		return this->newAuthInfo;
	};

	/**
	 * Sets the new authorization information for the contact if it needs
	 * to be changed
	 */
	void setNewAuthInfo( EppAuthInfo& authInfo )
	{
		if( this->newAuthInfo == null )
		{
			this->newAuthInfo = new EppAuthInfo();
		}
		*(this->newAuthInfo) = authInfo;
	};

	/**
	 * Converts the <code>EppCommandUpdateContact</code> object into 
	 * an XML element
	 *
	 * @param doc the XML <code>DOM_Element</code> object
	 * @param tag the tag/element name for the 
	 *            <code>EppCommandUpdateContact</code> object
	 *
	 * @return an <code>DOM_Element</code> object 
	 */
	DOM_Element toXML( DOM_Document& doc, const DOMString& tag );

	/**
	 * Converts an XML element into an <code>EppCommandUpdateDomain</code>
	 * object. The caller of this method must make sure that the root node
	 * is of an EPP Command Update entity for an EPP Contact object.
	 *
	 * @param root root node for an <code>EppCommandUpdateDomain</code>
	 *             object in XML format
	 *
	 * @return an <code>EppCommandUpdateDomain</code> object, or null
	 *         if the node is invalid
	 */
	static EppCommandUpdateContact * fromXML( const DOM_Node& root );
};

#endif     /* EPPCOMMANDUPDATECONTACT_HPP */  /* } */
