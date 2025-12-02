void delay_us(int dlyUs)
{
	dlyUs=dlyUs*12;
	for(;dlyUs;dlyUs--);
}

void delay_ms(int dlyMs)
{
	dlyMs=dlyMs*12000;
	for(;dlyMs;dlyMs--);
}

void delay_s(int dlyS)
{
	dlyS=dlyS*12000000;
	for(;dlyS;dlyS--);
}
