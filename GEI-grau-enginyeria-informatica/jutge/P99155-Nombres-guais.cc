//Un nombre n es guai en base b si totes les seves xifres en
//aquesta base son parells.
bool es_guai (int n, int b) {
    if (n < b) {
          return (n%2 == 0);
    }
    if ((n%b)%2 == 0) return es_guai (n/b, b);
    else return false;
}