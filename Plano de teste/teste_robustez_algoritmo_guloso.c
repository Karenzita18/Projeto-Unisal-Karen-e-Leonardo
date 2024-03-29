#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 20
#define MAX_SUM 2000
#define MIN_SUM -2000

typedef struct {
    int x, y, z;
} Coordinate;

// Função para preencher a matriz com valores aleatórios
void preencherMatriz(int matrix[SIZE][SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                matrix[i][j][k] = rand() % 201 - 100; // números aleatórios entre -100 e 100
            }
        }
    }
}

// Função para verificar se uma coordenada está dentro dos limites da matriz
int dentroDosLimites(int x, int y, int z) {
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE && z >= 0 && z < SIZE;
}

int main() {
    int matrix[SIZE][SIZE][SIZE];
    int visited[SIZE][SIZE][SIZE] = {0}; // Inicializa todas as posições como não visitadas
    Coordinate queue[SIZE*SIZE*SIZE]; // Fila para armazenar as coordenadas a serem visitadas
    int front = 0, rear = 0; // Variáveis de controle da fila
    Coordinate start, end; // Coordenadas inicial e final
    int sum = 0; // Soma dos valores coletados durante o caminho

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Gera coordenadas iniciais aleatórias
    start.x = rand() % SIZE;
    start.y = rand() % SIZE;
    start.z = rand() % SIZE;

    // Gera coordenadas finais aleatórias
    end.x = rand() % SIZE;
    end.y = rand() % SIZE;
    end.z = rand() % SIZE;

    // Preenche a matriz com valores aleatórios
    preencherMatriz(matrix);

    // Imprime as coordenadas inicial e final
    printf("Coordenada Inicial: (%d, %d, %d)\n", start.x, start.y, start.z);
    printf("Coordenada Final: (%d, %d, %d)\n", end.x, end.y, end.z);

    // Inicializa a fila com a coordenada inicial
    queue[rear++] = start;
    visited[start.x][start.y][start.z] = 1;
    sum += matrix[start.x][start.y][start.z];

    // Algoritmo Guloso
    while (front < rear) {
        Coordinate current = queue[front++];

        // Verifica se a soma atingiu os limites
        if (sum >= MAX_SUM || sum <= MIN_SUM) {
            printf("A soma alcançou o limite. Parando em: (%d, %d, %d)\n", current.x, current.y, current.z);
            printf("Soma dos valores coletados: %d\n", sum);
            break;
        }

        if (current.x == end.x && current.y == end.y && current.z == end.z) {
            printf("Coordenada final alcançada!\n");
            printf("Soma dos valores coletados: %d\n", sum);
            break;
        }

        // Verifica movimentos possíveis em todas as direções
        int dx[] = {1, -1, 0, 0, 0, 0};
        int dy[] = {0, 0, 1, -1, 0, 0};
        int dz[] = {0, 0, 0, 0, 1, -1};

        for (int d = 0; d < 6; d++) {
            int nx = current.x + dx[d];
            int ny = current.y + dy[d];
            int nz = current.z + dz[d];

            if (dentroDosLimites(nx, ny, nz) && !visited[nx][ny][nz]) {
                visited[nx][ny][nz] = 1;
                Coordinate next = {nx, ny, nz};
                queue[rear++] = next;
                sum += matrix[nx][ny][nz];
            }
        }
    }

    return 0;
}

