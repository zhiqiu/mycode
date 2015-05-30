% slope one algorithm
% Paper: A Creative Personalized Recommendation Algorithm——User-based Slope
% One Algorithm 
% Shiyu Song, Kejia Wu
% Author: Zhiqiu
% 2015-05-30
clc;
clear;
% load the matrix data set
load('G:\Users\chen\Desktop\大三下\数据挖掘\MovieLens.mat');
mat = R;
[userNum,itemNum]=size(R);
% userNum = 300;
% itemNum = 100;

% Dij the average difference between item Ii and item Ij
% Wij  means the number of users that have both rated item i and item j.
D = zeros(itemNum,itemNum);
W = zeros(itemNum,itemNum);
count_d = 0;
sum_d = 0;
for i = 1: itemNum
    for j = 1: itemNum
        sum_d = 0;
        count_d = 0;
        for c = 1 : userNum
            if R(c,i)~=0 && R(c,j)~=0
                sum_d = sum_d + R(c,i) - R(c,j);
                count_d = count_d + 1;
            end
        end
        D(i,j) = sum_d / count_d;
        W(i,j) = count_d;
    end
end
% 
% Measuring the rating similarity of users
% cosine  vector  similarity
Sim = zeros(userNum,userNum);
for i = 1 : userNum
    sum_i = 0;
    for c = 1:itemNum
        sum_i = sum_i+ R(i,c)*R(i,c);
    end
    
    for j = i : userNum
        sum_j = 0;
        sum_ij = 0;
        for c = 1:itemNum
            sum_ij = sum_ij+ R(i,c)*R(j,c);
            sum_j = sum_j+ R(j,c)*R(j,c);
        end
        Sim(i,j)  = sum_ij/sqrt(sum_i+sum_j);
    end
end
% sim

% User-based  Slope One algorithm
% Sti  to  express  the  average  of  the similarity between user t and users that have rated item i. 
S = zeros(userNum,itemNum);

for t = 1 : userNum
    for i = 1 : itemNum
        count = 0;
        ss = 0;
        for c = 1 : userNum
            if R(c,i)~=0 && c ~=t 
                count = count + 1;
                ss = ss + Sim(t,c);
            end
        end
        S(t,i) = ss/count;
    end
end

% prediction
% Pti is the prediction rating of user t to item i, Dic
% is  the  average deviation of the item i and item c
% Wic is the number of users that  have  both  rated  item  i  and  item  c. 
%Stc is  the  average similarity between user t and users that have rated item c.
% for t = 1: userNum
%     for i = 1 : itemNum
%         for c = 1: itemNum
%         end
%     end
% end
user = 5;
item = 7;
ratingSum = 0;
weightSum = 0;
for i= 1:itemNum
    if R(user,i)~=0
        ratingSum = ratingSum + (R(user,i)+D(item,i))*S(user,i)*W(i,item);
        weightSum = weightSum + S(user,i)*W(i,item);
    end
end 
ratingSum
weightSum
prediction = ratingSum / weightSum;
prediction