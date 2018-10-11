s = serial('COM4');
set(s,'BaudRate',1200);
fopen(s)
fwrite(s,11);
fscanf(s)