#include <stdio.h>
#include <stdlib.h>
#include <math.h>  // colocada para utilizar a fun��o de potencializa��o "pow (int n, int n)"
#include <locale.h> // necess�rio para aceitar acentos no c�digo

/*
	IFSC - GEST�O EM TI - L�GICA DE PROGRAMA��O
	TRABALHO EM C - CALCULAR ENDERE�OS DA REDE

	ALUNO:	GUSTAVO PEREIRA BORGES	
*/

	
int main(int argc, char *argv[]) {
	
	// mtheuew
	// ******************************************************************
	// *************** DECLARA��O DE VAR�IVEIS DO PROGRAMA **************
	// ****************************************************************** 
	

	int ip[4], ipbin[4][8];			// VETOR DO IP INSERIDO PELO USU�RIO
	int mask[4], maskbin[4][8];			// VETOR DA M�SCARA DE SUBREDE
	int net[4], netbin[4][8];			// VETOR DO ENDERE�O DE REDE	
	int bcast[4], bcastbin[4][8];   // VETOR DO ENDERE�O DE BROADCAST
	int wildcard[4];
//	int i_bcast = 0; 	// variavel para controle da opera��o que acha o endere�o de broadcast
	
	int bitsrede, bitshosts, bits;  // vari�veis para armazenar a quantidade de bits para a rede, quantidade de bits para hosts
	int qtdeips, qtdehosts;
	
	int i, u, n;	 //VARIAVEIS PARA CONTROLE DE OPERA��ES WHILE E FOR DENTRO ALGORITIMO;
	int resto; 		// vari�vel para controle de opera��es de convers�es de base num�rica.
	char p;	// VARI�VEL PARA PODER TRABALHAR COM PONTOS ENTRES OS NUMEROS DOS ENDERE�OS
	char loop;		
		
	setlocale(LC_ALL, "Portuguese");  // modifica configura��es de linguagem para Portugu�s, permitindo acentos e outras modifica��es.



	// ******************************************************************
	// ***************** ENTRADA DE DADOS PELO USU�RIO ******************
	// ****************************************************************** 
	
	inputdados:  // cria um label para o qual eu posso retornar no meio ou no final do c�digo usando o comando "goto", criando um loop


	// PEDE O ENDERE�O IP
	printf("\nDigite o endereco IP: ");
	// A SOLU��O AQUI USADA � DIVIDIR O IP EM 4 OCTETOS PARA FACILITAR AS OPERA��ES &AND E OUTRAS
	scanf("%d %c %d %c %d %c %d", &ip[0], &p, &ip[1], &p, &ip[2], &p, &ip[3]);
	// *******************************************************
	
	// PEDE A M�SCARA PARA O USU�RIO, DIVIDINDO-A EM 8 OCTETOS
	digitarmascara:
	printf("\nDigite a m�scara de sub-rede: ");
	scanf("%d %c %d %c %d %c %d", &mask[0], &p, &mask[1], &p, &mask[2], &p, &mask[3]);
	// *******************************************************
		
	// verifica se os valores digitados para a subm�scara respeitam os padr�es
	for (i=3; i>=0; --i) {
		if (mask[i]==0  || mask[i]==128 || mask[i]==192 || mask[i]==224 || mask[i]==240 || mask[i]==248 || mask[i]==252 || mask[i]==254 || mask[i]==255) {
			i++;
			i--;
		}  // endif
		else {
			printf("\nVoc� digitou um valor invalido para m�scara de rede.\nOs valores permitidos s�o: 0 | 128 | 192 | 224 | 240 | 248 | 252 | 254 | 255\n");
			i = 3;  // reseta a vari�vel de controle
			goto digitarmascara;
		} // endelse
	}  // endfor
	// *******************************************************
	
	// MONTA O IP DA REDE, TAMB�M DIVIDINDO EM OCTETOS
	for (i=3 ; i>=0 ; i--) {
		net[i] = ip[i] & mask[i];	
	}
	// *******************************************************

	// monta o endere�o wildcard da rede
	for (i=3 ; i>=0 ; i--) {
		wildcard[i] = 255 - mask[i];	
	}

	// ******************************************************************
	// ********* MOSTRANDO O IP DIGITADO E A MASCARA EM BINARIO *********
	// ******************************************************************
	
	// para esta convers�o, usarei uma matriz com 4 vari�veis de 8 indices cada
	// ipbin[4][8]
	
	// CONVERTER PRA BINARIO
	
	printf("\n\nO ip digitado em forma bin�ria �: \n");
	for(i = 0; i <= 3; i++) {
		n = ip[i];
		for(u = 7; u >= 0; u--) {
			resto = n % 2;
			n /= 2;
			ipbin[i][u] = resto;
			printf("%d", ipbin[i][u]);
		}
		if (i<30) {
			printf(".");
	}	}
	
	printf("\n\n");
	
	
	printf("A m�scara digitada em forma bin�ria �: \n");

	for(i = 0; i <= 3; i++) {
		n = mask[i];
		for(u = 7; u >= 0; u--) {
			resto = n % 2;
			n /= 2;
			maskbin[i][u] = resto;
			printf("%d", maskbin[i][u]);
		}
		if (i<30) {
			printf(".");
		}	
	}

	printf("\n\n");
	//printf("IP digitado em forma bin�ria: %b %c %b %c %b %c %b\n\n", ipbin[0], p, ipbin[1], p, ipbin[2], p, ipbin[3]);	
	
	
	
	// ******************************************************************
	// ************* ENCONTRANDO A QTDE DE BITS PARA REDE ***************
	// ******************************************************************

	// AS OPERA��ES ABAIXO DEDUZEM QUANTOS BITS TEM A REDE, BASEADO NA QUANTIDADE DE OCTETOS COMPLETAMENTE PREENCHIDOS
	bitsrede = 0;
	for (i = 3; i>=0 ; i--) {
		u = mask[i];
		if (u > 1) { // esta opera��o s� ser� feita se o valor do octeto n�o for 0, pois se for a rede n�o est� usando ele.
			bits = 128;
				while ( u > bits ) {
					bitsrede += 1;
					u -= bits;
					bits -= bits/2;
				}   //endwhile
			bitsrede += 1;		
		}  //endif
	} //endfor
		

	// ******************************************************************
	// ***** ENCONTRANDO A QTDE DE BITS PARA HOSTS E QTDE DE HOSTS ******
	// ******************************************************************
		
	bitshosts = 32 - bitsrede; // 32bits - qtde bits rede = bits para hosts.	
	qtdehosts = (pow(2,bitshosts)) - 2; // 2n - 2
	
	// ******************************************************************
	// *********** ENCONTRANDO A QTDE DE IPS DECIMAIS EM ****************
	// *********** TODOS OS OCTETOS N�O RESERVADOS PELA REDE ************
	// ******************************************************************
	
	n = bitshosts; // para poder operar o valor de bits para hosts sem perder ele	
	while (n>8) {
		qtdeips += 256;	// 256 equivalente a pow(2,8)
		n -= 8;
	}  //endwhile
	
	// SE A QUANTIDADE DE BITS PARA HOSTS FOR 8 OU MENOS, ENT�O 
	// A QUANTIDADE DE IPS DISPON�VEIS � IGUAL A 2 ELEVADO A N
	if (n<=8 && n > 0) {
		qtdeips += (pow(2,n)) - 1;
	} //endif


	// ******************************************************************
	// ************** 	ENCONTRANDO O ENDERE�O DE BROADCAST	 ************
	// ******************************************************************

	for (i=3 ; i>= 0 ; i--) {
		if (mask[i] < 255) {
			u = 255 - mask[i];
			bcast[i] = net[i] + u;
		} //endif
		if (mask[i]==255) {
			bcast[i] = net[i];
		}  // endif
		if (mask[i]==0) {
			bcast[i] = 255;
		} // endif
	} //endfor
		
	
	// ******************************************************************
	// ****** MOSTRAR OS DADOS DA REDE PARA O USU�RIO DO PROGRAMA *******
	// ****************************************************************** 
	
	// QTDE DE BITS PARA REDE
	printf("\nA rede usa %d bits \n\n", bitsrede);	
	
	// QTDE DE BITS PARA HOSTS
	printf("Quantidade de bits para hosts: %d \n\n", bitshosts);
	
	printf("Soma da quantidade de IPs disponiveis em cada octeto: %d \n\n", qtdeips);  // usando a variavel qtdehosts, pq a qtdeips ja foi modificada com operacoes no final do codigo
	
	// QTDE TOTAL DE HOSTS DISPON�VEIS
	printf("Quantidade de hosts (2n - 2): %d \n\n", qtdehosts);
		
	// ENDERE�O DA REDE
	printf("Endereco da rede: %d %c %d %c %d %c %d\n\n", net[0], p, net[1], p, net[2], p, net[3]);
	
	// ENDERE�O WILDCARD DA REDE
	printf("Endereco de Wildcard: %d %c %d %c %d %c %d\n\n", wildcard[0], p, wildcard[1], p, wildcard[2], p, wildcard[3]);
	
	// PRIMEIRO IP DA FAIXA
	printf("O primeiro IP disponivel na faixa eh: %d%c%d%c%d%c%d\n\n", net[0], p, net[1],  p, net[2], p, (net[3] + 1) );
	
	// �LTIMO IP DA FAIXA
	printf("O �ltimo IP disponivel na faixa eh: %d%c%d%c%d%c%d\n\n", bcast[0], p, bcast[1],  p, bcast[2], p, bcast[3] -1 );
	
	// IP DE BROADCAST DA REDE
	printf("O endere�o de broadcast da rede eh: %d%c%d%c%d%c%d \n\n", bcast[0], p, bcast[1],  p, bcast[2], p, bcast[3] );
	
	// IP DE GATEWAY NO PADR�O CISCO (�LTIMO IP DISNPON�VEL)
	printf("O gateway da rede eh: %d%c%d%c%d%c%d \n\n", bcast[0], p, bcast[1],  p, bcast[2], p, bcast[3] - 1 );


	// ******************************************************************
	// **************** FIM DO PROGRAMA -> LOOP *************************
	// ****************************************************************** 
	
	// PERGUNTA SE O USU�RIO QUER DIGITAR UM NOVO ENDERE�O.
	// SE A RESPOSTA FOR SIM, VOLTA PARA O COME�O DO C�DIGO
	// CASO N�O QUEIRA, TERMINA O C�DIGO
	printf("Deseja digitar um novo endere�o? (S / N)");
	scanf("%s" , &loop);
	if (loop == 's' || loop == 'S' ) {
		goto inputdados; // recome�a a execu��o a partir da label inputdados, no come�o do codigo
	}
	else{
		system("pause");	
	}
	return 0;

}
