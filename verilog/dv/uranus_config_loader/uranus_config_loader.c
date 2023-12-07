/*
	FPGA config loader via WB
*/

#include <defs.h>

// Address defines
#define OFF_CONFIG_LBLOCK       0x10000
#define OFF_CONFIG_VRNODE       0x11000
#define OFF_CONFIG_HRNODE       0x12000
#define OFF_CONFIG_RSTCFG       0x1A000
#define OFF_CONFIG_TAPCLK       0x1E000

// Test defines
#define WB_CNT                  101
#define WB_TEA                  102

#define FPGA_TEST               WB_CNT

// Define test offsets & include bitstream data
#if   FPGA_TEST == WB_CNT
#define OFF_CNT_ADDR            0x200F0
#define OFF_EFUSE_ADDR          0x140000

//#include "wb_cnt.txt_lb_bit.h"
//#include "wb_cnt.txt_vn_bit.h"
//#include "wb_cnt.txt_hn_bit.h"

#include "test.txt_lb_bit.h"
#include "test.txt_vn_bit.h"
#include "test.txt_hn_bit.h"

#elif FPGA_TEST == WB_TEA
#define OFF_K0_ADDR             0x20000
#define OFF_K1_ADDR             0x20004
#define OFF_DATA_ADDR           0x20008

#include "wb_tea.txt_lb_bit.h"
#include "wb_tea.txt_vn_bit.h"
#include "wb_tea.txt_hn_bit.h"

#else
#error "No FPGA test defined!"
#endif

#define write_user_reg(off, val) {(*(volatile uint32_t*)(0x30000000 + (off))) = (val);}
#define read_user_reg(off) (*(volatile uint32_t*)(0x30000000 + (off)))

#define DELAY   0

void putchar(char c);
void print_hex(uint32_t v, int digits);
void print(const char *p);
void delay(const int d);

void load_scanchain(int words, const uint16_t* config_data, uint32_t config_off, uint32_t tap)
{
    #if 0
    for (int i = 0; i < words/2; i++)
    {
        //putchar('0');
        // logic blocks
        uint32_t data = ((uint32_t*)config_data)[i];
        write_user_reg(config_off, ((uint16_t*)&data)[0]);
        //putchar('1');
        write_user_reg(OFF_CONFIG_TAPCLK, tap);
        //putchar('2');
        write_user_reg(OFF_CONFIG_TAPCLK, 0);
        //putchar('3');
        write_user_reg(config_off, ((uint16_t*)&data)[1]);
        //putchar('4');
        write_user_reg(OFF_CONFIG_TAPCLK, tap);
        //putchar('5');
        write_user_reg(OFF_CONFIG_TAPCLK, 0);
        //putchar('6');
    }
    #else
    // zero chain
    for (int i = 0; i < words+10; i++)
    {
        write_user_reg(config_off, 0);
        write_user_reg(OFF_CONFIG_TAPCLK, tap);
        write_user_reg(OFF_CONFIG_TAPCLK, 0);
    }
    
    int rep = 0;
    for (int i = 0; i < words; i++)
    {
        write_user_reg(config_off, config_data[i]);
        write_user_reg(OFF_CONFIG_TAPCLK, tap);
        write_user_reg(OFF_CONFIG_TAPCLK, 0);
        if (read_user_reg(config_off))
        {
            print_hex(tap, 1);
            print(" is ");
            print_hex(read_user_reg(config_off), 2);
            print(" on ");
            print_hex(i, 3);
            print(" of ");
            print_hex(words, 3);
            if (i == words-1)
                print(" (last)");
            putchar('\n');
            rep = 1;
        }
    }
    #endif
}


void test_scanchain(int words, uint32_t config_off, uint32_t tap, int bits)
{
    for (int bit = 0; bit < bits; ++bit)
    {
        // zero chain
        for (int i = 0; i < words+10; i++)
        {
            write_user_reg(config_off, 0);
            write_user_reg(OFF_CONFIG_TAPCLK, tap);
            write_user_reg(OFF_CONFIG_TAPCLK, 0);
        }
        
        for (int i = 0; i < words; i++)
        {
            if (read_user_reg(config_off))
            {
                print_hex(bit, 1);
                print(" is ");
                print_hex(words-i, 3);
                putchar('\n');
                break;
            }
            write_user_reg(config_off, 1<<bit);
            write_user_reg(OFF_CONFIG_TAPCLK, tap);
            write_user_reg(OFF_CONFIG_TAPCLK, 0);
        }
    }
}


// --------------------------------------------------------
// Firmware routines
// --------------------------------------------------------

void configure_io()
{

//  ======= Useful GPIO mode values =============

//      GPIO_MODE_MGMT_STD_INPUT_NOPULL
//      GPIO_MODE_MGMT_STD_INPUT_PULLDOWN
//      GPIO_MODE_MGMT_STD_INPUT_PULLUP
//      GPIO_MODE_MGMT_STD_OUTPUT
//      GPIO_MODE_MGMT_STD_BIDIRECTIONAL
//      GPIO_MODE_MGMT_STD_ANALOG

//      GPIO_MODE_USER_STD_INPUT_NOPULL
//      GPIO_MODE_USER_STD_INPUT_PULLDOWN
//      GPIO_MODE_USER_STD_INPUT_PULLUP
//      GPIO_MODE_USER_STD_OUTPUT
//      GPIO_MODE_USER_STD_BIDIRECTIONAL
//      GPIO_MODE_USER_STD_ANALOG


//  ======= set each IO to the desired configuration =============

    //  GPIO 0 is turned off to prevent toggling the debug pin; For debug, make this an output and
    //  drive it externally to ground.

    reg_mprj_io_0 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;

    // Changing configuration for IO[1-4] will interfere with programming flash. if you change them,
    // You may need to hold reset while powering up the board and initiating flash to keep the process
    // configuring these IO from their default values.

    reg_mprj_io_1 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_2 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_3 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_4 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;

    // -------------------------------------------

    reg_mprj_io_5 = GPIO_MODE_USER_STD_OUTPUT;     // UART Rx
    //reg_mprj_io_5 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;     // UART Rx
    reg_mprj_io_6 = GPIO_MODE_MGMT_STD_OUTPUT;           // UART Tx
    reg_mprj_io_7 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_8 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_9 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_10 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_11 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_12 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_13 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_14 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_15 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_16 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_17 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_18 = GPIO_MODE_MGMT_STD_OUTPUT;

    reg_mprj_io_19 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_20 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_21 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_22 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_23 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_24 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_25 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_26 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_27 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_28 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_29 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_30 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_31 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_32 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_33 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_34 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_35 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_36 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_37 = GPIO_MODE_MGMT_STD_OUTPUT;

    // Initiate the serial transfer to configure IO
    reg_mprj_xfer = 1;
    while (reg_mprj_xfer == 1);
}

void delay(const int d)
{
    if (!d)
        return;
    /* Configure timer for a single-shot countdown */
	reg_timer0_config = 0;
	reg_timer0_data = d;
    reg_timer0_config = 1;

    // Loop, waiting for value to reach zero
   reg_timer0_update = 1;  // latch current value
   while (reg_timer0_value > 0) {
           reg_timer0_update = 1;
   }

}

void putchar(char c)
{
	if (c == '\n')
		putchar('\r');
    while (reg_uart_txfull == 1);
	reg_uart_data = c;
}

void print_hex(uint32_t v, int digits)
{
	for (int i = digits - 1; i >= 0; i--) {
		char c = "0123456789abcdef"[(v >> (4*i)) & 15];
		putchar(c);
	}
}

void print(const char *p)
{
	while (*p)
		putchar(*(p++));
}

void* memcpy(void* destination, const void* source, int num)
{
	int i;
	unsigned char* d = destination;
	unsigned char* s = (void*)source;
	for (i = 0; i < num; i++) {
		d[i] = s[i];
	}
	return destination;
}

#define SIZE 302
uint16_t vnode_config_data2[SIZE];
int mangle_data(int x, int y)
{
    if (vnode_config_words != SIZE)
    {
        print("assert");
        return 1;
    }
    
    if ((x == y) || (vnode_config_data[x] != 0x7f) || (vnode_config_data[y] != 0x7f))
        return 1;
        
    int b,e;
        
    if (x < y)
    {
        b = x;
        e = y;
    }
    else
    {
        b = y;
        e = x;
    }
    
    int len = e-b;
    
    int eq = 1;
    for (int i = b; i < e; ++i)
        if (vnode_config_data[i] != 0x7f)
        {
            eq = 0;
            break;
        }
    if (eq)
        return 1;
    
    for (int i = 0; i < SIZE; ++i)
        vnode_config_data2[i] = 0;
    if (x < y)
    {
        memcpy(&vnode_config_data2[0], &vnode_config_data[0], sizeof(vnode_config_data[0])*x);
        memcpy(&vnode_config_data2[x], &vnode_config_data[x+1], sizeof(vnode_config_data[0])*len);
        vnode_config_data2[y-1] = 0x7f;
        memcpy(&vnode_config_data2[y], &vnode_config_data[y], sizeof(vnode_config_data[0])*(SIZE-y));
    }
    else
    {
        memcpy(&vnode_config_data2[0], &vnode_config_data[0], sizeof(vnode_config_data[0])*y);
        vnode_config_data2[y] = 0x7f;
        memcpy(&vnode_config_data2[y+1], &vnode_config_data[y], sizeof(vnode_config_data[0])*len);
        memcpy(&vnode_config_data2[x], &vnode_config_data[x+1], sizeof(vnode_config_data[0])*(SIZE-x));
    }
    
    #if 0
    for (int i = 0; i < SIZE; ++i)
    {
        print_hex(i, 3);
        putchar(' ');
        print_hex(vnode_config_data2[i], 2);
        putchar('\n');
    }
    #endif
    
    return 0;
}

int next_val(int x)
{
    int i = x+1;
    for (; i < SIZE; ++i)
    {
        for (int j = x; j < i; ++j)
            if (vnode_config_data[j] != 0x7f)
            {
                return i;
            }
    }
    return SIZE;
}

void main()
{
    reg_gpio_mode1 = 1;
    reg_gpio_mode0 = 0;
    reg_gpio_ien = 1;
    reg_gpio_oeb = 0;
    
    reg_uart_enable = 1;
    reg_wb_enable = 1;

    configure_io();

    // Configure All LA probes as inputs to the cpu
	reg_la0_oenb = reg_la0_iena = 0x00000000;    // [31:0]
	reg_la1_oenb = reg_la1_iena = 0x00000000;    // [63:32]
	reg_la2_oenb = reg_la2_iena = 0x00000000;    // [95:64]
	reg_la3_oenb = reg_la3_iena = 0x00000000;    // [127:96]

    // Reset FPGA & terminate pads
    write_user_reg(OFF_CONFIG_RSTCFG, 3);
    load_scanchain(lblock_config_words, lblock_config_data, OFF_CONFIG_LBLOCK, 1); // logic blocks
    load_scanchain(hnode_config_words, hnode_config_data, OFF_CONFIG_HRNODE, 4);   // horizontal routing nodes
    load_scanchain(vnode_config_words, vnode_config_data, OFF_CONFIG_VRNODE, 2);
    write_user_reg(OFF_CONFIG_RSTCFG, 0);
    delay(10000000);

    int i = 0xa;
    int j = 0xa;
    while (1)
    //for (int i = 0; i < SIZE; ++i)
    //for (int j = 0; j < SIZE; ++j)
    {
        j = next_val(j);
        if (j == SIZE)
        {
            j = 0xa;
            i = next_val(i);
            if (i == SIZE)
            {
                print("End!\n");
                return;
            }
        }
        
        if (mangle_data(i, j))
            continue;
            
        print("Vals: ");
        print_hex(i, 3);
        putchar(' ');    
        print_hex(j, 3);
        putchar('\n');
        
        print("Try\n");
        
        // Load config
        print("Reseting...\n");
        write_user_reg(OFF_CONFIG_RSTCFG, 3);
        
        print("Loading config...\n");
        #if 1
        load_scanchain(vnode_config_words, vnode_config_data2, OFF_CONFIG_VRNODE, 2);   // vertical routing nodes
        print("Done\n");
        
        // Release pads & FPGA reset
        print("Releasing FPGA reset...\n");
        write_user_reg(OFF_CONFIG_RSTCFG, 1);
        write_user_reg(OFF_CONFIG_RSTCFG, 0);
        
        // Reset WB logic in FPGA fabric
        print("Reseting FPGA WB logic...\n");
        write_user_reg(OFF_CONFIG_RSTCFG, 8);
        write_user_reg(OFF_CONFIG_RSTCFG, 0);
        //write_user_reg(OFF_CONFIG_RSTCFG, 6);     // force 1 on all outputs
        #else
        test_scanchain(320, OFF_CONFIG_VRNODE, 2, 7);
        //test_scanchain(800, OFF_CONFIG_HRNODE, 4, 2);
        #endif
        
        #if 0
        print_hex(read_user_reg(OFF_CONFIG_RSTCFG), 8);
        putchar('\n');
        print_hex(read_user_reg(OFF_CNT_ADDR), 8);
        putchar('\n');
        print_hex(read_user_reg(OFF_CONFIG_RSTCFG), 8);
        putchar('\n');
        #endif
        
        delay(10000000);
    }
}

