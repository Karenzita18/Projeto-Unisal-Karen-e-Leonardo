#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 20
#define MAX_SUM 2000
#define MIN_SUM -2000
#define MAX_MOVES 1000

typedef struct {
    int x, y, z;
} Coordinate;

typedef struct {
    Coordinate coord;
    int sum;
} ExplorationNode;

int main() {
    int matrix[SIZE][SIZE][SIZE];
    int visited[SIZE][SIZE][SIZE] = {0}; // Inicializa todas as posições como não visitadas
    Coordinate start, end; // Coordenadas inicial e final
    int i, j, k;
    int totalMoves = 0; // Contador de movimentos

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Gera coordenadas iniciais aleatórias dentro dos limites da matriz
    start.x = rand() % SIZE;
    start.y = rand() % SIZE;
    start.z = rand() % SIZE;

    // Gera coordenadas finais aleatórias dentro dos limites da matriz
    end.x = rand() % SIZE;
    end.y = rand() % SIZE;
    end.z = rand() % SIZE;

    // Preenche a matriz com números aleatórios entre -100 e 100
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            for (k = 0; k < SIZE; k++) {
                matrix[i][j][k] = rand() % 201 - 100; // números aleatórios entre -100 e 100
            }
        }
    }

    // Imprime as coordenadas inicial e final
    printf("Coordenada Inicial: (%d, %d, %d)\n", start.x, start.y, start.z);
    printf("Coordenada Final: (%d, %d, %d)\n", end.x, end.y, end.z);

    // Inicializa a fila para explorar as coordenadas
    ExplorationNode queue[SIZE*SIZE*SIZE];
    int front = 0, rear = 0;

    // Adiciona a coordenada inicial à fila
    ExplorationNode initialNode = {start, matrix[start.x][start.y][start.z]};
    queue[rear++] = initialNode;
    visited[start.x][start.y][start.z] = 1;
    totalMoves++;

    // Algoritmo de busca em largura modificado
    while (front < rear) {
        ExplorationNode currentNode = queue[front++];
        Coordinate currentCoord = currentNode.coord;
        int currentSum = currentNode.sum;

        // Verifica se a coordenada final foi alcançada
        if (currentCoord.x == end.x && currentCoord.y == end.y && currentCoord.z == end.z) {
            printf("Coordenada final alcançada!\n");
            printf("Soma dos valores coletados: %d\n", currentSum);
            break;
        }

        // Verifica se o número máximo de movimentos foi atingido
        if (totalMoves >= MAX_MOVES) {
            printf("Limite máximo de movimentos atingido.\n");
            break;
        }

        // Verifica movimentos possíveis em todas as direções
        int dx[] = {1, -1, 0, 0, 0, 0};
        int dy[] = {0, 0, 1, -1, 0, 0};
        int dz[] = {0, 0, 0, 0, 1, -1};

        for (int d = 0; d < 6; d++) {
            int nx = currentCoord.x + dx[d];
            int ny = currentCoord.y + dy[d];
            int nz = currentCoord.z + dz[d];

            // Verifica se a próxima coordenada está dentro dos limites da matriz
            if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && nz >= 0 && nz < SIZE && !visited[nx][ny][nz]) {
                visited[nx][ny][nz] = 1;

                // Verifica se a soma atual está dentro dos limites
                if (currentSum + matrix[nx][ny][nz] <= MAX_SUM && currentSum + matrix[nx][ny][nz] >= MIN_SUM) {
                    ExplorationNode nextNode = {{nx, ny, nz}, currentSum + matrix[nx][ny][nz]};
                    queue[rear++] = nextNode;
                    totalMoves++; // Incrementa o contador de movimentos
                }
            }
        }
    }

    return 0;
}