function [net, tr] = run_mlp(X, Y, config)
net = feedforwardnet(config.hiddenUnits);

net.trainFcn= config.trainFun;
net.trainParam.epochs = config.epochs;
net.trainParam.lr = config.lr;
net.trainParam.mc = config.momentum;

net.divideFcn = 'dividerand';
net.divideParam.trainRatio = config.ratio(1);
net.divideParam.valRatio = config.ratio(2);
net.divideParam.testRatio = config.ratio(3);

net.layers{1}.transferFcn = config.functions(1);
net.layers{2}.transferFcn = config.functions(2);
net.performFcn = config.functions(3);

net.outputs{2}.processParams{2}.ymin = 0;
net.trainParam.max_fail = config.patience;

[net, tr] = train(net, X, Y,                         ...
                  'UseParallel', config.useParallel, ...
                  'useGPU', config.useGPU);  

end
