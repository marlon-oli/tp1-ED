#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// definicao da estrutura Imagem
struct image {
  char type[2];
  int rows;
  int cols;
  int maxcollor;
  unsigned char **data;
};

// add

void free_image(Image *image) {
  for (int i = 0; i < (image->rows); i++) {
    free((image->data)[i]);
  }
  free(image);
}

int get_rows(Image *image) { return image->rows; }

int get_cols(Image *image) { return image->cols; }

// endof add

Image *create(int rows, int cols, char type[]) {

  // aloca memoria dinamicamente para a imagem
  Image *image = (Image *)malloc(sizeof(Image));
  strcpy(image->type, type);
  image->rows = rows;
  image->cols = cols;
  image->maxcollor = 255;

  if (strcmp(image->type, "P2") ==
      0) // aloca memoria para armazenar dados de imagens do tipo P2
  {
    image->data = (unsigned char **)malloc(rows * sizeof(unsigned char *));
    for (int j = 0; j < rows; j++) {
      (image->data)[j] = (unsigned char *)malloc(cols * sizeof(unsigned char));
    }
  } else if (strcmp(image->type, "P3") ==
             0) // aloca memoria para armazenar dados de imagens do tipo P3
  {
    image->data = (unsigned char **)malloc(rows * sizeof(unsigned char *));
    for (int j = 0; j < rows; j++) {
      (image->data)[j] =
          (unsigned char *)malloc(3 * cols * sizeof(unsigned char));
    }
  }
  return image;
}

Image *load_from_ppm(const char *filename) {
  FILE *arqe;
  char type[2];
  Image *image;
  int rows, cols, max;

  // abre o arquivo para leitura
  arqe = fopen(filename, "r");

  // verifica se nao houve erro na leitura
  if (arqe == NULL) {
    return NULL;
  }

  // le no arquivo as informacoes para criar a imagem
  fscanf(arqe, "%s", type);
  fscanf(arqe, "%d", &cols);
  fscanf(arqe, "%d", &rows);
  fscanf(arqe, "%d", &max);

  // cria a imagem
  image = create(rows, cols, type);

  image->maxcollor = max;

  // percorre o arquivo e preenche a matriz de dados de acordo com o tipo de
  // imagem
  if (strcmp(type, "P2") == 0) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        fscanf(arqe, "%hhu", &image->data[i][j]);
      }
    }
  } else if (strcmp(type, "P3") == 0) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols * 3; j++) {
        fscanf(arqe, "%hhu", &image->data[i][j]);
      }
    }
  }

  // fecha o arquivo
  fclose(arqe);
  return image;
}

void rgb_to_gray(Image *image_rgb, Image *image_gray) {

  // percorre a matriz de dados da imagem RGB, faz os calculos para conversao e
  // salva na matriz de dados da imagem em niveis de cinza
  for (int i = 0; i < image_gray->rows; i++) {
    for (int j = 0; j < image_rgb->cols * 3; j += 3) {
      image_gray->data[i][j / 3] =
          (unsigned char)((image_rgb->data[i][j] * 0.299) +
                          (image_rgb->data[i][j + 1] * 0.587) +
                          (image_rgb->data[i][j + 2] * 0.114));
    }
  }
}

void write_to_ppm(Image *image, const char *filename) {
  // abre o arquivo para escrita / cria um arquivo para escrita
  FILE *file = fopen(filename, "w");

  // verifica se houve algum erro no passo anterior
  if (file == NULL) {
    printf("Error opening file for writing: \n");
    return;
  }

  // escreve o cabecalho do arquivo
  fprintf(file, "%s\n", image->type);
  fprintf(file, "%d %d\n", image->cols, image->rows);
  fprintf(file, "%d\n", image->maxcollor); // Maximum pixel value

  // escreve os dados da imagem em si de acordo com o tipo de imagem
  if (strcmp(image->type, "P2") == 0) {
    for (int i = 0; i < image->rows; i++) {
      for (int j = 0; j < image->cols; j++) {
        fprintf(file, "%hhu", image->data[i][j]);
        if (j < image->cols - 1) {
          fprintf(file, " ");
        } else {
          fprintf(file, "\n");
        }
      }
    }
  } else if (strcmp(image->type, "P3") == 0) {
    for (int i = 0; i < image->rows; i++) {
      for (int j = 0; j < (3 * image->cols); j++) {
        fprintf(file, "%hhu", image->data[i][j]);
        if (j < ((3 * image->cols) - 1)) {
          fprintf(file, " ");
        } else {
          fprintf(file, "\n");
        }
      }
    }
  }

  // fecha o arquivo
  fclose(file);
};
