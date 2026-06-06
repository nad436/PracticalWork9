#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define START_HOUR 7
#define END_HOUR 9
#define FILE_PATH "secret_file.txt"

int main() {
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    int current_hour = timeinfo->tm_hour;

    printf("[*] Поточний час системи: %02d:%02d\n", current_hour, timeinfo->tm_min);

    if (current_hour < START_HOUR || current_hour >= END_HOUR) {
        fprintf(stderr, "[!] ДОСТУП ЗАБОРОНЕНО: Читання дозволено тільки з %02d:00 до %02d:00.\n", START_HOUR, END_HOUR);
        return EXIT_FAILURE;
    }

    printf("[+] ДОСТУП ДОЗВОЛЕНО! Читання файлу:\n\n");
    
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
    printf("\n");

    return EXIT_SUCCESS;
}
