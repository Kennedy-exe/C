#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>



//------------------------------------------ structs usadas no trabalho ------------------------------------------

typedef struct
{
	char cpf[15];
	char nome[50];
	char data_nascimento[13];
	char sexo;
	char salario[10];

	int cont_email;
	char email[5][40];

	int cont_tell;      
	char tell[5][15];

}clientes;


typedef struct
{
	char codigo[20];
	char descricao[40];
	char mls[10];
	char validade[15];
	float desconto;
	float valor;

}produtos;


typedef struct
{
	char cpf[15];
	char codigo[20];
	char data[13];
	char hora[6];
	float valor;

}vendas;


//------------------------------------------ Parte de clientes------------------------------------------

clientes * aloca(clientes * vet)
{
	vet = malloc(50 * sizeof(clientes));
	return vet;
}

clientes * realocamento(clientes *vet, int * limite)  // -------------------------------------- Função realocamento
{
	clientes * temp = realloc(vet, (*limite*2) * sizeof(clientes));
	*limite = *limite * 2;

	if(temp == NULL)
    	{
       		printf("Erro ao realocar memoria!\n");
        	return vet;
   	}
	else
	{
		vet = temp;
		printf("Novo Limite: %d", *limite);
		return vet;
	}
}


int buscador(clientes *vet, int *contador_clientes, char cpf[40])  // -------------------------------------- Função verificadora de chave
{
	int i,achou=-1;
	
	for(i=0;i<*contador_clientes;i++)
	{
		if (strcmp(cpf, vet[i].cpf) == 0)
		{
			achou = i;
		}
	}

	return achou;
}


void deletar_cliente(clientes *vet, int * contador_clientes) // -------------------------------------- Função deletar
{
	char cpf[15];                      // cpf temporario para não mudar nada na struct sem verificar
	int achou,i;
	printf("Digite um CPF para deletar ou 0 para cancelar: ");
	fgets(cpf,15,stdin);
	cpf[strcspn(cpf,"\n")] = '\0';
	
	if(strcmp(cpf,"0") == 0)
	{
		printf("Operacao cancelada!\n");
		return;
	}
	
	
	achou = buscador(vet,contador_clientes,cpf);
	
	if(achou >= 0)
	{
		for(i = achou; i < (*contador_clientes - 1); i++)
		{
			vet[i] = vet[i + 1];
		}
		(*contador_clientes)--;
	}
	else
	{
		printf("Cliente não localizado!! :/\n");
	}
	
}


clientes * criar_clientes(clientes * vet, int *contador_clientes, int * limite) // -------------------------------------- Função criadora de clientes
{
	char cpf[15];                      // cpf temporario para não mudar nada na struct sem verificar
	int achou;
	printf("Digite um CPF (Apenas numero): ");
	fgets(cpf,15,stdin);
	cpf[strcspn(cpf,"\n")] = '\0';
	
	if(*contador_clientes == *limite)
	{
		vet = realocamento(vet,limite);                       
	}	

	achou = buscador(vet,contador_clientes,cpf);
	if(achou >= 0)
	{
		printf("Valor ja cadastrado!!\n");
		return vet;
	}
	
	else{
		int j;
		vet[*contador_clientes].cont_email = 0;
		vet[*contador_clientes].cont_tell = 0;
		
		printf("\t Cliente de numero : %d\n",*contador_clientes);

		strcpy(vet[*contador_clientes].cpf,cpf);
		vet[*contador_clientes].cpf[strcspn(vet[*contador_clientes].cpf,"\n")] = '\0'; 
		
		printf("NOME: ");
		fgets(vet[*contador_clientes].nome,50,stdin);
		vet[*contador_clientes].nome[strcspn(vet[*contador_clientes].nome,"\n")] = '\0';
	
		printf("\nDATA DE NASCIMENTO ex(22/02/2002): ");
		fgets(vet[*contador_clientes].data_nascimento,13,stdin);
		vet[*contador_clientes].data_nascimento[strcspn(vet[*contador_clientes].data_nascimento,"\n")] = '\0';

		printf("SEXO (ex: M ou F): ");
		scanf("%c",&vet[*contador_clientes].sexo);
		getchar();

		printf("SALARIO: ");
		fgets(vet[*contador_clientes].salario,10,stdin);
		vet[*contador_clientes].salario[strcspn(vet[*contador_clientes].salario,"\n")] = '\0';

		
		printf("Ate 5 EMAILS, ou enter para cancelar:\n");
		for(j=0;j<5;j++)
		{
			
			printf("Email : ");
			fgets(vet[*contador_clientes].email[j],40,stdin);
			
			if(vet[*contador_clientes].email[j][0] == '\n')
			{
				break;
			}
			vet[*contador_clientes].email[j][strcspn(vet[*contador_clientes].email[j],"\n")] = '\0';
			vet[*contador_clientes].cont_email++;
		}

		printf("Ate 5 Telefones, ou enter para cancelar\n");
		for(j=0;j<5;j++)
		{
			
			printf("Telefone : ");
			fgets(vet[*contador_clientes].tell[j],15,stdin);
			
			if(vet[*contador_clientes].tell[j][0] == '\n')
			{
				break;
			}
			vet[*contador_clientes].tell[j][strcspn(vet[*contador_clientes].tell[j],"\n")] = '\0';
			vet[*contador_clientes].cont_tell++;

		}								
		(*contador_clientes)++;
		return vet;   
		
	}
}


void listar_todos(clientes *vet,int *contador_clientes) // -------------------------------------- Função listar todos
{
	printf("\t************Listar todos************\n");
	int i,j;
	for(i=0;i<*contador_clientes;i++)  
	{
		printf("\n\t valor %d\n",i);
		printf("CPF : %s\n",vet[i].cpf);
		printf("nome : %s\n",vet[i].nome);
		printf("Data de nascimento : %s\n",vet[i].data_nascimento);
		printf("Sexo %c\n",vet[i].sexo);
		printf("Salario : %s\n",vet[i].salario);


		for(j=0;j<(vet[i].cont_email);j++)
		{
			if(vet[i].email[j][0] != '\n')
			{
				printf("Email : %s\n",vet[i].email[j]);
			}
			else{break;}
		}
		
		for(j=0;j<(vet[i].cont_tell);j++)
		{
			if(vet[i].tell[j][0] != '\n')
			{
				printf("Telefone : %s\n",vet[i].tell[j]);
			}
			else{break;}
		}
		printf("--------------------------------------\n");
	}
}


void listar_especifico(clientes *vet, int *contador_clientes) // -------------------------------------- Função listar específico
{
	char cpf[15];                      // cpf temporario para não mudar nada na struct sem verificar

	printf("\t************Busca de cliente especifico************\n");
	int achou;
	printf("Digite um CPF: ");
	fgets(cpf,15,stdin);
	cpf[strcspn(cpf,"\n")] = '\0';

	achou = buscador(vet,contador_clientes,cpf);

	if(achou >= 0)
	{
		int j;		

		printf("\n\t Cliente numero: %d\n",achou);
		printf("CPF : %s\n",vet[achou].cpf);
		printf("nome : %s\n",vet[achou].nome);
		printf("Data de nascimento : %s\n",vet[achou].data_nascimento);
		printf("Sexo %c\n",vet[achou].sexo);
		printf("Salario : %s\n",vet[achou].salario);


		for(j=0;j<(vet[achou].cont_email);j++)
		{
			if(vet[achou].email[j][0] != '\n')
			{
				printf("Email : %s\n",vet[achou].email[j]);
			}
			else{break;}
		}
		
		for(j=0;j<(vet[achou].cont_tell);j++)
		{
			if(vet[achou].tell[j][0] != '\n')
			{
				printf("Telefone : %s\n",vet[achou].tell[j]);
			}
			else{break;}
		}

	}
	
	else
	{
		printf("Cliente não localizado!\n");
	}
	

	
}


void alterar(clientes *vet, int * contador_clientes) // -------------------------------------- Função modificar específico
{
	char cpf[15];                      // cpf temporario para não mudar nada na struct sem verificar

	printf("\t************Alterar Cliente************\n");
	int achou;
	printf("Digite um CPF: ");
	fgets(cpf,15,stdin);
	cpf[strcspn(cpf,"\n")] = '\0';

	achou = buscador(vet,contador_clientes,cpf);

	if(achou >= 0)
	{
		int j;
		vet[achou].cont_email = 0;
		vet[achou].cont_tell = 0;
		
		printf("\t Cliente de numero : %d",achou);
		
		printf("NOME: ");
		fgets(vet[achou].nome,50,stdin);
		vet[achou].nome[strcspn(vet[achou].nome,"\n")] = '\0';
	
		printf("DATA DE NASCIMENTO ex(22/02/2002): ");
		fgets(vet[achou].data_nascimento,13,stdin);
		vet[achou].data_nascimento[strcspn(vet[achou].data_nascimento,"\n")] = '\0';

		printf("SEXO: ");
		scanf("%c",&vet[achou].sexo);
		getchar();

		printf("\nSALARIO: ");
		fgets(vet[achou].salario,10,stdin);
		vet[achou].salario[strcspn(vet[achou].salario,"\n")] = '\0';

		
		printf("Ate 5 EMAILS, ou enter para cancelar\n");
		for(j=0;j<5;j++)
		{
			
			printf("Email : ");
			fgets(vet[achou].email[j],40,stdin);
			
			if(vet[achou].email[j][0] == '\n')
			{
				break;
			}
			vet[achou].email[j][strcspn(vet[achou].email[j],"\n")] = '\0';
			vet[achou].cont_email++;
		}

		printf("Ate 5 Telefones, ou enter para cancelar\n");
		for(j=0;j<5;j++)
		{
			
			printf("Telefone : ");
			fgets(vet[achou].tell[j],15,stdin);
			
			if(vet[achou].tell[j][0] == '\n')
			{
				break;
			}
			vet[achou].tell[j][strcspn(vet[achou].tell[j],"\n")] = '\0';
			vet[achou].cont_tell++;

		}
	}
}





clientes * Submenu_clientes(clientes *  vet_clientes,int * contador_clientes,int * limite) // -------------------------------------- Função submenu clentes
{
	int esc;

	//EM PREPARO

	/*
	listar todos        feito
	listar especifico	feito
	incluir             feito
	alterar			    feito
	excluir
	sair
	*/
	
	do
	{
		printf("**************Submenu Clientes****************\n\n");
		printf("\t1. Listar todos\n");
		printf("\t2. Listar especifico\n");
		printf("\t3. Incluir\n");
		printf("\t4. Alterar\n");
		printf("\t5. Excluir\n");
		printf("\t6. Sair\n");
		scanf("%d",&esc);
		getchar();
		
		switch (esc) 
		{
			case 1:
				//Listar todos
				listar_todos(vet_clientes,contador_clientes);
				break;
			
			case 2:
				//listar especifico
				listar_especifico(vet_clientes,contador_clientes);
				break;
			case 3:
				//incluir
				vet_clientes = criar_clientes(vet_clientes,contador_clientes,limite);
				//  realoc?
				break;
			case 4:
				//alterar
				alterar(vet_clientes,contador_clientes);
				break;
			case 5:
				//excluir
				deletar_cliente(vet_clientes,contador_clientes);	
				break;
			case 6:
				//fica aqui a parte de salvar aquivo

				printf("Encerrando\n");
				return vet_clientes;
				break;

			default: printf("Opção incorreta!\n");
			
		}
	}
	while(esc >= 1 && esc <= 6);
	return vet_clientes;
	
	
}


//------------------------------------------ fim das funções clientes------------------------------------------;



//------------------------------------------ inicio das funções produto------------------------------------------;


produtos * aloca_produtos(produtos * vet)         //--------------------------------------------------- Função de alocar clientes
{
	vet = malloc(50 * sizeof(produtos));
	return vet;
}

produtos * realocamento_produtos(produtos *vet,int * limite_produto)  // -------------------------------------- Função realocamento
{
	produtos * temp = realloc(vet, (*limite_produto*2) * sizeof(produtos));
	*limite_produto = *limite_produto * 2;

	if(temp == NULL)
    	{
       		printf("Erro ao realocar memoria!\n");
        	return vet;
   	}
	else
	{
		vet = temp;
		printf("Novo Limite: %d", *limite_produto);
		return vet;
	}
}

int buscador_produtos(produtos *vet, int *contador_produto,char chave_codigo[20])  // -------------------------------------- Função verificadora de chave
{
	int i,achou=-1;
	
	for(i=0;i<*contador_produto;i++)
	{
		if (strcmp(chave_codigo, vet[i].codigo) == 0)
		{
			achou = i;
		}
	}

	return achou;
}

void deletar_produto(produtos *vet, int * contador_produto) // -------------------------------------- Função deletar
{
	
	printf("Digite a chave de um produto, para deletar ou 0 para cancelar: ");
	int achou,i;
	char chave_codigo[20];

	fgets(chave_codigo,20,stdin);
	chave_codigo[strcspn(chave_codigo,"\n")] = '\0';

	achou = buscador_produtos(vet,contador_produto,chave_codigo);

	
	if(strcmp(chave_codigo,"0") == 0)
	{
		printf("Operacao cancelada!\n");
		return;
	}
	if(achou >= 0)
	{
		for(i = achou; i < (*contador_produto - 1); i++)
		{
			vet[i] = vet[i + 1];
		}
		(*contador_produto)--;
	}
	else
	{
		printf("Produto não localizado!! :/\n");
	}
	
}

void listar_Produto_especifico(produtos *vet, int *contador_produto) // -------------------------------------- Função listar específico
{
	printf("\t************Busca de Produto especifico************\n");
	
	int achou;
	char chave_codigo[20];

	printf("Digite um Codigo de produto: ");
	fgets(chave_codigo,20,stdin);
	chave_codigo[strcspn(chave_codigo,"\n")] = '\0';

	achou = buscador_produtos(vet,contador_produto,chave_codigo);

	if(achou >= 0)
	{
		printf("\n\t produto de numero: %d\n",achou);
		printf("Codigo : %s\n",vet[achou].codigo);
		printf("Descricao : %s\n",vet[achou].descricao);
		printf("Mililitros do produto : %s\n",vet[achou].mls);
		printf("Validade %s\n",vet[achou].validade);
		printf("desconto : %.2f%%\n",vet[achou].desconto);
		printf("Valor do produto: %.2f\n",vet[achou].valor);
		printf("--------------------------------------\n");

	}
	else
	{
		printf("Produto não localizado!\n");
	}
		
}

produtos * criar_produtos(produtos * vet,int *contador_produto,int * limite_produto) // -------------------------------------- Função criadora de prduto
{
	char chave_codigo[20];                      // 	TESTAR A ADIÇÃO DE MAIS DE UM VALOR DEPOIS
	int achou;

	printf("Digite um Codigo de produto: ");
	fgets(chave_codigo,20,stdin);
	chave_codigo[strcspn(chave_codigo,"\n")] = '\0';
	
	if(*contador_produto == *limite_produto)
	{
		vet = realocamento_produtos(vet,limite_produto);                       
	}	

	achou = buscador_produtos(vet,contador_produto,chave_codigo);

	if(achou >= 0)
	{
		printf("Valor ja cadastrado!!\n");
		return vet;
	}
	else{
		
		int j;
		
		printf("\t Produto de numero : %d\n",*contador_produto);

		strcpy(vet[*contador_produto].codigo,chave_codigo);
		
		printf("Descricao do produto: ");
		fgets(vet[*contador_produto].descricao,50,stdin);
		vet[*contador_produto].descricao[strcspn(vet[*contador_produto].descricao,"\n")] = '\0';

		printf("Mililitros do produto: ");
		fgets(vet[*contador_produto].mls,10,stdin);
		vet[*contador_produto].mls[strcspn(vet[*contador_produto].mls,"\n")] = '\0';
	
		printf("validade do produto ex(01/02/2003): ");
		fgets(vet[*contador_produto].validade,20,stdin);
		vet[*contador_produto].validade[strcspn(vet[*contador_produto].validade,"\n")] = '\0';

		printf("Desconto do produto porcento ex(25, 50...): ");
		scanf("%f",&vet[*contador_produto].desconto);
		

		printf("Valor do produto (o desconto sera adicionado automaticamente): ");
		scanf("%f",&vet[*contador_produto].valor);
		getchar();
		
		
		vet[*contador_produto].valor = (vet[*contador_produto].valor) - (vet[*contador_produto].valor * (vet[*contador_produto].desconto / 100));
		
		printf("\tValor final do produto: %.2f\n",vet[*contador_produto].valor);
								
		(*contador_produto)++;
		return vet;   
		
	}
}


void listar_todos_produtos(produtos *vet,int *contador_produto) // -------------------------------------- Função listar todos os produtos
{
	printf("\t************Listar todos************\n");
	int i,j;
	for(i=0;i<*contador_produto;i++)  
	{
		printf("\n\t produto de numero: %d\n",i);
		printf("Codigo : %s\n",vet[i].codigo);
		printf("Descricao : %s\n",vet[i].descricao);
		printf("Mililitros do produto : %s\n",vet[i].mls);
		printf("Validade %s\n",vet[i].validade);
		printf("desconto : %2.f%%\n",vet[i].desconto);
		printf("Valor do produto: %f\n",vet[i].valor);
		printf("--------------------------------------\n");
		
	}
}


void alterar_produto(produtos *vet, int * contador_produto) // -------------------------------------- Função modificar específico
{
	printf("\t************Busca de Produto especifico************\n");
	
	int achou;
	char chave_codigo[20];

	printf("Digite um Codigo de produto: ");
	fgets(chave_codigo,20,stdin);
	chave_codigo[strcspn(chave_codigo,"\n")] = '\0';

	achou = buscador_produtos(vet,contador_produto,chave_codigo);

	if(achou >= 0)
	{
		printf("\t Produto de numero : %d\n",achou);

		strcpy(vet[achou].codigo,chave_codigo);
		
		printf("Descricao do produto: ");
		fgets(vet[achou].descricao,50,stdin);
		vet[achou].descricao[strcspn(vet[achou].descricao,"\n")] = '\0';

		printf("Mililitros do produto: ");
		fgets(vet[achou].mls,10,stdin);
		vet[achou].mls[strcspn(vet[achou].mls,"\n")] = '\0';
	
		printf("validade do produto ex(01/02/2003): ");
		fgets(vet[achou].validade,20,stdin);
		vet[achou].validade[strcspn(vet[achou].validade,"\n")] = '\0';

		printf("Desconto do produto porcento ex(25, 50...): ");
		scanf("%f",&vet[achou].desconto);
		

		printf("Valor do produto (o desconto sera adicionado automaticamente): ");
		scanf("%f",&vet[achou].valor);
		getchar();	
		
		vet[achou].valor = (vet[achou].valor) - (vet[achou].valor * (vet[achou].desconto / 100));
		
		printf("\tValor final do produto: %.2f\n",vet[achou].valor);
								
		
	}
	else
	{
		printf("Produto invalido ou inexistente!\n");
	}
}




produtos * Submenu_produtos(produtos * vet_produtos,int * contador_produto, int *  limite_produto) // -------------------------------------- Função submenu produtos
{
	int esc;

	//EM PREPARO

	/*
	listar todos   	    feito            
	listar especifico   feito	    
	incluir             feito          
	alterar		    feito    
	excluir
	sair
	*/
	//Criação e alocação
	
	do
	{
		printf("**************Submenu Produtos****************\n\n");
		printf("\t1. Listar todos\n");
		printf("\t2. Listar especifico\n");
		printf("\t3. Incluir\n");
		printf("\t4. Alterar\n");
		printf("\t5. Excluir\n");
		printf("\t6. Sair\n");
		scanf("%d",&esc);
		getchar();
		
		switch (esc) 
		{
			case 1:
				//Listar todos
				listar_todos_produtos(vet_produtos,contador_produto);
				break;
			
			case 2:
				//listar especifico
				listar_Produto_especifico(vet_produtos,contador_produto);
				break;
			case 3:
				//incluir
				vet_produtos = criar_produtos(vet_produtos,contador_produto,limite_produto);
				break;
			case 4:
				//alterar
				alterar_produto(vet_produtos,contador_produto);
				break;
			case 5:
				//excluir
				deletar_produto(vet_produtos,contador_produto);	
				break;
			case 6:
				//fica aqui a parte de salvar aquivo

				printf("Encerrando\n");
				return vet_produtos;
				break;

			default: printf("Opção incorreta!\n");
			
		}
	}
	while(esc >= 1 && esc <= 6);
	return vet_produtos;
	
}

//------------------------------------------ fim das funções produto ------------------------------------------;

//------------------------------------------ inicio das funções vendas ------------------------------------------;

vendas * aloca_vendas(vendas * vet)
{
	vet = malloc(50 * sizeof(vendas));
	return vet;
}

vendas * realocamento_vendas(vendas *vet, int * limite)
{
    vendas * temp = realloc(vet, (*limite * 2) * sizeof(vendas));
    *limite = *limite * 2;

    if(temp == NULL)
    {
        printf("Erro ao realocar memoria!\n");
        return vet;
    }
    else
    {
        vet = temp;
        printf("Novo Limite: %d", *limite);
        return vet;
    }
}

int buscador_vendas(vendas *vet, int *contador, char cpf[15], char codigo[20])
{
    int i, achou = -1;
    for(i = 0; i < *contador; i++)
    {
        if(strcmp(cpf, vet[i].cpf) == 0 && strcmp(codigo, vet[i].codigo) == 0)
        {
            achou = i;
        }
    }
    return achou;
}

vendas * criar_venda(vendas *vet, int *contador, int *limite, clientes *vet_c, int *cont_c, produtos *vet_p, int *cont_p) // abreviações para caber na tela. c cliente p produto
{
    char cpf[15], codigo[20];

    printf("CPF do cliente: ");
    fgets(cpf, 15, stdin);
    cpf[strcspn(cpf, "\n")] = '\0';

    if(buscador(vet_c, cont_c, cpf) < 0)
    {
        printf("Cliente nao encontrado!\n");
        return vet;
    }

    printf("Codigo do produto: ");
    fgets(codigo, 20, stdin);
    codigo[strcspn(codigo, "\n")] = '\0';

    int idx_produto = buscador_produtos(vet_p, cont_p, codigo);
    if(idx_produto < 0)
    {
        printf("Produto nao encontrado!\n");
        return vet;
    }

    if(buscador_vendas(vet, contador, cpf, codigo) >= 0)
    {
        printf("Venda ja cadastrada para este cliente e produto!\n");
        return vet;
    }

    if(*contador == *limite)
    {
        vet = realocamento_vendas(vet, limite);
    }

    strcpy(vet[*contador].cpf, cpf);
    strcpy(vet[*contador].codigo, codigo);

    time_t agora = time(NULL);
	struct tm *t = localtime(&agora);
	strftime(vet[*contador].data, 13, "%d/%m/%Y", t);
	strftime(vet[*contador].hora, 6, "%H:%M", t);
	printf("Data: %s\n", vet[*contador].data);
	printf("Hora: %s\n", vet[*contador].hora);

    vet[*contador].valor = vet_p[idx_produto].valor;
    printf("Valor da venda: %.2f\n", vet[*contador].valor);

    (*contador)++;
    return vet;
}

void listar_todas_vendas(vendas *vet, int *contador)
{
    printf("\t************Listar todas as vendas************\n");
    int i;
    for(i = 0; i < *contador; i++)
    {
        printf("\nVenda %d\n", i);
        printf("CPF Cliente : %s\n", vet[i].cpf);
        printf("Codigo Produto : %s\n", vet[i].codigo);
        printf("Data : %s\n", vet[i].data);
        printf("Hora : %s\n", vet[i].hora);
        printf("Valor : %.2f\n", vet[i].valor);
        printf("--------------------------------------\n");
    }
}

void listar_venda_especifica(vendas *vet, int *contador)
{
    char cpf[15], codigo[20];
    int achou;

    printf("CPF do cliente: ");
    fgets(cpf, 15, stdin);
    cpf[strcspn(cpf, "\n")] = '\0';

    printf("Codigo do produto: ");
    fgets(codigo, 20, stdin);
    codigo[strcspn(codigo, "\n")] = '\0';

    achou = buscador_vendas(vet, contador, cpf, codigo);

    if(achou >= 0)
    {
        printf("CPF Cliente : %s\n", vet[achou].cpf);
        printf("Codigo Produto : %s\n", vet[achou].codigo);
        printf("Data : %s\n", vet[achou].data);
        printf("Hora : %s\n", vet[achou].hora);
        printf("Valor : %.2f\n", vet[achou].valor);
    }
    else
    {
        printf("Venda nao localizada!\n");
    }
}

void deletar_venda(vendas *vet, int *contador)
{
    char cpf[15], codigo[20];
    int achou, i;

    printf("CPF do cliente (ou 0 para cancelar): ");
    fgets(cpf, 15, stdin);
    cpf[strcspn(cpf, "\n")] = '\0';

    if(strcmp(cpf, "0") == 0) { printf("Cancelado!\n"); return; }

    printf("Codigo do produto: ");
    fgets(codigo, 20, stdin);
    codigo[strcspn(codigo, "\n")] = '\0';

    achou = buscador_vendas(vet, contador, cpf, codigo);

    if(achou >= 0)
    {
        for(i = achou; i < (*contador - 1); i++)
        {
            vet[i] = vet[i + 1];
        }
        (*contador)--;
        printf("Venda removida!\n");
    }
    else
    {
        printf("Venda nao localizada!\n");
    }
}

vendas * Submenu_vendas(vendas *vet_vendas, int *contador_venda, int *limite_venda, clientes *vet_c, int *cont_c, produtos *vet_p, int *cont_p) // Abreviei para caber na tela
{
    int esc;
    do
    {
        printf("**************Submenu Vendas****************\n\n");
        printf("\t1. Listar todas\n");
        printf("\t2. Listar especifica\n");
        printf("\t3. Incluir\n");
        printf("\t4. Excluir\n");
        printf("\t5. Sair\n");
        scanf("%d", &esc);
        getchar();

        switch(esc)
        {
            case 1:
                listar_todas_vendas(vet_vendas, contador_venda);
                break;
            case 2:
                listar_venda_especifica(vet_vendas, contador_venda);
                break;
            case 3:
                vet_vendas = criar_venda(vet_vendas, contador_venda, limite_venda, vet_c, cont_c, vet_p, cont_p);
                break;
            case 4:
                deletar_venda(vet_vendas, contador_venda);
                break;
            case 5:
                printf("Encerrando\n");
                return vet_vendas;
            default:
                printf("Opcao incorreta!\n");
        }
    }
    while(esc >= 1 && esc <= 5);
    return vet_vendas;
}

//------------------------------------------ fim das funções de vendas ------------------------------------------;

// ---------------------------------------------------------------- funções de arquivos --------------------------;

void salvar_clientes(clientes *vet, int *  contador)
{
    FILE *fp;

    fp = fopen("clientes.dat", "wb");

    if(fp == NULL)
    {
        printf("Erro ao abrir arquivo clientes!\n");
        return;
    }

    fwrite(contador, sizeof(int), 1, fp);

    fwrite(vet, sizeof(clientes), * contador, fp);

    fclose(fp);
}

clientes * carregar_clientes(clientes *vet, int *contador, int * limite)
{
    FILE *fp;

    fp = fopen("clientes.dat", "rb");

    if(fp == NULL)
    {
        printf("Arquivo clientes ainda nao existe!\n");
        return vet;
    }

    fread(contador, sizeof(int), 1, fp);
  	if(*contador > *limite)
    {
        *limite = *contador;

        vet = realloc(vet,(*limite) * sizeof(clientes));

        if(vet == NULL)
        {
            printf("Erro ao realocar memoria!\n");

            fclose(fp);

            return NULL;
        }
    }

    fread(vet, sizeof(clientes), * contador, fp);

    fclose(fp);

    return vet;
}

// -------------------------------------------------------------- produtos

void salvar_produtos(produtos *vet, int * contador)
{
    FILE *fp;

    fp = fopen("produtos.dat", "wb");

    if(fp == NULL)
    {
        printf("Erro ao abrir arquivo produtos!\n");
        return;
    }

    fwrite(contador, sizeof(int), 1, fp);

    fwrite(vet, sizeof(produtos), * contador, fp);

    fclose(fp);
}
produtos * carregar_produtos(produtos *vet, int *contador, int * limite)
{
    FILE *fp;

    fp = fopen("produtos.dat", "rb");

    if(fp == NULL)
    {
        printf("Arquivo produtos ainda nao existe!\n");
        return vet;
    }

    fread(contador, sizeof(int), 1, fp);
	if(*contador > *limite)
    {
        *limite = *contador;

        vet = realloc(vet,(*limite) * sizeof(produtos));

        if(vet == NULL)
        {
            printf("Erro ao realocar memoria!\n");

            fclose(fp);

            return NULL;
        }
    }

    fread(vet, sizeof(produtos), *contador, fp);

    fclose(fp);

    return vet;
}

void salvar_vendas(vendas *vet, int *contador)
{
    FILE *fp = fopen("vendas.dat", "wb");
    if(fp == NULL)
	{ 
		printf("Erro ao abrir arquivo vendas!\n"); 
		return; 
	}
    fwrite(contador, sizeof(int), 1, fp);
    fwrite(vet, sizeof(vendas), *contador, fp);
    fclose(fp);
}

vendas * carregar_vendas(vendas *vet, int *contador, int *limite)
{
    FILE *fp = fopen("vendas.dat", "rb");
    if(fp == NULL) { printf("Arquivo vendas ainda nao existe!\n"); return vet; }

    fread(contador, sizeof(int), 1, fp);
    if(*contador > *limite)
    {
        *limite = *contador;
        vet = realloc(vet, (*limite) * sizeof(vendas));
        if(vet == NULL)
		{ 
			printf("Erro ao realocar!\n"); 
			fclose(fp); 
			return NULL; 
		}
    }
    fread(vet, sizeof(vendas), *contador, fp);
    fclose(fp);
    return vet;
}
//------------------------------------------ fim das funções arquivo------------------------------------------;

// ------------------------------------------------------------------Inicio do relatório----------------------;

int comparar_datas(char *data1, char *data2)
{
    // Formato esperado: DD/MM/AAAA

    // Retorna negativo se data1 < data2, 0 se iguais, positivo se data1 > data2
    int d1, m1, a1, d2, m2, a2;           // decomposição da data para inteiros assim podemos comparar!!
    sscanf(data1, "%d/%d/%d", &d1, &m1, &a1);
    sscanf(data2, "%d/%d/%d", &d2, &m2, &a2);

    if (a1 != a2) return a1 - a2;
    if (m1 != m2) return m1 - m2;
    return d1 - d2;
}

void data_hoje(char *buf, int tamanho)   // pega a data de hoje
{
    time_t agora = time(NULL);
    struct tm *t = localtime(&agora);
    strftime(buf, tamanho, "%d/%m/%Y", t);
}

// ------------------------------------------ relatorio clientes com mais de X telefones ------------------------------------------

void relatorio_clientes_telefones(clientes *vet, int *contador)
{
    int x;
    printf("Clientes com mais de quantos telefones? ");
    scanf("%d", &x);
    getchar();

    FILE *fp = fopen("rel_telefones.txt", "w");
    if (fp == NULL)
    {
        printf("Erro ao criar arquivo de relatorio!\n");
        return;
    }

    long inicio = ftell(fp);  // posição inicial (0)
    int encontrados = 0;
    int i, j;

    fprintf(fp, "========================================\n");
    fprintf(fp, "  RELATORIO: Clientes com mais de %d telefone(s)\n", x);
    fprintf(fp, "========================================\n\n");

    long pos_cabecalho = ftell(fp);  // posição após cabeçalho

    for (i = 0; i < *contador; i++)
    {
        if (vet[i].cont_tell > x)
        {
            long pos_registro = ftell(fp);  // posição antes de escrever esse registro
            fprintf(fp, "CPF            : %s\n", vet[i].cpf);
            fprintf(fp, "Nome           : %s\n", vet[i].nome);
            fprintf(fp, "Nascimento     : %s\n", vet[i].data_nascimento);
            fprintf(fp, "Sexo           : %c\n", vet[i].sexo);
            fprintf(fp, "Salario        : %s\n", vet[i].salario);
            fprintf(fp, "Qtd. Telefones : %d\n", vet[i].cont_tell);

            for (j = 0; j < vet[i].cont_tell; j++)
                fprintf(fp, "  Telefone %d   : %s\n", j + 1, vet[i].tell[j]);

            for (j = 0; j < vet[i].cont_email; j++)
                fprintf(fp, "  Email %d      : %s\n", j + 1, vet[i].email[j]);

            fprintf(fp, "----------------------------------------\n");
            printf("  [Registro salvo no byte %ld]\n", pos_registro);
            encontrados++;
        }
    }

    // Volta ao início para anotar total encontrado no rodapé
    long pos_fim = ftell(fp);
    fprintf(fp, "\nTotal de clientes encontrados: %d\n", encontrados);

    // usa fseek para voltar e confirmar posição do cabeçalho (demonstração de fseek)
    fseek(fp, inicio, SEEK_SET);
    long verificacao = ftell(fp);
    fseek(fp, pos_fim, SEEK_SET); // volta ao fim para não corromper o arquivo
    fprintf(fp, "(Arquivo gerado do byte %ld ao byte %ld)\n", verificacao, pos_fim);

    fclose(fp);

    if (encontrados == 0)
        printf("Nenhum cliente com mais de %d telefone(s) encontrado.\n", x);
    else
        printf("%d cliente(s) encontrado(s). Relatorio salvo em 'rel_telefones.txt'.\n", encontrados);
}

// ------------------------------------------ Relatório 2: Produtos com validade expirada ------------------------------------------

void relatorio_produtos_expirados(produtos *vet, int *contador)
{
    char hoje[13];
    data_hoje(hoje, sizeof(hoje));

    FILE *fp = fopen("rel_expirados.txt", "w");
    if (fp == NULL)
    {
        printf("Erro ao criar arquivo de relatorio!\n");
        return;
    }

    int encontrados = 0;
    int i;

    fprintf(fp, "========================================\n");
    fprintf(fp, "  RELATORIO: Produtos com validade expirada\n");
    fprintf(fp, "  Data de referencia: %s\n", hoje);
    fprintf(fp, "========================================\n\n");

    for (i = 0; i < *contador; i++)
    {
        if (comparar_datas(vet[i].validade, hoje) < 0)
        {
            long pos_registro = ftell(fp);
            fprintf(fp, "Codigo    : %s\n", vet[i].codigo);
            fprintf(fp, "Descricao : %s\n", vet[i].descricao);
            fprintf(fp, "Mls       : %s\n", vet[i].mls);
            fprintf(fp, "Validade  : %s  <<< EXPIRADO\n", vet[i].validade);
            fprintf(fp, "Desconto  : %.2f%%\n", vet[i].desconto);
            fprintf(fp, "Valor     : R$ %.2f\n", vet[i].valor);
            fprintf(fp, "----------------------------------------\n");
            printf("  [Produto expirado salvo no byte %ld]\n", pos_registro);
            encontrados++;
        }
    }

    long pos_fim = ftell(fp);
    fprintf(fp, "\nTotal de produtos expirados: %d\n", encontrados);
    fprintf(fp, "Tamanho total do relatorio: %ld bytes\n", pos_fim);

    fclose(fp);

    if (encontrados == 0)
        printf("Nenhum produto expirado encontrado.\n");
    else
        printf("%d produto(s) expirado(s). Relatorio salvo em 'rel_expirados.txt'.\n", encontrados);
}

// ------------------------------------------ Relatório 3: Vendas entre datas X e Y ------------------------------------------

void relatorio_vendas_periodo(vendas *vet_v, int *cont_v, clientes *vet_c, int *cont_c, produtos *vet_p, int *cont_p) // vet vendas, vet clientes, vet produtos
{
    char data_inicio[13], data_fim[13];

    printf("Data inicial (DD/MM/AAAA): ");
    fgets(data_inicio, 13, stdin);
    data_inicio[strcspn(data_inicio, "\n")] = '\0';

    printf("Data final   (DD/MM/AAAA): ");
    fgets(data_fim, 13, stdin);
    data_fim[strcspn(data_fim, "\n")] = '\0';

    if (comparar_datas(data_inicio, data_fim) > 0)
    {
        printf("Data inicial nao pode ser maior que a data final!\n");
        return;
    }

    FILE *fp = fopen("rel_vendas_periodo.txt", "w");
    if (fp == NULL)
    {
        printf("Erro ao criar arquivo de relatorio!\n");
        return;
    }

    int encontrados = 0;
    int i, idx_c, idx_p;

    fprintf(fp, "========================================\n");
    fprintf(fp, "  RELATORIO: Vendas no periodo\n");
    fprintf(fp, "  De: %s  Ate: %s\n", data_inicio, data_fim);
    fprintf(fp, "========================================\n\n");

    long pos_dados = ftell(fp);  // marca onde os dados começam

    for (i = 0; i < *cont_v; i++)
    {
        if (comparar_datas(vet_v[i].data, data_inicio) >= 0 &&
            comparar_datas(vet_v[i].data, data_fim)    <= 0)
        {
            long pos_registro = ftell(fp);

            // Busca dados do cliente
            idx_c = buscador(vet_c, cont_c, vet_v[i].cpf);
            // Busca dados do produto
            idx_p = buscador_produtos(vet_p, cont_p, vet_v[i].codigo);

            fprintf(fp, "--- Venda %d (byte %ld) ---\n", encontrados + 1, pos_registro);

            // Dados da venda
            fprintf(fp, "Data         : %s\n", vet_v[i].data);
            fprintf(fp, "Hora         : %s\n", vet_v[i].hora);
            fprintf(fp, "Valor        : R$ %.2f\n", vet_v[i].valor);

            // Dados do cliente
            fprintf(fp, "CPF Cliente  : %s\n", vet_v[i].cpf);
            if (idx_c >= 0)
                fprintf(fp, "Nome Cliente : %s\n", vet_c[idx_c].nome);
            else
                fprintf(fp, "Nome Cliente : (nao encontrado)\n");

            // Dados do produto
            fprintf(fp, "Cod. Produto : %s\n", vet_v[i].codigo);
            if (idx_p >= 0)
            {
                fprintf(fp, "Descricao    : %s\n", vet_p[idx_p].descricao);
                fprintf(fp, "Mls          : %s\n", vet_p[idx_p].mls);
                fprintf(fp, "Validade     : %s\n", vet_p[idx_p].validade);
            }
            else
            {
                fprintf(fp, "Descricao    : (produto nao encontrado)\n");
            }

            fprintf(fp, "----------------------------------------\n");
            encontrados++;
        }
    }

    long pos_rodape = ftell(fp);

    // Usa fseek para voltar ao início e ler o tamanho do bloco de dados
    fseek(fp, pos_dados, SEEK_SET);
    long tamanho_bloco = pos_rodape - pos_dados;

    // Volta ao fim para escrever o rodapé
    fseek(fp, 0, SEEK_END);
    fprintf(fp, "\nTotal de vendas no periodo: %d\n", encontrados);
    fprintf(fp, "Bytes de dados gerados    : %ld\n", tamanho_bloco);

    fclose(fp);

    if (encontrados == 0)
        printf("Nenhuma venda encontrada no periodo informado.\n");
    else
        printf("%d venda(s) encontrada(s). Relatorio salvo em 'rel_vendas_periodo.txt'.\n", encontrados);
}

// ------------------------------------------ Submenu de Relatórios ------------------------------------------

void Submenu_relatorios(clientes *vet_c, int *cont_c, produtos *vet_p, int *cont_p, vendas *vet_v, int *cont_v)
{
    int esc;
    do
    {
        printf("**************Submenu Relatorios****************\n\n");
        printf("\t1. Clientes com mais de X telefones\n");
        printf("\t2. Produtos com validade expirada\n");
        printf("\t3. Vendas entre duas datas\n");
        printf("\t4. Sair\n");
        scanf("%d", &esc);
        getchar();

        switch (esc)
        {
            case 1:
                relatorio_clientes_telefones(vet_c, cont_c);
                break;
            case 2:
                relatorio_produtos_expirados(vet_p, cont_p);
                break;
            case 3:
                relatorio_vendas_periodo(vet_v, cont_v, vet_c, cont_c, vet_p, cont_p);
                break;
            case 4:
                printf("Encerrando relatorios\n");
                break;
            default:
                printf("Opcao incorreta!\n");
        }
    }
    while (esc >= 1 && esc <= 3);
}
//------------------------------------------ Menu principal --------------------------------------------------;

void menu()
{
	int escolha;

	int * contador_clientes = malloc(sizeof(int)), * limite = malloc(sizeof(int)); // variaveis de clientes
	*contador_clientes = 0;                
	*limite = 50;


	int * contador_produto = malloc(sizeof(int)), * limite_produto = malloc(sizeof(int)); // variaveis de produtos
	*contador_produto = 0;                
	*limite_produto = 50;


	int * contador_venda = malloc(sizeof(int)), * limite_venda = malloc(sizeof(int));
    *contador_venda = 0;
    *limite_venda = 50;

	clientes * vet_clientes = aloca(vet_clientes);
	produtos * vet_produtos = aloca_produtos(vet_produtos);
	vendas  * vet_vendas   = aloca_vendas(vet_vendas);

	vet_clientes = carregar_clientes(vet_clientes,contador_clientes,limite);
	vet_produtos = carregar_produtos(vet_produtos,contador_produto,limite_produto);
	vet_vendas   = carregar_vendas(vet_vendas, contador_venda, limite_venda);

	do
	{
	
		printf("**************Menu Geral****************\n\n");
		printf("\t1. Submenu Clientes\n");
		printf("\t2. Submenu Produtos\n");
		printf("\t3. Submenu Venda\n");
		printf("\t4. Submenu Relatorios\n");
		printf("\t5. Sair.\n");
		scanf("%d",&escolha);
		getchar();

		switch (escolha)
		{
			case 1:
				//Submenu Clientes
				vet_clientes = Submenu_clientes(vet_clientes,contador_clientes,limite); // acontece a captura de cada vetor
				break;
			case 2:
				//Submenu Produtos
				vet_produtos = Submenu_produtos(vet_produtos,contador_produto,limite_produto);
				break;
			case 3:
				//Submenu Venda
				vet_vendas = Submenu_vendas(vet_vendas, contador_venda, limite_venda, vet_clientes, contador_clientes, vet_produtos, contador_produto); // recebe todas as informações necessarias
				break;
			case 4:
				//Submenu Relatorios
				printf("\nSubmenu Relatorios\n");
    			Submenu_relatorios(vet_clientes, contador_clientes, vet_produtos, contador_produto, vet_vendas, contador_venda);
    			break;
				break;
			case 5:
				printf("Encerrando\n");
				salvar_clientes(vet_clientes,contador_clientes);
                salvar_produtos(vet_produtos,contador_produto);
				salvar_vendas(vet_vendas, contador_venda);

				// Talvez eu tenha usado muitas variaveis dinamicas :/
                free(vet_clientes);
                free(vet_produtos);
                free(vet_vendas);
                free(contador_clientes);
                free(limite);
                free(contador_produto);
                free(limite_produto);
                free(contador_venda);
                free(limite_venda);
				break;
			default: printf("Opção incorreta!\n");	
		}
	
	}
	while(escolha >= 1 && escolha <= 4);
}
	
int main()
{
	menu();
}
