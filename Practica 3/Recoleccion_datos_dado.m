clear all;
clc; 
close all;

% --- Configuración inicial ---
cara = input('¿Qué cara del dado vas a registrar? (1-6): ');
if cara < 1 || cara > 6
    error('Debe ser un entero entre 1 y 6');
end

ts = 0.005; % Tiempo de muestreo del código 1
t = 0:0.1:10; % Tiempo de captura

maxValue = 1023;
minValue = 0;

% Inicialización de matrices 
datosCara = zeros(length(t), 2);

arduino = serialport("COM8", 115200);
pause(4); 

% --- Interfaz de usuario ---
fprintf('Sostenga el dado con la CARA %d hacia arriba.\n', cara);
fprintf('Recolectando datos durante %d segundos. Mueva el dado horizontalmente...\n', t(end));
pause(2);

% --- Bucle de adquisición ---
for k = 1:length(t)
    tic;
    flush(arduino);
    data = strtrim(readline(arduino));
    valores = str2double(split(data, ","));
    
    if length(valores) == 2
        datosCara(k, :) = 2*(valores' - minValue) ./ (maxValue - minValue) - 1; 
    end
    while toc < ts, end
end

clear arduino; 
disp('Captura finalizada.');

% --- Preparación de datos y Guardado ---
valueN1 = datosCara(:, 1);
valueN2 = datosCara(:, 2);

% Ensamblar matriz 
P_temp = [valueN1'; valueN2'];

% Switch de guardado manteniendo tus nombres de archivo y variables
switch cara
    case 1, P1 = P_temp; save('Clase1.mat', 'P1');
    case 2, P2 = P_temp; save('Clase2.mat', 'P2');
    case 3, P3 = P_temp; save('Clase3.mat', 'P3');
    case 4, P4 = P_temp; save('Clase4.mat', 'P4');
    case 5, P5 = P_temp; save('Clase5.mat', 'P5');
    case 6, P6 = P_temp; save('Clase6.mat', 'P6');
end

fprintf('Guardado exitoso: Clase%d.mat\n', cara);

% --- Visualización ---
figure
subplot(2,1,1); 
plot(t, valueN1); 
grid on
title(sprintf('Cara %d - Datos Normalizados (Eje 1)', cara));

subplot(2,1,2); 
plot(t, valueN2); 
grid on
title(sprintf('Cara %d - Datos Normalizados (Eje 2)', cara));
xlabel('tiempo [s]');