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


import com.neulevel.epp.core.*;
import com.neulevel.epp.core.command.*;
import com.neulevel.epp.core.response.*;

import com.neulevel.biz.*;

import java.util.*;
import org.w3c.dom.*;

/**
 * The <code>EppResponseTest</code> class tests functions of
 * <code>EppResponse</code> objects.
 *
 * @author Ning Zhang ning.zhang@neustar.com
 * @version $Revision: 1.1 $ $Date: 2005/12/06 20:11:35 $
 */
public class EppResponseTest
{
	public static void main( String argv[] )
	{
		testGeneric();
		testCreate();
		testInfo();
		testCheck();
		testTransfer();
		testPoll();
	}

	private static void testGeneric()
	{
		Node epp;
		EppResponse res;
		EppResponse newres;
		EppResult result;
		EppTransactionId xid;

		res = new EppResponse();
		result = new EppResult(EppError.CODE_NO_ERROR,
		                       EppError.TEXT_NO_ERROR);
		res.addResult(result);

		result = new EppResult(EppError.CODE_COMMAND_SYNTAX_ERROR,
		                       EppError.TEXT_COMMAND_SYNTAX_ERROR);
		result.addValue("Value 1");
		result.addValue("Value 2");
		result.addValue("Value 3");
		result.addValue("Value 4");
		res.addResult(result);
		xid = new EppTransactionId("ABC-DEF-12345", "SERVER-ID-9999");
		res.setTransactionId(xid);
		res.setMessageQueued(99);
		res.setMessageQueueUpdated(Calendar.getInstance());
		System.out.println(res);

		EppParser parser = new EppParser(res.toString());
		if( parser.hasError() )
		{
			System.out.println(parser.getResult());
			System.exit(1);
		}

		epp = parser.getRootNode();
		newres = (EppResponse) EppResponse.fromXML(epp);
		if( newres == null )
		{
			System.out.println("Error in fromXML");
		}
		System.out.println(newres);
	}

	private static void testCreate()
	{
		EppResponseDataCreateContact contact;
		EppResponseDataCreateDomain  domain;
		EppResponseDataCreateHost    host;
		EppResponseDataCreateSvcsub  svcsub;

		contact = new EppResponseDataCreateContact("CONTACT-12345");
		testCreate(contact);
		domain = new EppResponseDataCreateDomain("example.biz",
			Calendar.getInstance());
		testCreate(domain);
		host = new EppResponseDataCreateHost("ns1.example.biz");
		testCreate(host);
		svcsub = new EppResponseDataCreateSvcsub("BIZLOCK-0123");
		testCreate(svcsub);
	}

	private static void testCreate( EppResponseData data )
	{
		Node epp;
		EppResponse res;
		EppResponse newres;
		EppResult result;
		EppTransactionId xid;

		res = new EppResponse();
		result = new EppResult(EppError.CODE_NO_ERROR,
		                       EppError.TEXT_NO_ERROR);
		res.addResult(result);
		res.setResponseData(data);
		xid = new EppTransactionId("ABC-DEF-12345", "SERVER-ID-9999");
		res.setTransactionId(xid);
		System.out.println(res);

		EppParser parser = new EppParser(res.toString());
		if( parser.hasError() )
		{
			System.out.println(parser.getResult());
			System.exit(1);
		}

		epp = parser.getRootNode();
		newres = (EppResponse) EppResponse.fromXML(epp);
		if( newres == null )
		{
			System.out.println("Error in fromXML");
		}
		System.out.println(newres);
	}

	private static void testInfo()
	{
		testInfoContact();
		testInfoDomain();
		testInfoHost();
		testInfoSvcsub();
	}

	private static void testInfo( EppObject object )
	{
		object.setRoid("OBJECTID-12345");
		object.setClientId("REGISTRAR-123");
		object.setClientIdCreated("REGISTRAR-000");
		object.setDateCreated(Calendar.getInstance());
		object.setClientIdCreated("REGISTRAR-111");
		object.setDateUpdated(Calendar.getInstance());
		object.setClientIdUpdated("REGISTRAR-222");
		object.addStatus(new EppStatus("ok"));
		object.addStatus(new EppStatus("pendingDelete"));

		Node epp;
		EppResponse res;
		EppResponse newres;
		EppResult result;
		EppTransactionId xid;

		res = new EppResponse();
		result = new EppResult(EppError.CODE_NO_ERROR,
		                       EppError.TEXT_NO_ERROR);
		res.addResult(result);
		xid = new EppTransactionId("ABC-DEF-12345", "SERVER-ID-9999");
		res.setTransactionId(xid);
		res.setResponseData(new EppResponseDataInfo(object));
		System.out.println(res);

		EppParser parser = new EppParser(res.toString());
		if( parser.hasError() )
		{
			System.out.println(parser.getResult());
			System.exit(1);
		}

		epp = parser.getRootNode();
		newres = (EppResponse) EppResponse.fromXML(epp);
		if( newres == null )
		{
			System.out.println("Error in fromXML");
		}
		System.out.println(newres);
	}

	private static void testInfoContact()
	{
		EppContact contact = getContact();
		contact.setDateTransferred(Calendar.getInstance());
		contact.setAuthInfo(new EppAuthInfo("pw", "2fooBar"));
		testInfo(contact);
	}

	private static void testInfoDomain()
	{
		EppDomain domain = getDomain();
		domain.addHost("ns1.domain.biz");
		domain.addHost("ns2.domain.biz");
		domain.addHost("ns3.domain.biz");
		domain.setRoid("DOMAIN-12345");
		domain.setDateTransferred(Calendar.getInstance());
		domain.setDateExpired(Calendar.getInstance());
		domain.setAuthInfo(new EppAuthInfo("pw", "2fooBar"));

		domain.setPeriod(null);
		testInfo(domain);
	}

	private static void testInfoHost()
	{
		EppHost host = getHost();
		testInfo(host);
	}

	private static void testInfoSvcsub()
	{
		EppSvcsub svcsub = getSvcsub();
		svcsub.setDateTransferred(Calendar.getInstance());
		svcsub.setDateExpired(Calendar.getInstance());
		svcsub.setAuthInfo(new EppAuthInfo("pw", "2fooBar"));
		testInfo(svcsub);
	}

	private static EppContact getContact()
	{
		EppAddress addr = new EppAddress();
		addr.setStreet(0, "101 Park Street");
		addr.setStreet(1, "Suite 101");
		addr.setCity("Sterling");
		addr.setState("VA");
		addr.setPostalCode("20166");
		addr.setCountryCode("US");

		EppContactData ascii = new EppContactData("FooBar, Inc,", null, addr);
		EppContactData i15d  = new EppContactData("Foo Bar", "FooBar, Inc.", addr);

		EppContact contact = new EppContact("CONTACT-ID");
		contact.setContactDataAscii(ascii);
		contact.setContactDataI15d(i15d);
		contact.setVoice("+1.7035551234", "9999");
		contact.setEmail("mail@foobar.com");
		contact.setAuthInfo(new EppAuthInfo("pw", "NEULEVEL-123"));

		EppCommandCreate cmd = new EppCommandCreate(contact);
		cmd.setClientTransactionId("ABC-DEF-12345");

		EppParser parser = new EppParser(cmd.toString());
		if( parser.hasError() )
		{
			System.out.println(parser.getResult());
			System.exit(1);
		}

		Node epp = parser.getRootNode();
		EppCommand newcmd = (EppCommand) EppCommand.fromXML(epp);
		if( newcmd == null )
		{
			System.out.println("Error in fromXML");
			System.exit(1);
		}
		return contact;
	}

	public static EppDomain getDomain()
	{
		EppDomain domain = new EppDomain("example.com");
		domain.setPeriod(new EppPeriod(2, 'y'));

		domain.addNameServer("ns1.example.com");
		domain.addNameServer("ns2.example.com");
		domain.setRegistrant("JD1234-EXAMPLE");
		domain.addContact(new EppContactType("JD1234-NEULEVEL", "admin"));
		domain.setAuthInfo(new EppAuthInfo("pw", "2fooBAR", "JD1234-EXAMPLE"));

		EppCommandCreate cmd = new EppCommandCreate(domain);
		cmd.setClientTransactionId("ABC-DEF-12345");

		EppParser parser = new EppParser(cmd.toString());
		if( parser.hasError() )
		{
			System.out.println(parser.getResult());
			System.exit(1);
		}

		Node epp = parser.getRootNode();
		EppCommand newcmd = (EppCommand) EppCommand.fromXML(epp);
		if( newcmd == null )
		{
			System.out.println("Error in fromXML");
			System.exit(1);
		}
		return domain;
	}

	public static EppHost getHost()
	{
		EppHost host = new EppHost("example.com");
		host.addAddress(new EppIpAddress("192.168.1.1"));
		host.addAddress(new EppIpAddress("192.168.1.2", "v4"));
		host.addAddress(new EppIpAddress("::FFFF:192.168.1.3", "v6"));

		EppCommandCreate cmd = new EppCommandCreate(host);
		cmd.setClientTransactionId("ABC-DEF-12345");

		EppParser parser = new EppParser(cmd.toString());
		if( parser.hasError() )
		{
			System.out.println(parser.getResult());
			System.exit(1);
		}

		Node epp = parser.getRootNode();
		EppCommand newcmd = (EppCommand) EppCommand.fromXML(epp);
		if( newcmd == null )
		{
			System.out.println("Error in fromXML");
			System.exit(1);
		}
		return host;
	}

	public static EppSvcsub getSvcsub()
	{
		EppSvcsub svcsub = new EppSvcsub("BIZLOCK-123");
		svcsub.setService(BizLock.ID);
		svcsub.setPeriod(new EppPeriod(2, 'y'));

		svcsub.addParam(BizLock.PARAM_DOMAIN  , "example.biz");
//		svcsub.addParam(BizLock.PARAM_PASSWORD, "2fooBAR");
		svcsub.addParam(BizLock.PARAM_BIZACCOUNT , "myBizAccount");
		svcsub.setRegistrant("JD1234-EXAMPLE");
		svcsub.addContact(new EppContactType("JD1234-NEULEVEL",
				svcsub.CONTACT_TYPE_PRIMARY));
		svcsub.addContact(new EppContactType("JD1235-NEULEVEL",
				svcsub.CONTACT_TYPE_SECONDARY));
		svcsub.addContact(new EppContactType("JD1235-NEULEVEL",
				svcsub.CONTACT_TYPE_BILLING));
		svcsub.setAuthInfo(new EppAuthInfo("pw", "2fooBAR", "JD1234-EXAMPLE"));

		EppCommandCreate cmd = new EppCommandCreate(svcsub);
		cmd.setClientTransactionId("ABC-DEF-12345");

		EppParser parser = new EppParser(cmd.toString());
		if( parser.hasError() )
		{
			System.out.println(parser.getResult());
			System.exit(1);
		}

		Node epp = parser.getRootNode();
		EppCommand newcmd = (EppCommand) EppCommand.fromXML(epp);
		if( newcmd == null )
		{
			System.out.println("Error in fromXML");
			System.exit(1);
		}
		return svcsub;
	}

	private static void testCheck()
	{
		testCheckContact();
		testCheckDomain();
		testCheckHost();
		testCheckSvcsub();
	}

	private static void testCheck( EppResponseDataCheck check )
	{
		testCreate(check);
	}

	private static void testCheckContact()
	{
		EppResponseDataCheckContact contact;
		contact = new EppResponseDataCheckContact();
		contact.add("CONTACT-00001", EppResponseDataCheck.FOUND);
		contact.add("CONTACT-00002", EppResponseDataCheck.NOT_FOUND);
		contact.add("CONTACT-00003", EppResponseDataCheck.FOUND);
		contact.add("CONTACT-00004", EppResponseDataCheck.NOT_FOUND);
		testCheck(contact);
	}

	private static void testCheckDomain()
	{
		EppResponseDataCheckDomain domain;
		domain = new EppResponseDataCheckDomain();
		domain.add("DOMAIN-00001.biz", EppResponseDataCheck.FOUND);
		domain.add("DOMAIN-00002.biz", EppResponseDataCheck.NOT_FOUND);
		domain.add("DOMAIN-00003.biz", EppResponseDataCheck.FOUND);
		domain.add("DOMAIN-00004.biz", EppResponseDataCheck.NOT_FOUND);
		testCheck(domain);
	}

	private static void testCheckHost()
	{
		EppResponseDataCheckHost host;
		host = new EppResponseDataCheckHost();
		host.add("ns1.DOMAIN.biz", EppResponseDataCheck.FOUND);
		host.add("ns2.DOMAIN.biz", EppResponseDataCheck.NOT_FOUND);
		host.add("ns3.DOMAIN.biz", EppResponseDataCheck.FOUND);
		host.add("ns4.DOMAIN.biz", EppResponseDataCheck.NOT_FOUND);
		testCheck(host);
	}

	private static void testCheckSvcsub()
	{
		EppResponseDataCheckSvcsub svcsub;
		svcsub = new EppResponseDataCheckSvcsub();
		svcsub.add("BIZLOCK-001", EppResponseDataCheck.FOUND);
		svcsub.add("BIZLOCK-002", EppResponseDataCheck.NOT_FOUND);
		svcsub.add("BIZLOCK-003", EppResponseDataCheck.FOUND);
		svcsub.add("BIZLOCK-004", EppResponseDataCheck.NOT_FOUND);
		testCheck(svcsub);
	}

	private static void testPoll()
	{
		testPoll(getPollContact(), 0);
		testPoll(getPollDomain(),  5);
		testPoll(getPollSvcsub(),  5);
	}

	private static void testPoll( EppPollable object, int n )
	{
		Node epp;
		EppResponse res;
		EppResponse newres;
		EppResult result;
		EppTransactionId xid;

		res = new EppResponse();
		if( n == 0 )
		{
			result = new EppResult(EppError.CODE_NO_ERROR_NO_MESSAGE,
		                               EppError.TEXT_NO_ERROR_NO_MESSAGE);
		}
		else
		{
			result = new EppResult(EppError.CODE_NO_ERROR_MESSAGE_PRESENT,
		                               EppError.TEXT_NO_ERROR_MESSAGE_PRESENT);
		}
		result.getMessage().setId("12345");
		res.addResult(result);
		res.setMessageQueued(n);
		xid = new EppTransactionId("ABC-DEF-12345", "SERVER-ID-9999");
		res.setTransactionId(xid);
		res.setResponseData(new EppResponseDataPoll(object));
		System.out.println(res);

		EppParser parser = new EppParser(res.toString());
		if( parser.hasError() )
		{
			System.out.println(parser.getResult());
			System.exit(1);
		}

		epp = parser.getRootNode();
		newres = (EppResponse) EppResponse.fromXML(epp);
		if( newres == null )
		{
			System.out.println("Error in fromXML");
		}
		System.out.println(newres);
	}

	private static EppCommandTransfer getPollContact()
	{
		Node epp;
		EppCommandTransfer cmd;
		EppCommandTransfer newcmd;

		cmd = new EppCommandTransferContact("CONTACT-12345");
		cmd.setClientTransactionId("ABC-DEF-12345");
		cmd.setOperation("request");
		cmd.setAuthInfo(new EppAuthInfo("pw", "2fooBar", "CONTACT-12345"));

		EppParser parser = new EppParser(cmd.toString());
		if( parser.hasError() )
		{
			System.out.println(parser.getResult());
			System.exit(1);
		}

		epp = parser.getRootNode();
		newcmd = (EppCommandTransfer) EppCommand.fromXML(epp);
		if( newcmd == null )
		{
			System.out.println("Error in fromXML");
			System.exit(1);
		}
		return cmd;
	}

	private static EppCommandTransfer getPollDomain()
	{
		Node epp;
		EppCommandTransfer cmd;
		EppCommandTransfer newcmd;

		cmd = new EppCommandTransferDomain("example.biz", new EppPeriod(1, 'y'));
		cmd.setClientTransactionId("ABC-DEF-12345");
		cmd.setOperation("approve");
		cmd.setAuthInfo(new EppAuthInfo("pw", "2fooBar", "EXAMPLE-12345"));

		EppParser parser = new EppParser(cmd.toString());
		if( parser.hasError() )
		{
			System.out.println(parser.getResult());
			System.exit(1);
		}

		epp = parser.getRootNode();
		newcmd = (EppCommandTransfer) EppCommand.fromXML(epp);
		if( newcmd == null )
		{
			System.out.println("Error in fromXML");
			System.exit(1);
		}
		return cmd;
	}

	private static EppCommandTransfer getPollSvcsub()
	{
		Node epp;
		EppCommandTransfer cmd;
		EppCommandTransfer newcmd;

		cmd = new EppCommandTransferSvcsub("BIZLOCK-12345");
		cmd.setClientTransactionId("ABC-DEF-12345");
		cmd.setOperation("request");
		cmd.setAuthInfo(new EppAuthInfo("pw", "2fooBar", "BIZLOCK-12345"));

		EppParser parser = new EppParser(cmd.toString());
		if( parser.hasError() )
		{
			System.out.println(parser.getResult());
			System.exit(1);
		}

		epp = parser.getRootNode();
		newcmd = (EppCommandTransfer) EppCommand.fromXML(epp);
		if( newcmd == null )
		{
			System.out.println("Error in fromXML");
			System.exit(1);
		}
		return cmd;
	}

	private static void testTransfer()
	{
		EppResponseDataTransferContact data1;
		EppResponseDataTransferDomain  data2;
		EppResponseDataTransferSvcsub  data3;
		data1 = new EppResponseDataTransferContact("CONTACT-12345");
		data1.setTransferStatus(EppResponseDataTransfer.STATUS_PENDING);
		testTransfer(data1);
		data2 = new EppResponseDataTransferDomain("example.biz");
		data2.setTransferStatus(EppResponseDataTransfer.STATUS_CLIENT_REJECTED);
		data2.setDateExpired(Calendar.getInstance());
		testTransfer(data2);
		data3 = new EppResponseDataTransferSvcsub("BIZLOCK-123");
		data3.setTransferStatus(EppResponseDataTransfer.STATUS_CLIENT_APPROVED);
		testTransfer(data3);
	}

	private static void testTransfer( EppResponseDataTransfer data )
	{
		data.setRequestClientId("CLIENT-ID-REQ");
		data.setActionClientId("CLIENT-ID-ACT");
		data.setRequestDate(Calendar.getInstance());
		data.setActionDate(Calendar.getInstance());

		Node epp;
		EppResponse res;
		EppResponse newres;
		EppResult result;
		EppTransactionId xid;

		res = new EppResponse();
		result = new EppResult(EppError.CODE_NO_ERROR_NO_MESSAGE,
	                               EppError.TEXT_NO_ERROR_NO_MESSAGE);
		res.addResult(result);
		xid = new EppTransactionId("ABC-DEF-12345", "SERVER-ID-9999");
		res.setTransactionId(xid);
		res.setResponseData(data);
		System.out.println(res);

		EppParser parser = new EppParser(res.toString());
		if( parser.hasError() )
		{
			System.out.println(parser.getResult());
			System.exit(1);
		}

		epp = parser.getRootNode();
		newres = (EppResponse) EppResponse.fromXML(epp);
		if( newres == null )
		{
			System.out.println("Error in fromXML");
		}
		System.out.println(newres);
	}
}
