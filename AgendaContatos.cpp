#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Contato {
    string nome;
    int numero = 0;
    string categoria;
};

bool compararContatosPorNome(const Contato& contato1, const Contato& contato2) {
    return contato1.nome < contato2.nome;
}

void exibirContatos(const vector<vector<Contato>>& matriz) {
    cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
    cout << "Agenda de Contatos:" << endl;
    cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;

    bool encontrouContatos = false;

    for (const auto& categoria : matriz) {
        for (const auto& contato : categoria) {
            if (!contato.nome.empty()) {
                cout << "Nome: " << contato.nome << endl;
                cout << "Numero: " << contato.numero << endl;
                cout << "Categoria: " << contato.categoria << endl;
                cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
                cout << endl;

                encontrouContatos = true;
            }
        }
    }

    if (!encontrouContatos) {
        cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
        cout << "Nenhum contato encontrado." << endl;
        cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
    }
}

void buscarContatos(const vector<vector<Contato>>& matriz) {
    string termoBusca;
    cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
    cout << "Digite o nome ou numero a ser buscado: " << endl;
    cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
    cin.ignore();
    getline(cin, termoBusca);

    vector<Contato> todosContatos;

    for (const auto& categoria : matriz) {
        for (const auto& contato : categoria) {
            todosContatos.push_back(contato);
        }
    }

    sort(todosContatos.begin(), todosContatos.end(), compararContatosPorNome);

    bool encontrouContatos = false;

    bool buscaPorNumero = true;
    for (char c : termoBusca) {
        if (!isdigit(c)) {
            buscaPorNumero = false;
            break;
        }
    }

    if (buscaPorNumero) {
        int numeroBusca = stoi(termoBusca);
        auto it = lower_bound(todosContatos.begin(), todosContatos.end(), numeroBusca, [](const Contato& contato, const int& numero) {
            return contato.numero < numero;
            });

        while (it != todosContatos.end() && it->numero == numeroBusca) {
            cout << "Nome: " << it->nome << endl;
            cout << "Numero: " << it->numero << endl;
            cout << "Categoria: " << it->categoria << endl;
            cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
            cout << endl;

            encontrouContatos = true;
            ++it;
        }
    }
    else {
        auto it = lower_bound(todosContatos.begin(), todosContatos.end(), termoBusca, [](const Contato& contato, const string& nome) {
            return contato.nome < nome;
            });

        while (it != todosContatos.end() && it->nome == termoBusca) {
            cout << "Nome: " << it->nome << endl;
            cout << "Numero: " << it->numero << endl;
            cout << "Categoria: " << it->categoria << endl;
            cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
            cout << endl;

            encontrouContatos = true;
            ++it;
        }
    }

    if (!encontrouContatos) {
        cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
        cout << "Nenhum contato encontrado para o termo de busca \"" << termoBusca << "\"." << endl;
        cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
    }
}

void adicionarContato(vector<vector<Contato>>& matriz) {
    Contato novoContato;
    cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
    cout << "Digite o nome do contato: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, novoContato.nome);

    cout << "Digite o numero do contato: ";
    cin >> novoContato.numero;

    if (cin.fail()) {
        cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
        cout << "Numero invalido. Apenas numeros sao permitidos." << endl;
        cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "Escolha a categoria do contato:" << endl;
    for (int i = 0; i < matriz.size(); ++i) {
        cout << i << ". " << matriz[i][0].categoria << endl;
    }
    cout << "Opcao: ";
    int opcao;
    cin >> opcao;

    if (opcao < 0 || opcao >= matriz.size()) {

        cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
        cout << "Opcao invalida." << endl;
        cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;

        return;
    }

    novoContato.categoria = matriz[opcao][0].categoria;

    matriz[opcao].push_back(novoContato);
    cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
    cout << "Contato adicionado com sucesso!" << endl;
    cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
}

void atualizarContato(vector<vector<Contato>>& matriz) {
    string nomeBusca;
    cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
    cout << "Digite o nome do contato que deseja atualizar: ";
    cin.ignore();
    getline(cin, nomeBusca);

    bool contatoEncontrado = false;

    for (auto& categoria : matriz) {
        for (auto& contato : categoria) {
            if (contato.nome == nomeBusca) {
                cout << "Digite o novo nome do contato: ";
                getline(cin,contato.nome);

                string numero;
                cout << "Digite o novo numero do contato: ";
                cin >> numero;

                int numeroInt;
                bool numeroValido = true;
                try {
                    numeroInt = stoi(numero);
                }
                catch (const invalid_argument& ) {
                    numeroValido = false;
                }

                if (!numeroValido) {
                    cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
                    cout << "Numero invalido. Apenas numeros sao permitidos." << endl;
                    cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
                    return;
                }

                contato.numero = numeroInt;

                cout << "Escolha a nova categoria do contato:" << endl;
                for (int i = 0; i < matriz.size(); ++i) {
                    cout << i << ". " << matriz[i][0].categoria << endl;
                }
                cout << "Opcao: ";
                int opcao;
                cin >> opcao;

                if (opcao < 0 || opcao >= matriz.size()) {
                    cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
                    cout << "Opcao invalida." << endl;
                    cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
                    return;
                }

                contato.categoria = matriz[opcao][0].categoria;

                cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
                cout << "Contato atualizado com sucesso!" << endl;
                cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;

                contatoEncontrado = true;
            }
        }
    }

    if (!contatoEncontrado) {
        cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
        cout << "Contato nao encontrado." << endl;
        cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
    }
}

void excluirContato(vector<vector<Contato>>& matriz) {
    string nomeBusca;
    cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
    cout << "Digite o nome do contato que deseja excluir: ";
    cin.ignore();
    getline(cin, nomeBusca);

    bool contatoEncontrado = false;

    for (auto& categoria : matriz) {
        auto it = categoria.begin();
        while (it != categoria.end()) {
            if (it->nome == nomeBusca) {
                it = categoria.erase(it);

                cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
                cout << "Contato excluido com sucesso!" << endl;
                cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;

                contatoEncontrado = true;
            }
            else {
                ++it;
            }
        }
    }

    if (!contatoEncontrado) {
        cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
        cout << "Contato nao encontrado." << endl;
        cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
    }
}

int main() {
    const vector<string> CATEGORIAS = { "Amigos", "Familia", "Trabalho" };
    vector<vector<Contato>> matriz;

    for (const string& categoria : CATEGORIAS) {
        matriz.push_back({ { "", 0, categoria } });
    }

    int opcao;
    do {
        cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
        cout << "\033[1;36mAGENDA DE CONTATOS\033[0m" << endl;
        cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
        cout << "\033[1;36m|\033[0m 1. Adicionar contato                            \033[1;36m|\033[0m" << endl;
        cout << "\033[1;36m|\033[0m 2. Atualizar contato                            \033[1;36m|\033[0m" << endl;
        cout << "\033[1;36m|\033[0m 3. Exibir contatos                              \033[1;36m|\033[0m" << endl;
        cout << "\033[1;36m|\033[0m 4. Excluir contato                              \033[1;36m|\033[0m" << endl;
        cout << "\033[1;36m|\033[0m 5. Buscar contatos                              \033[1;36m|\033[0m" << endl;
        cout << "\033[1;36m|\033[0m 6. Sair                                         \033[1;36m|\033[0m" << endl;
        cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
        cout << "Opcao: ";
        cin >> opcao;

        switch (opcao) {
        case 1:
            adicionarContato(matriz);
            break;
        case 2:
            atualizarContato(matriz);
            break;
        case 3:
            exibirContatos(matriz);
            break;
        case 4:
            excluirContato(matriz);
            break;
        case 5:
            buscarContatos(matriz);
            break;
        case 6:
            cout << "Encerrando o programa." << endl;
            break;
        default:
            cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
            cout << "Opcao invalida." << endl;
            cout << "\033[1;36m---------------------------------------------------\033[0m" << endl;
            break;
        }

        cout << endl;
    } while (opcao != 6);

    return 0;
}