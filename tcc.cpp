// tcc.cpp : define o ponto de entrada para o aplicativo do console.
//


#include "stdafx.h"

#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<stdio.h>
#include<ctime>
#include "cabecalho.h"
#include <windows.h> // for EXCEPTION_ACCESS_VIOLATION
#include <excpt.h>
#include <fcntl.h>
#include <io.h>
#include "dirent.h"

using namespace std;


int random(int min, int max) {
	static bool first = true;
	if (first) {
		srand(time(NULL));
		first = false;
	}
	return min + rand() % (max - min);
}


void lerDados(char *dir) {
	int a, b, c;
	errno_t err;
	FILE * f;
	err = fopen_s(&f, dir, "r");
	fscanf_s(f, "%d""%d""%d", &p, &a, &b);
	fflush(stdin);
	fscanf_s(f, "%d\n", &m);
	fflush(stdin);
	for (int i = 0; i < p; i++) {
		for (int j = 0; j < (2 * m); j++) {
			if ((j % 2) != 0) {
				fscanf_s(f, "%d", &mat[i][j / 2]);
				fflush(stdin);
			}
			else {
				fscanf_s(f, "%d", &c);
				fflush(stdin);
			}
		}
		fscanf_s(f, "\n");
		fflush(stdin);
	}

	//le a rsmin

	for (int z = 0; z < 7; z++) {
		fscanf_s(f, "%c", &s[z]);
		fflush(stdin);
	}


	for (int x = 0; x < m; x++) {
		for (int z = 0; z < 4; z++) {
			fscanf_s(f, "%c", &e[z]);
			fflush(stdin);
		}
		for (int j = 0; j < p; j++) {
			for (int k = 0; k < p; k++) {
				fscanf_s(f, "%d", &rsmin[x][j][k]);
			}
		}
	}

	//le a rsmax

	for (int z = 0; z < 7; z++) {
		fscanf_s(f, "%c", &s[z]);
	}


	for (int x = 0; x < m; x++) {
		for (int z = 0; z < 4; z++) {
			fscanf_s(f, "%c", &e[z]);
		}
		for (int j = 0; j < p; j++) {
			for (int k = 0; k < p; k++) {
				fscanf_s(f, "%d", &rsmax[x][j][k]);
			}
		}
	}

	//le a ssmin

	for (int z = 0; z < 7; z++) {
		fscanf_s(f, "%c", &s[z]);
	}

	for (int x = 0; x < m; x++) {
		for (int z = 0; z < 4; z++) {
			fscanf_s(f, "%c", &e[z]);
		}
		for (int j = 0; j < p; j++) {
			for (int k = 0; k < p; k++) {
				fscanf_s(f, "%d", &ssmin[x][j][k]);
			}
		}
	}

	//le a ssmax

	for (int z = 0; z < 7; z++) {
		fscanf_s(f, "%c", &s[z]);
	}

	for (int x = 0; x < m; x++) {
		for (int z = 0; z < 4; z++) {
			fscanf_s(f, "%c", &e[z]);
		}
		for (int j = 0; j < p; j++) {
			for (int k = 0; k < p; k++) {
				fscanf_s(f, "%d", &ssmax[x][j][k]);
			}
		}
	}

	//djasaMais(m,p);

	fclose(f);

}

										
Solucao solucaoDjasa() {
	

	for (i = 0; i < m; i++) {
		for (j = 0; j < p; j++) {
			if (mat[i][j] < index) {
				maq = i;
				tar = j;
				index = mat[i][j];
			}
		}
	}

	
	for (i = 0; i < m; i++)
	{
		ctAaux[i] = 0;
		lastJob[i] = 0;
		for (j = 0; j < p; j++)
		{
			mapa[i][j] = 0;
		}
	}
	for (j = 0; j < p; j++)
	{
		tarefasAssociadas[j] = -1;
		vetorTP[j] = 0;
	}

	ctAaux[maq] = mat[maq][tar];
	tarefasAssociadas[tar] = 0;
	mapa[maq][0] = tar + 1;
	lastJob[maq] = 1;
	vetorTP[tar] = mat[maq][tar];


	int numRecursos = 0;


	for (i = 0; i < p; i++)
	{
		for (j = 0; j < p; j++)
		{
			vetorRecursos[i][j] = 0;
			vetorSetups[i][j] = 0;
		}
	}

	int recursoAux, tarefaEscolhida = 0, maquinaEscolhida = 0, rFinal = 0, indiceAnt;
	double setupAux, indexD, funcaoObjetivoParcial, sFinal = 0;

	for (i = 0; i < p - 1; i++)
	{
		indexD = 99999999;
		recursoAux = 0;
		setupAux = 0;
		for (j = 0; j < p; j++)
		{
			if (tarefasAssociadas[j] != 0)
			{
				for (k = 0; k < m; k++)
				{
					recursoAux = 0;
					setupAux = 0;
					if (lastJob[k] != 0)
					{
						recursoAux = CalculaRecursos(k, (mapa[k][lastJob[k] - 1]) - 1, j);
						setupAux = CalculaSetupTime(k, (mapa[k][lastJob[k] - 1]) - 1, j, recursoAux);
					}
					funcaoObjetivoParcial = (ALFA * recursoAux) + ctAaux[k] + setupAux + mat[k][j];
					if (funcaoObjetivoParcial < indexD)
					{
						indexD = funcaoObjetivoParcial;
						tarefaEscolhida = j;
						maquinaEscolhida = k;
						rFinal = recursoAux;
						sFinal = setupAux;
					}
				}
			}
		}

		tarefasAssociadas[tarefaEscolhida] = 0;
		ctAaux[maquinaEscolhida] = ctAaux[maquinaEscolhida] + sFinal + mat[maquinaEscolhida][tarefaEscolhida];
		if (lastJob[maquinaEscolhida] != 0) {
			indiceAnt = mapa[maquinaEscolhida][lastJob[maquinaEscolhida] - 1];
			vetorRecursos[indiceAnt - 1][tarefaEscolhida] = rFinal;
			numRecursos += rFinal;
			vetorSetups[indiceAnt - 1][tarefaEscolhida] = sFinal;
		}
		vetorTP[tarefaEscolhida] = mat[maquinaEscolhida][tarefaEscolhida];
		mapa[maquinaEscolhida][lastJob[maquinaEscolhida]] = tarefaEscolhida + 1;
		lastJob[maquinaEscolhida] = lastJob[maquinaEscolhida] + 1;
	}
	/******************************
	* Inicio da Criação da Solução
	******************************/
	index = 0;
	for (i = 0; i < m; i++) {
		for (j = 0; j < p; j++) {
			if (mapa[i][j] != 0) {
				vetorS[index] = mapa[i][j];
				index++;
			}
		}
		if (index != p + m - 1) {
			vetorS[index] = -1;
			index++;
		}

	}

	Solucao Sol;
	for (int i = 0; i < m + p - 1; i++)
	{
		Sol.sequencia[i] = vetorS[i];
	}

	Sol.valorFuncaoObjetivo = CalculaFuncaoObjetivoPorSequencia(vetorS);

	cout << "solucao Djasa: " << Sol.valorFuncaoObjetivo << endl;
	imprimeSolucao(Sol);

	return Sol;
}

void clonarSol(Solucao &s, Solucao &c) {
	memcpy(&c, &s, sizeof(s));
}

void imprimeSolucao(Solucao &s) {
	cout << "\nMaquina 0 = ";
	int j = 0;
	for (int i = 0; i < p + m - 1; i++)
	{
		if (s.sequencia[i] == -1)
			cout << "\nMaquina " << ++j << " = ";
		else
			cout << "[" << s.sequencia[i] << "] ";
	}

	cout << "\n\nMalhor FO " << s.valorFuncaoObjetivo << endl;
}

int CalculaRecursos(int maq, int tar1, int tar2) {
	int soma = 0;
	soma = rsmax[maq][tar1][tar2] + rsmin[maq][tar1][tar2];
	if ((soma % 2) != 0) {
		return (int)((soma + 1) / 2);
	}
	else {
		return (int)soma / 2;
	}
}

double CalculaSetupTime(int maq, int tar1, int tar2, int R) {
	double RMais, RMenos, SMais, SMenos;
	RMais = rsmax[maq][tar1][tar2];
	RMenos = rsmin[maq][tar1][tar2];
	SMais = ssmax[maq][tar1][tar2];
	SMenos = ssmin[maq][tar1][tar2];

	if (RMais != RMenos) {
		return SMais - (((SMais - SMenos) / (RMais - RMenos))*(R - RMenos));
	}
	else {
		return SMais;
	}
}

double CalculaFuncaoObjetivoPorSequencia(int Seq[150]) {

	int i, maq = 0, nRecursos = 0, h, R;
	double c = 0, CTotal = 0, K2;
	for (i = 0; i < p + m - 1; i++) {
		if (Seq[i] != -1) {
			c += mat[Seq[i] - 1][maq];
			if ((i > 0) && (Seq[i - 1] != -1)) {
				K2 = CalculaK2(maq, Seq[i - 1] - 1, Seq[i] - 1);
				h = CalculaNumeroSucessores(i - 1, Seq);
				if ((K2 != 0) && ((K2*h) < ALFA)) {
					nRecursos += rsmin[maq][Seq[i - 1] - 1][Seq[i] - 1];
					c += ssmax[maq][Seq[i - 1] - 1][Seq[i] - 1];
				}
				else if ((K2 != 0) && (K2 * h > ALFA)) {
					nRecursos += rsmax[maq][Seq[i - 1] - 1][Seq[i] - 1];
					c += ssmin[maq][Seq[i - 1] - 1][Seq[i] - 1];
				}
				else {
					R = CalculaRecursos(maq, Seq[i - 1] - 1, Seq[i] - 1);
					nRecursos += R;
					c += CalculaSetupTime(maq, Seq[i - 1] - 1, Seq[i] - 1, R);
				}
			}
			CTotal += c;
		}
		else {
			c = 0;
			maq++;
		}
	}
	return ((ALFA * nRecursos) + CTotal);
}

double CalculaK2(int maq, int tar1, int tar2) {
	double RMais, RMenos, SMais, SMenos;
	RMais = rsmax[maq][tar1][tar2];
	RMenos = rsmin[maq][tar1][tar2];
	SMais = ssmax[maq][tar1][tar2];
	SMenos = ssmin[maq][tar1][tar2];

	if (RMais != RMenos) {
		return (SMais - SMenos) / (RMais - RMenos);
	}
	else {
		return 0;
	}
}

int CalculaNumeroSucessores(int jobIndex, int Seq[]) {
	int i, h = 0;

	for (i = jobIndex + 1; i < p + m - 1; i++) {
		if (Seq[i] != -1) {
			h++;
		}
		else {
			break;
		}
	}
	return h;
}

Solucao simulateAniling(float a, int SAmax, float T0, float Tc, Solucao s) {

	Solucao s1;
	Solucao s2Viz;
	float tempo = 0;
	float delta = 0;
	double x = 0;

	clonarSol(s, s1); //s1 melhor solução até o momento
	int interT = 0;
	float T = T0;

	hi = clock();
	while (tempo < segundos) {

		while (T > Tc) {

			while (interT < SAmax) {
				interT++;

				clonarSol(gerarVizinhos(s), s2Viz);

				delta = s2Viz.valorFuncaoObjetivo - s1.valorFuncaoObjetivo;

				if (delta < 0) {
					clonarSol(s2Viz, s);

					if (s2Viz.valorFuncaoObjetivo < s1.valorFuncaoObjetivo) {
						clonarSol(s2Viz, s1);
						cout << "SA FO:" << s1.valorFuncaoObjetivo << endl;

					}
				}
				else {

					x = rand() % (101);
					x = x / 100;

					if (x < exp((-delta / T))) {
						clonarSol(s2Viz, s);
					}
				}

			}

			hf = clock();
			tempo = (((double)hf - (double)hi) / CLOCKS_PER_SEC);

			//cout << tempo << endl;

			if (tempo > segundos) {
				break;
			}
			T = a * T;
			interT = 0;


		}
		T = T0;
	}
	return s1;

}


Solucao gerarVizinhos(Solucao Origem) {
	int melhorSolucao[500] = { 0 };
	int SeqOrigem[500] = { 0 };
	int i, j, k, elemTroca;
	double ValorFOAtual, ValorFOAux=0;
	Solucao sFinal;

	clonarSol(Origem, sFinal);
	ValorFOAtual = 99999999;
	for (int i = 0; i < p + m - 1; i++)
	{
		SeqOrigem[i] = Origem.sequencia[i];
	}
	for (i = 0; i < p + m - 2; i++) {
		for (j = i + 1; j < p + m - 1; j++) {
			elemTroca = SeqOrigem[j];
			SeqOrigem[j] = SeqOrigem[i];
			SeqOrigem[i] = elemTroca;

			ValorFOAux = CalculaFuncaoObjetivoPorSequencia(SeqOrigem);

			if (ValorFOAux < ValorFOAtual) {
				ValorFOAtual = ValorFOAux;
				for (k = 0; k < p + m - 1; k++) {
					melhorSolucao[k] = SeqOrigem[k];
				}
			}
			elemTroca = SeqOrigem[j];
			SeqOrigem[j] = SeqOrigem[i];
			SeqOrigem[i] = elemTroca;
		}
	}
	if (ValorFOAtual < Origem.valorFuncaoObjetivo) {
		for (int i = 0; i < m + p - 1; i++)
		{
			Origem.sequencia[i] = melhorSolucao[i];
		}

		Origem.valorFuncaoObjetivo = ValorFOAtual;
		clonarSol(Origem, sFinal);
		//cout << "FO busca" << ValorFOAtual << endl;
	}
	return sFinal;
}

void imprimir() {
	printf("%d\n", p);
	printf("%d\n", m);


	for (int i = 0; i < p; i++) {
		for (int j = 0; j < m; j++) {
			printf("\t%d", mat[i][j]);
		}
		printf("\n");
	}

	//imprime a rsmin

	printf("RSMIN\n");

	for (int x = 0; x < m; x++) {
		printf("m%d\n", x);
		for (int y = 0; y < p; y++) {
			for (int k = 0; k < p; k++) {
				printf("\t%d", rsmin[x][y][k]);
			}
			printf("\n");
		}
	}

	//imprime a rsmax

	printf("RSMAX\n");

	for (int x = 0; x < m; x++) {
		printf("m%d\n", x);
		for (int y = 0; y < p; y++) {
			for (int k = 0; k < p; k++) {
				printf("\t%d", rsmax[x][y][k]);
			}
			printf("\n");
		}
	}

	//imprime a ssmin

	printf("SSMIN\n");

	for (int x = 0; x < m; x++) {
		printf("m%d\n", x);
		for (int y = 0; y < p; y++) {
			for (int k = 0; k < p; k++) {
				printf("\t%d", ssmin[x][y][k]);
			}
			printf("\n");
		}
	}

	//imprime a ssmax

	printf("SSMAX\n");

	for (int x = 0; x < m; x++) {
		printf("m%d\n", x);
		for (int y = 0; y < p; y++) {
			for (int k = 0; k < p; k++) {
				printf("\t%d", ssmax[x][y][k]);
			}
			printf("\n");
		}
	}
}

Solucao solucaoGRASP(Solucao aux) {
	
	double FOGrasp = 9999999;
	int i=0;
	Solucao s;
	Solucao s1;
	Solucao s2;
	clonarSol(aux, s);

	clock_t time = clock();
	i = 0;
	while (((clock() - time) / 1000) < ((p*m) / 10)) {

		
		clonarSol(s, s1);
		fflush(stdin);
		clonarSol(simulateAniling(al, SAM, To, TC, s1), s2);
		fflush(stdin);

		if (s2.valorFuncaoObjetivo < FOGrasp) {
			clonarSol(s2, s);
			FOGrasp = s2.valorFuncaoObjetivo;
			//cout << "FO Grasp = " << s.valorFuncaoObjetivo << endl;
		}
		//cout << "Itaracoes: " << (i + 1) << endl;
		//imprimeSolucao(s2);
		i++;
	}
	cout << "FO Grasp = " << s.valorFuncaoObjetivo << endl;
	cout << "time=" << ((clock() - time) / 1000) << endl;
	cout << "niteracoes=" << i << endl;
	imprimeSolucao(s2);
	return s;
}

void lerArquivosLarge() {
	struct _finddata_t finddata;
	char filtro[256];
	char texto[256];
	long res;

	strcpy_s(filtro, ".//Parallel//large//");
	strcat_s(filtro, "*.txt");

	if ((res = _findfirst(filtro, &finddata)) == -1) {
		cout << "erro ao encontrar arquivo";
	}

	do {

		if (finddata.size > 0) {

			strcpy_s(texto, "Parallel/large/");
			strcat_s(texto, finddata.name);
			printf("Arquivo: %s \n", texto);
			lerDados(texto);
			Solucao aux, solGrasp;
			clonarSol(solucaoDjasa(), aux);
			clonarSol(solucaoGRASP(aux), solGrasp);
			escreveFOArq(solGrasp, "saida/large.csv", texto);
			//imprimir();
		}

	} while (!_findnext(res, &finddata));

	_findclose(res);

}

void lerArquivosSmall() {
	
	struct _finddata_t finddata;
	char filtro[256];
	char texto[256];
	long res;

	strcpy_s(filtro, ".//Parallel//small//");
	strcat_s(filtro, "*.txt");

	if ((res = _findfirst(filtro, &finddata)) == -1) {
		cout << "erro ao encontrar arquivo";
	}

	do {

		if (finddata.size > 0) {
			
			strcpy_s(texto,"Parallel/small/");
			strcat_s(texto, finddata.name);
			printf("Arquivo: %s \n", texto);
			lerDados(texto);
			Solucao aux, solGrasp;
			clonarSol(solucaoDjasa(), aux);
			clonarSol(solucaoGRASP(aux), solGrasp);
			escreveFOArq(solGrasp,"saida/small.csv",texto);
			//imprimir();
		}

	} while (!_findnext(res, &finddata));

	_findclose(res);

}

void escreveFOArq(Solucao solFinal, char nomeArq[256], char linha[256]) {
	FILE *saida;
	errno_t err;
	err = fopen_s(&saida, nomeArq, "a");
	fprintf(saida, "%s;", linha);
	fprintf(saida, "%f;\n", solFinal.valorFuncaoObjetivo);
	fclose(saida);
}


int main() {
	
	__try {

		lerArquivosSmall();
		lerArquivosLarge();
		fflush(stdin);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		printf("Excessão lancada.\n");
	}

	system("pause");
	return 0;
}