#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include "pico/multicore.h"
#include "Prompt.hpp"
#include <cstdio>
#include <string>
#include <malloc.h>

    Prompt my_prompt("AHU_2040");

static void
display_mallinfo2(void)
{
    struct mallinfo mi;

    mi = mallinfo();
    printf("============================================\n");
    printf("Total non-mmapped bytes (arena):       %zu\n", mi.arena);
    printf("# of free chunks (ordblks):            %zu\n", mi.ordblks);
    printf("# of free fastbin blocks (smblks):     %zu\n", mi.smblks);
    printf("# of mapped regions (hblks):           %zu\n", mi.hblks);
    printf("Bytes in mapped regions (hblkhd):      %zu\n", mi.hblkhd);
    printf("Max. total allocated space (usmblks):  %zu\n", mi.usmblks);
    printf("Free bytes held in fastbins (fsmblks): %zu\n", mi.fsmblks);
    printf("Total allocated space (uordblks):      %zu\n", mi.uordblks);
    printf("Total free space (fordblks):           %zu\n", mi.fordblks);
    printf("Topmost releasable block (keepcost):   %zu\n", mi.keepcost);
    malloc_stats();
    }

void callback(int id, const std::string &str)
{
    if (str.empty())
        return;

        printf("Received : id=%d arg=[%s]\n ", id, str.c_str());
}




void main_2(void)
{

    // Set up our UART with a basic baud rate.
    //stdio_init_all();

    printf("Modbus RTU slave started\n");
    


    my_prompt.attachFnKeyCallback(FnKey::F1, []()
                                  { printf("F1\n"); });
    my_prompt.attachFnKeyCallback(FnKey::F2, []()
                                  { printf("F2\n"); });
    my_prompt.attachFnKeyCallback(FnKey::F3, []()
                                  { printf("F3\n"); });
    my_prompt.attachFnKeyCallback(FnKey::F4, []()
                                  { printf("F4\n"); });
    my_prompt.attachFnKeyCallback(FnKey::F5, []()
                                  { printf("F5\n"); });

    my_prompt.insertMapElement("settings show", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("settings save", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("settings read", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("settings restore_default", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("system bootsel", [](std::string x)
                                  { reset_usb_boot(0, 0); });
    my_prompt.insertMapElement("system reset", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("system show info", [](std::string x)
                                  { display_mallinfo2(); });

    my_prompt.insertMapElement("operation show", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("operation set idle", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("operation set cool", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("operation set heat", std::bind(callback, 0, std::placeholders::_1));

    my_prompt.insertMapElement("modbus input_registers show", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("modbus holding_registers show", std::bind(callback, 1, std::placeholders::_1));
    my_prompt.insertMapElement("modbus holding_registers set", std::bind(callback, 2, std::placeholders::_1));
    my_prompt.insertMapElement("modbus show_info", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("control set local_0-10V", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("control set remote_0-100", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("control set remote_temperature", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("level set", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("level show", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("level increment", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("level decrement", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("temperature target set", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("temperature target show", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("temperature mode set static", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("temperature mode set dynamic", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("temperature show", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("temperature delta_low set", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("temperature delta_high set", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("temperature idle_time set", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("temperature dynamic test", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("temperature dynamic gain set", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("temperature dynamic offset set", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("temperature pid k_p set", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("temperature pid k_i set", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("temperature pid k_d set", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("temperature pid interval set", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("temperature pid hysteresis set", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("temperature pid show", std::bind(callback, 0, std::placeholders::_1));

    my_prompt.insertMapElement("oil low_freq set", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("oil interval set", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("oil target_frequency set", std::bind(callback, 0, std::placeholders::_1));
    my_prompt.insertMapElement("oil show", std::bind(callback, 0, std::placeholders::_1));


    my_prompt.updateAuxMenu("");
    
    while (1)
    {
        //printf("nic,\n");
        my_prompt.handleKey();
        //sleep_ms(1000);
    }
}

void stack_killer(void)
{
    static int iterations = 0;
    iterations++;
    
    int tab[10];
    printf("iter = %d, tab = %x, \n",iterations, tab);
    sleep_ms(10);
    stack_killer();
}

int main()
{
    stdio_init_all();
    int cnt = 0;
    multicore_launch_core1(main_2);
    //stack_killer();

    while(1)
    {
        //display_mallinfo2();
        
        //void *p = malloc(1000);
        //printf("cnt = %d, p = %x\n", cnt++, p);
        //memset(p,0,1000);
        sleep_ms(100);
    }
}