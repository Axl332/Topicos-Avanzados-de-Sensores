% PredecirEnVivo.m
% Lectura de Arduino Uno por puerto serie y clasificación en tiempo real.
% Requiere Weights_Dado.mat (generado con Train_Dado.m)

clear; clc; close all;

% --- Cargar el "cerebro" de la red ---
if ~exist('Weights_Dado.mat', 'file')
    error('No se encontró Weights_Dado.mat. Entrena la red primero.');
end
load Weights_Dado.mat   % Carga W1, b1, W2, b2, fhidden, foutput

% --- Configuración de Parámetros ---
ts        = 0.1;        % Tiempo de muestreo (10Hz)
maxValue  = 1023;       % Resolución ADC de Arduino Uno
minValue  = 0;

% Configuración del puerto (Asegúrate que en el IDE de Arduino sea el mismo)
arduino = serialport("COM8", 115200); 
flush(arduino);
pause(2); % El Arduino Uno se reinicia al abrir el puerto, esperamos a que inicie

disp('---------------------------------------------------------');
disp('SISTEMA DE RECONOCIMIENTO DE CARAS INICIADO');
disp('Clasificando en vivo (Presiona Ctrl+C para detener)...');
disp('---------------------------------------------------------');

nombres = {'CARA 1','CARA 2','CARA 3','CARA 4','CARA 5','CARA 6'};

% Usamos un bloque try-catch para cerrar el puerto correctamente al salir
try
    while true
        tic;
        
        % Leer línea del Arduino
        if arduino.NumBytesAvailable > 0
            data = strtrim(readline(arduino));
            valores = str2double(split(data, ","));

            if length(valores) == 2
                % 1. Normalización (Convertimos a vector columna para la red)
                pN = 2 * (valores - minValue) ./ (maxValue - minValue) - 1;
                
                % 2. Propagación hacia adelante (Predict)
                % Usamos la misma lógica del script de entrenamiento
                z1 = W1 * pN + b1;
                a1 = feval(fhidden, z1);
                
                z2 = W2 * a1 + b2;
                a2 = feval(foutput, z2);
                
                % 3. Identificar cara con valor máximo
                [~, indiceCara] = max(a2);
                
                % 4. Mostrar resultado
                fprintf('Datos: [%4.0f, %4.0f] | Norm: [%+1.2f, %+1.2f] | Predicción: %s\n', ...
                        valores(1), valores(2), pN(1), pN(2), nombres{indiceCara});
            end
        end

        % Control de tiempo de muestreo
        while toc < ts; end
    end
catch
    clear arduino;
    disp('Puerto serie cerrado. Programa terminado.');
end