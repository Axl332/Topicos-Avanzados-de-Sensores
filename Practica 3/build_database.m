% BuildDataSet.m
% Construye DataSet.mat a partir de Clase1.mat ... Clase6.mat
% Codificación one-hot para redes neuronales (tansig)

clear; clc;

% --- Verificación y Carga de Archivos ---
for i = 1:6
    nombreArchivo = sprintf('Clase%d.mat', i);
    if ~exist(nombreArchivo, 'file')
        error('Error: No se encuentra el archivo %s. Debes recolectar todas las caras primero.', nombreArchivo);
    end
    load(nombreArchivo);
end

% --- Concatenación de Entradas (P) ---
P = [P1 P2 P3 P4 P5 P6];

% --- Obtención de tamaños por clase ---
N1 = size(P1,2);  N2 = size(P2,2);  N3 = size(P3,2);
N4 = size(P4,2);  N5 = size(P5,2);  N6 = size(P6,2);

% --- Creación de Etiquetas One-Hot (T) ---
T1 = repmat([ 1;-1;-1;-1;-1;-1], 1, N1);
T2 = repmat([-1; 1;-1;-1;-1;-1], 1, N2);
T3 = repmat([-1;-1; 1;-1;-1;-1], 1, N3);
T4 = repmat([-1;-1;-1; 1;-1;-1], 1, N4);
T5 = repmat([-1;-1;-1;-1; 1;-1], 1, N5);
T6 = repmat([-1;-1;-1;-1;-1; 1], 1, N6);

% Concatenación de Salidas
T = [T1 T2 T3 T4 T5 T6];

% --- Guardado Final ---
save('DataSet.mat','P','T');

% --- Resumen en Consola ---
fprintf('==========================================\n');
fprintf('DataSet.mat generado correctamente.\n');
fprintf('Total de muestras: %d\n', size(P,2));
fprintf('Entradas (P): %dx%d (Pitch y Roll normalizados)\n', size(P,1), size(P,2));
fprintf('Salidas  (T): %dx%d (6 neuronas de salida)\n', size(T,1), size(T,2));
fprintf('Muestras por clase (1-6): [%d, %d, %d, %d, %d, %d]\n', N1, N2, N3, N4, N5, N6);
fprintf('==========================================\n');