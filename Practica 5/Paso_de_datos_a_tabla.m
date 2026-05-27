% ANÁLISIS PSICOMÉTRICO 
%Integrantes:
% - Axel Perea Pinedo
% - Diego Guillermo Guardado Viramontes
% - Valeria Carrillo Hernández

clear; clc; close all;

% Desactivar advertencia de encabezados
warning('off', 'MATLAB:table:ModifiedAndSavedVarnames');

%Seleccionar el archivo manualmente
[archivo, ruta] = uigetfile('*.csv', 'Selecciona tu archivo CSV de datos');

if isequal(archivo, 0)
    disp('Operación cancelada por el usuario. No se seleccionó ningún archivo.');
    return;
end

% Construimos la ruta completa del archivo seleccionado
nombreArchivo = fullfile(ruta, archivo);

% 2. Leer la tabla de datos
opciones = detectImportOptions(nombreArchivo);
opciones.VariableNamingRule = 'preserve'; 
datosTabla = readtable(nombreArchivo, opciones);

% 3. Asignación de variables desde las columnas del CSV
tiempo   = datosTabla{:, 1}; % Columna 1: Tiempo (s)
t_aht20  = datosTabla{:, 2}; % Columna 2: T_AHT20 (°C)
t_bmp280 = datosTabla{:, 3}; % Columna 3: T_BMP280 (°C)
t_lm35   = datosTabla{:, 4}; % Columna 4: T_LM35 (°C)
hr_aht20 = datosTabla{:, 5}; % Columna 5: HR_AHT20 (%)

% 4. Creación del Gráfico Psicométrico Profesional
figure('Color', [1 1 1], 'Position', [200, 200, 850, 550]);
hold on;

plot(hr_aht20, t_aht20, '-o', 'LineWidth', 1.8, 'MarkerSize', 4, ...
     'Color', [0.11, 0.56, 1.00], 'DisplayName', 'Sensor  (AHT20)');
plot(hr_aht20, t_bmp280, '-s', 'LineWidth', 1.8, 'MarkerSize', 4, ...
     'Color', [0.18, 0.80, 0.44], 'DisplayName', 'Sensor  (BMP280)');
plot(hr_aht20, t_lm35, '-^', 'LineWidth', 1.8, 'MarkerSize', 4, ...
     'Color', [0.90, 0.22, 0.22], 'DisplayName', 'Sensor  (LM35)');

% 5. Estética y Configuración de Ejes
grid on;
grid minor; 
set(gca, 'GridLineStyle', ':', 'GridColor', [0.5 0.5 0.5], 'MinorGridLineStyle', ':');

title('Gráfico Psicrométrico: Comportamiento Térmico', ...
      'FontSize', 13, 'FontWeight', 'bold');
xlabel('Humedad Relativa (% HR)', 'FontSize', 11, 'FontWeight', 'bold');
ylabel('Temperatura (°C)', 'FontSize', 11, 'FontWeight', 'bold');

xlim([min(hr_aht20)-3, max(hr_aht20)+3]);
ylim([min(t_aht20)-2, max(t_lm35)+2]);

legend('Location', 'best', 'FontSize', 10);

% Nota del número de muestras
text(min(hr_aht20)+1, max(t_lm35)-1, ...
     ['\leftarrow Curva Dinámica Transitoria: ', num2str(length(tiempo)), ' muestras'], ...
     'FontSize', 9, 'FontWeight', 'bold', 'Color', [0.3 0.3 0.3]);

hold off;