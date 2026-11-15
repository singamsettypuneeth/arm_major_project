#include "header.h"
// temp p0.29
//pot p0.28      for speed
//trigger p0.17
//echo p0.18
//left indicator intrpt1 0.14
//right indicator intrpt2 p0.15
//head light intrpt0 p0.16
//left indicator p0.22
//right indicator p0.23
//head light p0.24


CAN1 v1;

int main(){
        IODIR0|=(1<<17)|(1<<22)|(1<<23)|(1<<24); //output pins
        IOSET0=(1<<22)|(1<<23)|(1<<24);
        can1_init();
        adc_init();
        uart0_init(9600);
        config_ext_intrpt0();
        config_vic_for_ext_intrpt0();
        config_ext_intrpt1();
        config_vic_for_ext_intrpt1();
        config_ext_intrpt2();
        config_vic_for_ext_intrpt2();
        v1.id=0x123;
        v1.rtr=0;//data-frame
        v1.dlc=8;
        while(1){
                v1.byteA=0;
                v1.byteB=0;
                v1.byteA|=adc_read(2)&0X3FF;//temp sensor P0.29
                v1.byteA|=(adc_read(1)&0X3FF)<<10;//pot  P0.28
                uart0_tx_string("adc completed\r\n");
                v1.byteA|=(ultrasonic_read()&0x3FF)<<20;//ultrasonic sensor
                v1.byteB|=head_flag<<24;//head light
                v1.byteB|=right_flag<<23;//right indi
                v1.byteB|=left_flag<<22;//left indi
                uart0_tx_string("tx next\r\n");
                can1_tx(v1);//send data-frame
                delay_ms(300);
        }
}
