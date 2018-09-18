function [ ] = plot_cinematicaDireta( theta1, theta2, theta3 )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
    L1 = 4.250;
    L2 = 6.060;
    L3 = 8.973;
    Z_base = 5;

    angulo_vertical_cotovelo = theta2;
    angulo_vertical_punho = -180+angulo_vertical_cotovelo+theta3;

    figure; title('Cinematica Inversa'); hold on; grid on;
    xlim([0 15]);
    ylim([0 10]);
    
    ponto0_x = 0;
    ponto0_y = Z_base;
    ponto1_x = L1;
    ponto1_y = Z_base;
    ponto2_x = ponto1_x + L2*cosd(theta2);
    ponto2_y = ponto1_y + L2*sind(theta2);
    ponto3_x = ponto2_x + L3*cosd(angulo_vertical_punho);
    ponto3_y = ponto2_y + L3*sind(angulo_vertical_punho);
    plot([ponto0_x ponto1_x], [ponto0_y ponto1_y]);
    plot([ponto1_x ponto2_x], [ponto1_y ponto2_y]);
    plot([ponto2_x ponto3_x], [ponto2_y ponto3_y]);
    plot(ponto3_x, ponto3_y, 'b','MarkerSize',10);    
end

