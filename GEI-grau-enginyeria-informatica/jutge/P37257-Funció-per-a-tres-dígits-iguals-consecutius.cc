//Retorna true si n expressat en base b té tres dígits seguits iguals
bool tres_digits_seguits_iguals(int n, int b) {
    if (n < b*b) return false;
    else {
        int mod1 = n%b;
        int mod2 = (n/b)%b;
        int mod3 = (n/(b*b))%b;
        if (mod1 == mod2 and mod1 == mod3) return true;
        else return tres_digits_seguits_iguals(n/b, b);
    }
}