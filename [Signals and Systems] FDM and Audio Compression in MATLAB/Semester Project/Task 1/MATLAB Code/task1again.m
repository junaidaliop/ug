clc
clear all
cd 'C:\Users\ALTAMASH.2712080\Desktop\abc';
% *******************************Audio Signals fed into matlab************************************************************************************************************************
[sig1,fs1] = audioread('C:\Users\ALTAMASH.2712080\Desktop\abc\amur.m4a'); 
[sig2,fs2] = audioread('C:\Users\ALTAMASH.2712080\Desktop\abc\sannan.mp4');
[sig3,fs3] = audioread('C:\Users\ALTAMASH.2712080\Desktop\abc\junaid.m4a');
[sig4,fs4] = audioread('C:\Users\ALTAMASH.2712080\Desktop\abc\faiez.m4a');

% *******************************Converting Signals into Frequency Domain************************* 
[sig1_freq, L1] = freqDom(sig1,fs1);
[sig2_freq, L2] = freqDom(sig2,fs2);
[sig3_freq, L3] = freqDom(sig3,fs3);
[sig4_freq, L4] = freqDom(sig4,fs4);

% *******************************Plotting of Signals in Freq and Time Domains*******************
plotSignals(sig1,sig2,sig3,sig4,L1,L2,L3,L4,'Original Signals in Time. Dom');
plotSignals(sig1_freq,sig2_freq,sig3_freq,sig4_freq,L1,L2,L3,L4,'Original Signals in Freq Dom');

% *******************************Calling the Low Pass filter function*****************************
LPF = filter2();

% *******************************Filtering the Audion Signals************************************
sig1_filtered = filter(LPF,sig1);
sig2_filtered = filter(LPF,sig2);
sig3_filtered = filter(LPF,sig3);
sig4_filtered = filter(LPF,sig4);

% *******************************Converting the Filtered Signals into freq domain******************
[sig1_freq, L1] = freqDom(sig1_filtered,fs1);
[sig2_freq, L2] = freqDom(sig2_filtered,fs2);
[sig3_freq, L3] = freqDom(sig3_filtered,fs3);
[sig4_freq, L4] = freqDom(sig4_filtered,fs4);

% *******************************Plotting of Filtered Signals in freq domain************************************
plotSignals(sig1_freq,sig2_freq,sig3_freq,sig4_freq,L1,L2,L3,L4,'Low-pass Filtered Signals');

% *******************************Finding the largest signal**********************************
S1 = length(sig1_filtered);
S2 = length(sig2_filtered);
S3 = length(sig3_filtered);
S4 = length(sig4_filtered);
Lmax = max([S1, S2, S3, S4]);

% *******************************Padding the Filtered Signals*********************************
sig1_padded = padarray(sig1_filtered, Lmax-S1, 0, 'post');
sig2_padded = padarray(sig2_filtered, Lmax-S2, 0, 'post');
sig3_padded = padarray(sig3_filtered, Lmax-S3, 0, 'post');
sig4_padded = padarray(sig4_filtered, Lmax-S4, 0, 'post');
[temp, LmaxVec] = freqDom(sig1_padded, fs1); %getting a vector for Lmax

% *******************************Converting the Padded Signals into freq domain******************
[sig1_freq, L1] = freqDom(sig1_padded,fs1);
[sig2_freq, L2] = freqDom(sig2_padded,fs2);
[sig3_freq, L3] = freqDom(sig3_padded,fs3);
[sig4_freq, L4] = freqDom(sig4_padded,fs4);

% *******************************Plotting the Padded Signals in freq domain*****************
plotSignals(sig1_freq,sig2_freq,sig3_freq,sig4_freq,LmaxVec,LmaxVec,LmaxVec,LmaxVec,'Padded Signals');

% *******************************Taking transpose so that matrices are ready for elemental multiplication********************************************************************
t1 = transpose([linspace(0,Lmax/fs1,Lmax) ; linspace(0,Lmax/fs1,Lmax)]);
t2 = transpose([linspace(0,Lmax/fs2,Lmax) ; linspace(0,Lmax/fs2,Lmax)]);
t3 = transpose([linspace(0,Lmax/fs3,Lmax) ; linspace(0,Lmax/fs3,Lmax)]);
t4 = transpose([linspace(0,Lmax/fs4,Lmax) ; linspace(0,Lmax/fs4,Lmax)]);

% *******************************Modulating the Signals with cosine of assigned frequencies**********************************
fm1 = 3000;
fm2 = 9000;
fm3 = 15000;
fm4 = 21000;
mod1 = cos(2*pi*fm1*t1);
mod2 = cos(2*pi*fm2*t2);
mod3 = cos(2*pi*fm3*t3);
mod4 = cos(2*pi*fm4*t4);
modded1 = sig1_padded.*mod1;
modded2 = sig2_padded.*mod2;
modded3 = sig3_padded.*mod3;
modded4 = sig4_padded.*mod4;

% *******************************Converting Modulated Signals into freq domain*******************************
[sig1_freq, L1] = freqDom(modded1,fs1);
[sig2_freq, L2] = freqDom(modded2,fs2);
[sig3_freq, L3] = freqDom(modded3,fs3);
[sig4_freq, L4] = freqDom(modded4,fs4);

% *******************************Plotting Modulated Signals in freq domain*************************
plotSignals(sig1_freq,sig2_freq,sig3_freq,sig4_freq,L1,L2,L3,L4,'Modulated Signals');

% *******************************Adding then Converting and Plotting the Modulated Signals in freq domain*****************************
added = modded1 + modded2 + modded3 + modded4;
sig_addedfreq = freqDom(added,fs1);
figure;
plot(LmaxVec,sig_addedfreq);
title('Added Signals');

% *******************************Calling Band-Pass filter functions*******************************
BPF1 = filter3();
BPF2 = filter4();
BPF3 = filter5();
BPF4 = filter6();

% ********************************Filtering the Summed Signal through Band-Pass filter********************************************
added_filtered1 = filter(BPF1,added);
added_filtered2 = filter(BPF2,added);
added_filtered3 = filter(BPF3,added);
added_filtered4 = filter(BPF4,added);
% 
% ********************************Converting the Filtered Signals into freq domain**********************************************
[sig1_freq, L1] = freqDom(added_filtered1,fs1);
[sig2_freq, L2] = freqDom(added_filtered2,fs2);
[sig3_freq, L3] = freqDom(added_filtered3,fs3);
[sig4_freq, L4] = freqDom(added_filtered4,fs4);

% ********************************Plotting Filtered Signals in freq domain*******************************************************
plotSignals(sig1_freq,sig2_freq,sig3_freq,sig4_freq,L1,L2,L3,L4,'Summed & Band-passed Signals');

% ********************************Demodulating the Signals************************************************************************
demodded1 = added_filtered1.*mod1;
demodded2 = added_filtered2.*mod2;
demodded3 = added_filtered3.*mod3;
demodded4 = added_filtered4.*mod4;

% ********************************Converting the Demodualted Signals in freq domain******************************************************
[sig1_freq, L1] = freqDom(demodded1,fs1);
[sig2_freq, L2] = freqDom(demodded2,fs2);
[sig3_freq, L3] = freqDom(demodded3,fs3);
[sig4_freq, L4] = freqDom(demodded4,fs4);

% ********************************Plotting Demodulated Signals in freq domain**************************************************************
plotSignals(sig1_freq,sig2_freq,sig3_freq,sig4_freq,L1,L2,L3,L4,'Demodulated Signals');

% ********************************Filtering the Demodulated Signals through low pass filter*************************************************
demoddedf1 = filter(LPF, demodded1);
demoddedf2 = filter(LPF, demodded2);
demoddedf3 = filter(LPF, demodded3);
demoddedf4 = filter(LPF, demodded4);

% ********************************Converting Filtered Signals into freq domain************************************************************
[sig1_freq, L1] = freqDom(demoddedf1,fs1);
[sig2_freq, L2] = freqDom(demoddedf2,fs2);
[sig3_freq, L3] = freqDom(demoddedf3,fs3);
[sig4_freq, L4] = freqDom(demoddedf4,fs4);

% ********************************Plotting the Filtered Signals in freq domain************************************************************
plotSignals(sig1_freq,sig2_freq,sig3_freq,sig4_freq,L1,L2,L3,L4,'Retrieved Signals');

% ********************************Playing the Finally Retrieved Audios*********************************************************************
audiowrite('C:\Users\ALTAMASH.2712080\Desktop\abc\amurRegen.m4a',demoddedf1,fs1);
audiowrite('C:\Users\ALTAMASH.2712080\Desktop\abc\sannanRegen.mp4',demoddedf2,fs2);
audiowrite('C:\Users\ALTAMASH.2712080\Desktop\abc\junaidRegen.m4a',demoddedf3,fs3);
audiowrite('C:\Users\ALTAMASH.2712080\Desktop\abc\faiezRegen.m4a',demoddedf4,fs4);







