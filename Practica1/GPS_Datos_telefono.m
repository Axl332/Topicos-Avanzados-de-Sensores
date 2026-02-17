%%Codigo para determinar datos de los sensores del celular%%
% Cargar datos
load('Calles.mat'); 
lat = Position.latitude; lon = Position.longitude; alt = Position.altitude;

% FIGURA 1: Trayectoria
figure('Name', 'Trayectoria - Calles');
geoscatter(lat, lon, 10, 'b', 'filled', 'MarkerFaceAlpha', 0.4);
geobasemap satellite;
title('Trayectoria GPS sobre mapa satelital (Calles)');

% FIGURA 2: Altitud (Estilo 900 muestras)
figure('Color', [0.1 0.1 0.1], 'Name', 'Altitud - Calles');
plot(1:length(alt), alt, 'Color', [0.2 0.6 1.0], 'LineWidth', 0.8);
grid on; set(gca, 'Color', [0.05 0.05 0.05], 'XColor', 'w', 'YColor', 'w');
title(['Variación de Altitud (', num2str(length(alt)), ' muestras)'], 'Color', 'w');
ylabel('Altitud (m)'); xlabel('Muestra');