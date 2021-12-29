// -*- compile-command: "make d23" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

const array<int,4> moveCost = { 1, 10, 100, 1000 };
const int hallSz = 11, roomSz = 4;
const vector<int> roomLocs = {2, 4, 6, 8};
enum { EMPTY=-2, DOOR=-1, A=0, B, C, D };

vector<vector<int>> dist;
void init(int len) {
    vector<vector<int>> res;
    for (size_t i = 0; i < roomLocs.size(); ++i) {
        int r = roomLocs[i];
        vector<int> ds;
        for (int j = 0; j < len; ++j) {
            if (j == r) continue;
            ds.push_back(abs(r - j));
        }
        dist.push_back(ds);
    }
}

struct State {
    int cost;
    size_t rsz;
    vector<int> hall;
    vector<bool> roomDone;
    vector<vector<int>> rooms;
    State(int hsz, vector<vector<int>>& rs): cost(0), rooms(rs) {
        rsz = rs[0].size();
        hall.resize(hsz, EMPTY);
        for (auto& i : roomLocs) hall[i] = DOOR;
        roomDone.resize(rs.size(), false);
        for (int kind = 0; kind < (int)rooms.size(); ++kind) {
            bool ok = rooms[kind].size() == rsz;
            for (size_t i = 0; ok && i < rooms[kind].size(); ++i)
                ok = rooms[kind][i] == kind;
            roomDone[kind] = ok;
        }
    }
    int entrance(int r) const { return 2*r+2; }
    int toEntrance(int r) const { return 1 + rsz - rooms[r].size(); }
    int fromEntrance(int r) const { return rsz - rooms[r].size(); }
    bool done() const {
        for (auto r : roomDone) if (!r) return false;
        return true;
    }
    bool roomReady(int kind) const {
        if (rooms[kind].empty()) return true;
        for (auto& x : rooms[kind]) 
            if (x != kind) return false;
        return true;
    }
    int popRoom(int room, State& st) const {
        int kind = st.rooms[room].back();
        st.cost += toEntrance(room) * moveCost[kind];
        st.rooms[room].pop_back();
        return kind;
    }
    void pushRoom(int kind, State& st) const {
        st.cost += fromEntrance(kind) * moveCost[kind];
        st.rooms[kind].push_back(kind);
        st.roomDone[kind] = st.rooms[kind].size() == rsz;
    }
    bool hallToRoom(int pos, int kind, State& st) const {
        if (!roomReady(kind)) return false;
        int c = 0, goal = entrance(kind), dx = goal > pos ? 1 : -1;
        while (pos != goal) {
            pos += dx;
            if (!(st.hall[pos] == EMPTY || st.hall[pos] == DOOR)) return false;
            c += moveCost[kind];
        }
        assert(st.hall[pos] == DOOR && pos == entrance(kind));
        st.cost += c;
        pushRoom(kind, st);
        return true;
    }

    // move any amphipods from halls to their rooms if possible
    void addHallMoves(vector<State>& res) const {
        for (size_t i = 0; i < hall.size(); ++i) {
            if (hall[i] == DOOR || hall[i] == EMPTY || !roomReady(hall[i]))
                continue;
            State st(*this);
            if (hallToRoom(i, hall[i], st)) {
                st.hall[i] = EMPTY;
                res.push_back(st);
            }
        }
    }

    void waitInHall(size_t pos, int dx, int kind, State st, vector<State>& res) const {
        while (pos > 0 && pos+1 < st.hall.size()) {
            pos += dx;
            st.cost += moveCost[kind];
            if (st.hall[pos] == EMPTY) {
                st.hall[pos] = kind;
                res.push_back(st);
                st.hall[pos] = EMPTY;
            } else if (st.hall[pos] != DOOR) return;
        }
    }

    // move amphipods out of rooms into either their goal room or hallway
    void addRoomMoves(int r, vector<State>& res) const {
        if (rooms[r].empty() || roomDone[r] || roomReady(r)) return;
        State st(*this);
        int kind = popRoom(r, st),  // move to entrance
             pos = entrance(r);
        if (kind != r && hallToRoom(pos, kind, st)) {
            res.push_back(st);  // was able to move to goal room
        } else {                // otherwise, try waiting in hallway
            waitInHall(pos, -1, kind, st, res);
            waitInHall(pos, 1, kind, st, res);
        }
    }
    
    vector<State> neighbors() const {
        vector<State> res;
        addHallMoves(res);
        for (size_t r = 0; r < rooms.size(); ++r)
            addRoomMoves(r, res);
        return res;
    }

    char toChar(int v) const {
        return v == EMPTY || v == DOOR ? '.' : char('A' + v);
    }
    string rowString(size_t r) const {
        r = rsz - r - 1;
        string res;
        for (size_t i = 0; i < rooms.size(); ++i) {
            if (r >= rooms[i].size()) res += '.';
            else res += toChar(rooms[i][r]);
            if (i < rooms.size()-1) res += '#';
        }
        return res;
    }
    string hallString() const {
        string res;
        for (auto& x : hall) res += toChar(x);
        return res;
    }
};
ostream& operator<<(ostream& os, const State& st) {
    os << "cost: " << st.cost << "\n";
    string h = st.hallString();
    os << string(h.size()+2, '#') + "\n"
       << "#" << h << "#\n"
       << "###" << st.rowString(0) << "###\n";
    for (size_t i = 1; i < st.rsz; ++i)
        os << "  #" << st.rowString(i) << "#  \n";
    return os;
}
bool operator<(const State& a, const State& b) {
    return a.hall < b.hall || a.rooms < b.rooms;
}
map<State,int> memo;
int best = INT_MAX;
int dfs(State& st, int depth = 0) {
    if (st.cost > best) return memo[st] = INT_MAX;
    if (memo.count(st) && memo[st] < st.cost) return INT_MAX;
    memo[st] = st.cost;
    if (st.done()) {
        best = min(best, st.cost);
        cout << "moves=" << depth << "\n" << st << endl;
        return memo[st] = st.cost;
    }
    int res = INT_MAX;
    for (auto& neb : st.neighbors())
        if (neb.cost < best)
            res = min(res, dfs(neb, depth+1));
    if (res != INT_MAX) cout << st << endl;
    return res;
}
        
int main(int argc, char *argv[]) {
    string line;
    for (int i = 0; i < 2; ++i) getline(cin, line);
    init(hallSz);

    vector<vector<int>> pos(roomLocs.size(), vector<int>(roomSz));
    int rpos = 0;
    while (getline(cin, line)) {
        cout << line << endl;
        for (size_t i = 0; i < roomLocs.size(); ++i) {
            size_t j = roomLocs[i] + 1;
            if (isalpha(line[j]))
                pos[i][rpos] = line[j] - 'A';
        }
        ++rpos;
    }
    for (auto& r : pos) std::reverse(r.begin(), r.end());

    State st(hallSz, pos);
    (void)dfs(st);
    // 15338: 14 moves
    cout << best << endl;
    return 0;
}
