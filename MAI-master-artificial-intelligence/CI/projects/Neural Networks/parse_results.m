function [best_row] = parse_results(results)
best_row_idx = -1;
best_test_acc = 0.0;
for i = 1:length(results)
    hidden_neurons = results(i, 7);
    split_ratio = results(i, 5);

    % Modify to filter with different parameters
    if hidden_neurons{1} == 200 && split_ratio{1}(1) == 0.80

        accuracies = results(i, 9);
        test_acc = accuracies{1}(3);
        if test_acc > best_test_acc
           best_row_idx = i;
           best_test_acc = test_acc;
        end
    end
end
best_row = results(best_row_idx, :);

accuracies = best_row(9);
disp("Accuracies");
disp(accuracies{1});

tr = best_row(10);
disp("Epochs");
disp(tr{1}.best_epoch);

disp("Time/Epoch");
disp(tr{1}.time(length(tr{1}.time)) / length(tr{1}.time));
end