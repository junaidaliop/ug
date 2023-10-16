


function [] = plotSignals(y1,y2,y3,y4,L1,L2,L3,L4,titleStr)

    figure;
    subplot(411);
    plot(L1,y1);
    title(titleStr);
    subplot(412);
    plot(L2,y2);
    subplot(413);
    plot(L3,y3);
    subplot(414);
    plot(L4,y4);

end