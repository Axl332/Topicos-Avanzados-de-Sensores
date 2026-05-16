% Train_Dado.m
% Entrenamiento de la red neuronal para clasificar las 6 caras del dado.

clc; clear; close all;

% --- Carga de datos ---
if ~exist('DataSet.mat', 'file')
    error('No se encontró DataSet.mat. Ejecuta primero BuildDataSet.m');
end
load DataSet.mat   % carga P (2xQ) y T (6xQ)

% --- Configuración de la Red ---
nodeHidden = 12;   
fhidden = 'tansig';
foutput = 'tansig'; 

fprintf('Iniciando entrenamiento con %d neuronas en capa oculta...\n', nodeHidden);

%% --- Proceso de Entrenamiento ---
[W1, b1, W2, b2, emedio] = neuralTrain(P, T, nodeHidden, fhidden, foutput);

% Visualización del aprendizaje
figure('Name', 'Rendimiento del Entrenamiento');
plot(emedio, 'LineWidth', 1.5, 'Color', [0 0.4470 0.7410]); 
grid on;
xlabel('Época (Iteración)'); 
ylabel('Error Cuadrático Medio (MSE)');
title(['Curva de Convergencia - ', num2str(nodeHidden), ' Neuronas']);

%% --- Evaluación de Exactitud ---
Q = size(P, 2);
aciertos = 0;
matrizConfusion = zeros(6, 6); % Para ver dónde se confunde la red

for q = 1:Q
    % Propagación hacia adelante 
    a1 = neuralPredict(W1, P(:, q), b1, fhidden);
    a2 = neuralPredict(W2, a1, b2, foutput);
    
    % Identificar qué cara predijo 
    [~, cara_pred] = max(a2);
    [~, cara_real] = max(T(:, q));
    
    if cara_pred == cara_real
        aciertos = aciertos + 1;
    end
    
    % Llenamos matriz de confusión para análisis profundo
    matrizConfusion(cara_real, cara_pred) = matrizConfusion(cara_real, cara_pred) + 1;
end

% Resultados finales
exactitud = 100 * aciertos / Q;
fprintf('\n==========================================\n');
fprintf('RESULTADOS DEL ENTRENAMIENTO\n');
fprintf('Exactitud total: %.2f%% (%d/%d muestras)\n', exactitud, aciertos, Q);
fprintf('==========================================\n');

%% --- Guardar Pesos (Cerebro de la Red) ---
save('Weights_Dado.mat', 'W1', 'b1', 'W2', 'b2', 'fhidden', 'foutput', 'nodeHidden');
disp('Pesos guardados correctamente en Weights_Dado.mat');
