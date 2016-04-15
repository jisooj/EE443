close all; clc; clear all;
set(0,'DefaultFigureWindowStyle','docked')
% delete(instrfindall);
s = serial('COM5', 'BaudRate',115200); % Open the serial port to receive the data
set(s,'InputBufferSize',20000); % set the size of input buffer
fopen(s); % get ready to receive the data
buffersize = 256; % set the size of instant read of buffer
x = fread(s,buffersize,'int16'); % read the buffer when data arrive
fclose(s);
delete(s);

%%
% input = x(1:256);
% output = x(257:end);
output = x;
N = 8000;
%----- Output ---------
plot(output);
figure;
b = (abs(fft(output, N))/N);
range = linspace(-N/2, N/2, N);
plot(range, fftshift(b));
'done'

xlim([-5000 5000])
xlabel('Frequency (KHz)')	 
title('FFT');	 	 
xlabel('Frequency (Hz)')	 	 
ylabel('Magnitude');
