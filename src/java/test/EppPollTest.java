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
 * The <code>EppPollTest</code> class tests functions of
 * <code>EppCommandPoll</code> commands.
 *
 * @author Ning Zhang ning.zhang@neustar.com
 * @version $Revision: 1.1 $ $Date: 2005/12/06 20:11:35 $
 */
public class EppPollTest
{
	public static void main( String argv[] )
	{
		Node epp;
		EppCommandPoll cmd;
		EppCommandPoll newcmd;

		cmd = new EppCommandPoll();
		cmd.setOperation("ack");
		cmd.setMessageId("12345");
		cmd.setClientTransactionId("ABC-DEF-12345");
		System.out.println(cmd);

		EppParser parser = new EppParser(cmd.toString());
		if( parser.hasError() )
		{
			System.out.println(parser.getResult());
			System.exit(1);
		}

		epp = parser.getRootNode();
		newcmd = (EppCommandPoll) EppCommand.fromXML(epp);
		if( newcmd == null )
		{
			System.out.println("Error in fromXML");
			System.exit(1);
		}
		System.out.println(newcmd);
	}
}
