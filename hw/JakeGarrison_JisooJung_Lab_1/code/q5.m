% HW1 Question 5
% Jake and Jisoo

close all; clc; clear all;

%% Read UART
s = serial('COM4', 'BaudRate',115200); % Open the serial port to receive the data
set(s,'InputBufferSize',20000); % set the size of input buffer
fopen(s); % get ready to receive the data
buffersize = 512; % set the size of instant read of buffer
x = fread(s,buffersize,'int16'); % read the buffer when data arrive
plot(x);

%% FFT
N = 8000;
fclose(s); delete(s);
figure;
b = (abs(fft(x, N))/N);
range = linspace(-N/2, N/2, N);
plot(range, fftshift(b));
xlim([-5000 5000])
xlabel('Frequency (KHz)')	 
title('FFT');	 	 
xlabel('Frequency (Hz)')	 	 
ylabel('Magnitude');