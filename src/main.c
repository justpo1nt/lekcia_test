#include <stdio.h>
#include <string.h>

typedef struct user_t {
    const char* username;
    const char* password;
    int level;
} user_t;

user_t users[] = {
    {
        .username = "po1nt",
        .password = "buffer",
        .level = 10
    },
    {
        .username = "jozko",
        .password = "mrkvicka",
        .level = 2
    },
    {
        .username = 0
    }
};

user_t* login(const char* username, const char* password) {
    size_t i = 0;

    while (users[i].username != 0) {
        if (strcmp(users[i].username, username) != 0) {
            i++;
            continue;
        }

        if (strcmp(users[i].password, password) != 0) {
            i++;
            continue;
        }

        return &users[i];
    }

    return NULL;
}

int min_door_level = 3;
int door_state = 0;

void process_cmd(const user_t* user, const char* cmd) {
    if (strcmp(cmd, "door") == 0) {
        if (min_door_level > user->level) {
            printf("Nemas dostatocne prava\n");
            return;
        }

        if (door_state) {
            printf("Dvere otvorene\n");
        } else {
            printf("Dvere zatvorene\n");
        }
        door_state = !door_state;
    }
    if (strcmp(cmd, "help") == 0) {
        printf("exit - Zatvorit program\n");
        printf("door - Otvor dvere\n");
    }
}

int main(int argc, const char** args) {
    const char name_buffer[32] = {0};
    const char pass_buffer[32] = {0};

    printf("Zadajte meno: ");
    scanf("%s", name_buffer);
    printf("Zadajte heslo: ");
    scanf("%32s", pass_buffer);

    user_t* user = login(name_buffer, pass_buffer);

    if (user == NULL) {
        printf("Neznamy uzivatel\n");
        
        return 1;
    }

    printf("Vitaj %s, tvoj level je %d\n", user->username, user->level);

    const char command[128] = {0};
    while (strcmp(command, "exit") != 0) {
        printf("> ");
        scanf("%128s", command);
        process_cmd(user, command);
    }

    return 0;
}