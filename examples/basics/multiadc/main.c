
#include <bsp.h>
#include <rtl.h>

void read_analog_All()
{

	double adc0 = Adc_GetVoltage(0);
	double adc1 = Adc_GetVoltage(1);

	double vwc;
	if (adc0 < 1.1){
		vwc = (10*adc0) - 1; // 0.0 - 10.0
	}
	else if(adc0 >= 1.1 && adc0 <= 1.3){
		vwc = (25*adc0) - 17.5; // 10.0 - 15.4
	}
	else if(adc0 >= 1.3 && adc0 <= 1.82){
		vwc = (48.08*adc0) - 47.5; // 15.4 - 40.2
	}
	else if(adc0 >= 1.82 && adc0 <= 2.2){
		vwc = (26.32*adc0) - 7.89; // 40.2 - 50.0
	}
	else if(adc0 >= 2.2 && adc0 <= 2.5){
		vwc = (48.78*adc0) - 52; // 50.0 - 70.0
	}
	else if(adc0 >= 2.5 && adc0 <= 3.3){
		vwc = (26.32*adc0) + 4; // 70.0 - 100.0
	}
	else{
		vwc = 0;
	}

	double ph;
	double h_conc = 1e-4; // hydrogen ion concentration in moles per liter
	ph = adc1 / (0.0592 / -log10(h_conc));
	if (ph > 14){
		ph = 0;
	}
	Uart1_Printf("%.2f;%.2f;%.2f;%.2f;\r\n", adc0, vwc, adc1, ph);
}


void uart1_line_received(void *evt)
{
	uart_line_t *ue = (uart_line_t *)evt;
	const char *line = ue->buffer;

	if (!strcmp(line, "led,0,1\r\n"))
	{
		Uart2_Printf("LED1 ON");
		Led0_Set();
	}
	else if (!strcmp(line, "led,0,0\r\n"))
	{
		Uart2_Printf("LED1 OFF");
		Led0_Clr();
	}
	else if (!strcmp(line, "led,1,2\r\n"))
	{
		Uart2_Printf("LED2 ON");
		Led1_Inv();
	}
	else if (!strcmp(line, "led,1,0\r\n"))
	{
		Uart2_Printf("LED2 OFF");
		Led1_Clr();
	}
	else if (!strcmp(line, "led,2,2\r\n"))
	{
		Uart2_Printf("LED3 ON");
		Led2_Inv();
	}
	else if (!strcmp(line, "led,2,0\r\n"))
	{
		Uart2_Printf("LED3 OFF");
		Led2_Clr();
	}
}

int main()
{
	System_Init();
	Adc_Init(); // Init ADC Function
	Uart1_Init(115200, 64, 64);
	// Uart2_Init(115200, 64, 64);
	Uart1_SetRxLineCallback(uart1_line_received, 128);
	Timer_Create(1000, read_analog_All);
	System_Start();
}