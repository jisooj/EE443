% EE 443 Lab 3
% Jisoo Jung, Jake Garrison

close all; clc; clear all;

N = 205;
Fs = 8000;

f1 = 2000;
f2 = 2400;
f3 = 2800;

k1 = N * f1 / Fs;  % k1 = 51 
k2 = N * f2 / Fs;  % k2 = 62
k3 = N * f3 / Fs;  % k3 = 72

% Or don't round k values
k1 = round(k1);
k2 = round(k2);
k3 = round(k3);

coeff1 = 2 * cos(2 * pi * k1 / N) * (2^14);
coeff2 = 2 * cos(2 * pi * k2 / N) * (2^14);
coeff3 = 2 * cos(2 * pi * k3 / N) * (2^14);

% ones that are negated will be negated again in C program
c1 = dec2hex(round(coeff1))
c2 = dec2hex(round(-coeff2))
c3 = dec2hex(round(-coeff3))