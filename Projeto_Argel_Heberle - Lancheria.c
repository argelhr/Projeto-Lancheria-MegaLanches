#include <stdio.h>
#include <conio2.h>
#include <string.h>

char menu;
float p_bebidas[4]={2,5,7,8},p_refeicao[3]={15,12,18},OS[999][4];
int  contador=0;//////////variaveis globais

void mostraalmoco(float x);
void inicio (void);
void mostrabebida(float x);
void mostraOS();
void cifrao();
void pagamento();
void topo(void);
int menuprincipal();
void menualmoco(){////////////////////MOSTRA MENU DE ALMOÇO, APENAS IMPRIME NA TELA
		printf("\n(1)Almoco do dia R$%.2f",p_refeicao[0]);
		printf("\n(2)1/2 Marmita R$%.2f",p_refeicao[1]);
		printf("\n(3)Marmita completa R$%.2f",p_refeicao[2]);	
}
void menubebidas(){////////////////////MOSTRA MENU DE BEBIDAS, APENAS IMPRIME NA TELA
		printf("\n(1)Agua mineral 500ml R$%.2f",p_bebidas[0]);
		printf("\n(2)Refri 350ml R$%.2f",p_bebidas[1]);
		printf("\n(3)Refri 1L R$%.2f",p_bebidas[2]);
		printf("\n(4)Suco Natural(copo)R$%.2f",p_bebidas[3]);
}
void registrando(int x){/////////////animação de registro
	clrscr();
	gotoxy(5,24);
	printf("Anotando pedido");
	sleep(1); printf("...."); sleep(1);
	textcolor(LIGHTGREEN);
	gotoxy(5,24);
	printf("Pedido %d anotado!        ",x+1);
	textcolor(WHITE);
	sleep(1);
}		
main(){
	int x,aux,fim;
	float lojas[501][3],receita=0;
	
	for(x=0;x<501;x++)	lojas[x][0]=0; //valores do almoco
	for(x=0;x<501;x++)	lojas[x][1]=0; //valores de bebidas
	for(x=0;x<501;x++)	lojas[x][2]=0; //soma
	for(x=0;x<999;x++)	OS[x][0]=0;    //ordem de serviço

	inicio();
	sleep(1);
	
	do{
		topo();
		printf("Ola, pretende atualizar algum valor de encomenda?(S)Sim (N)Nao");
		menu = getch();
		menu = toupper(menu);
	}
	while(menu!='S'&&menu!='N');
	while(menu=='S'){
		do{
			topo();
			printf("Qual o menu a ser atualizado?\n(1)Refeicao\n(2)Bebidas\nCancelar(Backspace)");
			menu = getch();
			if(menu==8) break;
			
			if(menu=='2'){
				do{ 
					topo();
					printf("Qual das bebidas precisa ser atualizada?");
					menubebidas();
					printf("\nVoltar ao menu anterior(Backspace)");
					printf("\nItem selecionado:");
					do
						menu = getche();
					while(menu!='1'&&menu!='2'&&menu!='3'&&menu!='4'&&menu!=8);
					if(menu!=8){
						menu = menu - 49;
						printf("\nInforme o novo valor: R$");
						scanf("%f",&p_bebidas[menu]);
					}
					topo();
				}
				while(menu!=8);
			}
			if(menu=='1'){
				do{	
					topo();
					printf("Qual das refeicoes precisa ser atualizada?");
					menualmoco();
					printf("\nVoltar ao menu anterior(Backspace)");
					printf("\nItem selecionado:");
					do
						menu = getche();
					while(menu!='1'&&menu!='2'&&menu!='3'&&menu!='4'&&menu!=8);
					if(menu!=8){
						menu = menu - 49;
						printf("\nInforme o novo valor: R$");
						scanf("%f",&p_refeicao[menu]);
					}
				}
				while(menu!=8);
			}
			menu='g';
		}
		while(menu!=8);
	}	
	do{
		topo();
		menu = menuprincipal();
		if(menu==1){
			topo();
			do{
				printf("Qual o numero da loja para a entrega do pedido?");
				scanf("%d",&x);
			}
			while(x<1||x>500);
			printf("\nQual refeicao?\n");
			menualmoco();
			printf("\n(0)Nenhuma das alternativas\nItem selecionado:");
			
			do menu = getche();
			while(menu!='1'&&menu!='2'&&menu!='3'&&menu!='0');
			menu = menu - 49;
			if(menu!=-1)
				 lojas[x][0] = p_refeicao[menu];
			else
				lojas[x][0]=0;
						
			printf("\n\nAlguma bebida?\n");
			menubebidas();
			printf("\n(0)Nenhuma das alternativas\nItem selecionado:");
			do menu = getche();
			while(menu!='1'&&menu!='2'&&menu!='3'&&menu!='4'&&menu!='0');
			menu = menu - 49;
			
			if(menu!=-1)
				lojas[x][1] = p_bebidas[menu];
			else
				lojas[x][1] = 0;
						
			lojas[x][2] = lojas[x][0]+lojas[x][1];
			
			if(lojas[x][2]!=0){	
				printf("\n\nValor do pedido:R$%.2f",lojas[x][2]);
				printf("\nEsta correto?\n(S)Sim(N)Nao");
				do {
					menu = getch();
					menu = toupper(menu);
				}
				while(menu!='S' && menu!='N');
			
				if(menu=='S'){
					OS[contador][0] = x;          //guarda a loja x
					OS[contador][1] = lojas[x][0];//guarda o valor de almoço da loja x
					OS[contador][2] = lojas[x][1];//guarda o valor de bebidas
					OS[contador][3] = lojas[x][2];//Total de cada loja
					registrando(contador);
					contador++;
					
				}
			}
		}
		if(menu==2){
			topo();
			for(x=0;x<contador;x++){
				if(OS[x][3]!=0){
					printf("\n----- OS:%d -- Loja: %.0f -------\n",x+1,OS[x][0]);
					mostraalmoco(OS[x][1]);
					mostrabebida(OS[x][2]);
					printf("Total do pedido: R$%.2f",OS[x][3]);
					printf("\n_____________________________________________");
				}
			}
			getch();
		}
		if(menu==3&&contador>0){
			do{
			topo();
			printf("Qual OS esta sendo entregue para registrar o pagamento?\nInforme zero para cancelar e voltar ao menu anterior\n");
			for(x=0;x<999;x++){
				if(OS[x][3]>0)
					printf("OS %d Loja: %.0f- Valor: R$%.2f\n",x+1,OS[x][0],OS[x][3]);
			}
			gotoxy(56,5);
			scanf("%d",&aux);
			aux=aux-1;
			if(aux==-1)
				break;
			
			}
			while(OS[aux][3]==0);
			
			receita = receita + OS[aux][3];
			OS[aux][3] = 0;
			pagamento();
		}	
	
		fim=0;
		for(x=0;x<999;x++)
			if(OS[x][3]!=0)fim++;
	}
	while(menu!=9||fim!=0);
	topo();
	printf("Valor total hj: R$%.2f\n",receita);
	printf("Quantidade de OS:%d",contador);
}
void pagamento(void){
	int x, time = 1;
	for(x=0;x<2;x++){
		textcolor(BROWN);
		textbackground(DARKGRAY);
		clrscr();
		cifrao();
		sleep(time);
		textcolor(WHITE);
		textbackground(GREEN);
		clrscr();
		cifrao();
		sleep(time);
		if(x==1){
			gotoxy(45,25);
			printf("Pagamento recebido!");
		}
	}
	sleep(2);
	textcolor(WHITE);
	textbackground(BLACK);
	clrscr();
}

void mostraalmoco(float x){
		if(p_refeicao[0]== x)	printf("Refeicao: Almoco do dia\nR$%.2f",p_refeicao[0]);
		if(p_refeicao[1]== x)	printf("Refeicao: 1/2 Marmita\nR$%.2f",p_refeicao[1]);
		if(p_refeicao[2]== x)	printf("Refeicao: Marmita completa\nR$%.2f",p_refeicao[2]);
		printf("\n");
}
void mostrabebida(float x){
		if(p_bebidas[0]== x)	printf("Agua mineral 500ml \nR$%.2f",p_bebidas[0]);
		if(p_bebidas[1]== x)	printf("Refri 350ml \nR$%.2f",p_bebidas[1]);
		if(p_bebidas[2]== x)	printf("Refri 1L \nR$%.2f",p_bebidas[2]);
		if(p_bebidas[3]== x)	printf("Suco Natural(copo)\nR$%.2f",p_bebidas[3]);
		printf("\n");
}
void inicio (void){
	int m,x,b,y,aux,limite=1;
	do{
		gotoxy(26,10); textcolor(RED);
		printf("Para iniciar, aperte ENTER");
		m = getch();}
		while(m!= 13);
		sleep(1);
		clrscr();
		gotoxy(5,24);
		printf("Aguarde o carregamento do aplicativo");
		for(x=0;x<=2;x++){
			gotoxy(5,25);
			printf("Loading");
			for(y=0;y<=2;y++){
				sleep(0.4);
				printf(".");
				sleep(0.1);
				printf(".");
			}
			sleep(1);
			gotoxy(1,26);		
			for(aux=1;aux<=limite;aux++){	
				for(b=0;b<39;b++)	printf("%c",219);					
			}
			limite++;
			gotoxy(5,25);
			printf("                                                                        ");
		}
		gotoxy(5,24);
		printf("Aplicativo pronto!!                                 \n");
		gotoxy(5,25);
		printf("                          ");
		textcolor(GREEN);
		gotoxy(1,26);
		for(b=0;b<120;b++)	printf("%c",219);
}
void cifrao(){
	int x=4,y=15;
	gotoxy(y,x); printf("                   \n");x++;
	gotoxy(y,x); printf("      $$  $$       \n");x++;
	gotoxy(y,x); printf("      $$  $$       \n");x++;
	gotoxy(y,x); printf("    $$$$$$$$$$     \n");x++;
	gotoxy(y,x); printf("   $$$$$$$$$$$$    \n");x++;
	gotoxy(y,x); printf("  $$  $$  $$  $$   \n");x++;
	gotoxy(y,x); printf("  $$  $$  $$  $$   \n");x++;
	gotoxy(y,x); printf("  $$  $$  $$       \n");x++;
	gotoxy(y,x); printf("   $$$$$$$$$       \n");x++;
	gotoxy(y,x); printf("     $$$$$$$$$     \n");x++;
	gotoxy(y,x); printf("      $$  $$  $$   \n");x++;
	gotoxy(y,x); printf("  $$  $$  $$  $$$  \n");x++;
	gotoxy(y,x); printf("  $$  $$  $$   $$  \n");x++;
	gotoxy(y,x); printf("  $$  $$  $$   $$  \n");x++;
	gotoxy(y,x); printf("   $$$$$$$$$$$$$   \n");x++;
	gotoxy(y,x); printf("     $$$$$$$$      \n");x++;
	gotoxy(y,x); printf("      $$  $$       \n");x++;
	gotoxy(y,x); printf("      $$  $$       \n");x++;
	x = 4;y=45;
	gotoxy(y,x); printf("                   \n");x++;
	gotoxy(y,x); printf("      $$  $$       \n");x++;
	gotoxy(y,x); printf("      $$  $$       \n");x++;
	gotoxy(y,x); printf("    $$$$$$$$$$     \n");x++;
	gotoxy(y,x); printf("   $$$$$$$$$$$$    \n");x++;
	gotoxy(y,x); printf("  $$  $$  $$  $$   \n");x++;
	gotoxy(y,x); printf("  $$  $$  $$  $$   \n");x++;
	gotoxy(y,x); printf("  $$  $$  $$       \n");x++;
	gotoxy(y,x); printf("   $$$$$$$$$       \n");x++;
	gotoxy(y,x); printf("     $$$$$$$$$     \n");x++;
	gotoxy(y,x); printf("      $$  $$  $$   \n");x++;
	gotoxy(y,x); printf("  $$  $$  $$  $$$  \n");x++;
	gotoxy(y,x); printf("  $$  $$  $$   $$  \n");x++;
	gotoxy(y,x); printf("  $$  $$  $$   $$  \n");x++;
	gotoxy(y,x); printf("   $$$$$$$$$$$$$   \n");x++;
	gotoxy(y,x); printf("     $$$$$$$$      \n");x++;
	gotoxy(y,x); printf("      $$  $$       \n");x++;
	gotoxy(y,x); printf("      $$  $$       \n");x++;
	x = 4;y=75;
	gotoxy(y,x); printf("                   \n");x++;
	gotoxy(y,x); printf("      $$  $$       \n");x++;
	gotoxy(y,x); printf("      $$  $$       \n");x++;
	gotoxy(y,x); printf("    $$$$$$$$$$     \n");x++;
	gotoxy(y,x); printf("   $$$$$$$$$$$$    \n");x++;
	gotoxy(y,x); printf("  $$  $$  $$  $$   \n");x++;
	gotoxy(y,x); printf("  $$  $$  $$  $$   \n");x++;
	gotoxy(y,x); printf("  $$  $$  $$       \n");x++;
	gotoxy(y,x); printf("   $$$$$$$$$       \n");x++;
	gotoxy(y,x); printf("     $$$$$$$$$     \n");x++;
	gotoxy(y,x); printf("      $$  $$  $$   \n");x++;
	gotoxy(y,x); printf("  $$  $$  $$  $$$  \n");x++;
	gotoxy(y,x); printf("  $$  $$  $$   $$  \n");x++;
	gotoxy(y,x); printf("  $$  $$  $$   $$  \n");x++;
	gotoxy(y,x); printf("   $$$$$$$$$$$$$   \n");x++;
	gotoxy(y,x); printf("     $$$$$$$$      \n");x++;
	gotoxy(y,x); printf("      $$  $$       \n");x++;
	gotoxy(y,x); printf("      $$  $$       \n");x++;
}
void topo(void){
	int x;
	char y;
	clrscr();
	textcolor(WHITE);
	y = 201; 					printf("%c",y);
	y = 205; for(x=1;x<119;x++) printf("%c",y);
	y = 187;					printf("%c",y);
	y = 186; 					printf("%c",y);
	gotoxy(47,2);				printf("Lancheria MEGA LANCHES\n");
	gotoxy(120,2);				printf("%c",y);
	y = 200;                    printf("%c",y);
	y = 205; for(x=1;x<119;x++) printf("%c",y);
	y = 188;                    printf("%c\n",y);
}
int menuprincipal(){
	char c;
	printf("Qual a opcao desejada?\n(1)Registrar pedido\n");
	printf("(2)Verificar ordem dos pedidos\n");
	printf("(3)Registrar entrega de almoco\n");
	printf("(9)Finalizar o dia\n");
	do
	menu = getch();
	while(menu!='1'&&menu!='2'&&menu!='3'&&menu!='9');
	return menu-48;
}
