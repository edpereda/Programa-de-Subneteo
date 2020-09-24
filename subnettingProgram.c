#include <stdio.h>
#include<math.h>
//---------------------------------------------------------------------------Prototipos
void RPredef(unsigned char[], unsigned char);
void calculoC(unsigned char[], unsigned char);
void calculoB(unsigned char[], unsigned char);
void calculoA(unsigned char[], unsigned char);
void seleccionC(unsigned char[], unsigned char);
void seleccionB(unsigned char[], unsigned char);
void seleccionA(unsigned char[], unsigned char);
unsigned char calcularmascararedHOSTS(int, unsigned char);
int calcularmascararedSUBREDES(int, unsigned char);

void calculoC(unsigned char ip[], unsigned char mp)
{
	unsigned char i, rd;
	unsigned char mr;
	mr=0;

	if (mp<24)
		mp=24;
	

	mp=mp-24;
	for(i=0; i <= mp; i++)//MP para clase C
		mr=mr + pow(2, 8-i);
	printf("   mascara personalizada:	255.255.255.%d\n", mr);
	printf("   bits prestados:	%d\n\n", mp);

	mp=pow(2, mp);//divisor de red

	rd= 255/mp;//divicion total de la red
	ip[3]=0;
	printf("	| Dir subred |	Rango subred		|   Broadcast\n");
	for (i = 0; i < mp; i++)
	{//192.1.12.25/26
		printf("%d	", i);
		printf("%d.%d.%d.%d	", ip[0], ip[1], ip[2], ip[3]);
		printf("%d.%d.%d.%d  -  ", ip[0], ip[1], ip[2], (ip[3]+1));
		ip[3]=ip[3]+rd;
		printf("%d.%d.%d.%d	 ", ip[0], ip[1], ip[2], ip[3]-1);
		printf("%d.%d.%d.%d\n", ip[0], ip[1], ip[2], ip[3]);
		ip[3]++;
	}	
}
void calculoB(unsigned char ip[], unsigned char mp)
{
	unsigned char j, rd;
	unsigned char mr;
	int cont, i;
	mr=0;
	cont=0;
	
	if (mp<16)
		mp=16;
	
	
	mp=mp-16;
	if(mp>7)//MP para la clase B
	{
		for(i=0; i <= mp-8; i++)
			mr=mr + pow(2, 8-i);
		printf("   mascara personalizada:	255.255.255.%d\n", mr);
		printf("   bits prestados:	%d\n\n", mp);
		printf("	| Dir subred |	Rango subred		|   Broadcast\n");
		mp=pow(2, mp-8);//divisor de red
		rd= 255/mp;//divicion total de la red
		ip[2]=0;
		ip[3]=0;
		
		for (i=0; i<256; i++)
		{//190.1.12.25/26
			for (j = 0; j < mp; j++)
			{
				printf("%d	", cont); cont++;
				printf("%d.%d.%d.%d	 ", ip[0], ip[1], ip[2], ip[3]);
				printf("%d.%d.%d.%d  -  ", ip[0], ip[1], ip[2], (ip[3]+1));
				ip[3]=ip[3]+rd;
				printf("%d.%d.%d.%d	 ", ip[0], ip[1], ip[2], ip[3]-1);
				printf("%d.%d.%d.%d\n", ip[0], ip[1], ip[2], ip[3]);
				ip[3]++;
			}
			ip[3]=0;
			ip[2]++;
			//mr=getch();
		}/**/
	}
	else//   .../(<23)
	{
		for(i=0; i<=mp; i++)
			mr=mr + pow(2, 8-i);
		printf("   mascara personalizada:	255.255.%d.0\n", mr);
		printf("   bits prestados:	%d\n\n", mp);
		mp=pow(2, mp);//divisor de red
		rd= 255/mp;//divicion total de la red
		ip[2]=0; 
		ip[3]=0;
		printf("	| Dir subred |	Rango subred		|   Broadcast\n");
		for (i = 0; i < mp; i++)
		{//192.1.12.25/26
			printf("%d	", i);
			printf("%d.%d.%d.%d	 ", ip[0], ip[1], ip[2], ip[3]);
			printf("%d.%d.%d.%d  -  ", ip[0], ip[1], ip[2], ip[3]+1);
			ip[2]=ip[2]+rd;
			printf("%d.%d.%d.%d	 ", ip[0], ip[1], ip[2], ip[3]+254);
			printf("%d.%d.%d.%d\n", ip[0], ip[1], ip[2], ip[3]+255);
			ip[2]++;
		}	
	}
}
void calculoA(unsigned char ip[], unsigned char mp)
{
	unsigned char rd;
	unsigned char mr;
	int cont, i, k, j;
	mr=0;
	cont=0;
	
	if (mp<8)
		mp=8;
	
	mp=mp-8;
	if (mp>15)
	{
		for(i=0; i <= mp-16; i++)
			mr=mr + pow(2, 8-i);
		printf("   mascara personalizada:	255.255.255.%d\n", mr);
		printf("   bits prestados:	%d\n\n", mp);
		printf("	| Dir subred |	Rango subred		|   Broadcast\n");
		mp=pow(2, mp-16);//divisor de red
		rd= 255/mp;//divicion total de la red
		ip[1]=0;
		ip[2]=0;
		ip[3]=0;
		
		for (i=0; i<256; i++)
		{
			for (j=0; j<256; j++)
			{//12.1.12.25/26
				for (k=0; k<mp; k++)
				{
					printf("%d	", cont); cont++;
					printf("%d.%d.%d.%d	 ", ip[0], ip[1], ip[2], ip[3]);
					printf("%d.%d.%d.%d  -  ", ip[0], ip[1], ip[2], ip[3]+1);
					ip[3]=ip[3]+rd;
					printf("%d.%d.%d.%d	 ", ip[0], ip[1], ip[2], ip[3]-1);
					printf("%d.%d.%d.%d\n", ip[0], ip[1], ip[2], ip[3]);
					ip[3]++;
				}
				ip[3]=0;
				ip[2]++;
				//mr=getch();
			}
			ip[2]=0;
			ip[1]++;
			printf("\n\n\n rd= %d\n\n", rd);
			mr=rd;
			printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\nterminar: no(0) si(1)");
				scanf("%d", &mr);
			printf("\n\n\n rd= %d\n\n", rd);
			if(mr)
				i=255;
		}
	}/**/
	else if(mp>7)//MP para la clase A
	{
		for(i=0; i <= mp-8; i++)
			mr=mr + pow(2, 8-i);

		printf("   mascara personalizada:	255.0.%d.0\n", mr);
		printf("   bits prestados:	%d\n\n", mp);
		printf("	| Dir subred |	Rango subred		|   Broadcast\n");
		mp=pow(2, mp-8);//divisor de red
		rd= 255/mp;//divicion total de la red
		ip[1]=0;
		ip[2]=0;
		ip[3]=0;
		
		for (i=0; i<256; i++)
		{//12.1.12.25/26
			for (j = 0; j < mp; j++)
			{
				printf("%d	", cont); cont++;
				printf("%d.%d.%d.%d	 ", ip[0], ip[1], ip[2], ip[3]);
				printf("%d.%d.%d.%d  -  ", ip[0], ip[1], ip[2], ip[3]+1);
				ip[2]=ip[2]+rd;
				printf("%d.%d.%d.%d	 ", ip[0], ip[1], ip[2], ip[3]+254);
				printf("%d.%d.%d.%d\n", ip[0], ip[1], ip[2], ip[3]+255);
				ip[2]++;
			}
			ip[2]=0;
			ip[1]++;
			mr=getch();

		}/**/
	}
	else//   .../(<15)
	{
		for(i=0; i<=mp; i++)
			mr=mr + pow(2, 8-i);
		printf("   mascara personalizada:	255.%d.0.0\n", mr);
		printf("   bits prestados:	%d\n\n", mp);

		mp=pow(2, mp);//divisor de red
		rd= 255/mp;//divicion total de la red
		ip[1]=0;
		ip[2]=0; 
		ip[3]=0;
		printf("	| Dir subred |	Rango subred		|   Broadcast\n");
		for (i = 0; i < mp; i++)
		{//192.1.12.25/26
			printf("%d	", i);
			printf("%d.%d.%d.%d	 ", ip[0], ip[1], ip[2], ip[3]);
			printf("%d.%d.%d.%d  -  ", ip[0], ip[1], ip[2], ip[3]+1);
			ip[1]=ip[1]+rd;
			printf("%d.%d.%d.%d	 ", ip[0], ip[1], ip[2]+255, ip[3]+254);
			printf("%d.%d.%d.%d\n", ip[0], ip[1], ip[2]+255, ip[3]+255);
			ip[1]++;
		}	
	}
}

void RPredef(unsigned char ip[], unsigned char mp)
{
	unsigned char mr[4], tipo;
	
	mr[0]=255;
	mr[1]=255;
	mr[2]=255;
	mr[3]=255;

	printf("\n\n   IP:		%d.%d.%d.%d\n", ip[0], ip[1], ip[2], ip[3]);
	if(ip[0] & 128)
	{
		if(ip[0] & 64)
		{
			if(ip[0] & 32)
			{
				if(ip[0] & 16)
				{
					printf("   CLASE E\n");
					mr[0]=0;
					tipo=3;
				}
				else
				{
					printf("   CLASE D\n");	
					mr[0]=0;
					tipo=3;
				}
			}
			else
			{
				printf("   CLASE C\n");
				mr[3]=0;
				printf("   Tipo: ");
					if(ip[3]==0)//
						printf("red\n");
					else if(ip[3]==255)//
						printf("Broadcast\n");
					else//
						printf("host\n");
				printf("   Rango:			%d.%d.%d.%d   -   ", (ip[0]), (ip[1]), (ip[2]), ((ip[3] & mr[3]) + 1));
				printf("%d.%d.%d.%d \n", (ip[0]), (ip[1]), (ip[2]), ((ip[3] & mr[3]) + 254));
				tipo=0;
			}
		}
		else
		{
			printf("   CLASE B\n");
			mr[2]=0;
			mr[3]=0;
			printf("   Tipo: ");
				if(ip[2]==0)//
				{
					if (ip[3]==0)
						printf("red\n");
				}
				else if(ip[2]==255)//
				{
					if(ip[3]==255)
						printf("Broadcast\n");
				}
				else//
				{
					printf("host\n");
				}
			printf("   Rango:			%d.%d.%d.%d   -   ", (ip[0]), (ip[1]), ((ip[2] & mr[2])), ((ip[3] & mr[3]) + 1));
			printf("%d.%d.%d.%d \n", (ip[0]), (ip[1]), ((ip[2] & mr[2]) + 255), ((ip[3] & mr[3]) + 254));
			tipo=1;
		}
	}
	else
	{
		printf("   CLASE A\n");
		mr[1]=0;
		mr[2]=0;
		mr[3]=0;
		printf("   Tipo: ");
			if(ip[1]==0)//
			{
				if (ip[2]==0)
				{
					if (ip[3]==0)
						printf("red\n");
				}
			}
			else if(ip[1]==255)//
			{
				if(ip[2]==255)
				{
					if(ip[3]==255)
						printf("Broadcast\n");
				}
			}
			else//
			{
				printf("host\n");
			}
		printf("   Rango:			%d.%d.%d.%d   -   ", (ip[0]), ((ip[1] & mr[1])), ((ip[2] & mr[2])), ((ip[3] & mr[3]) + 1));
		printf("%d.%d.%d.%d \n", (ip[0]), ((ip[1] & mr[1]) + 255), ((ip[2] & mr[2]) + 255), ((ip[3] & mr[3]) + 254));
		tipo=2;
	}
	if(mr[0])
	{
		printf("   Mascara de red:		%d.%d.%d.%d \n", mr[0], mr[1], mr[2], mr[3]);
		printf("   IP madre:			%d.%d.%d.%d \n", (ip[0] & mr[0]), (ip[1] & mr[1]), (ip[2] & mr[2]), (ip[3] & mr[3]));
		mr[0]=~mr[0];
		mr[1]=~mr[1];
		mr[2]=~mr[2];
		mr[3]=~mr[3];
		printf("   IP Broadcast:		%d.%d.%d.%d \n", (ip[0] | mr[0]), (ip[1] | mr[1]), (ip[2] | mr[2]), (ip[3] | mr[3]));	
	}
	else
		printf("   Es una IP reservada\n");
////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	switch(tipo)
	{
		case 0:
			
			if(!mp)
				mp=24;
				
			//calculoC(ip,mp);
			seleccionC(ip,mp);
			break;
			
		case 1:
			if(!mp)
				mp=16;
				
			//calculoB(ip, mp);
			seleccionB(ip,mp);
			break;
		case 2:
			if(!mp)
				mp=8; 
			//calculoA(ip, mp);
			seleccionA(ip,mp);
			break;
		default:
			break;
	}/**/
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	unsigned char ip[5];
	int numhosts;
	ip[0]=0;
	ip[1]=0;
	ip[2]=0;
	ip[3]=0;
	ip[4]=0;
	//printf("\nhola Nidia\nmi ip: 8.12.0.174\nmi mac: D8-CB-8A-D5-7D-38\n\nINGRESA UNA IP: ");
	printf("\nINGRESA UNA IP: ");
	scanf("%d.%d.%d.%d/%d", &ip[0], &ip[1], &ip[2], &ip[3], &ip[4]);
	if(!ip[0])
		ip[0]=1;
	if(ip[4]>30)
		ip[4]=0;

	RPredef(ip, ip[4]);

	printf("continuar?.... 0(no) 1(si)");
	scanf("%d", &ip[0]);
	if(ip[0])
		main();
	return 0;	
}

unsigned char calcularmascararedHOSTS(int numhosts,unsigned char tipo){
int i=0,contador=0;
	
	switch(tipo){
		
		case 3:	
			contador=30;
			for (i=4;i<=256;i=i<<1){
				printf("Contador: %d",contador);
				system ("pause");
				if (numhosts<=i)
					return contador;
				contador--;
			}
			break;
			
		case 2:
			contador=30;
			for (i=4;i<=65536;i=i<<1){
				printf("Contador: %d",contador);
				system ("pause");
				if (numhosts<=i)
					return contador;
				contador--;
			}
			break;
			
		case 1:
			contador=30;
			for (i=4;i<=16777216;i=i<<1){
				printf("Contador: %d",contador);
				system ("pause");
				if (numhosts<=i)
					return contador;
				contador--;
			}
			break;
	}
}

void seleccionC(unsigned char ip[], unsigned char mr){
	unsigned char opcion=4, mp=mr,reintentar=0;
	int numhosts=0,numsubredes=0;
	do{
	printf("\n\n\n");
		reintentar=0;
	printf("\n\n1. Ingresar submascara de red \n"
		   "2. Ingresar numero de Hosts\n"
		   "3. Ingresar numero de Subredes\n"
		   "Opcion: ");
	scanf("%d",&opcion);
	
		switch(opcion){
		case 1:
				printf("\nIngrese la submascara: ");
				scanf("%d",&mp);  
				calculoC(ip,mp);
			break;
			
		case 2:
				printf("\nIngrese el numero de Hosts: ");
				scanf("%d",&numhosts);
				calculoC(ip,calcularmascararedHOSTS(numhosts,3));  //el tres es para clase c
			break;
			
		case 3:
				printf("\nIngrese el numero de Subredes: ");
				scanf("%d",&numsubredes);
				calculoC(ip,calcularmascararedSUBREDES(numsubredes,3));
			break;
		}
		printf("\nDesea otra forma? (no/0)(si/1)");
		scanf("%d",&reintentar);
	}while(reintentar!=0);
	
}

void seleccionB(unsigned char ip[], unsigned char mr){
	unsigned char opcion=4, mp=mr,reintentar=0;
	int numhosts=0;
	do{
	printf("\n\n\n");
		reintentar=0;
	printf("\n\n1. Ingresar submascara de red \n"
		   "2. Ingresar numero de Hosts\n"
		   "3. Ingresar numero de Subredes\n"
		   "Opcion: ");
	scanf("%d",&opcion);
	
		switch(opcion){
		case 1:
				printf("\nIngrese la submascara: ");
				scanf("%d",&mp); 
				calculoB(ip,mp);
			break;
			
		case 2:
				printf("\nIngrese el numero de Hosts: ");
				scanf("%d",&numhosts);
				calculoB(ip,calcularmascararedHOSTS(numhosts,2));  //el tres es para clase c
			break;
		case 3:
			//aqui pones parte del codigo
			break;
		}
		printf("\nDesea otra forma? (no/0)(si/1)");
		scanf("%d",&reintentar);
	}while(reintentar!=0);
	
}

void seleccionA(unsigned char ip[], unsigned char mr){
	unsigned char opcion=4, mp=mr,reintentar=0;
	int numhosts=0;
	do{
	printf("\n\n\n");
		reintentar=0;
	printf("\n\n1. Ingresar submascara de red \n"
		   "2. Ingresar numero de Hosts\n"
		   "3. Ingresar numero de Subredes\n"
		   "Opcion: ");
	scanf("%d",&opcion);
	
		switch(opcion){
		case 1:
				printf("\nIngrese la submascara: ");
				scanf("%d",&mp);  //reutilice la variable
				calculoA(ip,mp);
			break;
			
		case 2:
				printf("\nIngrese el numero de Hosts: ");
				scanf("%d",&numhosts);
				calculoA(ip,calcularmascararedHOSTS(numhosts,1));  //el tres es para clase c
			break;
		case 3:
			//aqui pones parte del codigo
			break;
		}
		printf("\nDesea otra forma? (no/0)(si/1)");
		scanf("%d",&reintentar);
	}while(reintentar!=0);
	
}

int calcularmascararedSUBREDES(int subredes,unsigned char tipo){
 int contador=0,i=1;
 	
	switch(tipo){
		case 1:
			contador=8;
			
			for (i=1;i<256;i=i<<1){
				if (i>=subredes)
					return contador;
				contador++;
			}
			break;
		case 2:
			contador=16;
			
			for (i=1;i<256;i=i<<1){
				if (i>=subredes)
					return contador;
				contador++;
			}
			break;
		case 3:
			contador=24;
			
			for (i=1;i<256;i=i<<1){
				if (i>=subredes)
					return contador;
				contador++;
			}
			break;
	}
}
