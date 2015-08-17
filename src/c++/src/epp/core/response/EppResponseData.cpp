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
#include "EppResponseData.hpp"
#include "EppResponseDataCreate.hpp"
#include "EppResponseDataCreateContact.hpp"
#include "EppResponseDataCreateDomain.hpp"
#include "EppResponseDataCreateHost.hpp"
#include "EppResponseDataCreateSvcsub.hpp"
#include "EppResponseDataInfo.hpp"
#include "EppResponseDataCheck.hpp"
#include "EppResponseDataCheckContact.hpp"
#include "EppResponseDataCheckDomain.hpp"
#include "EppResponseDataCheckHost.hpp"
#include "EppResponseDataCheckSvcsub.hpp"
#include "EppResponseDataPoll.hpp"
#include "EppResponseDataTransfer.hpp"
#include "EppResponseDataTransferContact.hpp"
#include "EppResponseDataTransferDomain.hpp"
#include "EppResponseDataTransferSvcsub.hpp"

EppResponseData * EppResponseData::fromXML( const DOM_Node& root )
{
	DOM_NodeList list = root.getChildNodes();
	for( unsigned int i = 0; i < list.getLength(); i++ )
	{
		DOM_Node node = list.item(i);
		DOMString prefix = node.getPrefix();
		DOMString name = node.getLocalName();
#if 0
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
#endif
		if( name == null )
		{
			name = node.getNodeName();
		}
		if( name == null )
		{
			continue;
		}
		if( name.equals("contact:creData") )
		{
			return EppResponseDataCreateContact::fromXML(node);
		}
		else if( name.equals("contact:infData") )
		{
			return EppResponseDataInfo::fromXML(node);
		}
		else if( name.equals("contact:chkData") )
		{
			return EppResponseDataCheckContact::fromXML(node);
		}
		else if( name.equals("contact:trnData") )
		{
			return EppResponseDataTransferContact::fromXML(node);
		}
		else if( name.equals("contact:transfer") )
		{
			return EppResponseDataPoll::fromXML(node);
		}
		else if( name.equals("domain:creData") )
		{
			return EppResponseDataCreateDomain::fromXML(node);
		}
		else if( name.equals("domain:infData") )
		{
			return EppResponseDataInfo::fromXML(node);
		}
		else if( name.equals("domain:chkData") )
		{
			return EppResponseDataCheckDomain::fromXML(node);
		}
		else if( name.equals("domain:trnData") )
		{
			return EppResponseDataTransferDomain::fromXML(node);
		}
		else if( name.equals("domain:transfer") )
		{
			return EppResponseDataPoll::fromXML(node);
		}
		else if( name.equals("host:creData") )
		{
			return EppResponseDataCreateHost::fromXML(node);
		}
		else if( name.equals("host:infData") )
		{
			return EppResponseDataInfo::fromXML(node);
		}
		else if( name.equals("host:chkData") )
		{
			return EppResponseDataCheckHost::fromXML(node);
		}
		else if( name.equals("svcsub:creData") )
		{
			return EppResponseDataCreateSvcsub::fromXML(node);
		}
		else if( name.equals("svcsub:infData") )
		{
			return EppResponseDataInfo::fromXML(node);
		}
		else if( name.equals("svcsub:chkData") )
		{
			return EppResponseDataCheckSvcsub::fromXML(node);
		}
		else if( name.equals("svcsub:trnData") )
		{
			return EppResponseDataTransferSvcsub::fromXML(node);
		}
		else if( name.equals("svcsub:transfer") )
		{
			return EppResponseDataPoll::fromXML(node);
		}
		/*
		 * other object types
		 */
	}

	return null;
}
