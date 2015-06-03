function prediction = UserBasedSlopeOne( user, item, matrixfilename )
% input:
% user -- given the user id
% item -- the item id
% matrixfilename -- the .mat file that contains the user-item rating matrix
%                   eg: matrixfilename = 'MovieLens.mat'
% output:
% prediction -- the prediction of user on item

% slope one algorithm
% Paper: A Creative Personalized Recommendation Algorithm¡ª¡ªUser-based Slope
% One Algorithm -- by Shiyu Song, Kejia Wu
% Author: Zhiqiu, Chen
% 2015-05-30


%% load the matrix data set
% load('MovieLens.mat');
load(matrixfilename);
mat = R;
[userNum,itemNum]=size(R);

% because the complexity is m*n*n, so use all data will cost too much time
% you can use a subset of data.
% userNum = 300;
% itemNum = 100;

%% Calculate item diference matrix D
% Dij the average difference between item Ii and item Ij
% Wij  means the number of users that have both rated item i and item j.

% use c program to save time, mex programing
RN = R;
RN(RN > 0) = 1;   % if RN(i,j)>0, RN(i,j) = 1
W = RN'*RN;       % count W matrix
D = GetTheDiffMat(R);
D = D./W;
D1 = D;
D(isnan(D)) = 0;   %replace Nan with 0
D(~isfinite(D)) = 0; %replace inf with 0
% -- old version code, high time comsuming -- 
%D = zeros(itemNum,itemNum);
%W = zeros(itemNum,itemNum);
% for i = 1: itemNum
%     for j = i: itemNum
%         sum_d = 0;
%         count_u = 0;
%         for c = 1 : userNum
%             if R(c,i)~=0 && R(c,j)~=0
%                 sum_d = sum_d + R(c,i) - R(c,j);
%                 count_u = count_u + 1;
%             end
%         end
%         if count_u > 0 
%              D(i,j) = sum_d / count_u;
%              D(j,i) = -D(i,j);
%         else
%             D(i,j) = 0; D(j,i) = 0;
%         end
% %         D(i,j) = sum_d / count_d;
%         W(i,j) = count_u;
%         W(j,i) = count_u;
%                 
%         %disp(j);
%     end
% %     disp(i);
% end
% 

%% Measuring the rating similarity of users
% cosine  vector  similarity
% after time optimization design, use repmat function to save time
R2 =  R.^2;   % 
A = sum(R2,2);
SumU = repmat(A,[1 userNum]);
Sim = R*R'./ (SumU*SumU'); 

% -- old version code, high time comsuming -- 
% Sim = zeros(userNum,userNum);
% for i = 1 : userNum
%     sum_i = 0;
%     for c = 1:itemNum
%         sum_i = sum_i+ R(i,c)*R(i,c);
%     end
%     
%     for j = 1 : userNum
%         sum_j = 0;
%         sum_ij = 0;
%         for c = 1:itemNum
%             sum_ij = sum_ij+ R(i,c)*R(j,c);
%             sum_j = sum_j+ R(j,c)*R(j,c);
%         end
%         Sim(i,j)  = sum_ij/sqrt(sum_i*sum_j);
%     end
% end
% sim


%% count average  of  the similarity S 
% User-based  Slope One algorithm
% Sti  to  express  the  average  of  the similarity between user t and users that have rated item i. 
S = GetTheAveSimMat(R,Sim);
% [m n] = size(S)
% -- old version code, high time comsuming -- 
% S = zeros(userNum,itemNum);
% for t = 1 : userNum
%     for i = 1 : itemNum
%         count = 0;
%         ss = 0;
%         for c = 1 : userNum
%             if R(c,i)~=0 && c ~=t 
%                 count = count + 1;
%                 ss = ss + Sim(t,c);
%             end
%         end
%         S(t,i) = ss/count;
%     end
% end


%% prediction
% Pti is the prediction rating of user t to item i, Dic
% is  the  average deviation of the item i and item c
% Wic is the number of users that  have  both  rated  item  i  and  item  c. 
%Stc is  the  average similarity between user t and users that have rated item c.
ratingSum = 0;  
weightSum = 0;
for i= 1:itemNum
    if R(user,i)~=0
        ratingSum = ratingSum + (R(user,i)+D(item,i))*S(user,i)*W(i,item);
        weightSum = weightSum + S(user,i)*W(i,item);
    end
end 
 weightSum
 ratingSum
if weightSum > 0 
    prediction = ratingSum / weightSum;
else
    prediction = 0;
end
save('matrixData2.mat','R','W','D','Sim','S','D1');
end

