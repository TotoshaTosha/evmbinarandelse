#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>

struct product {
    char name[40];
    int amount;
    char data[10];
    int best_before_in_days;
    float price;
};

int createfile(const char* filename) {
    FILE* bf;
    product a;
    if (fopen_s(&bf, filename, "wb+") != NULL)
        return 1;
    printf("Вводите данные!\n \"***\" - конец ввода\n");
    scanf_s("%s", a.name, 40);
    while (strcmp(a.name, "***")) {
        scanf_s("%d %s %d %f", a.amount, a.data, 10, a.best_before_in_days, a.price);
        fwrite(&a, sizeof(product), 1, bf);
        scanf_s("%s", a.name, 40);
    }
    fclose(bf);
    return 0;
}

int addToTheStart(const char* filename) {
    FILE* bf, *copyfile;
    const long int prodsize = sizeof(product);
    const char* copyname = "copy.txt";
    product a;
    if ((fopen_s(&bf, filename, "rb+") != NULL) && (fopen_s(&copyfile, copyname, "wb+" != NULL)))
        return 1;
    printf("Введите данные:\nНаименование\nКол-во\nДата поступления\nМаксимальный срок хранения в днях\nСтоимость\n");
    scanf_s("%s", a.name, 40);
    scanf_s("%d", &a.amount);
    scanf_s("%s", a.data, 10);
    scanf_s("%d", &a.best_before_in_days);
    scanf_s("%f", &a.price);
    fwrite(&a, prodsize, 1, copyfile);
    fseek(bf, 0, SEEK_SET);
    while (fread(&a, prodsize, 1, bf)) {
        fwrite(&a, prodsize, 1, copyfile);
    }
    fclose(bf);
    fclose(copyfile);
    remove(filename);
    rename(copyname, filename);
    return 0;
}

int addToTheEnd(const char* filename) {
    FILE* bf;
    const long int prodsize = sizeof(product);
    product a;

    if (fopen_s(&bf, filename, "rb+") != NULL)
        return 1;


    printf("Введите данные:\nНаименование\nКол-во\nДата поступления\nМаксимальный срок хранения в днях\nСтоимость\n");
    scanf_s("%s", a.name, 40);
    scanf_s("%d", &a.amount);
    scanf_s("%s", a.data, 10);
    scanf_s("%d", &a.best_before_in_days);
    scanf_s("%f", &a.price);
    fseek(bf, 0, SEEK_END);
    fwrite(&a, prodsize, 1, bf);
    fclose(bf);

    return 0;
}

int addToTheMid(const char* filename) {
    FILE* bf, *copyfile;
    long int length = 0;
    const long int prodsize = sizeof(product);
    const char* copyname = "copy.txt";
    product a;

    if ((fopen_s(&bf, filename, "rb+") != NULL) && (fopen_s(&copyfile, copyname, "wb+" != NULL)))
        return 1;
    
    fseek(bf, 0, SEEK_SET);
    while (fread(&a, prodsize, 1, bf)) {
        length++;
        fwrite(&a, prodsize, 1, copyfile);
    }


    printf("Введите данные:\nНаименование\nКол-во\nДата поступления\nМаксимальный срок хранения в днях\nСтоимость\n");
    scanf_s("%s", a.name, 40);
    scanf_s("%d", &a.amount);
    scanf_s("%s", a.data, 10);
    scanf_s("%d", &a.best_before_in_days);
    scanf_s("%f", &a.price);
    fseek(copyfile, length/2, SEEK_SET);
    fwrite(&a, prodsize, 1, copyfile);


    fseek(bf, length/2, SEEK_SET);
    while (fread(&a, prodsize, 1, bf)) {
        fwrite(&a, prodsize, 1, copyfile);
    }

    fclose(bf);
    fclose(copyfile);
    remove(filename);
    rename(copyname, filename);
    return 0;
}

int deleteRecord(const char* filename) {
    FILE* bf;
    product a;
    const long int prodsize = sizeof(product);

    if (fopen_s(&bf, filename, "rb+") != NULL)
        return 1;

    printf("Удалить по номеру|по информации? 1|2: ");
    char answ;
    scanf_s("%c", &answ);
    long corenum = -1L;
    if (c == '1') {
        int number;
        printf("Введите номер: ");
        scanf_s("%d", &number);
        fseek(bf, number - 1, SEEK_SET);
        corenum = ftell(bf);
    }
    else if (c == '2') {
        char findName[40];
        printf("Введите имя: ");
        scanf_s("%s", findname, 40);
        while(fread(&a, prodsize, 1, bf)) 
            if (!strcmp(findname, a.name))
                corenum = ftell(bf);
    }
    else return 2;
    if (corenum >= 0) {
        fseek(bf, 0, SEEK_END);
        long end = ftell(bf);
        while (corenum < end) {
            fseek(bf, corenum, SEEK_SET);
            if (fread(a, prodsize, 1, bf) != 1)
                break;
            fseek(bf, -2, SEEK_CUR);
            fwrite(&a, prodsize, 1, bf);
            corenum += prodsize;
        }
        memset(&a, 0, prodsize);
        fseek(bf, -1, SEEK_END);
        fwrite(&a, prodsize, 1, bf);
    }

    fclose(bf);
    return 0;
}

int changeRecord(const char* filename) {
    FILE* bf;
    product a;
    const long int prodsize = sizeof(product);

    if (fopen_s(&bf, filename, "rb+") != NULL)
        return 1;

    printf("Изменить по номеру|по информации? 1|2: ");
    char answ;
    scanf_s("%c", &answ);
    long corenum = -1L;
    if (c == '1') {
        int number;
        printf("Введите номер: ");
        scanf_s("%d", &number);
        fseek(bf, number - 1, SEEK_SET);
        corenum = ftell(bf);
    }
    else if (c == '2') {
        char findName[40];
        printf("Введите имя: ");
        scanf_s("%s", findname, 40);
        while(fread(&a, prodsize, 1, bf)) 
            if (!strcmp(findname, a.name))
                corenum = ftell(bf);
    }
    else return 2;
    if (corenum >= 0) {
        printf("Введите информацию:\n");
        scanf_s("%s%d%s%d%f", a.name, 40, a.amount, a.data, 10, a.best_before_in_days, a.price);
        fwrite(&a, prodsize, 1, bf);
    }
    fclose(bf);
    return 0;
}

int outOfDate (const char* filename) {
    FILE* bf;
    product a;
    const long int prodsize = sizeof(product);
    char* vvoddate[10];
    if (fopen_s(&bf, filename, "rb") != NULL)
        return 1;
    printf("Введите дату: ");
    scanf_s("%s", vvoddate, 10);
    while (fread(&a, prodsize, 1, bf)) {
        if (!strcmp(a.data, vvoddate)) {
            printf("%s %d %s %d %.5f\n", a.name, a.amount, a.data, a.best_before_in_days, a.price);
        }
    }
    fclose(bf);
    return 0;
}

int printFile (const char* filename) {
    FILE* bf;
    product a;
    const long int prodsize = sizeof(product);
    
    if (fopen_s(&bf, filename, "rb") != NULL)
        return 1;

    printf("Все товары: \n");
    while (fread(&a, prodsize, 1, bf)) 
            printf("%s %d %s %d %.5f\n", a.name, a.amount, a.data, a.best_before_in_days, a.price);       
    
    fclose(bf);
    return 0;
}
int main() {
    setlocale(LC_ALL, ".1251");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    printf("Выберите команду (1-9) из списка для выполнения:\n");
    bool menu = true;
    int choice;
    char filename[20];
    while (menu) {
        printf("1. Загрузить файл ( новый / существующий );\n");
        printf("2. Добавить запись в начало файла;\n");
        printf("3. Добавить запись в конец файла;\n");
        printf("4. Добавить запись в середину файла;\n");
        printf("5. Удалить запись ( по номеру / по информации );\n");
        printf("6. Изменить запись ( по номеру / по информации );\n");
        printf("7. Обработать файл;\n");
        printf("8. Печать файла;\n");
        printf("9. Выход.\n");
        scanf_s("%d", &choice);
        switch (choice) {
            case 1:
                char ch;
                printf("Создать новый файл или загрузить старый? 1|2: ");
                scanf_s("%c", &ch);
                printf("Введите имя файла: ");
                scanf_s("%s", filename, 20);
                if (ch == '1'); {
                    if (createfile(filename))
                        printf("Ошибка при создании файла!\nПопробуйте заново.\n");
                    else
                        printf("Файл успешно создан.\n");
                }
                break;
            case 2:
                if(addToTheStart(filename))
                    printf("Ошибка при  добавлении записи!\n");
                break;
            case 3:
                if(addToTheEnd(filename))
                    printf("Ошибка при  добавлении записи!\n");
                break;
            case 4:
                if(addToTheMid(filename))
                    printf("Ошибка при  добавлении записи!\n");
                break;
            case 5:
                int res = deleteRecord(filename);
                if(res == 1)
                    printf("Ошибка при  удалении записи!\n");
                else if (res == 2)
                    printf("Неправильно выбран тип удаления.\n");
                break;
            case 6:
                int res = changeRecord(filename);
                if(res == 1)
                    printf("Ошибка при  удалении записи!\n");
                else if (res == 2)
                    printf("Неправильно выбран тип удаления.\n");
                break;
            case 7:
                if (outOfDate(filename))
                    printf("Ошибка при обработке файла!\n");
                break;
            case 8:
                if (printFile(filename))
                    printf("Ошибка при печати файла!\n");
                break;
            case 9:
                printf("Выход!\n");
                menu = false;
            default:
                printf("Неправильная команда!");
                break;
        }
    }
}
