% --------------------------
% -- Rosenbrock Exercise ---
% --------------------------

%% Fitness Function

fitnessFunction = @(x) (1 - x(1))^2 + 100*(x(2) - x(1)^2)^2;

[X, Y] = meshgrid(-2:0.1:2);                                
Z = (1 - X).^2 + 100*(Y - X.^2).^2;

surf(X, Y, Z);

%% Random Search Configuration

RANDOM_SEARCH_IT = 1000;

selectionFun = {
    @selectionstochunif
    @selectionremainder
    @selectionroulette
    @selectiontournament
};

configs = zeros(RANDOM_SEARCH_IT, 4);
configRanges = zeros(RANDOM_SEARCH_IT, 4);
for i = 1:RANDOM_SEARCH_IT
    configs(i, :) = [
        50 * randi(20) + 50 % {50, 100, 150, ..., 950, 1000}
        50 * randi(20) + 50 % {50, 100, 150, ..., 950, 1000}
        rand()              % [0..1]
        randi(4)            % {1, 2, 3, 4}
    ];

    % [-2, ..., 2]
    minX = rand() * 4 - 2; maxX = rand() * 4 - 2;
    if minX > maxX; [minX, maxX] = deal(maxX, minX); end
    
    % [-2, ..., 2]
    minY = rand() * 4 - 2; maxY = rand() * 4 - 2;
    if minY > maxY; [minY, maxY] = deal(maxY, minY); end
    
    configRanges(i, :) = [minX minY maxX maxY];
end

%% Random Search Optimization

SEED_EXPERIMENTS = 5;

results = zeros(RANDOM_SEARCH_IT, 3);
for i = 1:RANDOM_SEARCH_IT
    c = configs(i, :);
    disp("Running configuration " + i);
    
    cr = configRanges(i, :);
    range = [cr(1:2) ; cr(3:4)];
    
    bestFVal = inf;
    for j = 1:SEED_EXPERIMENTS
        opts = gaoptimset('Generations',       c(1),  ...
                          'PopulationSize',    c(2),   ...
                          'CrossoverFraction', c(3), ...
                          'SelectionFcn',      selectionFun(c(4)),    ...
                          'PopInitRange',      range, ...
                          'Display', 'none');

        [x, fVal]= ga(fitnessFunction, 2, [], [], [], [], [], [], [], opts);
        if fVal < bestFVal
           bestFVal = fVal; 
        end
    end
    
    fprintf('> %.10f\n', bestFVal);
    results(i, :) = [bestFVal ; x(1) ; x(2)];
end

outputs = [configs results];

%% Table of Results

% Load Results
% load('outputs')
% load('configRanges')

K_TOP = min(10, RANDOM_SEARCH_IT);

varNames = ["\#Gen", "\#Pop", "CrossoverFrac", ...
            "SelectionFcn", "InitX", "InitY", ...
            "FVal", "X", "Y"];

% Display Headers
for name = varNames
    fprintf('%s ', name);
end; fprintf('\n');

[sortedOutputs, originalIdx] = sortrows(outputs, 5);

% Display Table Content
for i = 1:K_TOP
    o = sortedOutputs(i, :);
    
    fh = selectionFun(o(4));
    
    oi = originalIdx(i);
    cr = configRanges(oi, :);
    
    fprintf('%d %d %.5f %s [%.2f;%.2f] [%.2f,%.2f] %d %.5f %.5f\n', ...
        o(1), o(2), o(3), ...
        extractAfter(func2str(fh{1}), 9), ...
        cr(1), cr(3), cr(2), cr(4), ...
        o(5), o(6), o(7));
end; fprintf('\n');

% Output can be exported to LaTeX with this tool:
% https://latex-table-paste.herokuapp.com/

%% Contour plot 

[X, Y] = meshgrid(-3:0.01:3, -2:0.01:4);                                
Z = (1 - X).^2 + 100*(Y - X.^2).^2;

xs = sortedOutputs(:, 6);
ys = sortedOutputs(:, 7);

contour(X, Y, Z, 50);
hold on;

for i = 1:length(xs)
    plot(xs(i), ys(i), 'r.', 'MarkerSize', 12);
end

plot(1, 1, 'b o', 'MarkerSize', 12, 'MarkerFaceColor', [0.4 0.4 1]);

hold off;