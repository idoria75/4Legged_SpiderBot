clear; close all; clc; 

% Define constantes do robo
L1 = 4.250;
L2 = 6.060;
L3 = 8.973;

% Define altura da base
Z_base = 5;

% Define ponto desejado p/ efetuador final
X_EF = 2;
Y_EF = 10;
Z_EF = 0;

% Calcula theta 1
theta1 = atan2d(Y_EF,X_EF);

% Calcula distancia do efetuador 
% final para base
r = sqrt(X_EF^2+Y_EF^2);

% Calcula distancia da junta entre
% L1 e L2 ate o efetuador final
rx = r - L1;

% Calcula diagonal da junta de L1 com L2
% ate o efetuador final
K = sqrt(rx^2+Z_base^2);

% Calcula angulo auxiliar 1
aux = (L3^2-L2^2-K^2)/(-2*K*L2);
% aux_num = L3^2-L2^2-K^2;
% aux_den = -2*K*L2;
% plot([0 aux_num],[0 aux_den]);
fi1 = acosd(aux);
% fi1_ = acos(aux);
% fi1__ = arccos(aux);
% Calcula angulo auxiliar 2
fi2 = atan2d(rx,Z_base);

% Calcula theta 2
theta2 = fi1+fi2-90;

% Calcula angulo auxiliar 3
theta3_linha = acosd((K^2-L2^2-L3^2)/(-2*L2*L3));

% Calcula theta 3
theta3 = 180+theta3_linha;

% Displays results
disp('Theta 1: '); disp(theta1);
disp('Theta 2: '); disp(theta2);
disp('Theta 3: '); disp(theta3);
disp('Theta 3": '); disp(theta3_linha);

plot_cinematicaDireta(theta1,theta2,theta3_linha);
plot(Y_EF,Z_EF,'r*','MarkerSize',10);
% H1_0 = [cos(theta1) 0  sin(theta1) L1*cos(theta1);
%         sin(theta1) 0 -cos(theta1) L1*sin(theta1);
%             0       1       0             0      ;
%             0       0       0             1     ];
%         
% H2_1 = [cos(theta2) -sin(theta2) 0 L2*cos(theta2);
%         sin(theta2)  cos(theta2) 0 L2*sin(theta2);
%             0            0       1        0      ;
%             0            0       0        1     ];
% 
% H3_2 = [cos(theta3) -sin(theta3) 0 L3*cos(theta3);
%         sin(theta3)  cos(theta3) 0 L3*sin(theta3);
%             0            0       1        0      ;
%             0            0       0        1     ];
% 
% H3_0 = H1_0 * H2_1 * H3_2;
% disp(H3_0);