#include <iostream>
#include <string>

using namespace std;

struct NoConteudo {
    string titulo;
    NoConteudo* proximo;
};

struct NoDisciplina {
    string nome;
    int qntdCreditos;
    NoConteudo* conteudo;
    NoDisciplina* proximo;
};

struct Aluno {
    string nome;
    string cpf;
    int idade;
    string matricula;
    NoDisciplina* disciplina;
};

struct ElementoLista {
    Aluno dado;
    ElementoLista* proximo;
};

void enqueue(ElementoLista*& inicio, ElementoLista*& fim, Aluno aluno) {
    ElementoLista* elemento = new ElementoLista;
    elemento->dado = aluno;
    elemento->proximo = NULL;

    if (inicio == NULL && fim == NULL) {
        inicio = elemento;
        fim = elemento;
    } else {
        fim->proximo = elemento;
        fim = elemento;
    }
}

Aluno dequeue(ElementoLista*& inicio, ElementoLista*& fim) {
    if (inicio == NULL) {
        cout << "A fila de alunos está vazia." << endl;
        return Aluno();
    } else if (inicio == fim) {
        ElementoLista* aux = inicio;

        inicio = NULL;
        fim = NULL;

        Aluno alunoDeletado = aux->dado;
        delete aux;
        return alunoDeletado;
    } else {
        ElementoLista* aux = inicio;
        inicio = inicio->proximo;
        Aluno alunoDeletado = aux->dado;
        delete aux;
        return alunoDeletado;
    }
}

bool isEmpty(ElementoLista*& inicio, ElementoLista*& fim) {
    return (inicio == NULL);
}

Aluno front(ElementoLista*& inicio) {
    if (inicio == NULL) {
        cout << "A fila de alunos está vazia." << endl;
        return Aluno();
    }

    return inicio->dado;
}

int size(ElementoLista*& inicio, ElementoLista*& fim) {
    int tamanho = 0;
    ElementoLista* aux = inicio;

    if (inicio == NULL) {
        return 0;
    }
    while (aux != NULL) {
        aux = aux->proximo;
        tamanho++;
    }
    return tamanho;
}

void exibirFila(ElementoLista* inicio, ElementoLista* fim) {
    ElementoLista* atual = inicio;

    if (inicio == NULL) {
        cout << "A fila de alunos está vazia." << endl;
        return;
    }

    while (atual != NULL) {
        Aluno aluno = atual->dado;
        cout << "Nome: " << aluno.nome << endl;
        cout << "CPF: " << aluno.cpf << endl;
        cout << "Idade: " << aluno.idade << endl;
        cout << "Matrícula: " << aluno.matricula << endl;

        if (aluno.disciplina != NULL) {
            NoDisciplina* disciplina = aluno.disciplina;
            cout << "Disciplina: " << disciplina->nome << endl;
            cout << "Créditos: " << disciplina->qntdCreditos << endl;

            NoConteudo* conteudo = disciplina->conteudo;
            cout << "Conteúdo: ";
            while (conteudo != NULL) {
                cout << conteudo->titulo << " ";
                conteudo = conteudo->proximo;
            }
        } else {
            cout << "Aluno sem disciplina." << endl;
        }

        atual = atual->proximo;
        cout << "\n-------------" << endl;
    }
}

void removerDisciplina(Aluno& aluno, string nomeDisciplina) {
    NoDisciplina* anterior = NULL;
    NoDisciplina* disciplina = aluno.disciplina;

    while (disciplina != NULL) {
        if (disciplina->nome == nomeDisciplina) {
            if (anterior == NULL) {
                aluno.disciplina = disciplina->proximo;
            } else {
                anterior->proximo = disciplina->proximo;
            }
            delete disciplina;
            return;
        }
        anterior = disciplina;
        disciplina = disciplina->proximo;
    }

    cout << "Disciplina nao encontrada para remocao." << endl;
}

int main(int argc, char** argv) {
    ElementoLista* inicio = NULL;
    ElementoLista* fim = NULL;

    NoDisciplina* disciplina1 = new NoDisciplina;
    disciplina1->nome = "Estrutura de Dados";
    disciplina1->qntdCreditos = 3;
    disciplina1->conteudo = new NoConteudo;
    disciplina1->conteudo->titulo = "Filas";
    disciplina1->conteudo->proximo = NULL;
    disciplina1->proximo = NULL;

    NoDisciplina* disciplina2 = new NoDisciplina;
    disciplina2->nome = "Banco de Dados";
    disciplina2->qntdCreditos = 3;
    disciplina2->conteudo = new NoConteudo;
    disciplina2->conteudo->titulo = "Tabelas";
    disciplina2->conteudo->proximo = NULL;
    disciplina2->proximo = NULL;

    Aluno aluno1;
    aluno1.nome = "Dawyla";
    aluno1.cpf = "123456";
    aluno1.idade = 19;
    aluno1.matricula = "A123";
    aluno1.disciplina = disciplina1;

    Aluno aluno2;
    aluno2.nome = "Maria";
    aluno2.cpf = "78910";
    aluno2.idade = 19;
    aluno2.matricula = "A456";
    aluno2.disciplina = disciplina2;

    enqueue(inicio, fim, aluno1);
    enqueue(inicio, fim, aluno2);

    cout << "Fila de Alunos:" << endl;
    exibirFila(inicio, fim);

    cout << "Fila vazia: " << (isEmpty(inicio, fim) ? "Sim" : "Não") << endl;

    cout << "Tamanho da fila: " << size(inicio, fim) << endl;

    cout << endl;

    Aluno alunoNaFrente = front(inicio);
    cout << "Aluno na frente da fila: " << alunoNaFrente.nome << endl;

    removerDisciplina(aluno1, "Estrutura de Dados");
    removerDisciplina(aluno2, "Banco de Dados");

    cout << "Fila de Alunos após remover disciplinas:" << endl;
    exibirFila(inicio, fim);

    return 0;
}

