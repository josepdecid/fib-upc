useParallel = 'no';
useGPU = 'no';

load('caltech101_silhouettes_28.mat');

X = X';
Y = dummyvar(Y)';

hiddenUnits = [50, 200, 500];

splitRatios = [
    0.80 0.10 0.10
    0.40 0.20 0.40
    0.10 0.10 0.80
]';

functions = [
    "logsig" "logsig" "mse"
    "logsig" "softmax" "crossentropy"
]';

c = struct();
c.trainFun = 'traingdx';
c.useParallel = useParallel;
c.useGPU = useGPU;
c.epochs = 1000;
c.patience = 20;

it = 1;
idx = 1;
randomSearchIt = 60;
executions = 5;

results = cell(10,                     ...
               randomSearchIt       * ...
               size(splitRatios, 2) * ...
               size(functions, 2)   * ...
               size(hiddenUnits, 1)   ...
           )';

while it <= randomSearchIt
    it = it + 1;
    
    lr = 10^-(rand() * 2);
    momentum = 10^-(rand() / 2);
    
    c.lr = lr;
    c.momentum = momentum;

    % Split dataset randomly into training, validation and test sets
    for ratio = splitRatios
        c.ratio = ratio;

        % Try different configurations
        for fun = functions
            c.functions = fun;

            % Try different number of hidden units
            for hid = hiddenUnits
                c.hiddenUnits = hid;

                % Perform n randomized executions to get the mean performance
                executionsErrors = zeros(executions, 3);
                executionsAccuracies = zeros(executions, 3);
                
                disp("Traning the model with:");
                disp(c);
                
                for i = 1:executions
                    [net, tr] = run_mlp(X, Y, c);
                    
                    % Training Accuracy
                    accTrain = accuracy(net, X, Y, tr.trainInd);
                    
                    % Validation Accuracy
                    accVal = accuracy(net, X, Y, tr.valInd);
                    
                    % Test Accuracy
                    accTest= accuracy(net, X, Y, tr.testInd);
                    
                    executionsErrors(i, :) = [tr.best_perf, tr.best_vperf, tr.best_tperf];
                    executionsAccuracies(i, :) = [accTrain, accVal, accTest];
                end
                
                meanErrors = mean(executionsErrors, 1);
                meanAccuracies = mean(executionsAccuracies, 1);
                c.error = meanErrors;
                c.accuracy = meanAccuracies;
                c.tr = tr;
                cc = struct2cell(c);
                results(idx, :) = cc(4:13)';
                idx = idx + 1;
            end
        end
    end
end