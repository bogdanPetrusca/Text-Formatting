//PETRUSCA BOGDAN-MIHAI 313CB

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void deleteTrailingSpaces(char *str) {
  char p[1000];
  strcpy(p, str);
  int i, poz, nr = 0;
  for (i = strlen(p) - 2; i >= 0; i--)
    if (*(p + i) == ' ' || *(p + i) == '\t')
      nr++;
    else {
      poz = i + 1;
      break;
    }

  p[poz] = '\n';
  p[poz + 1] = '\0';
  strcpy(str, p);
}
void deleteStartingSpaces(char *str) {
  char p[1000];
  strcpy(p, str);
  int i, nr = 0;
  for (i = 0; i < strlen(p); i++)
    if (*(p + i) == ' ' || *(p + i) == '\t')
      nr++;
    else {
      break;
    }
  memmove(p, p + nr, 1000);
  strcpy(str, p);
}
void left_right_limits(int linii, char left[10], char right[10],
                       int *start_line, int *end_line) {
  if (strlen(left) == 0 && strlen(right) == 0) {
    *start_line = 0;
    *end_line = linii;
  }
  if (strlen(left) != 0 && strlen(right) == 0) {
    *start_line = atoi(left);
    *end_line = linii;
  }
  if (strlen(left) != 0 && strlen(right) != 0) {
    *start_line = atoi(left);
    *end_line = atoi(right);
  }
  if (*end_line > linii) *end_line = linii;
}
int max_Length(char a[1000][1000], int linii) {
  int maxLength = 0, i;
  for (i = 0; i < linii; i++) {
    if (strlen(a[i]) > maxLength) {
      maxLength = strlen(a[i]);
    }
  }
  return maxLength;
}
int line_Max(char a[1000][1000], int linii) {
  int lineMax = 0, i, maxLength = 0;
  for (i = 0; i < linii; i++)
    if (strlen(a[i]) > maxLength) {
      maxLength = strlen(a[i]);
      lineMax = i;
    }
  return lineMax;
}
void alignLeft(char a[1000][1000], int linii, char left[10], char right[10]) {
  int i, j, start_line, end_line, nr = 0;
  left_right_limits(linii, left, right, &start_line, &end_line);
  if (start_line == end_line) {
    for (j = 0; j < strlen(a[start_line]); j++)
      if (a[start_line][j] == ' ')
        nr++;
      else
        break;
    memmove(a[start_line], a[start_line] + nr, 1000);
  }
  for (i = start_line; i <= end_line; i++) {
    nr = 0;
    if (strlen(a[i]) != 1) {
      for (j = 0; j < strlen(a[i]); j++)
        if (a[i][j] == ' ')
          nr++;
        else
          break;
    }
    memmove(a[i], a[i] + nr, 1000);
  }

  deleteTrailingSpaces(a[linii - 1]);
}

void alignRight(char a[1000][1000], int linii, char left[10], char right[10]) {
  int i, maxLength, linieMax, start_line, end_line;
  left_right_limits(linii, left, right, &start_line, &end_line);
  maxLength = max_Length(a, linii);
  linieMax = line_Max(a, linii);

  if (start_line == end_line) {
    while (strlen(a[start_line]) < maxLength - 1) {
      memmove(a[start_line] + 1, a[start_line], strlen(a[start_line]));
      a[start_line][0] = ' ';
    }
  }
  if (start_line == end_line) {
    memmove(a[start_line] + 1, a[start_line], strlen(a[start_line]));
    a[start_line][0] = ' ';
  }
  for (i = start_line; i < end_line; i++) {
    if (i != linieMax && strlen(a[i]) != 1) {
      if (i != linii - 1) {
        while (strlen(a[i]) < maxLength) {
          memmove(a[i] + 1, a[i], strlen(a[i]));
          a[i][0] = ' ';
        }
      }
      if (i == linii - 1) {
        while (strlen(a[i]) < maxLength) {
          memmove(a[i] + 1, a[i], strlen(a[i]));
          a[i][0] = ' ';
        }
      }
    }
  }
}
void center(char a[1000][1000], int linii, char left[10], char right[10]) {
  int i, maxLength = strlen(a[0]), linieMax = 0, start_line, end_line;
  left_right_limits(linii, left, right, &start_line, &end_line);
  maxLength = max_Length(a, linii);
  linieMax = line_Max(a, linii);
  for (i = start_line; i <= end_line; i++) {
    int temp;
    temp = strlen(a[i]);
    if (i != linieMax && temp != 1) {
      int val = (maxLength - temp) / 2;
      int cont = 0;
      if ((maxLength - temp) % 2 == 0)
        while (cont < val) {
          memmove(a[i] + 1, a[i], strlen(a[i]));
          a[i][0] = ' ';
          cont++;
        }
      else
        while (cont < val + 1) {
          memmove(a[i] + 1, a[i], strlen(a[i]));
          a[i][0] = ' ';
          cont++;
        }
    }
  }
}
void list(char a[1000][1000], int linii, char list_type[10], char separator[10],
          char left[10], char right[10]) {
  int start_line, end_line, nr = 1, i;
  char buff[1000], cont_a = 'a', cont_A = 'A';
  left_right_limits(linii, left, right, &start_line, &end_line);
  for (i = start_line; i <= end_line; i++) {
    switch (list_type[0]) {
      case 'n':
        sprintf(buff, "%d%c %s", nr++, separator[0], a[i]);
        memmove(a[i], buff, 1000);
        break;
      case 'a':
        sprintf(buff, "%c%c %s", cont_a++, separator[0], a[i]);
        memmove(a[i], buff, 1000);
        break;
      case 'A':
        sprintf(buff, "%c%c %s", cont_A++, separator[0], a[i]);
        memmove(a[i], buff, 1000);
        break;
      case 'b':
        sprintf(buff, "%c %s", separator[0], a[i]);
        memmove(a[i], buff, 1000);
        break;
    }
  }

  deleteTrailingSpaces(a[linii - 2]);
}
void orderedList(char a[1000][1000], int linii, char list_type[10],
                 char separator[10], char ordering[10], char left[10],
                 char right[10]) {
  int start_line, end_line, nr = 1, i, j;
  char buff[1000], cont_a = 'a', cont_A = 'A';
  left_right_limits(linii, left, right, &start_line, &end_line);

  if (end_line == linii) {
    end_line--;
  }
  for (i = start_line; i <= end_line; i++)
    for (j = i + 1; j <= end_line; j++) {
      if (a[i][0] == '\n' || a[i][0] == '\0') continue;
      if (strcmp(ordering, "a") == 0) {
        if (strcmp(a[i], a[j]) > 0) {
          char temp[1000];
          strcpy(temp, a[i]);
          strcpy(a[i], a[j]);
          strcpy(a[j], temp);
        }
      } else if (strcmp(ordering, "z") == 0) {
        if (strcmp(a[i], a[j]) < 0) {
          char temp[1000];
          strcpy(temp, a[i]);
          strcpy(a[i], a[j]);
          strcpy(a[j], temp);
        }
      }
    }
  for (i = start_line; i <= end_line; i++) {
    switch (list_type[0]) {
      case 'n':
        sprintf(buff, "%d%c %s", nr++, separator[0], a[i]);
        memmove(a[i], buff, 1000);
        break;
      case 'a':
        sprintf(buff, "%c%c %s", cont_a++, separator[0], a[i]);
        memmove(a[i], buff, 1000);
        break;
      case 'A':
        sprintf(buff, "%c%c %s", cont_A++, separator[0], a[i]);
        memmove(a[i], buff, 1000);
        break;
      case 'b':
        sprintf(buff, "%c %s", separator[0], a[i]);
        memmove(a[i], buff, 1000);
        break;
    }
  }
  deleteTrailingSpaces(a[linii - 2]);
}
void paragraphs(char a[1000][1000], int linii, char tab_size[10], char left[10],
                char right[10]) {
  int start_line, end_line, i, j;
  int size = atoi(tab_size);
  char spaces[1000], buff[1000];
  left_right_limits(linii, left, right, &start_line, &end_line);

  for (j = 0; j < size; j++) spaces[j] = ' ';

  for (i = start_line; i <= end_line; i++) {
    if (strlen(a[i - 1]) == 1 || i == 0) {
      sprintf(buff, "%s%s", spaces, a[i]);
      memmove(a[i], buff, strlen(buff));
    }
  }
}
void justify(char a[1000][1000], int linii, char left[10], char right[10]) {
  int start_line, end_line, i, maxLength, j;
  left_right_limits(linii, left, right, &start_line, &end_line);
  for (i = start_line; i < end_line; i++) deleteStartingSpaces(a[i]);
  maxLength = max_Length(a, linii);
  int cont = 0, k;
  for (i = start_line; i < end_line; i++) {
    if (strlen(a[i]) == maxLength) continue;
    if (strlen(a[i + 1]) == 0) continue;
    if (strlen(a[i]) > 1) {
      while (strlen(a[i]) < maxLength) {
        for (j = 0; j < strlen(a[i]); j++) {
          if (a[i][j] == ' ') {
            memmove(a[i] + j + 1, a[i] + j, strlen(a[i]) - j);
            k = j;
            while (a[i][++k] == ' ') cont++;
            j = j + cont;
          }
          cont = 0;
          if (strlen(a[i]) == maxLength) break;
        }
      }
    }
  }
}
int wrap(char a[1000][1000], int *linii, char max_line_length[10]) {
  int i, j;
  char buff[1000 * 1000];
  int line_length = atoi(max_line_length);
  for (i = 0; i <= *linii; i++) {
    if (strlen(a[i]) > 1) {
      strcpy(a[i] + strlen(a[i]) - 1, a[i] + strlen(a[i]));
      strcat(buff, a[i]);
      if (strlen(a[i]) < line_length && a[i][strlen(a[i]) - 1] != ' ') {
        if (a[i][strlen(a[i])] != '\n' && a[i + 1][0] != '\n')
          strcat(buff, " ");
      }
    } else if (i == *linii) {
      strcat(buff, "\n");

    } else {
      strcat(buff, "\n");
      strcat(buff, "\n");
    }
  }
  char copy[1000 * 1000], *p;
  strcpy(copy, buff);
  int Max = 0;
  p = strtok(copy, " \n");
  while (p != NULL) {
    if (strlen(p) > Max) Max = strlen(p);
    p = strtok(NULL, " \n");
  }
  if (Max > line_length) return 0;
  int end = line_length;
  int start = 0;
  for (j = 0; j < strlen(buff); j++) {
    if (j == end) {
      if (buff[end] != ' ') {
        while (1) {
          end--;
          if (buff[end] == ' ') break;
        }
        buff[end] = '\n';
        start = end + 1;
        j = end + 1;
        end = start + line_length;
      } else {
        buff[end] = '\n';
        start = end + 1;
        j = end + 1;
        end = start + line_length;
      }
    }
    if (buff[j] == '\n' && buff[j + 1] == '\n') {
      start = j + 2;
      end = start + line_length;
    } else if (buff[j] == '\n') {
      start = j + 1;
      end = start + line_length;
    }
  }
  for (i = 0; i < strlen(buff); i++)
    if (buff[i] == '\n' && buff[i + 1] == ' ')
      memmove(&buff[i + 1], &buff[i + 2], strlen(buff) - i);
  for (i = 0; i < *linii; i++) memset(&a[i][0], 0, sizeof(a[i]));
  i = 0;
  int k = 0;
  for (j = 0; j < strlen(buff); j++) {
    if (buff[j] != '\n') {
      a[i][k++] = buff[j];

    } else {
      strcat(a[i], "\n");
      i++;

      k = 0;
    }
  }

  *linii = i;
  deleteTrailingSpaces(a[*linii - 1]);
  return 1;
}
int main(int argc, char *argv[]) {
  char buf[1000],               // buffer used for reading from the file
      original[1000][1000],     // original text, line by line
      result[1000][1000];       // text obtained after applying operations
                                // char cmd[1000];
  int original_line_count = 0,  // number of lines in the input file
      result_line_count = 0,    // number of lines in the output file
      i;

  if (argc != 4) {  // invalid number of arguments
    fprintf(stderr, "Usage: %s operations_string input_file output_file\n",
            argv[0]);
    return -1;
  }

  // Open input file for reading
  FILE *input_file = fopen(argv[2], "r");

  if (input_file == NULL) {
    fprintf(stderr, "File \"%s\" not found\n", argv[2]);
    return -2;
  }

  // Read data in file line by line
  while (fgets(buf, 1000, input_file)) {
    strcpy(original[original_line_count], buf);
    original_line_count++;
  }

  fclose(input_file);
  char copieOriginal[1000][1000];
  for (i = 0; i < original_line_count; i++)
    strcpy(copieOriginal[i], original[i]);
  int copieOriginal_line_count = original_line_count;
  char *p;
  char matrice[1000][1000];
  int m = 0, n = 0;
  p = strtok(argv[1], ",");
  int cont = 0;
  int *val, cont_comenzi = 0;
  val = &original_line_count;
  while (p != NULL) {
    cont_comenzi++;
    for (i = 0; i < strlen(p); i++) {
      if (*(p + i) != ' ') {
        matrice[m][n++] = *(p + i);
        if (*(p + i + 1) == ' ' || *(p + i + 1) == '\0') {
          matrice[m][n] = '\0';
          m++;
          n = 0;
        }
      }
    }
    int commandType = matrice[0][0];
    int ok;
    switch (commandType) {
      case 'L':
        if (matrice[1] > matrice[2]) {
          printf("Invalid operation!\n");
          for (i = 0; i < copieOriginal_line_count; i++)
            strcpy(result[i], copieOriginal[i]);
          result_line_count = copieOriginal_line_count;
          break;
        }
        alignLeft(original, original_line_count, matrice[1], matrice[2]);
        cont++;
        break;
      case 'l':
        if (matrice[1] > matrice[2]) {
          for (i = 0; i < copieOriginal_line_count; i++)
            strcpy(result[i], copieOriginal[i]);
          result_line_count = copieOriginal_line_count;
          printf("Invalid operation!\n");
          break;
        }
        alignLeft(original, original_line_count, matrice[1], matrice[2]);
        cont++;
        break;
      case 'R':
        if (matrice[1] > matrice[2]) {
          for (i = 0; i < copieOriginal_line_count; i++)
            strcpy(result[i], copieOriginal[i]);
          result_line_count = copieOriginal_line_count;
          printf("Invalid operation!\n");
          break;
        }
        alignRight(original, original_line_count, matrice[1], matrice[2]);
        cont++;
        break;
      case 'r':
        if (matrice[1] > matrice[2]) {
          for (i = 0; i < copieOriginal_line_count; i++)
            strcpy(result[i], copieOriginal[i]);
          result_line_count = copieOriginal_line_count;
          printf("Invalid operation!\n");
          break;
        }
        alignRight(original, original_line_count, matrice[1], matrice[2]);
        cont++;
        break;
      case 'C':
        if (matrice[1] > matrice[2]) {
          for (i = 0; i < copieOriginal_line_count; i++)
            strcpy(result[i], copieOriginal[i]);
          result_line_count = copieOriginal_line_count;
          printf("Invalid operation!\n");
          break;
        }
        center(original, original_line_count, matrice[1], matrice[2]);
        cont++;
        break;
      case 'c':
        if (matrice[1] > matrice[2]) {
          for (i = 0; i < copieOriginal_line_count; i++)
            strcpy(result[i], copieOriginal[i]);
          result_line_count = copieOriginal_line_count;
          printf("Invalid operation!\n");
          break;
        }
        center(original, original_line_count, matrice[1], matrice[2]);
        cont++;
        break;
      case 'I':
      	if (matrice[3] > matrice[4]) {
          for (i = 0; i < copieOriginal_line_count; i++)
            strcpy(result[i], copieOriginal[i]);
          result_line_count = copieOriginal_line_count;
          printf("Invalid operation!\n");
          break;
        }
        list(original, original_line_count, matrice[1], matrice[2], matrice[3],
             matrice[4]);
        cont++;
        break;
      case 'O':
      	if (matrice[4] > matrice[5]) {
          for (i = 0; i < copieOriginal_line_count; i++)
            strcpy(result[i], copieOriginal[i]);
          result_line_count = copieOriginal_line_count;
          printf("Invalid operation!\n");
          break;
        }
        orderedList(original, original_line_count, matrice[1], matrice[2],
                    matrice[3], matrice[4], matrice[5]);
        cont++;
        break;
      case 'P':
      	if (matrice[2] > matrice[3]) {
          for (i = 0; i < copieOriginal_line_count; i++)
            strcpy(result[i], copieOriginal[i]);
          result_line_count = copieOriginal_line_count;
          printf("Invalid operation!\n");
          break;
        }
        paragraphs(original, original_line_count, matrice[1], matrice[2],
                   matrice[3]);
        cont++;
        break;
      case 'W':

        if (strlen(matrice[2]) != 0) {
          for (i = 0; i < copieOriginal_line_count; i++)
            strcpy(result[i], copieOriginal[i]);
          result_line_count = copieOriginal_line_count;
          printf("Invalid operation!\n");
          break;
        }
        ok = wrap(original, val, matrice[1]);
        if (ok == 0) {
          for (i = 0; i < copieOriginal_line_count; i++) {
            strcpy(result[i], copieOriginal[i]);
          }
          result_line_count = copieOriginal_line_count;

          printf("Cannot wrap!\n");
          break;
        }
        cont++;
        break;
      case 'w':
        
        if (strlen(matrice[2]) != 0) {
          for (i = 0; i < copieOriginal_line_count; i++)
            strcpy(result[i], copieOriginal[i]);
          result_line_count = copieOriginal_line_count;
          printf("Invalid operation!\n");
          break;
        }
        ok = wrap(original, val, matrice[1]);
        if (ok == 0) {
          for (i = 0; i < copieOriginal_line_count; i++) {
            strcpy(result[i], copieOriginal[i]);
          }
          result_line_count = copieOriginal_line_count;

          printf("Cannot wrap!\n");
          break;
        }
        cont++;
        break;
      case 'J':
      	if (matrice[1] > matrice[2]) {
          for (i = 0; i < copieOriginal_line_count; i++)
            strcpy(result[i], copieOriginal[i]);
          result_line_count = copieOriginal_line_count;
          printf("Invalid operation!\n");
          break;
        }
        alignLeft(original, original_line_count, matrice[1], matrice[2]);
        justify(original, original_line_count, matrice[1], matrice[2]);
        cont++;
        break;
      default:
        printf("Invalid operation!\n");
        break;
    }
    if (cont == 10)
      printf("Too many operations! Only the first 10 will be applied.\n");
    p = strtok(NULL, ",");

    m = 0;
    n = 0;
  }
  if (cont_comenzi == cont)
    for (i = 0; i < original_line_count; i++) {
      strcpy(result[i], original[i]);
    }

  result_line_count = original_line_count;

  // Open output file for writing
  FILE *output_file = fopen(argv[3], "w");

  if (output_file == NULL) {
    fprintf(stderr, "Could not open or create file \"%s\"\n", argv[3]);
    return -2;
  }

  // Write result in output file
  for (i = 0; i < result_line_count; i++) {
    fputs(result[i], output_file);
  }
  fclose(output_file);
}