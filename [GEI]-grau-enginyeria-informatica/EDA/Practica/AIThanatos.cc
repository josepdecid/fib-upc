#include "Player.hh"
using namespace std;


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Thanatos





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

    int current_round = 0;
    int my_stones = 0;

    typedef pair<int, Pos> ArcW;

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
          int wPoint, wAttack, wDefense, wScope, wStone;
          // Points
          if (current_round < 100) wPoint = 5;
          else wPoint = -1;
          // Attack
          if (p.attack >= 10) wAttack = (rows()*cols())/2;
          else if (current_round < 100) wAttack = 1;
          else if (current_round < 350) wAttack = 2;
          else wAttack = 3;
          // Defense
          if (p.defense >= 10) wDefense = (rows()*cols())/2;
          else if (current_round < 80) wDefense = 1;
          else if (current_round < 350) wDefense = 2;
          else wDefense = 3;
          // Scope
          if (p.scope == max_scope()) wScope = (rows()*cols())/2;
          else if (current_round < 100) wScope = 2;
          else wScope = 3;
          // Stones
          if (p.scope == max_scope() || my_stones == max_stone()) wStone = (rows()*cols())/2;
          else if (current_round < 100) wStone = -1;
          else if (current_round < 350) wStone = 0;
          else wStone = 1;
          // Choose position
          Pos new_pos = dijkstra(current_pos, wPoint, wAttack, wDefense, wScope, wStone);
          if ((new_pos.i == -1 && new_pos.j == -1)) new_pos = berseker_mode(current_pos, p.attack);
          if ((new_pos.i == -1 && new_pos.j == -1)) new_pos = find_scape_wall(current_pos);
          Dir movement_direction = choose_direction(new_pos, current_pos);
          move(movement_direction);
        }
  		}
      ++current_round;
    }

    Pos dijkstra(Pos current_pos, int wPoint, int wAttack, int wDefense, int wScope, int wStone) {
      Matrix distance(rows(), Column(cols(), rows()*cols())); // rows*cols considered as dijkstra's infinite
      Matrix visited(rows(), Column(cols(), False)); // None of our cells have benn visited yet
      Pos whereFrom[rows()][cols()]; // Matrix used to know from where have we reached that cell
      for (int i = 0; i < rows(); ++i)
        for (int j = 0; j < cols(); ++j)
          whereFrom[i][j] = {-1, -1}; // This shouldn't even be necessary
      // When refactoring try to whereFrom[current_pos.i][current_pos.j] = {-1, -1};
      distance[current_pos.i][current_pos.j] = 0;
      priority_queue<ArcW, vector<ArcW>, greater<ArcW> > pQ;
      pQ.push({distance[current_pos.i][current_pos.j], current_pos});
      while (!pQ.empty()) {
        Pos new_pos = pQ.top().second;
        pQ.pop();
        int i = new_pos.i;
        int j = new_pos.j;
        if (!visited[i][j]) {
          visited[i][j] = True;
          // Above
          if (pos_ok(i-1, j)) {
            if (cell_type(i-1, j) != Wall) {
              if ((distance[i][j] + 1) < distance[i-1][j]) {
                distance[i-1][j] = distance[i][j] + 1;
                whereFrom[i-1][j] = {i, j};
              }
              if (distance[i-1][j] != ghost_wall({i-1, j}))
                pQ.push({distance[i-1][j], {i-1, j}});
            }
            else visited[i-1][j] = True;
          }
          // Below
          if (pos_ok(i+1, j)) {
            if (cell_type(i+1, j) != Wall) {
              if (distance[i][j] + 1 < distance[i+1][j]) {
                distance[i+1][j] = distance[i][j] + 1;
                whereFrom[i+1][j] = {i, j};
              }
              if (distance[i+1][j] != ghost_wall({i+1, j}))
                pQ.push({distance[i+1][j], {i+1, j}});
            }
            else visited[i+1][j] = True;
          }
          // Left
          if (pos_ok(i, j-1)) {
            if (cell_type(i, j-1) != Wall) {
              if ((distance[i][j] + 1) < distance[i][j-1]) {
                distance[i][j-1] = distance[i][j] + 1;
                whereFrom[i][j-1] = {i, j};
              }
              if (distance[i][j-1] != ghost_wall({i, j-1}))
                pQ.push({distance[i][j-1], {i, j-1}});
            }
            else visited[i][j-1] = True;
          }
          // Right
          if (pos_ok(i, j+1)) {
            if (cell_type(i, j+1) != Wall) {
              if ((distance[i][j] + 1) < distance[i][j+1]) {
                distance[i][j+1] = distance[i][j] + 1;
                whereFrom[i][j+1] = {i, j};
              }
              if (distance[i][j+1] != ghost_wall({i, j+1}))
                pQ.push({distance[i][j+1], {i, j+1}});
            }
            else visited[i][j+1] = True;
          }
        }
      }
      int closest_best_cell_distance = rows()*cols();
      Pos closest_best_cell = {-1, -1};
      for (int i = 0; i < rows(); ++i) {
        for (int j = 0; j < cols(); ++j) {
          if ((visited[i][j]) && ((cell_type(i, j) == Point && distance[i][j] + wPoint < closest_best_cell_distance)
                              || (cell_type(i, j) == Attack && distance[i][j] + wAttack < closest_best_cell_distance)
                              || (cell_type(i, j) == Defense && distance[i][j] + wDefense < closest_best_cell_distance)
                              || (cell_type(i, j) == Scope && distance[i][j] + wScope < closest_best_cell_distance)
                              || (cell_type(i, j) == Stone && distance[i][j] + wStone < closest_best_cell_distance))) {
            closest_best_cell_distance = distance[i][j];
            closest_best_cell = {i, j};
          }
        }
      }
      if (closest_best_cell.i == -1 && closest_best_cell.j == -1) return closest_best_cell;
      cerr << "Now we are in ("<< current_pos.i << "," << current_pos.j << ") Nearest/Important bonus path is: ";
      Pos result = closest_best_cell;
      cerr << "(" << result.i << "," << result.j << ")" << endl;
      closest_best_cell = whereFrom[result.i][result.j];
      if (closest_best_cell.i == -1 && closest_best_cell.j == -1) return result;
      while(1) {
        cerr << result.i << "," << result.j << " - This cell points to: " << whereFrom[result.i][result.j] << endl;
        Pos aux = whereFrom[closest_best_cell.i][closest_best_cell.j];
        if (aux.i == -1 && aux.j == -1) {
          cerr << "We are going to return: (" << result.i << "," << result.j << ")" << endl;
          return result;
        }
        result = closest_best_cell;
        closest_best_cell = aux;
      }
    }

    Pos berseker_mode(Pos current_pos, int my_attack)
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
            int idCell = cell_id({i-1, j});
            if (idCell != -1) {
              //Poquemon enemy = poquemon(idCell);
              //if (enemy.defense <= my_attack) {
                new_pos = {i-1, j};
                goto backtrack;
              //}
            }
            Q.push({i-1, j});
          }
          visited[i-1][j] = True;
        }
        //Right
        if (pos_ok(i+1, j) && !visited[i+1][j]) {
          if (cell_type(i+1, j) != Wall) {
            whereFrom[i+1][j] = new_pos;
            int idCell = cell_id({i+1, j});
            if (idCell != -1) {
              Poquemon enemy = poquemon(idCell);
              if (enemy.defense <= my_attack) {
                new_pos = {i+1, j};
                goto backtrack;
              }
            }
            Q.push({i+1, j});
          }
          visited[i+1][j] = True;
        }
        //Above
        if (pos_ok(i, j-1) && !visited[i][j-1]) {
          if (cell_type(i, j-1) != Wall) {
            whereFrom[i][j-1] = new_pos;
            int idCell = cell_id({i, j-1});
            if (idCell != -1) {
              Poquemon enemy = poquemon(idCell);
              if (enemy.defense <= my_attack) {
                new_pos = {i, j-1};
                goto backtrack;
              }
            }
            Q.push({i, j-1});
          }
          visited[i][j-1] = True;
        }
        //Below
        if (pos_ok(i, j+1) && !visited[i][j+1]) {
          if (cell_type(i, j+1) != Wall) {
            whereFrom[i][j+1] = new_pos;
            int idCell = cell_id({i, j+1});
            if (idCell != -1) {
              Poquemon enemy = poquemon(idCell);
              if (enemy.defense <= my_attack) {
                new_pos = {i, j+1};
                goto backtrack;
              }
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
      if (new_pos.i == -1 && new_pos.j == -1) return result;
      while(1) {
        cerr << new_pos.i << ":" << new_pos.j << " ";
        Pos aux = whereFrom[new_pos.i][new_pos.j];
        if (aux.i == -1 && aux.j == -1) return result;
        result = new_pos;
        new_pos = aux;
      }
    }

    Pos find_scape_wall(Pos current_pos)
    {
      Pos new_pos = {-1, -1};
      Matrix visited(rows(), Column(cols(), False));
      Pos whereFrom[rows()][cols()];
      whereFrom[current_pos.i][current_pos.j] = new_pos;
      visited[current_pos.i][current_pos.j] = True;
      queue<Pos> Q;
      Q.push(current_pos);
      while (!Q.empty()) {
        new_pos = Q.front(); Q.pop();
        // Search around positions to find a ghost wall
        if ((pos_ok(new_pos.i-1, new_pos.j) && ghost_wall({new_pos.i-1, new_pos.j}) != -1)
         || (pos_ok(new_pos.i+1, new_pos.j) && ghost_wall({new_pos.i+1, new_pos.j}) != -1)
         || (pos_ok(new_pos.i, new_pos.j-1) && ghost_wall({new_pos.i, new_pos.j-1}) != -1)
         || (pos_ok(new_pos.i, new_pos.j+1) && ghost_wall({new_pos.i, new_pos.j+1}) != -1)) goto backtrack;
        // Else we keep adding nodes into our queue
        // Above
        if (pos_ok(new_pos.i-1, new_pos.j) && !visited[new_pos.i-1][new_pos.j]) {
            if (cell_type(new_pos.i-1, new_pos.j) != Wall) {
              whereFrom[new_pos.i-1][new_pos.j] = new_pos;
              Q.push({new_pos.i-1, new_pos.j});
            }
            visited[new_pos.i-1][new_pos.j] = True;
        }
        if (pos_ok(new_pos.i+1, new_pos.j) && !visited[new_pos.i+1][new_pos.j]) {
            if (cell_type(new_pos.i+1, new_pos.j) != Wall) {
              whereFrom[new_pos.i+1][new_pos.j] = new_pos;
              Q.push({new_pos.i+1, new_pos.j});
            }
            visited[new_pos.i+1][new_pos.j] = True;
        }
        if (pos_ok(new_pos.i, new_pos.j-1) && !visited[new_pos.i][new_pos.j-1]) {
            if (cell_type(new_pos.i, new_pos.j-1) != Wall) {
              whereFrom[new_pos.i][new_pos.j-1] = new_pos;
              Q.push({new_pos.i, new_pos.j-1});
            }
            visited[new_pos.i][new_pos.j-1] = True;
        }
        if (pos_ok(new_pos.i, new_pos.j+1) && !visited[new_pos.i][new_pos.j+1]) {
            if (cell_type(new_pos.i, new_pos.j+1) != Wall) {
              whereFrom[new_pos.i][new_pos.j+1] = new_pos;
              Q.push({new_pos.i, new_pos.j+1});
            }
            visited[new_pos.i][new_pos.j+1] = True;
        }
      }
      return {-1, -1};
      backtrack:
      Pos result = new_pos;
      new_pos = whereFrom[result.i][result.j];
      if (new_pos.i == -1 && new_pos.j == -1) return result;
      while(1) {
        cerr << result.i << ":" << result.j << " ";
        Pos aux = whereFrom[new_pos.i][new_pos.j];
        if (aux.i == -1 && aux.j == -1) return result;
        result = new_pos;
        new_pos = aux;
      }
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

    //Selects a random direction to move to
    Dir rand_dir (Dir notd)
    {
  	  Dir DIRS[] = {Top, Bottom, Left, Right};
  	  while (true) {
  		Dir d = DIRS[randomize() % 4];
  		if (d != notd) return d;
  	  }
  	}


    // According to our current pos, chooses the direction to get the new_pos
    Dir choose_direction(Pos new_pos, Pos current_pos)
    {
      Dir DIRS[] = {Top, Bottom, Left, Right};
      if (current_pos.i - 1 == new_pos.i) return DIRS[0];
      if (current_pos.i + 1 == new_pos.i) return DIRS[1];
      if (current_pos.j - 1 == new_pos.j) return DIRS[2];
      if (current_pos.j + 1 == new_pos.j) return DIRS[3];
      return rand_dir(None);
    }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
