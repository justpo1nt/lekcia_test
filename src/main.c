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

int process_cmd(const user_t* user, const char* cmd) {
    if (strcmp(cmd, "door") == 0) {
        if (min_door_level > user->level) {
            printf("Nemas dostatocne prava\n");
            return 1;
        }

        if (door_state) {
            printf("Dvere otvorene\n");
        } else {
            printf("Dvere zatvorene\n");
        }
        door_state = !door_state;

        return 0;
    }

    if (strcmp(cmd, "help") == 0) {
        printf("exit - Zatvorit program\n");
        printf("door - Otvor dvere\n");

        return 0;
    }

    if (strcmp(cmd, "exit") == 0) {
        printf("exit");

        return 1;
    }
}

int main(int argc, const char** args) {
    const char name_buffer[32] = {0};
    const char pass_buffer[32] = {0};

    printf("Zadajte meno: ");
    scanf("%32[0-9a-zA-Z ]", name_buffer);
    printf("Zadajte heslo: ");
    scanf("%32[0-9a-zA-Z ]", pass_buffer);

    user_t* user = login(name_buffer, pass_buffer);

    if (user == NULL) {
        printf("Neznamy uzivatel\n");
        
        return 1;
    }

    printf("Vitaj %s, tvoj level je %d\n", user->username, user->level);

    const char command[128] = {0};
    while (1) {
        printf("> ");
        scanf("%128[0-9a-zA-Z ]", command);

        if(process_cmd(user, command)) {
            return 0;
        }
    }

    return 0;
}