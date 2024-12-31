#include <stdio.h>
#include <openssl/evp.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
  EVP_MD_CTX *mdctx;
  const EVP_MD *md;
  unsigned char md_value[EVP_MAX_MD_SIZE];
  unsigned int md_len, i, n;
  char buffer[BUFFER_SIZE];
  FILE *fileptr;

  if (argc < 2) {
    printf("Usage: %s" <filename>\n", argv[0]);
    exit(1);
  }

  fileptr = fopen(argv[1], "rb");
  if (fileptr == NULL) {
    printf("Failed to open file");
    exit(1);
  }

  md = EVP_sha256();
  if (md == NULL) {
    printf("Getting the message digest failed.\n");
    exit(1);
  }

  mdctx = EVP_MD_CTX_new();
  EVP_DigestInit_ex(mdctx, md, NULL);

  while ((n=fread(buffer, 1, sizeof(buffer), fileptr))) {
    EVP_DigestUpdate(mdctx, buffer, n);
  }

  EVP_DigestFinal_ex(mdctx, md_value, &md_len);

  for(i=0;i<md_len;i++) {
    printf("%02x", md_value[i]);
  }
  prinf("\n");
  fclose(fileptr);
  return 0;
}
