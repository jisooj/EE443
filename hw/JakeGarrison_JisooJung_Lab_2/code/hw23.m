% HW1 Question 5
% Jake and Jisoo

close all; clc; clear all;

%% Read UART
delete(instrfindall);
s = serial('COM5', 'BaudRate',115200); % Open the serial port to receive the data
set(s,'InputBufferSize',20000); % set the size of input buffer
fopen(s); % get ready to receive the data
buffersize = 128*6; % set the size of instant read of buffer
x = fread(s,buffersize,'int16'); % read the buffer when data arrive
%%
close all;
original= x(1:128*3);
flipped = x(128*3+1:end);

orig1 = original(1:128);
orig2 = original(128+1:2*128);
orig3 = original(2*128+1:end);
flip1 = flipud(flipped(1:128));
flip2 = flipud(flipped(128+1:2*128));
flip3 = flipud(flipped(2*128+1:end));

final_flip = [flip1; flip2; flip3];
original = [original(18:end); zeros(17,1)];
figure;
subplot(2,1,1);
plot(original);
xlim([0,384]);
ylim([-500, 500]);

subplot(2,1,2);
plot(final_flip);
xlim([0,384]);
ylim([-500, 500]);

figure
plot(abs(original - final_flip))
% figure;hoo
% plot(original_from_flipped);
% original - original_from_flipped
 