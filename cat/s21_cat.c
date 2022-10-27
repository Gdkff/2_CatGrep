#include <stdio.h>
#include <string.h>
#if defined(__APPLE__) || defined(__MACH__)
#define OS 'M'
#elif defined(__linux) || defined(__linux__)
#define OS 'L'
#endif

typedef struct cat_f {
  char b;
  char e;
  char n;
  char s;
  char t;
  char v;
  unsigned count_sqz;       // счетчик пустых строк
  unsigned long count_str;  // счетчик строк
  unsigned num_files;       // счетчик файлов
} cat_f;

void flags_null(cat_f *cat_flags) {
  cat_flags->b = '\0';
  cat_flags->e = '\0';
  cat_flags->n = '\0';
  cat_flags->s = '\0';
  cat_flags->t = '\0';
  cat_flags->v = '\0';
  cat_flags->count_sqz = 0;
  cat_flags->count_str = 0;
  cat_flags->num_files = 0;
}

void get_flags(int argc, char **argv, cat_f *cat_flags) {
  // перебор аргументов
  for (int i = 1; i < argc; i++) {
    // если аргумент флаг (начинается с -)
    if (argv[i][0] == '-') {
      // при совпадении флага, включаем флаг(и) в структуре
      if (!strcmp(argv[i], "-b") || !strcmp(argv[i], "--number-nonblank")) {
        cat_flags->b = 'b';
      } else if (!strcmp(argv[i], "-e")) {
        cat_flags->e = 'e';
        cat_flags->v = 'v';
      } else if (!strcmp(argv[i], "-E")) {
        cat_flags->e = 'e';
      } else if (!strcmp(argv[i], "-n") || !strcmp(argv[i], "--number")) {
        cat_flags->n = 'n';
      } else if (!strcmp(argv[i], "-s") ||
                 !strcmp(argv[i], "--squeeze-blank")) {
        cat_flags->s = 's';
      } else if (!strcmp(argv[i], "-t")) {
        cat_flags->t = 't';
        cat_flags->v = 'v';
      } else if (!strcmp(argv[i], "-T")) {
        cat_flags->t = 't';
      } else if (!strcmp(argv[i], "-v")) {
        cat_flags->v = 'v';
      } else if (!strcmp(argv[i], "--")) {
        argv[i] = 0;
        break;
      }
      // после записи флага в структуру, обнуляем указатель на аргумент (не
      // обнуленные останутся файлы)
      argv[i] = 0;
    }
  }
  // приоритет у флага b
  if (cat_flags->b && cat_flags->n) {
    cat_flags->n = 0;
  }
  // считаем количество файлов
  for (int i = 1; i < argc; i++) {
    if (argv[i]) {
      cat_flags->num_files++;
    }
  }
}

void char_processing(char c, cat_f *cat_flags) {
  unsigned char c_now = (unsigned char)c;
  // если флаг -е и текущий символ - перенос строки, печатем дополнительно $
  if (cat_flags->e == 'e' && c_now == '\n') {
    putchar('$');
    // если флаг -t и текущий символ - таб, печатем дополнительно ^, а потом
    // допечатаем I
  } else if (cat_flags->t == 't' && c_now == '\t') {
    putchar('^');
    c_now = 'I';
    // если флаг -v, в зависимости от текущего символа заменяем его
  } else if (cat_flags->v == 'v') {
    if (c_now < 32 && c_now != 9 && c_now != 10) {
      putchar('^');
      c_now += 64;
    } else if (c_now == 127) {
      putchar('^');
      c_now = '?';
    } else if (c_now > 127 && c_now < 160) {
      printf("M-^");
      c_now -= 64;
    } else if (c_now > 159 && c_now < 255) {
      printf("M-");
      c_now -= 128;
    } else if (c_now == 255) {
      printf("M-^");
      c_now = '?';
    }
  }
  putchar(c_now);
}

void stream_processing(FILE *stream, cat_f *cat_flags) {
  char c_now = '\n';
  char c_before = '\n';
  fseek(stream, 0, SEEK_END);
  // находим количество знаков в файле, если поток stdin, значение 1
  unsigned long end_of_file = stream == stdin ? 1 : ftell(stream);
  fseek(stream, 0, SEEK_SET);
  // идем посимвольно по файлу
  for (unsigned long i = 0; i < end_of_file; i++) {
    c_before = c_now;
    c_now = getc(stream);
    // если поток stdin, постоянно увеличиваем переменную количества знаков в
    // файле, до получения из stdin конца файла
    if (stream == stdin && c_now != EOF) {
      end_of_file++;
    } else if (stream == stdin && c_now == EOF) {
      break;
    }
    // если есть флаг -s, и подряд идут 2 переноса строки
    if (cat_flags->s == 's' && c_now == '\n' && c_before == '\n') {
      // после второй пустой строки пропускает печать строки в цикле
      if (cat_flags->count_sqz++ >= 1) {
        continue;
      }
    }
    // если флаг -b (нумерация только непустых строк) и текущий символ - не
    // перенос строки, а предыдущий - перенос, печатаем номер строки (исключаем
    // пустые строки)
    if (cat_flags->b == 'b' && c_now != '\n' && c_before == '\n') {
      printf("%6lu\t", ++cat_flags->count_str);
      // если есть флаг -n (нумерация всех строк) и предыдущий знак - перенос
      // строки, печатаем номер строки
    } else if (cat_flags->n == 'n' && c_before == '\n') {
      printf("%6lu\t", ++cat_flags->count_str);
    }
    // выводим текущий символ в соответствием с флагами
    char_processing(c_now, cat_flags);
    // когда заканчиваются пустые строки, обнуляем счетчик
    if (cat_flags->s == 's' && c_now != '\n' && c_before == '\n') {
      cat_flags->count_sqz = 0;
    }
  }
  // на маке нумерация строк идет в рамках одного файла, на линуксе сквозная
  // нумерация по всем файлам
  if (OS == 'M') {
    cat_flags->count_str = 0;
  }
}

void processing(int argc, char **argv, cat_f *cat_flags) {
  FILE *stream;
  // если не найдены пути к файлам, забираем ввод в stdin
  if (!cat_flags->num_files) {
    stream_processing(stdin, cat_flags);
    // если есть файлы
  } else {
    // перебираем оставшиеся аргументы (пути к файлам), открываем файлы по
    // порядку
    for (int i = 1; i < argc; i++) {
      if (argv[i]) {
        stream = fopen(argv[i], "r");
        if (stream == 0) {
          fprintf(stderr, "s21_cat: %s: No such file or directory\n", argv[i]);
          continue;
        }
        stream_processing(stream, cat_flags);
        fclose(stream);
      }
    }
  }
}

int main(int argc, char **argv) {
  cat_f cat_flags;
  flags_null(&cat_flags);
  // получение флагов из аргументов, заполнение структуры
  get_flags(argc, argv, &cat_flags);
  // вывод результата
  processing(argc, argv, &cat_flags);
}
