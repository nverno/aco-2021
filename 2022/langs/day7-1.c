// -*- compile-command: "make d7" -*-
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define maxN 256

struct Dir {
    int sz;
    char name[maxN];
    struct Dir *parent;
    struct Dir *children[maxN];
} root;
typedef struct Dir dir;

dir *cur = &root;

void add_subdir(char *line) {
    int i = 0;
    while (i < maxN && cur->children[i]) ++i;
    assert(i < maxN);
    dir *ch = cur->children[i] = (dir *)malloc(sizeof(dir));
    ch->sz = 0;
    ch->parent = cur;
    memset(ch->children, 0, sizeof(ch->children));
    strcpy(ch->name, line + 4);
    ch->name[strlen(ch->name) - 1] = '\0';
}

void cd(char *d) {
    if (strcmp("..", d) == 0) {
        assert(cur->parent);
        cur = cur->parent;
    } else {
        for (int i = 0; i < maxN; ++i) {
            dir *ch = cur->children[i];
            if (ch && strcmp(ch->name, d) == 0) {
                cur = ch;
                break;
            }
        }
    }
}

int dfs(dir *d, int *res) {
    int s = d->sz;
    for (int i = 0; i < maxN && d->children[i]; ++i) {
        s += dfs(d->children[i], res);
    }
    if (s <= 1e5) *res += s;
    return s;
}

void process_cmd(char *line) {
    if (line[2] == 'l') {
        // ignore
    } else {
        char d[maxN];
        strcpy(d, line + 5);
        d[strlen(d)-1] = '\0';
        cd(d);
    }
}

int main(int argc, char *argv[]) {
    char line[maxN];
    while (fgets(line, maxN, stdin)) {
        if (line[0] == '$') {
            process_cmd(line);
        } else {
            if (strncmp("dir", line, 3) == 0) {
                add_subdir(line);
            } else {
                int sz = 0;
                for (int i = 0; i < strlen(line); ++i) {
                    if (line[i] == ' ') break;
                    sz = 10*sz + (line[i] - '0');
                }
                cur->sz += sz;
            }
        }
    }

    int res = 0;
    dfs(&root, &res);
    fprintf(stdout, "Part 1: %d\n", res);
    return EXIT_SUCCESS;
}
