#pragma once
#ifndef CABECALHOS_H_INCLUDED
#define CABECALHOS_H_INCLUDED

static int mat[100][100] = { 0 };
static int mat_aux[100][100] = { 0 };
static int rsmin[50][100][100] = { 0 };
static int rsmax[50][100][100] = { 0 };
static int ssmin[50][100][100] = { 0 };
static int ssmax[50][100][100] = { 0 };
static int maquinas[100] = { 0 };
static int lastJob[50] = {-1};
static int ctim[50] = {0};
static int trec=0;
static int m=0,p=0;
static char s[8] = { 0 };
static char e[3] = { 0 };
static int ALFA = 50;
static int vetorRecursos[100][100] = { 0 };
static double vetorSetups[100][100] = { 0 };

static int mapa[150][150] = { 0 };
static double ctAaux[150] = { 0 };
static int tarefasAssociadas[100] = { 0 };
static int i, j, k, maq = -1, tar = -1, index = 999999;
static int vetorTP[150] = { 0 };
static int vetorS[150] = { 0 };

//variaveis para SA
static double al = 0.975;
static double TC = 0.01;
static double To = 1000;
static int SAM = 1000;

//Tempo de execução
static int segundos = 1;
clock_t hi, hf;

typedef struct solucaoBase
{
	int sequencia[150] = { 0 };
	double valorFuncaoObjetivo = 0;
}Solucao;

void lerDados(char dir[150]);

Solucao solucaoDjasa();

void clonarSol(Solucao &s, Solucao &c);

void imprimeSolucao(Solucao &s);

int CalculaRecursos(int maq, int tar1, int tar2);

double CalculaSetupTime(int maq, int tar1, int tar2, int R);

double CalculaFuncaoObjetivoPorSequencia(int Seq[]);

double CalculaK2(int maq, int tar1, int tar2);

int CalculaNumeroSucessores(int jobIndex, int Seq[]);

Solucao simulateAniling(float a, int SAmax, float T0, float Tc, Solucao s);

Solucao gerarVizinhos(Solucao Origem);

Solucao solucaoGRASP(Solucao aux);

void escreveFOArq(Solucao solFinal, char nomeArq[150], char linha[150]);

void lerArquivosSmall();

void lerArquivosLarge()

void imprimir();


#endif // CABECALHOS_H_INCLUDED