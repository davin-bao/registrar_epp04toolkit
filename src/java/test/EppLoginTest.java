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

import org.w3c.dom.*;

/**
 * The <code>EppLoginTest</code> class tests functions of
 * <code>EppLoginTest</code> commands.
 *
 * @author Ning Zhang ning.zhang@neustar.com
 * @version $Revision: 1.1 $ $Date: 2005/12/06 20:11:35 $
 */
public class EppLoginTest
{
	public static void main( String argv[] )
	{
		EppCreds creds = new EppCreds("username", "password");
		creds.setNewPassword("newpassword");

		EppServiceMenu menu = new EppServiceMenu();

		menu.addService("contact");
		menu.addService("domain");
		menu.addService("host");
		menu.addUnspec("obj1ext", "http://custom/obj1ext-1.0", "xml/obj1ext-1.0.xsd");

		EppCommandLogin login = new EppCommandLogin(menu);
		login.setClientTransactionId("ABC-DEF-12345");
		login.setCreds(creds);
		System.out.println(login);

		EppParser parser = new EppParser(login.toString());

		if( parser.hasError() )
		{
			System.out.println(parser.getResult());
			System.exit(1);
		}

		Node epp = parser.getRootNode();
		EppCommand cmd = (EppCommand) EppCommand.fromXML(epp);
		if( cmd == null )
		{
			System.out.println("Error in fromXML");
			System.exit(1);
		}
		System.out.println(cmd);
	}
}
