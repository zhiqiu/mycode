function prediction = UserBasedSlopeOne2( user, item )
% input:
% user -- given the user id
% item -- the item id
% output:
% prediction -- the prediction of user on item
% use trained-data for predict

% slope one algorithm
% Paper: A Creative Personalized Recommendation Algorithm¡ª¡ªUser-based Slope
% One Algorithm 
% Shiyu Song, Kejia Wu
% Author: Zhiqiu
% 2015-05-30

% load the matrix data set
% load('MovieLens.mat');
load('matrixData2.mat');
[userNum,itemNum]=size(R);


% % Dij the average difference between item Ii and item Ij
% % Wij  means the number of users that have both rated item i and item j.

% % prediction
% % Pti is the prediction rating of user t to item i, Dic
% % is  the  average deviation of the item i and item c
% % Wic is the number of users that  have  both  rated  item  i  and  item  c. 
% %Stc is  the  average similarity between user t and users that have rated item c.
ratingSum = 0;  
weightSum = 0;
for i= 1:itemNum
    if R(user,i)~=0 
        ratingSum = ratingSum + (R(user,i)+D(item,i))*S(user,i)*W(i,item);
        weightSum = weightSum + S(user,i)*W(i,item);
    end
end 
if weightSum > 0 
    prediction = ratingSum / weightSum;
else
    prediction = 0;
end
%prediction
end

