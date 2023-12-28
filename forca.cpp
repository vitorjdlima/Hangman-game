#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

string escolherPalavraAleatoria(const string& arquivo) {
    ifstream arquivoPalavras(arquivo);
    vector<string> palavras;
    string palavra;

    if (!arquivoPalavras.is_open()) {
        cerr << "Erro ao abrir o arquivo de palavras." << endl;
        exit(1);
    }

    while (arquivoPalavras >> palavra) {
        palavras.push_back(palavra);
    }

    arquivoPalavras.close();

    srand(static_cast<unsigned int>(time(0)));
    return palavras[rand() % palavras.size()];
}

string inicializarPalavraOculta(const string& palavra) {
    string palavraOculta;
    for (char letra : palavra) {
        palavraOculta += (isalpha(letra) ? '_' : letra);
    }
    return palavraOculta;
}

void exibirPalavraOculta(const string& palavraOculta) {
    cout << "Palavra: " << palavraOculta << endl;
}

int main() {
    const string arquivoPalavras = "palavras.txt";
    const int maxTentativas = 6;
    int tentativasRestantes = maxTentativas;

    string palavraSecreta = escolherPalavraAleatoria(arquivoPalavras);
    string palavraOculta = inicializarPalavraOculta(palavraSecreta);
    string chute;

    cout << "Bem-vindo ao Jogo da Forca!" << endl;

    while (tentativasRestantes > 0) {
        exibirPalavraOculta(palavraOculta);

        cout << "Tentativas restantes: " << tentativasRestantes << endl;
        cout << "Digite uma letra ou chute a palavra: ";
        cin >> chute;

        if (chute.size() == 1 && isalpha(chute[0])) {
            bool letraEncontrada = false;
            for (size_t i = 0; i < palavraSecreta.size(); ++i) {
                if (tolower(chute[0]) == tolower(palavraSecreta[i])) {
                    palavraOculta[i] = palavraSecreta[i];
                    letraEncontrada = true;
                }
            }

            if (!letraEncontrada) {
                cout << "Letra incorreta. Tente novamente." << endl;
                tentativasRestantes--;
            }
        } else if (chute.size() == palavraSecreta.size() && chute == palavraSecreta) {
            cout << "Parabens! Voce acertou a palavra." << endl;
            break;
        } else {
            cout << "Incorreto. Tente novamente." << endl;
            tentativasRestantes -= 2;
        }

        if (palavraOculta == palavraSecreta) {
            cout << "Parabens! Voce acertou a palavra: " << palavraSecreta << endl;
            break;
        }
    }

    if (tentativasRestantes <= 0) {
        cout << "Voce perdeu. A palavra era: " << palavraSecreta << endl;
    }

    return 0;
}