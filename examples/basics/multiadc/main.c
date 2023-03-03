
#include <bsp.h>
#include <rtl.h>

void read_analog_All()
{

	float adc0 = Adc_GetVoltage(0);
	double adc1 = Adc_GetVoltage(1);
	float adc2 = Adc_GetVoltage(2);
	float adc3 = Adc_GetVoltage(3);

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

	double ph;
	double h_conc = 1e-4; // hydrogen ion concentration in moles per liter
	ph = adc1 / (0.0592 / -log10(h_conc)); 
	Uart1_Printf("%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;\r\n", vwc, adc0, adc1, ph, adc2, adc3);
}

int main()
{
	System_Init();
	Adc_Init(); // Init ADC Function
	Timer_Create(1000, read_analog_All);
	System_Start();
}