matlab kod

s = serial('COM4')
set(s,'BaudRate',1200)
fopen(s)
fwrite(s,10)
// ili fprintf(s,'10')
// unosim 10, 11 , 20, 21, 30 ili 31 za paljenje i ga�enje sklopki
out = fscanf(s)

ili fread(s,4)

s = serial('COM4')
set(s,'BaudRate',1200)
fopen(s)
fwrite(s,10)
fread(s,4)