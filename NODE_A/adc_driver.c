void adc_init(void){
PINSEL1|=0x15400000;
ADCR=0x00200400;
}

u32 adc_read(u32 channel){
ADCR|=1<<channel;
ADCR|=1<<24;
while(((ADDR>>31)&1)==0);
ADCR^=1<<24;
ADCR^=1<<channel;
return ((ADDR>>6)&0X3ff);
}

u32 ultrasonic_read(void){
        u32 time;
        IOCLR0=(1<<17);
        delay_us(2);
        IOSET0=(1<<17);
        delay_us(10);
        IOCLR0=(1<<17);
        while(!((IOPIN0>>18)&1));
        T1PR=60-1;
        T1TCR=2;
        T1TCR=1;
        while(((IOPIN0>>18)&1));
        T1TCR=0;
        time=T1TC;
        return (u32)(time/58);//in cm
}
