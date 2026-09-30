#include "Player.hh"
using namespace std;

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Hypnos

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
    typedef vector<int> Row;
    typedef vector<Row> Graph;

    int currentRound = 0;
    int my_stones = 0;

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
        Matrix gravityZone(rows(), column(cols(), 0));
        Matrix whereFrom(rows(), column(cols(), -1))
        int wPoints, wAttack, wDefense, wScope, wStone;
        statisticalWeight(wPoints, wAttack, wDefense, wScope, wStone);
        Pos new_pos = treatGravityZone(p, gravityZone, whereFrom, wPoints, wAttack, wDefense, wScope, wStone);
        movementDirection(p, objectivePos, whereFrom);
  		}
      ++currentRound;
    }

    //This function is called from updateGravityZone once choosen new gravity values just to update them.
    void buildGravityZone(const Pos &currentPos, Matrix &gravityZone, const int &increase)
    {
      int i = currentPos.i;
      int j = currentPos.j;
      gravityZone[i][j] += increase;
      if (pos_ok(i-1, j)) gravityZone[i-1][j] += increase/2;
      if (pos_ok(i+1, j)) gravityZone[i+1][j] += increase/2;
      if (pos_ok(i, j-1)) gravityZone[i][j-1] += increase/2;
      if (pos_ok(i, j+1)) gravityZone[i][j+1] += increase/2;
    }

    //This function is called from treatGravityZone and will update gravityZone information according to currentPos content.
    void updateGravityZone(const Poquemon& p, const Pos &currentPos, Matrix &gravityZone, const int &wPoints, const int &wAttack, const int &wDefense, const int &wScope, const int &wStone)
    {
      if (cell_type(currentPos) == Point) buildGravityZone(currentPos, gravityZone, ponts_value(currentPos)*wPoints);
      else if (cell_type(currentPos) == Attack) buildGravityZone(currentPos, gravityZone, wAttack);
      else if (cell_type(currentPos) == Defense) buildGravityZone(currentPos, gravityZone, wDefense);
      else if (cell_type(currentPos) == Scope) buildGravityZone(currentPos, gravityZone, wScope);
      else if (cell_type(currentPos) == Stone) buildGravityZone(currentPos, gravityZone, wStone);
      else {
        int idCell = cell_id(currentPos);
        if (idCell != -1)  {
          Poquemon enemy = poquemon(idCell) {
            int myReward = (p.score * battle_reward())/100;
            int enemyReward = (enemy.score * battle_reward())/100;
            //According to enemy and my status, update gravityZone positively or negatively
            if (enemy.attack >= p.defense && enemy.defense > p.attack) buildGravityZone(currentPos, gravityZone, -1*myReward);
            else if (enemy.attack >= p.defense && enemy.defense <= p.attack) buildGravityZone(currentPos, gravityZone, -1*myReward + enemyReward);
            else if (enemy.attack < p.defense && enemy.defense < p.attack) buildGravityZone(currentPos, gravityZone, enemyReward);
            //If I can't hill him and he can't kill me I will not lose time there.
          }
        }
      }
    }

    //This function is called from treatGravityZone if currentPos have something on it and refreshes the position with more gravity in a local area.
    Pos MaxGravityZone(const Pos &currentPos, int &countMaxGravity, const Matrix &gravityZone)
    {
      int i = currentPos.i;
      int j = currentPos.j;
      Pos result;
      if (gravityZone[i][j] > countMaxGravity) { countMaxGravity = gravityZone[i][j]; result = {i, j}; };
      if (pos_ok(i-1, j) && gravityZone[i-1][j] > countMaxGravity) { countMaxGravity = gravityZone[i-1][j]; result = {i-1, j}; };
      if (pos_ok(i-1, j-1) && gravityZone[i-1][j-1] > countMaxGravity) { countMaxGravity = gravityZone[i-1][j-1]; result = {i-1, j-1}; };
      if (pos_ok(i-1, j+1) && gravityZone[i-1][j+1] > countMaxGravity) { countMaxGravity = gravityZone[i-1][j+1]; result = {i-1, j+1}; };
      if (pos_ok(i+1, j) && gravityZone[i+1][j] > countMaxGravity) { countMaxGravity = gravityZone[i+1][j]; result = {i+1, j}; };
      if (pos_ok(i+1, j-1) && gravityZone[i+1][j-1] > countMaxGravity) { countMaxGravity = gravityZone[i+1][j-1]; result = {i+1, j-1}; };
      if (pos_ok(i+1, j+1) && gravityZone[i+1][j+1] > countMaxGravity) { countMaxGravity = gravityZone[i+1][j+1]; result = {i+1, j+1}; };
      if (pos_ok(i, j-1) && gravityZone[i][j-1] > countMaxGravity) { countMaxGravity = gravityZone[i][j-1]; result = {i, j-1}; };
      if (pos_ok(i, j+1) && gravityZone[i][j+1] > countMaxGravity) { countMaxGravity = gravityZone[i][j+1]; result = {i, j+1}; };
      return result;
    }

    //This function is called from main method and will build a gravity zone according to weight assigned to different bonuses.
    Pos treatGravityZone(const Poquemon& p, Matrix &gravityZone, Matrix &whereFrom, const int &wPoints, const int &wAttack, const int &wDefense, const int &wScope, const int &wStone)
    {
      Pos currentPos = p.pos;
      Pos posMaxGravity = {-1, -1};
      int countMaxGravity = 0;
      Matrix visited(rows(), column(cols(), false));
      Matrix distance(rows(), column(cols(), 0));
      queue<Pos> Q;
      Q.push(currentPos);
      visited[i][j] = true;
      while (!Q.empty()) {
        Pos newPos = Q.front(); Q.pop();
        int i = newPos.i;
        int j = newPos.j;
        if (cell_type(new_pos) != Empty || cell_id(new_pos) != -1) {
          updateGravityZone(p, newPos, gravityZone, wPoints, wAttack, wDefense, wScope, wStone);
          posMaxGravity = (countMaxGravity, newPos, gravityZone);
        }
        //Add new adjacent vertices:
        //Above
        if (pos_ok(i-1, j) && !visited[i-1][j]) {
          if (cell_type(i-1, j) != Wall) {
            distance[i-1][j] = distance[i][j] + 1;
            if (ghost_wall({i-1, j}) > distance[i-1][j]) Q.push({i-1, j});
          }
          visited[i-1][j] = true;
        }
        //Below
        if (pos_ok(i+1, j) && !visited[i+1][j]) {
          if (cell_type(i+1, j) != Wall) {
            distance[i-1][j] = distance[i][j] + 1;
            if (ghost_wall({i+1, j}) > distance[i+1][j]) Q.push({i+1, j});
          }
          visited[i+1][j] = true;
        }
        //Left
        if (pos_ok(i, j-1) && !visited[i][j-1]) {
          if (cell_type(i, j-1) != Wall) {
            distance[i][j-1] = distance[i][j] + 1;
            if (ghost_wall({i, j-1}) > distance[i][j-1]) Q.push({i, j-1});
          }
          visited[i][j-1] = true;
        }
        //Right
        if (pos_ok(i, j+1) && !visited[i][j+1]) {
          if (cell_type(i, j+1) != Wall) {
            distance[i][j+1] = distance[i][j] + 1;
            if (ghost_wall({i, j+1}) > distance[i][j+1]) Q.push({i, j+1});
          }
          visited[i][j+1] = true;
        }
      }
      return posMaxGravity;
    }

    //This function is called from movementDirection and backtracks to return the adjacent vertice to move to.
    Pos bestPath(Pos objectivePos, Matrix &whereFrom)
    {
      Pos aux = whereFrom[objectivePos.i][objectivePos.j];
      while (aux != {-1, -1}) {
        objectivePos = aux;
        aux = whereFrom[objectivePos.i][objectivePos.j];
      }
      return objectivePos;
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

    //This function is called from main method and selects the movement direction according to the objective position.
    Dir movementDirection(const Poquemon& p, const Pos &objectivePos, Matrix &whereFrom)
    {
      Pos currentPos = p.pos;
      Pos new_pos = bestPath(objectivePos, whereFrom);
      Dir DIRS[] = {Top, Bottom, Left, Right};
      //Above
      if (currentPos.i - 1 == new_pos.i && currentPos.j == new_pos.j) return DIRS[0];
      //Below
      if (currentPos.i + 1 == new_pos.i && currentPos.j == new_pos.j) return DIRS[1];
      //Left
      if (currentPos.i == new_pos.i && currentPos.j - 1 == new_pos.j) return DIRS[2];
      //Right
      if (currentPos.i == new_pos.i && currentPos.j + 1 == new_pos.j) return DIRS[3];
      //Random DIR
      return rand_dir(None);
    }

};

/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
