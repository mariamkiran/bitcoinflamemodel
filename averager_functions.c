#include "header.h"
#include "Averager_agent_header.h"
#include "my_library_header.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int collect_data()
{
	double total_bits=0.0;
	int msg_cnt=0;
	double m_price=0.0;
	
	double vwap_bc=0.0;
	double vwap_tbc=0.0;
	
	broadcast_ledger_message=get_first_broadcast_ledger_message();
	while(broadcast_ledger_message)
	{
			total_bits+=broadcast_ledger_message->bits;
		broadcast_ledger_message=get_next_broadcast_ledger_message(broadcast_ledger_message);
	}
	
	BITCOIN_NUMBER_TOTAL=total_bits;
	
	

	money_transfer_message=get_first_money_transfer_message();
	while(money_transfer_message)
	{
		m_price+=money_transfer_message->price;
		msg_cnt++;
		printf("msg_found");
		vwap_bc+=(money_transfer_message->price * money_transfer_message->bits);
		vwap_tbc+= money_transfer_message->bits;
		
		money_transfer_message=get_next_money_transfer_message(money_transfer_message);
	}
	
	
	if(msg_cnt!=0)
	{
		NUMBER_OF_TRANSACTIONS=msg_cnt;
		AVERAGE_PRICE=m_price/(double)msg_cnt;
		if(vwap_tbc!=0)
		{
			TRUE_AVG_PRICE= vwap_bc/vwap_tbc;
		}
		else
		{
			TRUE_AVG_PRICE=0.0;
		}
		
	}
	else
	{
		NUMBER_OF_TRANSACTIONS=0;
		AVERAGE_PRICE=0.0;
		TRUE_AVG_PRICE=TRUE_AVG_PRICE;
	}	
	
	
	//volume weighted avergae price used formula
	
	people_in_simulation_message=get_first_people_in_simulation_message();
	while(people_in_simulation_message)
	{
		NUMBERS=people_in_simulation_message->people;
		people_in_simulation_message=get_next_people_in_simulation_message(people_in_simulation_message);
	}

	
	return 0;
}
