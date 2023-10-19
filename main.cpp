/* Enunciado: 
Prática Tabela Hash

1. Implementar uma estrutura de tabela hash para armazenar n objetos com encadeamento separado duplo. 
No encadeamento duplo existem dois níveis de endereçamento, nos dois o mapeamento da chave ao
endereço se dá por uma função hash. A figura abaixo ilustra o esquema de encadeamento separado duplo.

  a. No primeiro nível crie um vetor com 10 ponteiros para vetores.
Aplique a função hash para direcionar o elemento da chave c em uma das outras tabelas do segundo nível;

  b. No segundo nível cada tabela é composta por um vetor de n/10 listas de objetos a serem armazenados. 
Uma segunda função hash diferente da primeira deve ser definida para direcionar a chave c em uma das listas específicas.

2. Implemente as funções hash específica de cada nível de endereçamento, além dos métodos de inserção
de novos objetos a partir de suas chaves únicas e recuperação de objetos já cadastrados a partir da chave única.
*/


#include <iostream>
#include <vector>
using namespace std;

class aluno {
public:
    string nome;
    int matricula;
    
    aluno(string n, int m){
        nome = n;
        matricula = m;
    };

    string info() const {
        return nome + " - " + to_string(matricula) + "; ";
    };
};

//tabela hash com o encadeamento separado duplo
class tabela_hash {
    
    int tamanho;
    vector<vector<aluno>> primeiro_nivel; //lista
    vector<vector<vector<aluno>>> segundo_nivel; //lista da lista

    int hash_primeiro(string chave_str) {
        int num = 0;
        
        for (char c : chave_str) {
            num += int(c);
        };
        
        return num % tamanho;
    };
    
    int hash_segundo(string chave_str) {
        int num = 0;
        
        for (char c : chave_str) {
            num += int(c);
        };
        
        return num % (tamanho / 10);
    };

    public:
        tabela_hash(int s) : tamanho(int(s * 1.25)), primeiro_nivel(tamanho), segundo_nivel(tamanho / 10) {};
        
        void inserir(string chave, aluno valor) {
            //recebe
            int pos1 = hash_primeiro(chave);
            int pos2 = hash_segundo(chave);
            //insere
            primeiro_nivel[pos1].push_back(valor);
            segundo_nivel[pos1][pos2].push_back(valor);
        };
        
        /* //versão 1
        aluno* buscar(string chave) {
            vector<string> lista_alunos;
            //recebe
            int pos1 = hash_primeiro(chave);
            int pos2 = hash_segundo(chave);
            
            vector<aluno>& lista_alu = segundo_nivel[pos1][pos2];
            
            //verifica
            for (const aluno& al : lista_alu) {
                if (al.nome == chave) {
                    lista_alunos.push_back(al.info());
                };
            };
            //caso não ache
            return nullptr;
        };
        */
        
        //versão 2
        vector<string> buscar(string chave) {
        vector<string> lista_alunos;
        int pos1 = hash_primeiro(chave);
        int pos2 = hash_segundo(chave);
        
        vector<aluno>& lista_alu = segundo_nivel[pos1][pos2];
        
        for (const aluno& al : lista_alu) {
            if (al.nome == chave) {
                lista_alunos.push_back(al.info());
            };
        };
        
        return lista_alunos;
    };
        
        void imprimir() {
            for (int i = 0; i < tamanho; i++) {
                cout << "[";
                
                for (aluno& al : primeiro_nivel[i]) {
                    cout << al.info() << " ";
                };
                
                cout << "]" << endl;
            };
        };
};

int main() {
    aluno a1("Maria", 12);
    aluno a2("João", 6);
    aluno a3("José", 24);
    aluno a4("Lucas", 36);
    aluno a5("Matheus", 3);
    aluno a6("Simão", 7);
    
    //cout << a1.info();

    tabela_hash hash(10);
    
    //hash.imprimir();
    
    hash.inserir(a1.nome, a1);
    hash.inserir(a2.nome, a2);
    hash.inserir(a3.nome, a3);
    hash.inserir(a4.nome, a4);
    hash.inserir(a5.nome, a5);
    hash.inserir(a6.nome, a6);

    hash.imprimir();
    

    /* //versão 1
    aluno* al = hash.buscar("Maria");
    if (al != nullptr) {
        cout << "Aluno encontrado: " << al->info() << endl;
    } else {
        cout << "Aluno não encontrado." << endl;
    };
    */
    
    //versão 2
    vector<string> alunos = hash.buscar(a1.nome);
    for (const string& aluno : alunos) {
        cout << aluno << endl;
    };
    
    hash.imprimir();
    
    
    return 0;
};



