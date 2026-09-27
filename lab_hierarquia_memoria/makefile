CC = gcc
CFLAGS = -Wall -pthread
SRC_DIR = src
BIN_DIR = bin

all: clean create_bin O0 O3

create_bin:
	mkdir -p $(BIN_DIR)

O0:
	$(CC) $(CFLAGS) -O0 $(SRC_DIR)/varredura_linha.c -o $(BIN_DIR)/varredura_linha_O0
	$(CC) $(CFLAGS) -O0 $(SRC_DIR)/varredura_coluna.c -o $(BIN_DIR)/varredura_coluna_O0
	$(CC) $(CFLAGS) -O0 $(SRC_DIR)/matmul_padrao.c -o $(BIN_DIR)/matmul_padrao_O0
	$(CC) $(CFLAGS) -O0 $(SRC_DIR)/matmul_bloco.c -o $(BIN_DIR)/matmul_bloco_O0
	$(CC) $(CFLAGS) -O0 $(SRC_DIR)/matmul_pthreads.c -o $(BIN_DIR)/matmul_pthreads_O0
	$(CC) $(CFLAGS) -O0 $(SRC_DIR)/matmul_pthreads_bloco.c -o $(BIN_DIR)/matmul_pthreads_bloco_O0

O3:
	$(CC) $(CFLAGS) -O3 $(SRC_DIR)/varredura_linha.c -o $(BIN_DIR)/varredura_linha_O3
	$(CC) $(CFLAGS) -O3 $(SRC_DIR)/varredura_coluna.c -o $(BIN_DIR)/varredura_coluna_O3
	$(CC) $(CFLAGS) -O3 $(SRC_DIR)/matmul_padrao.c -o $(BIN_DIR)/matmul_padrao_O3
	$(CC) $(CFLAGS) -O3 $(SRC_DIR)/matmul_bloco.c -o $(BIN_DIR)/matmul_bloco_O3
	$(CC) $(CFLAGS) -O3 $(SRC_DIR)/matmul_pthreads.c -o $(BIN_DIR)/matmul_pthreads_O3
	$(CC) $(CFLAGS) -O3 $(SRC_DIR)/matmul_pthreads_bloco.c -o $(BIN_DIR)/matmul_pthreads_bloco_O3

clean:
	rm -rf $(BIN_DIR)