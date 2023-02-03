
/*

int compare_rows(const void * a, const void * b)
{
    int * row_a = (int * )a;
    int * row_b = (int * )b;
    if (row_a[1] < row_b[1])
        return 1;
    else if (row_a[1] > row_b[1])
        return -1;
    else
        return 0;
} 


void TriDecroissantHumidite(char  * fichier_entree, char * fichier_sortie)
{
    char line[62];
    float data[62][4];
    int row = 0;
    int col = 0;
    FILE * fichier = fopen(fichier_entree, "r");
    while (fgets(line, sizeof(line), fichier) != NULL)
    {
        char * token = strtok(line, ";");
        col = 0;
        while (token)
        {
            data[row][col] = atof(token);
            token = strtok(NULL, ";");
            col++;
        }
        row++;
    }
    fclose(fichier);
    qsort(data, row, sizeof(float[4]), compare_rows);
    FILE fichier2 = fopen(fichier_sortie, "w");
    for (int i = 0; i < row; i++)
    {
        fprintf(fichier2, "%.0f;%.0f;%f;%f\n", data[i][0], data[i][1], data[i][2], data[i][3]);
    }
    fclose(fichier2);
} 
char lines[MAX_LOCATIONS][MAX_LINE_LENGTH];
int numLines = 0;

void addLine(charline) {
  strncpy(lines[numLines], line, MAX_LINE_LENGTH);
  numLines++;
}

int findLine(char line) {
  for (int i = 0; i < numLines; i++) {
    if (strcmp(lines[i], line) == 0) {
      return i;
    }
  }
  return -1;
}

void readLines() {
  char line[MAX_LINE_LENGTH];
  FILEfile = fopen("sortie.txt", "r");
  while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
    int index = findLine(line);
    if (index == -1) {
      addLine(line);
    }
  }
  fclose(file);
}

void writeLines() {
  FILE *file = fopen("test.txt", "w");
  for (int i = 0; i < numLines; i++) {
    fprintf(file, "%s", lines[i]);
  }
  fclose(file);
}

int lines() {
  readLines();
  writeLines();
  TriDecroissantHumidite("test.txt","test.txt");
  return 0;
}





char lines[MAX_LOCATIONS][MAX_LINE_LENGTH];
int numLines = 0;

void addLine(char line) {
  strncpy(lines[numLines], line, MAX_LINE_LENGTH);
  numLines++;
}

int findLine(charline) {
  for (int i = 0; i < numLines; i++) {
    if (strcmp(lines[i], line) == 0) {
      return i;
    }
  }
  return -1;
}

void readLines() {
  char line[MAX_LINE_LENGTH];
  FILE file = fopen("altitude.txt", "r");
  while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
    int index = findLine(line);
    if (index == -1) {
      addLine(line);
    }
  }
  fclose(file);
}

void writeLines() {
  FILEfile = fopen("sortie.txt", "w");
  for (int i = 0; i < numLines; i++) {
    fprintf(file, "%s", lines[i]);
  }
  fclose(file);
}

int main() {
  readLines();
  writeLines();
  return 0;
}




typedef struct {
    int id;
    float temp;
} Record;

int compare(const void a, const voidb) {
    Record r1 = (Record) a;
    Record r2 = (Record) b;
    return r1->id - r2->id;
}

void tri_tab_altitude(char* entree, char* sortie) {
    Record records[N];
    int count = 0;
    FILE fp = fopen(entree, "r");
    if (fp == NULL) {
        printf("ouverture du fichier impossible\n");
        return 1;
    }
    while (fscanf(fp, "%d;%f", &records[count].id, &records[count].temp) == 2) {
        count++;
    }
    fclose(fp);

    qsort(records, count, sizeof(Record), compare);

    int id = records[0].id;
    float somme = 0, min = records[0].temp, max = records[0].temp;
    int id_count = 0;
    FILEfpo = fopen(sortie, "w");
    if (fpo == NULL) {
        printf("Can't open sortie.txt\n");
        return 1;
    }
    for (int i = 0; i < count; i++) {
        if (records[i].id != id) {
            fprintf(fpo, "%d;%.6f;%.6f;%.6f\n", id, somme / id_count, min, max);
            id = records[i].id;
            somme = records[i].temp;
            min = records[i].temp;
            max = records[i].temp;
            id_count = 1;
        } else {
            somme += records[i].temp;
            if (records[i].temp < min) {
                min = records[i].temp;
            }
            if (records[i].temp > max) {
                max = records[i].temp;
            }
            id_count++;
        }
    }
    fprintf(fpo, "%d;%.6f;%.6f;%.6f\n", id, somme / id_count, min, max);
    fclose(fpo);

    return 0;
}


*/
