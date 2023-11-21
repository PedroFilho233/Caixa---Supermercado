#include <iostream>

using namespace std;

struct nolista {
    string nome;
    int quant;
    double valor;
    nolista *ant;
    nolista *prox;
};

struct descritor {
    int tam;
    nolista *ini;
    nolista *fim;
};

descritor *criar_lista() {
    descritor *d = new descritor;
    d->tam = 0;
    d->ini = NULL;
    d->fim = NULL;
    return d;
}

struct nopilha {
    double dado;
    nopilha *prox;
};

nopilha *criar_pilha() {
    return NULL;
}

void menu() {
    cout << "--------------------MENU--------------------------" << endl;
    cout << "(1) Passar produtos" << endl;
    cout << "(2) Emitir nota fiscal" << endl;
    cout << "(3) Realizar novo atendimento" << endl;
    cout << "(4) Mostrar saldo do caixa e encerrar sistema" << endl;
    cout << "Escolha uma opcao: ";
}

void append(descritor *d, string nome, int quant, double valor) {
    nolista *novo = new nolista;
    novo->nome = nome;
    novo->quant = quant;
    novo->valor = valor;
    novo->ant = NULL;
    novo->prox = NULL;

    if (d->ini == NULL) {
        d->ini = novo;
        d->fim = novo;
        d->tam++;
    } else {
        d->fim->prox = novo;
        novo->ant = d->fim;
        d->fim = novo;
        d->tam++;
    }
}

void push(nopilha *&topo, int quant, double valor, double &saldoCaixa) {
    double valorCompra = quant * valor;
    nopilha *novo = new nopilha;
    novo->dado = valorCompra;
    novo->prox = topo;
    topo = novo;
    saldoCaixa += topo->dado;
}

void passarProdutos(descritor *d, nopilha *p, string nome, int quant, double valor, double &saldoCaixa) {
    int tam = 0;
    cout << "--------------------------------------------------" << endl;
    cout << "Quantidade de produtos: ";
    cin >> tam;
    cout << "--------------------------------------------------" << endl;

    for (int i = 0; i < tam; i++) {
        cout << "Nome do produto: ";
        cin >> nome;
        cout << "Quantidade: ";
        cin >> quant;
        cout << "Valor: ";
        cin >> valor;
        append(d, nome, quant, valor);
        push(p, quant, valor, saldoCaixa);
        cout << "\n";
    }
}

void notaFiscal(descritor *d) {
    string nome, cpf;
    double total = 0;
    nolista *p = d->ini;
    
    cout << "--------------------------------------------------" << endl;
    cout << "Nome do cliente: ";
    cin >> nome;
    cout << "CPF: ";
    cin >> cpf;
    
    if(d -> tam > 0) {
    cout << "\n------------------Nota fiscal--------------------" << endl;
    cout << "Cliente: " << nome << ", CPF: " << cpf << endl;
    cout << "Produtos comprados: " << endl;
    
    while (p != NULL) {
        cout << p->quant << "x " << p->nome << " = " << p->quant * p->valor << endl;
        total += p->quant * p->valor;
        p = p->prox;
    }
    
    cout << "Total: R$ " << total << endl;
    
    } else {
        cout << "--------------------------------------------------" << endl;
        cout << "Selecione um produto antes de emitir a nota fiscal" << endl;
    }
}

void mostrarSaldo(double saldoCaixa) {
    cout << "--------------------------------------------------" << endl;
    cout << "Saldo do caixa: R$ " << saldoCaixa << endl;
    cout << "Encerrando sistema...";
}

int main() {
    descritor *d = criar_lista();
    nopilha *p = criar_pilha();
    int op, quant;
    string nome;
    double valor, saldoCaixa = 0;

    do {
        menu();
        cin >> op;

        switch (op) {
        case 1:
            passarProdutos(d, p, nome, quant, valor, saldoCaixa);
            break;
        case 2:
            notaFiscal(d);
            break;
        case 3:
            cout << "--------------------------------------------------" << endl;
            cout << "Novo atendimento iniciado!" << endl;
            d = criar_lista();
            break;
        case 4:
            mostrarSaldo(saldoCaixa);
            break;
        default:
            cout << "--------------------------------------------------" << endl;
            cout << "Opcao invalida! Digite novamente." << endl;
        }
    } while (op != 4);

    return 0;
}
