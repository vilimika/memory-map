#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

void print_top()
{
	for(int i=0;i<2;i++) {
		if(i==0)
			printf("      +------+------+------+------+ 00000000\n");
		printf("      +------+------+------+------+\n");	
        }
}

void print_bottom()
{
	for(int i=0;i<2;i++) {
		if(i==1)
			printf("      +------+------+------+------+ FFFFFFFF\n");
		printf("      +------+------+------+------+\n");	
        }
}
		 
void print_split(void* addr, char* prefix)
{
	if (prefix == NULL)
	{
		prefix = "";
	}
	if (addr == NULL)
	{
		printf("%-6s+------+------+------+------+\n", prefix);
		return;
	}
	printf("%-6s+------+------+------+------+ %p\n", prefix, addr);
}
 
void print_data(void* address, int length, char* prefix, bool is_chars)
{
	unsigned char* data = (unsigned char*) address;
	for (int section = 0; section < length; section += sizeof(int))
	{
		print_split(NULL, NULL);
		printf("%-6s", prefix == NULL ? "" : prefix);

		for (int index = section + sizeof(int) - 1; index >= section; index--)
		{
			if (index < 0)
			{
				printf("|  --  ");
				continue;
			}
 
			unsigned char part = data[index];
			if (!is_chars)
			{
				printf("|  %02x  ", part);
			}
			else
			{
				printf("|  %2c  ", part);
			}
		}
 
		printf("|");
		if (address != NULL)	{
			printf(" %p", address);
		}
		printf("\n");
	}
	 
	print_split(NULL, NULL);
}
		 
		 
int main(int argc, char **argv)
{
//	printf("%p", &*(argv+1));
	print_top();
	print_data(&argv, sizeof(int), "argv" , false); 
	print_data(&argc, sizeof(argc), "argc", false);
	for (int i = 0; i < argc-1; i++)
        {       
		 char buffer[6]; 
                 sprintf(buffer, "argv+%d", i+1);
                 print_data(&*(argv+i), sizeof(int), buffer, false);
        }
	for (int i = 1; i < argc; i++)
	{
		print_data(argv[i], (int) strlen(argv[i]), "", true);
	}
	print_bottom();
		 
}
