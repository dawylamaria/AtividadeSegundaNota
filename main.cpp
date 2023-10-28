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
        cout << "A fila de alunos esta vazia!" << endl;
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
        cout << "A fila de alunos esta vazia!" << endl;
        return Aluno();
    }

    return inicio->dado;
}

int size(ElementoLista*& inicio, ElementoLista*& fim) {
    int tamanho = 0;
    ElementoLista* aux = inicio;

    while (aux != NULL) {
        aux = aux->proximo;
        tamanho++;
    }
    return tamanho;
}

void exibirFila(ElementoLista* inicio, ElementoLista* fim) {
    ElementoLista* atual = inicio;

    if (inicio == NULL) {
        cout << "A fila de alunos esta vazia!" << endl;
        return;
    }

    while (atual != NULL) {
        Aluno aluno = atual->dado;
        cout << "Nome: " << aluno.nome << endl;
        cout << "CPF: " << aluno.cpf << endl;
        cout << "Idade: " << aluno.idade << endl;
        cout << "Matricula: " << aluno.matricula << endl;

        NoDisciplina* disciplina = aluno.disciplina;
        while (disciplina != NULL) {
            cout << "Disciplina: " << disciplina->nome << endl;
            cout << "Creditos: " << disciplina->qntdCreditos << endl;

            NoConteudo* conteudo = disciplina->conteudo;
            cout << "Conteudo: ";
            while (conteudo != NULL) {
                cout << conteudo->titulo << " ";
                conteudo = conteudo->proximo;
            }

            disciplina = disciplina->proximo;
        }

        atual = atual->proximo;
        cout << "\n-------------" << endl;
    }
}

void listarDisciplinas(NoDisciplina* disciplina) {
    if (disciplina == NULL) {
        cout << "O aluno nao esta matriculado em nenhuma disciplina." << endl;
        return;
    }

    cout << "Disciplinas:" << endl;
    while (disciplina != NULL) {
        cout << "- " << disciplina->nome << endl;
        disciplina = disciplina->proximo;
    }
}

void listarConteudos(NoConteudo *conteudo) {
    if (conteudo == NULL) {
        cout << "Nao ha conteudo !" << endl;
        return;
    }

    cout << "Conteudos:" << endl;
    while (conteudo != NULL) {
        cout << "- " << conteudo->titulo << endl;
        conteudo = conteudo->proximo;
    }
}

void adicionarConteudo(NoDisciplina*& disciplina, string titulo) {
    NoConteudo* novoConteudo = new NoConteudo;
    novoConteudo->titulo = titulo;
    novoConteudo->proximo = disciplina->conteudo;
    disciplina->conteudo = novoConteudo;
}

void removerConteudo(NoDisciplina*& disciplina, string titulo) {
    NoConteudo* anterior = NULL;
    NoConteudo* conteudo = disciplina->conteudo;

    while (conteudo != NULL) {
        if (conteudo->titulo == titulo) {
            if (anterior == NULL) {
                disciplina->conteudo = conteudo->proximo;
            } else {
                anterior->proximo = conteudo->proximo;
            }
            delete conteudo;
            return;
        }
        anterior = conteudo;
        conteudo = conteudo->proximo;
    }

    cout << "Conteudo nao encontrado !" << endl;
}
void excluirDisciplina(Aluno& aluno, string nomeDisciplina) {
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
            cout << "Disciplina removida: " << nomeDisciplina << endl;
            return; 
        }
        anterior = disciplina;
        disciplina = disciplina->proximo;
    }

    cout << "Disciplina nao encontrada!" << nomeDisciplina << endl;
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
    
    cout << endl;

    cout << "Fila vazia: " << (isEmpty(inicio, fim) ? "Sim" : "Nao\n") << endl;
    
    cout << endl;

    cout << "Tamanho da fila:" << size(inicio, fim) << endl;

    cout << endl;

    Aluno alunoNaFrente = front(inicio);
    cout << "Aluno na frente da fila:" << alunoNaFrente.nome << endl;
    
    cout << endl;

    cout << "Disciplinas do aluno1: " << endl;
    listarDisciplinas(disciplina1);
    
    cout << endl;

    cout << "Adicionando conteudo 'Pilhas' a disciplina 'Estrutura de Dados'" << endl;
    adicionarConteudo(disciplina1, "Pilhas");
    listarConteudos(disciplina1->conteudo);
    
    cout << endl;

    cout << "Removendo conteudo 'Filas' da disciplina 'Estrutura de Dados'" << endl;
    removerConteudo(disciplina1, "Filas");
    listarConteudos(disciplina1->conteudo);
    
    cout << endl;

    excluirDisciplina(aluno1, "Estrutura de Dados");
    
    cout << endl;

    cout << "Fila de Alunos:" << endl;
    exibirFila(inicio, fim);

    return 0;
}

