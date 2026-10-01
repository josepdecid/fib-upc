var float: R; % Quarterly repayment
var float: P; % Principal initially borrowed 
var 0.0 .. 2.0: I; % Interest rate

% Balances after each quarter
var float: B1;
var float: B2;
var float: B3;
var float: B4;

constraint B1 = P  * (1.0 + I) - R;
constraint B2 = B1 * (1.0 + I) - R;
constraint B3 = B2 * (1.0 + I) - R;
constraint B4 = B3 * (1.0 + I) - R;

solve satisfy;

output ["Borrowing \(P) at \(I)% interest, and repaying \(R) per quarter for 1 year leaves \(B4) owing"]