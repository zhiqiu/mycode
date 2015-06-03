% test file for UserBasedSlopOne
% 
%load('matrixData2.mat');   % load traind model
load('dataset.mat');       % load testdata     
testD = train(1:100,:);
[m n] = size(testD);
target = testD(:,3);
predict = zeros(m,1);
for i =1: m
    predict(i,1) = UserBasedSlopeOne2( testD(i,1), testD(i,2) );
end
mae = MAE(predict,target)
rmse = RMSE(predict,target)