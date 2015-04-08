#include <stdio.h>
#include <string.h>

void	pc2str(long pc, char *pcstr)
{
	int a;
	int b;
	int c;
	
	c = pc & 0x07;
	b = (pc >> 3) & 0xFF;
	a = (pc >> 11) & 0x07;
	
	sprintf(pcstr,"%01d-%03d-%01d",a,b,c);
}

void	pc2str644(long pc, char *pcstr)
{
	int a;
	int b;
	int c;
	
	c = pc & 0x0F;
	b = (pc >> 4) & 0x0F;
	a = (pc >> 8) & 0x3F;
	
	sprintf(pcstr,"%d-%d-%d",a,b,c);
}


int cstr2pc(const char *in)
{
	char *sstr;
	long a;
	long b;
	long c;
	long res;
	char *pos;
	
	pos = strstr(in,".");
	if(pos != NULL)
	{
		sscanf(in,"%ld.%ld.%ld",&a,&b,&c);
		res = a << 11;
		res += b << 3;
		res += c;
		return res;
	}

	pos = strstr(in,"-");
	if(pos != NULL)
	{
		sscanf(in,"%ld-%ld-%ld",&a,&b,&c);
		res = a << 11;
		res += b << 3;
		res += c;
		return res;
	}

	if((in[0]=='0') && ((in[1]=='x') || (in[1]=='X')))
	{
		sscanf(in,"0x%lX",&res);
	}
	else
	{
		sscanf(in,"%ld",&res);
	}
	return res;
}

int cstr6442pc(const char *in)
{
	char *sstr;
	long a;
	long b;
	long c;
	long res;
	char *pos;
	
	pos = strstr(in,".");
	if(pos != NULL)
	{
		sscanf(in,"%ld.%ld.%ld",&a,&b,&c);
		res = a << 8;
		res += b << 4;
		res += c;
		return res;
	}

	pos = strstr(in,"-");
	if(pos != NULL)
	{
		sscanf(in,"%ld-%ld-%ld",&a,&b,&c);
		res = a << 8;
		res += b << 4;
		res += c;
		return res;
	}

	sscanf(in,"%ld",&res);
	return res;
}


int main(int argc, char *argv[])
{
	long pc;
	char str[20];
	char str644[20];
	int i = 0;
	
	for(i=1;i<argc;i++)
	{
#ifdef	USE644
		pc = cstr6442pc(argv[i]);
#else
		pc = cstr2pc(argv[i]);
#endif
pc2str(pc,str);
		pc2str644(pc,str644);
		printf("Pointcode: DEC: %ld\tHEX: 0x%lX\tITU: %s\tNAT644:%s\n",pc,pc,str,str644);
	}
}
