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
package com.neulevel.epp.core.response;

import org.w3c.dom.*;
import com.neulevel.epp.core.*;

/**
 * This <code>EppResponseData</code> class implements EPP Response Data entity.
 *
 * @author Ning Zhang ning.zhang@neustar.com
 * @version $Revision: 1.1 $ $Date: 2005/12/06 20:11:35 $
 */
abstract public class EppResponseData extends EppEntity
{
	/**
	 * Converts an XML element into an <code>EppResponseData</code> object.
	 * The caller of this method must make sure that the root node is the
	 * resData element of EPP responseType
	 *
	 * @param root root node for an <code>EppResponseData</code> object in
	 *             XML format
	 *
	 * @return an <code>EppResponseData</code> object, or null if the node
	 *         is invalid
	 */
	public static EppEntity fromXML( Node root )
	{
		NodeList list = root.getChildNodes();
		for( int i = 0; i < list.getLength(); i++ )
		{
			Node node = list.item(i);
			String prefix = node.getPrefix();
			String name = node.getLocalName();
			if( (prefix == null) || (name == null) )
			{
				continue;
			}
			if( prefix.equals("contact") )
			{
				if( name.equals("creData") )
				{
					return EppResponseDataCreateContact.fromXML(node);
				}
				else if( name.equals("infData") )
				{
					return EppResponseDataInfo.fromXML(node);
				}
				else if( name.equals("chkData") )
				{
					return EppResponseDataCheckContact.fromXML(node);
				}
				else if( name.equals("trnData") )
				{
					return EppResponseDataTransferContact.fromXML(node);
				}
				else if( name.equals("transfer") )
				{
					return EppResponseDataPoll.fromXML(node);
				}
				/*
				 * other response data types
				 */
			}
			else if( prefix.equals("domain") )
			{
				if( name.equals("creData") )
				{
					return EppResponseDataCreateDomain.fromXML(node);
				}
				else if( name.equals("infData") )
				{
					return EppResponseDataInfo.fromXML(node);
				}
				else if( name.equals("chkData") )
				{
					return EppResponseDataCheckDomain.fromXML(node);
				}
				else if( name.equals("trnData") )
				{
					return EppResponseDataTransferDomain.fromXML(node);
				}
				else if( name.equals("transfer") )
				{
					return EppResponseDataPoll.fromXML(node);
				}
				/*
				 * other response data types
				 */
			}
			else if( prefix.equals("host") )
			{
				if( name.equals("creData") )
				{
					return EppResponseDataCreateHost.fromXML(node);
				}
				else if( name.equals("infData") )
				{
					return EppResponseDataInfo.fromXML(node);
				}
				else if( name.equals("chkData") )
				{
					return EppResponseDataCheckHost.fromXML(node);
				}
				/*
				 * other response data types
				 */
			}
			else if( prefix.equals("svcsub") )
			{
				if( name.equals("creData") )
				{
					return EppResponseDataCreateSvcsub.fromXML(node);
				}
				else if( name.equals("infData") )
				{
					return EppResponseDataInfo.fromXML(node);
				}
				else if( name.equals("chkData") )
				{
					return EppResponseDataCheckSvcsub.fromXML(node);
				}
				else if( name.equals("trnData") )
				{
					return EppResponseDataTransferSvcsub.fromXML(node);
				}
				else if( name.equals("transfer") )
				{
					return EppResponseDataPoll.fromXML(node);
				}
				/*
				 * other response data types
				 */
			}
			/*
			 * other object types
			 */
		}

		return null;
	}

	public String toString()
	{
		return toString("resData");
	}
}
