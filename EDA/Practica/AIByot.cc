#include "Player.hh"

using namespace std;


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Byot





struct PLAYER_NAME : public Player {


    /**
     * Factory: returns a new instance of this class.
     * Do not modify this function.
     */
    static Player* factory () {
        return new PLAYER_NAME;
    }


    /**
     * Attributes for your player can be defined here.
     */

     typedef vector < vector<char> > Matrix;

    /**
     * Play method.
     *
     * This method will be invoked once per each round.
     * You have to read the board here to place your actions
     * for this round.
     *
     */

     bool is_available(Pos& p, string s) {
     	if (s == "top" and (p.i == 0 or cell_type(p + Top) == Wall)) return false;
     	if (s == "bottom" and (p.i == rows() - 1 or cell_type(p + Bottom) == Wall)) return false;
     	if (s == "left" and (p.j == 0 or cell_type(p + Left) == Wall)) return false;
     	if (s == "right" and (p.j == cols() - 1 or cell_type(p + Right) == Wall)) return false;
     	return true;
     }

     char bfs(Pos p) {
     	queue<Pos> Q;
     	Q.push(p);
     	Pos p_aux = Q.front();
     	Pos p_sec;
     	Matrix M(rows(), vector<char>(cols(), 'n'));
     	while (not Q.empty() and (cell_type(p_aux) != Point and cell_type(p_aux) != Scope and cell_type(p_aux) != Attack and cell_type(p_aux) != Defense and cell_type(p_aux) != Stone)) {
     		Q.pop();
     		if (is_available(p_aux, "top")) {
     			if (M[p_aux.i - 1][p_aux.j] == 'n') {
     				if (p_aux == p) M[p_aux.i - 1][p_aux.j] = 't';
     				else M[p_aux.i - 1][p_aux.j] = M[p_aux.i][p_aux.j];
     				p_sec = p_aux + Top;
     				Q.push(p_sec);
     			}
     		}
     		if (is_available(p_aux, "bottom")) {
     			if (M[p_aux.i + 1][p_aux.j] == 'n') {
     				if (p_aux == p) M[p_aux.i + 1][p_aux.j] = 'b';
     				else M[p_aux.i + 1][p_aux.j] = M[p_aux.i][p_aux.j];
     				p_sec = p_aux + Bottom;
     				Q.push(p_sec);
     			}
     		}
     		if (is_available(p_aux, "left")) {
     			if (M[p_aux.i][p_aux.j - 1] == 'n') {
     				if (p_aux == p) M[p_aux.i][p_aux.j - 1] = 'l';
     				else M[p_aux.i][p_aux.j - 1] = M[p_aux.i][p_aux.j];
     				p_sec = p_aux + Left;
     				Q.push(p_sec);
     			}
     		}
     		if (is_available(p_aux, "right")) {
     			if (M[p_aux.i][p_aux.j + 1] == 'n') {
     				if (p_aux == p) M[p_aux.i][p_aux.j + 1] = 'r';
     				else M[p_aux.i][p_aux.j + 1] = M[p_aux.i][p_aux.j];
     				p_sec = p_aux + Right;
     				Q.push(p_sec);
     			}
     		}
     		if (not Q.empty()) p_aux = Q.front();
     	}
     	return M[p_aux.i][p_aux.j];
     }


    virtual void play () {
    	const Poquemon& p = poquemon(me());
    	Pos pos = p.pos;
    	if (p.alive) {
    		char c = bfs(pos);
    		bool b;
    		int idCell;
    		if (c == 't') {
    			b = false;
    			idCell = cell_id(pos + Top);
    			if (idCell != -1) {
    				attack(Top);
    				b = true;
    			}
    			idCell = cell_id(pos + Bottom);
    			if (idCell != -1) {
    				attack(Bottom);
    				b = true;
    			}
    			idCell = cell_id(pos + Left);
    			if (idCell != -1) {
    				attack(Left);
    				b = true;
    			}
    			idCell = cell_id(pos + Right);
    			if (idCell != -1) {
    				attack(Right);
    				b = true;
    			}
    			if (not b) move(Top);

    		}
    		else if (c == 'b') {
    			b = false;
    			idCell = cell_id(pos + Top);
    			if (idCell != -1) {
    				attack(Top);
    				b = true;
    			}
    			idCell = cell_id(pos + Bottom);
    			if (idCell != -1) {
    				attack(Bottom);
    				b = true;
    			}
    			idCell = cell_id(pos + Left);
    			if (idCell != -1) {
    				attack(Left);
    				b = true;
    			}
    			idCell = cell_id(pos + Right);
    			if (idCell != -1) {
    				attack(Right);
    				b = true;
    			}
    			if (not b) move(Bottom);
    		}
    		else if (c == 'l') {
    			b = false;
    			idCell = cell_id(pos + Top);
    			if (idCell != -1) {
    				attack(Top);
    				b = true;
    			}
    			idCell = cell_id(pos + Bottom);
    			if (idCell != -1) {
    				attack(Bottom);
    				b = true;
    			}
    			idCell = cell_id(pos + Left);
    			if (idCell != -1) {
    				attack(Left);
    				b = true;
    			}
    			idCell = cell_id(pos + Right);
    			if (idCell != -1) {
    				attack(Right);
    				b = true;
    			}
    			if (not b) move(Left);
    		}
    		else if (c == 'r') {
    			b = false;
    			idCell = cell_id(pos + Top);
    			if (idCell != -1) {
    				attack(Top);
    				b = true;
    			}
    			idCell = cell_id(pos + Bottom);
    			if (idCell != -1) {
    				attack(Bottom);
    				b = true;
    			}
    			idCell = cell_id(pos + Left);
    			if (idCell != -1) {
    				attack(Left);
    				b = true;
    			}
    			idCell = cell_id(pos + Right);
    			if (idCell != -1) {
    				attack(Right);
    				b = true;
    			}
    			if (not b) move(Right);
   			}
    	}
    }


};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
