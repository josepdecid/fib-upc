//Deixa al paràmetre de sortida maxim l'n més gran
//Deixa al paràmetre de sortida minim l'n més petita
void digit_maxim_i_minim(int n, int& maxim, int& minim) {
    bool first = true;
    while (n != 0) {
      int d = n%10;
      if (first) {
        maxim = d; minim = d;
        first = false;
      }
      if (d > maxim) maxim = d;
      if (d < minim) minim = d;
      n /= 10;
    }
}