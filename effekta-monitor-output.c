/*

 effekta-monitor.c
 
 Copyright 2012 Albert Hakvoort @ = albert [at] hakvoort [dot] co
 
 Version 0.4

 libmodbus is required

 Compile with: cc `pkg-config --cflags --libs libmodbus` effekta-monitor-output.c -o effekta-monitor-output


*/


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <modbus.h>


int main(void)
{
	modbus_t *ctx;
	int rc;
	int i;
	uint16_t tab_reg[64];
	float data_0,data_4,data_5,data_6,data_13,data_14,data_15,data_16,data_17_18;

	ctx = modbus_new_rtu("/dev/YPort", 9600, 'N', 8, 1);
	if (ctx == NULL) {
		fprintf(stderr, "Unable to create the libmodbus context\n");
		return -1;
	}
	
	modbus_set_slave(ctx, 1);

	if (modbus_connect(ctx) == -1) {
		fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
		modbus_free(ctx);
		return -1;
	}
		
	rc = modbus_read_registers(ctx, 0xC020, 19, tab_reg);
	if (rc == -1) {
		fprintf(stderr, "%s\n", modbus_strerror(errno));
		return -1;
	}


		data_0=tab_reg[0]*10.0;
		data_4=tab_reg[4]/10.0;
		data_5=tab_reg[5]/10.0;
		data_6=tab_reg[6]/10.0;
		data_13=tab_reg[13]/10.0;
		data_14=tab_reg[14]/10.0;
		data_15=tab_reg[15]*10.0;
		//data_15=tab_reg[15]/100.0;
		//data_16=tab_reg[16]/100.0;
		data_16=tab_reg[16]*10.0;;

// data_15 = Output String A in Wp
// data_16 = Output String B in Wp
// data_0  = Output String A+B in Wp
// tab_reg[9] = Temperature Heatsink
// tab_reg[10] = Temperature Inverter
// tab_reg[18] = Total Produced kWh 
// tab_reg[7] = Voltage

    		printf("%3.0f", data_15);
		printf("\n");
    		printf("%3.0f", data_16);
		printf ("\n");
    		printf("%3.0f", data_0);
		printf ("\n");
    		printf("%d", tab_reg[9]);
		printf ("\n");
    		printf("%d", tab_reg[10]);
		printf ("\n");
    		printf("%d", tab_reg[18]);
		printf ("\n");
    		printf("%d", tab_reg[7]);
		printf ("\n");

	modbus_close(ctx);
	modbus_free(ctx);
        
	return(0);
}

