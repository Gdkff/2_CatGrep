#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct flag_s {
  char ignore_register_i;
  char invert_search_v;
  char number_of_string_c;
  char number_of_line_n;
  char string_without_names_h;
  char no_error_message_s;
  char print_only_coincidence_o;
  char flag_ef;
  char only_files_l;
} Flags;

// передается файл с текущей позицией курсора
// циклом проходится до переноса строки или конца файла
// возвращает курсор в первоначальную позицию
// возвращает количество символов в текущей строке
unsigned long size_of_line(FILE *file) {
  int currsor_position_start = ftell(file);
  char c;
  unsigned long size = 0;
  while (1) {
    c = fgetc(file);
    if (c == '\n') break;
    if (c == EOF) {
      size++;
      break;
    }
  }
  size = size + ftell(file) - currsor_position_start;
  fseek(file, currsor_position_start, SEEK_SET);
  return size - 1;
}

int add_flag_to_struct(Flags *struct_flags, char *flag) {
  int ret = 0;
  // проходим циклом по флагу со второго символа, вносим флаг в структуру
  for (int i = 1; i < (int)strlen(flag); i++) {
    switch (flag[i]) {
      case 'i':
        struct_flags->ignore_register_i = 'i';
        break;
      case 'v':
        struct_flags->invert_search_v = 'v';
        break;
      case 'c':
        struct_flags->number_of_string_c = 'c';
        break;
      case 'n':
        struct_flags->number_of_line_n = 'n';
        break;
      case 'h':
        struct_flags->string_without_names_h = 'h';
        break;
      case 's':
        struct_flags->no_error_message_s = 's';
        break;
      case 'o':
        struct_flags->print_only_coincidence_o = 'o';
        break;
      case 'e':
        struct_flags->flag_ef = '1';
        break;
      case 'f':
        struct_flags->flag_ef = '1';
        break;
      case 'l':
        struct_flags->only_files_l = 'l';
        break;
      default:
        ret = 1;
        break;
    }
  }
  return ret;
}

void null_struct(Flags *struct_flags) {
  struct_flags->ignore_register_i = '0';
  struct_flags->invert_search_v = '0';
  struct_flags->number_of_string_c = '0';
  struct_flags->number_of_line_n = '0';
  struct_flags->string_without_names_h = '0';
  struct_flags->no_error_message_s = '0';
  struct_flags->print_only_coincidence_o = '0';
  struct_flags->flag_ef = '0';
  struct_flags->only_files_l = '0';
}

void free_arrays(char **array_patterns, char **array_file) {
  int i = 0;
  while (array_patterns[i] != NULL) {
    free(array_patterns[i]);
    i++;
  }
  i = 0;
  while (array_file[i] != NULL) {
    free(array_file[i]);
    i++;
  }
}

int find_pattern(int argc, char **argv, char *pattern, char **array_pattern,
                 Flags *struct_flags) {
  char *pattern_flag = "^-";  //  pattern для поиска флагов
  // паттерны для поиска флагов f и e
  char *pattern_e = "^-.*[f]";
  char *pattern_f = "^-.*[e]";
  regex_t preg;
  regex_t preg_e;
  regex_t preg_f;

  regcomp(&preg, pattern_flag, REG_EXTENDED);
  regcomp(&preg_e, pattern_e, REG_EXTENDED);
  regcomp(&preg_f, pattern_f, REG_EXTENDED);

  regmatch_t pm;

  int error_code = 0;
  int flag_is_pattern = 0;  // Говорит, что есть шаблон.
  FILE *pattern_file;
  int count_pattern = 0;
  for (int i = 1; i < argc; i++) {
    // если в аргументе есть флаг e или f
    if ((regexec(&preg_e, argv[i], 0, &pm, 0) == 0) ||
        (regexec(&preg_f, argv[i], 0, &pm, 0) == 0)) {
      // если флаги в последнем аргументе - ошибка
      if (i == argc - 1) {
        error_code = -1;
        break;
      }
      count_pattern++;

      if (argv[i + 1] != NULL) {
        if ((regexec(&preg, argv[i], 0, &pm, 0) != 0)) {
          error_code = -1;
          break;
        }
        // если текущий флаг - е,
        if (strchr(argv[i], 'e')) {
          // копируем содержимое следующего аргумента в паттерн
          strcpy(pattern, argv[i + 1]);
          // выделяем память и заносим указатель в массив указателей на паттерны
          array_pattern[flag_is_pattern] =
              malloc(sizeof(char) * (strlen(argv[i + 1]) + 1));
          // проверка на выделение памяти маллоком
          if (array_pattern[flag_is_pattern] == NULL) {
            exit(1);
          }
          // в выделенную память заносим паттерн
          strcpy((array_pattern)[flag_is_pattern], argv[i + 1]);
          flag_is_pattern++;  // инкременируем счетчик паттернов

          // если текущий флаг f
        } else if (strchr(argv[i], 'f')) {
          // открываем файл по адресу из следующего аргумента
          pattern_file = fopen(argv[i + 1], "r");
          // проверка на открытие файла
          if (pattern_file == NULL) {
            error_code = 2;
            // если нет флага s, выводим сообщение об ошибке
            if (struct_flags->no_error_message_s != 's') {
              printf("grep: %s: %s\n", argv[i + 1], strerror(2));
            }
            break;
          }
          // в цикле забираем строки из файла
          while (fgets(pattern, 1024, pattern_file) != NULL) {
            // пропускаем пустые строки
            if (pattern[0] != '\n') {
              // в конце строки убираем перенос строки
              if (pattern[strlen(pattern) - 1] == '\n') {
                pattern[strlen(pattern) - 1] = '\0';
              }
              // выделяем память и заносим указатель в массив указателей на
              // паттерны
              array_pattern[flag_is_pattern] =
                  malloc(sizeof(char) * (strlen(pattern) + 1));
              if (array_pattern[flag_is_pattern] == NULL) {
                exit(1);
              }
              // в выделенную память заносим паттерн
              strcpy(array_pattern[flag_is_pattern], pattern);
              flag_is_pattern++;  // инкременируем счетчик паттернов
            }
          }
          fclose(pattern_file);
        }
        // если следующий аргумент NULL
      } else {
        if (struct_flags->no_error_message_s != 's') {
          printf("File pattern not found\n");
        }
        break;
      }
      // если аргумент не флаг и до этого паттерны не были найдены и нет флага e
      // или f и это не последний аргумент, заносим аргумент как одиночный
      // паттерн
    } else if ((regexec(&preg, argv[i], 0, &pm, 0) != 0) &&
               flag_is_pattern == 0 && struct_flags->flag_ef != '1' &&
               i != (argc - 1)) {
      array_pattern[flag_is_pattern] =
          malloc(sizeof(char) * (strlen(argv[i + 1]) + 1024));
      if (array_pattern[flag_is_pattern] == NULL) {
        exit(1);  // ВЫХОД ЕСЛИ ВДРУГ ОШИБКА МАллока2
      }
      strcpy(array_pattern[flag_is_pattern], argv[i]);
      flag_is_pattern++;
    }
  }
  if (flag_is_pattern == 0) {  // Паттерн не найден. Выход из программы
    error_code = -1;
  }
  regfree(&preg);
  regfree(&preg_e);
  regfree(&preg_f);
  return error_code;
}

int find_files(int argc, char **argv, char **array_file, Flags *struct_flags) {
  char pattern_flag[] = "^-";
  regex_t preg;  // структура с шаблоном
  regcomp(&preg, pattern_flag, REG_EXTENDED);  // Добавляем структуру в шаблон
  regmatch_t pm;
  int code_error = 0;
  int count_array = 0;
  int k = 2;  // начало цикла прохода по аргументам
  if (struct_flags->flag_ef == '1') {
    k = 1;
  }
  for (int i = k; i < argc; i++) {
    // если текущий аргумент не флаг и предыдущий аргумент не -е и не -f и
    // предыдущий аргумент вообще не флаг, считаем аргумент путем к целевому
    // файлу и заносим его в массив файлов
    if (regexec(&preg, argv[i], 0, &pm, 0) != 0 && strcmp(argv[i - 1], "-e") &&
        strcmp(argv[i - 1], "-f") &&
        !(regexec(&preg, argv[i - 1], 0, &pm, 0) == 0 && i == 2)) {
      array_file[count_array] = malloc(sizeof(char) * (strlen(argv[i]) + 1));
      if (array_file[count_array] == NULL) {
        exit(1);  // ВЫХОД ЕСЛИ ВДРУГ ОШИБКА МАллока
      }
      strcpy(array_file[count_array], argv[i]);
      count_array++;
    }
  }
  regfree(&preg);
  return code_error;
}

int what_regex_param(Flags struct_flags) {
  int param = 0;
  if (struct_flags.ignore_register_i == 'i') {
    param = 2;
  } else {
    param = 1;
  }
  return param;
}

int how_many_files(char **array_file) {
  int count = 0;
  while (array_file[count] != NULL) count++;
  return count;
}

//  печать имени файла и номера строки, учитывая флаги h и n
void print_format(char *file_name, char count_files, unsigned long num_string,
                  Flags struct_flags) {
  if (count_files > 1 && struct_flags.string_without_names_h != 'h') {
    if (struct_flags.number_of_line_n == 'n' && num_string != 0) {
      printf("%s:%lu:", file_name, num_string);
    } else {
      printf("%s:", file_name);
    }
  }
  if (count_files == 1 || struct_flags.string_without_names_h == 'h') {
    if (struct_flags.number_of_line_n == 'n' && num_string != 0) {
      printf("%lu:", num_string);
    }
  }
}

// печать при флаге -о
void printer(regex_t preg, char *line, char *file_name, char count_files,
             unsigned long num_string, Flags struct_flags) {
  char *line_file = line;
  regmatch_t pm;
  int regerr;
  while ((regerr = regexec(&preg, line_file, 1, &pm, 0)) == 0) {
    print_format(file_name, count_files, num_string, struct_flags);
    for (char *curr = (line_file + pm.rm_so); curr < line_file + pm.rm_eo;
         curr++) {
      putchar(*curr);
    }
    line_file = line_file + pm.rm_eo;
    printf("\n");
  }
}

//  проверяем есть ли паттерн(ы) в строке
char *is_pattern_in_string(char *line_file, char **array_patterns,
                           int regex_param, Flags struct_flags) {
  int i_pattern = 0;
  regex_t preg;
  int err_regcomp = 0, result_regcomp = 0;
  regmatch_t pm;
  char *finded_pattern = NULL;
  // перебираем паттерны в массиве
  while (array_patterns[i_pattern] != NULL) {
    // компилируем регулярное выражение
    err_regcomp = regcomp(&preg, array_patterns[i_pattern], regex_param);
    // при ошибке компиляции, выводим ошибку, переходим к следющему паттерну
    if (err_regcomp != 0) {
      if (struct_flags.no_error_message_s != 's') {
        printf("grep: Invalid pattern\n");
        regfree(&preg);
        i_pattern++;
        continue;
      }
    }

    result_regcomp = regexec(&preg, line_file, 1, &pm, 0);
    if (result_regcomp == 0) {
      finded_pattern = array_patterns[i_pattern];
    }
    regfree(&preg);
    i_pattern++;
  }
  return finded_pattern;
}

int searching_pattern_in_text(char **array_file, char **array_patterns,
                              Flags struct_flags) {
  FILE *file;
  regex_t preg;  //  структура с шаблоном
  // параметры регекса: 1 - нет флага i, 2 - есть флаг i
  int regex_param = what_regex_param(struct_flags);

  char str_to_counter_string[25] = {0};
  unsigned long counter_string = 0;
  unsigned long absolute_counter_string = 0;

  int count_files = how_many_files(array_file);
  int i_file = 0;
  int end_of_file_flag = 0;
  char c = '0';
  unsigned long counter_char = 1;
  int result_regcomp = 0;
  char *line_file = NULL;
  // проходим по файлам в массиве и открываем их
  while (array_file[i_file] != NULL) {
    if (array_file[i_file] != NULL) {
      file = fopen(array_file[i_file], "r");
    } else {
      break;
    }

    if (file == NULL) {  // обработка ошибки отсутствия файла
      if (struct_flags.no_error_message_s != 's') {
        printf("grep: %s: %s", array_file[i_file], strerror(2));
      }
      i_file++;
      continue;
    }
    end_of_file_flag = 0;         // символ флаг конца файла
    absolute_counter_string = 0;  // обнуляем счетчик строк
    while (1) {
      // малочим 1024 байт под строку
      line_file = calloc(counter_char + 1024, sizeof(char));
      if (line_file == NULL) {
        exit(1);  // ВЫХОД ЕСЛИ ВДРУГ ОШИБКА МАллока
      }
      // проходим посимвольно по файлу
      while ((c = getc(file)) != '\n') {
        // когда доходим до конца файла
        if (c == EOF) {
          line_file[counter_char - 1] = '\0';
          counter_char++;
          end_of_file_flag = 1;
          break;
        }
        counter_char++;
        // каждый раз реалочим на +1 память
        line_file = realloc(line_file, (sizeof(char) * counter_char + 1024));
        // записываем симвл в строку
        line_file[counter_char - 2] = c;
      }
      // если конец файла и пустая строка
      if (c == EOF && counter_char == 2) {
        counter_char = 1;
        free(line_file);
        line_file = NULL;
        break;
      }
      // увеличиваем абсолютный счетчик строк
      absolute_counter_string++;
      // зануляем строку
      line_file[counter_char - 1] = '\0';
      // проверяем совпадение паттерна(ов) в строке
      char *pattern = NULL;
      if (strchr(line_file, '\0') != NULL) {
        pattern = is_pattern_in_string(line_file, array_patterns, regex_param,
                                       struct_flags);
      }
      if (pattern != NULL) {
        // есть паттерн в строке
        result_regcomp = 0;
      } else {
        // нет паттерна в строке
        result_regcomp = 1;
      }
      // считаем количество строк с найденными паттернами
      if (result_regcomp == 0 && struct_flags.invert_search_v != 'v') {
        counter_string++;
      } else if (result_regcomp == 1 && struct_flags.invert_search_v == 'v') {
        counter_string++;  // Инвентируемый случай
      }

      if (pattern != NULL) {
        regcomp(&preg, pattern, regex_param);
      }

      ///  печать результата
      // если нет флагов с и l (вывода только количество строк и совпавшие
      // файлы)
      if (struct_flags.number_of_string_c != 'c' &&
          struct_flags.only_files_l != 'l') {
        // если есть совпадение и нет флага v (инверт смысла поиска)
        if (result_regcomp == 0 && struct_flags.invert_search_v != 'v') {
          // если флаг -о (печать совпавших с паттерном частей строки),
          // печатается последний совпавший паттерн
          if (struct_flags.print_only_coincidence_o == 'o') {
            printer(preg, line_file, array_file[i_file], count_files,
                    absolute_counter_string, struct_flags);
            // если нет флага -о
          } else {
            // печатаем при необходимости имя файла и номер строки
            print_format(array_file[i_file], count_files,
                         absolute_counter_string, struct_flags);
            // и выводим текущую строку
            printf("%s\n", line_file);
          }
          // если нет совпадений и есть флаг v (инверт смысла поиска)
        } else if (result_regcomp == 1 && struct_flags.invert_search_v == 'v') {
          // печатаем при необходимости имя файла и номер строки
          print_format(array_file[i_file], count_files, absolute_counter_string,
                       struct_flags);
          // и выводим текущую строку
          printf("%s\n", line_file);
        }
      }
      if (pattern != NULL) {
        regfree(&preg);
      }
      counter_char = 1;
      free(line_file);
      line_file = NULL;
      if (end_of_file_flag == 1) {
        break;  ///   Если конец файла, выходим из цикла.
      }
    }  //  Конец цикла для файла
    // если есть флаг -l (вывод только совпавших файлов)
    if (struct_flags.only_files_l == 'l') {
      // если количество строк больше 0, присваиваем значение 1
      if (counter_string > 0) {
        counter_string = 1;
      }
    }
    // если есть флаг -с (вывод количества совпавших строк)
    if (struct_flags.number_of_string_c == 'c') {
      sprintf(str_to_counter_string, "%lu", counter_string);
      print_format(array_file[i_file], count_files, 0, struct_flags);
      printf("%s\n", str_to_counter_string);
    }
    if (struct_flags.only_files_l == 'l' && counter_string > 0) {
      printf("%s\n", array_file[i_file]);
    }
    fclose(file);  //  закрываем файл перед открытием нового
    counter_string = 0;  //  обнуляем счетчик совпадающих строк
    i_file++;
  }
  return 0;
}

int main(int argc, char **argv) {
  char pattern[1000] = {0};
  char *array_patterns[1024] = {0};
  char *array_file[1024] = {0};
  int i = 1;
  char *flag = NULL;
  int error_code = 0;
  Flags struct_flags;
  // обнуляем структуру
  null_struct(&struct_flags);
  // проходим по аргументам (argv), если начинается с -, добавляем в флаги в
  // структуру
  while ((flag = argv[i++]) != NULL) {
    if (flag[0] == '-') {
      error_code = add_flag_to_struct(&struct_flags, flag);
      if (error_code == 1) {
        if (struct_flags.no_error_message_s == 's') {
          printf("grep: invalid option\n");
        }
      }
    }
  }
  // если нет ошибок, находим и заполняем паттерны
  if (error_code == 0) {
    error_code =
        find_pattern(argc, argv, pattern, array_patterns, &struct_flags);
  }
  // если нет ошибок, находим пути к целевым файлам и вносим указатели на строки
  // с путями к ним в массив указателей на файлы
  if (error_code == 0) {
    error_code = find_files(argc, argv, array_file, &struct_flags);
    // если нет ошибок ищем паттерны в тексте и делаем вывод в соответствии с
    // полученными настройками
    if (error_code == 0) {
      searching_pattern_in_text(array_file, array_patterns, struct_flags);
    }
  }
  free_arrays(array_patterns, array_file);
  return 0;
}
