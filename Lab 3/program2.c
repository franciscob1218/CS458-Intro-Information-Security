#include <stdio.h>

unsigned char abc[300] = {
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5'
};

unsigned char xyz[300] = {
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5'
};


int main()
{
        int i;
        int isSame=1;
        for(i = 0; i < 200; i++)
        {
                if(abc[i]!=xyz[i])
                        isSame=0;
        }
        if(isSame)
                printf("This would run the safe code and display the intended behaviour");
        else
                printf("This is where malicious code would be run");
        printf("\n");
}
