% HW1 Question 3
% Jake and Jisoo

close all; clc; clear all;
% Generate sine table for c code
n = 0:19';
f = 8*1000
table = round(1000*sin(2*pi*n*f/32000))'
plot(table)

%% Read UART
s = serial('COM4', 'BaudRate',115200); % Open the serial port to receive the data
set(s,'InputBufferSize',20000); % set the size of input buffer
fopen(s); % get ready to receive the data
buffersize = 512; % set the size of instant read of buffer
x = fread(s,buffersize,'int16'); % read the buffer when data arrive
plot(x);

%% FFT
N = 32000;
fclose(s); delete(s);
figure;
b = (abs(fft(x, N))/N);
range = linspace(-N/2, N/2, N);
plot(range, fftshift(b));
xlim([-10000 10000])
xlabel('Frequency (KHz)')	 
title('FFT');	 	 
xlabel('Frequency (Hz)')	 	 
ylabel('Magnitude');