clc;
close all;
clear all;

% **************************Reading of Audio Signal************************************************
[y,Fs]=audioread('samplewave.wav');

% **************************Finding the length of Signal and Plotting it**************************
sl = length(y); % length of the wave
Slength = sl/Fs; % time for input signal
t = linspace(0, Slength, sl);
figure;
plot(t,y); %graphing the signal
xlabel('Time[s]') 
ylabel('Amplitude')
title('Original Audio Signal')

% **************************Finding and Plotting the Frequency Spectrum of the Audio Signal**********************
N = length(y);              % Length of vector y, number of samples
Y = fft(y,N);               % Fourier transform of y
Yn= fftshift(Y);
w = ((-N/2:N/2-1)*(Fs/N));  % Frequency vector
F = w/(2*pi);               % Angular frequency vector
Fn = Fs/2;                  % Nyquist Frequency            
magnitudeY = abs(Yn);       % Magnitude of the FFT
phaseY = unwrap(angle(Yn)); % Phase of the FFT
figure;
plot(F, magnitudeY);
ylabel('Magnitude, dB');
xlabel('Frequency, Hz');
title('Audio Wave Frequency Graph');

% **************************Finding and Plotting the Compressed Signal******************************************
L=600;                      %Significant Frequency Component Value taken by US!
start = find(ceil(F) == -L);%this would return a matrix
stop = find(floor(F) == L);
lowindex = start(length(start)); %last value is closest to required frequency
upindex = stop(1); %first value is closest to required values
compressed_y=zeros(1,N);
compressed_y(lowindex:upindex)=Yn(lowindex:upindex);
figure;
plot(F,abs(compressed_y));
ylabel('Magnitude, dB');
xlabel('Frequency, Hz');
title('Compressed Frequency Signal')

% ***************************Plotting the Reconstructred Signal using Comressed Signal in Time Domain************************
figure;
convert = real(ifft(fftshift(compressed_y)));
plot(t,convert);
xlabel('Time[s]')
ylabel('Signal')
title('Reconstructed Signal using the Compressed Signal in Time Domain')

% ***************************Calculating the Compressed Ratio*************************************
compressionratio = 100 - ((upindex-lowindex)/N)*100;
fprintf('Audio signal was compressed');
fprintf('\nChosen L for significant frequency components was %d',L);
fprintf('\nCompressed Ratio is : %d%%\n',compressionratio);

audiowrite('compressedsample.wav',convert,Fs);
[newy,newFs]=audioread('compressedsample.wav');
sound(newy,newFs);
figure;
sinad(newy,newFs)







