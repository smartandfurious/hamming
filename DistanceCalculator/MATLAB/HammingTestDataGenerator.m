function HammingTestDataGenerator

disp('Generation started');
maxBlobLength = 4000;
numofTestSets = 5;
numofExtraSets = 4;

hTest = fopen('hamming_test.txt', 'wt');
fprintf(hTest, '%d\n', numofTestSets + numofExtraSets);
for k = 1:numofTestSets
    blobLength = randi(maxBlobLength);
    if(k == 1)  blobLength = maxBlobLength; end;
    op1 = randi([0 1],1,blobLength);
    op2 = randi([0 1],1,blobLength);
    D = pdist(cat(1,op1, op2),'hamming');
    D = int16(round(D * blobLength));
    printSet(hTest, op1, op2, D);
end
% different length
blobLength = randi(maxBlobLength);
op1 = randi([0 1],1,blobLength);
op2 = randi([0 1],1,blobLength + 3);
printSet(hTest, op1, op2, -2);
% bad character
blobLength = randi(maxBlobLength);
op1 = randi([2 3],1,blobLength);
op2 = randi([3 4],1,blobLength);
printSet(hTest, op1, op2, -3);
% empty lines 
blobLength = 0;
op1 = randi([0 1],1,blobLength);
op2 = randi([0 1],1,blobLength);
printSet(hTest, op1, op2, -4);
% too long lines 
blobLength = maxBlobLength + 50;
op1 = randi([0 1],1,blobLength);
op2 = randi([0 1],1,blobLength);
printSet(hTest, op1, op2, -1);
fclose(hTest);
disp('Generation complete');
end


function printSet(hTest, op1, op2, D) 
fprintf(hTest, '%d\n', numel(op1));
for m = 1:numel(op1)
    fprintf(hTest, '%ld', op1(m));
end
fprintf(hTest, '\n');
for m = 1:numel(op2)
    fprintf(hTest, '%ld', op2(m));
end
fprintf(hTest, '\n');
fprintf(hTest, '%d\n', D);
end
