 #include "header.h"

CAN1 r1;
int temp;
float adc_to_temp(u32 adc){
        float vout=(adc*3.3)/1023;
        return vout*100;
}

float adc_to_speed(u32 adc){
        float speed=(adc*140)/1023;
        return speed;
}

int adc_to_fuel(u32 adc){//1cm=10lit
        return 50-adc*10;
}

int main(){
    int temp,speed,fuel;
        int left_indi,right_indi,head_light;
    can1_init();
        config_vic_for_can1();
    uart0_init(9600);
    IODIR0|=(1<<22)|(1<<23)|(1<<24);
    IOSET0=(1<<22)|(1<<23)|(1<<24);

    while(1){
                        //can1_rx(&r1);
                        if(flag){
                        flag=0;
            // for sensor reading
            temp=adc_to_temp(r1.byteA&0x3FF);
                        speed=adc_to_speed((r1.byteA>>10)&0x3FF);
            fuel=adc_to_fuel((r1.byteA>>20)&0x3FF);
                        if (fuel<0)
                                fuel=0;

            // for indicators
            left_indi=(r1.byteB>>22)&1;
            right_indi=(r1.byteB>>23)&1;
            head_light=(r1.byteB>>24)&1;

            // temp
            uart0_tx_string("TEMP: ");
            uart0_integer(temp);
            uart0_tx_string("C\r\n");
                        delay_ms(20);

            // speed
            uart0_tx_string("SPEED: ");
            uart0_integer(speed);
            uart0_tx_string("km/h\r\n");
                        delay_ms(20);

            // fuel
            uart0_tx_string("FUEL LEVEL: ");
            uart0_integer(fuel);
            uart0_tx_string("L\r\n");
                        delay_ms(20);

            // left indi
            if(left_indi)
                uart0_tx_string("<--");
            else
                uart0_tx_string("  ");
                        delay_ms(20);

            // head light
            if(head_light)
                uart0_tx_string("*..*");
            else
                uart0_tx_string("   ");
                        delay_ms(20);

            // right indi
            if(right_indi)
                uart0_tx_string("-->");
            else
                uart0_tx_string("  ");
                        delay_ms(20);
                        uart0_tx_string("\r\n");
                        }

                // headlight control
        if(head_light)
            IOCLR0=1<<24;
        else
            IOSET0=1<<24;

        // indi control
        if(left_indi){
                        IOSET0=1<<23;
                        IOCLR0=1<<22;
                        delay_ms(100);
                        IOSET0=1<<22;
                        delay_ms(100);
                        }
        else if(right_indi){
                        IOSET0=1<<22;
                        IOCLR0=1<<23;
                        delay_ms(100);
                        IOSET0=1<<23;
                        delay_ms(100);
                        }
                else{
                IOSET0=1<<22;
                IOSET0=1<<23;
                }

         delay_ms(300);
        }
}
