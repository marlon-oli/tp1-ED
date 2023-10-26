#include "image.h"
#include <malloc.h>
#include <stdio.h>

int main() {

  // declaracao de variaveis
  Image *image, *image_gray;
  int choice;
  const char *path = (const char *)malloc(30 * sizeof(char));

  // menu inicial
  printf("Choose:\n\n");
  printf("1 - To load an RGB image;\n");
  printf("2 - To choose a default RGB image.\n\n");
  printf("->");

  // salva a escolha do usuario
  scanf("%d", &choice);

  // validacao de escolha
  if ((choice != 1) && (choice != 2)) // valida se a escolha e valida
  {
    printf("\nInvalid choice! Try again.");
    return 1;
  }

  // solicita o caminho para o arquivo PPM
  if (choice == 1) {
    printf("\nEnter the path for your PPM file:\n\n");
    printf("->");
    scanf("%s", path);
  }

  // usa um caminho para uma imagem default
  if (choice == 2) {
    path = "defaultimage.ppm";
  }

  // carrega a imagem de acordo com o caminho fornecido anteriormente
  image = load_from_ppm(path);

  // verifica se a imagem carregou corretamente
  if (!image) {
    printf("\nError opening the file!\n");
    return 1;
  };

  printf("\nChoose:\n\n");
  printf("1 - To transform an RGB image to a grayscale image;\n");
  printf("2 - To write the image to a PPM file.\n\n");
  printf("->");

  scanf("%d", &choice);

  if (choice == 1) {
    // aloca memoria para a imagem em niveis de cinza
    image_gray = create(get_rows(image), get_cols(image), "P2");

    // converte a imagem RGB em niveis de cinza
    rgb_to_gray(image, image_gray);

    printf("\nChoose:\n\n");
    printf("1 - To write the RGB image to a PPM file;\n");
    printf("2 - To write the grayscale image to a PPM file.\n\n");
    printf("->");

    scanf("%d", &choice);

    if (choice == 1) {
      // escreve no arquivo a imagem RGB
      write_to_ppm(image, "resultimage.ppm");

    } else if (choice == 2) {
      // escreve no arquivo a imagem RGB convertida para niveis de cinza
      write_to_ppm(image_gray, "resultimage.ppm");
    }

    free_image(image_gray);

  } else if (choice == 2) {
    // escreve no arquivo a imagem RGB
    write_to_ppm(image, "resultimage.ppm");
  }

  free_image(image);

  return 0;
}
