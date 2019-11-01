/* This program deals with manipulation of text file
   not binary file, therefore fprintf and fscanf are used
   to write and read to a file */

#include<stdio.h>
#include<conio.h>
#include<string.h>

void err(int n)
{
	if(n==0)
	{
		clrscr();
		printf("\n\nERROR");
		printf("\n\n\tFile could not be made");
		printf("\n\n\tMake sure the path is correct\n\n");
		getch();
	}

	else if(n==1)
	{
		clrscr();
		printf("\n\nERROR");
		printf("\n\n\tFile not found");
		printf("\n\n\tBe sure to write exact path and filename\n\n");
		getch();
	}

	else if(n==2)
	{
		clrscr();
		printf("\n\nERROR");
		printf("\n\n\tEncrypted file could not be created");
		printf("\n\n\tPress any key to exit\n\n");
		getch();
	}
}

int mak_fil()
{
	char f_nam_p[100],strng[100],f_nam_n[100],f_nam[200];
	FILE *fp;
	clrscr();
	printf("\nEnter the exact path of the file : ");
	scanf("%s",&f_nam_p);
	printf("\nEnter the name of the file : ");
	scanf("%s",&f_nam_n);
	strncat(f_nam_p,"/",1);
	strcat(f_nam, f_nam_p);
	strcat(f_nam, f_nam_n);
	fp = fopen(f_nam, "w");
	if(fp==NULL)
	{
		err(0);
		return 1;
	}
	printf("\n\nEnter the string to be stored in file :-\n");
	gets(strng);	//clear the input buffer generated due to scanf()
	gets(strng);
	fprintf(fp,"%s",strng);
	fclose(fp);
	getch();
	return 0;
}

int encr_fil()
{
	char f_nam[200],ch,f_nam_p[100],f_nam_n[100],count=0;
	int u=65;
	FILE *fp,*fp_new;
	clrscr();
	printf("\nEnter the exact path of the file : ");
	scanf("%s",&f_nam_p);
	printf("\nEnter the name of the file : ");
	scanf("%s",&f_nam_n);
	strncat(f_nam_p,"/",1);
	f_nam[0]='\0';   		//neccessary to make the path correct
	strcat(f_nam, f_nam_p);
	strcat(f_nam, f_nam_n);
	fp = fopen(f_nam, "r");
	if(fp==NULL)
	{
		err(1);
		return 1;
	}
	fp_new = fopen("buffer.txt","w");
	if(fp_new==NULL)
	{
		err(2);
		return 1;
	}
	while(ch!=EOF)
	{
		ch=fgetc(fp);
		if(ch==EOF)
		{
			break;
		}
		else
		{
			count++;
		}
	}
	printf("Total characters : %d",count);
	getch();
	ch=0;
	fseek(fp,0,0);
	while(ch!=EOF)
	{
		ch=fgetc(fp);
		if(ch==EOF)
		{
			break;
		}
		else
		{
			ch+=(count+u);
			fputc(ch, fp_new);
			u+=2;
		}
	}
	fclose(fp);
	fclose(fp_new);
	fp = fopen(f_nam,"w");
	if(fp==NULL)
	{
		err(1);
		return 1;
	}
	fp_new = fopen("buffer.txt","r");
	if(fp_new==NULL)
	{
		err(1);
		return 1;
	}
	ch=0;
	fseek(fp_new,0,0);
	fseek(fp,0,0);
	while(ch!=EOF)
	{
		ch=fgetc(fp_new);
		if(ch==EOF)
		{
			break;
		}
		else
		{
			fputc(ch, fp);
		}
	}
	getch();
	return 0;
}

int decr_fil()
{
	char f_nam[200],ch,f_nam_p[100],f_nam_n[100],count=0;
	int u=65;
	FILE *fp,*fp_new;
	clrscr();
	printf("\nEnter the exact path of the file : ");
	scanf("%s",&f_nam_p);
	printf("\nEnter the name of the file : ");
	scanf("%s",&f_nam_n);
	f_nam[0]='\0';
	strncat(f_nam_p,"/",1);
	strcat(f_nam, f_nam_p);
	strcat(f_nam, f_nam_n);
	fp = fopen(f_nam, "r");
	if(fp==NULL)
	{
		err(1);
		return 1;
	}
	fp_new = fopen("buffer.txt","w");
	if(fp_new==NULL)
	{
		err(2);
		return 1;
	}
	while(ch!=EOF)
	{
		ch=fgetc(fp);
		if(ch==EOF)
		{
			break;
		}
		else
		{
			count++;
		}
	}
	ch=0;
	fseek(fp,0,0);
	while(ch!=EOF)
	{
		ch=fgetc(fp);
		if(ch==EOF)
		{
			break;
		}
		else
		{
			ch-=(count+u);
			fputc(ch, fp_new);
			u+=2;
		}
	}
	fclose(fp);
	fclose(fp_new);
	fp = fopen(f_nam,"w");
	if(fp==NULL)
	{
		err(1);
		return 1;
	}
	fp_new = fopen("buffer.txt","r");
	if(fp_new==NULL)
	{
		err(1);
		return 1;
	}
	ch=0;
	fseek(fp,0,0);
	fseek(fp_new,0,0);
	while(ch!=EOF)
	{
		ch=fgetc(fp_new);
		if(ch==EOF)
		{
			break;
		}
		else
		{
			fputc(ch, fp);
		}
	}
	getch();
	return 0;
}

void main()
{
	int i=0,ans;
start:
	clrscr();
	printf("\nChoose the action you want to perform : ");
	printf("\n\n\n1) Create a file\t2) Encrypt a file");
	printf("\n\n3) Decrypt a file\t4) Exit\n");
	printf("\n\n\nInput option : ");
	scanf("%d",&ans);
	switch(ans)
	{
		case 1:
			i = mak_fil();
			if(i==1)
			{
				exit();
			}
			break;

		case 2:
			i = encr_fil();
			if(i==1)
			{
				exit();
			}
			break;

		case 3:
			i = decr_fil();
			if(i==1)
			{
				exit();
			}
			break;

		default :
			goto start;
			exit();
	}
}
