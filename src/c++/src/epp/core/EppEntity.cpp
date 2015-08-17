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
#include "EppEntity.hpp"
#include "EppUtil.hpp"

const int EppEntity::TYPE_EppEntity                      = 0   ;
const int EppEntity::TYPE_EppObject                      = 100 ;
const int EppEntity::TYPE_EppContact                     = 101 ;
const int EppEntity::TYPE_EppDomain                      = 102 ;
const int EppEntity::TYPE_EppHost                        = 103 ;
const int EppEntity::TYPE_EppSvcsub                      = 104 ;

const int EppEntity::TYPE_EppCommand                     = 200 ;
const int EppEntity::TYPE_EppCommandPoll                 = 201 ;
const int EppEntity::TYPE_EppCommandLogin                = 202 ;
const int EppEntity::TYPE_EppCommandLogout               = 203 ;
const int EppEntity::TYPE_EppCommandCreate               = 210 ;
const int EppEntity::TYPE_EppCommandCheck                = 220 ;
const int EppEntity::TYPE_EppCommandCheckContact         = 221 ;
const int EppEntity::TYPE_EppCommandCheckDomain          = 222 ;
const int EppEntity::TYPE_EppCommandCheckHost            = 223 ;
const int EppEntity::TYPE_EppCommandCheckSvcsub          = 224 ;
const int EppEntity::TYPE_EppCommandDelete               = 230 ;
const int EppEntity::TYPE_EppCommandDeleteContact        = 231 ;
const int EppEntity::TYPE_EppCommandDeleteDomain         = 232 ;
const int EppEntity::TYPE_EppCommandDeleteHost           = 233 ;
const int EppEntity::TYPE_EppCommandDeleteSvcsub         = 234 ;
const int EppEntity::TYPE_EppCommandInfo                 = 240 ;
const int EppEntity::TYPE_EppCommandInfoContact          = 241 ;
const int EppEntity::TYPE_EppCommandInfoDomain           = 242 ;
const int EppEntity::TYPE_EppCommandInfoHost             = 243 ;
const int EppEntity::TYPE_EppCommandInfoSvcsub           = 244 ;
const int EppEntity::TYPE_EppCommandUpdate               = 250 ;
const int EppEntity::TYPE_EppCommandUpdateContact        = 251 ;
const int EppEntity::TYPE_EppCommandUpdateDomain         = 252 ;
const int EppEntity::TYPE_EppCommandUpdateHost           = 253 ;
const int EppEntity::TYPE_EppCommandUpdateSvcsub         = 254 ;
const int EppEntity::TYPE_EppCommandRenew                = 260 ;
const int EppEntity::TYPE_EppCommandRenewContact         = 261 ;
const int EppEntity::TYPE_EppCommandRenewDomain          = 262 ;
const int EppEntity::TYPE_EppCommandRenewHost            = 263 ;
const int EppEntity::TYPE_EppCommandRenewSvcsub          = 264 ;
const int EppEntity::TYPE_EppCommandTransfer             = 270 ;
const int EppEntity::TYPE_EppCommandTransferContact      = 271 ;
const int EppEntity::TYPE_EppCommandTransferDomain       = 272 ;
const int EppEntity::TYPE_EppCommandTransferHost         = 273 ;
const int EppEntity::TYPE_EppCommandTransferSvcsub       = 274 ;

const int EppEntity::TYPE_EppResponse                    = 300 ;

const int EppEntity::TYPE_EppResponseData                = 400 ;
const int EppEntity::TYPE_EppResponseDataPoll            = 410 ;
const int EppEntity::TYPE_EppResponseDataInfo            = 420 ;
const int EppEntity::TYPE_EppResponseDataCreate          = 430 ;
const int EppEntity::TYPE_EppResponseDataCreateContact   = 431 ;
const int EppEntity::TYPE_EppResponseDataCreateDomain    = 432 ;
const int EppEntity::TYPE_EppResponseDataCreateHost      = 433 ;
const int EppEntity::TYPE_EppResponseDataCreateSvcsub    = 434 ;
const int EppEntity::TYPE_EppResponseDataCheck           = 440 ;
const int EppEntity::TYPE_EppResponseDataCheckContact    = 441 ;
const int EppEntity::TYPE_EppResponseDataCheckDomain     = 442 ;
const int EppEntity::TYPE_EppResponseDataCheckHost       = 443 ;
const int EppEntity::TYPE_EppResponseDataCheckSvcsub     = 444 ;
const int EppEntity::TYPE_EppResponseDataTransfer        = 450 ;
const int EppEntity::TYPE_EppResponseDataTransferContact = 451 ;
const int EppEntity::TYPE_EppResponseDataTransferDomain  = 452 ;
const int EppEntity::TYPE_EppResponseDataTransferHost    = 453 ;
const int EppEntity::TYPE_EppResponseDataTransferSvcsub  = 454 ;

EppEntity::~EppEntity()
{
}

EppEntity * EppEntity::fromXML( const DOM_Node &root )
{
	return 0;
}

DOMString EppEntity::toString( const DOMString &tag )
{
	DOM_Document doc = DOM_Document::createDocument();
	DOM_Element elm = toXML(doc, tag);
	doc.appendChild(elm);
	return EppUtil::toString(doc);
}

bool EppEntity::instanceOf( const int type )
{
	int obj = this->getEntityType();
	if( obj == type )
	{
		return true;
	}

	if( type == EppEntity::TYPE_EppEntity )
	{
		return true;
	}

	switch( type )
	{
	case EppEntity::TYPE_EppObject:
		return  (obj == EppEntity::TYPE_EppObject)  ||
		        (obj == EppEntity::TYPE_EppContact) ||
			(obj == EppEntity::TYPE_EppDomain)  ||
			(obj == EppEntity::TYPE_EppHost     ||
			(obj == EppEntity::TYPE_EppSvcsub));

	case EppEntity::TYPE_EppCommand:
		return  (obj >= EppEntity::TYPE_EppCommand) &&
			(obj <  EppEntity::TYPE_EppResponse);

	case EppEntity::TYPE_EppCommandCheck:
		return  (obj >= EppEntity::TYPE_EppCommandCheck) &&
			(obj <= EppEntity::TYPE_EppCommandCheckSvcsub);

	case EppEntity::TYPE_EppCommandDelete:
		return  (obj >= EppEntity::TYPE_EppCommandDelete) &&
			(obj <= EppEntity::TYPE_EppCommandDeleteSvcsub);

	case EppEntity::TYPE_EppCommandInfo:
		return  (obj >= EppEntity::TYPE_EppCommandInfo) &&
			(obj <= EppEntity::TYPE_EppCommandInfoSvcsub);

	case EppEntity::TYPE_EppCommandRenew:
		return  (obj >= EppEntity::TYPE_EppCommandRenew) &&
			(obj <= EppEntity::TYPE_EppCommandRenewSvcsub);

	case EppEntity::TYPE_EppCommandTransfer:
		return  (obj >= EppEntity::TYPE_EppCommandTransfer) &&
			(obj <= EppEntity::TYPE_EppCommandTransferSvcsub);

	case EppEntity::TYPE_EppCommandUpdate:
		return  (obj >= EppEntity::TYPE_EppCommandUpdate) &&
			(obj <= EppEntity::TYPE_EppCommandUpdateSvcsub);

	case EppEntity::TYPE_EppResponseData:
		return  (obj >= EppEntity::TYPE_EppResponseData) &&
			(obj <= EppEntity::TYPE_EppResponseDataTransferSvcsub);

	case EppEntity::TYPE_EppResponseDataCreate:
		return  (obj >= EppEntity::TYPE_EppResponseDataCreate) &&
			(obj <= EppEntity::TYPE_EppResponseDataCreateSvcsub);

	case EppEntity::TYPE_EppResponseDataCheck:
		return  (obj >= EppEntity::TYPE_EppResponseDataCheck) &&
			(obj <= EppEntity::TYPE_EppResponseDataCheckSvcsub);

	case EppEntity::TYPE_EppResponseDataTransfer:
		return  (obj >= EppEntity::TYPE_EppResponseDataTransfer) &&
			(obj <= EppEntity::TYPE_EppResponseDataTransferSvcsub);

	default:
		break;
	}

	return false;
}
