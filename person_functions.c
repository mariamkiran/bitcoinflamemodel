#include "header.h"
#include "person_agent_header.h"
#include "my_library_header.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int broadcast_my_bitcoin()
{
	//assumption emptying out my ledger first 
	reset_record_array(&LEDGER);
//	printf("free me");
	add_broadcast_ledger_message(ID, TOTALBITCOINS);
	return 0;
}

int update_my_ledger()
{
	//int i=0;
	broadcast_ledger_message=get_first_broadcast_ledger_message();
	while(broadcast_ledger_message)
	{
		//do calculation
		//for(i=0;i<LEDGER.size();i++)
		//{
		//printf("adding %d, ", ID);
			add_record(&LEDGER, broadcast_ledger_message->id, broadcast_ledger_message->bits);
		
		//}
		broadcast_ledger_message=get_next_broadcast_ledger_message(broadcast_ledger_message);
	}
	return 0;
}

int advert_selling_buying()
{
	double choice=0.0;
	int sb=0;
	choice=(double)rand()/(double)RAND_MAX;
	
	double pr=0.0;
	pr=(double)rand()/(double)RAND_MAX *10;
	
	if(choice<0.5)
	{
		//printf("I am selling");
		sb=1;
	}
	else
	{
		//printf("I am buying");
		sb=0;
	}
	
	MYCHOICE=sb;
	PRICE=pr;
	
	add_msg_send_status_message(ID, MYCHOICE, PRICE);
		
	return 0;
}
                 
  int  read_sellers()
{
	int i=0;
	double min_price=15.0;
	int save_id=0;
	//double c_price=0.0;
	msg_send_status_message=get_first_msg_send_status_message();
	while(msg_send_status_message)
	{
		if(MYCHOICE==0)//buying
		{
			if(msg_send_status_message->choice==1)
			{
				if(msg_send_status_message->price<=min_price)
				{
					min_price=msg_send_status_message->price;
					save_id=msg_send_status_message->id;
				}
			}
			//find minimum price from the messages
			
			//record the price and seller's id
			
			
		}
		msg_send_status_message=get_next_msg_send_status_message(msg_send_status_message);
	}
	
		//calculate a double value of how many bitcoins to buy from this person --looking at ledger
		
	double bc=0.0;
	for(i=0;i<LEDGER.size;i++)
	{
		if(LEDGER.array[i].person_id==save_id)
		{
			bc=LEDGER.array[i].bitcoinno;
			
		}
	}
	
	double ask=0.0;
	
	if(save_id!=0)
	{
		ask=(double)rand()/(double)RAND_MAX *bc;
		
	//printf("I am asking %f from %d", ask, save_id);
	//send message to seller that you want to buy from seller
	add_msg_choose_seller_message(ID, save_id, ask,min_price);
	}
	
	return 0;
}

 int confirm_transaction()
{
	//read message coming to me from buyers on their prices
	//agree on any one of them
	//send confirmation message to person that I will sell to you at this price
	//send bradcast message to everyone that this transaction is agreed
	int buy_id=0;
	double p=0.0;
	double b=0.0;
	
	msg_choose_seller_message=get_first_msg_choose_seller_message();
	{
		if(msg_choose_seller_message->sell_id==ID)
		{
			buy_id=msg_choose_seller_message->buy_id;
			p=msg_choose_seller_message->price;
			b=msg_choose_seller_message->bits;
		}
		msg_choose_seller_message=get_next_msg_choose_seller_message(msg_choose_seller_message);
	}
	
	add_msg_confirm_transaction_message(buy_id, ID, b, p);
	
	return 0;
}



 int get_sellers()
{
	//read confirmation messages and price exchange
	//start counter for 10 days and save the agreed price  
	int buyer=0;
	//miners start mining blockchains -> If I am a miner I start collecting transactions, make a hash of it, transaction is transfered from one block to next every time step everyone on the chain earns 25 bitcoins (to miner) miner also gets the transaction fee
	//priority = sum(input_value_in_base_units * input_age)/size_in_bytes //transactions 
	if(IM_LOCKED==0)
	{
		msg_confirm_transaction_message=get_first_msg_confirm_transaction_message();
		while(msg_confirm_transaction_message)
		{
			if(msg_confirm_transaction_message->sell_id==ID)
			{
			//	printf("me");
				IM_LOCKED=msg_confirm_transaction_message->buy_id;
				MY_COUNTER=11;
				LOCKED_SELLER=msg_confirm_transaction_message->sell_id;
				LOCKED_BUYER=msg_confirm_transaction_message->buy_id;
				LOCKED_BITS=msg_confirm_transaction_message->bits;
				LOCKED_PRICE=msg_confirm_transaction_message->price;
			
			
			}
			msg_confirm_transaction_message=get_next_msg_confirm_transaction_message(msg_confirm_transaction_message);
	
		}	
	}
	
	return 0;
}

 int locked()
{
	//read confirmation messages and price exchange
	//start counter for 10 days and save the agreed price  
	
	//miners start mining blockchains -> If I am a miner I start collecting transactions, make a hash of it, transaction is transfered from one block to next every time step everyone on the chain earns 25 bitcoins (to miner) miner also gets the transaction fee
	//priority = sum(input_value_in_base_units * input_age)/size_in_bytes //transactions 
	if(IM_LOCKED!=0)
	{
		MY_COUNTER=MY_COUNTER-1;
		printf("counter %d", MY_COUNTER);
	}
	
	//printf("in locked");
	
	return 0;
}



int transfer_money()
{
	//if counter ==10 transfer the price and add bitcoin
	//send message to everyone on network to update ledger
	
	//printf("transfer");
	if(IM_LOCKED!=0)
	{
		printf("rtransfer locked %d  and %d \n", IM_LOCKED, MY_COUNTER);
		if(MY_COUNTER==0)
		{
			printf("in transfer if for id %d", ID);
			IM_LOCKED=0;
			MY_COUNTER=0;
			add_money_transfer_message(LOCKED_BUYER, LOCKED_SELLER,LOCKED_BITS,LOCKED_PRICE);
		}
	}
	
	return 0;
}

int read_money()
{
	double r=0.0;
	
	r=(double)rand()/(double)RAND_MAX;
	
	money_transfer_message=get_first_money_transfer_message();
	while(money_transfer_message)
	{
		if(money_transfer_message->sell_id==ID)
		{
			TOTALBITCOINS=TOTALBITCOINS-money_transfer_message->bits;
		}
		else if(money_transfer_message->buy_id==ID)
		{
			TOTALBITCOINS=TOTALBITCOINS+money_transfer_message->bits;
		}
		else
		{ 
			if(r<0.05)
			{
				TOTALBITCOINS=TOTALBITCOINS+TRANSACTION_FEE;
			}
		}
		money_transfer_message=get_next_money_transfer_message(money_transfer_message);
	}
	return 0;
}

