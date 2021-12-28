// -*- compile-command: "make d23" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

const array<int,4> moveCost = { 1, 10, 100, 1000 };
const int hallSz = 11, roomSz = 2;
const vector<int> roomLocs = {2, 4, 6, 8};
enum { EMPTY=-1, A, B, C, D };

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
    int cost, rsz;
    vector<int> hall;
    vector<bool> roomDone;
    vector<vector<int>> rooms;
    State(int hsz, vector<vector<int>>& rs): cost(0), rooms(rs) {
        hall.resize(hsz, EMPTY);
        rsz = rs[0].size();
        roomDone.resize(rs.size(), false);
        for (int kind = 0; kind < (int)rooms.size(); ++kind) {
            bool ok = true;
            for (size_t i = 0; ok && i < rooms[kind].size(); ++i)
                ok = rooms[kind][i] == kind;
            roomDone[kind] = ok;
        }
    }
    bool roomReady(int kind) { return room[kind].empty() || room[kind].back() == kind; }

    int moveFromHall(int beg, State& st) {
        int pos = beg, kind = hall[pos];
        if (!roomReady(kind)) return INT_MAX;
        int res = 0, goal = 2 + kind, dx = goal > pos ? 1 : -1;
        if (goal > pos) goal--;
        while (pos != goal) {
            pos += dx;
            if (hall[pos] != EMPTY) return INT_MAX;
            res++;
        }
        res += 1 + rsz - rooms[kind].size();
        st.hall[beg] = EMPTY;
        st.rooms[kind].push_back(kind);
        st.roomDone[kind] = st.rooms[kind].size() == rsz;
        st.cost += res * moveCost[kind];
        return res;
    }

    int moveFromRoom(int kind, State& st) {
        if (roomDone[kind]) return INT_MAX;
        int res = 1 + rsz - rooms[kind].size();
        
        swap(st.hall[pos], st.rooms[kind][ri-1]);
    }

    vector<State> hallMoves() {
        vector<State> res;
        for (size_t i = 0; i < hall.size(); ++i) {
            int kind = hall[i];
            if (kind == EMPTY || !roomReady[kind]) continue;
            State st(*this);
            if (moveFromHall(i, st) != INT_MAX)
                res.push_back(st);
        }
        return res;
    }

    void roomMoves(vector<State>& res) {
        for (int kind = 0; kind < (int)rooms.size(); ++kind) {
            if (roomDone[kind]) continue;
            int mv = 1 + rsz - rooms[kind].size();
            State st(*this);
            
        }
    }
    vector<State> neighbors() {
        vector<State> res = hallMoves();
        for (int kind = 0; kind < rooms.size(); ++kind) {
            if (roomDone[kind]) continue;
            int mv = 1 + rsz - rooms[kind].size();
            State st(*this);
            st.cost += mv * moveCost[kind];
            st.rooms[kind].pop_back();

            size_t pos = 2 + kind;
            while (pos < hall.size() && hall[pos] == EMPTY) {  // add right
                st.cost += moveCost[kind];
                st.hall[pos] = kind;
                res.push_back(st);
                st.hall[pos] = EMPTY;
                st.cost += moveCost[kind];
                pos++;
            }
            pos = 1 + kind;  // moving left
            
        }
        return res;
    }

    char toChar(int v) const { return v == EMPTY ? '.' : char('A' + v); }
    string rowString(size_t r) const {
        string res;
        for (size_t i = 0; i < rooms.size(); ++i) {
            res += toChar(rooms[i][r]);
            if (i < rooms.size()-1) res += '#';
        }
        return res;
    }
    string hallString() const {
        string res;
        for (size_t i = 0; i < 2; ++i) res += toChar(hall[i]);
        for (size_t i = 2, r = 0; r < rooms.size(); ++i, ++r) {
            res += '.';
            res += toChar(hall[i]);
        }
        res += toChar(hall.back());
        return res;
    }
};
ostream& operator<<(ostream& os, const State& st) {
    string h = st.hallString();
    os << string(h.size()+2, '#') + "\n"
       << "#" << h << "#\n"
       << "###" << st.rowString(0) << "###\n";
    for (size_t i = 1; i < st.rooms[0].size(); ++i)
        os << "  #" << st.rowString(i) << "#  \n";
    return os;
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

    std::cout << std::endl;
    State st(hallSz, pos);
    swap(st.hall[0], st.rooms[0][0]);
    swap(st.hall[1], st.rooms[0][1]);
    swap(st.hall[hallSz-1], st.rooms[3][0]);
    st.roomReady[0] = true;
    cout << st << endl;
    for (auto& move : st.neighbors()) {
        cout << move << endl;
    }
    
    return 0;
}
