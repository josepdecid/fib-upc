function acc = accuracy(net, X, Y, indices)
    pred = net(X(:, indices));
    maxPred = pred == max(pred,[],1);
    corrects = sum(sum(abs(maxPred - Y(:, indices)), 1) == 0);
    acc = corrects / length(Y(:, indices));
end
