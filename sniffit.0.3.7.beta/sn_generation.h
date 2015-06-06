/* Sniffit Packet Generation File                                         */

void exec_generate(struct generate_mask *);

void transmit_TCP (int, char *, 
		     	   int, int , int ,
		           _32_bit, unsigned short,
			   _32_bit, unsigned short,
                           _32_bit, _32_bit, 
                           unsigned short);

void transmit_UDP (int, char *, 
			   int, int, 
		           _32_bit, unsigned short,
			   _32_bit, unsigned short);

int open_sending (void);

void sp_send_packet (struct sp_data_exchange *, unsigned char);
void sp_fix_TCP_packet (struct sp_data_exchange *);
void sp_fix_UDP_packet (struct sp_data_exchange *);
void sp_fix_IP_packet (struct sp_data_exchange *, unsigned char);
