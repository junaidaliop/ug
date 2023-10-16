function Hd = filter1
%FILTER1 Returns a discrete-time filter object.

% MATLAB Code
% Generated by MATLAB(R) 9.2 and the DSP System Toolbox 9.4.
% Generated on: 20-May-2021 20:51:26

% Equiripple Lowpass filter designed using the FIRPM function.

% All frequency values are in Hz.
Fs = 48000;  % Sampling Frequency

N     = 10;    % Order
Fpass = 0;     % Passband Frequency
Fstop = 3000;  % Stopband Frequency
Wpass = 1;     % Passband Weight
Wstop = 1;     % Stopband Weight
dens  = 20;    % Density Factor

% Calculate the coefficients using the FIRPM function.
b  = firpm(N, [0 Fpass Fstop Fs/2]/(Fs/2), [1 1 0 0], [Wpass Wstop], ...
           {dens});
Hd = dfilt.dffir(b);

% [EOF]
