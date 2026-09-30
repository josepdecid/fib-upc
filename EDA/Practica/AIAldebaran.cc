#include "Player.hh"
#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Aldebaran





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

    // Matrix used in visited elements (BFS)
    typedef int Boolean;
    typedef vector<Boolean> Column;
    typedef vector<Column> Matrix;
    #define False 0
    #define True 1

    // Matrix used in whereFrom of one node;
    typedef vector<int> Node_vector;
    typedef vector<Node_vector> Graph;


    //string mode_berseker[] = {"Stone", "Attack", "Scope", "Bag", "Defense"};
    //string mode_shell[] = {"Stone", "Defense", "Bag", "Attack", "Scope"};
    //string mode_powerOfMoney[] = {"Point", "Stone", "Defense", "Attack", "Scope"};

    int mode_selected = 0;

    /**
     * Play method.
     *
     * This method will be invoked once per each round.
     * You have to read the board here to place your actions
     * for this round.
     *
     */
    virtual void play () {

      const Poquemon& p = poquemon(me());

      if (p.alive) {
        Pos current_pos = p.pos;
        Dir attack_direction = find_poquemon(current_pos, p.scope, p.attack);
        if (attack_direction != None) attack(attack_direction);
        else {
          Pos new_pos = nearest_Bag(current_pos);
          if (new_pos.i == -1 && new_pos.j == -1) new_pos = nearest_bonus(current_pos);
          Dir movement_direction = choose_direction(new_pos, current_pos);
          move(movement_direction);
        }
  		}
    }

    Dir rand_dir (Dir notd) {
  	  Dir DIRS[] = {Top, Bottom, Left, Right};
  	  while (true) {
  		Dir d = DIRS[randomize() % 4];
  		if (d != notd) return d;
  	  }
  	}

    Dir choose_direction(Pos new_pos, Pos current_pos)
    {
      Dir DIRS[] = {Top, Bottom, Left, Right};
      if (current_pos.i - 1 == new_pos.i) return DIRS[0];
      if (current_pos.i + 1 == new_pos.i) return DIRS[1];
      if (current_pos.j - 1 == new_pos.j) return DIRS[2];
      if (current_pos.j + 1 == new_pos.j) return DIRS[3];
      return rand_dir(None);
    }

    Dir find_poquemon(Pos current_pos, int my_scope, int my_attack)
    {
      int offset, idCell;
      Poquemon enemy;
      Dir DIRS[] = {Top, Bottom, Left, Right};
      Pos aux;
      // Look for an enemy above us
      offset = 1;
      aux = current_pos;
      --aux.i;
      while (pos_ok(aux) && cell_type(aux) != Wall && my_scope >= offset) {
        int idCell = cell_id(aux);
        if (idCell != -1) {
          enemy = poquemon(idCell);
          if (offset == 1) return DIRS[0];
          if (enemy.defense <= my_attack) return DIRS[0];
        }
        --aux.i; ++offset;
      }
      // Look for an enemy below us
      offset = 1;
      aux = current_pos;
      ++aux.i;
      while (pos_ok(aux) && cell_type(aux) != Wall && my_scope >= offset) {
        int idCell = cell_id(aux);
        if (idCell != -1) {
          enemy = poquemon(idCell);
          if (offset == 1) return DIRS[1];
          if (enemy.defense <= my_attack) return DIRS[1];
        }
        ++aux.i; ++offset;
      }
      // Look for an enemy on left
      offset = 1;
      aux = current_pos;
      --aux.j;
      while (pos_ok(aux) && cell_type(aux) != Wall && my_scope >= offset) {
        int idCell = cell_id(aux);
        if (idCell != -1) {
          enemy = poquemon(idCell);
          if (offset == 1) return DIRS[2];
          if (enemy.defense <= my_attack) return DIRS[2];
        }
        --aux.j; ++offset;
      }
      // Look for an enemy on right
      offset = 1;
      aux = current_pos;
      ++aux.j;
      while (pos_ok(aux) && cell_type(aux) != Wall && my_scope >= offset) {
        int idCell = cell_id(aux);
        if (idCell != -1) {
          enemy = poquemon(idCell);
          if (offset == 1) return DIRS[3];
          if (enemy.defense <= my_attack) return DIRS[3];
        }
        ++aux.j; ++offset;
      }
      return None;
    }

    Pos nearest_bonus(Pos current_pos)
    {
      Pos new_pos = {-1, -1};
      Pos whereFrom[rows()][cols()];
      whereFrom[current_pos.i][current_pos.j] = new_pos;
      Matrix visited(rows(), Column(cols(), False));
      queue<Pos> Q;
      Q.push(current_pos);
      visited[current_pos.i][current_pos.j] = True;
      while (!Q.empty()) {
        new_pos = Q.front();
        Q.pop();
        int i = new_pos.i;
        int j = new_pos.j;
        //Left
        if (pos_ok(i-1, j) && !visited[i-1][j]) {
          if (cell_type(i-1, j) != Wall) {
            whereFrom[i-1][j] = new_pos;
            if (cell_type(i-1, j) != Empty) {
              new_pos = {i-1, j};
              goto backtrack;
            }
            Q.push({i-1, j});
          }
          visited[i-1][j] = True;
        }
        //Right
        if (pos_ok(i+1, j) && !visited[i+1][j]) {
          if (cell_type(i+1, j) != Wall) {
            whereFrom[i+1][j] = new_pos;
            if (cell_type(i+1, j) != Empty) {
              new_pos = {i+1, j};
              goto backtrack;
            }
            Q.push({i+1, j});
          }
          visited[i+1][j] = True;
        }
        //Above
        if (pos_ok(i, j-1) && !visited[i][j-1]) {
          if (cell_type(i, j-1) != Wall) {
            whereFrom[i][j-1] = new_pos;
            if (cell_type(i, j-1) != Empty) {
              new_pos = {i, j-1};
              goto backtrack;
            }
            Q.push({i, j-1});
          }
          visited[i][j-1] = True;
        }
        //Below
        if (pos_ok(i, j+1) && !visited[i][j+1]) {
          if (cell_type(i, j+1) != Wall) {
            whereFrom[i][j+1] = new_pos;
            if (cell_type(i, j+1) != Empty) {
              new_pos = {i, j+1};
              goto backtrack;
            }
            Q.push({i, j+1});
          }
          visited[i][j+1] = True;
        }
      }
      return {-1, -1};
      backtrack:
      Pos result = new_pos;
      new_pos = whereFrom[result.i][result.j];
      while(1) {
        cerr << result.i << ":" << result.j << " ";
        Pos aux = whereFrom[new_pos.i][new_pos.j];
        if (aux.i == -1 && aux.j == -1) return result;
        result = new_pos;
        new_pos = aux;
      }
    }

    // From the current point, returns nearest positon where there is a bag.
    Pos nearest_Bag(Pos current_pos)
    {
      Pos new_pos = {-1, -1};
      Pos whereFrom[rows()][cols()];
      whereFrom[current_pos.i][current_pos.j] = new_pos;
      Matrix visited(rows(), Column(cols(), False));
      queue<Pos> Q;
      Q.push(current_pos);
      visited[current_pos.i][current_pos.j] = True;
      while (!Q.empty()) {
        new_pos = Q.front();
        Q.pop();
        int i = new_pos.i;
        int j = new_pos.j;
        //Left
        if (pos_ok(i-1, j) && !visited[i-1][j]) {
          if (cell_type(i-1, j) != Wall) {
            whereFrom[i-1][j] = new_pos;
            if (cell_type(i-1, j) == Point || cell_type(i-1, j) == Defense) {
              new_pos = {i-1, j};
              goto backtrack;
            }
            Q.push({i-1, j});
          }
          visited[i-1][j] = True;
        }
        //Right
        if (pos_ok(i+1, j) && !visited[i+1][j]) {
          if (cell_type(i+1, j) != Wall) {
            whereFrom[i+1][j] = new_pos;
            if (cell_type(i+1, j) == Point || cell_type(i+1, j) == Defense) {
              new_pos = {i+1, j};
              goto backtrack;
            }
            Q.push({i+1, j});
          }
          visited[i+1][j] = True;
        }
        //Above
        if (pos_ok(i, j-1) && !visited[i][j-1]) {
          if (cell_type(i, j-1) != Wall) {
            whereFrom[i][j-1] = new_pos;
            if (cell_type(i, j-1) == Point || cell_type(i, j-1) == Defense) {
              new_pos = {i, j-1};
              goto backtrack;
            }
            Q.push({i, j-1});
          }
          visited[i][j-1] = True;
        }
        //Below
        if (pos_ok(i, j+1) && !visited[i][j+1]) {
          if (cell_type(i, j+1) != Wall) {
            whereFrom[i][j+1] = new_pos;
            if (cell_type(i, j+1) == Point || cell_type(i, j+1) == Defense) {
              new_pos = {i, j+1};
              goto backtrack;
            }
            Q.push({i, j+1});
          }
          visited[i][j+1] = True;
        }
      }
      return {-1, -1};
      backtrack:
      Pos result = new_pos;
      new_pos = whereFrom[result.i][result.j];
      while(1) {
        cerr << result.i << ":" << result.j << " ";
        Pos aux = whereFrom[new_pos.i][new_pos.j];
        if (aux.i == -1 && aux.j == -1) return result;
        result = new_pos;
        new_pos = aux;
      }
    }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
