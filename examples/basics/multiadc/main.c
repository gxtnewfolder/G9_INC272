
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
	if (ph > 14){
		ph = 0;
	}
	Uart1_Printf("%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;\r\n", vwc, adc0, adc1, ph, adc2, adc3);
}


void uart1_line_received(void *evt)
{

	/**
	 * Get line data from the event
	 */
	uart_line_t *ue = (uart_line_t *)evt;
	const char *line = ue->buffer;

	/**
	 * Note: `line` variable contains `\r\n`
	 */

	Uart2_Printf("Received: %s", line);

	/**
	 * Control logic
	 */
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
}

int main()
{
	System_Init();
	Adc_Init(); // Init ADC Function
	Uart1_Init(115200, 64, 64);
	Uart1_SetRxLineCallback(uart1_line_received, 128);
	Timer_Create(1000, read_analog_All);
	System_Start();
}