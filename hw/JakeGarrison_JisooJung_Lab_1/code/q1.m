close all; clc; clear all;
set(0,'DefaultFigureWindowStyle','docked')

s = serial('COM7', 'BaudRate',115200); % Open the serial port to receive the data
set(s,'InputBufferSize',20000); % set the size of input buffer
fopen(s); % get ready to receive the data
buffersize = 256; % set the size of instant read of buffer
x = fread(s,buffersize,'int16'); % read the buffer when data arrive


%%

N = 8000;
plot(x);
fclose(s);
delete(s);
figure;
b = (abs(fft(x, N))/N);
range = linspace(-N/2, N/2, N);

plot(range, fftshift(b));
'done'

xlim([-1000 1000])
xlabel('Frequency (KHz)')	 
title('FFT');	 	 
xlabel('Frequency (Hz)')	 	 
ylabel('Magnitude');

