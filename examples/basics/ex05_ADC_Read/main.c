
#include <bsp.h>
#include <rtl.h>

void read_analog_0()
{

	float adc0 = Adc_GetVoltage(0);

	float vwc;
	if (adc0 < 1.1){
		vwc = (10*adc0) - 1;
	}
	else if(adc0 >= 1.1 & adc0 <= 1.3){
		vwc = (25*adc0) - 17.5;
	}
	else if(adc0 >= 1.3 & adc0 <= 1.82){
		vwc = (48.08*adc0) - 47.5;
	}
	else if(adc0 >= 1.82 & adc0 <= 2.2){
		vwc = (26.32*adc0) - 7.89;
	}


	Uart1_Printf("Voltage from signal: %.2f\r\n", adc0);
	Uart1_Printf("VWC: %.2f \r", vwc);
}

int main()
{
	System_Init();

	Adc_Init(); // Init ADC Function

	Timer_Create(1000, read_analog_0);

	System_Start();
}