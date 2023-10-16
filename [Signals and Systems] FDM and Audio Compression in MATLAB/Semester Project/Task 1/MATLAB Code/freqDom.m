% This function converts time domain signals into freq domain signals


function [y,n] = freqDom(sig,fs)
L = length(sig);
y = fft(sig,L);
y = fftshift(y);
n = ((-L/2:L/2-1)*(fs/L));
end