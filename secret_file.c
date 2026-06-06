#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define START_HOUR 9
#define END_HOUR 18
#define FILE_PATH "secret_file.txt"

int is_access_allowed() {
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    int current_hour = timeinfo->tm_hour;

    if (current_hour >= START_HOUR && current_hour < END_HOUR) {
        return 1;
    }
    return 0;
}

int main() {
    if (!is_access_allowed()) {
        fprintf(stderr, "[!] Помилка: Доступ до файлу дозволено лише у робочий час (з %02d:00 до %02d:00).\n", START_HOUR, END_HOUR);
        return EXIT_FAILURE;
    }

    printf("[+] Доступ дозволено. Читання файлу...\n");
    
    FILE *file = fopen(FILE_PATH, "r");
    if (!file) {
        perror("Не вдалося відкрити файл");
        return EXIT_FAILURE;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);

    return EXIT_SUCCESS;
}
