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


#if ! defined(EPPSERVICEMENU_HPP)    /* { */
#define       EPPSERVICEMENU_HPP        1

#include <util/ValueVectorOf.hpp>
#include "EppEntity.hpp"

#define	MAX_NUM_OF_VERSIONS	5
#define	MAX_NUM_OF_SERVICES	10
#define	MAX_NUM_OF_LANGUAGES	20
#define	MAX_NUM_OF_UNSPECS	10

/**
 * This <code>EppServiceMenu</code> class implements EPP svcMenuType entity.
 *
 * @author Ning Zhang ning.zhang@neustar.com
 * @version $Revision: 1.1 $ $Date: 2005/12/06 20:11:35 $
 */
class EPP_EXPORT EppServiceMenu : public EppEntity
{
protected:
	/**
	 * The version list of the EPP Service Menu
	 */
	ValueVectorOf<DOMString> * version;
	/**
	 * The language list of the EPP Service Menu
	 */
	ValueVectorOf<DOMString> * lang;
	/**
	 * The standard object list of the EPP Service Menu
	 */
	ValueVectorOf<DOMString> * svc;
	/**
	 * The <I>unspec</I> object list of the EPP Service Menu. Each entry
	 * contains three tokens: name, url, and schema file name.
	 * For example: "obj1ext http://custom/obj1ext-1.0 obj1ext-1.0.xsd"
	 */
	ValueVectorOf<DOMString> * unspec;

public:
	/**
	 * Creates an <code>EppServiceMenu</code> object
	 */
	EppServiceMenu()
	{
		this->version = new ValueVectorOf<DOMString>(MAX_NUM_OF_VERSIONS);
		this->lang    = new ValueVectorOf<DOMString>(MAX_NUM_OF_LANGUAGES);
		this->svc     = new ValueVectorOf<DOMString>(MAX_NUM_OF_SERVICES);
		this->unspec  = new ValueVectorOf<DOMString>(MAX_NUM_OF_UNSPECS);
	};

	/**
	 * Destructor
	 */
	~EppServiceMenu()
	{
		if( this->version != null )
		{
			delete this->version;
		}
		if( this->lang != null )
		{
			delete this->lang;
		}
		if( this->svc != null )
		{
			delete this->svc;
		}
		if( this->unspec != null )
		{
			delete this->unspec;
		}
		this->version = null;
		this->lang    = null;
		this->svc     = null;
		this->unspec  = null;
	};

	/**
	 * Returns a <code>Vector</code> containing all version numbers
	 * supported by the EPP server
	 */
	ValueVectorOf<DOMString> * getVersion()
	{
		return this->version;
	};

	/**
	 * Adds a version number to the list of versions supported by the
	 * EPP server
	 */
	void addVersion( DOMString version )
	{
		this->version->addElement(version);
	};

	/**
	 * Returns a <code>Vector</code> containing all languages supported
	 * by the Epp server
	 */
	ValueVectorOf<DOMString> * getLanguage()
	{
		return this->lang;
	};

	/**
	 * Adds a language to the list of languages supported by the
	 * EPP server
	 */
	void addLanguage( DOMString language )
	{
		this->lang->addElement(language);
	};

	/**
	 * Returns a <code>Vector</code> containing the name space and schema
	 * location of all objects supported by the EPP server
	 */
	ValueVectorOf<DOMString> * getService()
	{
		return this->svc;
	};

	/**
	 * Adds an object name to the list of all objects supported by
	 * the EPP server
	 */
	void addService( DOMString service )
	{
		this->svc->addElement(service);
	};

	/**
	 * Returns a <code>Vector</code> containing the name space and schema
	 * location of all <I>unspec</I> objects supported by the EPP server.
	 * Each entry in the vector is a string containing three tokens:
	 * three tokens: name, url, and schema file name. For example:
	 * "obj1ext http://custom/obj1ext-1.0 obj1ext-1.0.xsd"
	 */
	ValueVectorOf<DOMString> * getUnspec()
	{
		return this->unspec;
	};

	/**
	 * Adds an <I>unspec</I> object to the list of all <I>unspec</I>
	 * objects supported by the EPP server
	 *
	 * @param name the name of the object
	 * @param uri the uri of the object
	 * @param schema the XML schema defining the object
	 *
	 * @note if any of the parameters is null, empty, or containing spaces
	 *       no action will be taken
	 */
        void addUnspec( DOMString name, DOMString uri, DOMString schema );

	/**
	 * Converts the <code>EppServiceMenu</code> object into an XML element
	 *
	 * @param doc the XML <code>DOM_Element</code> object
	 * @param tag the tag/element name for the <code>EppServiceMenu</code>
	 *            object
	 *
	 * @return an <code>DOM_Element</code> object
	 */
	DOM_Element toXML( DOM_Document& doc, const DOMString& tag );

	/**
	 * Converts an XML element into an <code>EppServiceMenu</code> object.
	 * The caller of this method must make sure that the root node is of
	 * the EPP addrType.
	 *
	 * @param root root node for an <code>EppServiceMenu</code> object
	 *             in XML format
	 *
	 * @return an <code>EppServiceMenu</code> object, or null if the node
	 *         is invalid
	 */
	static EppServiceMenu * fromXML( const DOM_Node& root );

	DOMString toString()
	{
		return EppEntity::toString(DOMString("svcMenu"));
	};
};

#endif     /* EPPSERVICEMENU_HPP */  /* } */
