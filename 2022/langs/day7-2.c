// -*- compile-command: "make d7" -*-
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define ll long long
#define maxN 256
const int SZ = 70000000;
const int NEED = 30000000;

struct Dir {
    ll sz;
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

ll update_sz(dir *d) {
    for (int i = 0; i < maxN && d->children[i]; ++i) {
        d->sz += update_sz(d->children[i]);
    }
    return d->sz;
}

void dfs(dir *d, int req, int *best, char **name) {
    if (d->sz < req) return;
    if (d->sz - req < *best - req) {
        *best = d->sz;
        *name = d->name;
    }
    for (int i = 0; i < maxN && d->children[i]; ++i) {
        dfs(d->children[i], req, best, name);
    }
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
    ll used = update_sz(&root),
      extra = SZ - used,
        req = NEED - extra;

    int best = SZ;
    char *name;
    dfs(&root, req, &best, &name);
    fprintf(stdout, "Part 2: %s = %d\n", name, best);
    return EXIT_SUCCESS;
}
